//
// Created by Moritz Herzog on 27.02.24.
//

#include <nlohmann/json.hpp>
#include <sysmlv2/rest/entities/JSONEntities.h>
#include <sysmlv2/rest/entities/ExternalData.h>

namespace SysMLv2::REST {
    ExternalData::ExternalData(std::string jsonStringOrIRI) : Data(jsonStringOrIRI){
        try {
            ExternalData::deserializeAndPopulate(jsonStringOrIRI);
        }catch (...) {
            ResourceIdentifier = jsonStringOrIRI;
        }
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
        nlohmann::json parsedJson = nlohmann::json::parse(jsonString);
        ResourceIdentifier = parsedJson[JSON_RESOURCE_IDENTIFIER_ENTITY];
    }
} // SysMLv2::Entities