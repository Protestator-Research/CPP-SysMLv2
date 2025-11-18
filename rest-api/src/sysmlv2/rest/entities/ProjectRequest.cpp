//
// Created by Moritz Herzog on 13.11.25.
//

#include <nlohmann/json.hpp>
#include <sysmlv2/rest/entities/ProjectRequest.h>
#include <sysmlv2/rest/entities/JSONEntities.h>

namespace SysMLv2::REST {
    ProjectRequest::ProjectRequest(const std::string& name, const std::string& description, const std::string& defaultBranch) {
        Name = name;
        Description = description;
        DefaultBranchName = defaultBranch;
        _dType = "Project";
    }

    ProjectRequest::ProjectRequest(const std::string &jsonString) {
        deserializeAndPopulate(jsonString);
    }

    std::string ProjectRequest::name() const {
        return Name;
    }

    std::string ProjectRequest::description() const {
        return Description;
    }

    std::string ProjectRequest::defaultBranch() const {
        return DefaultBranchName;
    }

    std::string ProjectRequest::serializeToJson() {
        nlohmann::json json;
        json[JSON_NAME_ENTITY] = Name;
        json[JSON_DESCRIPTION_ENTITY] = Description;
        json[JSON_DEFAULT_BRANCH_ENTITY] = DefaultBranchName;
        return json.dump(JSON_INTENT);
    }

    void ProjectRequest::deserializeAndPopulate(const std::string &jsonString) {
        nlohmann::json json = nlohmann::json::parse(jsonString);
        Name = json[JSON_NAME_ENTITY] ;
        Description = json[JSON_DESCRIPTION_ENTITY];
        DefaultBranchName = json[JSON_DEFAULT_BRANCH_ENTITY];
    }
}
