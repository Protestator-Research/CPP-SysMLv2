// Native functions of the scalar packages of the Kernel Function Library: NumericalFunctions (sum, product, abs, isZero, isUnit),
// DataFunctions (min, max), the conversions of IntegerFunctions / NaturalFunctions / RationalFunctions / RealFunctions / BooleanFunctions
// (ToString, ToInteger, ToNatural, ToRational, ToReal, ToBoolean, floor, round, sqrt, gcd, rat), TrigFunctions (sin, cos, arcsin, arccos,
// arctan; tan, cot, deg and rad run through their bodies) and StringFunctions (Length, Substring).
//
// Decisions: a Rational is a double (there are no exact fractions), so `rat(n, d)` is the Real n / d, and `numer` and `denom` are not
// implemented. `round` rounds half away from zero, `floor` and `ToInteger` give an Integer (`ToInteger` of a Real truncates towards
// zero), a Real that does not fit into an Integer is an Error. `sum` and `product` of an empty collection are 0 and 1 (0.0 and 1.0 for
// RationalFunctions and RealFunctions); a Real among Integers makes the result a Real. Strings are UTF-8; Length and Substring count
// code points, Substring(x, lower, upper) takes the characters lower..upper (1-based, inclusive) and an Error if they are outside.

#include "FunctionSupport.h"
#include "StandardFunctions.h"

#include <algorithm>
#include <charconv>
#include <cmath>
#include <limits>
#include <string>
#include <utility>

namespace SysMLv2::Evaluation::Functions {

    namespace {
        /// The number of an element of a collection (Integer or Real), or reports a type error.
        bool collectNumbers(EvaluationContext& context, const std::string& name, const Value& collection, std::vector<Number>& numbers) {
            for (const Item& item : collection.items()) {
                const auto number = toNumber(Value(item));
                if (!number) {
                    typeError(context, name, Arguments{collection});
                    return false;
                }
                numbers.push_back(*number);
            }
            return true;
        }

        /// sum (@p product false) or product of a collection of numbers.
        StrictFunction reduction(std::string name, bool product, bool alwaysReal) {
            return [name = std::move(name), product, alwaysReal](EvaluationContext& context, Arguments arguments) {
                if (!checkArity(context, name, arguments.size(), 1, 1)) return Value();
                std::vector<Number> numbers;
                if (!collectNumbers(context, name, arguments[0], numbers)) return Value();
                const bool real = alwaysReal || std::any_of(numbers.begin(), numbers.end(), [](const Number& number) { return !number.isInteger; });
                if (!real) {
                    std::int64_t result = product ? 1 : 0;
                    for (const Number& number : numbers) {
                        const bool fits = product ? checkedMultiply(result, number.integer, result) : checkedAdd(result, number.integer, result);
                        if (!fits) return fail(context, name, "Integer overflow");
                    }
                    return Value::integer(result);
                }
                double result = product ? 1.0 : 0.0;
                for (const Number& number : numbers) result = product ? result * number.value : result + number.value;
                return realResult(context, name, result);
            };
        }

        /// Converts a Real to an Integer with @p rounding, or reports that it does not fit.
        Value toIntegerResult(EvaluationContext& context, const std::string& name, double value) {
            if (!std::isfinite(value) || value >= 9223372036854775808.0 || value < -9223372036854775808.0) return fail(context, name, "the value " + Value::real(value).toString() + " is not an Integer");
            return Value::integer(static_cast<std::int64_t>(value));
        }

        /// Parses a whole String as an Integer (decimal, optional sign).
        std::optional<std::int64_t> parseInteger(const std::string& text) {
            std::int64_t value = 0;
            const char* begin = text.data();
            if (!text.empty() && text.front() == '+') ++begin;
            const auto result = std::from_chars(begin, text.data() + text.size(), value);
            if (result.ec != std::errc() || result.ptr != text.data() + text.size() || begin == text.data() + text.size()) return std::nullopt;
            return value;
        }

        /// Parses a whole String as a finite Real (the locale-independent classic format).
        std::optional<double> parseReal(const std::string& text) {
            if (text.empty()) return std::nullopt;
            try {
                std::size_t used = 0;
                const double value = std::stod(text, &used);
                if (used != text.size() || !std::isfinite(value)) return std::nullopt;
                return value;
            } catch (...) {
                return std::nullopt;
            }
        }

