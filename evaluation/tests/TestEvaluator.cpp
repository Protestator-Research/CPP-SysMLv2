// Tests of the Evaluator on hand-built expressions (no parser): dispatch, the lookup of the functions with and without a bound
// function(), diagnostics, the depth limit, the lookup cache, concurrency and exceptions.

#include "TestSupport.h"

#include <sysmlv2/evaluation/Evaluator.h>

#include <kerml/core/features/Feature.h>
#include <kerml/core/features/FeatureMembership.h>
#include <kerml/core/features/Redefinition.h>
#include <kerml/kernel/expressions/CollectExpression.h>
#include <kerml/kernel/expressions/ConstructorExpression.h>
#include <kerml/kernel/expressions/FeatureChainExpression.h>
#include <sysmlv2/evaluation/ModelLevelEvaluable.h>
#include <kerml/kernel/expressions/FeatureReferenceExpression.h>
#include <kerml/kernel/expressions/IndexExpression.h>
#include <kerml/kernel/expressions/InvocationExpression.h>
#include <kerml/kernel/expressions/MetadataAccessExpression.h>
#include <kerml/kernel/expressions/OperatorExpression.h>
#include <kerml/kernel/expressions/SelectExpression.h>
#include <kerml/kernel/featurevalues/FeatureValue.h>
#include <kerml/kernel/functions/ParameterMembership.h>
#include <kerml/kernel/functions/ReturnParameterMembership.h>
#include <kerml/root/namespaces/Membership.h>

#include <atomic>
#if defined(__unix__) || defined(__APPLE__)
#include <pthread.h>
#endif
#include <iostream>
#include <new>
#include <stdexcept>
#include <thread>

using namespace TestSupport;
using KerML::Entities::Feature;
using KerML::Entities::Function;
using KerML::Entities::InvocationExpression;
using KerML::Entities::OperatorExpression;

namespace {
    ExpressionPtr integer(std::int64_t value) { return literalInteger(value); }
    ExpressionPtr boolean(bool value) { return literalBoolean(value); }

    ExpressionPtr real(double value) {
        auto literal = std::make_shared<KerML::Entities::LiteralRational>();
        literal->setValue(value);
        return literal;
    }

    ExpressionPtr text(const std::string& value) {
        auto literal = std::make_shared<KerML::Entities::LiteralString>();
        literal->setValue(value);
        return literal;
    }

    /// An operator expression without a bound function (it is found through the name of the operator).
    std::shared_ptr<OperatorExpression> op(const std::string& name, const std::vector<ExpressionPtr>& arguments,
                                           const std::shared_ptr<Function>& function = nullptr) {
        auto expression = std::make_shared<OperatorExpression>();
        expression->setOperatorName(name);
        expression->setArgument(arguments);
        if (function) {
            expression->setFunction(function);
            expression->setInstantiatedType(function);
        }
        return expression;
    }

    std::shared_ptr<InvocationExpression> invoke(const std::shared_ptr<Function>& function, const std::vector<ExpressionPtr>& arguments) {
        auto expression = std::make_shared<InvocationExpression>();
        expression->setArgument(arguments);
        if (function) {
            expression->setFunction(function);
            expression->setInstantiatedType(function);
        }
        return expression;
    }

    /// `Package::name` below the root namespace of a source, as the standard library has it.
    std::shared_ptr<Function> libraryFunction(const std::string& package, const std::string& name) {
        return makeFunction(name, makePackage(package, makeRoot()));
    }

    /// Exactly one Error containing @p fragment, located at @p element (if given).
    void expectOneError(const Result& result, const std::string& fragment, const ExpressionPtr& element = nullptr) {
        ASSERT_EQ(result.diagnostics.size(), 1u) << (result.diagnostics.empty() ? "no diagnostic" : result.diagnostics.front().message);
        const Diagnostic& diagnostic = result.diagnostics.front();
        EXPECT_EQ(diagnostic.severity, Severity::Error);
        EXPECT_NE(diagnostic.message.find(fragment), std::string::npos) << diagnostic.message;
        if (element) {
            EXPECT_EQ(diagnostic.element, element);
        }
        EXPECT_TRUE(result.value.isNull());
        EXPECT_FALSE(result.ok());
    }

    void expectValue(const Result& result, const Value& expected) {
        EXPECT_EQ(result.value, expected);
        EXPECT_TRUE(result.diagnostics.empty()) << (result.diagnostics.empty() ? "" : result.diagnostics.front().message);
        EXPECT_TRUE(result.ok());
    }

    /// A chain of @p count unary minus operators around the literal 1.
    ExpressionPtr minusChain(std::size_t count) {
        ExpressionPtr current = integer(1);
        for (std::size_t index = 0; index < count; ++index) current = op("-", {current});
        return current;
    }
}

// Literals ---------------------------------------------------------------------------------------------------------------------

TEST(EvaluatorLiterals, EveryLiteralKindAndNull) {
    const Evaluator evaluator;
    expectValue(evaluator.evaluate(boolean(true)), B(true));
    expectValue(evaluator.evaluate(boolean(false)), B(false));
    expectValue(evaluator.evaluate(integer(-42)), I(-42));
    expectValue(evaluator.evaluate(integer(Max)), I(Max));
    expectValue(evaluator.evaluate(real(2.5)), R(2.5));
    expectValue(evaluator.evaluate(text("hello")), S("hello"));
    expectValue(evaluator.evaluate(text("")), S(""));
    expectValue(evaluator.evaluate(std::make_shared<KerML::Entities::LiteralInfinity>()), Inf());
    expectValue(evaluator.evaluate(std::make_shared<KerML::Entities::NullExpression>()), N());
}

TEST(EvaluatorLiterals, ARealLiteralStaysARealAndAnIntegerAnInteger) {
    const Evaluator evaluator;
    EXPECT_NE(evaluator.evaluate(real(2.0)).value, I(2));
    EXPECT_EQ(evaluator.evaluate(real(2.0)).value, R(2.0));
}

TEST(EvaluatorInputs, NullPointersAreErrors) {
    const Evaluator evaluator;
    const Result expression = evaluator.evaluate(ExpressionPtr());
    expectOneError(expression, "missing expression");
    const Result feature = evaluator.evaluateFeatureValue(std::shared_ptr<Feature>());
    expectOneError(feature, "missing feature");
}

TEST(EvaluatorInputs, TheTargetIsAcceptedAndIgnored) {
    const Evaluator evaluator;
    const auto target = std::make_shared<KerML::Entities::Namespace>();
    expectValue(evaluator.evaluate(op("+", {integer(1), integer(2)}), target), I(3));
}

// Operators --------------------------------------------------------------------------------------------------------------------

TEST(EvaluatorOperators, NestedOperatorsWithoutABoundFunctionUseTheNameOfTheOperator) {
    const Evaluator evaluator;
    // (2 + 3) * 4 - 1
    const auto expression = op("-", {op("*", {op("+", {integer(2), integer(3)}), integer(4)}), integer(1)});
    expectValue(evaluator.evaluate(expression), I(19));
    expectValue(evaluator.evaluate(op("/", {integer(7), integer(2)})), R(3.5));
    expectValue(evaluator.evaluate(op("+", {text("a"), text("b")})), S("ab"));
    expectValue(evaluator.evaluate(op("==", {integer(1), real(1.0)})), B(true));
    expectValue(evaluator.evaluate(op("-", {integer(5)})), I(-5));
    expectValue(evaluator.evaluate(op(",", {integer(1), integer(2)})), Seq({1, 2}));
}

TEST(EvaluatorOperators, ABoundFunctionIsFoundInTheRegistryByItsQualifiedName) {
    const Evaluator evaluator;
    const auto plus = libraryFunction("DataFunctions", "+");
    expectValue(evaluator.evaluate(op("+", {integer(1), integer(2)}, plus)), I(3));
}

