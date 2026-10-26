//
// Tests of the versioning entities of the REST API (AP 1): Project, ProjectRequest, Commit, CommitReference, Branch, Tag,
// BranchRequest, TagRequest and the parts of CommitRequest that do not depend on DataVersion. Contains the Annex B examples,
// round trips and the compatibility tests of the deprecated APIs and JSON formats.
//

#include <gtest/gtest.h>
#include <chrono>
#include <map>
#include <memory>
#include <set>
#include <stdexcept>
#include <string>
#include <nlohmann/json.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include "support/CerrCapture.h"
#include <sysmlv2/rest/Deprecation.h>
#include <kerml/kernel/packages/Package.h>
#include <kerml/core/types/Specialization.h>
#include <kerml/root/elements/Relationship.h>
#include <kerml/root/namespaces/OwningMembership.h>
#include <sysmlv2/rest/entities/Branch.h>
#include <sysmlv2/rest/entities/BranchRequest.h>
#include <sysmlv2/rest/entities/Commit.h>
#include <sysmlv2/rest/entities/CommitRequest.h>
#include <sysmlv2/rest/entities/Data.h>
#include <sysmlv2/rest/entities/DataDifference.h>
#include <sysmlv2/rest/entities/DataIdentity.h>
#include <sysmlv2/rest/entities/DataVersion.h>
#include <sysmlv2/rest/entities/Project.h>
#include <sysmlv2/rest/entities/ProjectRequest.h>
#include <sysmlv2/rest/entities/Tag.h>
#include <sysmlv2/rest/entities/TagRequest.h>
#include <sysmlv2/rest/serialization/Utilities.h>
#include <sysmlv2/rest/versioning/CommitFactory.h>
#include <sysmlv2/rest/versioning/ElementReferences.h>
#include <sysmlv2/rest/versioning/Merge.h>
#include <sysmlv2/rest/versioning/VersionedData.h>

using namespace SysMLv2::REST;
using nlohmann::json;

namespace {
    const std::string ProjectId = "6e701bf8-7793-49de-9b0e-2f43376edabf";
    const std::string BranchId = "7eea9bd1-1082-4521-8bb2-d94202c8dd63";
    const std::string CommitId = "c4fc0b1e-2d3a-4b5c-8d6e-7f8091a2b3c4";
    const std::string OtherCommitId = "0f1e2d3c-4b5a-4968-8776-655443322110";
    const std::string DataId = "11111111-2222-4333-8444-555555555555";

    std::size_t countWarnings(const std::string& output) {
        std::size_t count = 0;
        for (auto pos = output.find("Deprecated:"); pos != std::string::npos; pos = output.find("Deprecated:", pos + 1))
            ++count;
        return count;
    }

    std::string ref(const std::string& id) {
        return json{{"@id", id}}.dump();
    }

    json reference(const std::string& id) {
        return json{{"@id", id}};
    }

    boost::uuids::uuid uuidOf(const std::string& id) {
        return boost::uuids::string_generator()(id);
    }

    bool endsWithZ(const std::string& text) {
        return !text.empty() && text.back() == 'Z';
    }

    class RestVersioning : public ::testing::Test {
    protected:
        void SetUp() override { resetDeprecationWarningsForTesting(); }
    };
}

// ---------------------------------------------------------------------------------------------------------------------------
// Project
// ---------------------------------------------------------------------------------------------------------------------------

TEST_F(RestVersioning, ProjectAnnexBWithNullDescription) {
    CerrCapture capture;
    const Project project(json{{"@id", ProjectId}, {"@type", "Project"}, {"name", "Hello"}, {"description", nullptr},
                                {"created", "2025-03-13T10:00:00Z"}, {"defaultBranch", reference(BranchId)}}.dump());
    EXPECT_EQ(project.getName(), "Hello");
    EXPECT_EQ(project.getDescription(), "");
    ASSERT_TRUE(project.getCreated().has_value());
    ASSERT_EQ(const_cast<Project&>(project).getDefaultBranch()->getId(), uuidOf(BranchId));
    EXPECT_EQ(project.getBranches().size(), 1u);
    EXPECT_EQ(countWarnings(capture.str()), 0u);
}

TEST_F(RestVersioning, ProjectRoundTripWritesCreatedWithZ) {
    CerrCapture capture;
    Project project("P", "D", "main");
    const json written = json::parse(project.serializeToJson());
    ASSERT_TRUE(written.contains("created"));
    EXPECT_TRUE(endsWithZ(written["created"].get<std::string>()));
    EXPECT_EQ(written["defaultBranch"]["@id"], boost::uuids::to_string(project.getDefaultBranch()->getId()));

    Project copy(project.serializeToJson());
    EXPECT_EQ(copy.getId(), project.getId());
    EXPECT_EQ(copy.getName(), "P");
    EXPECT_EQ(copy.getDefaultBranch()->getId(), project.getDefaultBranch()->getId());
    EXPECT_EQ(countWarnings(capture.str()), 0u);
}

TEST_F(RestVersioning, ProjectDefaultBranchIsContainedOnceInBranches) {
    Project project("P", "D", "main");
    EXPECT_EQ(project.getBranches().size(), 1u);
    auto branch = project.getDefaultBranch();
    project.setDefaultBranch(branch);
    project.setDefaultBranch(branch);
    EXPECT_EQ(project.getBranches().size(), 1u);

    auto other = std::make_shared<Branch>("develop");
    project.setDefaultBranch(other);
    EXPECT_EQ(project.getBranches().size(), 2u);
    EXPECT_EQ(project.getDefaultBranch(), other);
}

TEST_F(RestVersioning, ProjectWithoutDefaultBranchSerializes) {
    Project project(json{{"@id", ProjectId}, {"@type", "Project"}, {"name", "x"}}.dump());
    EXPECT_EQ(project.getDefaultBranch(), nullptr);
    json written;
    ASSERT_NO_THROW(written = json::parse(project.serializeToJson()));
    EXPECT_TRUE(written["defaultBranch"].is_null());
    EXPECT_FALSE(written.contains("created"));
}

TEST_F(RestVersioning, ProjectMalformedJsonThrowsAndNameIsAccepted) {
    EXPECT_THROW(Project("{\"name\": "), std::invalid_argument);
    EXPECT_THROW(Project(json{{"defaultBranch", "main"}}.dump()), std::invalid_argument);
    Project byName("Some name");
    EXPECT_EQ(byName.getName(), "Some name");
    EXPECT_EQ(byName.getAlias().size(), 1u);
}

// ---------------------------------------------------------------------------------------------------------------------------
// ProjectRequest
// ---------------------------------------------------------------------------------------------------------------------------

TEST_F(RestVersioning, ProjectRequestNewFormat) {
    CerrCapture capture;
    const ProjectRequest request("n", "d", std::optional<boost::uuids::uuid>(uuidOf(BranchId)));
    const json written = json::parse(const_cast<ProjectRequest&>(request).serializeToJson());
    EXPECT_EQ(written["@type"], "Project");
    EXPECT_EQ(written["defaultBranch"], reference(BranchId));
    EXPECT_FALSE(written.contains("@id"));
    ASSERT_TRUE(request.defaultBranchId().has_value());
    EXPECT_EQ(*request.defaultBranchId(), uuidOf(BranchId));

    ProjectRequest withoutBranch("n", "d", std::nullopt);
    EXPECT_FALSE(json::parse(withoutBranch.serializeToJson()).contains("defaultBranch"));

    ProjectRequest parsed(json{{"name", "n"}, {"defaultBranch", reference(BranchId)}}.dump());
    EXPECT_EQ(parsed.description(), "");
    EXPECT_EQ(*parsed.defaultBranchId(), uuidOf(BranchId));
    ProjectRequest minimal(json{{"name", "n"}, {"description", nullptr}, {"defaultBranch", nullptr}}.dump());
    EXPECT_FALSE(minimal.defaultBranchId().has_value());
    EXPECT_EQ(countWarnings(capture.str()), 0u);
}

TEST_F(RestVersioning, ProjectRequestInvalidInputThrows) {
    EXPECT_THROW(ProjectRequest("{"), std::invalid_argument);
    EXPECT_THROW(ProjectRequest(json{{"name", 5}}.dump()), std::invalid_argument);
    EXPECT_THROW(ProjectRequest(json{{"name", "n"}, {"defaultBranch", 5}}.dump()), std::invalid_argument);
    EXPECT_THROW(ProjectRequest(json{{"name", "n"}, {"defaultBranch", json{{"@id", "nope"}}}}.dump()), std::invalid_argument);
}

// ---------------------------------------------------------------------------------------------------------------------------
// Commit
// ---------------------------------------------------------------------------------------------------------------------------

TEST_F(RestVersioning, CommitListWithPreviousCommitNullAndObject) {
    CerrCapture capture;
    // Annex B: "previousCommit" is null for the first commit and a single object for the next one.
    const Commit first(json{{"@id", CommitId}, {"@type", "Commit"}, {"created", "2025-03-13T10:00:00Z"},
                             {"previousCommit", nullptr}, {"owningProject", reference(ProjectId)}}.dump());
    EXPECT_TRUE(first.getPreviousCommits().empty());
    EXPECT_NE(capture.str().find("previousCommit"), std::string::npos);
    EXPECT_EQ(countWarnings(capture.str()), 1u);

    resetDeprecationWarningsForTesting();
    CerrCapture second;
    const Commit next(json{{"@id", OtherCommitId}, {"@type", "Commit"}, {"previousCommit", reference(CommitId)}}.dump());
    ASSERT_EQ(next.getPreviousCommits().size(), 1u);
    EXPECT_EQ(next.getPreviousCommits()[0]->getId(), uuidOf(CommitId));
    EXPECT_EQ(countWarnings(second.str()), 1u);
}

