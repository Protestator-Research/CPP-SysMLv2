//
// Tests of SysMLv2Deserializer (AP 4): every REST type is recognised by "@type", JSON null gives nullptr / an empty list, arrays
// mix REST entities and model elements, and DataVersion payloads come back as their REST classes.
//

#include <gtest/gtest.h>
#include <memory>
#include <string>
#include <nlohmann/json.hpp>
#include <kerml/kernel/packages/Package.h>
#include <kerml/root/elements/Element.h>
#include <sysml/parts/PartDefinition.h>
#include "support/CerrCapture.h"
#include <sysmlv2/rest/Deprecation.h>
#include <sysmlv2/rest/entities/Branch.h>
#include <sysmlv2/rest/entities/Commit.h>
#include <sysmlv2/rest/entities/Constraint.h>
#include <sysmlv2/rest/entities/DataDifference.h>
#include <sysmlv2/rest/entities/DataIdentity.h>
#include <sysmlv2/rest/entities/DataVersion.h>
#include <sysmlv2/rest/entities/ExternalData.h>
#include <sysmlv2/rest/entities/ExternalRelationship.h>
#include <sysmlv2/rest/entities/Project.h>
#include <sysmlv2/rest/entities/ProjectUsage.h>
#include <sysmlv2/rest/entities/Query.h>
#include <sysmlv2/rest/entities/QueryRequest.h>
#include <sysmlv2/rest/entities/Tag.h>
#include <sysmlv2/rest/serialization/SysMLv2Deserializer.h>

using namespace SysMLv2::REST;
using SysMLv2::SysMLv2Deserializer;
using nlohmann::json;

namespace {
    const std::string ProjectId = "6e701bf8-7793-49de-9b0e-2f43376edabf";
    const std::string BranchId = "b1b1b1b1-2d3a-4b5c-8d6e-7f8091a2b3c4";
    const std::string TagId = "7a7a7a7a-2d3a-4b5c-8d6e-7f8091a2b3c4";
    const std::string CommitId = "c4fc0b1e-2d3a-4b5c-8d6e-7f8091a2b3c4";
    const std::string DataId = "11111111-2222-4333-8444-555555555555";
    const std::string OtherDataId = "99999999-8888-4777-8666-555555555555";
    const std::string VersionId = "aaaaaaaa-bbbb-4ccc-8ddd-eeeeeeeeeeee";
    const std::string QueryId = "55555555-2222-4333-8444-555555555555";

    json reference(const std::string& id) {
        return json{{"@id", id}};
    }

    template<typename T>
    std::shared_ptr<T> parseAs(const json& value) {
        return std::dynamic_pointer_cast<T>(SysMLv2Deserializer::deserializeJsonString(value.dump()));
    }

    class RestDeserializer : public ::testing::Test {
    protected:
        void SetUp() override { resetDeprecationWarningsForTesting(); }
    };
}

TEST_F(RestDeserializer, Project) {
    auto project = parseAs<Project>({{"@id", ProjectId}, {"@type", "Project"}, {"name", "P"}, {"description", nullptr}});
    ASSERT_NE(project, nullptr);
    EXPECT_EQ(project->getType(), "Project");
    EXPECT_EQ(project->getName(), "P");
}

TEST_F(RestDeserializer, TypeIsCaseInsensitive) {
    EXPECT_NE(parseAs<Project>({{"@id", ProjectId}, {"@type", "PROJECT"}}), nullptr);
    EXPECT_NE(parseAs<Project>({{"@id", ProjectId}, {"@type", "project"}}), nullptr);
    EXPECT_NE(parseAs<Query>({{"@id", QueryId}, {"@type", "query"}}), nullptr);
    EXPECT_NE(parseAs<Query>({{"@id", QueryId}, {"@type", "QUERY"}}), nullptr);
    EXPECT_NO_THROW(QueryRequest(json{{"@type", "query"}}.dump()));
    EXPECT_NO_THROW(QueryRequest(json{{"@type", "QUERY"}}.dump()));
    const json primitive = {{"inverse", false}, {"property", "@type"}, {"operator", "="}, {"value", "x"}};
    json lowerPrimitive = primitive;
    lowerPrimitive["@type"] = "primitiveconstraint";
    EXPECT_NE(parseAs<PrimitiveConstraint>(lowerPrimitive), nullptr);
    EXPECT_NE(Constraint::fromJsonValue(lowerPrimitive), nullptr);
    json primitiveWithType = primitive;
    primitiveWithType["@type"] = "PrimitiveConstraint";
    EXPECT_NE(parseAs<CompositeConstraint>({{"@type", "COMPOSITECONSTRAINT"}, {"operator", "or"},
                                            {"constraint", json::array({primitiveWithType, primitiveWithType})}}), nullptr);
}

