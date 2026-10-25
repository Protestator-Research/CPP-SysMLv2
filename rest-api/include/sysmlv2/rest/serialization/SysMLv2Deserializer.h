//
// Created by Moritz Herzog on 29.02.24.
//
//---------------------------------------------------------
// Constants, Definitions, Pragmas
//---------------------------------------------------------
#pragma once
//---------------------------------------------------------
// External Classes
//---------------------------------------------------------
#include <memory>
#include <vector>
//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include <sysmlv2/rest/entities/IEntity.h>
#include <sysmlv2/rest/sysmlv2rest_global.h>

namespace SysMLv2 {
    /**
     *
     */
    class SYSMLV2REST_EXPORT SysMLv2Deserializer {
    public:
        /**
         * Deserializes a single element, which is contained within the inputValue.
         * @param inputValue string of the element that is to deserialize
         * Every REST type is recognised by "@type" (case-insensitive): Project, Branch, Tag, Commit, DataIdentity, DataVersion,
         * DataDifference, ProjectUsage, ExternalData, ExternalRelationship, Query, PrimitiveConstraint and CompositeConstraint.
         * The request types share "@type" with the records and are returned as the record classes. Everything else with a string
         * "@id" is a KerML/SysML element. JSON null, a non-object or an unknown "@type" without "@id" gives nullptr.
         * @throws nlohmann::json::parse_error If the text is no JSON; the entity classes throw std::invalid_argument for invalid content.
         * @return the Element given as an IEntity.
         * @see SysMLv2::Entities::IEntity
         */
        static std::shared_ptr<SysMLv2::REST::IEntity> deserializeJsonString(std::string inputValue);

        /**
         * Deserializes a JSON Array, containing any number of Elements.
         * JSON null gives an empty vector; entries that are null or no entity are skipped.
         * @param inputValue The json string of the Array.
         * @return A vector of the entities.
         * @see std::vector
         * @see SysMLv2::Entities::IEntity
         */
        static std::vector<std::shared_ptr<SysMLv2::REST::IEntity>> deserializeJsonArray(std::string inputValue);
    };

} // SysMLv2