TEST_F(RestVersioning, CommitPreviousCommitsAsArrayAreWrittenAndRead) {
    CerrCapture capture;
    const Commit commit(json{{"@id", OtherCommitId}, {"previousCommits", json::array({reference(CommitId)})},
                             {"created", "2025-03-13T10:00:00.5Z"}, {"owningProject", reference(ProjectId)}}.dump());
    ASSERT_EQ(commit.getPreviousCommits().size(), 1u);
    EXPECT_EQ(countWarnings(capture.str()), 0u);

    Commit copy(const_cast<Commit&>(commit).serializeToJson());
    const json written = json::parse(copy.serializeToJson());
    EXPECT_EQ(written["previousCommits"][0], reference(CommitId));
    EXPECT_TRUE(endsWithZ(written["created"].get<std::string>()));
    EXPECT_FALSE(written.contains("timestamp"));
    EXPECT_FALSE(written.contains("previousCommit"));
    EXPECT_EQ(written["owningProject"], reference(ProjectId));
    EXPECT_EQ(copy.getCreated(), commit.getCreated());
    EXPECT_EQ(countWarnings(capture.str()), 0u);
}

TEST_F(RestVersioning, CommitTimestampFallbackWarnsOnce) {
    CerrCapture capture;
    const Commit commit(json{{"@id", CommitId}, {"timestamp", "2025-03-13T00:00:00Z"}}.dump());
    const Commit again(json{{"@id", CommitId}, {"timestamp", "2025-03-13T00:00:00Z"}}.dump());
    EXPECT_EQ(commit.getCreated(), again.getCreated());
    EXPECT_NE(commit.getCreated(), std::chrono::system_clock::time_point{});
    EXPECT_EQ(countWarnings(capture.str()), 1u);
    EXPECT_NE(capture.str().find("timestamp"), std::string::npos);
}

TEST_F(RestVersioning, CommitWithoutProjectSerializes) {
    Commit commit("d", nullptr);
    json written;
    ASSERT_NO_THROW(written = json::parse(commit.serializeToJson()));
    EXPECT_TRUE(written["owningProject"].is_null());
    EXPECT_TRUE(written["previousCommits"].is_array());
    EXPECT_TRUE(endsWithZ(written["created"].get<std::string>()));
}

TEST_F(RestVersioning, CommitInvalidJsonThrows) {
    EXPECT_THROW(Commit("not json"), std::invalid_argument);
    EXPECT_THROW(Commit(json{{"@id", CommitId}, {"previousCommits", 5}}.dump()), std::invalid_argument);
    EXPECT_THROW(Commit(json{{"@id", CommitId}, {"created", "yesterday"}}.dump()), std::invalid_argument);
}

// ---------------------------------------------------------------------------------------------------------------------------
// Branch, Tag, CommitReference
// ---------------------------------------------------------------------------------------------------------------------------

TEST_F(RestVersioning, BranchAnnexBWithNullNameAndHeadAndReferencedCommit) {
    CerrCapture capture;
    Branch branch(json{{"@id", BranchId}, {"@type", "Branch"}, {"name", nullptr}, {"description", nullptr},
                       {"created", "2025-03-13T10:00:00Z"}, {"head", reference(CommitId)},
                       {"referencedCommit", reference(CommitId)}, {"owningProject", reference(ProjectId)}}.dump());
    EXPECT_EQ(branch.getName(), "");
    EXPECT_TRUE(branch.getAlias().empty());
    ASSERT_NE(branch.getHead(), nullptr);
    EXPECT_EQ(branch.getHead()->getId(), uuidOf(CommitId));
    EXPECT_EQ(branch.referencedCommit()->getId(), uuidOf(CommitId));
    ASSERT_NE(branch.getOwningProject(), nullptr);
    EXPECT_EQ(branch.getOwningProject()->getId(), uuidOf(ProjectId));
    EXPECT_FALSE(branch.isDeleted());
    EXPECT_EQ(countWarnings(capture.str()), 0u);

    const json written = json::parse(branch.serializeToJson());
    EXPECT_EQ(written["@type"], "Branch");
    EXPECT_FALSE(written.contains("deleted"));
    EXPECT_TRUE(endsWithZ(written["created"].get<std::string>()));
    EXPECT_EQ(written["head"], reference(CommitId));
    EXPECT_EQ(written["referencedCommit"], reference(CommitId));
    EXPECT_EQ(written["owningProject"], reference(ProjectId));
}

TEST_F(RestVersioning, BranchHeadAndReferencedCommitStayInSync) {
    Branch onlyHead(json{{"@id", BranchId}, {"head", reference(CommitId)}}.dump());
    EXPECT_EQ(onlyHead.referencedCommit()->getId(), uuidOf(CommitId));
    Branch onlyReferenced(json{{"@id", BranchId}, {"referencedCommit", reference(CommitId)}}.dump());
    ASSERT_NE(onlyReferenced.getHead(), nullptr);
    EXPECT_EQ(onlyReferenced.getHead()->getId(), uuidOf(CommitId));

    auto commit = std::make_shared<Commit>("c", nullptr);
    Branch branch("b");
    branch.setHead(commit);
    EXPECT_EQ(branch.referencedCommit(), commit);
    EXPECT_EQ(json::parse(branch.serializeToJson())["head"]["@id"], boost::uuids::to_string(commit->getId()));
}

TEST_F(RestVersioning, BranchWithoutHeadSerializes) {
    Branch branch("lonely");
    json written;
    ASSERT_NO_THROW(written = json::parse(branch.serializeToJson()));
    EXPECT_TRUE(written["head"].is_null());
    EXPECT_TRUE(written["referencedCommit"].is_null());
    EXPECT_EQ(written["name"], "lonely");
}

TEST_F(RestVersioning, BranchWithoutHeadRoundTripKeepsOwningProject) {
    auto project = std::make_shared<Project>(json{{"@id", ProjectId}}.dump());
    Branch branch("main");
    branch.setOwningProject(project);
    const json written = json::parse(branch.serializeToJson());
    EXPECT_EQ(written["owningProject"], reference(ProjectId));
    EXPECT_TRUE(written["head"].is_null());

    // the null of a branch without head is read back as no head
    const Branch read(written.dump());
    EXPECT_EQ(const_cast<Branch&>(read).getHead(), nullptr);
    ASSERT_NE(read.getOwningProject(), nullptr);
    EXPECT_EQ(read.getOwningProject()->getId(), uuidOf(ProjectId));
}

TEST_F(RestVersioning, BranchMalformedThrowsWithClassName) {
    try {
        Branch(json{{"@id", BranchId}, {"head", "abc"}}.dump());
        FAIL() << "expected std::invalid_argument";
    } catch (const std::invalid_argument& ex) {
        EXPECT_NE(std::string(ex.what()).find("Branch"), std::string::npos);
    }
    EXPECT_THROW(Branch("{\"@id\": "), std::invalid_argument);
    try {
        Tag(json{{"@id", BranchId}, {"taggedCommit", 3}}.dump());
        FAIL() << "expected std::invalid_argument";
    } catch (const std::invalid_argument& ex) {
        EXPECT_NE(std::string(ex.what()).find("Tag"), std::string::npos);
    }
}

TEST_F(RestVersioning, DeletedIsOptional) {
    CerrCapture capture;
    Branch branch("b");
    EXPECT_FALSE(branch.isDeleted());
    EXPECT_FALSE(branch.deletedAt().has_value());
    EXPECT_FALSE(json::parse(branch.serializeToJson()).contains("deleted"));
    EXPECT_EQ(branch.deleted(), std::chrono::system_clock::time_point{});

    const auto when = std::chrono::system_clock::time_point{} + std::chrono::seconds(1700000000);
    branch.setDeleted(when);
    EXPECT_TRUE(branch.isDeleted());
    EXPECT_EQ(branch.deleted(), when);
    const json written = json::parse(branch.serializeToJson());
    EXPECT_TRUE(endsWithZ(written["deleted"].get<std::string>()));

    Branch copy(branch.serializeToJson());
    ASSERT_TRUE(copy.deletedAt().has_value());
    EXPECT_EQ(*copy.deletedAt(), when);
    EXPECT_EQ(countWarnings(capture.str()), 0u);
}

TEST_F(RestVersioning, TagAnnexB) {
    CerrCapture capture;
    Tag tag(json{{"@id", BranchId}, {"@type", "Tag"}, {"name", "v1"}, {"created", "2025-03-13T10:00:00Z"},
                 {"taggedCommit", reference(CommitId)}, {"owningProject", reference(ProjectId)}}.dump());
    EXPECT_EQ(tag.getType(), "Tag");
    ASSERT_NE(tag.taggedCommit(), nullptr);
    EXPECT_EQ(tag.taggedCommit()->getId(), uuidOf(CommitId));
    EXPECT_EQ(tag.referencedCommit(), tag.taggedCommit());
    EXPECT_EQ(tag.owningProject()->getId(), uuidOf(ProjectId));
    EXPECT_EQ(tag.getOwningProject(), tag.owningProject());

    const json written = json::parse(tag.serializeToJson());
    EXPECT_EQ(written["@type"], "Tag");
    EXPECT_EQ(written["taggedCommit"], reference(CommitId));
    EXPECT_EQ(written["referencedCommit"], reference(CommitId));
    EXPECT_EQ(written["owningProject"], reference(ProjectId));
    EXPECT_EQ(countWarnings(capture.str()), 0u);

    Tag onlyReferenced(json{{"@id", BranchId}, {"referencedCommit", reference(CommitId)}}.dump());
    EXPECT_EQ(onlyReferenced.taggedCommit()->getId(), uuidOf(CommitId));
}

