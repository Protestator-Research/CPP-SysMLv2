#pragma once

// Shared helpers of the native function implementations: argument checking, diagnostics and numeric promotion.

#include <sysmlv2/evaluation/EvaluationContext.h>
#include <sysmlv2/evaluation/Value.h>

#include <cmath>
#include <cstddef>
#include <cstdint>
#include <limits>
#include <optional>
#include <string>
#include <variant>
#include <vector>

namespace SysMLv2::Evaluation::Functions {

    using Arguments = std::vector<Value>;

    /// A short description of what a value is, for messages: `null`, `Boolean`, `Integer`, `Real`, `String`, `Element`, `Infinity` or
    /// `sequence of N items`.
    inline std::string describe(const Value& value) {
        if (value.isNull()) return "null";
        if (value.size() > 1) return "sequence of " + std::to_string(value.size()) + " items";
        struct Visitor {
            const char* operator()(bool) const { return "Boolean"; }
            const char* operator()(std::int64_t) const { return "Integer"; }
            const char* operator()(double) const { return "Real"; }
            const char* operator()(const std::string&) const { return "String"; }
            const char* operator()(const std::shared_ptr<KerML::Entities::Element>&) const { return "Element"; }
            const char* operator()(Infinity) const { return "Infinity"; }
        };
        return std::visit(Visitor{}, value.items().front());
    }

    inline std::string describe(const Arguments& arguments) {
        std::string out;
        for (std::size_t index = 0; index < arguments.size(); ++index) {
            if (index > 0) out += ", ";
            out += describe(arguments[index]);
        }
        return out;
    }

    /// Reports an Error `<function>: <message>` and returns null.
    inline Value fail(EvaluationContext& context, const std::string& function, const std::string& message) {
        context.report(Severity::Error, function + ": " + message);
        return Value();
    }

    /// Reports that the argument types are not supported by the function and returns null.
    inline Value typeError(EvaluationContext& context, const std::string& function, const Arguments& arguments) {
        return fail(context, function, "unsupported argument types (" + describe(arguments) + ")");
    }

    /// Checks `minimum <= count <= maximum`; reports an Error if not.
    inline bool checkArity(EvaluationContext& context, const std::string& function, std::size_t count, std::size_t minimum, std::size_t maximum) {
        if (count >= minimum && count <= maximum) return true;
        const std::string expected = minimum == maximum ? std::to_string(minimum) : std::to_string(minimum) + " to " + std::to_string(maximum);
        fail(context, function, "expected " + expected + " argument(s) but got " + std::to_string(count));
        return false;
    }

    inline bool anyNull(const Arguments& arguments) {
        for (const Value& argument : arguments) {
            if (argument.isNull()) return true;
        }
        return false;
    }

    /// An Integer or Real operand; `value` is the (promoted) double in both cases.
    struct Number {
        bool isInteger = false;
        std::int64_t integer = 0;
        double value = 0.0;
    };

    inline std::optional<Number> toNumber(const Value& value) {
        if (const auto integer = value.asInteger()) return Number{true, *integer, static_cast<double>(*integer)};
        if (value.size() == 1) {
            if (const double* real = std::get_if<double>(&value.items().front())) return Number{false, 0, *real};
        }
        return std::nullopt;
    }

    // Integer arithmetic without undefined behaviour: false if the result does not fit into 64 bits.
    inline bool checkedAdd(std::int64_t a, std::int64_t b, std::int64_t& result) {
        constexpr std::int64_t maximum = std::numeric_limits<std::int64_t>::max();
        constexpr std::int64_t minimum = std::numeric_limits<std::int64_t>::min();
        if (b > 0 ? a > maximum - b : a < minimum - b) return false;
        result = a + b;
        return true;
    }

    inline bool checkedSubtract(std::int64_t a, std::int64_t b, std::int64_t& result) {
        constexpr std::int64_t maximum = std::numeric_limits<std::int64_t>::max();
        constexpr std::int64_t minimum = std::numeric_limits<std::int64_t>::min();
        if (b > 0 ? a < minimum + b : a > maximum + b) return false;
        result = a - b;
        return true;
    }

