//
// Created by Moritz Herzog on 27.02.24.
//

#include <nlohmann/json.hpp>
#include <sysmlv2/rest/entities/ExternalRelationship.h>

#include "sysmlv2/rest/entities/JSONEntities.h"

namespace SysMLv2::REST {
    ExternalRelationship::ExternalRelationship(std::string jsonString) : Data(jsonString){
        ExternalRelationship::deserializeAndPopulate(jsonString);
    }

    ExternalRelationship::ExternalRelationship(std::string specification, std::string language) {
        Specification = specification;
        Language = language;
    }

    void ExternalRelationship::setLanguage(std::string lanuage) {
        Language = lanuage;
    }

    std::string ExternalRelationship::language() {
        return Language;
    }

    void ExternalRelationship::setSpecification(std::string specification) {
        Specification = specification;
    }

    std::string ExternalRelationship::specification() {
        return Specification;
    }

    std::string ExternalRelationship::serializeToJson() {
        nlohmann::json json = nlohmann::json::parse(Data::serializeToJson());
        json[JSON_SPECIFICATION_ENTITY] = Specification;
        json[JSON_LANGUAGE_ENTITY] = Language;
        return json.dump(JSON_INTENT);
    }

    void ExternalRelationship::deserializeAndPopulate(const std::string &jsonString) {
        nlohmann::json parsedJson = nlohmann::json::parse(jsonString);

        Specification = parsedJson[JSON_SPECIFICATION_ENTITY].get<std::string>();
        Language = parsedJson[JSON_LANGUAGE_ENTITY].get<std::string>();
    }
} // SysMLv2