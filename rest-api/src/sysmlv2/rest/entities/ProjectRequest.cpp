//
// Created by Moritz Herzog on 13.11.25.
//

#include <nlohmann/json.hpp>
#include <stdexcept>
#include <sysmlv2/rest/Deprecation.h>
#include <sysmlv2/rest/entities/ProjectRequest.h>
#include <sysmlv2/rest/entities/JSONEntities.h>
#include "RestJson.h"

namespace SysMLv2::REST {
    ProjectRequest::ProjectRequest(const std::string& name, const std::string& description, std::optional<boost::uuids::uuid> defaultBranch) {
        Name = name;
        Description = description;
        DefaultBranchId = defaultBranch;
        _dType = "Project";
    }

    ProjectRequest::ProjectRequest(const std::string& name, const std::string& description, const std::string& defaultBranch) {
        warnDeprecated("ProjectRequest(name, description, defaultBranchName)",
                       "ProjectRequest(name, description, std::optional<boost::uuids::uuid>)");
        Name = name;
        Description = description;
        DefaultBranchName = defaultBranch;
        _dType = "Project";
    }

    ProjectRequest::ProjectRequest(const std::string &jsonString) : _dType("Project") {
        deserializeAndPopulate(jsonString);
    }

    std::string ProjectRequest::name() const {
        return Name;
    }

    std::string ProjectRequest::description() const {
        return Description;
    }

    std::optional<boost::uuids::uuid> ProjectRequest::defaultBranchId() const {
        return DefaultBranchId;
    }

    std::string ProjectRequest::defaultBranch() const {
        warnDeprecated("ProjectRequest::defaultBranch()", "ProjectRequest::defaultBranchId()");
        return DefaultBranchName.value_or(std::string());
    }

    std::string ProjectRequest::serializeToJson() {
        nlohmann::json json;
        json[JSON_NAME_ENTITY] = Name;
        json[JSON_TYPE_ENTITY] = _dType;
        json[JSON_DESCRIPTION_ENTITY] = Description;
        if (DefaultBranchName.has_value())
            json[JSON_DEFAULT_BRANCH_ENTITY] = *DefaultBranchName;
        else if (DefaultBranchId.has_value() && !DefaultBranchId->is_nil())
            Internal::writeReference(json, JSON_DEFAULT_BRANCH_ENTITY, DefaultBranchId);
        return json.dump(JSON_INTENT);
    }

    void ProjectRequest::deserializeAndPopulate(const std::string &jsonString) {
        const nlohmann::json json = Internal::parseObject(jsonString, "ProjectRequest");
        try {
            Name = Internal::readOptionalString(json, JSON_NAME_ENTITY);
            Description = Internal::readOptionalString(json, JSON_DESCRIPTION_ENTITY);

            DefaultBranchId.reset();
            DefaultBranchName.reset();
            const auto branch = json.find(JSON_DEFAULT_BRANCH_ENTITY);
            if (branch != json.end() && !branch->is_null()) {
                if (branch->is_string()) {
                    // Earlier library versions wrote the name of the branch.
                    warnDeprecated("JSON field \"defaultBranch\" as a branch name", "\"defaultBranch\" as a reference {\"@id\": ...}");
                    DefaultBranchName = branch->get<std::string>();
                } else {
                    DefaultBranchId = Internal::readReference(json, JSON_DEFAULT_BRANCH_ENTITY);
                }
            }
        } catch (const std::exception& ex) {
            throw std::invalid_argument(std::string("ProjectRequest: ") + ex.what());
        }
    }
}
