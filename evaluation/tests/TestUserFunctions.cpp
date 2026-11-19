// Native sequence and scalar functions through the harness, function values through the context, and a hand-built user function with a
// body (no parser).

#include "TestSupport.h"

#include <sysmlv2/evaluation/Evaluator.h>

#include <kerml/core/features/Feature.h>
#include <kerml/core/features/FeatureMembership.h>
#include <kerml/kernel/expressions/FeatureReferenceExpression.h>
#include <kerml/kernel/expressions/InvocationExpression.h>
#include <kerml/kernel/expressions/OperatorExpression.h>
#include <kerml/kernel/featurevalues/FeatureValue.h>
#include <kerml/kernel/functions/ResultExpressionMembership.h>

using namespace TestSupport;
using KerML::Entities::Feature;

namespace {
    void expectValue(const Result& result, const Value& expected) {
        EXPECT_EQ(result.value, expected);
        EXPECT_TRUE(result.diagnostics.empty()) << (result.diagnostics.empty() ? "" : result.diagnostics.front().message);
    }

    void expectOneError(const Result& result, const std::string& fragment, const ExpressionPtr& element) {
        ASSERT_EQ(result.diagnostics.size(), 1u) << (result.diagnostics.empty() ? "no diagnostic" : result.diagnostics.front().message);
        EXPECT_NE(result.diagnostics.front().message.find(fragment), std::string::npos) << result.diagnostics.front().message;
        EXPECT_EQ(result.diagnostics.front().element, element);
        EXPECT_TRUE(result.value.isNull());
    }

    std::string Q(const char* package, const char* name) { return std::string(package) + "::" + name; }
    Value Nil() { return Value(); }
    Value Real(double value) { return Value::real(value); }

    std::vector<Case> sequenceCases() {
        const auto seq = [](const char* name) { return Q("SequenceFunctions", name); };
        return {
            {seq("size"), {Seq({1, 2, 3})}, I(3), ""},
            {seq("size"), {Nil()}, I(0), ""},
            {seq("isEmpty"), {Nil()}, B(true), ""},
            {seq("notEmpty"), {Nil()}, B(false), ""},
            {seq("includes"), {Seq({1, 2, 3}), Seq({3, 1})}, B(true), ""},
            {seq("includes"), {Seq({1, 2}), Seq({3})}, B(false), ""},
            {seq("includes"), {Seq({1, 2}), Nil()}, B(true), ""},
            {seq("includesOnly"), {Seq({1, 2, 2}), Seq({2, 1})}, B(true), ""},
            {seq("excludes"), {Seq({1, 2}), Seq({3})}, B(true), ""},
            {seq("union"), {Seq({1}), Seq({2, 3})}, Seq({1, 2, 3}), ""},
            {seq("intersection"), {Seq({1, 2, 3, 2}), Seq({2})}, Seq({2, 2}), ""},
            {seq("excluding"), {Seq({1, 2, 3}), Seq({2})}, Seq({1, 3}), ""},
            {seq("including"), {Seq({1}), Seq({9})}, Seq({1, 9}), ""},
            {seq("includingAt"), {Seq({1, 2, 3}), Seq({9}), I(2)}, Seq({1, 9, 3}), ""},
            {seq("excludingAt"), {Seq({1, 2, 3, 4}), I(2), I(3)}, Seq({1, 4}), ""},
            {seq("subsequence"), {Seq({1, 2, 3, 4}), I(2), I(3)}, Seq({2, 3}), ""},
            {seq("subsequence"), {Seq({1, 2, 3, 4}), I(3)}, Seq({3, 4}), ""},
            {seq("subsequence"), {Seq({1, 2, 3}), I(0), I(9)}, Seq({1, 2, 3}), ""},
            {seq("subsequence"), {Seq({1, 2, 3}), I(3), I(2)}, Nil(), ""},
            {seq("subsequence"), {Seq({1, 2, 3}), S("x")}, Nil(), "unsupported argument types"},
            {seq("head"), {Seq({7, 8})}, I(7), ""},
            {seq("head"), {Nil()}, Nil(), ""},
            {seq("tail"), {Seq({7, 8, 9})}, Seq({8, 9}), ""},
            {seq("last"), {Seq({7, 8, 9})}, I(9), ""},
            {seq("last"), {Nil()}, Nil(), ""},
            {seq("equals"), {Seq({1, 2}), Seq({1, 2})}, B(true), ""},
            {seq("equals"), {Seq({1, 2}), Seq({1})}, B(false), ""},
            {seq("size"), {}, Nil(), "expected 1 argument(s) but got 0"},
            {BF("#"), {Seq({10, 20, 30}), I(2)}, I(20), ""},
            {BF("#"), {Seq({10, 20, 30}), I(4)}, Nil(), ""},
            {BF("#"), {Seq({10, 20, 30}), I(0)}, Nil(), ""},
            {BF("#"), {Seq({10, 20, 30}), I(-1)}, Nil(), ""},
            {BF("#"), {Seq({10, 20, 30}), Seq({3, 1})}, Seq({30, 10}), ""},
            {BF("#"), {Seq({10, 20, 30}), S("a")}, Nil(), "unsupported argument types"},
            {BF("#"), {Nil(), I(1)}, Nil(), ""},
        };
    }