TEST(EvaluatorOperators, ABoundSpecializationInheritsTheImplementationOfItsGeneral) {
    const Evaluator evaluator;
    const auto root = makeRoot();
    const auto general = makeFunction("+", makePackage("DataFunctions", root));
    const auto specific = makeFunction("+", makePackage("IntegerFunctions", root));
    specialize(specific, general);
    expectValue(evaluator.evaluate(op("+", {integer(40), integer(2)}, specific)), I(42));
    disposeAll({general, specific});
}

TEST(EvaluatorOperators, ABoundFunctionWinsOverTheNameOfTheOperator) {
    // `+` bound to a function that has no implementation: no silent fallback to DataFunctions::'+'
    const Evaluator evaluator;
    const auto other = libraryFunction("MyFunctions", "plus");
    const Result result = evaluator.evaluate(op("+", {integer(1), integer(2)}, other));
    expectOneError(result, "MyFunctions::plus");
    EXPECT_NE(result.diagnostics.front().message.find("operator '+'"), std::string::npos);
}

TEST(EvaluatorOperators, AnUnknownOperatorIsAnError) {
    const Evaluator evaluator;
    const auto expression = op("frobnicate", {integer(1)});
    const Result result = evaluator.evaluate(expression);
    expectOneError(result, "operator 'frobnicate'", expression);
}

TEST(EvaluatorOperators, AnOperatorWithoutAnImplementationNamesTheOperatorAndTheFunction) {
    const Evaluator evaluator;
    const auto expression = op("~", {integer(1)});
    const Result result = evaluator.evaluate(expression);
    expectOneError(result, "no native implementation for DataFunctions::'~'", expression);
    EXPECT_NE(result.diagnostics.front().message.find("operator '~'"), std::string::npos);
}

TEST(EvaluatorOperators, AnArrowWithoutAFunctionIsAnError) {
    const Evaluator evaluator;
    const auto expression = op("->", {integer(1)});
    expectOneError(evaluator.evaluate(expression), "operator '->' is not bound", expression);
}

TEST(EvaluatorOperators, ErrorsAreLocatedAtTheExpressionWhereTheyOccurred) {
    const Evaluator evaluator;
    const auto division = op("/", {integer(1), integer(0)});
    const auto outer = op("+", {integer(5), division});
    const Result result = evaluator.evaluate(outer);
    ASSERT_EQ(result.diagnostics.size(), 1u);
    EXPECT_EQ(result.diagnostics.front().element, division);
    EXPECT_TRUE(result.value.isNull());
}

TEST(EvaluatorOperators, TheValueIsNullWheneverAnErrorWasReported) {
    const Evaluator evaluator;
    const Result result = evaluator.evaluate(op(",", {integer(1), op("/", {integer(1), integer(0)})}));
    EXPECT_FALSE(result.ok());
    EXPECT_TRUE(result.value.isNull());
}

TEST(EvaluatorOperators, ShortCircuitDoesNotEvaluateTheOtherOperandOrReportIt) {
    const Evaluator evaluator;
    const ExpressionPtr unsupported = std::make_shared<KerML::Entities::IndexExpression>();
    expectValue(evaluator.evaluate(op("and", {boolean(false), unsupported})), B(false));
    expectValue(evaluator.evaluate(op("or", {boolean(true), unsupported})), B(true));
    expectValue(evaluator.evaluate(op("if", {boolean(false), unsupported, integer(2)})), I(2));
    expectValue(evaluator.evaluate(op("??", {integer(5), unsupported})), I(5));
    // and the other way round it is evaluated
    expectOneError(evaluator.evaluate(op("and", {boolean(true), unsupported})), "not supported yet: IndexExpression", unsupported);
}

TEST(EvaluatorOperators, TheRangeIsLimitedByTheOption) {
    EvaluationOptions options;
    options.maxSequenceLength = 5;
    const Evaluator limited(FunctionRegistry::withStandardFunctions(), options);
    expectValue(limited.evaluate(op("..", {integer(1), integer(5)})), Seq({1, 2, 3, 4, 5}));
    EXPECT_FALSE(limited.evaluate(op("..", {integer(1), integer(6)})).ok());
    EXPECT_EQ(limited.options().maxSequenceLength, 5u);
}

// Not supported yet ----------------------------------------------------------------------------------------------------------

TEST(EvaluatorUnsupported, EveryUnsupportedMetaclassIsAnErrorAndNull) {
    const Evaluator evaluator;
    const std::vector<std::pair<ExpressionPtr, std::string>> cases = {
        {std::make_shared<KerML::Entities::SelectExpression>(), "SelectExpression"},
        {std::make_shared<KerML::Entities::CollectExpression>(), "CollectExpression"},
        {std::make_shared<KerML::Entities::IndexExpression>(), "IndexExpression"},
        {std::make_shared<KerML::Entities::MetadataAccessExpression>(), "MetadataAccessExpression"},
        {std::make_shared<KerML::Entities::ConstructorExpression>(), "ConstructorExpression"},
        {std::make_shared<Expression>(), "Expression"},
    };
    for (const auto& [expression, metaclass] : cases) {
        SCOPED_TRACE(metaclass);
        expectOneError(evaluator.evaluate(expression), "not supported yet: " + metaclass, expression);
    }
}

TEST(EvaluatorUnsupported, TheSubclassesOfTheOperatorExpressionAreNotEvaluatedAsOperators) {
    // a SelectExpression has the operator name `select` of the library, which has no implementation: the message must still be the
    // "not supported yet" one
    const Evaluator evaluator;
    const auto select = std::make_shared<KerML::Entities::SelectExpression>();
    select->setOperatorName("select");
    select->setArgument({integer(1)});
    expectOneError(evaluator.evaluate(select), "not supported yet: SelectExpression", select);
}

TEST(EvaluatorUnsupported, AnUnsupportedOperandMakesTheOuterResultNull) {
    const Evaluator evaluator;
    const ExpressionPtr reference = std::make_shared<KerML::Entities::IndexExpression>();
    const Result result = evaluator.evaluate(op("+", {integer(1), reference}));
    expectOneError(result, "not supported yet: IndexExpression", reference);
}

// Invocations ----------------------------------------------------------------------------------------------------------------

TEST(EvaluatorInvocations, ANativeFunctionIsCalledWithThePositionalArguments) {
    const Evaluator evaluator;
    const auto minus = libraryFunction("DataFunctions", "-");
    expectValue(evaluator.evaluate(invoke(minus, {integer(10), integer(4)})), I(6));
    expectValue(evaluator.evaluate(invoke(minus, {integer(10)})), I(-10));
}

TEST(EvaluatorInvocations, TheArrowFormPassesTheLeftOperandAsTheFirstArgument) {
    const Evaluator evaluator;
    const auto minus = libraryFunction("DataFunctions", "-");
    // 10->DataFunctions::'-'(4) is the same as DataFunctions::'-'(10, 4)
    expectValue(evaluator.evaluate(op("->", {integer(10), integer(4)}, minus)), I(6));
    expectValue(evaluator.evaluate(op("->", {integer(10)}, minus)), I(-10));
}

TEST(EvaluatorInvocations, AFunctionWithoutAnImplementationIsAnError) {
    const Evaluator evaluator;
    const auto sum = libraryFunction("NumericalFunctions", "sum");
    const auto call = invoke(sum, {integer(1)});
    expectOneError(evaluator.evaluate(call), "no native implementation for NumericalFunctions::sum", call);
    const auto arrow = op("->", {integer(1)}, sum);
    expectOneError(evaluator.evaluate(arrow), "no native implementation for NumericalFunctions::sum", arrow);
}

