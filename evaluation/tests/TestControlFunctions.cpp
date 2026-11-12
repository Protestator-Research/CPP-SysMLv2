#include "TestSupport.h"

using namespace TestSupport;

namespace {
    // The conditions and branches are real literal objects; the harness hook logs which of them were evaluated.
    struct Calls {
        Harness harness;
        ExpressionPtr yes = literalBoolean(true);
        ExpressionPtr no = literalBoolean(false);
        ExpressionPtr one = literalInteger(1);
        ExpressionPtr two = literalInteger(2);
        ExpressionPtr nothing = std::make_shared<KerML::Entities::NullExpression>();
        ExpressionPtr text = std::make_shared<KerML::Entities::LiteralString>();

        Value call(const std::string& name, const std::vector<ExpressionPtr>& arguments) { return harness.callExpressions(name, arguments); }
        bool evaluated(const ExpressionPtr& expression) const { return harness.wasEvaluated(expression); }
    };
}

TEST(ControlFunctions, IfEvaluatesOnlyTheChosenBranch) {
    {
        Calls c;
        EXPECT_EQ(c.call(CF("if"), {c.yes, c.one, c.two}), I(1));
        EXPECT_TRUE(c.evaluated(c.yes));
        EXPECT_TRUE(c.evaluated(c.one));
        EXPECT_FALSE(c.evaluated(c.two));
        EXPECT_TRUE(c.harness.Context.diagnostics().empty());
    }
    {
        Calls c;
        EXPECT_EQ(c.call(CF("if"), {c.no, c.one, c.two}), I(2));
        EXPECT_TRUE(c.evaluated(c.two));
        EXPECT_FALSE(c.evaluated(c.one));
    }
    {
        // a missing else branch gives null
        Calls c;
        EXPECT_EQ(c.call(CF("if"), {c.no, c.one}), N());
        EXPECT_FALSE(c.evaluated(c.one));
        EXPECT_TRUE(c.harness.Context.diagnostics().empty());
        EXPECT_EQ(c.call(CF("if"), {c.yes, c.one}), I(1));
    }
    {
        // a sequence is returned as it is
        Calls c;
        EXPECT_EQ(c.call(CF("if"), {c.yes, c.harness.stand(Seq({1, 2, 3}))}), Seq({1, 2, 3}));
    }
    {
        // a null condition gives null and evaluates no branch
        Calls c;
        EXPECT_EQ(c.call(CF("if"), {c.nothing, c.one, c.two}), N());
        EXPECT_FALSE(c.evaluated(c.one));
        EXPECT_FALSE(c.evaluated(c.two));
        EXPECT_TRUE(c.harness.Context.diagnostics().empty());
    }
    {
        Calls c;
        EXPECT_EQ(c.call(CF("if"), {c.one, c.one, c.two}), N());
        EXPECT_TRUE(hasError(c.harness.Context.diagnostics(), "ControlFunctions::'if': unsupported argument types (Integer)"));
        EXPECT_FALSE(c.evaluated(c.two));
    }
    {
        Calls c;
        EXPECT_EQ(c.call(CF("if"), {c.yes}), N());
        EXPECT_TRUE(hasError(c.harness.Context.diagnostics(), "expected 2 to 3 argument(s) but got 1"));
        EXPECT_FALSE(c.evaluated(c.yes));   // (the arity is checked before anything is evaluated)
        EXPECT_EQ(c.call(CF("if"), {c.yes, c.one, c.two, c.two}), N());
        EXPECT_TRUE(hasError(c.harness.Context.diagnostics(), "but got 4"));
    }
}

TEST(ControlFunctions, AndShortCircuits) {
    {
        Calls c;
        EXPECT_EQ(c.call(CF("and"), {c.no, c.one}), B(false));   // (the second operand is not even looked at: no type error)
        EXPECT_FALSE(c.evaluated(c.one));
        EXPECT_TRUE(c.harness.Context.diagnostics().empty());
    }
    {
        Calls c;
        EXPECT_EQ(c.call(CF("and"), {c.yes, c.yes}), B(true));
        EXPECT_EQ(c.call(CF("and"), {c.yes, c.no}), B(false));
        EXPECT_TRUE(c.harness.Context.diagnostics().empty());
    }
    {
        Calls c;
        EXPECT_EQ(c.call(CF("and"), {c.nothing, c.yes}), N());
        EXPECT_FALSE(c.evaluated(c.yes));
        EXPECT_EQ(c.call(CF("and"), {c.yes, c.nothing}), N());
        EXPECT_TRUE(c.harness.Context.diagnostics().empty());
    }
    {
        Calls c;
        EXPECT_EQ(c.call(CF("and"), {c.yes, c.one}), N());
        EXPECT_TRUE(hasError(c.harness.Context.diagnostics(), "ControlFunctions::'and': unsupported argument types (Integer)"));
        EXPECT_EQ(c.call(CF("and"), {c.one, c.yes}), N());
        EXPECT_EQ(c.call(CF("and"), {c.yes}), N());
        EXPECT_TRUE(hasError(c.harness.Context.diagnostics(), "expected 2 argument(s) but got 1"));
    }
}

