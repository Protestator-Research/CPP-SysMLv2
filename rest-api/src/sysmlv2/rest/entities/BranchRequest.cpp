//
// Created by Moritz Herzog on 18.11.25.
//
#include <nlohmann/json.hpp>
#include <sysmlv2/rest/entities/Project.h>
#include <sysmlv2/rest/entities/Commit.h>
#include <sysmlv2/rest/entities/BranchRequest.h>
#include <sysmlv2/rest/entities/JSONEntities.h>

namespace SysMLv2::REST {
    BranchRequest::BranchRequest(std::string name, std::shared_ptr<Project> project, std::shared_ptr<Commit> commit) {
        _dType = "Branch";
        Name = name;
        OwingProject = project;
        Head = commit;
    }

    BranchRequest::BranchRequest(std::string jsonString) {
        BranchRequest::deserializeAndPopulate(jsonString);
    }

    std::string BranchRequest::serializeToJson() {
        nlohmann::json json;
        json[JSON_TYPE_ENTITY] = _dType;
        json[JSON_NAME_ENTITY] = Name;
        json[JSON_HEAD_ID] = Head->serializeIdentification();
        json[JSON_TYPE_ENTITY] = OwingProject->serializeIdentification();
        return json.dump(JSON_INTENT);
    }

    std::string BranchRequest::getName() {
        return Name;
    }

    std::shared_ptr<Project> BranchRequest::getProject() {
        return OwingProject;
    }

    std::shared_ptr<Commit> BranchRequest::getHead() {
        return Head;
    }

    void BranchRequest::deserializeAndPopulate(const std::string &jsonString) {
        nlohmann::json json = nlohmann::json::parse(jsonString);
        Name = json[JSON_TYPE_ENTITY].get<std::string>();
        OwingProject = std::make_shared<Project>(json[JSON_NAME_ENTITY]);
        Head = std::make_shared<Commit>(json[JSON_HEAD_ID]);
    }
} // SysMLv2::REST