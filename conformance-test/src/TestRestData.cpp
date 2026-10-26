//
// Tests of the data entities of the REST API (AP 2): DataIdentity, DataVersion, DataDifference, MergeResult, ProjectUsage,
// ExternalData, ExternalRelationship and the change list of CommitRequest. Contains the Annex B commit change entry, round
// trips and the compatibility tests of the deprecated APIs and JSON formats.
//

#include <gtest/gtest.h>
#include <memory>
#include <stdexcept>
#include <string>
#include <nlohmann/json.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <kerml/kernel/packages/Package.h>
#include "support/CerrCapture.h"
#include <sysmlv2/rest/Deprecation.h>
#include <sysmlv2/rest/entities/Branch.h>
#include <sysmlv2/rest/entities/ChangeType.h>
#include <sysmlv2/rest/entities/Commit.h>
#include <sysmlv2/rest/entities/CommitRequest.h>
#include <sysmlv2/rest/entities/Data.h>
#include <sysmlv2/rest/entities/DataDifference.h>
#include <sysmlv2/rest/entities/DataIdentity.h>
#include <sysmlv2/rest/entities/DataVersion.h>
#include <sysmlv2/rest/entities/ExternalData.h>
#include <sysmlv2/rest/entities/ExternalRelationship.h>
#include <sysmlv2/rest/entities/MergeResult.h>
#include <sysmlv2/rest/entities/Project.h>
#include <sysmlv2/rest/entities/ProjectUsage.h>
#include <sysmlv2/service/implementation/ElementNavigationService.h>
#include <sysmlv2/service/implementation/ProjectVersioningService.h>

using namespace SysMLv2::REST;
using nlohmann::json;

namespace {
    const std::string ProjectId = "6e701bf8-7793-49de-9b0e-2f43376edabf";
    const std::string CommitId = "c4fc0b1e-2d3a-4b5c-8d6e-7f8091a2b3c4";
    const std::string OtherCommitId = "0f1e2d3c-4b5a-4968-8776-655443322110";
    const std::string DataId = "11111111-2222-4333-8444-555555555555";
    const std::string VersionId = "aaaaaaaa-bbbb-4ccc-8ddd-eeeeeeeeeeee";
    const std::string OtherDataId = "99999999-8888-4777-8666-555555555555";

    std::size_t countWarnings(const std::string& output) {
        std::size_t count = 0;
        for (auto pos = output.find("Deprecated:"); pos != std::string::npos; pos = output.find("Deprecated:", pos + 1))
            ++count;
        return count;
    }

    json reference(const std::string& id) {
        return json{{"@id", id}};
    }

    boost::uuids::uuid uuidOf(const std::string& id) {
        return boost::uuids::string_generator()(id);
    }

    std::shared_ptr<KerML::Entities::Package> makePackage(const std::string& name) {
        auto package = std::make_shared<KerML::Entities::Package>();
        package->setDeclaredName(name);
        return package;
    }

    class RestData : public ::testing::Test {
    protected:
        void SetUp() override { resetDeprecationWarningsForTesting(); }
    };
}

// ---------------------------------------------------------------------------------------------------------------------------
// DataIdentity
// ---------------------------------------------------------------------------------------------------------------------------

TEST_F(RestData, DataIdentityMinimalJson) {
    CerrCapture capture;
    DataIdentity identity(json{{"@id", DataId}, {"@type", "DataIdentity"}}.dump());
    EXPECT_EQ(identity.getId(), uuidOf(DataId));
    EXPECT_EQ(identity.getType(), "DataIdentity");
    EXPECT_EQ(identity.getCreatedAt(), nullptr);
    EXPECT_EQ(identity.getDeletedAt(), nullptr);
    EXPECT_TRUE(identity.getDataVersions().empty());
    EXPECT_EQ(countWarnings(capture.str()), 0u);

    const json written = json::parse(identity.serializeToJson());
    EXPECT_EQ(written, (json{{"@id", DataId}, {"@type", "DataIdentity"}}));
}

TEST_F(RestData, DataIdentityWritesCommitReferences) {
    CerrCapture capture;
    DataIdentity identity(uuidOf(DataId));
    identity.setCreatedAt(std::make_shared<Commit>(json{{"@id", CommitId}}.dump()));
    identity.setDeletedAt(std::make_shared<Commit>(json{{"@id", OtherCommitId}}.dump()));
    const json written = json::parse(identity.serializeToJson());
    EXPECT_EQ(written["createdAt"], reference(CommitId));
    EXPECT_EQ(written["deletedAt"], reference(OtherCommitId));
    EXPECT_FALSE(written.contains("dataVersions"));
    EXPECT_FALSE(written.contains("created"));
    EXPECT_FALSE(written.contains("deleted"));

    DataIdentity read(written.dump());
    ASSERT_NE(read.getCreatedAt(), nullptr);
    EXPECT_EQ(read.getCreatedAt()->getId(), uuidOf(CommitId));
    ASSERT_NE(read.getDeletedAt(), nullptr);
    EXPECT_EQ(read.getDeletedAt()->getId(), uuidOf(OtherCommitId));
    EXPECT_EQ(countWarnings(capture.str()), 0u);
}

TEST_F(RestData, DataIdentityNameAndInvalidJson) {
    DataIdentity named("some name");
    EXPECT_EQ(named.getName(), "some name");
    try {
        DataIdentity broken("{not json");
        FAIL() << "expected an exception";
    } catch (const std::invalid_argument& ex) {
        EXPECT_NE(std::string(ex.what()).find("DataIdentity"), std::string::npos);
    }
    EXPECT_THROW(DataIdentity(json{{"@id", "no-uuid"}}.dump()), std::invalid_argument);
}