TEST(EvaluatorInvocations, AnInvocationWithoutAFunctionIsAnError) {
    const Evaluator evaluator;
    const auto call = invoke(nullptr, {integer(1)});
    expectOneError(evaluator.evaluate(call), "not bound to a function", call);
}

namespace {
    /// An argument as the listeners build it for a plain invocation: the value is owned by a parameter (exactly a Feature); a named
    /// argument's parameter redefines the named parameter. (@p throughFeatureValue: the owner is the parameter's feature value.)
    /// The caller disposes the links (disposeLinks of the parameter) when it is done.
    ExpressionPtr argumentOf(const ExpressionPtr& value, bool named, bool throughFeatureValue, std::shared_ptr<Feature>& parameter) {
        parameter = std::make_shared<Feature>();
        if (named) parameter->appendOwnedRedefinition(std::make_shared<KerML::Entities::Redefinition>(std::make_shared<Feature>(), parameter));
        if (throughFeatureValue) {
            const auto featureValue = std::make_shared<KerML::Entities::FeatureValue>();
            featureValue->setOwner(parameter);
            value->setOwner(featureValue);
            parameter->appendOwnedElement(featureValue);
        } else {
            value->setOwner(parameter);
        }
        return value;
    }

    void release(const ExpressionPtr& value, const std::shared_ptr<Feature>& parameter) {
        value->setOwner(nullptr);
        for (const auto& owned : parameter->ownedElements()) owned->setOwner(nullptr);
        KerML::Entities::disposeLinks(*parameter);
    }
}

TEST(EvaluatorInvocations, NamedArgumentsWithoutAMatchingParameterAreRefused) {
    const Evaluator evaluator;
    const auto minus = libraryFunction("DataFunctions", "-");
    for (const bool throughFeatureValue : {false, true}) {
        // `-(y = 4, x = 10)`
        std::shared_ptr<Feature> parameter;
        const ExpressionPtr value = argumentOf(integer(4), true, throughFeatureValue, parameter);
        const auto call = invoke(minus, {value, integer(10)});
        expectOneError(evaluator.evaluate(call), "named arguments not supported yet", call);
        release(value, parameter);
    }
}

TEST(EvaluatorInvocations, NamedArgumentsOfTheArrowFormAreRefused) {
    const Evaluator evaluator;
    const auto minus = libraryFunction("DataFunctions", "-");
    const auto named = std::make_shared<Expression>();   // (the listener wraps `y = 4` in a plain expression that carries the name)
    named->setDeclaredName("y");
    const auto arrow = op("->", {integer(10), named}, minus);
    expectOneError(evaluator.evaluate(arrow), "named arguments not supported yet", arrow);
}

TEST(EvaluatorInvocations, PositionalArgumentsOwnedByParametersAreNotNamed) {
    const Evaluator evaluator;
    const auto minus = libraryFunction("DataFunctions", "-");
    for (const bool throughFeatureValue : {false, true}) {
        std::shared_ptr<Feature> parameter;
        const ExpressionPtr value = argumentOf(integer(4), false, throughFeatureValue, parameter);
        expectValue(evaluator.evaluate(invoke(minus, {integer(10), value})), I(6));
        release(value, parameter);
    }
}

TEST(EvaluatorInvocations, AUserRegisteredFunctionIsCalledThroughAnInvocation) {
    FunctionRegistry registry = FunctionRegistry::withStandardFunctions();
    registry.registerStrictFunction("MyFunctions::twice", [](EvaluationContext&, std::vector<Value> arguments) {
        return Value::integer(2 * arguments.at(0).asInteger().value());
    });
    const Evaluator evaluator(registry);
    const auto twice = libraryFunction("MyFunctions", "twice");
    expectValue(evaluator.evaluate(invoke(twice, {op("+", {integer(10), integer(11)})})), I(42));
    expectValue(evaluator.evaluate(op("->", {integer(4)}, twice)), I(8));
}

// Features ---------------------------------------------------------------------------------------------------------------------

TEST(EvaluatorFeatures, TheValueOfTheOwnFeatureValueIsEvaluated) {
    const Evaluator evaluator;
    const auto feature = std::make_shared<Feature>();
    const auto value = std::make_shared<KerML::Entities::FeatureValue>();
    value->setFeatureWithValue(feature);
    value->setValue(op("*", {integer(6), integer(7)}));
    value->setOwner(feature);
    feature->appendOwnedElement(value);
    expectValue(evaluator.evaluateFeatureValue(feature), I(42));
    KerML::Entities::disposeLinks(*feature);
}

TEST(EvaluatorFeatures, AFeatureWithoutAValueIsNullWithoutADiagnostic) {
    const Evaluator evaluator;
    const auto feature = std::make_shared<Feature>();
    const Result result = evaluator.evaluateFeatureValue(feature);
    EXPECT_TRUE(result.value.isNull());
    EXPECT_TRUE(result.diagnostics.empty());
    EXPECT_TRUE(result.ok());
}

TEST(EvaluatorFeatures, AnErrorInTheValueIsReported) {
    const Evaluator evaluator;
    const auto feature = std::make_shared<Feature>();
    const auto value = std::make_shared<KerML::Entities::FeatureValue>();
    const auto division = op("/", {integer(1), integer(0)});
    value->setValue(division);
    feature->appendOwnedElement(value);
    const Result result = evaluator.evaluateFeatureValue(feature);
    expectOneError(result, "division", division);
    KerML::Entities::disposeLinks(*feature);
}

// Depth ------------------------------------------------------------------------------------------------------------------------

TEST(EvaluatorDepth, EveryNestedExpressionCostsOneLevel) {
    EvaluationOptions options;
    options.maxDepth = 100;
    const Evaluator evaluator(FunctionRegistry::withStandardFunctions(), options);
    // 99 operators and the literal are 100 levels: the limit
    expectValue(evaluator.evaluate(minusChain(99)), I(-1));
    const Result result = evaluator.evaluate(minusChain(100));
    EXPECT_FALSE(result.ok());
    EXPECT_TRUE(result.value.isNull());
    ASSERT_EQ(result.diagnostics.size(), 1u);
    EXPECT_NE(result.diagnostics.front().message.find("maximum evaluation depth of 100"), std::string::npos);
}

TEST(EvaluatorDepth, AVeryDeepChainIsAnErrorAndNoCrash) {
    EvaluationOptions options;
    options.maxDepth = 200;
    const Evaluator evaluator(FunctionRegistry::withStandardFunctions(), options);
    const Result result = evaluator.evaluate(minusChain(5000));
    EXPECT_TRUE(hasError(result.diagnostics, "maximum evaluation depth"));
    EXPECT_TRUE(result.value.isNull());
}

TEST(EvaluatorDepth, TheLimitIsConfigurable) {
    EvaluationOptions options;
    options.maxDepth = 3;
    const Evaluator evaluator(FunctionRegistry::withStandardFunctions(), options);
    expectValue(evaluator.evaluate(minusChain(2)), I(1));
    EXPECT_FALSE(evaluator.evaluate(minusChain(3)).ok());
    EXPECT_EQ(evaluator.options().maxDepth, 3u);
    EXPECT_EQ(EvaluationOptions().maxDepth, EvaluationContext::DefaultMaxDepth);
}

TEST(EvaluatorDepth, TheDefaultLimitIs256Levels) {
    EXPECT_EQ(EvaluationContext::DefaultMaxDepth, 256u);
    const Evaluator evaluator;
    expectValue(evaluator.evaluate(minusChain(255)), I(-1));
    const Result result = evaluator.evaluate(minusChain(5000));
    ASSERT_EQ(result.diagnostics.size(), 1u);
    EXPECT_NE(result.diagnostics.front().message.find("maximum evaluation depth of 256"), std::string::npos);
    EXPECT_TRUE(result.value.isNull());
}