    std::vector<Case> scalarCases() {
        const auto num = [](const char* name) { return Q("NumericalFunctions", name); };
        return {
            {num("sum"), {Seq({1, 2, 3})}, I(6), ""},
            {num("sum"), {Nil()}, I(0), ""},
            {num("sum"), {Value(std::vector<Item>{Item(std::int64_t(1)), Item(2.5)})}, Real(3.5), ""},
            {num("sum"), {Seq({Max, 1})}, Nil(), "Integer overflow"},
            {num("sum"), {Value(std::vector<Item>{Item(std::string("a"))})}, Nil(), "unsupported argument types"},
            {Q("RealFunctions", "sum"), {Nil()}, Real(0.0), ""},
            {Q("IntegerFunctions", "sum"), {Seq({4, 5})}, I(9), ""},
            {num("product"), {Seq({2, 3, 4})}, I(24), ""},
            {num("product"), {Nil()}, I(1), ""},
            {num("abs"), {I(-5)}, I(5), ""},
            {num("abs"), {Real(-2.5)}, Real(2.5), ""},
            {num("abs"), {I(Min)}, Nil(), "Integer overflow"},
            {num("isZero"), {I(0)}, B(true), ""},
            {num("isUnit"), {Real(1.0)}, B(true), ""},
            {Q("DataFunctions", "max"), {I(3), Real(7.5)}, Real(7.5), ""},
            {Q("DataFunctions", "min"), {I(3), I(1)}, I(1), ""},
            {Q("DataFunctions", "max"), {S("a"), S("b")}, S("b"), ""},
            {Q("DataFunctions", "min"), {S("a"), I(1)}, Nil(), "unsupported argument types"},
            {Q("DataFunctions", "max"), {Nil(), I(1)}, Nil(), ""},
            {Q("RealFunctions", "sqrt"), {I(9)}, Real(3.0), ""},
            {Q("RealFunctions", "sqrt"), {I(-1)}, Nil(), "square root of a negative"},
            {Q("RealFunctions", "floor"), {Real(-2.1)}, I(-3), ""},
            {Q("RealFunctions", "floor"), {Real(1e30)}, Nil(), "is not an Integer"},
            {Q("RealFunctions", "round"), {Real(2.5)}, I(3), ""},
            {Q("RealFunctions", "round"), {Real(-2.5)}, I(-3), ""},
            {Q("RealFunctions", "ToInteger"), {Real(-2.9)}, I(-2), ""},
            {Q("IntegerFunctions", "ToInteger"), {S("-12")}, I(-12), ""},
            {Q("IntegerFunctions", "ToInteger"), {S("1x")}, Nil(), "is not an Integer"},
            {Q("IntegerFunctions", "ToNatural"), {I(-1)}, Nil(), "not a Natural"},
            {Q("RealFunctions", "ToReal"), {S("1e3")}, Real(1000.0), ""},
            {Q("RealFunctions", "ToReal"), {S("nan")}, Nil(), "is not a Real"},
            {Q("BooleanFunctions", "ToBoolean"), {S("false")}, B(false), ""},
            {Q("BooleanFunctions", "ToBoolean"), {S("yes")}, Nil(), "is not a Boolean"},
            {Q("BaseFunctions", "ToString"), {Real(2.0)}, S("2.0"), ""},
            {Q("BaseFunctions", "ToString"), {S("x")}, S("x"), ""},
            {Q("BaseFunctions", "ToString"), {Nil()}, Nil(), ""},
            {Q("RationalFunctions", "gcd"), {I(-12), I(18)}, I(6), ""},
            {Q("RationalFunctions", "rat"), {I(1), I(0)}, Nil(), "division by zero"},
            {Q("TrigFunctions", "cos"), {Real(0.0)}, Real(1.0), ""},
            {Q("TrigFunctions", "arcsin"), {Real(1.5)}, Nil(), "outside of [-1, 1]"},
            {Q("StringFunctions", "Length"), {S("h\xc3\xa9llo")}, I(5), ""},          // (UTF-8: five characters)
            {Q("StringFunctions", "Substring"), {S("h\xc3\xa9llo"), I(2), I(3)}, S("\xc3\xa9l"), ""},
            {Q("StringFunctions", "Substring"), {S("abc"), I(0), I(1)}, Nil(), "outside of a string"},
            {Q("StringFunctions", "Substring"), {S("abc"), I(4), I(3)}, S(""), ""},
        };
    }
}

TEST(NativeSequenceFunctions, Table) { runCases(sequenceCases()); }
TEST(NativeScalarFunctions, Table) { runCases(scalarCases()); }

TEST(NativeSequenceFunctions, TheLengthOfConcatenationsIsLimited) {
    Harness harness;
    harness.Context.setMaxSequenceLength(4);
    const Value result = harness.call(Q("SequenceFunctions", "union"), {Seq({1, 2, 3}), Seq({4, 5})});
    EXPECT_TRUE(result.isNull());
    EXPECT_TRUE(hasError(harness.Context.diagnostics(), "longer than the limit"));
}

