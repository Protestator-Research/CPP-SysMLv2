// The DataFunctions of the Kernel Function Library: arithmetic, comparisons, Boolean operators and the range `..`.
//
// Runtime type choice: Integer op Integer gives an Integer for `+ - * % ** ^` (a negative exponent gives a Real); `/` always gives a
// Real (the library result type is Rational, which this code base represents as double); any Real operand gives a Real. Integer
// overflow and division by zero are errors (a diagnostic and the null result). A null operand gives null without a diagnostic.

#include "FunctionSupport.h"
#include "StandardFunctions.h"

#include <cmath>
#include <utility>

namespace SysMLv2::Evaluation::Functions {

    namespace {
        using IntegerOperation = bool (*)(std::int64_t, std::int64_t, std::int64_t&);
        using RealOperation = double (*)(double, double);

        /// Checks the arguments of a binary numeric function. False: the caller returns null (a diagnostic is reported where needed).
        bool binaryNumbers(EvaluationContext& context, const std::string& name, const Arguments& arguments, Number& left, Number& right) {
            if (!checkArity(context, name, arguments.size(), 2, 2)) return false;
            if (anyNull(arguments)) return false;
            const auto a = toNumber(arguments[0]);
            const auto b = toNumber(arguments[1]);
            if (!a || !b) {
                typeError(context, name, arguments);
                return false;
            }
            if (!std::isfinite(a->value) || !std::isfinite(b->value)) {
                fail(context, name, "operand is not a finite number");
                return false;
            }
            left = *a;
            right = *b;
            return true;
        }

        StrictFunction numeric(std::string name, IntegerOperation integerOperation, RealOperation realOperation) {
            return [name = std::move(name), integerOperation, realOperation](EvaluationContext& context, const Arguments& arguments) {
                Number a, b;
                if (!binaryNumbers(context, name, arguments, a, b)) return Value();
                if (a.isInteger && b.isInteger) {
                    std::int64_t result = 0;
                    if (!integerOperation(a.integer, b.integer, result)) return fail(context, name, "Integer overflow");
                    return Value::integer(result);
                }
                return realResult(context, name, realOperation(a.value, b.value));
            };
        }

        /// `a ** b` for an Integer base and a non-negative Integer exponent; false on overflow.
        bool integerPower(std::int64_t base, std::int64_t exponent, std::int64_t& result) {
            std::int64_t accumulator = 1;
            while (exponent > 0) {
                if ((exponent & 1) != 0 && !checkedMultiply(accumulator, base, accumulator)) return false;
                exponent >>= 1;
                // (the last squaring would overflow needlessly)
                if (exponent > 0 && !checkedMultiply(base, base, base)) return false;
            }
            result = accumulator;
            return true;
        }

        StrictFunction power(std::string name) {
            return [name = std::move(name)](EvaluationContext& context, const Arguments& arguments) {
                Number a, b;
                if (!binaryNumbers(context, name, arguments, a, b)) return Value();
                if (a.isInteger && b.isInteger && b.integer >= 0) {
                    std::int64_t result = 0;
                    if (!integerPower(a.integer, b.integer, result)) return fail(context, name, "Integer overflow");
                    return Value::integer(result);
                }
                if (a.value == 0.0 && b.value < 0.0) return fail(context, name, "zero raised to a negative power (division by zero)");
                return realResult(context, name, std::pow(a.value, b.value));
            };
        }

        /// `+` and `-`: binary, or unary with one argument; `+` also concatenates two Strings.
        StrictFunction plus() {
            const std::string name = "DataFunctions::'+'";
            return [name](EvaluationContext& context, Arguments arguments) {
                if (!checkArity(context, name, arguments.size(), 1, 2)) return Value();
                if (anyNull(arguments)) return Value();
                if (arguments.size() == 2) {
                    const auto left = arguments[0].asString();
                    const auto right = arguments[1].asString();
                    if (left && right) return Value::string(*left + *right);
                }
                Number a, b;
                if (arguments.size() == 1) {
                    const auto only = toNumber(arguments[0]);
                    if (!only) return typeError(context, name, arguments);
                    if (!std::isfinite(only->value)) return fail(context, name, "operand is not a finite number");
                    return std::move(arguments[0]);
                }
                if (!binaryNumbers(context, name, arguments, a, b)) return Value();
                if (a.isInteger && b.isInteger) {
                    std::int64_t result = 0;
                    if (!checkedAdd(a.integer, b.integer, result)) return fail(context, name, "Integer overflow");
                    return Value::integer(result);
                }
                return realResult(context, name, a.value + b.value);
            };
        }