TEST_F(RestData, DataIdentityOldCreatedDeletedWarnOnce) {
    CerrCapture capture;
    DataIdentity identity(json{{"@id", DataId}, {"@type", "DataIdentity"}, {"created", "2025-03-13T10:00:00"},
                               {"deleted", "2025-03-14T10:00:00"}}.dump());
    // one message per field
    EXPECT_EQ(countWarnings(capture.str()), 2u);
    EXPECT_NE(capture.str().find("\"created\""), std::string::npos);
    EXPECT_NE(capture.str().find("\"deleted\""), std::string::npos);
    EXPECT_LT(identity.createdAt(), identity.deletedAt());
    EXPECT_EQ(identity.getCreatedAt(), nullptr);
}

TEST_F(RestData, DataIdentityOldDataVersionsWarnOnce) {
    CerrCapture capture;
    // The old format: the DataVersion has the id of its payload and no identity.
    const auto package = makePackage("Old");
    const json oldVersion = {{"@id", boost::uuids::to_string(package->getId())}, {"@type", "DataVersion"},
                             {"payload", json::parse(package->serializeToJson())}};
    DataIdentity identity(json{{"@id", boost::uuids::to_string(package->getId())}, {"@type", "DataIdentity"},
                               {"dataVersions", json::array({oldVersion})}}.dump());
    ASSERT_EQ(identity.getDataVersions().size(), 1u);
    EXPECT_EQ(identity.getDataVersions()[0]->getId(), package->getId());
    const auto output = capture.str();
    // "dataVersions" and the DataVersion without identity: one message each
    EXPECT_EQ(countWarnings(output), 2u);
    EXPECT_NE(output.find("\"dataVersions\""), std::string::npos);
}

TEST_F(RestData, DataIdentityTimesWithoutLegacyFieldsAreEpoch) {
    DataIdentity identity(uuidOf(DataId));
    EXPECT_EQ(identity.createdAt(), std::chrono::system_clock::time_point{});
    EXPECT_EQ(identity.deletedAt(), std::chrono::system_clock::time_point{});
}

// ---------------------------------------------------------------------------------------------------------------------------
// DataVersion
// ---------------------------------------------------------------------------------------------------------------------------

TEST_F(RestData, DataVersionCreate) {
    CerrCapture capture;
    const auto package = makePackage("Created");
    DataVersion version(package);
    EXPECT_FALSE(version.getVersionId().is_nil());
    EXPECT_NE(version.getVersionId(), package->getId());
    ASSERT_NE(version.getIdentity(), nullptr);
    EXPECT_EQ(version.getIdentity()->getId(), package->getId());
    EXPECT_EQ(version.getId(), package->getId());
    EXPECT_EQ(version.getPayload(), package);
    EXPECT_EQ(version.getCommit(), nullptr);

    const json request = json::parse(version.serializeAsRequest());
    EXPECT_FALSE(request.contains("@id"));
    EXPECT_FALSE(request.contains("identity"));
    EXPECT_EQ(request["@type"], "DataVersion");
    EXPECT_EQ(request["payload"]["@id"], boost::uuids::to_string(package->getId()));

    const json full = json::parse(version.serializeToJson());
    EXPECT_EQ(full["@id"], boost::uuids::to_string(version.getVersionId()));
    EXPECT_EQ(full["@type"], "DataVersion");
    EXPECT_EQ(full["identity"], (json{{"@id", boost::uuids::to_string(package->getId())}, {"@type", "DataIdentity"}}));
    EXPECT_FALSE(full.contains("commit"));
    EXPECT_EQ(countWarnings(capture.str()), 0u);
}

TEST_F(RestData, DataVersionIdsAreRandomAndCustomizable) {
    const auto package = makePackage("Ids");
    DataVersion first(package);
    DataVersion second(package);
    EXPECT_NE(first.getVersionId(), second.getVersionId());
    DataVersion given(package, nullptr, uuidOf(VersionId));
    EXPECT_EQ(given.getVersionId(), uuidOf(VersionId));
}

TEST_F(RestData, DataVersionUpdate) {
    CerrCapture capture;
    const auto package = makePackage("Updated");
    auto identity = std::make_shared<DataIdentity>(package->getId());
    DataVersion version(package, identity);
    EXPECT_EQ(version.getIdentity(), identity);

    const json request = json::parse(version.serializeAsRequest());
    EXPECT_FALSE(request.contains("@id"));
    EXPECT_EQ(request["identity"], reference(boost::uuids::to_string(package->getId())));
    EXPECT_TRUE(request["payload"].is_object());
    EXPECT_EQ(countWarnings(capture.str()), 0u);
}

TEST_F(RestData, DataVersionDeleteRoundTrip) {
    CerrCapture capture;
    DataVersion version(nullptr, std::make_shared<DataIdentity>(uuidOf(DataId)));
    EXPECT_EQ(version.getPayload(), nullptr);
    EXPECT_EQ(version.getId(), uuidOf(DataId));

    const json request = json::parse(version.serializeAsRequest());
    EXPECT_EQ(request["identity"], reference(DataId));
    EXPECT_TRUE(request["payload"].is_null());
    EXPECT_TRUE(request.contains("payload"));

    const json full = json::parse(version.serializeToJson());
    EXPECT_TRUE(full["payload"].is_null());
    DataVersion read(full.dump());
    EXPECT_EQ(read.getPayload(), nullptr);
    EXPECT_EQ(read.getId(), uuidOf(DataId));
    EXPECT_EQ(read.getVersionId(), version.getVersionId());
    ASSERT_NE(read.getIdentity(), nullptr);
    EXPECT_EQ(read.getIdentity()->getId(), uuidOf(DataId));

    DataVersion fromRequest(request.dump());
    EXPECT_EQ(fromRequest.getPayload(), nullptr);
    EXPECT_EQ(fromRequest.getId(), uuidOf(DataId));
    EXPECT_TRUE(fromRequest.getVersionId().is_nil());
    EXPECT_EQ(countWarnings(capture.str()), 0u);
}