TEST_F(RestVersioning, TagConstructedFromValues) {
    CerrCapture capture;
    auto project = std::make_shared<Project>("P", "D", "main");
    auto commit = std::make_shared<Commit>("c", project);
    Tag tag("v2", project, commit);
    EXPECT_EQ(tag.getName(), "v2");
    EXPECT_EQ(tag.taggedCommit(), commit);
    EXPECT_EQ(tag.owningProject(), project);
    EXPECT_EQ(json::parse(tag.serializeToJson())["@type"], "Tag");
    Tag withoutCommit("v3");
    EXPECT_NO_THROW(withoutCommit.serializeToJson());
    EXPECT_EQ(countWarnings(capture.str()), 0u);
}

TEST_F(RestVersioning, OldLibraryDeletedPlaceholdersMeanNotDeleted) {
    for (const std::string placeholder : {"1970-01-01T00:00:00", "1970-01-01T00:00:00.000000", "1970-01-01T00:00:00.000000Z",
                                          "2262-04-11T23:47:16.145224", "2262-04-11T23:47:16.145224Z",
                                          "1677-09-21T00:12:44.-854775", "1677-09-21T00:12:44", "2000-01-01T00:00:00.-5"}) {
        resetDeprecationWarningsForTesting();
        CerrCapture capture;
        Branch branch(json{{"@id", BranchId}, {"created", "2025-03-13T10:00:00Z"}, {"deleted", placeholder},
                           {"head", reference(CommitId)}}.dump());
        Branch again(json{{"@id", BranchId}, {"deleted", placeholder}}.dump());
        EXPECT_FALSE(branch.isDeleted()) << placeholder;
        EXPECT_FALSE(json::parse(branch.serializeToJson()).contains("deleted")) << placeholder;
        EXPECT_EQ(countWarnings(capture.str()), 1u) << placeholder;
    }
}

TEST_F(RestVersioning, RealDeletedTimestampIsKept) {
    CerrCapture capture;
    Tag tag(json{{"@id", BranchId}, {"deleted", "2025-03-13T10:00:00Z"}}.dump());
    EXPECT_TRUE(tag.isDeleted());
    EXPECT_EQ(countWarnings(capture.str()), 0u);
}

TEST_F(RestVersioning, BranchHeadWinsOverReferencedCommit) {
    Branch branch(json{{"@id", BranchId}, {"head", reference(CommitId)}, {"referencedCommit", reference(OtherCommitId)}}.dump());
    EXPECT_EQ(branch.getHead()->getId(), uuidOf(CommitId));
    EXPECT_EQ(branch.referencedCommit()->getId(), uuidOf(CommitId));
}

TEST_F(RestVersioning, TagTaggedCommitWinsOverReferencedCommit) {
    Tag tag(json{{"@id", BranchId}, {"taggedCommit", reference(CommitId)}, {"referencedCommit", reference(OtherCommitId)}}.dump());
    EXPECT_EQ(tag.taggedCommit()->getId(), uuidOf(CommitId));
    EXPECT_EQ(tag.referencedCommit()->getId(), uuidOf(CommitId));
}

TEST_F(RestVersioning, CommitOldPreviousCommitArrayWarnsOnce) {
    CerrCapture capture;
    const Commit commit(json{{"@id", OtherCommitId}, {"previousCommit", json::array({reference(CommitId), reference(BranchId)})}}.dump());
    EXPECT_EQ(commit.getPreviousCommits().size(), 2u);
    EXPECT_EQ(countWarnings(capture.str()), 1u);
}

TEST_F(RestVersioning, ProjectDuplicateBranchDetectedById) {
    Project project("P", "D", "main");
    auto first = std::make_shared<Branch>(json{{"@id", BranchId}}.dump());
    auto second = std::make_shared<Branch>(json{{"@id", BranchId}}.dump());
    ASSERT_NE(first, second);
    project.setDefaultBranch(first);
    project.setDefaultBranch(second);
    EXPECT_EQ(project.getBranches().size(), 2u);  // the "main" branch of the constructor and the one with BranchId
}

TEST_F(RestVersioning, MalformedJsonNamesTheConcreteClass) {
    const auto message = [](auto make) {
        try {
            make();
        } catch (const std::invalid_argument& ex) {
            return std::string(ex.what());
        }
        return std::string();
    };
    EXPECT_EQ(message([] { Branch("{\"@id\": "); }).rfind("Branch:", 0), 0u);
    EXPECT_EQ(message([] { Tag("{\"@id\": "); }).rfind("Tag:", 0), 0u);
    EXPECT_EQ(message([] { Commit("{\"@id\": "); }).rfind("Commit:", 0), 0u);
    EXPECT_EQ(message([] { Project("{\"@id\": "); }).rfind("Project:", 0), 0u);
}

TEST_F(RestVersioning, BranchRequestValueConstructorWithoutHeadWarnsOnce) {
    CerrCapture capture;
    BranchRequest first("b", nullptr, nullptr);
    BranchRequest second("c", nullptr, nullptr);
    EXPECT_EQ(countWarnings(capture.str()), 1u);
    BranchRequest withHead("d", nullptr, std::make_shared<Commit>(uuidOf(CommitId), "x", nullptr));
    EXPECT_EQ(json::parse(withHead.serializeToJson())["head"], reference(CommitId));
}

// ---------------------------------------------------------------------------------------------------------------------------
// BranchRequest, TagRequest, CommitRequest
// ---------------------------------------------------------------------------------------------------------------------------

TEST_F(RestVersioning, BranchRequestWithHeadDoesNotWarn) {
    CerrCapture capture;
    BranchRequest request(json{{"@type", "Branch"}, {"name", "b"}, {"head", reference(CommitId)}}.dump());
    EXPECT_EQ(request.getHead()->getId(), uuidOf(CommitId));
    EXPECT_EQ(countWarnings(capture.str()), 0u);
}

TEST_F(RestVersioning, BranchRequestWithoutHeadWarnsOnce) {
    CerrCapture capture;
    BranchRequest request(json{{"name", "b"}}.dump());
    BranchRequest second(json{{"name", "c"}, {"head", nullptr}}.dump());
    EXPECT_EQ(request.getHead(), nullptr);
    EXPECT_EQ(countWarnings(capture.str()), 1u);
    EXPECT_NE(capture.str().find("head"), std::string::npos);
}

TEST_F(RestVersioning, TagRequestRoundTrip) {
    CerrCapture capture;
    TagRequest request("v1", uuidOf(CommitId));
    const json written = json::parse(request.serializeToJson());
    EXPECT_EQ(written["@type"], "Tag");
    EXPECT_EQ(written["name"], "v1");
    EXPECT_EQ(written["taggedCommit"], reference(CommitId));
    EXPECT_FALSE(written.contains("@id"));

    TagRequest copy(request.serializeToJson());
    EXPECT_EQ(copy.getName(), "v1");
    ASSERT_NE(copy.getTaggedCommit(), nullptr);
    EXPECT_EQ(copy.getTaggedCommit()->getId(), uuidOf(CommitId));

    TagRequest fromCommit("v2", std::make_shared<Commit>(uuidOf(OtherCommitId), "d", nullptr));
    EXPECT_EQ(json::parse(fromCommit.serializeToJson())["taggedCommit"], reference(OtherCommitId));
    EXPECT_EQ(countWarnings(capture.str()), 0u);
}

TEST_F(RestVersioning, TagRequestStrictParsing) {
    EXPECT_THROW(TagRequest("["), std::invalid_argument);
    EXPECT_THROW(TagRequest("v1"), std::invalid_argument);
    EXPECT_THROW(TagRequest(json{{"taggedCommit", reference(CommitId)}}.dump()), std::invalid_argument);
    EXPECT_THROW(TagRequest(json{{"name", ""}, {"taggedCommit", reference(CommitId)}}.dump()), std::invalid_argument);
    EXPECT_THROW(TagRequest(json{{"name", "v"}}.dump()), std::invalid_argument);
    EXPECT_THROW(TagRequest(json{{"name", "v"}, {"taggedCommit", nullptr}}.dump()), std::invalid_argument);
    EXPECT_THROW(TagRequest(json{{"name", "v"}, {"taggedCommit", "abc"}}.dump()), std::invalid_argument);
    EXPECT_THROW(TagRequest(json{{"@type", "Branch"}, {"name", "v"}, {"taggedCommit", reference(CommitId)}}.dump()),
                 std::invalid_argument);
    EXPECT_NO_THROW(TagRequest(json{{"name", "v"}, {"taggedCommit", reference(CommitId)}}.dump()));
}

TEST_F(RestVersioning, CommitRequestWritesCommitTypeAndPreviousCommits) {
    CerrCapture capture;
    CommitRequest request("d", {}, {uuidOf(CommitId)});
    const json written = json::parse(request.serializeToJson());
    EXPECT_EQ(written["@type"], "Commit");
    EXPECT_EQ(written["description"], "d");
    EXPECT_EQ(written["previousCommits"][0], reference(CommitId));
    EXPECT_TRUE(written["change"].is_array());

    CommitRequest copy(request.serializeToJson());
    EXPECT_EQ(copy.description(), "d");
    ASSERT_EQ(copy.previousCommits().size(), 1u);
    EXPECT_EQ(copy.previousCommits()[0], uuidOf(CommitId));

    CommitRequest withoutPrevious("d2", {});
    EXPECT_FALSE(json::parse(withoutPrevious.serializeToJson()).contains("previousCommits"));
    EXPECT_EQ(countWarnings(capture.str()), 0u);
}