// Function values ------------------------------------------------------------------------------------------------------------

TEST(FunctionValues, TheInvokerOfTheContextIsCalledWithTheArgumentValues) {
    EvaluationContext context;
    context.setFunctionInvoker([](const ExpressionPtr&, std::vector<Value> arguments, EvaluationContext&) {
        std::int64_t sum = 0;
        for (const Value& argument : arguments) sum += argument.asInteger().value_or(0);
        return Value::integer(sum);
    });
    const ExpressionPtr callable = std::make_shared<Expression>();
    EXPECT_EQ(context.invokeFunctionValue(callable, {I(2), I(3)}), I(5));
    EXPECT_EQ(context.depth(), 0u);
    // without an invoker, or without a function, it is an Error
    EvaluationContext bare;
    EXPECT_TRUE(bare.invokeFunctionValue(callable, {}).isNull());
    EXPECT_TRUE(bare.hasErrors());
    EXPECT_TRUE(context.invokeFunctionValue(nullptr, {}).isNull());
    EXPECT_TRUE(context.hasErrors());
}

TEST(FunctionValues, TheDepthLimitAlsoCountsFunctionValueCalls) {
    EvaluationContext context;
    context.setMaxDepth(5);
    context.setFunctionInvoker([](const ExpressionPtr& function, std::vector<Value> arguments, EvaluationContext& inner) {
        return inner.invokeFunctionValue(function, std::move(arguments));   // (endless)
    });
    const ExpressionPtr callable = std::make_shared<Expression>();
    EXPECT_TRUE(context.invokeFunctionValue(callable, {}).isNull());
    EXPECT_TRUE(hasError(context.diagnostics(), "maximum evaluation depth of 5"));
    EXPECT_EQ(context.depth(), 0u);
}

// A hand-built user function with a body --------------------------------------------------------------------------------------

namespace {
    /// `function F { in x; in y default 10; x * 2 + y }` below a package.
    struct DoubledPlus {
        std::shared_ptr<KerML::Entities::Function> Function;
        std::shared_ptr<Feature> X, Y;

        DoubledPlus() {
            Function = makeFunction("F", makePackage("MyFunctions", makeRoot()));
            X = parameter("x", nullptr);
            Y = parameter("y", integer10());
            const auto reference = [](const std::shared_ptr<Feature>& parameter) {
                auto expression = std::make_shared<KerML::Entities::FeatureReferenceExpression>();
                expression->setReferent(parameter);
                return expression;
            };
            auto times = std::make_shared<KerML::Entities::OperatorExpression>();
            times->setOperatorName("*");
            times->setArgument({reference(X), literalInteger(2)});
            auto plus = std::make_shared<KerML::Entities::OperatorExpression>();
            plus->setOperatorName("+");
            plus->setArgument({times, reference(Y)});
            auto result = std::make_shared<KerML::Entities::ResultExpressionMembership>();
            result->setMemberElement(plus);
            std::vector<std::shared_ptr<KerML::Entities::Relationship>> relationships = Function->ownedRelationship();
            relationships.push_back(result);
            Function->setOwnedRelationship(relationships);
        }

        ~DoubledPlus() {
            for (const auto& parameter : {X, Y}) KerML::Entities::disposeLinks(*parameter);
        }

    private:
        static ExpressionPtr integer10() { return literalInteger(10); }

        std::shared_ptr<Feature> parameter(const std::string& name, const ExpressionPtr& defaultValue) {
            auto feature = std::make_shared<Feature>();
            feature->setDeclaredName(name);
            feature->setDirection(KerML::Entities::IN);
            feature->setOwner(Function);
            if (defaultValue) {
                auto value = std::make_shared<KerML::Entities::FeatureValue>();
                value->setValue(defaultValue);
                feature->appendOwnedElement(value);
            }
            auto membership = std::make_shared<KerML::Entities::FeatureMembership>();
            membership->setMemberElement(feature);
            auto relationships = Function->ownedRelationship();
            relationships.push_back(membership);
            Function->setOwnedRelationship(relationships);
            return feature;
        }
    };
}

TEST(UserFunctionsHandBuilt, ABodyRunsWithTheArgumentsBoundToTheParameters) {
    const Evaluator evaluator;
    DoubledPlus model;
    const auto invocation = [&](const std::vector<ExpressionPtr>& arguments) {
        auto call = std::make_shared<KerML::Entities::InvocationExpression>();
        call->setFunction(model.Function);
        call->setInstantiatedType(model.Function);
        call->setArgument(arguments);
        return call;
    };
    expectValue(evaluator.evaluate(invocation({literalInteger(3), literalInteger(1)})), I(7));
    expectValue(evaluator.evaluate(invocation({literalInteger(3)})), I(16));   // (the default of y)
    // nested calls and arguments that are calls
    expectValue(evaluator.evaluate(invocation({invocation({literalInteger(1)}), literalInteger(0)})), I(24));
    // too many arguments
    const auto tooMany = invocation({literalInteger(1), literalInteger(2), literalInteger(3)});
    expectOneError(evaluator.evaluate(tooMany), "too many arguments", tooMany);
}
