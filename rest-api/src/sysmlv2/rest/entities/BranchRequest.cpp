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

namespace {
    /**
     * Reads an optional identification object ({"@id": "<uuid>"}) from the given key.
     * @return The identification object or a null JSON, if the key is missing or null.
     * @throws std::invalid_argument If the value is not an object with a valid UUID string as "@id".
     */
    nlohmann::json readIdentification(const nlohmann::json &json, const std::string &key) {
        if (!json.contains(key) || json[key].is_null())
            return nlohmann::json();
        const auto &value = json[key];
        if (!value.is_object() || !value.contains(SysMLv2::REST::JSON_ID_ENTITY) || !value[SysMLv2::REST::JSON_ID_ENTITY].is_string())
            throw std::invalid_argument("BranchRequest: '" + key + "' must be an object with an '@id'.");
        try {
            boost::uuids::string_generator()(value[SysMLv2::REST::JSON_ID_ENTITY].get<std::string>());
        } catch (const std::exception &) {
            throw std::invalid_argument("BranchRequest: '" + key + "' has an invalid '@id'.");
        }
        return value;
    }
}

namespace SysMLv2::REST {
    BranchRequest::BranchRequest(std::string name, std::shared_ptr<Project> project, std::shared_ptr<Commit> commit) {
        _dType = "Branch";
        Name = name;
        OwingProject = project;
        Head = commit;
    }

    BranchRequest::BranchRequest(std::string jsonString) : _dType("Branch") {
        BranchRequest::deserializeAndPopulate(jsonString);
    }

    std::string BranchRequest::serializeToJson() {
        nlohmann::json json;
        json[JSON_TYPE_ENTITY] = _dType.empty() ? "Branch" : _dType;
        json[JSON_NAME_ENTITY] = Name;
        if (Head != nullptr)
            json[JSON_HEAD_ID] = nlohmann::json::parse(Head->serializeIdentification());
        if (OwingProject != nullptr)
            json[JSON_OWNING_PROJECT] = nlohmann::json::parse(OwingProject->serializeIdentification());
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
        nlohmann::json json = nlohmann::json::parse(jsonString, nullptr, false);
        if (json.is_discarded() || !json.is_object())
            throw std::invalid_argument("BranchRequest: the JSON must be an object.");

        if (!json.contains(JSON_NAME_ENTITY) || !json[JSON_NAME_ENTITY].is_string() ||
            json[JSON_NAME_ENTITY].get<std::string>().empty())
            throw std::invalid_argument("BranchRequest: 'name' must be a non-empty string.");

        _dType = "Branch";
        if (json.contains(JSON_TYPE_ENTITY) && json[JSON_TYPE_ENTITY].is_string())
            _dType = json[JSON_TYPE_ENTITY].get<std::string>();

        const nlohmann::json head = readIdentification(json, JSON_HEAD_ID);
        const nlohmann::json project = readIdentification(json, JSON_OWNING_PROJECT);

        Name = json[JSON_NAME_ENTITY].get<std::string>();
        Head = head.is_null() ? nullptr : std::make_shared<Commit>(head.dump());
        OwingProject = project.is_null() ? nullptr : std::make_shared<Project>(project.dump());
    }
} // SysMLv2::REST