TEST(ControlFunctions, OrShortCircuits) {
    {
        Calls c;
        EXPECT_EQ(c.call(CF("or"), {c.yes, c.one}), B(true));
        EXPECT_FALSE(c.evaluated(c.one));
        EXPECT_TRUE(c.harness.Context.diagnostics().empty());
    }
    {
        Calls c;
        EXPECT_EQ(c.call(CF("or"), {c.no, c.yes}), B(true));
        EXPECT_EQ(c.call(CF("or"), {c.no, c.no}), B(false));
        EXPECT_TRUE(c.evaluated(c.no));
        EXPECT_EQ(c.call(CF("or"), {c.nothing, c.yes}), N());
        EXPECT_EQ(c.call(CF("or"), {c.no, c.nothing}), N());
        EXPECT_TRUE(c.harness.Context.diagnostics().empty());
    }
    {
        Calls c;
        EXPECT_EQ(c.call(CF("or"), {c.no, c.text}), N());   // (a String is no Boolean; the empty LiteralString evaluates to "")
        EXPECT_TRUE(hasError(c.harness.Context.diagnostics(), "ControlFunctions::'or': unsupported argument types (String)"));
    }
}

TEST(ControlFunctions, ImpliesShortCircuits) {
    {
        Calls c;
        EXPECT_EQ(c.call(CF("implies"), {c.no, c.one}), B(true));   // false implies _ = true
        EXPECT_FALSE(c.evaluated(c.one));
        EXPECT_TRUE(c.harness.Context.diagnostics().empty());
    }
    {
        Calls c;
        EXPECT_EQ(c.call(CF("implies"), {c.yes, c.yes}), B(true));
        EXPECT_EQ(c.call(CF("implies"), {c.yes, c.no}), B(false));
        EXPECT_EQ(c.call(CF("implies"), {c.nothing, c.no}), N());
        EXPECT_EQ(c.call(CF("implies"), {c.yes, c.nothing}), N());
        EXPECT_TRUE(c.harness.Context.diagnostics().empty());
        EXPECT_EQ(c.call(CF("implies"), {c.yes, c.one}), N());
        EXPECT_TRUE(hasError(c.harness.Context.diagnostics(), "ControlFunctions::'implies'"));
    }
}

TEST(ControlFunctions, NullCoalescing) {
    const std::string name = "ControlFunctions::'\?\?'";
    {
        Calls c;
        EXPECT_EQ(c.call(name, {c.one, c.two}), I(1));
        EXPECT_FALSE(c.evaluated(c.two));
    }
    {
        Calls c;
        EXPECT_EQ(c.call(name, {c.nothing, c.two}), I(2));
        EXPECT_TRUE(c.evaluated(c.two));
        EXPECT_EQ(c.call(name, {c.nothing, c.nothing}), N());
        EXPECT_EQ(c.call(name, {c.harness.stand(Seq({1, 2})), c.two}), Seq({1, 2}));
        EXPECT_EQ(c.call(name, {c.no, c.two}), B(false));   // (false is not null)
        EXPECT_TRUE(c.harness.Context.diagnostics().empty());
        EXPECT_EQ(c.call(name, {c.one}), N());
        EXPECT_TRUE(hasError(c.harness.Context.diagnostics(), "expected 2 argument(s) but got 1"));
    }
}

TEST(ControlFunctions, EvaluationNeedsAHook) {
    // Without a hook, evaluating an argument is an Error and gives null.
    const auto registry = FunctionRegistry::withStandardFunctions();
    EvaluationContext context;
    const std::vector<ExpressionPtr> arguments = {literalBoolean(true), literalInteger(1), literalInteger(2)};
    const NativeFunction* function = registry.find(CF("if"));
    ASSERT_NE(function, nullptr);
    EXPECT_EQ((*function)(context, arguments), N());
    EXPECT_TRUE(hasError(context.diagnostics(), "No expression evaluator"));
}

TEST(EvaluationContext, DepthLimitAndGuard) {
    EvaluationContext context;
    EXPECT_EQ(context.maxDepth(), 256u);
    EXPECT_EQ(context.maxSequenceLength(), 1'000'000u);
    context.setMaxDepth(3);
    int calls = 0;
    ExpressionPtr expression = std::make_shared<KerML::Entities::Expression>();
    context.setExpressionEvaluator([&](const ExpressionPtr& e, EvaluationContext& inner) {
        ++calls;
        return inner.evaluate(e);   // endless recursion, stopped by the depth limit
    });
    EXPECT_EQ(context.evaluate(expression), N());
    EXPECT_EQ(calls, 3);
    EXPECT_EQ(context.depth(), 0u);   // (the guards have released every level)
    EXPECT_TRUE(hasError(context.diagnostics(), "maximum evaluation depth of 3"));
    EXPECT_TRUE(context.hasErrors());
    EXPECT_EQ(context.takeDiagnostics().size(), 1u);
    EXPECT_TRUE(context.diagnostics().empty());

    {
        auto outer = context.enterScope();
        EXPECT_TRUE(static_cast<bool>(outer));
        EXPECT_EQ(context.depth(), 1u);
    }
    EXPECT_EQ(context.depth(), 0u);

    EvaluationContext warnings;
    warnings.report(Severity::Warning, "careful");
    EXPECT_FALSE(warnings.hasErrors());
    EXPECT_EQ(warnings.diagnostics().size(), 1u);
    EXPECT_EQ(warnings.evaluate(nullptr), N());
    EXPECT_TRUE(warnings.hasErrors());

    Result result;
    result.diagnostics.push_back(Diagnostic{Severity::Warning, "w", nullptr});
    EXPECT_TRUE(result.ok());
    result.diagnostics.push_back(Diagnostic{Severity::Error, "e", nullptr});
    EXPECT_FALSE(result.ok());
}