TEST_F(RestData, DataVersionWithoutPayloadAndIdentityThrows) {
    EXPECT_THROW(DataVersion(std::shared_ptr<Data>(), nullptr), std::invalid_argument);
    EXPECT_THROW(DataVersion(json{{"@id", VersionId}}.dump()), std::invalid_argument);
    EXPECT_THROW(DataVersion(json{{"@id", VersionId}, {"payload", nullptr}}.dump()), std::invalid_argument);
}

TEST_F(RestData, DataVersionAnnexBChangeEntry) {
    CerrCapture capture;
    const json entry = {{"@id", VersionId}, {"identity", {{"@id", DataId}, {"@type", "DataIdentity"}}}, {"payload", nullptr}};
    DataVersion version(entry.dump());
    EXPECT_EQ(version.getVersionId(), uuidOf(VersionId));
    EXPECT_EQ(version.getId(), uuidOf(DataId));
    EXPECT_EQ(version.getPayload(), nullptr);
    EXPECT_EQ(json::parse(version.serializeToJson()),
              (json{{"@id", VersionId}, {"@type", "DataVersion"}, {"identity", {{"@id", DataId}, {"@type", "DataIdentity"}}},
                    {"payload", nullptr}}));
    EXPECT_EQ(countWarnings(capture.str()), 0u);
}

TEST_F(RestData, DataVersionFullRoundTripWithCommit) {
    CerrCapture capture;
    const auto package = makePackage("Round trip");
    DataVersion version(package);
    version.setCommit(std::make_shared<Commit>(json{{"@id", CommitId}}.dump()));
    const std::string text = version.serializeToJson();
    EXPECT_EQ(json::parse(text)["commit"], reference(CommitId));

    DataVersion read(text);
    EXPECT_EQ(read.getVersionId(), version.getVersionId());
    EXPECT_EQ(read.getId(), package->getId());
    ASSERT_NE(read.getPayload(), nullptr);
    EXPECT_EQ(read.getPayload()->getType(), "Package");
    ASSERT_NE(read.getCommit(), nullptr);
    EXPECT_EQ(read.getCommit()->getId(), uuidOf(CommitId));
    EXPECT_EQ(countWarnings(capture.str()), 0u);
}

TEST_F(RestData, DataVersionRequestWithoutIdentityIsCreation) {
    CerrCapture capture;
    const auto package = makePackage("Request");
    const json request = {{"@type", "DataVersion"}, {"payload", json::parse(package->serializeToJson())}};
    DataVersion version(request.dump());
    EXPECT_EQ(version.getId(), package->getId());
    // still a creation: no identity is written
    EXPECT_FALSE(json::parse(version.serializeAsRequest()).contains("identity"));
    EXPECT_EQ(countWarnings(capture.str()), 0u);
}

TEST_F(RestData, DataVersionSetPayloadFollowsDerivedIdentity) {
    DataVersion version(makePackage("A"));
    const auto other = makePackage("B");
    version.setPayload(other);
    EXPECT_EQ(version.getId(), other->getId());
    version.setPayload(nullptr);
    // the identity stays for the deletion
    EXPECT_EQ(version.getId(), other->getId());
}

TEST_F(RestData, DataVersionInvalidJson) {
    try {
        DataVersion broken("{not json");
        FAIL() << "expected an exception";
    } catch (const std::invalid_argument& ex) {
        EXPECT_NE(std::string(ex.what()).find("DataVersion"), std::string::npos);
    }
    EXPECT_THROW(DataVersion("no json"), std::invalid_argument);
    EXPECT_THROW(DataVersion(json{{"identity", "x"}, {"payload", nullptr}}.dump()), std::invalid_argument);
    EXPECT_THROW(DataVersion(json{{"identity", reference(DataId)}, {"payload", 5}}.dump()), std::invalid_argument);
}

TEST_F(RestData, DataVersionOldFormatWithoutIdentityWarnsOnce) {
    CerrCapture capture;
    const auto package = makePackage("Old format");
    const std::string packageId = boost::uuids::to_string(package->getId());
    const json old = {{"@id", packageId}, {"@type", "DataVersion"}, {"payload", json::parse(package->serializeToJson())}};
    DataVersion version(old.dump());
    EXPECT_EQ(version.getId(), package->getId());
    ASSERT_NE(version.getIdentity(), nullptr);
    EXPECT_EQ(version.getIdentity()->getId(), package->getId());
    EXPECT_EQ(countWarnings(capture.str()), 1u);
}

#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable : 4996)
#else
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif

TEST_F(RestData, DeprecatedDataVersionConstructorWithPayload) {
    CerrCapture capture;
    const auto package = makePackage("Old constructor");
    DataVersion version(uuidOf(VersionId), package);
    EXPECT_EQ(countWarnings(capture.str()), 1u);
    EXPECT_NE(capture.str().find("DataVersion(uuid, payload)"), std::string::npos);
    // the uuid was ignored for a payload
    EXPECT_EQ(version.getId(), package->getId());
    EXPECT_EQ(version.getIdentity()->getId(), package->getId());
    EXPECT_NE(version.getVersionId(), uuidOf(VersionId));
    EXPECT_FALSE(json::parse(version.serializeAsRequest()).contains("identity"));

    // once per process
    DataVersion again(uuidOf(VersionId), package);
    EXPECT_EQ(countWarnings(capture.str()), 1u);
}