TEST(EvaluatorDepth, TheDepthLimitIsReportedOncePerEvaluation) {
    // 2000 terms `1 + 1 + ... + 1`, nested to the left: the innermost part exceeds the limit, and every operand on the way up is
    // evaluated without a second report
    ExpressionPtr chain = integer(1);
    for (int term = 1; term < 2000; ++term) chain = op("+", {chain, integer(1)});
    const Result result = Evaluator().evaluate(chain);
    EXPECT_EQ(result.diagnostics.size(), 1u);
    EXPECT_TRUE(hasError(result.diagnostics, "maximum evaluation depth"));
    EXPECT_TRUE(result.value.isNull());
}

#if defined(__unix__) || defined(__APPLE__)
namespace {
    struct ThreadJob {
        Result result;
        Result nearLimit;
    };

    void* runOnSmallStack(void* argument) {
        auto* job = static_cast<ThreadJob*>(argument);
        const Evaluator evaluator;
        // the deepest chains that the default limit allows, with the operators that have the biggest frames
        job->result = evaluator.evaluate(minusChain(EvaluationContext::DefaultMaxDepth - 1));
        ExpressionPtr current = integer(1);
        for (std::size_t level = 1; level + 1 < EvaluationContext::DefaultMaxDepth; ++level) current = op(level % 2 ? "and" : "or", {boolean(level % 2 != 0), current});
        job->nearLimit = evaluator.evaluate(current);
        return nullptr;
    }
}

// The default depth must not overflow a 1 MB stack (the Windows main thread, a typical small worker) in any build type.
TEST(EvaluatorDepth, TheDefaultDepthFitsAOneMegabyteThreadStack) {
    pthread_attr_t attributes;
    ASSERT_EQ(pthread_attr_init(&attributes), 0);
    ASSERT_EQ(pthread_attr_setstacksize(&attributes, 1024 * 1024), 0);
    ThreadJob job;
    pthread_t thread;
    ASSERT_EQ(pthread_create(&thread, &attributes, runOnSmallStack, &job), 0);
    ASSERT_EQ(pthread_join(thread, nullptr), 0);
    pthread_attr_destroy(&attributes);
    expectValue(job.result, I(-1));
    // (`and` / `or` of a Boolean with an Integer is a type error at the bottom, which must be reported without a crash)
    EXPECT_FALSE(job.nearLimit.ok());
}
#endif

// Stack use per level of depth: reported, and bounded loosely so that a regression of the frame size (a big local array in a frame on
// the recursion path) is noticed. Measured: about 470 to 580 bytes per level optimized (GCC and clang), 1.4 to 1.8 KB unoptimized.
namespace {
    thread_local std::uintptr_t DeepestAddress = 0;
    thread_local std::uintptr_t ShallowAddress = 0;
}

TEST(EvaluatorDepth, StackUsePerLevelOfDepth) {
    FunctionRegistry registry = FunctionRegistry::withStandardFunctions();
    registry.registerFunction("MyFunctions::probe", [](EvaluationContext&, const std::vector<ExpressionPtr>&) {
        int local = 0;
        DeepestAddress = reinterpret_cast<std::uintptr_t>(&local);
        return Value::integer(1);
    });
    const Evaluator evaluator(registry);
    const auto probe = libraryFunction("MyFunctions", "probe");
    const std::size_t levels = 100;
    // `-(-(...-(probe())))`
    ExpressionPtr current = invoke(probe, {});
    for (std::size_t index = 0; index < levels; ++index) current = op("-", {current});
    int local = 0;
    ShallowAddress = reinterpret_cast<std::uintptr_t>(&local);
    EXPECT_FALSE(evaluator.evaluate(current).value.isNull());
    const std::size_t used = ShallowAddress > DeepestAddress ? ShallowAddress - DeepestAddress : DeepestAddress - ShallowAddress;
    const std::size_t perLevel = used / (levels + 1);
    std::cout << "[  INFO  ] stack use per level of depth: about " << perLevel << " bytes (" << used << " bytes for " << levels + 1 << " levels)"
              << std::endl;
    // (the frames of an instrumented build are much larger)
#if defined(__SANITIZE_ADDRESS__)
#define SYSMLV2_TEST_SANITIZED 1
#elif defined(__has_feature)
#if __has_feature(address_sanitizer)
#define SYSMLV2_TEST_SANITIZED 1
#endif
#endif
#ifndef SYSMLV2_TEST_SANITIZED
    EXPECT_LT(perLevel, std::size_t(4096));
#endif
}

// The cache --------------------------------------------------------------------------------------------------------------------

TEST(EvaluatorCache, TheSameFunctionIsEvaluatedTwice) {
    const Evaluator evaluator;
    const auto plus = libraryFunction("DataFunctions", "+");
    expectValue(evaluator.evaluate(op("+", {integer(1), integer(2)}, plus)), I(3));
    expectValue(evaluator.evaluate(op("+", {integer(3), integer(4)}, plus)), I(7));
    // and a function without an implementation twice (the miss is cached as well)
    const auto missing = libraryFunction("Nowhere", "missing");
    expectOneError(evaluator.evaluate(invoke(missing, {})), "no native implementation");
    expectOneError(evaluator.evaluate(invoke(missing, {})), "no native implementation");
}

TEST(EvaluatorCache, ReplacingTheRegistryUsesTheNewImplementation) {
    Evaluator evaluator;
    const auto plus = libraryFunction("DataFunctions", "+");
    const auto expression = op("+", {integer(1), integer(2)}, plus);
    expectValue(evaluator.evaluate(expression), I(3));

    FunctionRegistry replaced = evaluator.registry();
    replaced.registerFunction("DataFunctions::'+'", [](EvaluationContext&, const std::vector<ExpressionPtr>&) { return Value::integer(42); });
    evaluator.setRegistry(replaced);
    expectValue(evaluator.evaluate(expression), I(42));

    // and back to a registry without the function
    evaluator.setRegistry(FunctionRegistry());
    expectOneError(evaluator.evaluate(expression), "no native implementation for DataFunctions::'+'", expression);
    EXPECT_EQ(evaluator.registry().find("DataFunctions::'+'"), nullptr);
}

TEST(EvaluatorCache, AChangedHierarchyIsSeenByTheNextCall) {
    // (the lookup cache lives for one call: the generals of a function may be resolved in place between two calls)
    FunctionRegistry registry;
    registry.registerFunction("Base::f", [](EvaluationContext&, const std::vector<ExpressionPtr>&) { return Value::integer(1); });
    const Evaluator evaluator(registry);
    const auto root = makeRoot();
    const auto general = makeFunction("f", makePackage("Base", root));
    const auto specific = makeFunction("g", makePackage("Derived", root));
    const auto call = invoke(specific, {});
    EXPECT_FALSE(evaluator.evaluate(call).ok());
    specialize(specific, general);
    expectValue(evaluator.evaluate(call), I(1));
    disposeAll({general, specific});
}

TEST(EvaluatorCache, FunctionsThatAreFreedAndReallocatedNeverGetTheResultOfTheirPredecessor) {
    FunctionRegistry registry;
    registry.registerFunction("Lib::one", [](EvaluationContext&, const std::vector<ExpressionPtr>&) { return Value::integer(1); });
    registry.registerFunction("Lib::two", [](EvaluationContext&, const std::vector<ExpressionPtr>&) { return Value::integer(2); });
    const Evaluator evaluator(registry);
    // Functions that are allocated apart from their control block (so that their memory is really freed and reused) and ones from
    // make_shared, each evaluated by its own call (the cache of the registry lookup lives for one call only).
    for (int round = 0; round < 3000; ++round) {
        const bool second = round % 2 == 1;
        const std::string name = second ? "two" : "one";
        auto owner = makePackage("Lib", makeRoot());
        std::shared_ptr<Function> function;
        if (round % 3 == 0) {
            function = std::shared_ptr<Function>(new Function());
            function->setDeclaredName(name);
            function->setOwner(owner);
        } else {
            function = makeFunction(name, owner);
        }
        const Result result = evaluator.evaluate(invoke(function, {}));
        ASSERT_TRUE(result.ok()) << round;
        ASSERT_EQ(result.value, I(second ? 2 : 1)) << round << " " << name;
    }
}

