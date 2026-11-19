// The ControlFunctions of the Kernel Function Library that are implemented natively. Their arguments are evaluated on demand, left to
// right, so that the branch that is not taken (and the second operand of a decided `and` / `or` / `implies`) is never evaluated.
// A null condition or left operand gives null without a diagnostic.

#include "FunctionSupport.h"
#include "StandardFunctions.h"

#include <optional>
#include <string>
#include <utility>

namespace SysMLv2::Evaluation::Functions {

    namespace {
        using Expressions = std::vector<std::shared_ptr<KerML::Entities::Expression>>;

        /// Evaluates a Boolean operand. nullopt: null or not a Boolean (a type error has been reported in the second case).
        std::optional<bool> booleanOperand(EvaluationContext& context, const std::string& name, const std::shared_ptr<KerML::Entities::Expression>& argument) {
            const Value value = context.evaluate(argument);
            if (value.isNull()) return std::nullopt;
            const auto result = value.asBoolean();
            if (!result) typeError(context, name, Arguments{value});
            return result;
        }

        /// `and`, `or`, `implies`: `decidedBy` is the value of the first operand that decides the result, which is then `decidedResult`.
        NativeFunction shortCircuit(std::string name, bool decidedBy, bool decidedResult) {
            return [name = std::move(name), decidedBy, decidedResult](EvaluationContext& context, const Expressions& arguments) {
                if (!checkArity(context, name, arguments.size(), 2, 2)) return Value();
                const auto first = booleanOperand(context, name, arguments[0]);
                if (!first) return Value();
                if (*first == decidedBy) return Value::boolean(decidedResult);
                const auto second = booleanOperand(context, name, arguments[1]);
                if (!second) return Value();
                return Value::boolean(*second);
            };
        }

        NativeFunction conditional() {
            const std::string name = "ControlFunctions::'if'";
            return [name](EvaluationContext& context, const Expressions& arguments) {
                if (!checkArity(context, name, arguments.size(), 2, 3)) return Value();
                const auto condition = booleanOperand(context, name, arguments[0]);
                if (!condition) return Value();
                if (*condition) return context.evaluate(arguments[1]);
                if (arguments.size() == 3) return context.evaluate(arguments[2]);
                return Value();   // (no else branch)
            };
        }

        NativeFunction nullCoalescing() {
            const std::string name = "ControlFunctions::'\?\?'";
            return [name](EvaluationContext& context, const Expressions& arguments) {
                if (!checkArity(context, name, arguments.size(), 2, 2)) return Value();
                Value first = context.evaluate(arguments[0]);
                if (!first.isNull()) return first;
                return context.evaluate(arguments[1]);
            };
        }
    }

    namespace {
        /// The truth of a test: a Boolean; null counts as not true; anything else is a type error (reported, nullopt).
        std::optional<bool> truth(EvaluationContext& context, const std::string& name, const Value& value) {
            if (value.isNull()) return false;
            const auto boolean = value.asBoolean();
            if (!boolean) typeError(context, name, Arguments{value});
            return boolean;
        }

        /// Calls the function value @p function with one item; nullopt after an error.
        std::optional<bool> test(EvaluationContext& context, const std::string& name, const std::shared_ptr<KerML::Entities::Expression>& function, const Item& item) {
            const Value result = context.invokeFunctionValue(function, {Value(item)});
            if (context.hasErrors()) return std::nullopt;
            return truth(context, name, result);
        }

        /// The collection of a higher-order function: its first argument, evaluated.
        bool collection(EvaluationContext& context, const std::string& name, const Expressions& arguments, Value& result) {
            if (!checkArity(context, name, arguments.size(), 2, 2)) return false;
            result = context.evaluate(arguments[0]);
            return !context.hasErrors();
        }

        NativeFunction selection(std::string name, bool keepIfTrue, bool firstOnly) {
            return [name = std::move(name), keepIfTrue, firstOnly](EvaluationContext& context, const Expressions& arguments) {
                Value items;
                if (!collection(context, name, arguments, items)) return Value();
                std::vector<Item> kept;
                for (const Item& item : items.items()) {
                    const auto passed = test(context, name, arguments[1], item);
                    if (!passed) return Value();
                    if (*passed == keepIfTrue) {
                        kept.push_back(item);
                        if (firstOnly) break;
                    }
                }
                return Value(std::move(kept));
            };
        }

        NativeFunction quantifier(std::string name, bool all) {
            return [name = std::move(name), all](EvaluationContext& context, const Expressions& arguments) {
                Value items;
                if (!collection(context, name, arguments, items)) return Value();
                for (const Item& item : items.items()) {
                    const auto passed = test(context, name, arguments[1], item);
                    if (!passed) return Value();
                    if (*passed != all) return Value::boolean(!all);   // forAll: a failing item; exists: a passing one
                }
                return Value::boolean(all);
            };
        }