        /// The characters (code points) of a UTF-8 string as byte ranges.
        std::vector<std::pair<std::size_t, std::size_t>> characters(const std::string& text) {
            std::vector<std::pair<std::size_t, std::size_t>> result;
            for (std::size_t index = 0; index < text.size();) {
                const auto lead = static_cast<unsigned char>(text[index]);
                std::size_t length = lead < 0x80 ? 1 : (lead >> 5) == 0x6 ? 2 : (lead >> 4) == 0xE ? 3 : (lead >> 3) == 0x1E ? 4 : 1;
                length = std::min(length, text.size() - index);
                result.emplace_back(index, length);
                index += length;
            }
            return result;
        }

        /// A function of one Real: the argument is a number, the result a finite Real.
        StrictFunction realFunction(std::string name, double (*function)(double), bool (*domain)(double) = nullptr, const char* domainMessage = nullptr) {
            return [name = std::move(name), function, domain, domainMessage](EvaluationContext& context, Arguments arguments) {
                if (!checkArity(context, name, arguments.size(), 1, 1)) return Value();
                if (arguments[0].isNull()) return Value();
                const auto number = toNumber(arguments[0]);
                if (!number) return typeError(context, name, arguments);
                if (domain != nullptr && !domain(number->value)) return fail(context, name, domainMessage);
                return realResult(context, name, function(number->value));
            };
        }

        /// ToInteger / ToNatural / ToRational / ToReal / ToString conversions registered under every package that declares them.
        Value toIntegerValue(EvaluationContext& context, const std::string& name, const Arguments& arguments, bool natural) {
            if (!checkArity(context, name, arguments.size(), 1, 1) || arguments[0].isNull()) return Value();
            Value result;
            if (const auto text = arguments[0].asString()) {
                const auto parsed = parseInteger(*text);
                if (!parsed) return fail(context, name, "\"" + *text + "\" is not an Integer");
                result = Value::integer(*parsed);
            } else if (const auto number = toNumber(arguments[0])) {
                result = number->isInteger ? Value::integer(number->integer) : toIntegerResult(context, name, std::trunc(number->value));
                if (result.isNull()) return result;
            } else {
                return typeError(context, name, arguments);
            }
            if (natural && *result.asInteger() < 0) return fail(context, name, "the value " + std::to_string(*result.asInteger()) + " is not a Natural number");
            return result;
        }
    }