TEST_F(RestVersioning, CommitRequestOptionalDescriptionAndPlainText) {
    CerrCapture capture;
    CommitRequest noDescription(json{{"@type", "Commit"}, {"change", json::array()}}.dump());
    EXPECT_EQ(noDescription.description(), "");
    CommitRequest plain("just a description");
    EXPECT_EQ(plain.description(), "just a description");
    EXPECT_THROW(CommitRequest("{\"change\": 5}"), std::invalid_argument);
    EXPECT_THROW(CommitRequest("{broken"), std::invalid_argument);
    EXPECT_EQ(countWarnings(capture.str()), 0u);
}

TEST_F(RestVersioning, CommitRequestOldTypeIsReadWithWarning) {
    CerrCapture capture;
    CommitRequest request(json{{"@type", "CommitRequest"}, {"description", "d"}, {"change", json::array()},
                               {"previousCommit", json::array({reference(CommitId)})}}.dump());
    EXPECT_EQ(request.description(), "d");
    EXPECT_EQ(request.previousCommits().size(), 1u);
    EXPECT_EQ(countWarnings(capture.str()), 2u);
}

// ---------------------------------------------------------------------------------------------------------------------------
// Compatibility: deprecated APIs keep working and print exactly one warning.
// ---------------------------------------------------------------------------------------------------------------------------

#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable : 4996)
#else
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif

TEST_F(RestVersioning, DeprecatedProjectRequestConstructorAndGetter) {
    CerrCapture capture;
    ProjectRequest twoArguments("n", "d");
    ProjectRequest threeArguments("n", "d", "develop");
    ProjectRequest again("n", "d", "develop");
    EXPECT_EQ(twoArguments.defaultBranch(), "main");
    EXPECT_EQ(threeArguments.defaultBranch(), "develop");
    EXPECT_EQ(json::parse(threeArguments.serializeToJson())["defaultBranch"], "develop");
    EXPECT_FALSE(twoArguments.defaultBranchId().has_value());
    // one message for the constructor and one for the getter, both only once
    EXPECT_EQ(countWarnings(capture.str()), 2u);
}

TEST_F(RestVersioning, DeprecatedProjectRequestStringBranchInJson) {
    CerrCapture capture;
    ProjectRequest request("{\"@type\": \"Project\", \"defaultBranch\": \"main\", \"description\": \"d\", \"name\": \"n\"}");
    ProjectRequest second("{\"defaultBranch\": \"main\", \"name\": \"n\"}");
    EXPECT_EQ(countWarnings(capture.str()), 1u);
    EXPECT_FALSE(request.defaultBranchId().has_value());
    EXPECT_EQ(json::parse(request.serializeToJson())["defaultBranch"], "main");
}

TEST_F(RestVersioning, DeprecatedCommitGetters) {
    Commit commit(json{{"@id", OtherCommitId}, {"previousCommits", json::array({reference(CommitId)})}}.dump());
    {
        CerrCapture capture;
        EXPECT_EQ(commit.getPreviusCommits().size(), 1u);
        EXPECT_EQ(commit.getPreviusCommits().size(), 1u);
        EXPECT_EQ(countWarnings(capture.str()), 1u);
    }
    {
        CerrCapture capture;
        EXPECT_TRUE(commit.getDataVersion().empty());
        EXPECT_TRUE(commit.getDataVersion().empty());
        EXPECT_EQ(countWarnings(capture.str()), 1u);
    }
    {
        resetDeprecationWarningsForTesting();
        CerrCapture capture;
        EXPECT_TRUE(commit.getChange().empty());
        EXPECT_EQ(commit.getPreviousCommits().size(), 1u);
        EXPECT_EQ(countWarnings(capture.str()), 0u);
    }
}

TEST_F(RestVersioning, DeprecatedTagSetReferencedCommit) {
    Tag tag("v1");
    auto commit = std::make_shared<Commit>("c", nullptr);
    CerrCapture capture;
    tag.setReferencedCommit(commit);
    tag.setReferencedCommit(commit);
    EXPECT_EQ(tag.taggedCommit(), commit);
    EXPECT_EQ(countWarnings(capture.str()), 1u);
    EXPECT_EQ(json::parse(tag.serializeToJson())["taggedCommit"]["@id"], boost::uuids::to_string(commit->getId()));
}

TEST_F(RestVersioning, DeprecatedBranchSetReferencedCommit) {
    Branch branch("b");
    auto commit = std::make_shared<Commit>("c", nullptr);
    CerrCapture capture;
    branch.setReferencedCommit(commit);
    EXPECT_EQ(branch.getHead(), commit);
    EXPECT_EQ(countWarnings(capture.str()), 1u);
}

// ---------------------------------------------------------------------------------------------------------------------------
// Versioning logic: versionedData, createCommit, getCommitChange, diffCommits, merge (7.1.2, 7.2.3)
// ---------------------------------------------------------------------------------------------------------------------------

namespace {
    namespace V = SysMLv2::REST::Versioning;

    std::shared_ptr<KerML::Entities::Package> package(const std::string& name, const boost::uuids::uuid& id = boost::uuids::random_generator()()) {
        return std::make_shared<KerML::Entities::Package>(
            json{{"@id", boost::uuids::to_string(id)}, {"@type", "Package"}, {"declaredName", name}}.dump());
    }

    std::shared_ptr<KerML::Entities::Specialization> relationship(const std::vector<boost::uuids::uuid>& sources,
                                                                const std::vector<boost::uuids::uuid>& targets) {
        auto result = std::make_shared<KerML::Entities::Specialization>();
        std::vector<std::shared_ptr<KerML::Entities::Element>> sourceElements;
        std::vector<std::shared_ptr<KerML::Entities::Element>> targetElements;
        for (const auto& id : sources)
            sourceElements.push_back(std::make_shared<KerML::Entities::Element>(id));
        for (const auto& id : targets)
            targetElements.push_back(std::make_shared<KerML::Entities::Element>(id));
        result->setSource(sourceElements);
        result->setTarget(targetElements);
        return result;
    }

    std::shared_ptr<DataVersion> upsert(const std::shared_ptr<Data>& data) {
        return std::make_shared<DataVersion>(data);
    }

    std::shared_ptr<DataVersion> removal(const boost::uuids::uuid& id) {
        return std::make_shared<DataVersion>(nullptr, std::make_shared<DataIdentity>(id));
    }

    /** The commits of one project, the way a service keeps them. */
    class CommitStore {
    public:
        CommitStore() : TheProject(std::make_shared<Project>(json{{"@id", ProjectId}}.dump())) {}

        std::shared_ptr<Commit> commit(const std::vector<std::shared_ptr<Commit>>& previous,
                                       const std::vector<std::shared_ptr<DataVersion>>& change, const std::string& description = "") {
            auto created = V::prepareCommit(TheProject, description, change, previous, resolver(), &Cache);
            Commits[created->getId()] = created;
            return created;
        }

        V::CommitResolver resolver() const {
            return [this](const boost::uuids::uuid& id) -> std::shared_ptr<Commit> {
                const auto found = Commits.find(id);
                return found != Commits.end() ? found->second : nullptr;
            };
        }

        /** Replaces the commits by what is read from their JSON: previous commits and payload references are stubs then. */
        void reloadFromJson() {
            for (auto& [id, stored] : Commits)
                stored = std::make_shared<Commit>(stored->serializeToJson());
        }

        std::shared_ptr<Project> project() const { return TheProject; }
        std::shared_ptr<Commit> get(const std::shared_ptr<Commit>& commit) const { return Commits.at(commit->getId()); }
        V::VersionedDataCache* cache() { return &Cache; }
        std::size_t size() const { return Commits.size(); }

    private:
        std::shared_ptr<Project> TheProject;
        std::map<boost::uuids::uuid, std::shared_ptr<Commit>> Commits;
        V::VersionedDataCache Cache;
    };

    std::string nameOf(const V::VersionedData& state, const boost::uuids::uuid& id) {
        return json::parse(state.at(id)->getPayload()->serializeToJson())["declaredName"].get<std::string>();
    }

    std::set<boost::uuids::uuid> identitiesOf(const V::VersionedData& state) {
        std::set<boost::uuids::uuid> ids;
        for (const auto& [id, version] : state)
            ids.insert(id);
        return ids;
    }

    std::set<boost::uuids::uuid> identitiesOf(const std::vector<std::shared_ptr<DataVersion>>& versions) {
        std::set<boost::uuids::uuid> ids;
        for (const auto& version : versions)
            ids.insert(version->getId());
        return ids;
    }
}

