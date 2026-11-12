// The BaseFunctions of the Kernel Function Library that are implemented natively: equality, identity and sequence concatenation.

#include "../Arguments.h"
#include "FunctionSupport.h"
#include "StandardFunctions.h"

#include <kerml/kernel/expressions/OperatorExpression.h>

#include <cmath>
#include <utility>

namespace SysMLv2::Evaluation::Functions {

    namespace {
        struct ItemEquality {
            bool operator()(bool a, bool b) const { return a == b; }
            bool operator()(std::int64_t a, std::int64_t b) const { return a == b; }
            bool operator()(double a, double b) const { return a == b; }
            bool operator()(std::int64_t a, double b) const { return compareIntegerWithReal(a, b) == Order::Equal; }
            bool operator()(double a, std::int64_t b) const { return compareIntegerWithReal(b, a) == Order::Equal; }
            bool operator()(const std::string& a, const std::string& b) const { return a == b; }
            bool operator()(const std::shared_ptr<KerML::Entities::Element>& a, const std::shared_ptr<KerML::Entities::Element>& b) const {
                return a.get() == b.get();   // (identity)
            }
            bool operator()(Infinity, Infinity) const { return true; }
            template <class A, class B>
            bool operator()(const A&, const B&) const { return false; }   // (different kinds are never equal)
        };

        /// Sequence-wise equality: the same length and equal items at every position. An Integer equals the Real of the same value.
        bool equal(const Value& a, const Value& b) {
            if (a.size() != b.size()) return false;
            for (std::size_t index = 0; index < a.size(); ++index) {
                if (!std::visit(ItemEquality{}, a.items()[index], b.items()[index])) return false;
            }
            return true;
        }

        StrictFunction equality(std::string name, bool negate) {
            return [name = std::move(name), negate](EvaluationContext& context, const Arguments& arguments) {
                if (!checkArity(context, name, arguments.size(), 2, 2)) return Value();
                return Value::boolean(equal(arguments[0], arguments[1]) != negate);
            };
        }

        using Expressions = std::vector<std::shared_ptr<KerML::Entities::Expression>>;

        /// The two operands of a nested `,` operator expression, or an empty vector if the expression is something else.
        Expressions nestedOperands(const std::shared_ptr<KerML::Entities::Expression>& expression) {
            const auto nested = std::dynamic_pointer_cast<KerML::Entities::OperatorExpression>(expression);
            if (!nested || nested->operatorName() != ",") return {};
            ArgumentList list = argumentsOf(*nested);   // (also the XMI shapes, where argument() is empty)
            return !list.MissingValue && list.Values.size() == 2 ? std::move(list.Values) : Expressions{};
        }

        /**
         * `a, b`: the concatenation of the two sequences (null contributes nothing). A sequence `(e1, e2, ..., eN)` is parsed as nested `,`
         * expressions, so the nesting (left or right) is walked iteratively with an explicit stack: only the leaves are evaluated, each
         * one appends to one result vector. Neither the nesting depth nor the evaluation depth limit applies to the chain.
         */
        NativeFunction concatenation() {
            const std::string name = "BaseFunctions::','";
            return [name](EvaluationContext& context, const Expressions& arguments) {
                if (!checkArity(context, name, arguments.size(), 2, 2)) return Value();
                std::vector<Item> items;
                Expressions pending = {arguments[1], arguments[0]};   // (the top of the stack is the next operand in order)
                while (!pending.empty()) {
                    const std::shared_ptr<KerML::Entities::Expression> next = std::move(pending.back());
                    pending.pop_back();
                    if (Expressions operands = nestedOperands(next); !operands.empty()) {
                        pending.push_back(std::move(operands[1]));
                        pending.push_back(std::move(operands[0]));
                        continue;
                    }
                    Value value = context.evaluate(next);
                    if (items.size() + value.size() > context.maxSequenceLength())
                        return fail(context, name, "the sequence is longer than the limit of " + std::to_string(context.maxSequenceLength()) + " items");
                    if (items.empty()) {
                        items = std::vector<Item>(value.items());
                    } else {
                        items.insert(items.end(), value.items().begin(), value.items().end());
                    }
                }
                return Value(std::move(items));
            };
        }
    }

    void registerBaseFunctions(FunctionRegistry& registry) {
        // (for data values `===` is the same as `==`, since equal data values are identical; elements are compared by identity in both)
        registry.registerStrictFunction("BaseFunctions::'=='", equality("BaseFunctions::'=='", false));
        registry.registerStrictFunction("BaseFunctions::'!='", equality("BaseFunctions::'!='", true));
        registry.registerStrictFunction("BaseFunctions::'==='", equality("BaseFunctions::'==='", false));
        registry.registerStrictFunction("BaseFunctions::'!=='", equality("BaseFunctions::'!=='", true));
        registry.registerFunction("BaseFunctions::','", concatenation());
    }
}
