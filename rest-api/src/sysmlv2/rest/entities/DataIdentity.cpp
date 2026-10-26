//
// Created by Moritz Herzog on 19.02.24.
//
//---------------------------------------------------------
// Constants, Definitions, Pragmas
//---------------------------------------------------------

//---------------------------------------------------------
// External Classes
//---------------------------------------------------------
#include <nlohmann/json.hpp>
#include <boost/uuid/nil_generator.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include <sysmlv2/rest/entities/DataIdentity.h>
#include <sysmlv2/rest/entities/DataVersion.h>
#include <sysmlv2/rest/entities/Commit.h>
#include <sysmlv2/rest/entities/Project.h>
#include <sysmlv2/rest/entities/JSONEntities.h>

#include <sysmlv2/rest/serialization/Utilities.h>
#include "RestJson.h"


namespace SysMLv2::REST {

    DataIdentity::DataIdentity(boost::uuids::uuid id) :
            Record(id){
        Record::Type = "DataIdentity";
    }

    DataIdentity::DataIdentity(std::string jsonStringOrName) : Record(jsonStringOrName, "DataIdentity") {
        Record::Type = "DataIdentity";
        if (Internal::looksLikeJson(jsonStringOrName))
            DataIdentity::deserializeAndPopulate(jsonStringOrName);
    }

    std::vector<std::shared_ptr<DataVersion>> DataIdentity::getDataVersions() const {
        return Version;
    }

    std::chrono::system_clock::time_point DataIdentity::createdAt() const {
        if (CreatedAt != nullptr && CreatedAt->getCreated() != std::chrono::system_clock::time_point{})
            return CreatedAt->getCreated();
        return Created.value_or(std::chrono::system_clock::time_point{});
    }

    std::chrono::system_clock::time_point DataIdentity::deletedAt() const {
        if (DeletedAt != nullptr && DeletedAt->getCreated() != std::chrono::system_clock::time_point{})
            return DeletedAt->getCreated();
        return Deleted.value_or(std::chrono::system_clock::time_point{});
    }

    std::shared_ptr<Commit> DataIdentity::getCreatedAt() const {
        return CreatedAt;
    }

    void DataIdentity::setCreatedAt(std::shared_ptr<Commit> commit) {
        CreatedAt = std::move(commit);
    }

    std::shared_ptr<Commit> DataIdentity::getDeletedAt() const {
        return DeletedAt;
    }

    void DataIdentity::setDeletedAt(std::shared_ptr<Commit> commit) {
        DeletedAt = std::move(commit);
    }

    std::string DataIdentity::serializeToJson() {
        nlohmann::json json = nlohmann::json::parse(Record::serializeToJson());

        // createdAt and deletedAt are derived properties; they are written only if they are known.
        if (CreatedAt != nullptr)
            Internal::writeReference(json, JSON_CREATED_AT_ENTITY, CreatedAt->getId());
        if (DeletedAt != nullptr)
            Internal::writeReference(json, JSON_DELETED_AT_ENTITY, DeletedAt->getId());

        return json.dump(JSON_INTENT);
    }

    bool DataIdentity::operator==(const DataIdentity &other) {
        if(other.Id != Id)
            return false;

        if(other.Version.size() != Version.size())
            return false;

        for(size_t i = 0; i<Version.size(); i++)
            if(Version[i] != other.Version[i])
                return false;

        return true;
    }

    void DataIdentity::setDataVersions(std::vector<std::shared_ptr<DataVersion>> versions) {
        Version=versions;
    }


    void DataIdentity::deserializeAndPopulate(const std::string& jsonString)
    {
        const nlohmann::json parsedJson = Internal::parseObject(jsonString, "DataIdentity");
        Record::deserializeAndPopulate(jsonString);
        Type = "DataIdentity";

        try {
            CreatedAt.reset();
            DeletedAt.reset();
            if (const auto createdId = Internal::readReference(parsedJson, JSON_CREATED_AT_ENTITY))
                CreatedAt = std::make_shared<Commit>(Internal::referenceObjectText(*createdId));
            if (const auto deletedId = Internal::readReference(parsedJson, JSON_DELETED_AT_ENTITY))
                DeletedAt = std::make_shared<Commit>(Internal::referenceObjectText(*deletedId));

            // Fields of earlier library versions. The timestamps cannot be turned into commit references, they are kept
            // for createdAt() and deletedAt().
            if (parsedJson.contains(JSON_CREATED_ENTITY)) {
                warnDeprecated("JSON field \"created\" of a DataIdentity", "\"createdAt\" (a reference to the creating commit)");
                Created = Internal::readOptionalTimestamp(parsedJson, JSON_CREATED_ENTITY);
            }
            if (parsedJson.contains(JSON_DELETED_ENTITY)) {
                warnDeprecated("JSON field \"deleted\" of a DataIdentity", "\"deletedAt\" (a reference to the deleting commit)");
                Deleted = Internal::readOptionalTimestamp(parsedJson, JSON_DELETED_ENTITY);
            }

            if (parsedJson.contains(JSON_DATA_VER_ENTITIY)) {
                warnDeprecated("JSON field \"dataVersions\" of a DataIdentity", "the DataVersions of the commits that reference the identity");
                const auto& versions = parsedJson[JSON_DATA_VER_ENTITIY];
                if (!versions.is_null()) {
                    if (!versions.is_array())
                        throw std::invalid_argument("'" + JSON_DATA_VER_ENTITIY + "' must be an array or null");
                    Version.clear();
                    for (const auto& value : versions)
                        Version.push_back(std::make_shared<DataVersion>(value.dump()));
                }
            }
        } catch (const std::exception& ex) {
            throw std::invalid_argument(std::string("DataIdentity: ") + ex.what());
        }
    }

}
