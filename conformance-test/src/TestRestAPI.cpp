//
// Created by Moritz Herzog on 26.11.25.
//

#include <gtest/gtest.h>
#include <sysmlv2/rest/entities/Commit.h>
#include <sysmlv2/rest/entities/Branch.h>
#include <sysmlv2/rest/entities/Project.h>
#include <sysmlv2/rest/entities/JSONEntities.h>
#include <boost/uuid/string_generator.hpp>
#include <nlohmann/json.hpp>
#include <sysmlv2/rest/serialization/Utilities.h>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <ios>
#include <string>

#include <sysmlv2/rest/entities/ProjectRequest.h>


TEST(TestRESTfulAPI, SerializeProject) {
    const auto project = std::make_shared<SysMLv2::REST::Project>("TestProject","Test Project for Conformance Test", "main");
    std::string projectSerialized = project->serializeToJson();

    nlohmann::json json = nlohmann::json::parse(projectSerialized);
    std::string projectId = json[SysMLv2::REST::JSON_ID_ENTITY].get<std::string>();
    ASSERT_EQ(boost::uuids::string_generator()(projectId), project->getId());
    ASSERT_EQ(json[SysMLv2::REST::JSON_TYPE_ENTITY].get<std::string>(), "Project");
    ASSERT_EQ(json[SysMLv2::REST::JSON_DESCRIPTION_ENTITY].get<std::string>(), project->getDescription());
    ASSERT_EQ(json[SysMLv2::REST::JSON_NAME_ENTITY].get<std::string>(), project->getName());
    const auto branch = json[SysMLv2::REST::JSON_DEFAULT_BRANCH_ENTITY];
    ASSERT_EQ(!branch.empty(), true);
}

TEST(TestRESTfulAPI, DeserializeProject) {
    const std::string projectString = "{\"@id\": \"6e701bf8-7793-49de-9b0e-2f43376edabf\",\"@type\": \"Project\",\"defaultBranch\": {\"@id\": \"7eea9bd1-1082-4521-8bb2-d94202c8dd63\"},\"description\": \"Test Project for Conformance Test\",\"name\": \"Hello SysML v2\"}";

    const auto project = std::make_shared<SysMLv2::REST::Project>(projectString);
    ASSERT_EQ(project->getId(), boost::uuids::string_generator()("6e701bf8-7793-49de-9b0e-2f43376edabf"));
    ASSERT_EQ(project->getName(), "Hello SysML v2");
    ASSERT_EQ(project->getDescription(), "Test Project for Conformance Test");
    ASSERT_EQ(project->getDefaultBranch()->getId(), boost::uuids::string_generator()("7eea9bd1-1082-4521-8bb2-d94202c8dd63"));
}

TEST(TestRESTfulAPI, SerializeProjectRequest) {
    const auto projectRequest = std::make_shared<SysMLv2::REST::ProjectRequest>("TestProjectRequest", "Test Project Request", "main");
    std::string projectRequestSerialized = projectRequest->serializeToJson();

    nlohmann::json json = nlohmann::json::parse(projectRequestSerialized);
    ASSERT_EQ(json[SysMLv2::REST::JSON_TYPE_ENTITY].get<std::string>(), "Project");
    ASSERT_FALSE(json.contains(SysMLv2::REST::JSON_ID_ENTITY));
    ASSERT_EQ(json[SysMLv2::REST::JSON_NAME_ENTITY].get<std::string>(), projectRequest->name());
    ASSERT_EQ(json[SysMLv2::REST::JSON_DESCRIPTION_ENTITY].get<std::string>(), projectRequest->description());
    ASSERT_EQ(json[SysMLv2::REST::JSON_DEFAULT_BRANCH_ENTITY].get<std::string>(), projectRequest->defaultBranch());

}