    inline bool checkedMultiply(std::int64_t a, std::int64_t b, std::int64_t& result) {
        constexpr std::int64_t maximum = std::numeric_limits<std::int64_t>::max();
        constexpr std::int64_t minimum = std::numeric_limits<std::int64_t>::min();
        if (a > 0) {
            if (b > 0 ? a > maximum / b : b < minimum / a) return false;
        } else {
            if (b > 0 ? a < minimum / b : (a != 0 && b < maximum / a)) return false;
        }
        result = a * b;
        return true;
    }

    /// The result of ordering two numbers.
    enum class Order { Less, Equal, Greater, Unordered };

    template <class T>
    Order order(const T& a, const T& b) {
        return a < b ? Order::Less : (b < a ? Order::Greater : (a == b ? Order::Equal : Order::Unordered));
    }

    /// Exact three-way comparison of an Integer with a Real (no rounding of the Integer): NaN is unordered, infinities and values
    /// beyond the int64 range order correctly.
    inline Order compareIntegerWithReal(std::int64_t integer, double real) {
        if (std::isnan(real)) return Order::Unordered;
        if (real >= 9223372036854775808.0) return Order::Less;     // (2^63 and above, including +inf)
        if (real < -9223372036854775808.0) return Order::Greater;  // (below -2^63, including -inf)
        const double whole = std::trunc(real);                      // (within [-2^63, 2^63): converts exactly)
        const auto truncated = static_cast<std::int64_t>(whole);
        if (integer < truncated) return Order::Less;
        if (integer > truncated) return Order::Greater;
        const double fraction = real - whole;
        return fraction > 0.0 ? Order::Less : (fraction < 0.0 ? Order::Greater : Order::Equal);
    }

    /// Exact three-way comparison of two numbers; Integer with Integer is exact, Integer with Real see compareIntegerWithReal.
    inline Order compareNumbers(const Number& a, const Number& b) {
        if (a.isInteger && b.isInteger) return order(a.integer, b.integer);
        if (a.isInteger) return compareIntegerWithReal(a.integer, b.value);
        if (b.isInteger) {
            const Order reversed = compareIntegerWithReal(b.integer, a.value);
            return reversed == Order::Less ? Order::Greater : (reversed == Order::Greater ? Order::Less : reversed);
        }
        return order(a.value, b.value);
    }

    /// A Real result: finite, else an Error (`result is not a finite number`) and null.
    inline Value realResult(EvaluationContext& context, const std::string& function, double result) {
        if (!std::isfinite(result)) return fail(context, function, "result is not a finite number");
        return Value::real(result);
    }

    // Equality of values ------------------------------------------------------------------------------------------------------

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
    inline bool equal(const Value& a, const Value& b) {
        if (a.size() != b.size()) return false;
        for (std::size_t index = 0; index < a.size(); ++index) {
            if (!std::visit(ItemEquality{}, a.items()[index], b.items()[index])) return false;
        }
        return true;
    }


    // Ordering of values (numbers, strings, Infinity) ---------------------------------------------------------------------------

    struct Ordered {
        enum class Kind { Number, String, Infinity } kind = Kind::Number;
        Number number;
        std::string text;
    };

    inline std::optional<Ordered> toOrdered(const Value& value) {
        Ordered ordered;
        if (const auto number = toNumber(value)) {
            ordered.number = *number;
            return ordered;
        }
        if (const auto text = value.asString()) {
            ordered.kind = Ordered::Kind::String;
            ordered.text = *text;
            return ordered;
        }
        if (value.size() == 1 && std::holds_alternative<Infinity>(value.items().front())) {
            ordered.kind = Ordered::Kind::Infinity;
            return ordered;
        }
        return std::nullopt;
    }

    /// Orders two operands; nullopt if they are not comparable (a String with a number).
    inline std::optional<Order> compareOrdered(const Ordered& a, const Ordered& b) {
        using Kind = Ordered::Kind;
        if (a.kind == Kind::Infinity || b.kind == Kind::Infinity) {
            if (a.kind == Kind::String || b.kind == Kind::String) return std::nullopt;
            if (a.kind == b.kind) return Order::Equal;
            return a.kind == Kind::Infinity ? Order::Greater : Order::Less;   // (Infinity is greater than every number)
        }
        if (a.kind != b.kind) return std::nullopt;
        if (a.kind == Kind::String) {
            const int comparison = a.text.compare(b.text);   // (by code unit)
            return comparison < 0 ? Order::Less : (comparison > 0 ? Order::Greater : Order::Equal);
        }
        return compareNumbers(a.number, b.number);
    }
}
