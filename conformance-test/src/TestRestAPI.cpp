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

#include "sysmlv2/rest/entities/ProjectRequest.h"


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