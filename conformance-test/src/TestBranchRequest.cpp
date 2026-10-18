//
// Tests of SysMLv2::REST::BranchRequest (serialization and deserialization).
//

#include <gtest/gtest.h>
#include <nlohmann/json.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <memory>
#include <stdexcept>
#include <string>

#include <sysmlv2/rest/entities/BranchRequest.h>
#include <sysmlv2/rest/entities/Commit.h>
#include <sysmlv2/rest/entities/Project.h>

namespace {
    const std::string HeadId = "c4fc0b1e-2d3a-4b5c-8d6e-7f8091a2b3c4";
    const std::string ProjectId = "0f1e2d3c-4b5a-4968-8776-655443322110";

    std::shared_ptr<SysMLv2::REST::Commit> makeCommit(const std::string &id) {
        return std::make_shared<SysMLv2::REST::Commit>(nlohmann::json{{"@id", id}}.dump());
    }

    std::shared_ptr<SysMLv2::REST::Project> makeProject(const std::string &id) {
        return std::make_shared<SysMLv2::REST::Project>(nlohmann::json{{"@id", id}}.dump());
    }
}

TEST(TestBranchRequest, RoundTrip) {
    SysMLv2::REST::BranchRequest original("round-trip", makeProject(ProjectId), makeCommit(HeadId));
    const auto json = nlohmann::json::parse(original.serializeToJson());
    EXPECT_EQ(json["@type"], "Branch");
    EXPECT_EQ(json["name"], "round-trip");
    EXPECT_EQ(json["head"]["@id"], HeadId);
    EXPECT_EQ(json["owningProject"]["@id"], ProjectId);

    SysMLv2::REST::BranchRequest copy(original.serializeToJson());
    EXPECT_EQ(copy.getName(), "round-trip");
    ASSERT_NE(copy.getHead(), nullptr);
    EXPECT_EQ(boost::uuids::to_string(copy.getHead()->getId()), HeadId);
    ASSERT_NE(copy.getProject(), nullptr);
    EXPECT_EQ(boost::uuids::to_string(copy.getProject()->getId()), ProjectId);
}

TEST(TestBranchRequest, ClientJson) {
    SysMLv2::REST::BranchRequest request(
            R"({"@type":"Branch","name":"smoke-branch","head":{"@id":")" + HeadId + R"("}})");
    EXPECT_EQ(request.getName(), "smoke-branch");
    ASSERT_NE(request.getHead(), nullptr);
    EXPECT_EQ(boost::uuids::to_string(request.getHead()->getId()), HeadId);
    EXPECT_EQ(request.getProject(), nullptr);
}

TEST(TestBranchRequest, MissingNameThrows) {
    EXPECT_THROW(SysMLv2::REST::BranchRequest(R"({"@type":"Branch"})"), std::invalid_argument);
    EXPECT_THROW(SysMLv2::REST::BranchRequest(R"({"name":""})"), std::invalid_argument);
    EXPECT_THROW(SysMLv2::REST::BranchRequest(R"([1,2])"), std::invalid_argument);
}

TEST(TestBranchRequest, MissingHead) {
    std::unique_ptr<SysMLv2::REST::BranchRequest> request;
    EXPECT_NO_THROW(request = std::make_unique<SysMLv2::REST::BranchRequest>(R"({"name":"no-head"})"));
    ASSERT_NE(request, nullptr);
    EXPECT_EQ(request->getHead(), nullptr);
    EXPECT_EQ(request->getProject(), nullptr);
}

TEST(TestBranchRequest, SerializeWithoutHeadAndProject) {
    SysMLv2::REST::BranchRequest request("lonely", nullptr, nullptr);
    nlohmann::json json;
    EXPECT_NO_THROW(json = nlohmann::json::parse(request.serializeToJson()));
    EXPECT_EQ(json["@type"], "Branch");
    EXPECT_EQ(json["name"], "lonely");
    EXPECT_FALSE(json.contains("head"));
    EXPECT_FALSE(json.contains("owningProject"));
}

TEST(TestBranchRequest, MalformedHeadThrows) {
    EXPECT_THROW(SysMLv2::REST::BranchRequest(R"({"name":"x","head":"abc"})"), std::invalid_argument);
    EXPECT_THROW(SysMLv2::REST::BranchRequest(R"({"name":"x","head":{"@id":"not-a-uuid"}})"), std::invalid_argument);
    EXPECT_THROW(SysMLv2::REST::BranchRequest(R"({"name":"x","owningProject":5})"), std::invalid_argument);
}
