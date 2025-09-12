//
// Created by Moritz Herzog on 23.02.24.
//

#include "DataVersion.h"

#include <iostream>

#include "DataIdentity.h"
#include "JSONEntities.h"
#include "Data.h"

#include <boost/uuid/random_generator.hpp>
#include <nlohmann/json.hpp>

namespace SysMLv2::REST {
    DataVersion::DataVersion(std::shared_ptr<DataIdentity> identity, std::shared_ptr<Data> payload) : Record(boost::uuids::random_generator()()) {
        Type = "DataVersion";
        Identity = identity;
        Payload = payload;
    }

    DataVersion::~DataVersion() {

    }

    std::shared_ptr<DataIdentity> DataVersion::getIdentity() {
        return Identity;
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
        std::cout << "Identity" << std::endl;
        json[JSON_IDENTITY_ENTITY] = nlohmann::json::parse(Identity->serializeToJson());
        json[JSON_PAYLOAD_ENTITY] = nlohmann::json::parse(Payload->serializeToJson());

	    return json.dump(JSON_INTENT);
    }
}
