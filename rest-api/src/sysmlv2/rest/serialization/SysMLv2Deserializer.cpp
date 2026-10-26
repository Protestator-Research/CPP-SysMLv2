//
// Created by Moritz Herzog on 29.02.24.
//

#include <sysmlv2/rest/serialization/SysMLv2Deserializer.h>
#include <sysmlv2/rest/entities/JSONEntities.h>
#include <sysmlv2/rest/entities/Project.h>
#include <sysmlv2/rest/entities/DataIdentity.h>
#include <sysmlv2/rest/entities/Branch.h>
#include <sysmlv2/rest/entities/Tag.h>
#include <sysmlv2/rest/entities/Query.h>
#include <sysmlv2/rest/entities/Commit.h>
#include <sysmlv2/rest/entities/Constraint.h>
#include <sysmlv2/rest/entities/DataDifference.h>
#include <sysmlv2/rest/entities/DataVersion.h>
#include <sysmlv2/rest/entities/ExternalData.h>
#include <sysmlv2/rest/entities/ExternalRelationship.h>
#include <sysmlv2/rest/entities/ProjectUsage.h>
#include <stdexcept>
#include <nlohmann/json.hpp>
#include <vector>
#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <string>

#include "kerml/root/annotations/TextualRepresentation.h"
#include "kerml/root/elements/Element.h"
#include "kerml/model/ElementFactory.h"
#include "kerml/model/ElementLinker.h"
#include "sysml/model/ElementFactory.h"

namespace SysMLv2 {
    namespace {
        // Lower case "@type" values of the REST types that are not listed in JSONEntities.h.
        const std::string DATA_DIFFERENCE_TYPE = "datadifference";
        const std::string PROJECT_USAGE_TYPE = "projectusage";
        const std::string EXTERNAL_DATA_TYPE = "externaldata";
        const std::string EXTERNAL_RELATIONSHIP_TYPE = "externalrelationship";
        const std::string PRIMITIVE_CONSTRAINT_TYPE = "primitiveconstraint";
        const std::string COMPOSITE_CONSTRAINT_TYPE = "compositeconstraint";
    }

    std::shared_ptr<SysMLv2::REST::IEntity> SysMLv2Deserializer::deserializeJsonString(std::string inputValue) {

        const nlohmann::json json = nlohmann::json::parse(inputValue);

        // "null" is an absent entity (for example a deleted payload), and only an object can be an entity.
        if (!json.is_object())
            return nullptr;

        // Without a (string) "@type" only the fallback for model elements with an "@id" applies, see below.
        std::string type;
        const auto typeEntry = json.find(REST::JSON_TYPE_ENTITY);
        if (typeEntry != json.end() && typeEntry->is_string()) {
            type = typeEntry->get<std::string>();
            std::transform(type.begin(), type.end(), type.begin(), [](unsigned char c) { return std::tolower(c); });
        }

        // The request types (ProjectRequest, BranchRequest, TagRequest, CommitRequest, QueryRequest) share the "@type" with the
        // records of the responses. This deserializer reads responses, so these types are restored as the record classes.
        // MergeResult has no "@type" of its own (the response is a Commit or an array of DataIdentity) and is not created here.
        if(type==REST::PROJECT_TYPE)
            return std::make_shared<REST::Project>(inputValue);

        if(type==REST::DATA_IDENTITY_TYPE)
            return std::make_shared<REST::DataIdentity>(inputValue);

        if(type==REST::DATA_VERSION_TYPE)
            return std::make_shared<REST::DataVersion>(inputValue);

        if(type==DATA_DIFFERENCE_TYPE)
            return std::make_shared<REST::DataDifference>(inputValue);

        if(type==REST::BRANCH_TYPE)
            return std::make_shared<REST::Branch>(inputValue);

        if(type==REST::TAG_TYPE)
            return std::make_shared<REST::Tag>(inputValue);

        if(type==REST::QUERY_TYPE)
            return std::make_shared<REST::Query>(inputValue);

        if(type==REST::COMMIT_TYPE)
            return std::make_shared<REST::Commit>(inputValue);

        if(type==PROJECT_USAGE_TYPE)
            return std::make_shared<REST::ProjectUsage>(inputValue);

        if(type==EXTERNAL_DATA_TYPE)
            return std::make_shared<REST::ExternalData>(inputValue);

        if(type==EXTERNAL_RELATIONSHIP_TYPE)
            return std::make_shared<REST::ExternalRelationship>(inputValue);

        if(type==PRIMITIVE_CONSTRAINT_TYPE || type==COMPOSITE_CONSTRAINT_TYPE)
            return REST::Constraint::fromJsonValue(json);

        if (type==REST::TEXTUAL_REPRESENTATION_TYPE)
            return std::make_shared<KerML::Entities::TextualRepresentation>(inputValue);

        // Every other type ("Element", "Package", "PartDefinition", "Feature", ...) is an element of the model, as long as
        // it has an identifier. The SysML and KerML metaclasses ("PartUsage", "Package", "Feature", ...) are restored as objects of
        // their class, every other type as a plain Element that keeps the original type and JSON (see
        // SysMLv2::Entities::createElementFromJson, which falls back to KerML::Entities::createElementFromJson).
        const auto id = json.find(REST::JSON_ID_ENTITY);
        if (id != json.end() && id->is_string())
            return SysMLv2::Entities::createElementFromJson(inputValue);

        return nullptr;
    }

    std::vector<std::shared_ptr<SysMLv2::REST::IEntity>> SysMLv2Deserializer::deserializeJsonArray(std::string inputValue) {
        const nlohmann::json json = nlohmann::json::parse(inputValue);
        std::vector<std::shared_ptr<SysMLv2::REST::IEntity>> returnValues;

        // A JSON null is an empty list.
        if (json.is_null())
            return returnValues;
        if (!json.is_array())
            throw std::invalid_argument("SysMLv2Deserializer: the JSON text is no array");

        returnValues.reserve(json.size());
        for(const nlohmann::json& elem : json) {
            // Entries that are null (or no entity) are skipped; they are no entities.
            if (auto entity = SysMLv2Deserializer::deserializeJsonString(elem.dump()))
                returnValues.emplace_back(std::move(entity));
        }

        // The elements of one array belong together: their references are resolved by the element ids and their derived properties
        // (owner, ownedElement, the members of the namespaces, ...) are rebuilt. What stays unresolved is written back unchanged.
        std::vector<std::shared_ptr<KerML::Entities::Element>> elements;
        for (const auto& value : returnValues) {
            if (auto element = std::dynamic_pointer_cast<KerML::Entities::Element>(value))
                elements.push_back(std::move(element));
        }
        KerML::Entities::linkElements(elements);
        return returnValues;
    }

} // SysMLv2