TEST_F(RestData, DeprecatedDataVersionConstructorDeletionDoesNotCrash) {
    CerrCapture capture;
    DataVersion version(uuidOf(DataId), nullptr);
    EXPECT_EQ(countWarnings(capture.str()), 1u);
    EXPECT_EQ(version.getPayload(), nullptr);
    EXPECT_EQ(version.getId(), uuidOf(DataId));
    EXPECT_EQ(json::parse(version.serializeAsRequest())["identity"], reference(DataId));
    EXPECT_NO_THROW(version.serializeToJson());
}

TEST_F(RestData, DeprecatedDataVersionDefaultConstructorDoesNotCrash) {
    CerrCapture capture;
    DataVersion version;
    EXPECT_EQ(countWarnings(capture.str()), 1u);
    EXPECT_EQ(version.getPayload(), nullptr);
    EXPECT_FALSE(version.getId().is_nil());
}

TEST_F(RestData, DeprecatedDataDifferenceComparedData) {
    CerrCapture capture;
    auto compare = std::make_shared<DataVersion>(makePackage("c"));
    DataDifference difference(nullptr, compare);
    EXPECT_EQ(difference.comparedData(), compare);
    EXPECT_EQ(countWarnings(capture.str()), 1u);
    EXPECT_EQ(difference.comparedData(), compare);
    EXPECT_EQ(countWarnings(capture.str()), 1u);
}

#if defined(_MSC_VER)
#pragma warning(pop)
#else
#pragma GCC diagnostic pop
#endif

// ---------------------------------------------------------------------------------------------------------------------------
// CommitRequest
// ---------------------------------------------------------------------------------------------------------------------------

TEST_F(RestData, CommitRequestWithCreateUpdateDelete) {
    CerrCapture capture;
    const auto created = makePackage("Created");
    const auto updated = makePackage("Updated");
    std::vector<std::shared_ptr<DataVersion>> changes = {
        std::make_shared<DataVersion>(created),
        std::make_shared<DataVersion>(updated, std::make_shared<DataIdentity>(updated->getId())),
        std::make_shared<DataVersion>(nullptr, std::make_shared<DataIdentity>(uuidOf(DataId)))};
    CommitRequest request("changes", changes, {uuidOf(CommitId)});

    const json written = json::parse(request.serializeToJson());
    EXPECT_EQ(written["@type"], "Commit");
    ASSERT_EQ(written["change"].size(), 3u);
    for (const auto& change : written["change"])
        EXPECT_FALSE(change.contains("@id"));
    // create
    EXPECT_FALSE(written["change"][0].contains("identity"));
    EXPECT_TRUE(written["change"][0]["payload"].is_object());
    // update
    EXPECT_EQ(written["change"][1]["identity"], reference(boost::uuids::to_string(updated->getId())));
    EXPECT_TRUE(written["change"][1]["payload"].is_object());
    // delete
    EXPECT_EQ(written["change"][2]["identity"], reference(DataId));
    EXPECT_TRUE(written["change"][2]["payload"].is_null());

    CommitRequest read(written.dump());
    EXPECT_EQ(read.description(), "changes");
    ASSERT_EQ(read.changeRequested().size(), 3u);
    EXPECT_EQ(read.changeRequested()[0]->getId(), created->getId());
    EXPECT_EQ(read.changeRequested()[1]->getId(), updated->getId());
    EXPECT_EQ(read.changeRequested()[2]->getId(), uuidOf(DataId));
    EXPECT_EQ(read.changeRequested()[2]->getPayload(), nullptr);
    EXPECT_EQ(read.previousCommits().size(), 1u);
    // the round trip keeps the shapes
    EXPECT_EQ(json::parse(read.serializeToJson()), written);
    EXPECT_EQ(countWarnings(capture.str()), 0u);
}

TEST_F(RestData, CommitRequestReadsAnnexBDataVersions) {
    CerrCapture capture;
    const json request = {{"@type", "Commit"}, {"description", "x"},
                          {"change", {{{"@id", VersionId}, {"identity", {{"@id", DataId}, {"@type", "DataIdentity"}}}, {"payload", nullptr}}}}};
    CommitRequest read(request.dump());
    ASSERT_EQ(read.changeRequested().size(), 1u);
    EXPECT_EQ(read.changeRequested()[0]->getVersionId(), uuidOf(VersionId));
    EXPECT_EQ(read.changeRequested()[0]->getId(), uuidOf(DataId));
    EXPECT_EQ(countWarnings(capture.str()), 0u);
}

// ---------------------------------------------------------------------------------------------------------------------------
// DataDifference and MergeResult
// ---------------------------------------------------------------------------------------------------------------------------

TEST_F(RestData, DataDifferenceRoundTrip) {
    CerrCapture capture;
    const auto base = std::make_shared<DataVersion>(makePackage("Base"));
    const auto compare = std::make_shared<DataVersion>(nullptr, std::make_shared<DataIdentity>(uuidOf(DataId)));
    DataDifference difference(base, compare);

    const json written = json::parse(difference.serializeToJson());
    EXPECT_EQ(written["@type"], "DataDifference");
    EXPECT_TRUE(written["baseData"].is_object());
    EXPECT_TRUE(written["compareData"].is_object());

    DataDifference read(written.dump());
    ASSERT_NE(read.baseData(), nullptr);
    EXPECT_EQ(read.baseData()->getId(), base->getId());
    ASSERT_NE(read.compareData(), nullptr);
    EXPECT_EQ(read.compareData()->getId(), uuidOf(DataId));
    EXPECT_EQ(read.compareData()->getPayload(), nullptr);
    EXPECT_EQ(json::parse(read.serializeToJson()), written);
    EXPECT_EQ(countWarnings(capture.str()), 0u);
}