TEST_F(RestDeserializer, Commit) {
    auto commit = parseAs<Commit>({{"@id", CommitId}, {"@type", "Commit"}, {"created", "2024-05-01T10:00:00Z"},
                                   {"owningProject", reference(ProjectId)}, {"previousCommits", json::array()}});
    ASSERT_NE(commit, nullptr);
    EXPECT_EQ(commit->getType(), "Commit");
}

TEST_F(RestDeserializer, BranchAndTag) {
    auto branch = parseAs<Branch>({{"@id", BranchId}, {"@type", "Branch"}, {"name", "main"}, {"head", reference(CommitId)},
                                   {"referencedCommit", reference(CommitId)}, {"owningProject", reference(ProjectId)}});
    ASSERT_NE(branch, nullptr);
    EXPECT_EQ(branch->getType(), "Branch");
    EXPECT_EQ(branch->getName(), "main");

    auto tag = parseAs<Tag>({{"@id", TagId}, {"@type", "Tag"}, {"name", "v1"}, {"taggedCommit", reference(CommitId)},
                             {"referencedCommit", reference(CommitId)}, {"owningProject", reference(ProjectId)}});
    ASSERT_NE(tag, nullptr);
    EXPECT_EQ(tag->getType(), "Tag");
    EXPECT_EQ(tag->getName(), "v1");
    EXPECT_EQ(std::dynamic_pointer_cast<Branch>(tag), nullptr);
}

TEST_F(RestDeserializer, DataIdentityVersionAndDifference) {
    auto identity = parseAs<DataIdentity>({{"@id", DataId}, {"@type", "DataIdentity"}});
    ASSERT_NE(identity, nullptr);
    EXPECT_EQ(identity->getType(), "DataIdentity");

    auto version = parseAs<DataVersion>({{"@id", VersionId}, {"@type", "DataVersion"},
                                         {"identity", {{"@id", DataId}, {"@type", "DataIdentity"}}}, {"payload", nullptr}});
    ASSERT_NE(version, nullptr);
    EXPECT_EQ(version->getPayload(), nullptr);
    EXPECT_EQ(version->getType(), "DataVersion");

    auto difference = parseAs<DataDifference>({{"@type", "DataDifference"}, {"baseData", nullptr}, {"compareData", nullptr}});
    ASSERT_NE(difference, nullptr);
}

TEST_F(RestDeserializer, ProjectUsageExternalDataAndRelationship) {
    auto usage = parseAs<ProjectUsage>({{"@id", DataId}, {"@type", "ProjectUsage"}, {"usedProjectCommit", reference(CommitId)}});
    ASSERT_NE(usage, nullptr);
    EXPECT_EQ(usage->getType(), "ProjectUsage");

    auto external = parseAs<ExternalData>({{"@id", OtherDataId}, {"@type", "ExternalData"},
                                           {"resourceIdentifier", "https://example.com/model.sysml"}});
    ASSERT_NE(external, nullptr);
    EXPECT_EQ(external->resourceIdentifier(), "https://example.com/model.sysml");

    auto relationship = parseAs<ExternalRelationship>({{"@id", VersionId}, {"@type", "ExternalRelationship"},
                                                       {"elementEnd", reference(DataId)}, {"externalDataEnd", reference(OtherDataId)},
                                                       {"specification", "x"}, {"language", "SQL"}});
    ASSERT_NE(relationship, nullptr);
    EXPECT_EQ(relationship->language(), "SQL");
}

TEST_F(RestDeserializer, QueryAndConstraints) {
    const json primitive = {{"@type", "PrimitiveConstraint"}, {"inverse", false}, {"property", "@type"}, {"operator", "="},
                            {"value", "PartDefinition"}};
    const json composite = {{"@type", "CompositeConstraint"}, {"operator", "and"}, {"constraint", json::array({primitive, primitive})}};

    auto query = parseAs<Query>({{"@id", QueryId}, {"@type", "Query"}, {"select", json::array({"name"})},
                                 {"owningProject", reference(ProjectId)}, {"where", primitive}});
    ASSERT_NE(query, nullptr);
    EXPECT_EQ(query->getType(), "Query");

    auto primitiveConstraint = parseAs<PrimitiveConstraint>(primitive);
    ASSERT_NE(primitiveConstraint, nullptr);
    EXPECT_EQ(primitiveConstraint->getType(), "PrimitiveConstraint");

    auto compositeConstraint = parseAs<CompositeConstraint>(composite);
    ASSERT_NE(compositeConstraint, nullptr);
    EXPECT_EQ(compositeConstraint->getType(), "CompositeConstraint");
    EXPECT_NE(std::dynamic_pointer_cast<Constraint>(compositeConstraint), nullptr);
}

