#include "TestSupport.h"

#include <kerml/kernel/packages/Package.h>

#include <clocale>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <locale>

using namespace TestSupport;

TEST(Value, NullIsTheEmptySequence) {
    const Value null;
    EXPECT_TRUE(null.isNull());
    EXPECT_EQ(null.size(), 0u);
    EXPECT_EQ(null, Value::null());
    EXPECT_EQ(null, Value(std::vector<Item>{}));
    EXPECT_FALSE(null.asBoolean());
    EXPECT_FALSE(null.asInteger());
    EXPECT_FALSE(null.asReal());
    EXPECT_FALSE(null.asString());
    EXPECT_FALSE(null.asElement());
}

TEST(Value, SingleItemAccessors) {
    EXPECT_EQ(B(true).asBoolean(), std::optional<bool>(true));
    EXPECT_FALSE(B(true).asInteger());
    EXPECT_EQ(I(7).asInteger(), std::optional<std::int64_t>(7));
    EXPECT_EQ(I(7).asReal(), std::optional<double>(7.0));   // (an Integer is promoted)
    EXPECT_EQ(R(2.5).asReal(), std::optional<double>(2.5));
    EXPECT_FALSE(R(2.5).asInteger());
    EXPECT_EQ(S("x").asString(), std::optional<std::string>("x"));
    EXPECT_FALSE(S("x").asReal());
    EXPECT_FALSE(Inf().asReal());
    EXPECT_FALSE(Inf().isNull());

    const auto element = std::make_shared<KerML::Entities::Package>();
    ASSERT_TRUE(Value::element(element).asElement());
    EXPECT_EQ(*Value::element(element).asElement(), element);
    EXPECT_FALSE(I(1).asElement());
}

TEST(Value, SequencesHaveNoSingleItemAccess) {
    const Value sequence = Seq({1, 2});
    EXPECT_EQ(sequence.size(), 2u);
    EXPECT_FALSE(sequence.isNull());
    EXPECT_FALSE(sequence.asInteger());
    EXPECT_FALSE(sequence.asReal());
    ASSERT_EQ(sequence.items().size(), 2u);
    EXPECT_EQ(std::get<std::int64_t>(sequence.items()[1]), 2);
}

TEST(Value, EqualityIsStructural) {
    EXPECT_EQ(I(1), I(1));
    EXPECT_NE(I(1), I(2));
    EXPECT_NE(I(2), R(2.0));   // (the function `==` compares numerically, the Value does not)
    EXPECT_NE(I(1), B(true));
    EXPECT_EQ(Seq({1, 2}), Seq({1, 2}));
    EXPECT_NE(Seq({1, 2}), Seq({2, 1}));
    EXPECT_NE(Seq({1}), Seq({1, 1}));
    EXPECT_EQ(Inf(), Inf());
    EXPECT_NE(Inf(), I(1));
    const auto a = std::make_shared<KerML::Entities::Package>();
    const auto b = std::make_shared<KerML::Entities::Package>();
    EXPECT_EQ(Value::element(a), Value::element(a));
    EXPECT_NE(Value::element(a), Value::element(b));   // (identity)
}

TEST(Value, KeepsElementsAlive) {
    std::weak_ptr<KerML::Entities::Element> weak;
    Value value;
    {
        auto element = std::make_shared<KerML::Entities::Package>();
        weak = element;
        value = Value::element(element);
    }
    EXPECT_FALSE(weak.expired());
    value = Value();
    EXPECT_TRUE(weak.expired());
}

TEST(Value, ToStringOfScalars) {
    EXPECT_EQ(N().toString(), "null");
    EXPECT_EQ(B(true).toString(), "true");
    EXPECT_EQ(B(false).toString(), "false");
    EXPECT_EQ(I(-42).toString(), "-42");
    EXPECT_EQ(I(Min).toString(), "-9223372036854775808");
    EXPECT_EQ(S("a\"b\\c\n").toString(), "\"a\\\"b\\\\c\\n\"");
    EXPECT_EQ(Inf().toString(), "*");
    EXPECT_EQ(Seq({1, 2, 3}).toString(), "(1, 2, 3)");
}

