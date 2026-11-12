#include "TestSupport.h"

#include <kerml/kernel/expressions/OperatorFunctions.h>

#include <algorithm>
#include <cstring>

using namespace TestSupport;

namespace {
    // Operators of KerML::operatorFunctions that have no native implementation yet. Every other entry must be registered.
    const char* const NotImplemented[] = {
        "BaseFunctions::'['",     "BaseFunctions::'#'",      "BaseFunctions::'all'",        "BaseFunctions::'istype'",
        "BaseFunctions::'hastype'", "BaseFunctions::'@'",    "BaseFunctions::'@@'",         "BaseFunctions::'as'",
        "BaseFunctions::'meta'",  "ControlFunctions::'.'",   "ControlFunctions::collect",   "ControlFunctions::select",
        "DataFunctions::'~'",
    };

    bool isNotImplemented(const char* name) {
        return std::any_of(std::begin(NotImplemented), std::end(NotImplemented), [name](const char* entry) { return std::strcmp(entry, name) == 0; });
    }
}

TEST(Registry, EveryOperatorFunctionIsRegisteredOrListedAsNotImplemented) {
    const FunctionRegistry registry = FunctionRegistry::withStandardFunctions();
    std::size_t registered = 0;
    for (const KerML::OperatorFunction& entry : KerML::operatorFunctions) {
        const bool found = registry.find(std::string(entry.functionName)) != nullptr;
        if (isNotImplemented(entry.functionName)) {
            EXPECT_FALSE(found) << entry.functionName << " is registered: remove it from the list of the missing functions";
        } else {
            EXPECT_TRUE(found) << entry.functionName << " is neither registered nor listed as not implemented";
            if (found) ++registered;
        }
    }
    EXPECT_EQ(registered + std::size(NotImplemented), KerML::operatorFunctionCount);
    EXPECT_EQ(registered, 26u);
    // (a list entry that is not in the table would be a typo)
    for (const char* name : NotImplemented) {
        const auto* end = KerML::operatorFunctions + KerML::operatorFunctionCount;
        EXPECT_NE(std::find_if(KerML::operatorFunctions, end, [name](const KerML::OperatorFunction& e) { return std::strcmp(e.functionName, name) == 0; }), end)
            << name;
    }
}

TEST(Registry, FindByNameAndUnknownFunction) {
    const FunctionRegistry registry = FunctionRegistry::withStandardFunctions();
    EXPECT_NE(registry.find(std::string("DataFunctions::'+'")), nullptr);
    EXPECT_EQ(registry.find(std::string("DataFunctions::'nope'")), nullptr);
    EXPECT_EQ(registry.find(std::string("")), nullptr);
    EXPECT_EQ(FunctionRegistry().find(std::string("DataFunctions::'+'")), nullptr);
    EXPECT_EQ(registry.find(std::shared_ptr<KerML::Entities::Function>()), nullptr);
}

TEST(Registry, RegisterReplacesAndUserFunctionsWork) {
    Harness harness;
    harness.Registry.registerFunction("My::answer", [](EvaluationContext&, const std::vector<ExpressionPtr>&) { return I(1); });
    EXPECT_EQ(harness.call("My::answer", {}), I(1));
    harness.Registry.registerFunction("My::answer", [](EvaluationContext&, const std::vector<ExpressionPtr>&) { return I(2); });
    EXPECT_EQ(harness.call("My::answer", {}), I(2));

    // A standard function can be replaced as well.
    harness.Registry.registerFunction("DataFunctions::'+'", [](EvaluationContext&, const std::vector<ExpressionPtr>&) { return S("replaced"); });
    EXPECT_EQ(harness.call("DataFunctions::'+'", {I(1), I(2)}), S("replaced"));
}

TEST(Registry, StrictFunctionsGetTheEvaluatedArguments) {
    Harness harness;
    harness.Registry.registerStrictFunction("My::count", [](EvaluationContext&, const std::vector<Value>& arguments) {
        return I(static_cast<std::int64_t>(arguments.size()) * 10 + (arguments.empty() ? 0 : static_cast<std::int64_t>(arguments[0].size())));
    });
    EXPECT_EQ(harness.call("My::count", {Seq({1, 2, 3}), N()}), I(23));
    EXPECT_EQ(harness.call("My::count", {}), I(0));
    const auto first = harness.stand(I(1));
    const auto second = harness.stand(I(2));
    (void)harness.callExpressions("My::count", {first, second});
    EXPECT_TRUE(harness.wasEvaluated(first));
    EXPECT_TRUE(harness.wasEvaluated(second));
}

TEST(Registry, FindsTheImplementationAlongTheSpecializationChain) {
    const auto root = makeRoot();
    const auto dataPackage = makePackage("DataFunctions", root);
    const auto numericalPackage = makePackage("NumericalFunctions", root);
    const auto integerPackage = makePackage("IntegerFunctions", root);
    const auto naturalPackage = makePackage("NaturalFunctions", root);
    const auto dataPlus = makeFunction("+", dataPackage);
    const auto numericalPlus = makeFunction("+", numericalPackage);
    const auto integerPlus = makeFunction("+", integerPackage);
    const auto naturalPlus = makeFunction("+", naturalPackage);
    specialize(naturalPlus, integerPlus);
    specialize(integerPlus, numericalPlus);
    specialize(numericalPlus, dataPlus);

    FunctionRegistry registry = FunctionRegistry::withStandardFunctions();
    const NativeFunction* standard = registry.find(std::string("DataFunctions::'+'"));
    ASSERT_NE(standard, nullptr);
    EXPECT_EQ(registry.find(dataPlus), standard);
    EXPECT_EQ(registry.find(naturalPlus), standard);   // (three generals up)

    // The nearest registered general wins.
    registry.registerFunction("IntegerFunctions::'+'", [](EvaluationContext&, const std::vector<ExpressionPtr>&) { return I(99); });
    const NativeFunction* integerImplementation = registry.find(std::string("IntegerFunctions::'+'"));
    EXPECT_EQ(registry.find(naturalPlus), integerImplementation);
    EXPECT_EQ(registry.find(numericalPlus), registry.find(std::string("DataFunctions::'+'")));

    // A function with no registered name in its chain.
    const auto other = makeFunction("unknown", makePackage("Elsewhere", root));
    EXPECT_EQ(registry.find(other), nullptr);

    // (break the shared_ptr cycles of the test model)
    disposeAll({dataPlus, numericalPlus, integerPlus, naturalPlus, other});
}