// Concurrency and exceptions -----------------------------------------------------------------------------------------------------

TEST(EvaluatorConcurrency, SeveralThreadsEvaluateOnTheSameEvaluator) {
    const Evaluator evaluator;
    const auto plus = libraryFunction("DataFunctions", "+");
    const auto times = libraryFunction("DataFunctions", "*");
    std::vector<ExpressionPtr> expressions;
    for (int index = 0; index < 8; ++index) expressions.push_back(op("*", {op("+", {integer(index), integer(1)}, plus), integer(2)}, times));
    std::atomic<int> failures{0};
    std::vector<std::thread> threads;
    for (int thread = 0; thread < 8; ++thread) {
        threads.emplace_back([&, thread] {
            for (int round = 0; round < 300; ++round) {
                const int index = (thread + round) % 8;
                const Result result = evaluator.evaluate(expressions[index]);
                if (!result.ok() || result.value != I((index + 1) * 2)) ++failures;
                // unbound operators and a function that is looked up (and missed) concurrently
                if (evaluator.evaluate(op("+", {integer(1), integer(2)})).value != I(3)) ++failures;
                if (evaluator.evaluate(invoke(libraryFunction("Nowhere", "missing"), {})).ok()) ++failures;
            }
        });
    }
    for (std::thread& thread : threads) thread.join();
    EXPECT_EQ(failures.load(), 0);
}

TEST(EvaluatorExceptions, AnExceptionInANativeFunctionBecomesAnError) {
    FunctionRegistry registry = FunctionRegistry::withStandardFunctions();
    registry.registerFunction("MyFunctions::boom", [](EvaluationContext&, const std::vector<ExpressionPtr>&) -> Value {
        throw std::runtime_error("boom happened");
    });
    registry.registerFunction("MyFunctions::weird", [](EvaluationContext&, const std::vector<ExpressionPtr>&) -> Value { throw 42; });
    registry.registerFunction("MyFunctions::memory", [](EvaluationContext&, const std::vector<ExpressionPtr>&) -> Value { throw std::bad_alloc(); });
    const Evaluator evaluator(registry);

    const auto boom = invoke(libraryFunction("MyFunctions", "boom"), {});
    const Result thrown = evaluator.evaluate(op("+", {integer(1), boom}));
    expectOneError(thrown, "boom happened", boom);

    const auto weird = invoke(libraryFunction("MyFunctions", "weird"), {});
    expectOneError(evaluator.evaluate(weird), "unknown exception", weird);

    const auto memory = invoke(libraryFunction("MyFunctions", "memory"), {});
    EXPECT_FALSE(evaluator.evaluate(memory).ok());
    EXPECT_TRUE(evaluator.evaluate(memory).value.isNull());

    // the evaluator is fine afterwards
    expectValue(evaluator.evaluate(op("+", {integer(1), integer(2)})), I(3));
}

TEST(EvaluatorLifecycle, AnEvaluatorCanBeMoved) {
    Evaluator first;
    Evaluator second(std::move(first));
    expectValue(second.evaluate(op("+", {integer(1), integer(2)})), I(3));
    Evaluator third;
    third = std::move(second);
    expectValue(third.evaluate(op("+", {integer(2), integer(2)})), I(4));
}

// The XMI shape ---------------------------------------------------------------------------------------------------------------
//
// The XMI import leaves argument(), function() and instantiatedType() empty: the arguments are the owned ParameterMemberships (input
// features with a FeatureValue), then a ReturnParameterMembership, and the invoked function is the member of a plain Membership.

namespace {
    /// Builds the XMI shape on an invocation; keeps the pieces and breaks their reference cycles when it ends.
    class XmiShape {
    public:
        /// @param function the member of the plain Membership (nullptr: none, as for the operators).
        XmiShape(const std::shared_ptr<InvocationExpression>& invocation, const std::shared_ptr<Function>& function, const std::vector<ExpressionPtr>& values,
                 const std::vector<std::string>& redefinedNames = {}) {
            std::vector<std::shared_ptr<KerML::Entities::Relationship>> relationships;
            for (std::size_t index = 0; index < values.size(); ++index) {
                const auto parameter = parameterWithValue(values[index], KerML::Entities::IN);
                if (index < redefinedNames.size()) {
                    const auto redefined = std::make_shared<Feature>();
                    redefined->setDeclaredName(redefinedNames[index]);
                    parameter->appendOwnedRedefinition(std::make_shared<KerML::Entities::Redefinition>(redefined, parameter));
                }
                auto membership = std::make_shared<KerML::Entities::ParameterMembership>();
                membership->setMemberElement(parameter);
                relationships.push_back(membership);
            }
            if (function) {
                auto membership = std::make_shared<KerML::Entities::Membership>();
                membership->setMemberElement(function);
                relationships.push_back(membership);
            }
            // the result: direction out, never an argument (it carries a value here to prove that it is skipped)
            auto result = parameterWithValue(integer(99), KerML::Entities::OUT);
            auto resultMembership = std::make_shared<KerML::Entities::ReturnParameterMembership>();
            resultMembership->setMemberElement(result);
            relationships.push_back(resultMembership);
            invocation->setOwnedRelationship(relationships);
        }
        ~XmiShape() {
            for (const auto& parameter : Parameters) {
                for (const auto& owned : parameter->ownedElements()) {
                    if (const auto featureValue = std::dynamic_pointer_cast<KerML::Entities::FeatureValue>(owned)) {
                        if (const auto value = featureValue->value()) value->setOwner(nullptr);
                    }
                    owned->setOwner(nullptr);
                }
                KerML::Entities::disposeLinks(*parameter);
            }
        }
        XmiShape(const XmiShape&) = delete;
        XmiShape& operator=(const XmiShape&) = delete;

    private:
        std::shared_ptr<Feature> parameterWithValue(const ExpressionPtr& value, KerML::Entities::FeatureDirectionKind direction) {
            auto parameter = std::make_shared<Feature>();
            parameter->setDirection(direction);
            auto featureValue = std::make_shared<KerML::Entities::FeatureValue>();
            featureValue->setOwner(parameter);
            featureValue->setValue(value);
            value->setOwner(featureValue);
            parameter->appendOwnedElement(featureValue);
            Parameters.push_back(parameter);
            return parameter;
        }
        std::vector<std::shared_ptr<Feature>> Parameters;
    };

    FunctionRegistry withCount() {
        FunctionRegistry registry = FunctionRegistry::withStandardFunctions();
        registry.registerFunction("Test::count", [](EvaluationContext&, const std::vector<ExpressionPtr>& arguments) {
            return Value::integer(static_cast<std::int64_t>(arguments.size()));
        });
        return registry;
    }
}

TEST(EvaluatorXmiShape, OperatorArgumentsComeFromTheParameters) {
    const Evaluator evaluator;
    const auto expression = op("+", {});
    const XmiShape shape(expression, nullptr, {integer(1), integer(2)});
    ASSERT_TRUE(expression->argument().empty());
    expectValue(evaluator.evaluate(expression), I(3));
}

TEST(EvaluatorXmiShape, TheInvokedFunctionIsTheMemberOfThePlainMembership) {
    const Evaluator evaluator;
    const auto call = invoke(nullptr, {});
    const XmiShape shape(call, libraryFunction("DataFunctions", "-"), {integer(10), integer(4)});
    expectValue(evaluator.evaluate(call), I(6));
    // an arrow: the left operand is the first parameter
    const auto arrow = op("->", {});
    const XmiShape arrowShape(arrow, libraryFunction("DataFunctions", "-"), {integer(10), integer(4)});
    expectValue(evaluator.evaluate(arrow), I(6));
}