TEST_F(RestVersioning, VersionedDataAccumulatesCommitsAndUpdates) {
    CommitStore store;
    const auto p1 = package("P1");
    const auto p2 = package("P2");
    const auto first = store.commit({}, {upsert(p1), upsert(p2)});
    const auto second = store.commit({first}, {upsert(package("P1 renamed", p1->getId()))});

    const auto stateOfFirst = V::versionedData(first, store.resolver());
    ASSERT_EQ(stateOfFirst->size(), 2u);
    const auto stateOfSecond = V::versionedData(second, store.resolver());
    ASSERT_EQ(stateOfSecond->size(), 2u);
    EXPECT_NE(stateOfSecond->find(p2->getId()), stateOfSecond->end());
    EXPECT_NE(stateOfFirst->at(p1->getId()), stateOfSecond->at(p1->getId()));
    // the earlier commit is untouched
    EXPECT_EQ(json::parse(stateOfFirst->at(p1->getId())->getPayload()->serializeToJson())["declaredName"], "P1");
    EXPECT_EQ(json::parse(stateOfSecond->at(p1->getId())->getPayload()->serializeToJson())["declaredName"], "P1 renamed");
    // the unchanged data is the very same version
    EXPECT_EQ(stateOfFirst->at(p2->getId()), stateOfSecond->at(p2->getId()));
}

TEST_F(RestVersioning, VersionedDataOmitsDeletedDataButKeepsItInEarlierCommits) {
    CommitStore store;
    const auto p1 = package("P1");
    const auto p2 = package("P2");
    const auto first = store.commit({}, {upsert(p1), upsert(p2)});
    const auto second = store.commit({first}, {removal(p1->getId())});
    EXPECT_EQ(identitiesOf(*V::versionedData(second, store.resolver())), std::set<boost::uuids::uuid>{p2->getId()});
    EXPECT_EQ(V::versionedData(first, store.resolver())->size(), 2u);

    // every listed DataVersion has a payload
    const auto stateOfSecond = V::versionedData(second, store.resolver());
    for (const auto& [id, version] : *stateOfSecond)
        EXPECT_NE(version->getPayload(), nullptr);

    // Data that was deleted can be created again
    const auto third = store.commit({second}, {upsert(package("P1 again", p1->getId()))});
    EXPECT_EQ(V::versionedData(third, store.resolver())->size(), 2u);
    EXPECT_EQ(V::classifyChange(third->getChange().front(), *V::versionedData(second, store.resolver())), ChangeType::CREATED);
}

TEST_F(RestVersioning, VersionedDataOfAMergeIsTheUnionOfTheParents) {
    CommitStore store;
    const auto shared = package("Shared");
    const auto left = package("Left");
    const auto right = package("Right");
    const auto root = store.commit({}, {upsert(shared)});
    const auto leftCommit = store.commit({root}, {upsert(left)});
    const auto rightCommit = store.commit({root}, {upsert(right)});
    // the parents agree on "shared" (the same version), so the merge commit does not have to list it
    const auto merge = store.commit({leftCommit, rightCommit}, {});
    const auto state = V::versionedData(merge, store.resolver());
    EXPECT_EQ(identitiesOf(*state), (std::set<boost::uuids::uuid>{shared->getId(), left->getId(), right->getId()}));
    EXPECT_EQ(merge->getPreviousCommits().size(), 2u);
}

TEST_F(RestVersioning, VersionedDataResolvesPreviousCommitsById) {
    CommitStore store;
    const auto p1 = package("P1");
    const auto p2 = package("P2");
    const auto first = store.commit({}, {upsert(p1)});
    const auto second = store.commit({first}, {upsert(p2)});
    const auto third = store.commit({second}, {removal(p1->getId())});
    store.reloadFromJson();

    // after the reload the previous commits are stubs without changes
    const auto reloaded = store.get(third);
    ASSERT_EQ(reloaded->getPreviousCommits().size(), 1u);
    EXPECT_TRUE(reloaded->getPreviousCommits().front()->getChange().empty());
    V::VersionedDataCache cache;
    EXPECT_EQ(identitiesOf(*V::versionedData(reloaded, store.resolver(), &cache)), std::set<boost::uuids::uuid>{p2->getId()});
    EXPECT_EQ(identitiesOf(*V::versionedData(store.get(second), store.resolver(), &cache)),
              (std::set<boost::uuids::uuid>{p1->getId(), p2->getId()}));
}

TEST_F(RestVersioning, VersionedDataUnknownPreviousCommitThrows) {
    CommitStore store;
    const auto first = store.commit({}, {upsert(package("P1"))});
    const auto second = store.commit({first}, {upsert(package("P2"))});
    store.reloadFromJson();
    const auto onlySecond = [&store, second](const boost::uuids::uuid& id) -> std::shared_ptr<Commit> {
        return id == second->getId() ? store.get(second) : nullptr;
    };
    EXPECT_THROW(V::versionedData(store.get(second), onlySecond), std::runtime_error);
}

TEST_F(RestVersioning, VersionedDataOfLongHistoryDoesNotOverflowTheStack) {
    CommitStore store;
    const auto data = package("Counter");
    auto head = store.commit({}, {upsert(data)});
    // The commits are linked by id (stubs), like commits that are read from a database. That also keeps the commits from
    // owning each other, which would make the destruction of such a long chain recursive.
    std::map<boost::uuids::uuid, std::shared_ptr<Commit>> commits{{head->getId(), head}};
    for (int index = 0; index < 10000; ++index) {
        const auto stub = std::make_shared<Commit>(json{{"@id", boost::uuids::to_string(head->getId())}}.dump());
        auto next = std::make_shared<Commit>("", store.project(), std::vector<std::shared_ptr<Commit>>{stub});
        next->addChange(upsert(package("Counter " + std::to_string(index), data->getId())));
        commits[next->getId()] = next;
        head = next;
    }
    const V::CommitResolver resolver = [&commits](const boost::uuids::uuid& id) -> std::shared_ptr<Commit> {
        const auto found = commits.find(id);
        return found != commits.end() ? found->second : nullptr;
    };
    V::VersionedDataCache cache;
    const auto state = V::versionedData(head, resolver, &cache);
    ASSERT_EQ(state->size(), 1u);
    EXPECT_EQ(json::parse(state->begin()->second->getPayload()->serializeToJson())["declaredName"], "Counter 9999");
    // only the requested commit is cached, the intermediate states are released
    EXPECT_EQ(cache.size(), 1u);
}

TEST_F(RestVersioning, VersionedDataIsCached) {
    CommitStore store;
    const auto first = store.commit({}, {upsert(package("P1"))});
    V::VersionedDataCache cache;
    const auto computed = V::versionedData(first, store.resolver(), &cache);
    EXPECT_EQ(cache.size(), 1u);
    EXPECT_EQ(V::versionedData(first, store.resolver(), &cache), computed);
    EXPECT_TRUE(V::versionedData(nullptr, store.resolver())->empty());
}

TEST_F(RestVersioning, VersionedDataDetectsCycles) {
    auto project = std::make_shared<Project>(json{{"@id", ProjectId}}.dump());
    const auto stubOfFirst = std::make_shared<Commit>(ref(CommitId));
    const auto stubOfSecond = std::make_shared<Commit>(ref(OtherCommitId));
    auto first = std::make_shared<Commit>(uuidOf(CommitId), "", project, std::vector<std::shared_ptr<Commit>>{stubOfSecond});
    auto second = std::make_shared<Commit>(uuidOf(OtherCommitId), "", project, std::vector<std::shared_ptr<Commit>>{stubOfFirst});
    const V::CommitResolver resolver = [&](const boost::uuids::uuid& id) -> std::shared_ptr<Commit> {
        if (id == uuidOf(CommitId))
            return first;
        return id == uuidOf(OtherCommitId) ? second : nullptr;
    };
    EXPECT_THROW(V::versionedData(first, resolver), std::runtime_error);
}

TEST_F(RestVersioning, CommitSetCreated) {
    Commit commit("", nullptr);
    const auto time = std::chrono::system_clock::time_point{} + std::chrono::seconds(1700000000);
    commit.setCreated(time);
    EXPECT_EQ(commit.getCreated(), time);
    EXPECT_TRUE(json::parse(commit.serializeToJson())["created"].get<std::string>().rfind("2023-11-14T22:13:20", 0) == 0);
}

TEST_F(RestVersioning, PrepareCommitGivesEveryChangeAnOwnIdAndTheCommit) {
    CommitStore store;
    const auto p1 = package("P1");
    // a request has no id for its DataVersion
    const auto requested = std::make_shared<DataVersion>(json{{"@type", "DataVersion"}, {"payload", json::parse(p1->serializeToJson())}}.dump());
    ASSERT_TRUE(requested->getVersionId().is_nil());
    const auto commit = store.commit({}, {requested});

    ASSERT_EQ(commit->getChange().size(), 1u);
    const auto version = commit->getChange().front();
    EXPECT_FALSE(version->getVersionId().is_nil());
    EXPECT_NE(version->getVersionId(), p1->getId());
    EXPECT_EQ(version->getId(), p1->getId());
    ASSERT_NE(version->getCommit(), nullptr);
    EXPECT_EQ(version->getCommit()->getId(), commit->getId());
    // the request is not modified
    EXPECT_TRUE(requested->getVersionId().is_nil());
    EXPECT_EQ(requested->getCommit(), nullptr);

    const json written = json::parse(commit->serializeToJson());
    ASSERT_EQ(written["change"].size(), 1u);
    EXPECT_EQ(written["change"][0]["@id"], boost::uuids::to_string(version->getVersionId()));
    EXPECT_EQ(written["change"][0]["commit"], reference(boost::uuids::to_string(commit->getId())));
    EXPECT_EQ(written["change"][0]["identity"]["@id"], boost::uuids::to_string(p1->getId()));
    EXPECT_EQ(written["owningProject"], reference(ProjectId));

    // a deletion has an id as well
    const auto second = store.commit({commit}, {removal(p1->getId())});
    EXPECT_FALSE(second->getChange().front()->getVersionId().is_nil());
    EXPECT_TRUE(json::parse(second->serializeToJson())["change"][0]["payload"].is_null());
}

