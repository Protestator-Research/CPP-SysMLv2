#pragma once

#include <sysmlv2/evaluation/sysmlv2evaluation_global.h>

#include <kerml/root/elements/Element.h>

#include <cstddef>
#include <cstdint>
#include <memory>
#include <nlohmann/json.hpp>
#include <optional>
#include <string>
#include <variant>
#include <vector>

namespace SysMLv2::Evaluation {

    /// The value of the literal `*` (LiteralInfinity): unbounded. All Infinity items are equal.
    struct Infinity {
        bool operator==(const Infinity&) const = default;
    };

    /**
     * One element of a value sequence: a Boolean, an Integer, a Real (the code base represents Rational as double), a String, a model
     * element (compared by identity) or Infinity.
     */
    using Item = std::variant<bool, std::int64_t, double, std::string, std::shared_ptr<KerML::Entities::Element>, Infinity>;

    /**
     * The result of an evaluation. Every KerML value is a sequence: a single value is a sequence of one item, null is the empty sequence.
     * A Value that holds elements keeps them alive (it holds shared pointers).
     *
     * operator== is structural: it compares the items one by one and an Integer never equals a Real. The numeric equality of the KerML
     * function `==` (2 == 2.0) is implemented by the function, not by this operator.
     */
    class SYSMLV2EVALUATION_EXPORT Value {
    public:
        /// The null value (the empty sequence).
        Value() = default;
        /// A sequence of one item.
        explicit Value(Item item);
        /// A sequence of the given items (empty: null).
        explicit Value(std::vector<Item> items);

        [[nodiscard]] static Value null();
        [[nodiscard]] static Value boolean(bool value);
        [[nodiscard]] static Value integer(std::int64_t value);
        [[nodiscard]] static Value real(double value);
        [[nodiscard]] static Value string(std::string value);
        /// A single element; a null pointer gives the null Value (the empty sequence).
        [[nodiscard]] static Value element(std::shared_ptr<KerML::Entities::Element> value);
        [[nodiscard]] static Value infinity();

        [[nodiscard]] const std::vector<Item>& items() const;
        [[nodiscard]] std::size_t size() const;
        [[nodiscard]] bool isNull() const;

        /// Typed access for the single-item case: std::nullopt if the value is not exactly one item of that type.
        [[nodiscard]] std::optional<bool> asBoolean() const;
        [[nodiscard]] std::optional<std::int64_t> asInteger() const;
        /// A Real, or an Integer promoted to double.
        [[nodiscard]] std::optional<double> asReal() const;
        [[nodiscard]] std::optional<std::string> asString() const;
        [[nodiscard]] std::optional<std::shared_ptr<KerML::Entities::Element>> asElement() const;

        /**
         * Text of the value, independent of the global C and C++ locale. null: `null`; one item: the item; else `(a, b, c)`.
         * Booleans: `true` / `false`; Integers: decimal; Reals: the shortest digits that read back as the same double in one fixed format, independent
         * of the standard library and the locale: plain decimal with a decimal point for 1e-5 <= |x| < 1e21 (`100.0`, `0.1`, `2.0`, so
         * that the Real 2.0 differs from the Integer 2), else `d[.ddd]e[+-]x` (`1e+21`, `1e-7`); negative zero `-0.0`; non-finite: `nan`, `inf`, `-inf`;
         * Strings: double-quoted with the escape sequences `\" \\ \n \r \t`; elements: `@<uuid>`; Infinity: `*`.
         */
        [[nodiscard]] std::string toString() const;

        /**
         * JSON of the value. Scalars are JSON scalars (a Real with an integral value stays a JSON floating point number, a non-finite Real
         * is the string "NaN", "Infinity" or "-Infinity"), elements are `{"@id": "<uuid>"}`, Infinity is the string "*", a sequence of
         * any other size than one is an array and null is JSON `null` (the empty sequence).
         */
        [[nodiscard]] nlohmann::json toJson() const;

        bool operator==(const Value& other) const;
        bool operator!=(const Value& other) const;

    private:
        std::vector<Item> Items;
    };

    /// The text of one item, see Value::toString().
    [[nodiscard]] SYSMLV2EVALUATION_EXPORT std::string itemToString(const Item& item);
    /// The JSON of one item, see Value::toJson().
    [[nodiscard]] SYSMLV2EVALUATION_EXPORT nlohmann::json itemToJson(const Item& item);
}
