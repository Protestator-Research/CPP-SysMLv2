//
// Created by Moritz Herzog on 05.09.24.
//
//---------------------------------------------------------
// Constants, Definitions, Pragmas
//---------------------------------------------------------
#pragma once
//---------------------------------------------------------
// External Classes
//---------------------------------------------------------
#include <boost/uuid/uuid.hpp>
#include <nlohmann/json.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/uuid/string_generator.hpp>
#include <boost/uuid/random_generator.hpp>
//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include <sysmlv2/rest/entities/IEntity.h>
#include <sysmlv2/rest/entities/JSONEntities.h>
#include <sysmlv2/rest/sysmlv2rest_global.h>
//---------------------------------------------------------
// Forwarding
//---------------------------------------------------------


namespace SysMLv2::REST {
    /**
     * Defines the Identification between Objects of the REST API. This not in accordance with the SysML standardization,
     * but needed for the compatibility to the AGILA Backend.
     * @version 1.0
     * @author Moritz Herzog
     * @class Identification
     */
    class SYSMLV2REST_EXPORT Identification : public IEntity {
    public:
        /**
         * CTOR deleted
         */
        Identification() = default;

        /**
         * Builds the Idenfication object from the uuid
         * @param id The uuid of the object
         * @see boost::uuids::uuid
         */
        explicit Identification(boost::uuids::uuid id);

        /**
         * C-Tor for the parsing of the Identification object.
         * @param JSONstring JSON string of the object.
         */
        explicit Identification(std::string JSONstring);

        /**
         * D-Tor
         */
        virtual ~Identification() = default;

        /**
         * Returns the Id of the given Object.
         * @return Id of the object as uuid
         * @see boost::uuids::uuid
         */
        boost::uuids::uuid getID() const;

        std::string serializeToJson() override;

        Identification& operator=(const Identification& other);

    protected:
        boost::uuids::uuid Id = boost::uuids::random_generator()();
    };
}

inline void to_json(nlohmann::json &j, const SysMLv2::REST::Identification &ident) {
    j = nlohmann::json{{SysMLv2::REST::JSON_ID_ENTITY, boost::lexical_cast<std::string>(ident.getID())}};
}

inline void to_json(nlohmann::json &j, const SysMLv2::REST::Identification* ident) {
    if(ident != nullptr)
        j = nlohmann::json{{SysMLv2::REST::JSON_ID_ENTITY, boost::lexical_cast<std::string>(ident->getID())}};
    else
        j = nlohmann::json(nlohmann::detail::value_t::null);
}

inline void from_json(const nlohmann::json &j, SysMLv2::REST::Identification &ident) {
    ident = SysMLv2::REST::Identification(boost::uuids::string_generator()(j[SysMLv2::REST::JSON_ID_ENTITY].get<std::string>()));
}
