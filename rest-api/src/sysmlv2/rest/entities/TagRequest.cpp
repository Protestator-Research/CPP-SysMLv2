//
// Request to create a Tag.
//
#include <nlohmann/json.hpp>
#include <stdexcept>
#include <sysmlv2/rest/entities/TagRequest.h>
#include <sysmlv2/rest/entities/Commit.h>
#include <sysmlv2/rest/entities/JSONEntities.h>
#include "RestJson.h"

namespace SysMLv2::REST {
    TagRequest::TagRequest(std::string name, std::shared_ptr<Commit> taggedCommit) :
        Name(std::move(name)), TaggedCommit(std::move(taggedCommit)) {
    }

    TagRequest::TagRequest(std::string name, const boost::uuids::uuid& taggedCommitId) :
        Name(std::move(name)), TaggedCommit(std::make_shared<Commit>(Internal::referenceObjectText(taggedCommitId))) {
    }

    TagRequest::TagRequest(const std::string& jsonString) {
        TagRequest::deserializeAndPopulate(jsonString);
    }

    std::string TagRequest::serializeToJson() {
        nlohmann::json json;
        json[JSON_TYPE_ENTITY] = "Tag";
        json[JSON_NAME_ENTITY] = Name;
        Internal::writeReference(json, JSON_TAGGED_COMMIT_ENTITY,
                                 TaggedCommit != nullptr ? std::optional<boost::uuids::uuid>(TaggedCommit->getId()) : std::nullopt);
        return json.dump(JSON_INTENT);
    }

    std::string TagRequest::getName() const {
        return Name;
    }

    std::shared_ptr<Commit> TagRequest::getTaggedCommit() const {
        return TaggedCommit;
    }

    void TagRequest::deserializeAndPopulate(const std::string& jsonString) {
        const nlohmann::json json = Internal::parseObject(jsonString, "TagRequest");
        try {
            const auto type = json.find(JSON_TYPE_ENTITY);
            if (type != json.end() && !type->is_null() && (!type->is_string() || type->get<std::string>() != "Tag"))
                throw std::invalid_argument("'@type' must be \"Tag\"");

            const auto name = json.find(JSON_NAME_ENTITY);
            if (name == json.end() || !name->is_string() || name->get<std::string>().empty())
                throw std::invalid_argument("'name' must be a non-empty string");

            const auto commitId = Internal::readReference(json, JSON_TAGGED_COMMIT_ENTITY);
            if (!commitId.has_value())
                throw std::invalid_argument("'taggedCommit' is required");

            Name = name->get<std::string>();
            TaggedCommit = std::make_shared<Commit>(Internal::referenceObjectText(*commitId));
        } catch (const std::exception& ex) {
            throw std::invalid_argument(std::string("TagRequest: ") + ex.what());
        }
    }
}
