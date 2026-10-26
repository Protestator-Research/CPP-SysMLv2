//
// Created by Moritz Herzog on 27.02.24.
//

#include <nlohmann/json.hpp>
#include <boost/uuid/random_generator.hpp>
#include <sysmlv2/rest/entities/ExternalRelationship.h>

#include "sysmlv2/rest/entities/JSONEntities.h"
#include "RestJson.h"

namespace SysMLv2::REST {
    namespace {
        boost::uuids::uuid idOfJson(const std::string& jsonString) {
            const auto json = Internal::parseObject(jsonString, "ExternalRelationship");
            try {
                return Internal::readId(json);
            } catch (const std::exception& ex) {
                throw std::invalid_argument(std::string("ExternalRelationship: ") + ex.what());
            }
        }
    }

    ExternalRelationship::ExternalRelationship(std::string jsonString) : Data(idOfJson(jsonString), "ExternalRelationship"){
        ExternalRelationship::deserializeAndPopulate(jsonString);
    }

    ExternalRelationship::ExternalRelationship(std::string specification, std::string language) :
        Data(boost::uuids::random_generator()(), "ExternalRelationship") {
        Specification = specification;
        Language = language;
    }

    ExternalRelationship::ExternalRelationship(std::shared_ptr<Data> elementEnd, std::shared_ptr<ExternalData> externalDataEnd,
                                               std::string specification, std::string language) :
        Data(boost::uuids::random_generator()(), "ExternalRelationship") {
        ElementEnd = std::move(elementEnd);
        ExternalDataEnd = std::move(externalDataEnd);
        Specification = std::move(specification);
        Language = std::move(language);
    }

    void ExternalRelationship::setLanguage(std::string lanuage) {
        Language = lanuage;
    }

    std::string ExternalRelationship::language() const {
        return Language;
    }

    void ExternalRelationship::setSpecification(std::string specification) {
        Specification = specification;
    }

    std::string ExternalRelationship::specification() const {
        return Specification;
    }

    std::shared_ptr<Data> ExternalRelationship::elementEnd() const {
        return ElementEnd;
    }

    void ExternalRelationship::setElementEnd(std::shared_ptr<Data> elementEnd) {
        ElementEnd = std::move(elementEnd);
    }

    std::shared_ptr<ExternalData> ExternalRelationship::externalDataEnd() const {
        return ExternalDataEnd;
    }

    void ExternalRelationship::setExternalDataEnd(std::shared_ptr<ExternalData> externalDataEnd) {
        ExternalDataEnd = std::move(externalDataEnd);
    }

    std::string ExternalRelationship::serializeToJson() {
        nlohmann::json json = nlohmann::json::parse(Data::serializeToJson());
        Internal::writeReference(json, JSON_ELEMENT_END_ENTITY,
                                 ElementEnd != nullptr ? std::optional<boost::uuids::uuid>(ElementEnd->getId()) : std::nullopt);
        Internal::writeReference(json, JSON_EXTERNAL_DATA_END_ENTITY,
                                 ExternalDataEnd != nullptr ? std::optional<boost::uuids::uuid>(ExternalDataEnd->getId()) : std::nullopt);
        // specification and language are optional.
        if (!Specification.empty())
            json[JSON_SPECIFICATION_ENTITY] = Specification;
        if (!Language.empty())
            json[JSON_LANGUAGE_ENTITY] = Language;
        return json.dump(JSON_INTENT);
    }

    void ExternalRelationship::deserializeAndPopulate(const std::string &jsonString) {
        const nlohmann::json parsedJson = Internal::parseObject(jsonString, "ExternalRelationship");
        try {
            if (const auto id = Internal::readOptionalId(parsedJson))
                _dId = *id;
            _dType = "ExternalRelationship";

            Specification = Internal::readOptionalString(parsedJson, JSON_SPECIFICATION_ENTITY);
            Language = Internal::readOptionalString(parsedJson, JSON_LANGUAGE_ENTITY);

            ElementEnd.reset();
            ExternalDataEnd.reset();
            if (const auto elementId = Internal::readReference(parsedJson, JSON_ELEMENT_END_ENTITY))
                ElementEnd = std::make_shared<Data>(*elementId);
            if (const auto dataId = Internal::readReference(parsedJson, JSON_EXTERNAL_DATA_END_ENTITY))
                ExternalDataEnd = std::make_shared<ExternalData>(Internal::referenceObjectText(*dataId));
        } catch (const std::exception& ex) {
            throw std::invalid_argument(std::string("ExternalRelationship: ") + ex.what());
        }
    }
} // SysMLv2