TEST(EvaluatorXmiShape, TheResultParameterIsNotAnArgumentAndZeroArgumentCallsStayZeroArgument) {
    const Evaluator evaluator(withCount());
    const auto count = libraryFunction("Test", "count");
    const auto none = invoke(nullptr, {});
    const XmiShape noneShape(none, count, {});
    expectValue(evaluator.evaluate(none), I(0));
    const auto two = invoke(nullptr, {});
    const XmiShape twoShape(two, count, {integer(5), integer(6)});
    expectValue(evaluator.evaluate(two), I(2));
}

TEST(EvaluatorXmiShape, AnInvocationWithoutAFunctionIsAnErrorInTheXmiShape) {
    const Evaluator evaluator;
    const auto call = invoke(nullptr, {});
    const XmiShape shape(call, nullptr, {integer(1)});
    expectOneError(evaluator.evaluate(call), "not bound to a function", call);
}

namespace {
    /// `F(x, y)` for the named arguments: a function with two input parameters x and y.
    std::shared_ptr<Function> functionWithParameters(const std::string& name, const std::vector<std::string>& parameters, std::vector<std::shared_ptr<Feature>>& keep) {
        const auto function = libraryFunction("DataFunctions", name);
        std::vector<std::shared_ptr<KerML::Entities::Relationship>> relationships;
        for (const std::string& parameterName : parameters) {
            auto parameter = std::make_shared<Feature>();
            parameter->setDeclaredName(parameterName);
            parameter->setDirection(KerML::Entities::IN);
            auto membership = std::make_shared<KerML::Entities::ParameterMembership>();
            membership->setMemberElement(parameter);
            relationships.push_back(membership);
            keep.push_back(parameter);
        }
        function->setOwnedRelationship(relationships);
        return function;
    }
}

TEST(EvaluatorNamedArguments, TheArgumentsAreOrderedByTheParametersTheyRedefine) {
    const Evaluator evaluator;
    std::vector<std::shared_ptr<Feature>> keep;
    const auto minus = functionWithParameters("-", {"x", "y"}, keep);
    const auto call = invoke(nullptr, {});
    // `-(y = 10, x = 4)` is 4 - 10
    const XmiShape shape(call, minus, {integer(10), integer(4)}, {"y", "x"});
    expectValue(evaluator.evaluate(call), I(-6));
    // in the order of the parameters it is the same
    const auto sameOrder = invoke(nullptr, {});
    const XmiShape sameShape(sameOrder, minus, {integer(4), integer(10)}, {"x", "y"});
    expectValue(evaluator.evaluate(sameOrder), I(-6));
    // a function without parameters of its own takes them from its general
    const auto root = makeRoot();
    const auto specific = makeFunction("-", makePackage("IntegerFunctions", root));
    specialize(specific, minus);
    const auto inherited = invoke(nullptr, {});
    const XmiShape inheritedShape(inherited, specific, {integer(10), integer(4)}, {"y", "x"});
    expectValue(evaluator.evaluate(inherited), I(-6));
    disposeAll({specific});
}

TEST(EvaluatorNamedArguments, AnAmbiguousBindingIsRefused) {
    const Evaluator evaluator;
    std::vector<std::shared_ptr<Feature>> keep;
    const auto minus = functionWithParameters("-", {"x", "y"}, keep);
    const std::vector<std::vector<std::string>> refused = {{"x", "x"}, {"x", "z"}, {"y"}, {"y", ""}};
    for (const auto& names : refused) {
        const auto call = invoke(nullptr, {});
        std::vector<ExpressionPtr> values;
        for (std::size_t index = 0; index < names.size(); ++index) values.push_back(integer(static_cast<std::int64_t>(index) + 1));
        const XmiShape shape(call, minus, values, names);
        SCOPED_TRACE(names.empty() ? "" : names.front());
        expectOneError(evaluator.evaluate(call), "named arguments not supported yet", call);
    }
}

// Results, failures, subclasses ----------------------------------------------------------------------------------------------

TEST(EvaluatorResults, AWarningKeepsTheValue) {
    FunctionRegistry registry = FunctionRegistry::withStandardFunctions();
    registry.registerFunction("Test::careful", [](EvaluationContext& context, const std::vector<ExpressionPtr>&) {
        context.report(Severity::Warning, "be careful");
        return Value::integer(5);
    });
    const Evaluator evaluator(registry);
    const Result result = evaluator.evaluate(op("+", {invoke(libraryFunction("Test", "careful"), {}), integer(1)}));
    EXPECT_EQ(result.value, I(6));
    EXPECT_TRUE(result.ok());
    ASSERT_EQ(result.diagnostics.size(), 1u);
    EXPECT_EQ(result.diagnostics.front().severity, Severity::Warning);
}

TEST(EvaluatorResults, AFailureWithoutADiagnosticIsNotOk) {
    FunctionRegistry registry = FunctionRegistry::withStandardFunctions();
    registry.registerFunction("Test::fail", [](EvaluationContext& context, const std::vector<ExpressionPtr>&) {
        context.markFailed();   // (what report() does when it cannot store a diagnostic)
        return Value::integer(5);
    });
    const Evaluator evaluator(registry);
    const Result result = evaluator.evaluate(invoke(libraryFunction("Test", "fail"), {}));
    EXPECT_TRUE(result.diagnostics.empty());
    EXPECT_TRUE(result.failed);
    EXPECT_FALSE(result.ok());
    EXPECT_TRUE(result.value.isNull());
}

TEST(EvaluatorResults, AMovedFromEvaluatorReportsAnError) {
    Evaluator first;
    const Evaluator second(std::move(first));
    const Result expression = first.evaluate(integer(1));
    EXPECT_FALSE(expression.ok());
    EXPECT_TRUE(expression.value.isNull());
    EXPECT_TRUE(hasError(expression.diagnostics, "moved-from"));
    EXPECT_FALSE(first.evaluateFeatureValue(std::make_shared<Feature>()).ok());
    EXPECT_EQ(first.registry().find("DataFunctions::'+'"), nullptr);
    EXPECT_EQ(first.options().maxDepth, EvaluationContext::DefaultMaxDepth);
    first.setRegistry(FunctionRegistry::withStandardFunctions());   // (usable again)
    expectValue(first.evaluate(op("+", {integer(1), integer(2)})), I(3));
}

TEST(EvaluatorUnsupported, AnInvocationOfAnotherMetaclassIsNotSupportedYet) {
    // (a trigger invocation of sysml is such a subclass; the evaluation does not depend on sysml)
    struct OtherInvocation : public virtual InvocationExpression {};
    const Evaluator evaluator;
    const auto other = std::make_shared<OtherInvocation>();
    other->setFunction(libraryFunction("DataFunctions", "+"));
    other->setArgument({integer(1), integer(2)});
    const Result result = evaluator.evaluate(other);
    expectOneError(result, "not supported yet", other);
    EXPECT_EQ(result.diagnostics.front().message.find("not bound"), std::string::npos);
}

TEST(EvaluatorFeatures, DefaultAndInitialValuesAreTreatedLikeBoundValues) {
    const Evaluator evaluator;
    for (const bool initial : {false, true}) {
        const auto feature = std::make_shared<Feature>();
        const auto value = std::make_shared<KerML::Entities::FeatureValue>();
        value->setValue(op("+", {integer(40), integer(2)}));
        value->setIsDefault(!initial);
        value->setIsInitial(initial);
        feature->appendOwnedElement(value);
        expectValue(evaluator.evaluateFeatureValue(feature), I(42));
        KerML::Entities::disposeLinks(*feature);
    }
}

