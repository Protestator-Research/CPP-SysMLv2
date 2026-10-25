//
// Created by Moritz Herzog on 18.11.25.
//
#include <nlohmann/json.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <stdexcept>
#include <sysmlv2/rest/entities/Project.h>
#include <sysmlv2/rest/entities/Commit.h>
#include <sysmlv2/rest/entities/BranchRequest.h>
#include <sysmlv2/rest/entities/JSONEntities.h>
#include "RestJson.h"

namespace SysMLv2::REST {
    BranchRequest::BranchRequest(std::string name, std::shared_ptr<Project> project, std::shared_ptr<Commit> commit) {
        _dType = "Branch";
        Name = name;
        OwingProject = project;
        Head = commit;
        if (Head == nullptr)
            warnDeprecated("a BranchRequest without \"head\"", "a BranchRequest with a \"head\" reference");
    }

    BranchRequest::BranchRequest(std::string jsonString) : _dType("Branch") {
        BranchRequest::deserializeAndPopulate(jsonString);
    }

    std::string BranchRequest::serializeToJson() {
        nlohmann::json json;
        json[JSON_TYPE_ENTITY] = _dType.empty() ? "Branch" : _dType;
        json[JSON_NAME_ENTITY] = Name;
        if (Head != nullptr)
            Internal::writeReference(json, JSON_HEAD_ID, Head->getId());
        if (OwingProject != nullptr)
            Internal::writeReference(json, JSON_OWNING_PROJECT, OwingProject->getId());
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
        const nlohmann::json json = Internal::parseObject(jsonString, "BranchRequest");

        if (!json.contains(JSON_NAME_ENTITY) || !json[JSON_NAME_ENTITY].is_string() ||
            json[JSON_NAME_ENTITY].get<std::string>().empty())
            throw std::invalid_argument("BranchRequest: 'name' must be a non-empty string.");

        _dType = "Branch";
        if (json.contains(JSON_TYPE_ENTITY) && json[JSON_TYPE_ENTITY].is_string())
            _dType = json[JSON_TYPE_ENTITY].get<std::string>();

        std::optional<boost::uuids::uuid> head;
        std::optional<boost::uuids::uuid> project;
        try {
            head = Internal::readReference(json, JSON_HEAD_ID);
            project = Internal::readReference(json, JSON_OWNING_PROJECT);
        } catch (const std::exception& ex) {
            throw std::invalid_argument(std::string("BranchRequest: ") + ex.what());
        }

        // The API needs the head to create a branch. Requests without head were accepted by earlier library versions, they
        // are still read but reported.
        if (!head.has_value())
            warnDeprecated("a BranchRequest without \"head\"", "a BranchRequest with a \"head\" reference");

        Name = json[JSON_NAME_ENTITY].get<std::string>();
        Head = head.has_value() ? std::make_shared<Commit>(Internal::referenceObjectText(*head)) : nullptr;
        OwingProject = project.has_value() ? std::make_shared<Project>(Internal::referenceObjectText(*project)) : nullptr;
    }
} // SysMLv2::REST
