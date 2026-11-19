// The SequenceFunctions of the Kernel Function Library, implemented natively. The library defines most of them by recursion over
// `size`, `tail` and `subsequence` (`size(seq) = if isEmpty(seq) ? 0 else size(tail(seq)) + 1`), which is quadratic and runs into the
// depth limit for a list of a few hundred items, so they are linear native functions with the semantics of those bodies. A sequence
// that is null is the empty sequence, never an error. Positions are 1-based.

#include "FunctionSupport.h"
#include "StandardFunctions.h"

#include <cmath>
#include <optional>
#include <unordered_set>
#include <utility>

namespace SysMLv2::Evaluation::Functions {

    namespace {
        Value fromItems(std::vector<Item> items) { return Value(std::move(items)); }

        /// The identity of an item for hashing, consistent with `==` (ItemEquality): an integral Real is the Integer of the same value
        /// (2 == 2.0), elements are equal by identity. A NaN is equal to nothing and has no key.
        struct ItemKey {
            int Kind = 0;                 // 0 Boolean, 1 Integer, 2 Real (not integral), 3 String, 4 element, 5 Infinity
            std::int64_t Integer = 0;     // (also the Boolean)
            double Real = 0.0;
            std::string Text;
            const void* Pointer = nullptr;
            bool operator==(const ItemKey& other) const {
                return Kind == other.Kind && Integer == other.Integer && Real == other.Real && Text == other.Text && Pointer == other.Pointer;
            }
        };

        struct ItemKeyHash {
            std::size_t operator()(const ItemKey& key) const {
                std::size_t hash = std::hash<int>()(key.Kind);
                const auto mix = [&hash](std::size_t value) { hash ^= value + 0x9e3779b97f4a7c15ULL + (hash << 6) + (hash >> 2); };
                mix(std::hash<std::int64_t>()(key.Integer));
                mix(std::hash<double>()(key.Real));
                mix(std::hash<std::string>()(key.Text));
                mix(std::hash<const void*>()(key.Pointer));
                return hash;
            }
        };

        std::optional<ItemKey> keyOf(const Item& item) {
            ItemKey key;
            if (const auto* flag = std::get_if<bool>(&item)) {
                key.Kind = 0;
                key.Integer = *flag ? 1 : 0;
            } else if (const auto* integer = std::get_if<std::int64_t>(&item)) {
                key.Kind = 1;
                key.Integer = *integer;
            } else if (const auto* real = std::get_if<double>(&item)) {
                if (std::isnan(*real)) return std::nullopt;
                if (*real >= -9223372036854775808.0 && *real < 9223372036854775808.0 && std::trunc(*real) == *real) {
                    key.Kind = 1;
                    key.Integer = static_cast<std::int64_t>(*real);
                } else {
                    key.Kind = 2;
                    key.Real = *real;
                }
            } else if (const auto* text = std::get_if<std::string>(&item)) {
                key.Kind = 3;
                key.Text = *text;
            } else if (const auto* element = std::get_if<std::shared_ptr<KerML::Entities::Element>>(&item)) {
                key.Kind = 4;
                key.Pointer = element->get();
            } else {
                key.Kind = 5;
            }
            return key;
        }

        /// The items of a sequence for membership tests in constant time (`==` of the items).
        class ItemSet {
        public:
            explicit ItemSet(const Value& seq) {
                Keys.reserve(seq.size());
                for (const Item& item : seq.items()) {
                    if (auto key = keyOf(item)) Keys.insert(std::move(*key));
                }
            }
            bool contains(const Item& item) const {
                const auto key = keyOf(item);
                return key && Keys.count(*key) != 0;
            }

        private:
            std::unordered_set<ItemKey, ItemKeyHash> Keys;
        };

        /// A position argument: a single Integer. Reports a type error and returns nullopt otherwise.
        std::optional<std::int64_t> position(EvaluationContext& context, const std::string& name, const Value& value, const Arguments& all) {
            const auto integer = value.asInteger();
            if (!integer) typeError(context, name, all);
            return integer;
        }

        /// The items start..end (inclusive, 1-based) of a sequence; positions outside of the sequence select nothing (the library maps
        /// `seq#(i)` over the range and `#` of a missing position is empty); end < start is empty.
        Value subsequence(const Value& seq, std::int64_t start, std::int64_t end) {
            std::vector<Item> items;
            const auto size = static_cast<std::int64_t>(seq.size());
            const std::int64_t from = start < 1 ? 1 : start;
            const std::int64_t to = end > size ? size : end;
            for (std::int64_t index = from; index <= to; ++index) items.push_back(seq.items()[static_cast<std::size_t>(index - 1)]);
            return fromItems(std::move(items));
        }