TEST_F(RestData, DataDifferenceNullSides) {
    DataDifference empty;
    const json written = json::parse(empty.serializeToJson());
    EXPECT_TRUE(written["baseData"].is_null());
    EXPECT_TRUE(written["compareData"].is_null());
    DataDifference read(written.dump());
    EXPECT_EQ(read.baseData(), nullptr);
    EXPECT_EQ(read.compareData(), nullptr);
    DataDifference minimal(R"({"@type":"DataDifference"})");
    EXPECT_EQ(minimal.baseData(), nullptr);
    DataDifference fromNullptr(nullptr);
    EXPECT_EQ(fromNullptr.compareData(), nullptr);
    EXPECT_THROW(DataDifference("{not json"), std::invalid_argument);
    EXPECT_THROW(DataDifference(R"({"baseData": 5})"), std::invalid_argument);
}

TEST_F(RestData, MergeResultCommitShape) {
    CerrCapture capture;
    auto commit = std::make_shared<Commit>("merged", nullptr);
    MergeResult result(commit);
    const std::string text = result.serializeToJson();
    EXPECT_TRUE(json::parse(text).is_object());
    EXPECT_EQ(json::parse(text)["@id"], boost::uuids::to_string(commit->getId()));

    const MergeResult read = MergeResult::fromJson(text);
    ASSERT_NE(read.mergeCommit(), nullptr);
    EXPECT_EQ(read.mergeCommit()->getId(), commit->getId());
    EXPECT_TRUE(read.conflict().empty());
    EXPECT_EQ(countWarnings(capture.str()), 0u);
}

TEST_F(RestData, MergeResultConflictShape) {
    CerrCapture capture;
    MergeResult result(nullptr, {std::make_shared<DataIdentity>(uuidOf(DataId)), std::make_shared<DataIdentity>(uuidOf(OtherDataId))});
    const std::string text = result.serializeToJson();
    const json written = json::parse(text);
    ASSERT_TRUE(written.is_array());
    ASSERT_EQ(written.size(), 2u);
    EXPECT_EQ(written[0]["@id"], DataId);
    EXPECT_EQ(written[0]["@type"], "DataIdentity");

    MergeResult read = MergeResult::fromJson(text);
    EXPECT_EQ(read.mergeCommit(), nullptr);
    ASSERT_EQ(read.conflict().size(), 2u);
    EXPECT_EQ(read.conflict()[1]->getId(), uuidOf(OtherDataId));
    EXPECT_EQ(json::parse(read.serializeToJson()), written);
    EXPECT_EQ(countWarnings(capture.str()), 0u);
}

TEST_F(RestData, MergeResultFromMinimalConflictsAndErrors) {
    MergeResult read = MergeResult::fromJson(json::array({json{{"@id", DataId}}}).dump());
    EXPECT_EQ(read.conflict().size(), 1u);
    MergeResult empty = MergeResult::fromJson("[]");
    EXPECT_EQ(empty.mergeCommit(), nullptr);
    EXPECT_TRUE(empty.conflict().empty());
    EXPECT_THROW(MergeResult::fromJson("{not json"), std::invalid_argument);
    EXPECT_THROW(MergeResult::fromJson("5"), std::invalid_argument);
    EXPECT_THROW(MergeResult::fromJson("[5]"), std::invalid_argument);
}

// ---------------------------------------------------------------------------------------------------------------------------
// ProjectUsage
// ---------------------------------------------------------------------------------------------------------------------------

TEST_F(RestData, ProjectUsageWritesReferences) {
    CerrCapture capture;
    auto project = std::make_shared<Project>(json{{"@id", ProjectId}}.dump());
    auto commit = std::make_shared<Commit>(uuidOf(CommitId), "used", project);
    ProjectUsage usage(commit);
    const json written = json::parse(usage.serializeToJson());
    EXPECT_EQ(written["@type"], "ProjectUsage");
    EXPECT_EQ(written["@id"], boost::uuids::to_string(usage.getId()));
    EXPECT_EQ(written["usedProjectCommit"], reference(CommitId));
    EXPECT_EQ(written["usedProject"], reference(ProjectId));
    EXPECT_FALSE(written.contains("usedCommit"));
    ASSERT_NE(usage.getUsedProject(), nullptr);
    EXPECT_EQ(usage.getUsedProject()->getId(), uuidOf(ProjectId));

    ProjectUsage read(written.dump());
    EXPECT_EQ(read.getId(), usage.getId());
    EXPECT_EQ(read.getType(), "ProjectUsage");
    ASSERT_NE(read.getUsedProjectCommit(), nullptr);
    EXPECT_EQ(read.getUsedProjectCommit()->getId(), uuidOf(CommitId));
    ASSERT_NE(read.getUsedProject(), nullptr);
    EXPECT_EQ(read.getUsedProject()->getId(), uuidOf(ProjectId));
    EXPECT_EQ(countWarnings(capture.str()), 0u);
}

