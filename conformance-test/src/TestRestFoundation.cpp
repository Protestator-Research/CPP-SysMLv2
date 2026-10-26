#include <gtest/gtest.h>
#include <chrono>
#include <stdexcept>
#include <string>
#include <nlohmann/json.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include "support/CerrCapture.h"
#include <sysmlv2/rest/Deprecation.h>
#include <sysmlv2/rest/entities/Record.h>
#include <sysmlv2/rest/serialization/Utilities.h>

using namespace SysMLv2::REST;

namespace {
    // Record has a deleted default constructor and a protected deserializer; this exposes what the tests need.
    class TestRecord : public Record {
    public:
        explicit TestRecord(const std::string& text) : Record(text) {}
        TestRecord(boost::uuids::uuid id, std::string name) : Record(id, std::move(name)) {}
    };
}

TEST(RestFoundation, DeprecationWarningIsPrintedOncePerMessage) {
    resetDeprecationWarningsForTesting();
    CerrCapture capture;
    warnDeprecated("old()", "new()");
    warnDeprecated("old()", "new()");
    warnDeprecated("other()", "new()");
    const std::string output = capture.str();
    EXPECT_NE(output.find("[SysMLv2 REST] Deprecated: old() is from an older library version. Use new() instead."), std::string::npos);
    EXPECT_NE(output.find("other()"), std::string::npos);
    EXPECT_EQ(output.find("old()"), output.rfind("old()"));

    resetDeprecationWarningsForTesting();
    CerrCapture second;
    warnDeprecated("old()", "new()");
    EXPECT_FALSE(second.str().empty());
}

TEST(RestFoundation, Iso8601EndsWithZAndStillParsesOldStrings) {
    const auto now = std::chrono::system_clock::now();
    const std::string text = Utilities::toIso8601(now);
    ASSERT_FALSE(text.empty());
    EXPECT_EQ(text.back(), 'Z');
    const auto parsed = Utilities::fromIso8601(text);
    EXPECT_LT(std::chrono::abs(parsed - now), std::chrono::milliseconds(1));
    EXPECT_NO_THROW(Utilities::fromIso8601("2024-03-01T10:20:30.123456"));
    EXPECT_NO_THROW(Utilities::fromIso8601("2024-03-01T10:20:30"));
}

TEST(RestFoundation, RecordAcceptsNullFields) {
    const TestRecord record{R"({"@id":"6d7e1b9c-3f0a-4f4e-8a8f-0f2f7d9a1c11","name":null,"description":null,"alias":null})"};
    EXPECT_EQ(record.getName(), "");
    EXPECT_EQ(record.getDescription(), "");
    EXPECT_TRUE(record.getAlias().empty());
    EXPECT_FALSE(record.getId().is_nil());
}

TEST(RestFoundation, RecordEmptyAliasEntryIsSkippedAndWarned) {
    resetDeprecationWarningsForTesting();
    CerrCapture capture;
    const TestRecord record{R"({"name":"N","alias":["","a"]})"};
    const auto aliases = record.getAlias();
    ASSERT_EQ(aliases.size(), 2u);
    EXPECT_EQ(aliases.front(), "N");
    EXPECT_EQ(aliases.back(), "a");
    EXPECT_NE(capture.str().find("alias"), std::string::npos);
}

TEST(RestFoundation, RecordWithoutIdKeepsNameAndNilId) {
    const TestRecord record{R"({"name":"Request","description":"d"})"};
    EXPECT_EQ(record.getName(), "Request");
    EXPECT_EQ(record.getDescription(), "d");
    EXPECT_TRUE(record.getId().is_nil());
}

TEST(RestFoundation, RecordPlainNameAndMalformedJson) {
    const TestRecord named{std::string("Plain name")};
    EXPECT_EQ(named.getName(), "Plain name");
    EXPECT_FALSE(named.getId().is_nil());
    EXPECT_THROW(TestRecord("{\"name\": "), std::invalid_argument);
    EXPECT_THROW(TestRecord(R"({"name": 5})"), std::invalid_argument);
}

TEST(RestFoundation, RecordResourceIdentifierRoundTrip) {
    TestRecord record{boost::uuids::random_generator()(), "A"};
    auto json = nlohmann::json::parse(record.serializeToJson());
    EXPECT_FALSE(json.contains("resourceIdentifier"));
    record.setResourceIdentifier("https://example.org/a");
    json = nlohmann::json::parse(record.serializeToJson());
    EXPECT_EQ(json["resourceIdentifier"], "https://example.org/a");
}

TEST(RestFoundation, SetNameKeepsNameInAlias) {
    TestRecord record{boost::uuids::random_generator()(), "Old"};
    std::string extra = "Extra";
    record.appendAlias(extra);
    record.setName("New");
    EXPECT_EQ(record.getAlias(), (std::list<std::string>{"New", "Extra"}));
    record.setName("");
    EXPECT_EQ(record.getAlias(), (std::list<std::string>{"Extra"}));
    const TestRecord empty{boost::uuids::random_generator()(), ""};
    EXPECT_TRUE(empty.getAlias().empty());
}

TEST(RestFoundation, Iso8601BeforeEpochHasNonNegativeFraction) {
    const std::chrono::system_clock::time_point t{std::chrono::duration_cast<std::chrono::system_clock::duration>(
        std::chrono::milliseconds(-1500))};
    EXPECT_EQ(Utilities::toIso8601(t), "1969-12-31T23:59:58.500000Z");
}

TEST(RestFoundation, RecordAliasWithoutNameGetsNamePrepended) {
    const TestRecord record{R"({"name":"N","alias":["a","b"]})"};
    EXPECT_EQ(record.getAlias(), (std::list<std::string>{"N", "a", "b"}));
}

TEST(RestFoundation, RecordInvalidIdThrows) {
    EXPECT_THROW(TestRecord(R"({"@id":"not-a-uuid"})"), std::invalid_argument);
    EXPECT_THROW(TestRecord(R"({"@id":5})"), std::invalid_argument);
    EXPECT_THROW(TestRecord(R"({"@type":5})"), std::invalid_argument);
}

TEST(RestFoundation, SetNameToExistingAlias) {
    TestRecord record{boost::uuids::random_generator()(), "Old"};
    std::string extra = "Extra";
    record.appendAlias(extra);
    record.setName("Extra");
    EXPECT_EQ(record.getAlias(), (std::list<std::string>{"Extra"}));
    EXPECT_EQ(record.getName(), "Extra");
}

TEST(RestFoundation, WhitespaceBeforeBraceIsJson) {
    const TestRecord record{std::string("  \n\t{\"name\":\"Json\"}")};
    EXPECT_EQ(record.getName(), "Json");
    EXPECT_TRUE(record.getId().is_nil());
}

TEST(RestFoundation, RecordWithoutIdSerializesWithoutId) {
    const TestRecord record{R"({"name":"Request"})"};
    EXPECT_FALSE(nlohmann::json::parse(const_cast<TestRecord&>(record).serializeToJson()).contains("@id"));
}