TEST(EvaluatorFeatures, AFeatureThatIsAnExpressionIsEvaluatedAsOne) {
    // e.g. a SysML constraint or calculation usage: it has no FeatureValue, and silent null would hide that it is not evaluated
    const Evaluator evaluator;
    const auto expression = std::make_shared<Expression>();
    const std::shared_ptr<Feature> asFeature = expression;
    expectOneError(evaluator.evaluateFeatureValue(asFeature), "not supported yet: Expression", expression);
    expectOneError(evaluator.evaluate(expression), "not supported yet: Expression", expression);
    // an expression with a FeatureValue of its own: the value wins
    const auto literal = literalInteger(7);
    const auto value = std::make_shared<KerML::Entities::FeatureValue>();
    value->setValue(literal);
    expression->appendOwnedElement(value);
    expectValue(evaluator.evaluateFeatureValue(asFeature), I(7));
    KerML::Entities::disposeLinks(*expression);
}

// The shape that XmiWriter writes (and the XMI import reads back): the operands are owned directly through plain FeatureMemberships.
namespace {
    /// An operator expression (`,` or any) whose operands are owned through plain FeatureMemberships; argument() stays empty.
    std::shared_ptr<OperatorExpression> writerShaped(const std::string& name, const std::vector<ExpressionPtr>& operands) {
        auto expression = std::make_shared<OperatorExpression>();
        expression->setOperatorName(name);
        std::vector<std::shared_ptr<KerML::Entities::Relationship>> relationships;
        for (const auto& operand : operands) {
            auto membership = std::make_shared<KerML::Entities::FeatureMembership>();
            membership->setMemberElement(operand);
            relationships.push_back(membership);
        }
        expression->setOwnedRelationship(relationships);
        return expression;
    }
}

TEST(EvaluatorXmiShape, OperandsOwnedThroughFeatureMembershipsAreTheArguments) {
    const Evaluator evaluator;
    expectValue(evaluator.evaluate(writerShaped("-", {integer(10), integer(4)})), I(6));
    expectValue(evaluator.evaluate(writerShaped("**", {integer(2), writerShaped("**", {integer(3), integer(2)})})), I(512));
    expectValue(evaluator.evaluate(writerShaped("if", {boolean(false), integer(1), integer(2)})), I(2));
}

TEST(EvaluatorXmiShape, ALongSequenceOfTheWriterShapeIsFlattened) {
    // `,` nested to the right, 400 elements: far beyond the depth limit, so the flattening must be iterative in this shape as well
    ExpressionPtr chain = integer(400);
    for (std::int64_t element = 399; element >= 1; --element) chain = writerShaped(",", {integer(element), chain});
    const Result result = Evaluator().evaluate(chain);
    EXPECT_TRUE(result.ok());
    ASSERT_EQ(result.value.size(), 400u);
    EXPECT_EQ(result.value.items().front(), Item(std::int64_t(1)));
    EXPECT_EQ(result.value.items().back(), Item(std::int64_t(400)));
}

TEST(EvaluatorXmiShape, AParameterWithoutAValueIsAnErrorAndNeverSkipped) {
    const Evaluator evaluator;
    const auto call = op("-", {});
    const XmiShape shape(call, nullptr, {integer(10), integer(4)});
    // a second input parameter without a FeatureValue
    auto parameter = std::make_shared<Feature>();
    parameter->setDirection(KerML::Entities::IN);
    auto membership = std::make_shared<KerML::Entities::ParameterMembership>();
    membership->setMemberElement(parameter);
    auto relationships = call->ownedRelationship();
    relationships.insert(relationships.begin() + 1, membership);
    call->setOwnedRelationship(relationships);
    expectOneError(evaluator.evaluate(call), "has no value", call);
}

TEST(EvaluatorSequences, TheLengthLimitAlsoAppliesToConcatenation) {
    EvaluationOptions options;
    options.maxSequenceLength = 10;
    const Evaluator evaluator(FunctionRegistry::withStandardFunctions(), options);
    const auto range = [] { return op("..", {integer(1), integer(10)}); };
    // 10 items fit (a null contributes nothing), 20 and 30 do not
    const Result fits = evaluator.evaluate(op(",", {range(), std::make_shared<KerML::Entities::NullExpression>()}));
    EXPECT_TRUE(fits.ok());
    EXPECT_EQ(fits.value.size(), 10u);
    expectOneError(evaluator.evaluate(op(",", {range(), range()})), "longer than the limit of 10");
    expectOneError(evaluator.evaluate(op(",", {range(), op(",", {range(), range()})})), "longer than the limit of 10");
}

TEST(EvaluatorResults, ANonFiniteRealLiteralIsAnError) {
    const Evaluator evaluator;
    for (const double value : {std::numeric_limits<double>::infinity(), -std::numeric_limits<double>::infinity(), std::numeric_limits<double>::quiet_NaN()}) {
        const ExpressionPtr literal = real(value);
        expectOneError(evaluator.evaluate(literal), "not a finite number", literal);
    }
}

TEST(EvaluatorLifecycle, ANativeFunctionMayReplaceTheRegistryWhileItRuns) {
    Evaluator evaluator;
    FunctionRegistry registry = FunctionRegistry::withStandardFunctions();
    registry.registerFunction("Test::replace", [&evaluator](EvaluationContext&, const std::vector<ExpressionPtr>&) {
        evaluator.setRegistry(FunctionRegistry());   // (destroys the registry that holds this very function)
        return Value::integer(7);
    });
    evaluator.setRegistry(registry);
    expectValue(evaluator.evaluate(invoke(libraryFunction("Test", "replace"), {})), I(7));
    EXPECT_EQ(evaluator.registry().find("Test::replace"), nullptr);
    Evaluator other;
    FunctionRegistry assigning = FunctionRegistry::withStandardFunctions();
    assigning.registerFunction("Test::reassign", [&other](EvaluationContext&, const std::vector<ExpressionPtr>&) {
        other = Evaluator(FunctionRegistry());
        return Value::integer(8);
    });
    other.setRegistry(assigning);
    expectValue(other.evaluate(invoke(libraryFunction("Test", "reassign"), {})), I(8));
}

// Feature references --------------------------------------------------------------------------------------------------------

namespace {
    /// A feature below a package with a value expression (the feature owns its feature value).
    std::shared_ptr<Feature> featureWithValue(const std::string& name, const ExpressionPtr& value, const std::shared_ptr<KerML::Entities::Element>& owner,
                                              bool isDefault = false) {
        auto feature = std::make_shared<Feature>();
        feature->setDeclaredName(name);
        feature->setOwner(owner);
        if (value) {
            auto featureValue = std::make_shared<KerML::Entities::FeatureValue>();
            featureValue->setValue(value);
            featureValue->setIsDefault(isDefault);
            feature->appendOwnedElement(featureValue);
        }
        return feature;
    }

    std::shared_ptr<KerML::Entities::FeatureReferenceExpression> referenceTo(const std::shared_ptr<Feature>& referent) {
        auto reference = std::make_shared<KerML::Entities::FeatureReferenceExpression>();
        reference->setReferent(referent);
        return reference;
    }

    void dispose(const std::vector<std::shared_ptr<Feature>>& features) {
        for (const auto& feature : features) KerML::Entities::disposeLinks(*feature);
    }
}

TEST(EvaluatorReferences, TheValueOfTheReferentIsTheValueOfItsFeatureValue) {
    const Evaluator evaluator;
    const auto package = makePackage("P", makeRoot());
    const auto x = featureWithValue("x", integer(40), package);
    const auto none = featureWithValue("none", nullptr, package);
    expectValue(evaluator.evaluate(op("+", {referenceTo(x), integer(2)})), I(42));
    expectValue(evaluator.evaluate(referenceTo(none)), N());   // (a feature without a value: the empty sequence)
    expectValue(evaluator.evaluateFeatureValue(featureWithValue("y", referenceTo(x), package)), I(40));
    dispose({x, none});
}