TEST_F(RestData, ProjectUsageWithoutCommitDoesNotCrash) {
    ProjectUsage usage{std::shared_ptr<Commit>()};
    EXPECT_EQ(usage.getUsedProject(), nullptr);
    const json written = json::parse(usage.serializeToJson());
    EXPECT_TRUE(written["usedProjectCommit"].is_null());
    EXPECT_FALSE(written.contains("usedProject"));

    // a commit that does not know its project: usedProject comes from the JSON
    ProjectUsage read(json{{"@id", DataId}, {"@type", "ProjectUsage"}, {"usedProjectCommit", reference(CommitId)},
                           {"usedProject", reference(ProjectId)}}.dump());
    ASSERT_NE(read.getUsedProject(), nullptr);
    EXPECT_EQ(read.getUsedProject()->getId(), uuidOf(ProjectId));
    // a new commit makes the project derived again
    read.setUsedProjectCommit(nullptr);
    EXPECT_EQ(read.getUsedProject(), nullptr);

    ProjectUsage minimal(json{{"@id", DataId}}.dump());
    EXPECT_EQ(minimal.getUsedProjectCommit(), nullptr);
    EXPECT_EQ(minimal.getUsedProject(), nullptr);
    EXPECT_THROW(ProjectUsage("{not json"), std::invalid_argument);
    EXPECT_THROW(ProjectUsage(json{{"@type", "ProjectUsage"}}.dump()), std::invalid_argument);
    EXPECT_THROW(ProjectUsage(json{{"@id", DataId}, {"usedProjectCommit", 5}}.dump()), std::invalid_argument);
}

TEST_F(RestData, ProjectUsageOldUsedCommitStringFormat) {
    CerrCapture capture;
    // earlier versions wrote the full commit as escaped JSON text
    const json commit = {{"@id", CommitId}, {"@type", "Commit"}, {"owningProject", reference(ProjectId)}};
    ProjectUsage usage(json{{"@id", DataId}, {"@type", "ProjectUsage"}, {"usedCommit", commit.dump()}}.dump());
    EXPECT_EQ(countWarnings(capture.str()), 1u);
    EXPECT_NE(capture.str().find("\"usedCommit\""), std::string::npos);
    ASSERT_NE(usage.getUsedProjectCommit(), nullptr);
    EXPECT_EQ(usage.getUsedProjectCommit()->getId(), uuidOf(CommitId));
    ASSERT_NE(usage.getUsedProject(), nullptr);
    EXPECT_EQ(usage.getUsedProject()->getId(), uuidOf(ProjectId));
    // written in the new format
    const json written = json::parse(usage.serializeToJson());
    EXPECT_EQ(written["usedProjectCommit"], reference(CommitId));
    EXPECT_FALSE(written.contains("usedCommit"));
}

TEST_F(RestData, ProjectUsageOldUsedCommitObjectFormat) {
    CerrCapture capture;
    ProjectUsage usage(json{{"@id", DataId}, {"@type", "ProjectUsage"}, {"usedCommit", reference(CommitId)}}.dump());
    EXPECT_EQ(countWarnings(capture.str()), 1u);
    ASSERT_NE(usage.getUsedProjectCommit(), nullptr);
    EXPECT_EQ(usage.getUsedProjectCommit()->getId(), uuidOf(CommitId));
    EXPECT_THROW(ProjectUsage(json{{"@id", DataId}, {"usedCommit", "not json"}}.dump()), std::invalid_argument);
}

// ---------------------------------------------------------------------------------------------------------------------------
// ExternalData and ExternalRelationship
// ---------------------------------------------------------------------------------------------------------------------------

TEST_F(RestData, ExternalDataFromIriDoesNotThrow) {
    CerrCapture capture;
    ExternalData data("https://example.com/model.sysml");
    EXPECT_EQ(data.resourceIdentifier(), "https://example.com/model.sysml");
    EXPECT_EQ(data.getType(), "ExternalData");
    EXPECT_FALSE(data.getId().is_nil());

    const json written = json::parse(data.serializeToJson());
    EXPECT_EQ(written["@type"], "ExternalData");
    EXPECT_EQ(written["resourceIdentifier"], "https://example.com/model.sysml");
    EXPECT_EQ(written["@id"], boost::uuids::to_string(data.getId()));

    ExternalData read(written.dump());
    EXPECT_EQ(read.getId(), data.getId());
    EXPECT_EQ(read.resourceIdentifier(), "https://example.com/model.sysml");
    EXPECT_EQ(countWarnings(capture.str()), 0u);
}

TEST_F(RestData, ExternalDataJsonErrors) {
    EXPECT_THROW(ExternalData("{not json"), std::invalid_argument);
    EXPECT_THROW(ExternalData(json{{"resourceIdentifier", "x"}}.dump()), std::invalid_argument);
    EXPECT_THROW(ExternalData(json{{"@id", DataId}, {"resourceIdentifier", 5}}.dump()), std::invalid_argument);
    ExternalData withNull(json{{"@id", DataId}, {"resourceIdentifier", nullptr}}.dump());
    EXPECT_EQ(withNull.resourceIdentifier(), "");
}