        StrictFunction minus() {
            const std::string name = "DataFunctions::'-'";
            const StrictFunction binary = numeric(
                name, [](std::int64_t a, std::int64_t b, std::int64_t& r) { return checkedSubtract(a, b, r); },
                [](double a, double b) { return a - b; });
            return [name, binary](EvaluationContext& context, Arguments arguments) {
                if (!checkArity(context, name, arguments.size(), 1, 2)) return Value();
                if (arguments.size() == 2) return binary(context, std::move(arguments));
                if (anyNull(arguments)) return Value();
                const auto only = toNumber(arguments[0]);
                if (!only) return typeError(context, name, arguments);
                if (only->isInteger) {
                    std::int64_t result = 0;
                    if (!checkedSubtract(0, only->integer, result)) return fail(context, name, "Integer overflow");
                    return Value::integer(result);
                }
                if (!std::isfinite(only->value)) return fail(context, name, "operand is not a finite number");
                return Value::real(-only->value);
            };
        }

        /// `/`: Integer / Integer gives a Real.
        StrictFunction divide() {
            const std::string name = "DataFunctions::'/'";
            return [name](EvaluationContext& context, const Arguments& arguments) {
                Number a, b;
                if (!binaryNumbers(context, name, arguments, a, b)) return Value();
                if (b.value == 0.0) return fail(context, name, "division by zero");
                return realResult(context, name, a.value / b.value);
            };
        }

        /// `%`: the sign of the result follows the dividend (truncated division, like C++ `%` and std::fmod).
        StrictFunction remainder() {
            const std::string name = "DataFunctions::'%'";
            return [name](EvaluationContext& context, const Arguments& arguments) {
                Number a, b;
                if (!binaryNumbers(context, name, arguments, a, b)) return Value();
                if (b.value == 0.0) return fail(context, name, "modulo by zero");
                if (a.isInteger && b.isInteger) {
                    // (INT64_MIN % -1 is undefined behaviour in C++; mathematically it is 0 and does not overflow)
                    if (b.integer == -1) return Value::integer(0);
                    return Value::integer(a.integer % b.integer);
                }
                return realResult(context, name, std::fmod(a.value, b.value));
            };
        }

        // Ordering ---------------------------------------------------------------------------------------------------------------

        StrictFunction comparison(std::string name, bool (*accepts)(Order)) {
            return [name = std::move(name), accepts](EvaluationContext& context, const Arguments& arguments) {
                if (!checkArity(context, name, arguments.size(), 2, 2)) return Value();
                if (anyNull(arguments)) return Value();
                const auto a = toOrdered(arguments[0]);
                const auto b = toOrdered(arguments[1]);
                const auto result = (a && b) ? compareOrdered(*a, *b) : std::nullopt;
                if (!result) return typeError(context, name, arguments);
                return Value::boolean(accepts(*result));
            };
        }

        // Booleans ---------------------------------------------------------------------------------------------------------------

        StrictFunction booleanBinary(std::string name, bool (*operation)(bool, bool)) {
            return [name = std::move(name), operation](EvaluationContext& context, const Arguments& arguments) {
                if (!checkArity(context, name, arguments.size(), 2, 2)) return Value();
                if (anyNull(arguments)) return Value();
                const auto a = arguments[0].asBoolean();
                const auto b = arguments[1].asBoolean();
                if (!a || !b) return typeError(context, name, arguments);
                return Value::boolean(operation(*a, *b));
            };
        }