TEST_F(RestVersioning, PrepareCommitRejectsInvalidChanges) {
    CommitStore store;
    const auto p1 = package("P1");
    const auto first = store.commit({}, {upsert(p1)});

    // deleting Data that does not exist
    EXPECT_THROW(store.commit({first}, {removal(uuidOf(DataId))}), V::InvalidCommitException);
    EXPECT_THROW(store.commit({}, {removal(p1->getId())}), V::InvalidCommitException);
    // the same identity twice
    EXPECT_THROW(store.commit({first}, {upsert(package("a", p1->getId())), upsert(package("b", p1->getId()))}), V::InvalidCommitException);
    EXPECT_THROW(store.commit({first}, {upsert(package("a", p1->getId())), removal(p1->getId())}), V::InvalidCommitException);
    // a change without data
    EXPECT_THROW(store.commit({first}, {nullptr}), V::InvalidCommitException);
    // an unknown previous commit
    const auto unknown = std::make_shared<Commit>(ref(OtherCommitId));
    EXPECT_THROW(store.commit({unknown}, {upsert(package("x"))}), V::InvalidCommitException);
    // a previous commit of another project
    auto foreignProject = std::make_shared<Project>(json{{"@id", BranchId}}.dump());
    auto foreign = std::make_shared<Commit>("", foreignProject);
    const V::CommitResolver foreignResolver = [&foreign](const boost::uuids::uuid&) { return foreign; };
    EXPECT_THROW(V::prepareCommit(store.project(), "", {upsert(package("x"))}, {foreign}, foreignResolver), V::InvalidCommitException);
    EXPECT_THROW(V::prepareCommit(nullptr, "", {}, {}, store.resolver()), V::InvalidCommitException);
    // it is an std::invalid_argument, so callers that map it to "bad request" keep working
    EXPECT_THROW(store.commit({first}, {removal(uuidOf(DataId))}), std::invalid_argument);
    // nothing was stored by the failed attempts
    EXPECT_EQ(store.size(), 1u);
}

TEST_F(RestVersioning, PrepareCommitAcceptsEmptyChange) {
    CommitStore store;
    const auto first = store.commit({}, {upsert(package("P1"))});
    const auto second = store.commit({first}, {});
    EXPECT_TRUE(second->getChange().empty());
    EXPECT_EQ(V::versionedData(second, store.resolver())->size(), 1u);
}

TEST_F(RestVersioning, PrepareCommitRemovesDuplicatePreviousCommits) {
    CommitStore store;
    const auto first = store.commit({}, {upsert(package("P1"))});
    const auto second = store.commit({first, first, std::make_shared<Commit>(json{{"@id", boost::uuids::to_string(first->getId())}}.dump())}, {});
    ASSERT_EQ(second->getPreviousCommits().size(), 1u);
    EXPECT_EQ(second->getPreviousCommits().front()->getId(), first->getId());
}

TEST_F(RestVersioning, PrepareCommitCreatedIsStrictlyNewerThanThePreviousCommits) {
    CommitStore store;
    auto previous = store.commit({}, {upsert(package("P0"))});
    for (int index = 0; index < 200; ++index) {
        const auto next = store.commit({previous}, {upsert(package("P" + std::to_string(index)))});
        // compared as written to JSON: microseconds
        EXPECT_GT(Utilities::toIso8601(next->getCreated()), Utilities::toIso8601(previous->getCreated()));
        previous = next;
    }

    // a previous commit from the future (clock skew) is still older
    auto future = std::make_shared<Commit>("", store.project());
    future->setCreated(std::chrono::system_clock::now() + std::chrono::hours(24));
    const V::CommitResolver resolver = [&future](const boost::uuids::uuid&) { return future; };
    const auto after = V::prepareCommit(store.project(), "", {upsert(package("x"))}, {future}, resolver);
    EXPECT_GT(after->getCreated(), future->getCreated());
}

TEST_F(RestVersioning, PrepareCommitDeletionOfAnElementDeletesIncomingRelationships) {
    CommitStore store;
    const auto a = package("A");
    const auto b = package("B");
    const auto c = package("C");
    const auto aToB = relationship({a->getId()}, {b->getId()});
    const auto cToA = relationship({c->getId()}, {a->getId()});
    const auto bToC = relationship({b->getId()}, {c->getId()});
    // a relationship can end at a relationship
    const auto onRelationship = relationship({c->getId()}, {cToA->getId()});
    const auto first = store.commit({}, {upsert(a), upsert(b), upsert(c), upsert(aToB), upsert(cToA), upsert(bToC), upsert(onRelationship)});

    const auto second = store.commit({first}, {removal(a->getId())});
    EXPECT_EQ(identitiesOf(second->getChange()),
              (std::set<boost::uuids::uuid>{a->getId(), aToB->getId(), cToA->getId(), onRelationship->getId()}));
    for (const auto& version : second->getChange())
        EXPECT_EQ(version->getPayload(), nullptr);
    EXPECT_EQ(identitiesOf(*V::versionedData(second, store.resolver())),
              (std::set<boost::uuids::uuid>{b->getId(), c->getId(), bToC->getId()}));
    // the deleted data stays reachable in the earlier commit
    EXPECT_EQ(V::versionedData(first, store.resolver())->size(), 7u);

    // the cascade is also found if the base state was read from JSON
    store.reloadFromJson();
    const auto third = store.commit({store.get(second)}, {removal(b->getId())});
    EXPECT_EQ(identitiesOf(third->getChange()), (std::set<boost::uuids::uuid>{b->getId(), bToC->getId()}));
}

TEST_F(RestVersioning, PrepareCommitCascadeLeavesRelationshipsTheChangeLists) {
    CommitStore store;
    const auto a = package("A");
    const auto b = package("B");
    const auto aToB = relationship({a->getId()}, {b->getId()});
    const auto first = store.commit({}, {upsert(a), upsert(b), upsert(aToB)});
    // the client deletes the relationship itself: it is listed once
    const auto second = store.commit({first}, {removal(aToB->getId()), removal(a->getId())});
    EXPECT_EQ(second->getChange().size(), 2u);
    // the client keeps a relationship (an update) in the same commit: its version is the client's
    const auto movedRelationship = relationship({b->getId()}, {b->getId()});
    const auto third = store.commit({first}, {removal(b->getId()), upsert(movedRelationship)});
    EXPECT_EQ(third->getChange().size(), 3u); // b, aToB (ends at b), movedRelationship (as sent)
}

TEST_F(RestVersioning, GetCommitChangeClassifiesCreatedUpdatedDeleted) {
    CommitStore store;
    const auto p1 = package("P1");
    const auto p2 = package("P2");
    const auto p3 = package("P3");
    const auto first = store.commit({}, {upsert(p1), upsert(p2)});
    const auto second = store.commit({first}, {upsert(package("P1 renamed", p1->getId())), removal(p2->getId()), upsert(p3)});

    const auto all = V::getCommitChange(second, {}, store.resolver(), store.cache());
    EXPECT_EQ(all.size(), 3u);
    EXPECT_EQ(V::getCommitChange(first, {}, store.resolver()).size(), 2u);
    const auto created = V::getCommitChange(second, {CREATED}, store.resolver(), store.cache());
    ASSERT_EQ(created.size(), 1u);
    EXPECT_EQ(created[0]->getId(), p3->getId());
    const auto updated = V::getCommitChange(second, {UPDATED}, store.resolver());
    ASSERT_EQ(updated.size(), 1u);
    EXPECT_EQ(updated[0]->getId(), p1->getId());
    const auto deleted = V::getCommitChange(second, {DELETED}, store.resolver());
    ASSERT_EQ(deleted.size(), 1u);
    EXPECT_EQ(deleted[0]->getId(), p2->getId());
    EXPECT_EQ(V::getCommitChange(second, {CREATED, UPDATED}, store.resolver()).size(), 2u);
    EXPECT_EQ(V::getCommitChange(first, {UPDATED, DELETED}, store.resolver()).size(), 0u);
    EXPECT_TRUE(V::getCommitChange(nullptr, {}, store.resolver()).empty());

    // also for a commit that was read from JSON
    store.reloadFromJson();
    EXPECT_EQ(V::getCommitChange(store.get(second), {DELETED}, store.resolver()).size(), 1u);
}