TEST_F(RestData, ExternalRelationshipAllFields) {
    CerrCapture capture;
    auto element = std::make_shared<Data>(uuidOf(DataId));
    auto external = std::make_shared<ExternalData>("https://example.com/x");
    ExternalRelationship relationship(element, external, "select *", "SQL");

    const json written = json::parse(relationship.serializeToJson());
    EXPECT_EQ(written["@type"], "ExternalRelationship");
    EXPECT_EQ(written["elementEnd"], reference(DataId));
    EXPECT_EQ(written["externalDataEnd"], reference(boost::uuids::to_string(external->getId())));
    EXPECT_EQ(written["specification"], "select *");
    EXPECT_EQ(written["language"], "SQL");

    ExternalRelationship read(written.dump());
    EXPECT_EQ(read.getId(), relationship.getId());
    ASSERT_NE(read.elementEnd(), nullptr);
    EXPECT_EQ(read.elementEnd()->getId(), uuidOf(DataId));
    ASSERT_NE(read.externalDataEnd(), nullptr);
    EXPECT_EQ(read.externalDataEnd()->getId(), external->getId());
    EXPECT_EQ(read.specification(), "select *");
    EXPECT_EQ(read.language(), "SQL");
    EXPECT_EQ(json::parse(read.serializeToJson()), written);
    EXPECT_EQ(countWarnings(capture.str()), 0u);
}

TEST_F(RestData, ExternalRelationshipOptionalFieldsMissing) {
    CerrCapture capture;
    ExternalRelationship fromJson(json{{"@id", VersionId}, {"@type", "ExternalRelationship"}, {"elementEnd", reference(DataId)},
                                       {"externalDataEnd", reference(OtherDataId)}, {"specification", nullptr}}.dump());
    EXPECT_EQ(fromJson.specification(), "");
    EXPECT_EQ(fromJson.language(), "");
    const json written = json::parse(fromJson.serializeToJson());
    EXPECT_FALSE(written.contains("specification"));
    EXPECT_FALSE(written.contains("language"));

    ExternalRelationship minimal(json{{"@id", VersionId}}.dump());
    EXPECT_EQ(minimal.elementEnd(), nullptr);
    EXPECT_EQ(minimal.externalDataEnd(), nullptr);
    const json minimalWritten = json::parse(minimal.serializeToJson());
    EXPECT_TRUE(minimalWritten["elementEnd"].is_null());
    EXPECT_TRUE(minimalWritten["externalDataEnd"].is_null());

    // the old constructor
    ExternalRelationship old("spec", "lang");
    EXPECT_EQ(old.specification(), "spec");
    EXPECT_EQ(old.language(), "lang");
    EXPECT_EQ(old.getType(), "ExternalRelationship");
    ExternalRelationship empty("", "");
    EXPECT_FALSE(json::parse(empty.serializeToJson()).contains("language"));
    EXPECT_EQ(countWarnings(capture.str()), 0u);
}

TEST_F(RestData, ExternalRelationshipJsonErrors) {
    EXPECT_THROW(ExternalRelationship("{not json"), std::invalid_argument);
    EXPECT_THROW(ExternalRelationship(json{{"@id", DataId}, {"elementEnd", "x"}}.dump()), std::invalid_argument);
    EXPECT_THROW(ExternalRelationship(json{{"@id", DataId}, {"language", 5}}.dump()), std::invalid_argument);
}

// ---------------------------------------------------------------------------------------------------------------------------
// Services
// ---------------------------------------------------------------------------------------------------------------------------

TEST_F(RestData, ElementNavigationServiceFindsElementsByDataId) {
    CerrCapture capture;
    auto project = std::make_shared<Project>(json{{"@id", ProjectId}}.dump());
    auto commit = std::make_shared<Commit>("commit", project);
    const auto package = makePackage("Navigated");
    commit->addChange(std::make_shared<DataVersion>(package));

    SysMLv2::API::ElementNavigationService service;
    EXPECT_EQ(service.getElements(project, commit).size(), 1u);
    const auto found = service.getElementById(project, commit, package->getId());
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->getId(), package->getId());
    EXPECT_THROW(service.getElementById(project, commit, uuidOf(OtherDataId)), std::runtime_error);
    EXPECT_EQ(countWarnings(capture.str()), 0u);
}

TEST_F(RestData, ProjectVersioningServiceChangeFilterAndLookup) {
    CerrCapture capture;
    auto project = std::make_shared<Project>(json{{"@id", ProjectId}}.dump());
    // The package exists in the previous commit, so the change in "commit" is an update.
    const auto package = makePackage("Filtered");
    auto previous = std::make_shared<Commit>("previous", project);
    previous->addChange(std::make_shared<DataVersion>(package));
    auto commit = std::make_shared<Commit>("commit", project, std::vector<std::shared_ptr<Commit>>{previous});
    auto update = std::make_shared<DataVersion>(package);
    auto deletion = std::make_shared<DataVersion>(nullptr, std::make_shared<DataIdentity>(uuidOf(DataId)));
    commit->addChange(update);
    commit->addChange(deletion);

    SysMLv2::API::ProjectVersioningService service;
    const auto updated = service.getCommitChange(project, commit, {static_cast<int>(ChangeType::UPDATED)});
    ASSERT_EQ(updated.size(), 1u);
    EXPECT_EQ(updated[0], update);
    const auto deleted = service.getCommitChange(project, commit, {static_cast<int>(ChangeType::DELETED)});
    ASSERT_EQ(deleted.size(), 1u);
    EXPECT_EQ(deleted[0], deletion);

    // by the id of the DataVersion and by the id of the Data
    auto versionId = deletion->getVersionId();
    EXPECT_EQ(service.getCommitChangeById(project, commit, versionId), deletion);
    auto dataId = package->getId();
    EXPECT_EQ(service.getCommitChangeById(project, commit, dataId), update);
    auto unknown = uuidOf(OtherDataId);
    EXPECT_EQ(service.getCommitChangeById(project, commit, unknown), nullptr);
    EXPECT_EQ(countWarnings(capture.str()), 0u);
}

namespace {
    // Registers a project in the (protected) maps of the service.
    class OpenVersioningService : public SysMLv2::API::ProjectVersioningService {
    public:
        void registerProject(const boost::uuids::uuid& id) { ProjectIdBranchMap[id]; }
    };
}

