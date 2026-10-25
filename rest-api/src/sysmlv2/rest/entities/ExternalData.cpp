//
// Created by Moritz Herzog on 27.02.24.
//

#include <nlohmann/json.hpp>
#include <boost/uuid/random_generator.hpp>
#include <sysmlv2/rest/entities/ExternalData.h>
#include "sysmlv2/rest/entities/JSONEntities.h"
#include "RestJson.h"

namespace SysMLv2::REST {
    namespace {
        /** The id of the JSON text; a new id if the text is no JSON (an IRI). */
        boost::uuids::uuid idOfJsonOrNew(const std::string& jsonStringOrIRI) {
            if (!Internal::looksLikeJson(jsonStringOrIRI))
                return boost::uuids::random_generator()();
            const auto json = Internal::parseObject(jsonStringOrIRI, "ExternalData");
            try {
                return Internal::readId(json);
            } catch (const std::exception& ex) {
                throw std::invalid_argument(std::string("ExternalData: ") + ex.what());
            }
        }
    }

    ExternalData::ExternalData(std::string jsonStringOrIRI) : Data(idOfJsonOrNew(jsonStringOrIRI), "ExternalData"){
        if (Internal::looksLikeJson(jsonStringOrIRI))
            ExternalData::deserializeAndPopulate(jsonStringOrIRI);
        else
            ResourceIdentifier = jsonStringOrIRI;
    }

    void ExternalData::setResourceIdentifier(std::string resourceIdentifier) {
        ResourceIdentifier = resourceIdentifier;
    }

    std::string ExternalData::resourceIdentifier() const {
        return ResourceIdentifier;
    }

    std::string ExternalData::serializeToJson() {
        nlohmann::json json = nlohmann::json::parse(Data::serializeToJson());
        json[JSON_RESOURCE_IDENTIFIER_ENTITY] = ResourceIdentifier;
        return json.dump(JSON_INTENT);
    }

    void ExternalData::deserializeAndPopulate(const std::string &jsonString) {
        const nlohmann::json parsedJson = Internal::parseObject(jsonString, "ExternalData");
        try {
            if (const auto id = Internal::readOptionalId(parsedJson))
                _dId = *id;
            _dType = "ExternalData";
            ResourceIdentifier = Internal::readOptionalString(parsedJson, JSON_RESOURCE_IDENTIFIER_ENTITY);
        } catch (const std::exception& ex) {
            throw std::invalid_argument(std::string("ExternalData: ") + ex.what());
        }
    }
} // SysMLv2::Entities