TEST(EvaluationContext, TheHookMayReplaceItselfWhileRunning) {
    EvaluationContext context;
    const ExpressionPtr expression = std::make_shared<KerML::Entities::Expression>();
    // A hook with captured state that replaces itself and then keeps using its captures.
    context.setExpressionEvaluator([payload = std::make_shared<std::vector<int>>(1000, 7)](const ExpressionPtr&, EvaluationContext& inner) {
        inner.setExpressionEvaluator([](const ExpressionPtr&, EvaluationContext&) { return Value::integer(2); });
        std::int64_t sum = 0;
        for (const int item : *payload) sum += item;
        return Value::integer(sum);
    });
    EXPECT_EQ(context.evaluate(expression), I(7000));
    EXPECT_EQ(context.evaluate(expression), I(2));   // (the replacement is used from the next call on)
    context.setExpressionEvaluator(nullptr);
    EXPECT_EQ(context.evaluate(expression), N());
    EXPECT_TRUE(hasError(context.diagnostics(), "No expression evaluator"));
}

TEST(EvaluationContext, DiagnosticsAreLocatedAtTheInnermostCurrentElement) {
    Harness harness;
    const auto outer = std::make_shared<KerML::Entities::Expression>();
    const auto inner = std::make_shared<KerML::Entities::Expression>();
    const auto explicitElement = std::make_shared<KerML::Entities::Expression>();

    // Without a current element there is no location.
    harness.Context.report(Severity::Warning, "nowhere");
    ASSERT_EQ(harness.Context.diagnostics().size(), 1u);
    EXPECT_EQ(harness.Context.diagnostics()[0].element, nullptr);

    {
        const auto scope = harness.Context.enterElement(outer);
        harness.Context.report(Severity::Warning, "in outer");
        {
            const auto nested = harness.Context.enterElement(inner);
            harness.Context.report(Severity::Warning, "in inner");
            harness.Context.report(Severity::Warning, "explicit", explicitElement);
        }
        harness.Context.report(Severity::Warning, "back in outer");
    }
    harness.Context.report(Severity::Warning, "again nowhere");
    const auto& diagnostics = harness.Context.diagnostics();
    ASSERT_EQ(diagnostics.size(), 6u);
    EXPECT_EQ(diagnostics[1].element, outer);
    EXPECT_EQ(diagnostics[2].element, inner);
    EXPECT_EQ(diagnostics[3].element, explicitElement);
    EXPECT_EQ(diagnostics[4].element, outer);
    EXPECT_EQ(diagnostics[5].element, nullptr);
}

TEST(EvaluationContext, ErrorsOfNativeFunctionsCarryTheInvokingExpression) {
    // The hook plays the evaluator: it calls the native function for the expression it was asked to evaluate.
    const FunctionRegistry registry = FunctionRegistry::withStandardFunctions();
    EvaluationContext context;
    const ExpressionPtr invocation = std::make_shared<KerML::Entities::Expression>();
    const ExpressionPtr one = literalInteger(1);
    const ExpressionPtr text = std::make_shared<KerML::Entities::LiteralString>();
    context.setExpressionEvaluator([&](const ExpressionPtr& expression, EvaluationContext& inner) {
        if (expression == invocation) return (*registry.find(D("+")))(inner, {one, text});
        if (expression == one) return Value::integer(1);
        return Value::string("s");
    });
    EXPECT_EQ(context.evaluate(invocation), N());
    ASSERT_EQ(context.diagnostics().size(), 1u);
    EXPECT_EQ(context.diagnostics()[0].element, invocation);   // (the leaves are evaluated inside the invocation, but did not fail)
    EXPECT_NE(context.diagnostics()[0].message.find("DataFunctions::'+'"), std::string::npos);

    // An explicit element still wins.
    (void)context.takeDiagnostics();
    context.setExpressionEvaluator([&](const ExpressionPtr&, EvaluationContext& inner) {
        inner.report(Severity::Error, "explicit", one);
        return Value();
    });
    (void)context.evaluate(invocation);
    ASSERT_EQ(context.diagnostics().size(), 1u);
    EXPECT_EQ(context.diagnostics()[0].element, one);
}