        Value concatenate(EvaluationContext& context, const std::string& name, std::initializer_list<const Value*> parts) {
            std::vector<Item> items;
            for (const Value* part : parts) {
                if (items.size() + part->size() > context.maxSequenceLength())
                    return fail(context, name, "the sequence is longer than the limit of " + std::to_string(context.maxSequenceLength()) + " items");
                items.insert(items.end(), part->items().begin(), part->items().end());
            }
            return fromItems(std::move(items));
        }
    }

    void registerSequenceFunctions(FunctionRegistry& registry) {
        // `seq#(i)`: the item at a position, null if there is none. Several positions give the items at each of them.
        const auto index = [](const std::string& name) {
            return [name](EvaluationContext& context, Arguments arguments) {
                if (!checkArity(context, name, arguments.size(), 2, 2)) return Value();
                if (arguments[1].isNull()) return Value();
                std::vector<Item> items;
                for (const Item& at : arguments[1].items()) {
                    const auto* integer = std::get_if<std::int64_t>(&at);
                    if (integer == nullptr) return typeError(context, name, arguments);
                    // (a position outside of the sequence, also one below 1, selects nothing)
                    if (*integer >= 1 && static_cast<std::uint64_t>(*integer) <= arguments[0].size()) items.push_back(arguments[0].items()[static_cast<std::size_t>(*integer - 1)]);
                }
                return fromItems(std::move(items));
            };
        };
        registry.registerStrictFunction("BaseFunctions::'#'", index("BaseFunctions::'#'"));
        registry.registerStrictFunction("SequenceFunctions::'#'", index("SequenceFunctions::'#'"));

        registry.registerStrictFunction("SequenceFunctions::size", [](EvaluationContext& context, Arguments arguments) {
            if (!checkArity(context, "SequenceFunctions::size", arguments.size(), 1, 1)) return Value();
            return Value::integer(static_cast<std::int64_t>(arguments[0].size()));
        });
        registry.registerStrictFunction("SequenceFunctions::isEmpty", [](EvaluationContext& context, Arguments arguments) {
            if (!checkArity(context, "SequenceFunctions::isEmpty", arguments.size(), 1, 1)) return Value();
            return Value::boolean(arguments[0].isNull());
        });
        registry.registerStrictFunction("SequenceFunctions::notEmpty", [](EvaluationContext& context, Arguments arguments) {
            if (!checkArity(context, "SequenceFunctions::notEmpty", arguments.size(), 1, 1)) return Value();
            return Value::boolean(!arguments[0].isNull());
        });

        // equals compares the items one by one (`==`), same compares them as `===` (for data values the same)
        for (const char* name : {"SequenceFunctions::equals", "SequenceFunctions::same"}) {
            registry.registerStrictFunction(name, [name = std::string(name)](EvaluationContext& context, Arguments arguments) {
                if (!checkArity(context, name, arguments.size(), 2, 2)) return Value();
                return Value::boolean(equal(arguments[0], arguments[1]));
            });
        }

        // includes: every item of the second sequence is in the first; includesOnly: both ways; excludes: no item of the second is in the first
        registry.registerStrictFunction("SequenceFunctions::includes", [](EvaluationContext& context, Arguments arguments) {
            if (!checkArity(context, "SequenceFunctions::includes", arguments.size(), 2, 2)) return Value();
            const ItemSet first(arguments[0]);
            for (const Item& item : arguments[1].items()) {
                if (!first.contains(item)) return Value::boolean(false);
            }
            return Value::boolean(true);
        });
        registry.registerStrictFunction("SequenceFunctions::includesOnly", [](EvaluationContext& context, Arguments arguments) {
            if (!checkArity(context, "SequenceFunctions::includesOnly", arguments.size(), 2, 2)) return Value();
            const ItemSet first(arguments[0]);
            const ItemSet second(arguments[1]);
            for (const Item& item : arguments[1].items()) {
                if (!first.contains(item)) return Value::boolean(false);
            }
            for (const Item& item : arguments[0].items()) {
                if (!second.contains(item)) return Value::boolean(false);
            }
            return Value::boolean(true);
        });
        registry.registerStrictFunction("SequenceFunctions::excludes", [](EvaluationContext& context, Arguments arguments) {
            if (!checkArity(context, "SequenceFunctions::excludes", arguments.size(), 2, 2)) return Value();
            const ItemSet first(arguments[0]);
            for (const Item& item : arguments[1].items()) {
                if (first.contains(item)) return Value::boolean(false);
            }
            return Value::boolean(true);
        });

        for (const char* name : {"SequenceFunctions::union", "SequenceFunctions::including"}) {
            registry.registerStrictFunction(name, [name = std::string(name)](EvaluationContext& context, Arguments arguments) {
                if (!checkArity(context, name, arguments.size(), 2, 2)) return Value();
                return concatenate(context, name, {&arguments[0], &arguments[1]});
            });
        }
        registry.registerStrictFunction("SequenceFunctions::intersection", [](EvaluationContext& context, Arguments arguments) {
            if (!checkArity(context, "SequenceFunctions::intersection", arguments.size(), 2, 2)) return Value();
            std::vector<Item> items;
            const ItemSet second(arguments[1]);
            for (const Item& item : arguments[0].items()) {
                if (second.contains(item)) items.push_back(item);
            }
            return fromItems(std::move(items));
        });
        registry.registerStrictFunction("SequenceFunctions::excluding", [](EvaluationContext& context, Arguments arguments) {
            if (!checkArity(context, "SequenceFunctions::excluding", arguments.size(), 2, 2)) return Value();
            std::vector<Item> items;
            const ItemSet second(arguments[1]);
            for (const Item& item : arguments[0].items()) {
                if (!second.contains(item)) items.push_back(item);
            }
            return fromItems(std::move(items));
        });

        // includingAt replaces the item at the position by the values, like the library body (seq[1..i-1], values, seq[i+1..])
        registry.registerStrictFunction("SequenceFunctions::includingAt", [](EvaluationContext& context, Arguments arguments) {
            const std::string name = "SequenceFunctions::includingAt";
            if (!checkArity(context, name, arguments.size(), 3, 3)) return Value();
            if (arguments[2].isNull()) return Value();   // (no position: nothing to include at)
            const auto at = position(context, name, arguments[2], arguments);
            if (!at) return Value();
            const Value before = subsequence(arguments[0], 1, *at - 1);
            const Value after = subsequence(arguments[0], *at + 1, static_cast<std::int64_t>(arguments[0].size()));
            return concatenate(context, name, {&before, &arguments[1], &after});
        });
        registry.registerStrictFunction("SequenceFunctions::excludingAt", [](EvaluationContext& context, Arguments arguments) {
            const std::string name = "SequenceFunctions::excludingAt";
            if (!checkArity(context, name, arguments.size(), 2, 3)) return Value();
            if (arguments[1].isNull()) return Value();
            const auto start = position(context, name, arguments[1], arguments);
            if (!start) return Value();
            std::optional<std::int64_t> end = start;
            if (arguments.size() == 3 && !arguments[2].isNull()) end = position(context, name, arguments[2], arguments);
            if (!end) return Value();
            const Value before = subsequence(arguments[0], 1, *start - 1);
            const Value after = subsequence(arguments[0], *end + 1, static_cast<std::int64_t>(arguments[0].size()));
            return concatenate(context, name, {&before, &after});
        });
        registry.registerStrictFunction("SequenceFunctions::subsequence", [](EvaluationContext& context, Arguments arguments) {
            const std::string name = "SequenceFunctions::subsequence";
            if (!checkArity(context, name, arguments.size(), 2, 3)) return Value();
            if (arguments[1].isNull()) return Value();
            const auto start = position(context, name, arguments[1], arguments);
            if (!start) return Value();
            std::optional<std::int64_t> end = static_cast<std::int64_t>(arguments[0].size());   // (the default of the end index is size(seq))
            if (arguments.size() == 3 && !arguments[2].isNull()) end = position(context, name, arguments[2], arguments);
            if (!end) return Value();
            return subsequence(arguments[0], *start, *end);
        });
        registry.registerStrictFunction("SequenceFunctions::head", [](EvaluationContext& context, Arguments arguments) {
            if (!checkArity(context, "SequenceFunctions::head", arguments.size(), 1, 1)) return Value();
            return subsequence(arguments[0], 1, 1);
        });
        registry.registerStrictFunction("SequenceFunctions::tail", [](EvaluationContext& context, Arguments arguments) {
            if (!checkArity(context, "SequenceFunctions::tail", arguments.size(), 1, 1)) return Value();
            return subsequence(arguments[0], 2, static_cast<std::int64_t>(arguments[0].size()));
        });
        registry.registerStrictFunction("SequenceFunctions::last", [](EvaluationContext& context, Arguments arguments) {
            if (!checkArity(context, "SequenceFunctions::last", arguments.size(), 1, 1)) return Value();
            const auto size = static_cast<std::int64_t>(arguments[0].size());
            return subsequence(arguments[0], size, size);
        });
    }
}
