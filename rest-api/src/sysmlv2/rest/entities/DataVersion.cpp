//
// Created by Moritz Herzog on 23.02.24.
//

#include <sysmlv2/rest/entities/DataVersion.h>

#include <iostream>

#include <sysmlv2/rest/entities/Commit.h>
#include <sysmlv2/rest/entities/DataIdentity.h>
#include <sysmlv2/rest/entities/JSONEntities.h>
#include <sysmlv2/rest/entities/Data.h>
#include <sysmlv2/rest/serialization/SysMLv2Deserializer.h>

#include <boost/uuid/random_generator.hpp>
#include <nlohmann/json.hpp>
#include "RestJson.h"

namespace SysMLv2::REST {
    namespace {
        /** The reference to the identity as it is written in a DataVersion: {"@id": ..., "@type": "DataIdentity"}. */
        nlohmann::json identityToJson(const std::shared_ptr<DataIdentity>& identity) {
            nlohmann::json json = nlohmann::json::object();
            json[JSON_ID_ENTITY] = boost::uuids::to_string(identity->getId());
            json[JSON_TYPE_ENTITY] = "DataIdentity";
            return json;
        }
    }

    DataVersion::DataVersion(std::shared_ptr<Data> payload, std::shared_ptr<DataIdentity> identity, boost::uuids::uuid id) : Record(id) {
        Type = "DataVersion";
        Payload = std::move(payload);
        if (identity != nullptr) {
            if (Payload != nullptr && Payload->getId() != identity->getId())
                throw std::invalid_argument("DataVersion: the id of the identity must be the id of the payload");
            Identity = std::move(identity);
            IdentityGiven = true;
        } else if (Payload != nullptr) {
            Identity = std::make_shared<DataIdentity>(Payload->getId());
        } else {
            throw std::invalid_argument("DataVersion: a version without payload (a deletion) needs an identity");
        }
    }

    DataVersion::DataVersion(boost::uuids::uuid id, std::shared_ptr<Data> payload) : Record(boost::uuids::random_generator()()) {
        warnDeprecated("DataVersion(uuid, payload)", "DataVersion(payload, identity, id)");
        Type = "DataVersion";
        Payload = std::move(payload);
        if (Payload != nullptr) {
            // The uuid was ignored for a version with payload.
            Identity = std::make_shared<DataIdentity>(Payload->getId());
        } else {
            // A deletion: the uuid is the id of the deleted Data.
            Identity = std::make_shared<DataIdentity>(id);
            IdentityGiven = true;
        }
    }

    DataVersion::DataVersion(std::string jsonValue) : Record(jsonValue, "DataVersion")
    {
        Type = "DataVersion";
        DataVersion::deserializeAndPopulate(jsonValue);
    }

    DataVersion::~DataVersion() {

    }
    void DataVersion::setPayload(std::shared_ptr<Data> payload) {
        Payload = std::move(payload);
        if (!IdentityGiven && Payload != nullptr)
            Identity = std::make_shared<DataIdentity>(Payload->getId());
    }

    std::shared_ptr<Data> DataVersion::getPayload() {
        return Payload;
    }

    boost::uuids::uuid DataVersion::getId() const {
        if (Identity != nullptr)
            return Identity->getId();
        if (Payload != nullptr)
            return Payload->getId();
        return boost::uuids::nil_uuid();
    }

    boost::uuids::uuid DataVersion::getVersionId() const {
        return Record::getId();
    }

    std::shared_ptr<DataIdentity> DataVersion::getIdentity() const {
        return Identity;
    }

    std::shared_ptr<Commit> DataVersion::getCommit() const {
        return OwningCommit;
    }

    void DataVersion::setCommit(std::shared_ptr<Commit> commit) {
        OwningCommit = std::move(commit);
    }