TEST(TestRESTfulAPI, DeserializeProjectRequest) {
    std::string serializedProjectRequest = "{\"@type\": \"Project\", \"defaultBranch\": \"main\", \"description\": \"Test Project Request\",\"name\": \"TestProjectRequest\"}";

    const auto projectRequest = std::make_shared<SysMLv2::REST::ProjectRequest>(serializedProjectRequest);

    nlohmann::json json = nlohmann::json::parse(serializedProjectRequest);
    ASSERT_EQ(projectRequest->name(), json[SysMLv2::REST::JSON_NAME_ENTITY].get<std::string>());
    ASSERT_EQ(projectRequest->description(), json[SysMLv2::REST::JSON_DESCRIPTION_ENTITY].get<std::string>());
    ASSERT_EQ(projectRequest->defaultBranch(), json[SysMLv2::REST::JSON_DEFAULT_BRANCH_ENTITY].get<std::string>());
}

// ---------------------------------------------------------------------------
// Regression tests: Utilities::fromIso8601 (typo __GNUC___ selected a broken local-time fallback on GCC)
// ---------------------------------------------------------------------------
namespace {
    using SysClock = std::chrono::system_clock;

    // Independently computed expected value (not via fromIso8601).
    template <typename Duration>
    SysClock::time_point utc20250313(Duration timeOfDay) {
        using namespace std::chrono;
        using namespace std::chrono_literals;
        return time_point_cast<SysClock::duration>(
                sys_days{std::chrono::year{2025} / std::chrono::March / 13} + timeOfDay);
    }

    // The MSVC runtime does not understand IANA names, it expects the POSIX form "std offset dst".
#if defined(_WIN32)
    constexpr const char* BERLIN_TIME_ZONE = "CET-1CEST";
#else
    constexpr const char* BERLIN_TIME_ZONE = "Europe/Berlin";
#endif

    // Portable wrappers: setenv/unsetenv/tzset are POSIX and not available in the MSVC runtime.
    void setTimeZoneVariable(const char* value) {
#if defined(_WIN32)
        _putenv_s("TZ", value);
#else
        setenv("TZ", value, 1);
#endif
    }

    void unsetTimeZoneVariable() {
#if defined(_WIN32)
        // An empty value removes the variable from the environment of the process.
        _putenv_s("TZ", "");
#else
        unsetenv("TZ");
#endif
    }

    void applyTimeZone() {
#if defined(_WIN32)
        _tzset();
#else
        tzset();
#endif
    }

    // Sets TZ for the lifetime of the object and restores the previous value afterwards.
    class ScopedTimeZone {
    public:
        explicit ScopedTimeZone(const char* tz) {
            const char* old = std::getenv("TZ");
            if (old) { _had = true; _old = old; }
            setTimeZoneVariable(tz);
            applyTimeZone();
        }
        ~ScopedTimeZone() {
            if (_had) setTimeZoneVariable(_old.c_str()); else unsetTimeZoneVariable();
            applyTimeZone();
        }
    private:
        bool _had = false;
        std::string _old;
    };
}

TEST(TestIso8601, ParsesUtcMidnight) {
    EXPECT_EQ(SysMLv2::REST::Utilities::fromIso8601("2025-03-13T00:00:00Z"),
              utc20250313(std::chrono::hours{0}));
}

TEST(TestIso8601, ParsesUtcTimeOfDay) {
    EXPECT_EQ(SysMLv2::REST::Utilities::fromIso8601("2025-03-13T14:25:36Z"),
              utc20250313(std::chrono::hours{14} + std::chrono::minutes{25} + std::chrono::seconds{36}));
}

TEST(TestIso8601, UtcIsIndependentOfLocalTimeZone) {
    ScopedTimeZone tz(BERLIN_TIME_ZONE);
    EXPECT_EQ(SysMLv2::REST::Utilities::fromIso8601("2025-03-13T00:00:00Z"),
              utc20250313(std::chrono::hours{0}));
    EXPECT_EQ(SysMLv2::REST::Utilities::fromIso8601("2025-03-13T12:30:00Z"),
              utc20250313(std::chrono::hours{12} + std::chrono::minutes{30}));
}

TEST(TestIso8601, PreservesMilliseconds) {
    EXPECT_EQ(SysMLv2::REST::Utilities::fromIso8601("2025-03-13T00:00:00.123Z"),
              utc20250313(std::chrono::milliseconds{123}));
}