    void registerScalarFunctions(FunctionRegistry& registry) {
        // sum / product ------------------------------------------------------------------------------------------------------------
        registry.registerStrictFunction("NumericalFunctions::sum", reduction("NumericalFunctions::sum", false, false));
        registry.registerStrictFunction("NumericalFunctions::product", reduction("NumericalFunctions::product", true, false));
        registry.registerStrictFunction("IntegerFunctions::sum", reduction("IntegerFunctions::sum", false, false));
        registry.registerStrictFunction("IntegerFunctions::product", reduction("IntegerFunctions::product", true, false));
        for (const char* package : {"RationalFunctions", "RealFunctions"}) {
            registry.registerStrictFunction(std::string(package) + "::sum", reduction(std::string(package) + "::sum", false, true));
            registry.registerStrictFunction(std::string(package) + "::product", reduction(std::string(package) + "::product", true, true));
        }

        // abs, isZero, isUnit ----------------------------------------------------------------------------------------------------
        registry.registerStrictFunction("NumericalFunctions::abs", [](EvaluationContext& context, Arguments arguments) {
            const std::string name = "NumericalFunctions::abs";
            if (!checkArity(context, name, arguments.size(), 1, 1) || arguments[0].isNull()) return Value();
            const auto number = toNumber(arguments[0]);
            if (!number) return typeError(context, name, arguments);
            if (number->isInteger) {
                std::int64_t result = 0;
                if (!checkedSubtract(0, number->integer, result)) return fail(context, name, "Integer overflow");
                return Value::integer(number->integer < 0 ? result : number->integer);
            }
            return Value::real(std::fabs(number->value));
        });
        const auto compareWith = [](const char* name, std::int64_t constant) {
            return [name = std::string(name), constant](EvaluationContext& context, Arguments arguments) {
                if (!checkArity(context, name, arguments.size(), 1, 1) || arguments[0].isNull()) return Value();
                const auto number = toNumber(arguments[0]);
                if (!number) return typeError(context, name, arguments);
                return Value::boolean(compareNumbers(*number, Number{true, constant, static_cast<double>(constant)}) == Order::Equal);
            };
        };
        registry.registerStrictFunction("NumericalFunctions::isZero", compareWith("NumericalFunctions::isZero", 0));
        registry.registerStrictFunction("NumericalFunctions::isUnit", compareWith("NumericalFunctions::isUnit", 1));

        // min, max (numbers, strings) --------------------------------------------------------------------------------------------
        for (const bool maximum : {false, true}) {
            const std::string name = maximum ? "DataFunctions::max" : "DataFunctions::min";
            registry.registerStrictFunction(name, [name, maximum](EvaluationContext& context, Arguments arguments) {
                if (!checkArity(context, name, arguments.size(), 2, 2)) return Value();
                if (anyNull(arguments)) return Value();
                const auto a = toOrdered(arguments[0]);
                const auto b = toOrdered(arguments[1]);
                const auto order = (a && b) ? compareOrdered(*a, *b) : std::nullopt;
                if (!order || *order == Order::Unordered) return typeError(context, name, arguments);
                const bool second = maximum ? *order == Order::Less : *order == Order::Greater;
                return second ? std::move(arguments[1]) : std::move(arguments[0]);
            });
        }

        // Real functions -----------------------------------------------------------------------------------------------------------
        registry.registerStrictFunction("RealFunctions::sqrt", realFunction("RealFunctions::sqrt", [](double x) { return std::sqrt(x); }, [](double x) { return x >= 0.0; },
                                                                           "the square root of a negative number"));
        const auto rounding = [](const char* name, double (*function)(double)) {
            return [name = std::string(name), function](EvaluationContext& context, Arguments arguments) {
                if (!checkArity(context, name, arguments.size(), 1, 1) || arguments[0].isNull()) return Value();
                const auto number = toNumber(arguments[0]);
                if (!number) return typeError(context, name, arguments);
                if (number->isInteger) return Value::integer(number->integer);
                return toIntegerResult(context, name, function(number->value));
            };
        };
        registry.registerStrictFunction("RealFunctions::floor", rounding("RealFunctions::floor", [](double x) { return std::floor(x); }));
        registry.registerStrictFunction("RealFunctions::round", rounding("RealFunctions::round", [](double x) { return std::round(x); }));
        registry.registerStrictFunction("RationalFunctions::gcd", [](EvaluationContext& context, Arguments arguments) {
            const std::string name = "RationalFunctions::gcd";
            if (!checkArity(context, name, arguments.size(), 2, 2) || anyNull(arguments)) return Value();
            const auto a = arguments[0].asInteger();
            const auto b = arguments[1].asInteger();
            if (!a || !b) return typeError(context, name, arguments);
            std::uint64_t x = *a < 0 ? 0 - static_cast<std::uint64_t>(*a) : static_cast<std::uint64_t>(*a);
            std::uint64_t y = *b < 0 ? 0 - static_cast<std::uint64_t>(*b) : static_cast<std::uint64_t>(*b);
            while (y != 0) {
                const std::uint64_t rest = x % y;
                x = y;
                y = rest;
            }
            if (x > static_cast<std::uint64_t>(std::numeric_limits<std::int64_t>::max())) return fail(context, name, "Integer overflow");
            return Value::integer(static_cast<std::int64_t>(x));
        });
        registry.registerStrictFunction("RationalFunctions::rat", [](EvaluationContext& context, Arguments arguments) {
            const std::string name = "RationalFunctions::rat";
            if (!checkArity(context, name, arguments.size(), 2, 2) || anyNull(arguments)) return Value();
            const auto numerator = toNumber(arguments[0]);
            const auto denominator = toNumber(arguments[1]);
            if (!numerator || !denominator) return typeError(context, name, arguments);
            if (denominator->value == 0.0) return fail(context, name, "division by zero");
            return realResult(context, name, numerator->value / denominator->value);
        });

        // Conversions ---------------------------------------------------------------------------------------------------------------
        for (const char* name : {"RealFunctions::ToInteger", "RationalFunctions::ToInteger", "IntegerFunctions::ToInteger"}) {
            registry.registerStrictFunction(name, [name = std::string(name)](EvaluationContext& context, Arguments arguments) { return toIntegerValue(context, name, arguments, false); });
        }
        for (const char* name : {"IntegerFunctions::ToNatural", "NaturalFunctions::ToNatural"}) {
            registry.registerStrictFunction(name, [name = std::string(name)](EvaluationContext& context, Arguments arguments) { return toIntegerValue(context, name, arguments, true); });
        }
        const auto toReal = [](const char* name) {
            return [name = std::string(name)](EvaluationContext& context, Arguments arguments) {
                if (!checkArity(context, name, arguments.size(), 1, 1) || arguments[0].isNull()) return Value();
                if (const auto text = arguments[0].asString()) {
                    const auto parsed = parseReal(*text);
                    if (!parsed) return fail(context, name, "\"" + *text + "\" is not a Real number");
                    return Value::real(*parsed);
                }
                const auto number = toNumber(arguments[0]);
                if (!number) return typeError(context, name, arguments);
                return realResult(context, name, number->value);
            };
        };
        registry.registerStrictFunction("RealFunctions::ToReal", toReal("RealFunctions::ToReal"));
        registry.registerStrictFunction("RealFunctions::ToRational", toReal("RealFunctions::ToRational"));
        registry.registerStrictFunction("RationalFunctions::ToRational", toReal("RationalFunctions::ToRational"));
        registry.registerStrictFunction("BooleanFunctions::ToBoolean", [](EvaluationContext& context, Arguments arguments) {
            const std::string name = "BooleanFunctions::ToBoolean";
            if (!checkArity(context, name, arguments.size(), 1, 1) || arguments[0].isNull()) return Value();
            const auto text = arguments[0].asString();
            if (!text) return typeError(context, name, arguments);
            if (*text == "true") return Value::boolean(true);
            if (*text == "false") return Value::boolean(false);
            return fail(context, name, "\"" + *text + "\" is not a Boolean");
        });
        // ToString of any value: a String is itself, everything else its text (see Value::toString)
        registry.registerStrictFunction("BaseFunctions::ToString", [](EvaluationContext& context, Arguments arguments) {
            if (!checkArity(context, "BaseFunctions::ToString", arguments.size(), 1, 1) || arguments[0].isNull()) return Value();
            if (const auto text = arguments[0].asString()) return Value::string(*text);
            return Value::string(arguments[0].toString());
        });

        // Trigonometry (the angles are in radians; `pi` is the constant of the evaluator) -----------------------------------------------
        registry.registerStrictFunction("TrigFunctions::sin", realFunction("TrigFunctions::sin", [](double x) { return std::sin(x); }));
        registry.registerStrictFunction("TrigFunctions::cos", realFunction("TrigFunctions::cos", [](double x) { return std::cos(x); }));
        registry.registerStrictFunction("TrigFunctions::arctan", realFunction("TrigFunctions::arctan", [](double x) { return std::atan(x); }));
        registry.registerStrictFunction("TrigFunctions::arcsin", realFunction("TrigFunctions::arcsin", [](double x) { return std::asin(x); }, [](double x) { return x >= -1.0 && x <= 1.0; },
                                                                               "the argument is outside of [-1, 1]"));
        registry.registerStrictFunction("TrigFunctions::arccos", realFunction("TrigFunctions::arccos", [](double x) { return std::acos(x); }, [](double x) { return x >= -1.0 && x <= 1.0; },
                                                                               "the argument is outside of [-1, 1]"));
    }

