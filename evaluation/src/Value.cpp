#include <sysmlv2/evaluation/Value.h>

#include <charconv>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <system_error>

namespace SysMLv2::Evaluation {

    namespace {
        std::string integerText(std::int64_t value) {
            char buffer[32];
            const auto result = std::to_chars(buffer, buffer + sizeof(buffer), value);
            return std::string(buffer, result.ptr);
        }

        /// The text of a double in one fixed format that depends neither on the standard library nor on the locale: the shortest decimal
        /// digits that read back as the same value (found with snprintf / strtod, not std::to_chars, which libc++ offers only from
        /// macOS 13.3), laid out as plain decimal for 1e-5 <= |x| < 1e21 (always with a decimal point: 100.0, 0.1, 123456789.0) and as
        /// `d[.ddd]e[+-]x` outside (1e+21, 1e-7, 5e-324). Negative zero is `-0.0`.
        std::string realText(double value) {
            if (std::isnan(value)) return "nan";
            if (std::isinf(value)) return value < 0 ? "-inf" : "inf";
            const bool negative = std::signbit(value);
            const double magnitude = std::fabs(value);

            // The significant digits and the decimal exponent of the shortest round-tripping "%.{p-1}e" text. The text is read digit by
            // digit, so a decimal point other than '.' (a locale) does not matter; strtod reads what snprintf wrote in the same locale.
            std::string digits = "0";
            int exponent = 0;
            if (magnitude != 0.0) {
                char buffer[64];
                for (int precision = 1; precision <= 17; ++precision) {
                    std::snprintf(buffer, sizeof(buffer), "%.*e", precision - 1, magnitude);
                    if (precision == 17 || std::strtod(buffer, nullptr) == magnitude) break;
                }
                digits.clear();
                const char* position = buffer;
                for (; *position != '\0' && *position != 'e' && *position != 'E'; ++position) {
                    if (*position >= '0' && *position <= '9') digits.push_back(*position);
                }
                if (*position != '\0') exponent = std::atoi(position + 1);
                while (digits.size() > 1 && digits.back() == '0') digits.pop_back();
            }

            std::string text = negative ? "-" : "";
            if (magnitude == 0.0 || (exponent >= -5 && exponent <= 20)) {
                if (exponent >= 0) {
                    const std::size_t integerDigits = static_cast<std::size_t>(exponent) + 1;
                    std::string integerPart = digits.substr(0, integerDigits);
                    integerPart.append(integerDigits > integerPart.size() ? integerDigits - integerPart.size() : 0, '0');
                    const std::string fraction = digits.size() > integerDigits ? digits.substr(integerDigits) : "0";
                    text += integerPart + "." + fraction;
                } else {
                    text += "0." + std::string(static_cast<std::size_t>(-exponent - 1), '0') + digits;
                }
            } else {
                text += digits.substr(0, 1);
                if (digits.size() > 1) text += "." + digits.substr(1);
                text += exponent < 0 ? "e-" : "e+";
                text += std::to_string(exponent < 0 ? -exponent : exponent);
            }
            return text;
        }

        std::string quoted(const std::string& value) {
            std::string out = "\"";
            for (const char c : value) {
                switch (c) {
                    case '"': out += "\\\""; break;
                    case '\\': out += "\\\\"; break;
                    case '\n': out += "\\n"; break;
                    case '\r': out += "\\r"; break;
                    case '\t': out += "\\t"; break;
                    default: out.push_back(c); break;
                }
            }
            out.push_back('"');
            return out;
        }

        template <class T>
        std::optional<T> single(const std::vector<Item>& items) {
            if (items.size() != 1) return std::nullopt;
            if (const T* value = std::get_if<T>(&items.front())) return *value;
            return std::nullopt;
        }
    }

    std::string itemToString(const Item& item) {
        struct Visitor {
            std::string operator()(bool value) const { return value ? "true" : "false"; }
            std::string operator()(std::int64_t value) const { return integerText(value); }
            std::string operator()(double value) const { return realText(value); }
            std::string operator()(const std::string& value) const { return quoted(value); }
            std::string operator()(const std::shared_ptr<KerML::Entities::Element>& value) const {
                return value ? "@" + value->elementId() : std::string("@null");
            }
            std::string operator()(Infinity) const { return "*"; }
        };
        return std::visit(Visitor{}, item);
    }

    nlohmann::json itemToJson(const Item& item) {
        struct Visitor {
            nlohmann::json operator()(bool value) const { return value; }
            nlohmann::json operator()(std::int64_t value) const { return value; }
            nlohmann::json operator()(double value) const {
                if (std::isnan(value)) return "NaN";
                if (std::isinf(value)) return value < 0 ? "-Infinity" : "Infinity";
                return value;
            }
            nlohmann::json operator()(const std::string& value) const { return value; }
            nlohmann::json operator()(const std::shared_ptr<KerML::Entities::Element>& value) const {
                nlohmann::json json = nlohmann::json::object();
                json["@id"] = value ? value->elementId() : std::string();
                return json;
            }
            nlohmann::json operator()(Infinity) const { return "*"; }
        };
        return std::visit(Visitor{}, item);
    }

    Value::Value(Item item) { Items.push_back(std::move(item)); }

    Value::Value(std::vector<Item> items) : Items(std::move(items)) {}

    Value Value::null() { return Value(); }
    Value Value::boolean(bool value) { return Value(Item(std::in_place_type<bool>, value)); }
    Value Value::integer(std::int64_t value) { return Value(Item(std::in_place_type<std::int64_t>, value)); }
    Value Value::real(double value) { return Value(Item(std::in_place_type<double>, value)); }
    Value Value::string(std::string value) { return Value(Item(std::in_place_type<std::string>, std::move(value))); }
    Value Value::element(std::shared_ptr<KerML::Entities::Element> value) {
        if (!value) return Value();
        return Value(Item(std::in_place_type<std::shared_ptr<KerML::Entities::Element>>, std::move(value)));
    }
    Value Value::infinity() { return Value(Item(std::in_place_type<Infinity>)); }

    const std::vector<Item>& Value::items() const { return Items; }
    std::size_t Value::size() const { return Items.size(); }
    bool Value::isNull() const { return Items.empty(); }

    std::optional<bool> Value::asBoolean() const { return single<bool>(Items); }
    std::optional<std::int64_t> Value::asInteger() const { return single<std::int64_t>(Items); }
    std::optional<double> Value::asReal() const {
        if (const auto real = single<double>(Items)) return real;
        if (const auto integer = single<std::int64_t>(Items)) return static_cast<double>(*integer);
        return std::nullopt;
    }
    std::optional<std::string> Value::asString() const { return single<std::string>(Items); }
    std::optional<std::shared_ptr<KerML::Entities::Element>> Value::asElement() const {
        return single<std::shared_ptr<KerML::Entities::Element>>(Items);
    }

    std::string Value::toString() const {
        if (Items.empty()) return "null";
        if (Items.size() == 1) return itemToString(Items.front());
        std::string out = "(";
        for (std::size_t index = 0; index < Items.size(); ++index) {
            if (index > 0) out += ", ";
            out += itemToString(Items[index]);
        }
        out.push_back(')');
        return out;
    }

    nlohmann::json Value::toJson() const {
        if (Items.empty()) return nullptr;
        if (Items.size() == 1) return itemToJson(Items.front());
        nlohmann::json array = nlohmann::json::array();
        for (const Item& item : Items) array.push_back(itemToJson(item));
        return array;
    }

    bool Value::operator==(const Value& other) const { return Items == other.Items; }
    bool Value::operator!=(const Value& other) const { return !(*this == other); }
}