TEST_F(RestDeserializer, RequestTypesBecomeRecords) {
    // The request types share "@type" with the records; the deserializer reads responses.
    EXPECT_NE(parseAs<Project>({{"@type", "Project"}, {"name", "n"}, {"defaultBranch", reference(BranchId)}}), nullptr);
    EXPECT_NE(parseAs<Branch>({{"@type", "Branch"}, {"name", "n"}, {"head", reference(CommitId)}}), nullptr);
    EXPECT_NE(parseAs<Tag>({{"@type", "Tag"}, {"name", "n"}, {"taggedCommit", reference(CommitId)}}), nullptr);
}

TEST_F(RestDeserializer, NullAndNonEntities) {
    EXPECT_EQ(SysMLv2Deserializer::deserializeJsonString("null"), nullptr);
    EXPECT_EQ(SysMLv2Deserializer::deserializeJsonString("[1]"), nullptr);
    EXPECT_EQ(SysMLv2Deserializer::deserializeJsonString("5"), nullptr);
    EXPECT_EQ(SysMLv2Deserializer::deserializeJsonString("{}"), nullptr);
    EXPECT_EQ(SysMLv2Deserializer::deserializeJsonString(R"({"@type":"Nothing Known"})"), nullptr);
    EXPECT_EQ(SysMLv2Deserializer::deserializeJsonString(R"({"@type":5})"), nullptr);
    EXPECT_THROW(SysMLv2Deserializer::deserializeJsonString("{not json"), nlohmann::json::exception);
}

TEST_F(RestDeserializer, MissingOrNonStringTypeFallsBackToElementById) {
    auto element = SysMLv2Deserializer::deserializeJsonString(json{{"@id", DataId}, {"declaredName", "x"}}.dump());
    EXPECT_NE(std::dynamic_pointer_cast<KerML::Entities::Element>(element), nullptr);
    auto nonString = SysMLv2Deserializer::deserializeJsonString(json{{"@id", DataId}, {"@type", 5}}.dump());
    EXPECT_NE(std::dynamic_pointer_cast<KerML::Entities::Element>(nonString), nullptr);
}

TEST_F(RestDeserializer, ModelElementsAreStillCreated) {
    auto package = parseAs<KerML::Entities::Package>({{"@id", DataId}, {"@type", "Package"}, {"declaredName", "P"}});
    ASSERT_NE(package, nullptr);
    EXPECT_EQ(package->getType(), "Package");

    auto part = parseAs<SysMLv2::Entities::PartDefinition>({{"@id", OtherDataId}, {"@type", "PartDefinition"}, {"declaredName", "Vehicle"}});
    ASSERT_NE(part, nullptr);
    EXPECT_EQ(part->getType(), "PartDefinition");
}

TEST_F(RestDeserializer, ArrayMixesRestEntitiesAndElements) {
    const json array = json::array({
        {{"@id", ProjectId}, {"@type", "Project"}, {"name", "P"}},
        {{"@id", BranchId}, {"@type", "Branch"}, {"name", "main"}, {"head", reference(CommitId)}, {"referencedCommit", reference(CommitId)}},
        {{"@id", DataId}, {"@type", "Package"}, {"declaredName", "P"}},
        nullptr,
        {{"@id", OtherDataId}, {"@type", "PartDefinition"}, {"declaredName", "Vehicle"}},
        {{"@type", "Unknown"}},
    });
    const auto entities = SysMLv2Deserializer::deserializeJsonArray(array.dump());
    ASSERT_EQ(entities.size(), 4u);
    EXPECT_NE(std::dynamic_pointer_cast<Project>(entities[0]), nullptr);
    EXPECT_NE(std::dynamic_pointer_cast<Branch>(entities[1]), nullptr);
    EXPECT_NE(std::dynamic_pointer_cast<KerML::Entities::Package>(entities[2]), nullptr);
    EXPECT_NE(std::dynamic_pointer_cast<SysMLv2::Entities::PartDefinition>(entities[3]), nullptr);
}

