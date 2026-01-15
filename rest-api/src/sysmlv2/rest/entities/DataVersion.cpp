//
// Created by Moritz Herzog on 23.02.24.
//

#include <sysmlv2/rest/entities/DataVersion.h>

#include <iostream>

#include <sysmlv2/rest/entities/DataIdentity.h>
#include <sysmlv2/rest/entities/JSONEntities.h>
#include <sysmlv2/rest/entities/Data.h>

#include <boost/uuid/random_generator.hpp>
#include <nlohmann/json.hpp>

namespace SysMLv2::REST {
    DataVersion::DataVersion(boost::uuids::uuid id, std::shared_ptr<Data> payload) : Record(payload->getId()) {
        Type = "DataVersion";
        Payload = payload;
    }

    DataVersion::DataVersion(std::string jsonValue) : Record(jsonValue)
    {
        DataVersion::deserializeAndPopulate(jsonValue);
    }

    DataVersion::~DataVersion() {

    }
    void DataVersion::setPayload(std::shared_ptr<Data> payload) {
        Payload = payload;
    }

    std::shared_ptr<Data> DataVersion::getPayload() {
        return Payload;
    }

    boost::uuids::uuid DataVersion::getId() {
        return Payload->getId();
    }

    std::string DataVersion::serializeToJson()
    {
        nlohmann::json json = nlohmann::json::parse(Record::serializeToJson());

        json[JSON_PAYLOAD_ENTITY] = nlohmann::json::parse(Payload->serializeToJson());

	    return json.dump(JSON_INTENT);
    }

    void DataVersion::deserializeAndPopulate(const std::string& jsonString)
    {
        nlohmann::json parsedJson = nlohmann::json::parse(jsonString);
        Payload = std::make_shared<Data>(parsedJson[JSON_PAYLOAD_ENTITY].dump());
    }
}