TEST_F(RestVersioning, DiffCommitsReportsCreatedUpdatedDeleted) {
    CommitStore store;
    const auto kept = package("Kept");
    const auto changed = package("Changed");
    const auto removed = package("Removed");
    const auto base = store.commit({}, {upsert(kept), upsert(changed), upsert(removed)});
    const auto added = package("Added");
    const auto compare = store.commit({base}, {upsert(package("Changed 2", changed->getId())), removal(removed->getId()), upsert(added)});

    const auto diff = V::diffCommits(base, compare, {}, store.resolver(), store.cache());
    ASSERT_EQ(diff.size(), 3u);
    std::map<boost::uuids::uuid, std::shared_ptr<DataDifference>> byIdentity;
    for (const auto& difference : diff) {
        const auto& version = difference->baseData() != nullptr ? difference->baseData() : difference->compareData();
        byIdentity[version->getId()] = difference;
    }
    EXPECT_EQ(byIdentity.at(added->getId())->baseData(), nullptr);
    EXPECT_NE(byIdentity.at(added->getId())->compareData(), nullptr);
    EXPECT_NE(byIdentity.at(removed->getId())->baseData(), nullptr);
    EXPECT_EQ(byIdentity.at(removed->getId())->compareData(), nullptr);
    EXPECT_NE(byIdentity.at(changed->getId())->baseData(), nullptr);
    EXPECT_NE(byIdentity.at(changed->getId())->compareData(), nullptr);
    EXPECT_EQ(byIdentity.count(kept->getId()), 0u);

    EXPECT_EQ(V::diffCommits(base, compare, {CREATED}, store.resolver()).size(), 1u);
    EXPECT_EQ(V::diffCommits(base, compare, {UPDATED}, store.resolver()).size(), 1u);
    EXPECT_EQ(V::diffCommits(base, compare, {DELETED}, store.resolver()).size(), 1u);
    EXPECT_EQ(V::diffCommits(base, compare, {CREATED, UPDATED}, store.resolver()).size(), 2u);
    // the other direction swaps created and deleted
    const auto reverse = V::diffCommits(compare, base, {CREATED}, store.resolver());
    ASSERT_EQ(reverse.size(), 1u);
    EXPECT_EQ(reverse[0]->compareData()->getId(), removed->getId());
    EXPECT_TRUE(V::diffCommits(base, base, {}, store.resolver()).empty());

    // a new version with the same payload is not a difference
    const auto same = store.commit({base}, {upsert(package("Kept", kept->getId()))});
    EXPECT_TRUE(V::diffCommits(base, same, {}, store.resolver()).empty());
    // the differences serialize
    EXPECT_TRUE(json::parse(diff.front()->serializeToJson()).contains("compareData"));
}

TEST_F(RestVersioning, MergeWithoutConflictTakesTheChangesOfBothSides) {
    CommitStore store;
    const auto p1 = package("P1");
    const auto p2 = package("P2");
    const auto p3 = package("P3");
    const auto root = store.commit({}, {upsert(p1), upsert(p2), upsert(p3)});
    const auto head = store.commit({root}, {upsert(package("P1 head", p1->getId())), upsert(package("Head only"))});
    const auto other = store.commit({root}, {upsert(package("P2 other", p2->getId())), removal(p3->getId())});

    const auto analysis = V::analyzeMerge(head, {other}, {}, store.resolver(), store.cache());
    EXPECT_TRUE(analysis.conflicts.empty());
    ASSERT_NE(analysis.commonAncestor, nullptr);
    EXPECT_EQ(analysis.commonAncestor->getId(), root->getId());

    const auto merge = store.commit({head, other}, analysis.changes);
    const auto state = *V::versionedData(merge, store.resolver());
    EXPECT_EQ(state.size(), 3u); // P1 head, P2 other, Head only; P3 is deleted
    EXPECT_EQ(nameOf(state, p1->getId()), "P1 head");
    EXPECT_EQ(nameOf(state, p2->getId()), "P2 other");
    EXPECT_EQ(state.count(p3->getId()), 0u);
    // The merge commit lists what differs from a parent (7.1.2): P1 (the version of "other" is not part of the result),
    // P2 (differs from the head) and P3 (deleted). "Head only" is the same in the head and unknown to "other".
    EXPECT_EQ(identitiesOf(merge->getChange()), (std::set<boost::uuids::uuid>{p1->getId(), p2->getId(), p3->getId()}));
    EXPECT_EQ(merge->getPreviousCommits().size(), 2u);
}

TEST_F(RestVersioning, MergeConflictIsReportedAndResolvedByPayload) {
    CommitStore store;
    const auto p1 = package("P1");
    const auto p2 = package("P2");
    const auto root = store.commit({}, {upsert(p1), upsert(p2)});
    const auto head = store.commit({root}, {upsert(package("P1 head", p1->getId())), upsert(package("P2 head", p2->getId()))});
    const auto other = store.commit({root}, {upsert(package("P1 other", p1->getId())), removal(p2->getId())});

    const auto conflicting = V::analyzeMerge(head, {other}, {}, store.resolver());
    ASSERT_EQ(conflicting.conflicts.size(), 2u);
    std::set<boost::uuids::uuid> conflictIds;
    for (const auto& identity : conflicting.conflicts)
        conflictIds.insert(identity->getId());
    EXPECT_EQ(conflictIds, (std::set<boost::uuids::uuid>{p1->getId(), p2->getId()}));
    EXPECT_TRUE(conflicting.changes.empty());

    // a resolution for one of them is not enough
    const auto partly = V::analyzeMerge(head, {other}, {package("P1 resolved", p1->getId())}, store.resolver());
    ASSERT_EQ(partly.conflicts.size(), 1u);
    EXPECT_EQ(partly.conflicts[0]->getId(), p2->getId());

    const auto resolved = V::analyzeMerge(head, {other}, {package("P1 resolved", p1->getId()), package("P2 resolved", p2->getId())},
                                          store.resolver());
    EXPECT_TRUE(resolved.conflicts.empty());
    const auto merge = store.commit({head, other}, resolved.changes);
    const auto state = *V::versionedData(merge, store.resolver());
    EXPECT_EQ(nameOf(state, p1->getId()), "P1 resolved");
    EXPECT_EQ(nameOf(state, p2->getId()), "P2 resolved");
}

TEST_F(RestVersioning, MergeOfTheSameChangeOnBothSidesIsNoConflict) {
    CommitStore store;
    const auto p1 = package("P1");
    const auto root = store.commit({}, {upsert(p1)});
    const auto head = store.commit({root}, {upsert(package("Same", p1->getId()))});
    const auto other = store.commit({root}, {upsert(package("Same", p1->getId()))});
    const auto analysis = V::analyzeMerge(head, {other}, {}, store.resolver());
    EXPECT_TRUE(analysis.conflicts.empty());
    const auto merge = store.commit({head, other}, analysis.changes);
    EXPECT_EQ(nameOf(*V::versionedData(merge, store.resolver()), p1->getId()), "Same");

    // deleted on both sides
    const auto headDeleted = store.commit({root}, {removal(p1->getId())});
    const auto otherDeleted = store.commit({root}, {removal(p1->getId())});
    EXPECT_TRUE(V::analyzeMerge(headDeleted, {otherDeleted}, {}, store.resolver()).conflicts.empty());
}

TEST_F(RestVersioning, MergeFastForwardAndMergeOfAnAncestor) {
    CommitStore store;
    const auto p1 = package("P1");
    const auto root = store.commit({}, {upsert(p1)});
    const auto ahead = store.commit({root}, {upsert(package("P2")), upsert(package("P1 ahead", p1->getId()))});

    // the head is an ancestor of the commit: the result is the state of the commit
    const auto forward = V::analyzeMerge(root, {ahead}, {}, store.resolver());
    EXPECT_TRUE(forward.conflicts.empty());
    EXPECT_EQ(forward.commonAncestor->getId(), root->getId());
    const auto merge = store.commit({root, ahead}, forward.changes);
    EXPECT_EQ(V::diffCommits(ahead, merge, {}, store.resolver()).size(), 0u);

    // the commit is an ancestor of the head: nothing to take over
    const auto nothing = V::analyzeMerge(ahead, {root}, {}, store.resolver());
    EXPECT_TRUE(nothing.conflicts.empty());
    EXPECT_EQ(nothing.commonAncestor->getId(), root->getId());
    const auto mergeNothing = store.commit({ahead, root}, nothing.changes);
    EXPECT_EQ(V::diffCommits(ahead, mergeNothing, {}, store.resolver()).size(), 0u);
}

TEST_F(RestVersioning, MergeIntoABranchWithoutHeadAndOfUnrelatedHistories) {
    CommitStore store;
    const auto p1 = package("P1");
    const auto p2 = package("P2");
    const auto first = store.commit({}, {upsert(p1)});
    const auto unrelated = store.commit({}, {upsert(p2)});

    const auto intoEmpty = V::analyzeMerge(nullptr, {first}, {}, store.resolver());
    EXPECT_TRUE(intoEmpty.conflicts.empty());
    EXPECT_EQ(intoEmpty.commonAncestor, nullptr);
    const auto mergeIntoEmpty = store.commit({first}, intoEmpty.changes);
    EXPECT_EQ(V::diffCommits(first, mergeIntoEmpty, {}, store.resolver()).size(), 0u);

    const auto both = V::analyzeMerge(first, {unrelated}, {}, store.resolver());
    EXPECT_TRUE(both.conflicts.empty());
    EXPECT_EQ(both.commonAncestor, nullptr);
    const auto merge = store.commit({first, unrelated}, both.changes);
    EXPECT_EQ(V::versionedData(merge, store.resolver())->size(), 2u);

    // unrelated histories that created the same identity differently conflict
    const auto otherP1 = store.commit({}, {upsert(package("P1 elsewhere", p1->getId()))});
    EXPECT_EQ(V::analyzeMerge(first, {otherP1}, {}, store.resolver()).conflicts.size(), 1u);
}

TEST_F(RestVersioning, MergeCommonAncestorIsTheNewestOne) {
    CommitStore store;
    const auto root = store.commit({}, {upsert(package("P1"))});
    const auto middle = store.commit({root}, {upsert(package("P2"))});
    const auto head = store.commit({middle}, {upsert(package("P3"))});
    const auto other = store.commit({middle}, {upsert(package("P4"))});
    EXPECT_EQ(V::analyzeMerge(head, {other}, {}, store.resolver()).commonAncestor->getId(), middle->getId());

    const auto ancestors = V::ancestorsOf(head, store.resolver());
    EXPECT_EQ(ancestors.size(), 3u);
    EXPECT_TRUE(V::ancestorsOf(nullptr, store.resolver()).empty());
}