TEST(Registry, LookupTellsOwnFromInheritedImplementations) {
    const auto root = makeRoot();
    const auto dataPlus = makeFunction("+", makePackage("DataFunctions", root));
    const auto integerPlus = makeFunction("+", makePackage("IntegerFunctions", root));
    const auto naturalPlus = makeFunction("+", makePackage("NaturalFunctions", root));
    specialize(naturalPlus, integerPlus);
    specialize(integerPlus, dataPlus);

    FunctionRegistry registry = FunctionRegistry::withStandardFunctions();
    const auto own = registry.lookup(dataPlus);
    ASSERT_NE(own.implementation, nullptr);
    EXPECT_FALSE(own.inherited);
    const auto inherited = registry.lookup(naturalPlus);
    EXPECT_EQ(inherited.implementation, own.implementation);
    EXPECT_TRUE(inherited.inherited);
    EXPECT_EQ(registry.find(naturalPlus), inherited.implementation);

    // Once the function itself has an implementation it is not inherited any more.
    registry.registerFunction("IntegerFunctions::'+'", [](EvaluationContext&, const std::vector<ExpressionPtr>&) { return I(1); });
    const auto direct = registry.lookup(integerPlus);
    EXPECT_FALSE(direct.inherited);
    EXPECT_NE(direct.implementation, own.implementation);
    EXPECT_TRUE(registry.lookup(naturalPlus).inherited);
    EXPECT_EQ(registry.lookup(naturalPlus).implementation, direct.implementation);

    const auto none = registry.lookup(makeFunction("unknown", nullptr));
    EXPECT_EQ(none.implementation, nullptr);
    EXPECT_FALSE(none.inherited);
    EXPECT_EQ(registry.lookup(nullptr).implementation, nullptr);

    disposeAll({dataPlus, integerPlus, naturalPlus});
}

TEST(Registry, HeldPointersSurviveOtherRegistrationsAndSeeReplacements) {
    Harness harness;
    harness.Registry.registerFunction("My::f", [](EvaluationContext&, const std::vector<ExpressionPtr>&) { return I(1); });
    const NativeFunction* held = harness.Registry.find(std::string("My::f"));
    ASSERT_NE(held, nullptr);
    for (int index = 0; index < 100; ++index) {
        harness.Registry.registerFunction("My::other" + std::to_string(index), [](EvaluationContext&, const std::vector<ExpressionPtr>&) { return I(0); });
    }
    EXPECT_EQ(harness.Registry.find(std::string("My::f")), held);
    EXPECT_EQ((*held)(harness.Context, {}), I(1));
    harness.Registry.registerFunction("My::f", [](EvaluationContext&, const std::vector<ExpressionPtr>&) { return I(2); });
    EXPECT_EQ((*held)(harness.Context, {}), I(2));   // (the held pointer calls the replacement)
}

TEST(Registry, ChainWalkIsBreadthFirstAndHandlesSeveralGenerals) {
    const auto root = makeRoot();
    const auto pkg = makePackage("P", root);
    const auto leaf = makeFunction("leaf", pkg);
    const auto left = makeFunction("left", pkg);
    const auto right = makeFunction("right", pkg);
    const auto deep = makeFunction("deep", pkg);
    specialize(leaf, left);
    specialize(leaf, right);
    specialize(left, deep);
    struct Cleanup {
        std::vector<std::shared_ptr<KerML::Entities::Function>> functions;
        ~Cleanup() { disposeAll(functions); }
    } cleanup{{leaf, left, right, deep}};

    FunctionRegistry registry;
    registry.registerFunction("P::deep", [](EvaluationContext&, const std::vector<ExpressionPtr>&) { return I(1); });
    registry.registerFunction("P::right", [](EvaluationContext&, const std::vector<ExpressionPtr>&) { return I(2); });
    // right is one level up, deep two: breadth-first finds right first.
    EXPECT_EQ(registry.find(leaf), registry.find(std::string("P::right")));
}

TEST(Registry, CyclicSpecializationDoesNotHang) {
    const auto root = makeRoot();
    const auto pkg = makePackage("Cycle", root);
    const auto a = makeFunction("a", pkg);
    const auto b = makeFunction("b", pkg);
    const auto self = makeFunction("self", pkg);
    specialize(a, b);
    specialize(b, a);
    specialize(self, self);
    const FunctionRegistry registry = FunctionRegistry::withStandardFunctions();
    EXPECT_EQ(registry.find(a), nullptr);
    EXPECT_EQ(registry.find(self), nullptr);

    FunctionRegistry with;
    with.registerFunction("Cycle::b", [](EvaluationContext&, const std::vector<ExpressionPtr>&) { return I(3); });
    EXPECT_EQ(with.find(a), with.find(std::string("Cycle::b")));

    // (break the shared_ptr cycles of the test model)
    disposeAll({a, b, self});
}