TEST_F(RestDeserializer, ArrayNullAndEmpty) {
    EXPECT_TRUE(SysMLv2Deserializer::deserializeJsonArray("null").empty());
    EXPECT_TRUE(SysMLv2Deserializer::deserializeJsonArray("[]").empty());
    EXPECT_TRUE(SysMLv2Deserializer::deserializeJsonArray("[null, null]").empty());
    EXPECT_THROW(SysMLv2Deserializer::deserializeJsonArray("{}"), std::invalid_argument);
    EXPECT_THROW(SysMLv2Deserializer::deserializeJsonArray("[not json"), nlohmann::json::exception);
}

TEST_F(RestDeserializer, DataVersionPayloadTypes) {
    CerrCapture capture;
    const auto identity = [](const std::string& id) { return json{{"@id", id}, {"@type", "DataIdentity"}}; };

    DataVersion usage(json{{"@id", VersionId}, {"@type", "DataVersion"}, {"identity", identity(DataId)},
                           {"payload", {{"@id", DataId}, {"@type", "ProjectUsage"}, {"usedProjectCommit", reference(CommitId)}}}}.dump());
    EXPECT_NE(std::dynamic_pointer_cast<ProjectUsage>(usage.getPayload()), nullptr);

    DataVersion external(json{{"@id", VersionId}, {"@type", "DataVersion"}, {"identity", identity(DataId)},
                              {"payload", {{"@id", DataId}, {"@type", "ExternalData"}, {"resourceIdentifier", "https://example.com/a"}}}}.dump());
    EXPECT_NE(std::dynamic_pointer_cast<ExternalData>(external.getPayload()), nullptr);

    DataVersion relationship(json{{"@id", VersionId}, {"@type", "DataVersion"}, {"identity", identity(DataId)},
                                  {"payload", {{"@id", DataId}, {"@type", "ExternalRelationship"},
                                               {"elementEnd", reference(OtherDataId)}, {"externalDataEnd", reference(OtherDataId)}}}}.dump());
    EXPECT_NE(std::dynamic_pointer_cast<ExternalRelationship>(relationship.getPayload()), nullptr);

    DataVersion package(json{{"@id", VersionId}, {"@type", "DataVersion"}, {"identity", identity(DataId)},
                             {"payload", {{"@id", DataId}, {"@type", "Package"}, {"declaredName", "P"}}}}.dump());
    EXPECT_NE(std::dynamic_pointer_cast<KerML::Entities::Package>(package.getPayload()), nullptr);

    EXPECT_EQ(capture.str().find("Deprecated:"), std::string::npos);
}

TEST_F(RestDeserializer, TypesWrittenByEarlierLibraryVersionsDoNotCrash) {
    CerrCapture capture;
    // "CommitRequest" (written by earlier versions as @type) is no known REST type here; with an "@id" it becomes a plain
    // model Element that keeps the original type, without an "@id" the result is nullptr.
    EXPECT_NO_THROW(SysMLv2Deserializer::deserializeJsonString(json{{"@type", "CommitRequest"}, {"description", "d"}}.dump()));
    EXPECT_EQ(SysMLv2Deserializer::deserializeJsonString(json{{"@type", "CommitRequest"}, {"description", "d"}}.dump()), nullptr);
    auto request = SysMLv2Deserializer::deserializeJsonString(json{{"@id", CommitId}, {"@type", "CommitRequest"}}.dump());
    EXPECT_NO_THROW(request ? request->serializeToJson() : std::string());

    // Tags written with "@type": "CommitReference" are likewise not a Tag; the result does not crash.
    auto reference = SysMLv2Deserializer::deserializeJsonString(
        json{{"@id", TagId}, {"@type", "CommitReference"}, {"name", "v1"}}.dump());
    EXPECT_NO_THROW(reference ? reference->serializeToJson() : std::string());
    EXPECT_EQ(std::dynamic_pointer_cast<Tag>(reference), nullptr);
}

TEST_F(RestDeserializer, NullChangeEntriesAreSkipped) {
    const json change = {{"@id", VersionId}, {"@type", "DataVersion"}, {"identity", {{"@id", DataId}, {"@type", "DataIdentity"}}},
                         {"payload", nullptr}};
    auto commit = parseAs<Commit>({{"@id", CommitId}, {"@type", "Commit"}, {"change", json::array({nullptr, change})}});
    ASSERT_NE(commit, nullptr);
    EXPECT_EQ(commit->getChange().size(), 1u);
}
