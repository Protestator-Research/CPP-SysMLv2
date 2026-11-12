#include "TestSupport.h"

#include <kerml/kernel/expressions/OperatorExpression.h>

#include <cmath>

using namespace TestSupport;

TEST(BaseFunctions, EqualityOfData) {
    const double nan = std::nan("");
    runCases({
        {BF("=="), {I(1), I(1)}, B(true), ""},
        {BF("=="), {I(1), I(2)}, B(false), ""},
        {BF("=="), {I(2), R(2.0)}, B(true), ""},     // Integer and Real compare numerically
        {BF("=="), {R(2.0), I(2)}, B(true), ""},
        {BF("=="), {I(2), R(2.5)}, B(false), ""},
        {BF("=="), {I(Max), R(9223372036854775808.0)}, B(false), ""},   // (no rounding of the Integer)
        {BF("=="), {I(Min), R(-9223372036854775808.0)}, B(true), ""},
        {BF("=="), {R(0.1), R(0.1)}, B(true), ""},
        {BF("=="), {R(nan), R(nan)}, B(false), ""},
        {BF("=="), {S("a"), S("a")}, B(true), ""},
        {BF("=="), {S("a"), S("b")}, B(false), ""},
        {BF("=="), {B(true), B(true)}, B(true), ""},
        {BF("=="), {B(true), B(false)}, B(false), ""},
        {BF("=="), {I(1), S("1")}, B(false), ""},    // (different kinds are unequal, not an error)
        {BF("=="), {I(1), B(true)}, B(false), ""},
        {BF("=="), {Inf(), Inf()}, B(true), ""},
        {BF("=="), {Inf(), I(1)}, B(false), ""},
        // sequences
        {BF("=="), {Seq({1, 2}), Seq({1, 2})}, B(true), ""},
        {BF("=="), {Seq({1, 2}), Seq({1, 3})}, B(false), ""},
        {BF("=="), {Seq({1, 2}), Seq({1})}, B(false), ""},
        {BF("=="), {Seq({1}), I(1)}, B(true), ""},    // (a single value is a sequence of one)
        // null does not propagate: it is the empty sequence
        {BF("=="), {N(), N()}, B(true), ""},
        {BF("=="), {N(), I(1)}, B(false), ""},
        {BF("=="), {I(1), N()}, B(false), ""},
        {BF("!="), {N(), N()}, B(false), ""},
        {BF("!="), {I(1), I(2)}, B(true), ""},
        {BF("!="), {I(1), R(1.0)}, B(false), ""},
        {BF("!="), {Seq({1, 2}), Seq({1})}, B(true), ""},
        // identity of data values: the same as equality (equal data values are identical)
        {BF("==="), {I(1), I(1)}, B(true), ""},
        {BF("==="), {I(1), I(2)}, B(false), ""},
        {BF("==="), {S("a"), S("a")}, B(true), ""},
        {BF("==="), {I(2), R(2.0)}, B(true), ""},
        {BF("==="), {N(), N()}, B(true), ""},
        {BF("!=="), {I(1), I(2)}, B(true), ""},
        {BF("!=="), {S("a"), S("a")}, B(false), ""},
        {BF("!=="), {Seq({1, 2}), Seq({1, 2})}, B(false), ""},
        // arity
        {BF("=="), {I(1)}, N(), "BaseFunctions::'==': expected 2 argument(s) but got 1"},
        {BF("!="), {I(1), I(2), I(3)}, N(), "expected 2 argument(s) but got 3"},
        {BF("==="), {}, N(), "expected 2 argument(s) but got 0"},
        {BF("!=="), {I(1)}, N(), "expected 2 argument(s) but got 1"},
    });
}

TEST(BaseFunctions, ElementsAreComparedByIdentity) {
    const auto a = std::make_shared<KerML::Entities::Package>();
    const auto b = std::make_shared<KerML::Entities::Package>();
    const std::shared_ptr<KerML::Entities::Element> first = a;
    const std::shared_ptr<KerML::Entities::Element> second = b;
    runCases({
        {BF("=="), {Value::element(first), Value::element(first)}, B(true), ""},
        {BF("=="), {Value::element(first), Value::element(second)}, B(false), ""},
        {BF("!="), {Value::element(first), Value::element(second)}, B(true), ""},
        {BF("==="), {Value::element(first), Value::element(first)}, B(true), ""},
        {BF("==="), {Value::element(first), Value::element(second)}, B(false), ""},
        {BF("!=="), {Value::element(first), Value::element(second)}, B(true), ""},
        {BF("!=="), {Value::element(first), Value::element(first)}, B(false), ""},
        {BF("=="), {Value::element(first), I(1)}, B(false), ""},
    });
}