    std::string DataVersion::serializeToJson()
    {
        nlohmann::json json = nlohmann::json::parse(Record::serializeToJson());

        // The identity is always set (the constructors and the JSON reader guarantee it).
        json[JSON_IDENTITY_ENTITY] = identityToJson(Identity);

        json[JSON_PAYLOAD_ENTITY] = Payload != nullptr ? nlohmann::json::parse(Payload->serializeToJson()) : nlohmann::json(nullptr);

        if (OwningCommit != nullptr)
            Internal::writeReference(json, JSON_COMMIT_ENTITY, OwningCommit->getId());

        return json.dump(JSON_INTENT);
    }

    std::string DataVersion::serializeAsRequest()
    {
        nlohmann::json json = nlohmann::json::object();
        json[JSON_TYPE_ENTITY] = "DataVersion";

        // A creation has no identity yet; update and deletion refer to the identity of the Data.
        if (IdentityGiven && Identity != nullptr)
            Internal::writeReference(json, JSON_IDENTITY_ENTITY, Identity->getId());

        json[JSON_PAYLOAD_ENTITY] = Payload != nullptr ? nlohmann::json::parse(Payload->serializeToJson()) : nlohmann::json(nullptr);

        return json.dump(JSON_INTENT);
    }

    void DataVersion::deserializeAndPopulate(const std::string& jsonString)
    {
        const nlohmann::json parsedJson = Internal::parseObject(jsonString, "DataVersion");
        Record::deserializeAndPopulate(jsonString);
        Type = "DataVersion";

        try {
            // payload
            Payload.reset();
            const auto payloadEntry = parsedJson.find(JSON_PAYLOAD_ENTITY);
            if (payloadEntry != parsedJson.end() && !payloadEntry->is_null()) {
                if (!payloadEntry->is_object())
                    throw std::invalid_argument("'" + JSON_PAYLOAD_ENTITY + "' must be an object or null");
                if (!payloadEntry->contains(JSON_ID_ENTITY) || !payloadEntry->contains(JSON_TYPE_ENTITY))
                    throw std::invalid_argument("'payload' needs '@id' and '@type'");
                const auto entity = SysMLv2::SysMLv2Deserializer::deserializeJsonString(payloadEntry->dump());
                Payload = std::dynamic_pointer_cast<Data>(entity);
                if (Payload == nullptr)
                    throw std::invalid_argument("'" + JSON_PAYLOAD_ENTITY + "' is no Data element (missing '@id' or unsuitable '@type')");
            }

            // identity
            Identity.reset();
            IdentityGiven = false;
            const auto identityEntry = parsedJson.find(JSON_IDENTITY_ENTITY);
            if (identityEntry != parsedJson.end() && !identityEntry->is_null()) {
                if (!identityEntry->is_object())
                    throw std::invalid_argument("'" + JSON_IDENTITY_ENTITY + "' must be an object or null");
                Identity = std::make_shared<DataIdentity>(identityEntry->dump());
                IdentityGiven = true;
                if (Payload != nullptr && Payload->getId() != Identity->getId())
                    throw std::invalid_argument("the id of the identity must be the id of the payload");
            } else if (Payload != nullptr) {
                // Requests that create Data have no identity. Earlier library versions did not write one either, and their
                // "@id" was the id of the payload.
                if (!Record::getId().is_nil() && Record::getId() == Payload->getId())
                    warnDeprecated("JSON of a DataVersion without \"identity\" (\"@id\" is the id of the payload)",
                                   "\"identity\" with the id of the payload and an own \"@id\"");
                Identity = std::make_shared<DataIdentity>(Payload->getId());
            } else {
                throw std::invalid_argument("'" + JSON_IDENTITY_ENTITY + "' is required if there is no payload");
            }

            // commit
            OwningCommit.reset();
            if (const auto commitId = Internal::readReference(parsedJson, JSON_COMMIT_ENTITY))
                OwningCommit = std::make_shared<Commit>(Internal::referenceObjectText(*commitId));
        } catch (const std::exception& ex) {
            const std::string message = ex.what();
            if (message.rfind("DataVersion: ", 0) == 0)
                throw std::invalid_argument(message);
            throw std::invalid_argument("DataVersion: " + message);
        }
    }
}