TEST(TestIso8601, PreservesMicroseconds) {
    EXPECT_EQ(SysMLv2::REST::Utilities::fromIso8601("2025-03-13T00:00:00.123456Z"),
              utc20250313(std::chrono::microseconds{123456}));
}

TEST(TestIso8601, AppliesPositiveOffset) {
    const auto parsed = SysMLv2::REST::Utilities::fromIso8601("2025-03-13T02:00:00+02:00");
    EXPECT_EQ(parsed, utc20250313(std::chrono::hours{0}));
    EXPECT_EQ(parsed, SysMLv2::REST::Utilities::fromIso8601("2025-03-13T00:00:00Z"));
}

TEST(TestIso8601, AppliesNegativeOffset) {
    EXPECT_EQ(SysMLv2::REST::Utilities::fromIso8601("2025-03-12T19:00:00-05:00"),
              utc20250313(std::chrono::hours{0}));
}

TEST(TestIso8601, RoundTripKeepsMicrosecondPrecision) {
    const auto tp = utc20250313(std::chrono::hours{9} + std::chrono::minutes{8} +
                                std::chrono::seconds{7} + std::chrono::microseconds{654321});
    EXPECT_EQ(SysMLv2::REST::Utilities::fromIso8601(SysMLv2::REST::Utilities::toIso8601(tp)), tp);
}

TEST(TestIso8601, RoundTripIndependentOfLocalTimeZone) {
    ScopedTimeZone tz(BERLIN_TIME_ZONE);
    const auto tp = utc20250313(std::chrono::hours{9} + std::chrono::microseconds{654321});
    EXPECT_EQ(SysMLv2::REST::Utilities::fromIso8601(SysMLv2::REST::Utilities::toIso8601(tp)), tp);
}

TEST(TestIso8601, InvalidStringThrows) {
    EXPECT_THROW(SysMLv2::REST::Utilities::fromIso8601("not a date"), std::ios_base::failure);
    EXPECT_THROW(SysMLv2::REST::Utilities::fromIso8601(""), std::ios_base::failure);
}

TEST(TestRESTfulAPI, CommitGetCreatedParsesTimestampAsUtc) {
    const std::string json =
            "{\"@id\": \"6f9619ff-8b86-d011-b42d-00c04fc964ff\", \"@type\": \"Commit\", "
            "\"description\": \"c\", \"timestamp\": \"2025-03-13T00:00:00.123456Z\"}";
    const SysMLv2::REST::Commit commit(json);
    EXPECT_EQ(commit.getCreated(), utc20250313(std::chrono::microseconds{123456}));
}

TEST(TestRESTfulAPI, CommitGetCreatedIndependentOfLocalTimeZone) {
    ScopedTimeZone tz(BERLIN_TIME_ZONE);
    const std::string json =
            "{\"@id\": \"6f9619ff-8b86-d011-b42d-00c04fc964ff\", \"@type\": \"Commit\", "
            "\"description\": \"c\", \"timestamp\": \"2025-03-13T10:00:00Z\"}";
    const SysMLv2::REST::Commit commit(json);
    EXPECT_EQ(commit.getCreated(), utc20250313(std::chrono::hours{10}));
}

TEST(TestRESTfulAPI, CommitGetCreatedWithoutDescription) {
    const std::string json =
            "{\"@id\": \"6f9619ff-8b86-d011-b42d-00c04fc964ff\", \"@type\": \"Commit\", "
            "\"timestamp\": \"2025-03-13T00:00:00Z\"}";
    const SysMLv2::REST::Commit commit(json);
    EXPECT_EQ(commit.getCreated(), utc20250313(std::chrono::seconds{0}));
}

TEST(TestRESTfulAPI, CommitWithoutTimestampDoesNotThrow) {
    const std::string json =
            "{\"@id\": \"6f9619ff-8b86-d011-b42d-00c04fc964ff\", \"@type\": \"Commit\", "
            "\"description\": \"c\"}";
    EXPECT_NO_THROW(SysMLv2::REST::Commit commit(json));
}
