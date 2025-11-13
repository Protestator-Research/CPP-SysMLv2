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
#include <sysmlv2/rest/entities/IEntity.h>
#include <sysmlv2/interfaces/sysmlv2interfaces_global.h>
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
    class SYSMLV2INTERFACE_EXPORT Data  : public IEntity {
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
        void deserializeAndPopulate(const std::string& jsonString) override;

        /**
         * Type of the element.
         */
        std::string _dType;
        boost::uuids::uuid _dId;
    private:
        
    };
}