    void registerStringFunctions(FunctionRegistry& registry) {
        registry.registerStrictFunction("StringFunctions::Length", [](EvaluationContext& context, Arguments arguments) {
            const std::string name = "StringFunctions::Length";
            if (!checkArity(context, name, arguments.size(), 1, 1) || arguments[0].isNull()) return Value();
            const auto text = arguments[0].asString();
            if (!text) return typeError(context, name, arguments);
            return Value::integer(static_cast<std::int64_t>(characters(*text).size()));
        });
        registry.registerStrictFunction("StringFunctions::Substring", [](EvaluationContext& context, Arguments arguments) {
            const std::string name = "StringFunctions::Substring";
            if (!checkArity(context, name, arguments.size(), 3, 3) || anyNull(arguments)) return Value();
            const auto text = arguments[0].asString();
            const auto lower = arguments[1].asInteger();
            const auto upper = arguments[2].asInteger();
            if (!text || !lower || !upper) return typeError(context, name, arguments);
            const auto chars = characters(*text);
            if (*lower < 1 || *upper > static_cast<std::int64_t>(chars.size()) || *lower > *upper + 1)
                return fail(context, name, "the characters " + std::to_string(*lower) + ".." + std::to_string(*upper) + " are outside of a string of " + std::to_string(chars.size()) + " characters");
            if (*lower > *upper) return Value::string("");
            const std::size_t begin = chars[static_cast<std::size_t>(*lower - 1)].first;
            const auto& last = chars[static_cast<std::size_t>(*upper - 1)];
            return Value::string(text->substr(begin, last.first + last.second - begin));
        });
    }
}