TEST(BaseFunctions, Concatenation) {
    const auto element = std::make_shared<KerML::Entities::Package>();
    runCases({
        {BF(","), {I(1), I(2)}, Seq({1, 2}), ""},
        {BF(","), {Seq({1, 2}), I(3)}, Seq({1, 2, 3}), ""},
        {BF(","), {I(1), Seq({2, 3})}, Seq({1, 2, 3}), ""},
        {BF(","), {Seq({1}), Seq({2})}, Seq({1, 2}), ""},
        {BF(","), {N(), I(1)}, I(1), ""},          // null contributes nothing (no propagation)
        {BF(","), {I(1), N()}, I(1), ""},
        {BF(","), {N(), N()}, N(), ""},
        {BF(","), {S("a"), I(1)}, Value(std::vector<Item>{Item(std::in_place_type<std::string>, "a"), Item(std::in_place_type<std::int64_t>, 1)}), ""},
        {BF(","), {Value::element(element), Inf()},
         Value(std::vector<Item>{Item(std::shared_ptr<KerML::Entities::Element>(element)), Item(Infinity{})}), ""},
        {BF(","), {I(1)}, N(), "expected 2 argument(s) but got 1"},
        {BF(","), {I(1), I(2), I(3)}, N(), "expected 2 argument(s) but got 3"},
    });
}

namespace {
    using KerML::Entities::OperatorExpression;

    std::shared_ptr<OperatorExpression> comma(const ExpressionPtr& left, const ExpressionPtr& right) {
        auto expression = std::make_shared<OperatorExpression>();
        expression->setOperatorName(",");
        expression->setArgument({left, right});
        return expression;
    }

    /// The nodes of a long chain, kept so that the chain can be taken apart iteratively (a 100'000 deep chain of shared_ptr would
    /// overflow the stack when it is destroyed recursively).
    struct Chain {
        std::vector<std::shared_ptr<OperatorExpression>> nodes;
        ~Chain() {
            for (const auto& node : nodes) node->setArgument({});
        }
    };
}

TEST(BaseFunctions, ConcatenationWalksNestedChainsIteratively) {
    // (creating an element costs ~50 microseconds because of its random UUID, so the literals are shared: ten distinct ones, cycled)
    constexpr int count = 100'000;
    constexpr int leftCount = 20'000;
    std::vector<ExpressionPtr> shared;
    for (int index = 0; index < 10; ++index) shared.push_back(literalInteger(index));
    const auto length = [](const Value& value) { return value.size(); };
    {
        // (1, (2, (3, ...))): right nested, as the parser builds `(e1, ..., eN)`
        Chain chain;
        const auto literal = [&](int index) { return shared[static_cast<std::size_t>(index % 10)]; };
        ExpressionPtr tail = literal(count - 1);
        for (int index = count - 2; index >= 0; --index) {
            chain.nodes.push_back(comma(literal(index), tail));
            tail = chain.nodes.back();
        }
        Harness harness;
        const Value result = harness.callExpressions(BF(","), chain.nodes.back()->argument());
        ASSERT_EQ(length(result), static_cast<std::size_t>(count));
        EXPECT_EQ(std::get<std::int64_t>(result.items().front()), 0);
        EXPECT_EQ(std::get<std::int64_t>(result.items()[12345]), 5);
        EXPECT_EQ(std::get<std::int64_t>(result.items().back()), (count - 1) % 10);
        EXPECT_TRUE(harness.Context.diagnostics().empty());
        EXPECT_EQ(harness.Evaluated.size(), static_cast<std::size_t>(count));   // (only the leaves are evaluated)
    }
    {
        // ((((1, 2), 3), 4), ...): left nested
        Chain chain;
        const auto literal = [&](int index) { return shared[static_cast<std::size_t>(index % 10)]; };
        ExpressionPtr head = literal(0);
        for (int index = 1; index < leftCount - 1; ++index) {
            chain.nodes.push_back(comma(head, literal(index)));
            head = chain.nodes.back();
        }
        Harness harness;
        const Value result = harness.callExpressions(BF(","), {head, literal(leftCount - 1)});
        ASSERT_EQ(length(result), static_cast<std::size_t>(leftCount));
        EXPECT_EQ(std::get<std::int64_t>(result.items().front()), 0);
        EXPECT_EQ(std::get<std::int64_t>(result.items()[777]), 7);
        EXPECT_EQ(std::get<std::int64_t>(result.items().back()), (leftCount - 1) % 10);
        EXPECT_TRUE(harness.Context.diagnostics().empty());
    }
}

TEST(BaseFunctions, ConcatenationOfNestedExpressionsKeepsOrderAndNulls) {
    Harness harness;
    const auto a = harness.stand(Seq({1, 2}));
    const auto nothing = harness.stand(N());
    const auto c = literalInteger(3);
    const auto d = literalInteger(4);
    const auto inner = comma(a, nothing);
    const auto other = comma(c, d);
    EXPECT_EQ(harness.callExpressions(BF(","), {inner, other}), Seq({1, 2, 3, 4}));
    EXPECT_EQ(harness.callExpressions(BF(","), {other, inner}), Seq({3, 4, 1, 2}));
    EXPECT_TRUE(harness.Context.diagnostics().empty());

    // A nested `,` with the wrong number of operands is evaluated (and fails) like any expression: the hook yields null for it.
    auto malformed = std::make_shared<OperatorExpression>();
    malformed->setOperatorName(",");
    malformed->setArgument({c});
    EXPECT_EQ(harness.callExpressions(BF(","), {malformed, d}), I(4));
    inner->setArgument({});
    other->setArgument({});
}