TEST_F(RestVersioning, RelationshipEndsAreReadFromTheJson) {
    const auto source = boost::uuids::random_generator()();
    const auto target = boost::uuids::random_generator()();
    const auto link = relationship({source}, {target});
    const auto ends = V::relationshipEnds(link);
    EXPECT_TRUE(ends.isRelationship);
    EXPECT_EQ(ends.source, std::vector<boost::uuids::uuid>{source});
    EXPECT_EQ(ends.target, std::vector<boost::uuids::uuid>{target});

    // a payload that was read from JSON keeps its references as ids, whatever source() says
    const auto read = std::make_shared<KerML::Entities::Specialization>(link->serializeToJson());
    const auto readEnds = V::relationshipEnds(read);
    EXPECT_TRUE(readEnds.isRelationship);
    EXPECT_EQ(readEnds.source, std::vector<boost::uuids::uuid>{source});
    EXPECT_EQ(readEnds.target, std::vector<boost::uuids::uuid>{target});

    EXPECT_FALSE(V::relationshipEnds(package("P")).isRelationship);
    EXPECT_FALSE(V::relationshipEnds(nullptr).isRelationship);
}

TEST_F(RestVersioning, DeclaresOwnerReadsOwnerAndOwningRelationship) {
    EXPECT_FALSE(V::declaresOwner(package("Root")));
    EXPECT_FALSE(V::declaresOwner(nullptr));
    const auto ownerId = boost::uuids::to_string(boost::uuids::random_generator()());
    const auto owned = std::make_shared<KerML::Entities::Package>(
        json{{"@id", ownerId}, {"@type", "Package"}, {"declaredName", "Child"}, {"owner", reference(ownerId)}}.dump());
    EXPECT_TRUE(V::declaresOwner(owned));
    const auto viaRelationship = std::make_shared<KerML::Entities::Package>(
        json{{"@id", ownerId}, {"@type", "Package"}, {"owningRelationship", reference(ownerId)}}.dump());
    EXPECT_TRUE(V::declaresOwner(viaRelationship));
    const auto nullOwner = std::make_shared<KerML::Entities::Package>(
        json{{"@id", ownerId}, {"@type", "Package"}, {"owner", nullptr}}.dump());
    EXPECT_FALSE(V::declaresOwner(nullOwner));
}

TEST_F(RestVersioning, DeletionOfAPackageTakesItsWholeSubtreeWithIt) {
    CommitStore store;
    const auto owning = [](const boost::uuids::uuid& owner, const boost::uuids::uuid& member) {
        return std::make_shared<KerML::Entities::OwningMembership>(json{
            {"@id", boost::uuids::to_string(boost::uuids::random_generator()())}, {"@type", "OwningMembership"},
            {"source", json::array({reference(boost::uuids::to_string(owner))})},
            {"target", json::array({reference(boost::uuids::to_string(member))})},
            {"owningRelatedElement", reference(boost::uuids::to_string(owner))},
            {"ownedRelatedElement", json::array({reference(boost::uuids::to_string(member))})}}.dump());
    };
    // root -> m1 -> child -> m2 -> grandchild; an outside relationship ends at the grandchild; "other" has nothing to do with it
    const auto root = package("Root");
    const auto child = package("Child");
    const auto grandchild = package("Grandchild");
    const auto other = package("Other");
    const auto m1 = owning(root->getId(), child->getId());
    const auto m2 = owning(child->getId(), grandchild->getId());
    const auto outside = relationship({other->getId()}, {grandchild->getId()});
    const auto first = store.commit({}, {upsert(root), upsert(child), upsert(grandchild), upsert(other), upsert(m1), upsert(m2), upsert(outside)});

    const auto second = store.commit({first}, {removal(root->getId())});
    EXPECT_EQ(identitiesOf(second->getChange()),
              (std::set<boost::uuids::uuid>{root->getId(), m1->getId(), child->getId(), m2->getId(), grandchild->getId(), outside->getId()}));
    for (const auto& version : second->getChange())
        EXPECT_EQ(version->getPayload(), nullptr);
    EXPECT_EQ(identitiesOf(*V::versionedData(second, store.resolver())), std::set<boost::uuids::uuid>{other->getId()});

    // deleting the membership alone deletes what it owns (and what hangs on that), but not its owner
    store.reloadFromJson();
    const auto third = store.commit({store.get(first)}, {removal(m1->getId())});
    EXPECT_EQ(identitiesOf(third->getChange()),
              (std::set<boost::uuids::uuid>{m1->getId(), child->getId(), m2->getId(), grandchild->getId(), outside->getId()}));
    EXPECT_EQ(identitiesOf(*V::versionedData(third, store.resolver())), (std::set<boost::uuids::uuid>{root->getId(), other->getId()}));

    // what the client lists itself is left as the client sent it
    const auto fourth = store.commit({store.get(first)}, {removal(root->getId()), upsert(package("Child kept", child->getId()))});
    // root and its membership go, the child stays with the version the client sent, and so does everything below it
    EXPECT_EQ(identitiesOf(fourth->getChange()), (std::set<boost::uuids::uuid>{root->getId(), m1->getId(), child->getId()}));
    EXPECT_EQ(identitiesOf(*V::versionedData(fourth, store.resolver())).count(grandchild->getId()), 1u);
    EXPECT_EQ(nameOf(*V::versionedData(fourth, store.resolver()), child->getId()), "Child kept");
}

TEST_F(RestVersioning, RedundantPreviousCommitsAreRemovedAndNothingComesBack) {
    CommitStore store;
    const auto p1 = package("P1");
    const auto p2 = package("P2");
    const auto a = store.commit({}, {upsert(p1), upsert(p2)});
    const auto b = store.commit({a}, {upsert(package("P1 changed", p1->getId()))});
    const auto c = store.commit({b}, {removal(p2->getId())});

    // a is an ancestor of c: with both as parents the union would bring P2 back and the old P1 as well
    const auto d = store.commit({c, a}, {upsert(package("P3"))});
    ASSERT_EQ(d->getPreviousCommits().size(), 1u);
    EXPECT_EQ(d->getPreviousCommits().front()->getId(), c->getId());
    const auto state = *V::versionedData(d, store.resolver());
    EXPECT_EQ(state.count(p2->getId()), 0u);
    EXPECT_EQ(nameOf(state, p1->getId()), "P1 changed");
    EXPECT_EQ(state.size(), 2u);

    // the order does not matter
    const auto e = store.commit({a, c}, {upsert(package("P4"))});
    ASSERT_EQ(e->getPreviousCommits().size(), 1u);
    EXPECT_EQ(e->getPreviousCommits().front()->getId(), c->getId());
    EXPECT_EQ(V::versionedData(e, store.resolver())->count(p2->getId()), 0u);
}

TEST_F(RestVersioning, DivergingPreviousCommitsAreResolvedByTheCommit) {
    CommitStore store;
    const auto p1 = package("P1");
    const auto p2 = package("P2");
    const auto p3 = package("P3");
    const auto root = store.commit({}, {upsert(p1), upsert(p2), upsert(p3)});
    const auto left = store.commit({root}, {removal(p2->getId()), upsert(package("P3 left", p3->getId()))});
    const auto right = store.commit({root}, {upsert(package("P1 right", p1->getId()))});

    // the client's change does not mention the merged data: the commit takes over what the merge gives
    const auto p4 = package("P4");
    const auto merge = store.commit({left, right}, {upsert(p4)});
    EXPECT_EQ(merge->getPreviousCommits().size(), 2u);
    const auto state = *V::versionedData(merge, store.resolver());
    EXPECT_EQ(state.size(), 3u);
    EXPECT_EQ(state.count(p2->getId()), 0u);
    EXPECT_EQ(nameOf(state, p1->getId()), "P1 right");
    EXPECT_EQ(nameOf(state, p3->getId()), "P3 left");
    // The change has the client's data and what the plain union of the parents would get wrong: P2, which the left parent deleted,
    // and P1, which the right parent changed (the first parent's version would win). P3 is not listed, because the union already
    // gives the left parent's version.
    EXPECT_EQ(identitiesOf(merge->getChange()),
              (std::set<boost::uuids::uuid>{p1->getId(), p2->getId(), p4->getId()}));
}

TEST_F(RestVersioning, DivergingPreviousCommitsWithAConflictNeedAResolution) {
    CommitStore store;
    const auto p1 = package("P1");
    const auto root = store.commit({}, {upsert(p1)});
    const auto left = store.commit({root}, {upsert(package("P1 left", p1->getId()))});
    const auto right = store.commit({root}, {upsert(package("P1 right", p1->getId()))});

    EXPECT_THROW(store.commit({left, right}, {upsert(package("P2"))}), V::InvalidCommitException);
    const auto resolved = store.commit({left, right}, {upsert(package("P1 resolved", p1->getId()))});
    EXPECT_EQ(nameOf(*V::versionedData(resolved, store.resolver()), p1->getId()), "P1 resolved");
    // a deletion resolves it as well
    const auto deleted = store.commit({left, right}, {removal(p1->getId())});
    EXPECT_TRUE(V::versionedData(deleted, store.resolver())->empty());
    // only the commits that were stored: the failed attempt left nothing behind
    EXPECT_EQ(store.size(), 5u);
}

#if defined(_MSC_VER)
#pragma warning(pop)
#else
#pragma GCC diagnostic pop
#endif
