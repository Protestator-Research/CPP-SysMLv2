//
// Created by Moritz Herzog on 27.02.24.
//
//---------------------------------------------------------
// Constants, Definitions, Pragmas
//---------------------------------------------------------
#pragma once
//---------------------------------------------------------
// External Classes
//---------------------------------------------------------
#include <boost/uuid/uuid.hpp>
#include <string>
//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include "IEntity.h"
#include "../sysmlv2rest_global.h"
//---------------------------------------------------------
// Forwarding
//---------------------------------------------------------

namespace SysMLv2::REST {

    /**
     * Represents an abstract baseclass that is used for the SysMLv2 API
     * @class Record
     * @author Moritz Herzog
     * @version 1.0
     */
    class SYSMLV2REST_EXPORT Data  : public IEntity {
    public:
        /**
         * C-Tor
         */
        Data();

        /**
         * C-Tor with the option to set the id.
         * @param id The given ID of the Data element
         */
        explicit Data(boost::uuids::uuid id);

        /**
         * C-Tor allowing for the parsing of the JSON String.
         * @param jsonString The JSON string that is to be parsed.
         */
        explicit Data(std::string jsonString);

        /**
         * D-Tor
         */
        virtual ~Data() = default;

        /**
         * Returns the Id that was given.
         * @return The Id as a UUID
         * @see boost::uuids::uuid
         */
        boost::uuids::uuid getId();

        /**
         * Returns the type of the data element.
         * @return Type as a String
         */
        std::string getType();

        std::string serializeToJson() override;
    protected:
        /**
         * Type of the element.
         */
        std::string Type;
        boost::uuids::uuid Id;
    private:
        
    };
}
