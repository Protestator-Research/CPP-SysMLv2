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
#include <sysmlv2/rest/entities/Project.h>
#include <sysmlv2/rest/entities/JSONEntities.h>

#include <sysmlv2/rest/serialization/Utilities.h>


namespace SysMLv2::REST {

    DataIdentity::DataIdentity(boost::uuids::uuid id) :
            Record(id){
        Record::Type = "DataIdentity";
    }

    DataIdentity::DataIdentity(std::string jsonStringOrName) : Record(jsonStringOrName) {
        Record::Type = "DataIdentity";
        DataIdentity::deserializeAndPopulate(jsonStringOrName);
    }

    std::vector<std::shared_ptr<DataVersion>> DataIdentity::getDataVersions() const {
        return Version;
    }

    std::chrono::system_clock::time_point DataIdentity::createdAt() {
        return Created;
    }

    std::chrono::system_clock::time_point DataIdentity::deletedAt() {
        return Deleted;
    }

    std::string DataIdentity::serializeToJson() {
        nlohmann::json json = nlohmann::json::parse(Record::serializeToJson());

        std::string jsonElements = "[\r\n";
        for (size_t i = 0; i < Version.size(); i++) {
            jsonElements += Version[i]->serializeToJson();

            if (i != (Version.size() - 1))
                jsonElements += ",\r\n";
        }
        jsonElements += "]\r\n";

        json[JSON_DATA_VER_ENTITIY] = nlohmann::json::parse(jsonElements);
    	json[JSON_CREATED_ENTITY] = Utilities::toIso8601(Created);
        json[JSON_DELETED_ENTITY] = Utilities::toIso8601(Deleted);

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
        nlohmann::json parsedJson = nlohmann::json::parse(jsonString);

    	Deleted = Utilities::fromIso8601(parsedJson[JSON_DELETED_ENTITY]);
        Created = Utilities::fromIso8601(parsedJson[JSON_CREATED_ENTITY]);

        std::vector<nlohmann::json> arrayValues = parsedJson[JSON_DATA_VER_ENTITIY].get<std::vector<nlohmann::json>>();
        for (const auto& value : arrayValues)
        {
            auto versionToBeAdded = std::make_shared<DataVersion>(value.dump());
            Version.push_back(versionToBeAdded);
        }
    }

}