TEST(Value, ToStringOfReals) {
    // One fixed format: plain decimal with a decimal point for 1e-5 <= |x| < 1e21, else d[.ddd]e[+-]x.
    EXPECT_EQ(R(2.0).toString(), "2.0");
    EXPECT_NE(R(2.0).toString(), I(2).toString());   // (the Real 2.0 differs from the Integer 2)
    EXPECT_EQ(R(100.0).toString(), "100.0");
    EXPECT_EQ(R(120.0).toString(), "120.0");
    EXPECT_EQ(R(123456789.0).toString(), "123456789.0");
    EXPECT_EQ(R(123456789.125).toString(), "123456789.125");
    EXPECT_EQ(R(0.1).toString(), "0.1");
    EXPECT_EQ(R(-1.5).toString(), "-1.5");
    EXPECT_EQ(R(0.00001).toString(), "0.00001");
    EXPECT_EQ(R(0.000123).toString(), "0.000123");
    EXPECT_EQ(R(1e-7).toString(), "1e-7");
    EXPECT_EQ(R(1.5e-7).toString(), "1.5e-7");
    EXPECT_EQ(R(1e20).toString(), "100000000000000000000.0");
    EXPECT_EQ(R(1e21).toString(), "1e+21");
    EXPECT_EQ(R(1.25e22).toString(), "1.25e+22");
    EXPECT_EQ(R(5e-324).toString(), "5e-324");
    EXPECT_EQ(R(std::numeric_limits<double>::max()).toString(), "1.7976931348623157e+308");
    EXPECT_EQ(R(-0.0).toString(), "-0.0");
    EXPECT_EQ(R(0.0).toString(), "0.0");
    EXPECT_EQ(R(std::numeric_limits<double>::infinity()).toString(), "inf");
    EXPECT_EQ(R(-std::numeric_limits<double>::infinity()).toString(), "-inf");
    EXPECT_EQ(R(std::nan("")).toString(), "nan");
    // Round trip: the text reads back as the same double.
    std::uint64_t state = 0x9E3779B97F4A7C15ull;
    std::vector<double> values = {0.1, 1.0 / 3.0, 1e-300, 123456789.123456789, 5e-324, 1.7976931348623157e308, 2.0, -0.0, 100.0, 1e21, 1e-7};
    for (int index = 0; index < 2000; ++index) {
        state = state * 6364136223846793005ull + 1442695040888963407ull;
        double value = 0.0;
        const std::uint64_t bits = state ^ (state >> 29);
        std::memcpy(&value, &bits, sizeof(value));
        if (std::isfinite(value)) values.push_back(value);
        values.push_back(static_cast<double>(state >> 11) / 9007199254740992.0 * 1000.0);   // (random-looking values in [0, 1000))
    }
    for (const double value : values) {
        const std::string text = R(value).toString();
        EXPECT_EQ(std::strtod(text.c_str(), nullptr), value) << text;
        EXPECT_NE(text.find_first_of(".e"), std::string::npos) << text;
        // (shortest: one digit fewer does not round-trip is not asserted, but 17 significant digits is the maximum)
    }
}

TEST(Value, ElementOfNullptrIsNull) {
    EXPECT_TRUE(Value::element(nullptr).isNull());
    EXPECT_EQ(Value::element(nullptr), Value());
    EXPECT_FALSE(Value::element(nullptr).asElement());
}

TEST(Value, ToJson) {
    EXPECT_TRUE(N().toJson().is_null());
    EXPECT_EQ(B(true).toJson(), nlohmann::json(true));
    EXPECT_EQ(I(5).toJson(), nlohmann::json(5));
    EXPECT_TRUE(I(5).toJson().is_number_integer());
    EXPECT_TRUE(R(2.0).toJson().is_number_float());   // (the Real 2.0 stays a floating point number)
    EXPECT_EQ(R(2.5).toJson(), nlohmann::json(2.5));
    EXPECT_EQ(R(std::nan("")).toJson(), nlohmann::json("NaN"));
    EXPECT_EQ(R(std::numeric_limits<double>::infinity()).toJson(), nlohmann::json("Infinity"));
    EXPECT_EQ(S("x").toJson(), nlohmann::json("x"));
    EXPECT_EQ(Inf().toJson(), nlohmann::json("*"));
    EXPECT_EQ(Seq({1, 2}).toJson(), nlohmann::json::parse("[1,2]"));

    const auto element = std::make_shared<KerML::Entities::Package>();
    const nlohmann::json json = Value::element(element).toJson();
    ASSERT_TRUE(json.is_object());
    EXPECT_EQ(json.at("@id"), element->elementId());
    EXPECT_EQ(Value(Item(element)).toString(), "@" + element->elementId());

    // A sequence of one element is the element itself, mixed sequences are arrays.
    const Value mixed(std::vector<Item>{Item(std::in_place_type<std::int64_t>, 1), Item(std::in_place_type<std::string>, "a"), Item(element)});
    ASSERT_TRUE(mixed.toJson().is_array());
    EXPECT_EQ(mixed.toJson().size(), 3u);
    EXPECT_EQ(mixed.toJson()[2].at("@id"), element->elementId());
}

TEST(Value, TextIsIndependentOfTheGlobalLocale) {
    const char* const candidates[] = {"de_DE.UTF-8", "de_DE.utf8", "de_DE", "fr_FR.UTF-8", "fr_FR.utf8"};
    std::string previousC = std::setlocale(LC_ALL, nullptr);
    const std::locale previousCpp = std::locale::global(std::locale::classic());
    bool found = false;
    for (const char* name : candidates) {
        if (std::setlocale(LC_ALL, name) == nullptr) continue;
        // (a comma decimal point is what the check is about)
        if (std::string(std::localeconv()->decimal_point) != ",") continue;
        found = true;
        try {
            std::locale::global(std::locale(name));
        } catch (const std::exception&) {
            // (only the C locale is switched)
        }
        break;
    }
    if (found) {
        EXPECT_EQ(R(0.1).toString(), "0.1");
        EXPECT_EQ(R(1234567.5).toString(), "1234567.5");
        EXPECT_EQ(R(2.0).toString(), "2.0");
        EXPECT_EQ(R(100.0).toString(), "100.0");
        EXPECT_EQ(R(1e-7).toString(), "1e-7");
        EXPECT_EQ(R(123456.789).toString(), "123456.789");
        EXPECT_EQ(I(1234567).toString(), "1234567");
        EXPECT_EQ(Seq({1000, 2}).toString(), "(1000, 2)");
        EXPECT_EQ(R(1.25).toJson().dump(), "1.25");
    }
    std::setlocale(LC_ALL, previousC.c_str());
    std::locale::global(previousCpp);
    if (!found) GTEST_SKIP() << "no locale with a comma decimal point is installed";
}
