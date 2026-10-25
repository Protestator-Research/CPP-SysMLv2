//
// Tests of the versioning entities of the REST API (AP 1): Project, ProjectRequest, Commit, CommitReference, Branch, Tag,
// BranchRequest, TagRequest and the parts of CommitRequest that do not depend on DataVersion. Contains the Annex B examples,
// round trips and the compatibility tests of the deprecated APIs and JSON formats.
//

#include <gtest/gtest.h>
#include <chrono>
#include <memory>
#include <stdexcept>
#include <string>
#include <nlohmann/json.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include "support/CerrCapture.h"
#include <sysmlv2/rest/Deprecation.h>
#include <sysmlv2/rest/entities/Branch.h>
#include <sysmlv2/rest/entities/BranchRequest.h>
#include <sysmlv2/rest/entities/Commit.h>
#include <sysmlv2/rest/entities/CommitRequest.h>
#include <sysmlv2/rest/entities/Project.h>
#include <sysmlv2/rest/entities/ProjectRequest.h>
#include <sysmlv2/rest/entities/Tag.h>
#include <sysmlv2/rest/entities/TagRequest.h>

using namespace SysMLv2::REST;
using nlohmann::json;

namespace {
    const std::string ProjectId = "6e701bf8-7793-49de-9b0e-2f43376edabf";
    const std::string BranchId = "7eea9bd1-1082-4521-8bb2-d94202c8dd63";
    const std::string CommitId = "c4fc0b1e-2d3a-4b5c-8d6e-7f8091a2b3c4";
    const std::string OtherCommitId = "0f1e2d3c-4b5a-4968-8776-655443322110";

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

#if defined(_MSC_VER)
#pragma warning(pop)
#else
#pragma GCC diagnostic pop
#endif