        /// minimize / maximize: the least / greatest of the values of the function over the collection (null if the collection is empty).
        NativeFunction extreme(std::string name, bool maximum) {
            return [name = std::move(name), maximum](EvaluationContext& context, const Expressions& arguments) {
                Value items;
                if (!collection(context, name, arguments, items)) return Value();
                // like the library body `collection->collect {in x; fn(x)}->reduce min`: the values of the function for all items,
                // flattened, then the least or greatest of them
                std::vector<Item> values;
                for (const Item& item : items.items()) {
                    const Value result = context.invokeFunctionValue(arguments[1], {Value(item)});
                    if (context.hasErrors()) return Value();
                    if (values.size() + result.size() > context.maxSequenceLength())
                        return fail(context, name, "the sequence is longer than the limit of " + std::to_string(context.maxSequenceLength()) + " items");
                    values.insert(values.end(), result.items().begin(), result.items().end());
                }
                std::optional<Value> best;
                for (const Item& item : values) {
                    Value value{Item(item)};
                    if (!best) {
                        best = std::move(value);
                        continue;
                    }
                    const auto a = toOrdered(*best);
                    const auto b = toOrdered(value);
                    const auto order = (a && b) ? compareOrdered(*a, *b) : std::nullopt;
                    if (!order || *order == Order::Unordered) return typeError(context, name, Arguments{*best, value});
                    if (maximum ? *order == Order::Less : *order == Order::Greater) best = std::move(value);
                }
                return best ? *best : Value();
            };
        }
    }

    void registerControlFunctions(FunctionRegistry& registry) {
        registry.registerFunction("ControlFunctions::collect", [](EvaluationContext& context, const Expressions& arguments) {
            const std::string name = "ControlFunctions::collect";
            Value items;
            if (!collection(context, name, arguments, items)) return Value();
            std::vector<Item> mapped;
            for (const Item& item : items.items()) {
                const Value result = context.invokeFunctionValue(arguments[1], {Value(item)});
                if (context.hasErrors()) return Value();
                if (mapped.size() + result.size() > context.maxSequenceLength())
                    return fail(context, name, "the sequence is longer than the limit of " + std::to_string(context.maxSequenceLength()) + " items");
                mapped.insert(mapped.end(), result.items().begin(), result.items().end());
            }
            return Value(std::move(mapped));
        });
        registry.registerFunction("ControlFunctions::select", selection("ControlFunctions::select", true, false));
        registry.registerFunction("ControlFunctions::selectOne", selection("ControlFunctions::selectOne", true, true));
        registry.registerFunction("ControlFunctions::reject", selection("ControlFunctions::reject", false, false));
        registry.registerFunction("ControlFunctions::forAll", quantifier("ControlFunctions::forAll", true));
        registry.registerFunction("ControlFunctions::exists", quantifier("ControlFunctions::exists", false));
        registry.registerFunction("ControlFunctions::reduce", [](EvaluationContext& context, const Expressions& arguments) {
            const std::string name = "ControlFunctions::reduce";
            Value items;
            if (!collection(context, name, arguments, items)) return Value();
            if (items.isNull()) return Value();
            Value accumulator(items.items().front());
            for (std::size_t index = 1; index < items.size(); ++index) {
                accumulator = context.invokeFunctionValue(arguments[1], {std::move(accumulator), Value(items.items()[index])});
                if (context.hasErrors()) return Value();
            }
            return accumulator;
        });
        registry.registerFunction("ControlFunctions::minimize", extreme("ControlFunctions::minimize", false));
        registry.registerFunction("ControlFunctions::maximize", extreme("ControlFunctions::maximize", true));
        registry.registerStrictFunction("ControlFunctions::allTrue", [](EvaluationContext& context, Arguments arguments) {
            if (!checkArity(context, "ControlFunctions::allTrue", arguments.size(), 1, 1)) return Value();
            for (const Item& item : arguments[0].items()) {
                const auto passed = truth(context, "ControlFunctions::allTrue", Value(item));
                if (!passed) return Value();
                if (!*passed) return Value::boolean(false);
            }
            return Value::boolean(true);
        });
        registry.registerStrictFunction("ControlFunctions::anyTrue", [](EvaluationContext& context, Arguments arguments) {
            if (!checkArity(context, "ControlFunctions::anyTrue", arguments.size(), 1, 1)) return Value();
            for (const Item& item : arguments[0].items()) {
                const auto passed = truth(context, "ControlFunctions::anyTrue", Value(item));
                if (!passed) return Value();
                if (*passed) return Value::boolean(true);
            }
            return Value::boolean(false);
        });

        registry.registerFunction("ControlFunctions::'if'", conditional());
        // and: false and _ = false;  or: true or _ = true;  implies: false implies _ = true
        registry.registerFunction("ControlFunctions::'and'", shortCircuit("ControlFunctions::'and'", false, false));
        registry.registerFunction("ControlFunctions::'or'", shortCircuit("ControlFunctions::'or'", true, true));
        registry.registerFunction("ControlFunctions::'implies'", shortCircuit("ControlFunctions::'implies'", false, true));
        registry.registerFunction("ControlFunctions::'\?\?'", nullCoalescing());
    }
}