        StrictFunction booleanNot() {
            const std::string name = "DataFunctions::'not'";
            return [name](EvaluationContext& context, const Arguments& arguments) {
                if (!checkArity(context, name, arguments.size(), 1, 1)) return Value();
                if (anyNull(arguments)) return Value();
                const auto a = arguments[0].asBoolean();
                if (!a) return typeError(context, name, arguments);
                return Value::boolean(!*a);
            };
        }

        // Range ------------------------------------------------------------------------------------------------------------------

        /// `lower..upper`: the Integers from lower to upper, inclusive; empty if lower > upper.
        StrictFunction range() {
            const std::string name = "DataFunctions::'..'";
            return [name](EvaluationContext& context, const Arguments& arguments) {
                if (!checkArity(context, name, arguments.size(), 2, 2)) return Value();
                if (anyNull(arguments)) return Value();
                const auto lower = arguments[0].asInteger();
                const auto upper = arguments[1].asInteger();
                if (!lower || !upper) return typeError(context, name, arguments);
                if (*lower > *upper) return Value();
                // (the distance fits into an unsigned 64 bit number; the number of items is distance + 1)
                const std::uint64_t distance = static_cast<std::uint64_t>(*upper) - static_cast<std::uint64_t>(*lower);
                if (distance >= static_cast<std::uint64_t>(context.maxSequenceLength())) {
                    return fail(context, name, "the range " + std::to_string(*lower) + ".." + std::to_string(*upper)
                                                   + " is longer than the maximum sequence length of " + std::to_string(context.maxSequenceLength()));
                }
                std::vector<Item> items;
                items.reserve(static_cast<std::size_t>(distance) + 1);
                for (std::uint64_t step = 0; step <= distance; ++step) {
                    items.emplace_back(std::in_place_type<std::int64_t>, static_cast<std::int64_t>(static_cast<std::uint64_t>(*lower) + step));
                }
                return Value(std::move(items));
            };
        }
    }

    void registerDataFunctions(FunctionRegistry& registry) {
        // Deliberate differences to the declarations of the Kernel Function Library: `%` is also defined for Reals (std::fmod); a negative
        // Integer exponent gives a Real instead of failing; `==` (see BaseFunctions) is defined for sequences of any length.
        // A Real result must be finite, else the call is an Error (one policy for + - * / % ** ^).
        registry.registerStrictFunction("DataFunctions::'+'", plus());
        registry.registerStrictFunction("DataFunctions::'-'", minus());
        registry.registerStrictFunction("DataFunctions::'*'",
            numeric("DataFunctions::'*'", [](std::int64_t a, std::int64_t b, std::int64_t& r) { return checkedMultiply(a, b, r); },
                    [](double a, double b) { return a * b; }));
        registry.registerStrictFunction("DataFunctions::'/'", divide());
        registry.registerStrictFunction("DataFunctions::'%'", remainder());
        registry.registerStrictFunction("DataFunctions::'**'", power("DataFunctions::'**'"));
        registry.registerStrictFunction("DataFunctions::'^'", power("DataFunctions::'^'"));

        registry.registerStrictFunction("DataFunctions::'<'", comparison("DataFunctions::'<'", [](Order o) { return o == Order::Less; }));
        registry.registerStrictFunction("DataFunctions::'>'", comparison("DataFunctions::'>'", [](Order o) { return o == Order::Greater; }));
        registry.registerStrictFunction("DataFunctions::'<='",
            comparison("DataFunctions::'<='", [](Order o) { return o == Order::Less || o == Order::Equal; }));
        registry.registerStrictFunction("DataFunctions::'>='",
            comparison("DataFunctions::'>='", [](Order o) { return o == Order::Greater || o == Order::Equal; }));

        registry.registerStrictFunction("DataFunctions::'not'", booleanNot());
        registry.registerStrictFunction("DataFunctions::'xor'", booleanBinary("DataFunctions::'xor'", [](bool a, bool b) { return a != b; }));
        registry.registerStrictFunction("DataFunctions::'|'", booleanBinary("DataFunctions::'|'", [](bool a, bool b) { return a || b; }));
        registry.registerStrictFunction("DataFunctions::'&'", booleanBinary("DataFunctions::'&'", [](bool a, bool b) { return a && b; }));

        registry.registerStrictFunction("DataFunctions::'..'", range());
    }
}