TEST_F(RestData, ProjectVersioningServiceCreateBranchSetsOwningProject) {
    CerrCapture capture;
    auto project = std::make_shared<Project>(json{{"@id", ProjectId}}.dump());
    auto head = std::make_shared<Commit>("head", project);
    OpenVersioningService service;
    service.registerProject(project->getId());
    const auto branch = service.createBranch(project, "feature", head);
    ASSERT_NE(branch, nullptr);
    EXPECT_EQ(branch->getOwningProject(), project);
    EXPECT_EQ(branch->getHead(), head);
    EXPECT_EQ(json::parse(branch->serializeToJson())["owningProject"], reference(ProjectId));
    EXPECT_EQ(countWarnings(capture.str()), 0u);
}

TEST_F(RestData, ElementNavigationServiceSkipsDeletions) {
    auto project = std::make_shared<Project>(json{{"@id", ProjectId}}.dump());
    auto commit = std::make_shared<Commit>("commit", project);
    const auto package = makePackage("Alive");
    commit->addChange(std::make_shared<DataVersion>(package));
    commit->addChange(std::make_shared<DataVersion>(nullptr, std::make_shared<DataIdentity>(uuidOf(DataId))));

    SysMLv2::API::ElementNavigationService service;
    const auto elements = service.getElements(project, commit);
    ASSERT_EQ(elements.size(), 1u);
    EXPECT_NE(elements[0], nullptr);
    // a deleted element is not found, like an unknown id
    EXPECT_THROW(service.getElementById(project, commit, uuidOf(DataId)), std::runtime_error);
    EXPECT_NE(service.getElementById(project, commit, package->getId()), nullptr);
}

TEST_F(RestData, MergeResultAndDataDifferenceAreAssignable) {
    auto commit = std::make_shared<Commit>("merged", nullptr);
    MergeResult first(commit);
    MergeResult second;
    second = first;
    EXPECT_EQ(second.mergeCommit(), commit);
    MergeResult third;
    third = std::move(second);
    EXPECT_EQ(third.mergeCommit(), commit);
    MergeResult copy(third);
    EXPECT_EQ(copy.mergeCommit(), commit);

    auto version = std::make_shared<DataVersion>(makePackage("d"));
    DataDifference a(version, nullptr);
    DataDifference b;
    b = a;
    EXPECT_EQ(b.baseData(), version);
    DataDifference c;
    c = std::move(b);
    EXPECT_EQ(c.baseData(), version);
    const DataDifference constant(c);
    EXPECT_EQ(constant.baseData(), version);
    EXPECT_EQ(constant.compareData(), nullptr);
}

TEST_F(RestData, DataVersionIdentityMustMatchPayload) {
    const auto package = makePackage("Mismatch");
    EXPECT_THROW(DataVersion(package, std::make_shared<DataIdentity>(uuidOf(DataId))), std::invalid_argument);
    const json bad = {{"identity", reference(DataId)}, {"payload", json::parse(package->serializeToJson())}};
    EXPECT_THROW(DataVersion(bad.dump()), std::invalid_argument);
}

TEST_F(RestData, DataVersionPayloadNeedsIdAndType) {
    try {
        DataVersion version(json{{"identity", reference(DataId)}, {"payload", {{"name", "x"}}}}.dump());
        FAIL() << "expected an exception";
    } catch (const std::invalid_argument& ex) {
        EXPECT_EQ(std::string(ex.what()), "DataVersion: 'payload' needs '@id' and '@type'");
    }
}

TEST_F(RestData, DataIdentityTimeFallsBackWhenCommitHasNoTimestamp) {
    DataIdentity identity(json{{"@id", DataId}, {"createdAt", reference(CommitId)}, {"created", "2025-03-13T10:00:00"}}.dump());
    EXPECT_NE(identity.createdAt(), std::chrono::system_clock::time_point{});
}

TEST_F(RestData, CommitJsonRoundTripWithAnnexBDeletion) {
    CerrCapture capture;
    const json commitJson = {{"@id", CommitId}, {"@type", "Commit"}, {"owningProject", reference(ProjectId)},
                             {"change", {{{"@id", VersionId}, {"identity", {{"@id", DataId}, {"@type", "DataIdentity"}}}, {"payload", nullptr}}}}};
    Commit commit(commitJson.dump());
    ASSERT_EQ(commit.getChange().size(), 1u);
    EXPECT_EQ(commit.getChange()[0]->getPayload(), nullptr);
    EXPECT_EQ(commit.getChange()[0]->getId(), uuidOf(DataId));
    const json written = json::parse(commit.serializeToJson());
    EXPECT_EQ(written["change"], commitJson["change"].is_array() ? json::array({json{{"@id", VersionId}, {"@type", "DataVersion"},
              {"identity", {{"@id", DataId}, {"@type", "DataIdentity"}}}, {"payload", nullptr}}}) : json());
    EXPECT_EQ(countWarnings(capture.str()), 0u);
}

TEST_F(RestData, DataIdentityAsWrittenByEarlierLibraryVersion) {
    CerrCapture capture;
    DataIdentity identity(json{{"@id", DataId}, {"@type", "DataIdentity"}, {"dataVersions", json::array()},
                               {"created", "2025-03-13T10:00:00"}, {"deleted", "1970-01-01T00:00:00"}}.dump());
    EXPECT_EQ(identity.getId(), uuidOf(DataId));
    EXPECT_TRUE(identity.getDataVersions().empty());
    EXPECT_EQ(countWarnings(capture.str()), 3u);
}