TEST(EvaluatorReferences, ADefaultValueIsUsedIfNothingBindsAValue) {
    const Evaluator evaluator;
    const auto package = makePackage("P", makeRoot());
    const auto d = featureWithValue("d", integer(3), package, true);
    expectValue(evaluator.evaluate(referenceTo(d)), I(3));
    dispose({d});
}

TEST(EvaluatorReferences, UnresolvedAndMissingReferentsAreErrors) {
    const Evaluator evaluator;
    // the parser keeps a placeholder (no owner) for a name that it could not resolve
    auto placeholder = std::make_shared<Feature>();
    placeholder->setDeclaredName("nothere");
    const auto unresolved = referenceTo(placeholder);
    expectOneError(evaluator.evaluate(unresolved), "unresolved reference 'nothere'", unresolved);
    const auto missing = std::make_shared<KerML::Entities::FeatureReferenceExpression>();
    expectOneError(evaluator.evaluate(missing), "no referent", missing);
}

TEST(EvaluatorReferences, ThePilotShapeRecordsTheReferentInAPlainMembership) {
    const Evaluator evaluator;
    const auto package = makePackage("P", makeRoot());
    const auto x = featureWithValue("x", integer(7), package);
    const auto reference = std::make_shared<KerML::Entities::FeatureReferenceExpression>();
    auto membership = std::make_shared<KerML::Entities::Membership>();
    membership->setMemberElement(x);
    reference->setOwnedRelationship({membership});
    ASSERT_EQ(reference->referent(), nullptr);
    expectValue(evaluator.evaluate(reference), I(7));
    // a wrapper that owns an expression (a lazily evaluated operand) evaluates that expression, a plain Expression (a body) is not supported yet
    for (const bool body : {false, true}) {
        const auto wrapper = std::make_shared<KerML::Entities::FeatureReferenceExpression>();
        auto owned = std::make_shared<KerML::Entities::FeatureMembership>();
        const ExpressionPtr inner = body ? std::make_shared<Expression>() : integer(9);
        owned->setMemberElement(inner);
        wrapper->setOwnedRelationship({owned});
        if (body) expectOneError(evaluator.evaluate(wrapper), "not supported yet: Expression");
        else expectValue(evaluator.evaluate(wrapper), I(9));
    }
    dispose({x});
}

TEST(EvaluatorReferences, CyclesAreOneError) {
    const Evaluator evaluator;
    const auto package = makePackage("P", makeRoot());
    // a = b; b = a;
    auto a = featureWithValue("a", nullptr, package);
    auto b = featureWithValue("b", referenceTo(a), package);
    auto featureValue = std::make_shared<KerML::Entities::FeatureValue>();
    featureValue->setValue(referenceTo(b));
    a->appendOwnedElement(featureValue);
    for (const auto& start : {a, b}) {
        const Result result = evaluator.evaluateFeatureValue(start);
        ASSERT_EQ(result.diagnostics.size(), 1u);
        EXPECT_NE(result.diagnostics.front().message.find("cyclic definition"), std::string::npos) << result.diagnostics.front().message;
        EXPECT_NE(result.diagnostics.front().message.find("P::a"), std::string::npos);
        EXPECT_NE(result.diagnostics.front().message.find("P::b"), std::string::npos);
        EXPECT_TRUE(result.value.isNull());
    }
    dispose({a, b});
}

TEST(EvaluatorReferences, ABoundFeatureHasTheBoundValueAndSelfIsTheTarget) {
    const auto package = makePackage("P", makeRoot());
    const auto bound = featureWithValue("bound", integer(1), package);
    FunctionRegistry registry = FunctionRegistry::withStandardFunctions();
    registry.registerFunction("Test::withBinding", [bound](EvaluationContext& context, const std::vector<ExpressionPtr>& arguments) {
        const auto scope = context.bind(bound, Value::integer(5));
        return context.evaluate(arguments.at(0));
    });
    const Evaluator evaluator(registry);
    const auto call = invoke(libraryFunction("Test", "withBinding"), {referenceTo(bound)});
    expectValue(evaluator.evaluate(call), I(5));
    expectValue(evaluator.evaluate(referenceTo(bound)), I(1));   // (the binding ended with the scope)
    dispose({bound});
}

TEST(EvaluationContextScopes, TargetsAndBindingsNestAndEnd) {
    EvaluationContext context;
    EXPECT_EQ(context.target(), nullptr);
    const auto first = std::make_shared<Feature>();
    const auto second = std::make_shared<Feature>();
    {
        const auto outer = context.enterTarget(first);
        EXPECT_EQ(context.target(), first);
        {
            const auto inner = context.enterTarget(second);
            EXPECT_EQ(context.target(), second);
            const auto nothing = context.enterTarget(nullptr);
            EXPECT_EQ(context.target(), nullptr);
        }
        EXPECT_EQ(context.target(), first);
        EXPECT_EQ(context.binding(first.get()), nullptr);
        const auto one = context.bind(first, Value::integer(1));
        {
            const auto two = context.bind(first, Value::integer(2));
            ASSERT_NE(context.binding(first.get()), nullptr);
            EXPECT_EQ(*context.binding(first.get()), I(2));
        }
        EXPECT_EQ(*context.binding(first.get()), I(1));
    }
    EXPECT_EQ(context.target(), nullptr);
    EXPECT_EQ(context.binding(first.get()), nullptr);
}

TEST(ModelLevelEvaluable, TheRulesOfTheHelper) {
    const auto package = makePackage("P", makeRoot());
    const auto constant = featureWithValue("c", op("+", {integer(1), integer(2)}), package);
    const auto none = featureWithValue("none", nullptr, package);
    EXPECT_TRUE(isModelLevelEvaluable(integer(1)));
    EXPECT_TRUE(isModelLevelEvaluable(std::make_shared<KerML::Entities::NullExpression>()));
    EXPECT_TRUE(isModelLevelEvaluable(op("*", {integer(2), op("-", {integer(3)})})));
    EXPECT_TRUE(isModelLevelEvaluable(op("if", {boolean(true), integer(1), integer(2)})));
    EXPECT_TRUE(isModelLevelEvaluable(op("+", {referenceTo(constant), integer(1)})));
    // a feature without a featuring type and without a value is (the spec lets it be evaluated to the empty sequence)
    EXPECT_TRUE(isModelLevelEvaluable(referenceTo(none)));
    EXPECT_TRUE(isModelLevelEvaluable(op("+", {referenceTo(none), integer(1)})));
    EXPECT_TRUE(isModelLevelEvaluable(op("istype", {integer(1)})));
    EXPECT_TRUE(isModelLevelEvaluable(op("#", {integer(1), integer(1)})));
    EXPECT_TRUE(isModelLevelEvaluable(std::make_shared<KerML::Entities::MetadataAccessExpression>()));
    EXPECT_FALSE(isModelLevelEvaluable(op("frobnicate", {integer(1)})));
    EXPECT_FALSE(isModelLevelEvaluable(std::make_shared<Expression>()));
    EXPECT_FALSE(isModelLevelEvaluable(nullptr));
    EXPECT_FALSE(isModelLevelEvaluable(std::make_shared<KerML::Entities::FeatureReferenceExpression>()));
    // a cycle is not
    auto a = featureWithValue("a", nullptr, package);
    auto fv = std::make_shared<KerML::Entities::FeatureValue>();
    fv->setValue(referenceTo(a));
    a->appendOwnedElement(fv);
    EXPECT_FALSE(isModelLevelEvaluable(referenceTo(a)));
    dispose({constant, none, a});
}
