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
#include "DataIdentity.h"
#include "DataVersion.h"
#include "Project.h"
#include "JSONEntities.h"

namespace SysMLv2::Entities {

    DataIdentity::DataIdentity(boost::uuids::uuid id) :
            Record(id){
        Record::Type = "DataIdentity";
    }

    DataIdentity::DataIdentity(std::string jsonStringOrName) : Record(jsonStringOrName) {
        Record::Type = "DataIdentity";
    }

    DataIdentity::~DataIdentity() {

    }

    std::vector<DataVersion *> DataIdentity::getDataVersions() const {
        return std::vector<DataVersion *>();
    }

    std::chrono::system_clock::time_point DataIdentity::createdAt() {
        return std::chrono::system_clock::time_point();
    }

    std::chrono::system_clock::time_point DataIdentity::deletedAt() {
        return std::chrono::system_clock::time_point();
    }

    std::string DataIdentity::serializeToJson() {
        nlohmann::json jsonGeneration;

        jsonGeneration[JSON_ID_ENTITY] = boost::uuids::to_string(Id);
        jsonGeneration[JSON_TYPE_ENTITY] = Type;

        return jsonGeneration.dump(JSON_INTENT);
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

    void DataIdentity::setDataVersions(std::vector<DataVersion *> versions) {
        Version=versions;
    }
}