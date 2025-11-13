//
// Created by Moritz Herzog on 19.02.24.
//
//---------------------------------------------------------
// Constants, Definitions, Pragmas
//---------------------------------------------------------
#pragma once
//---------------------------------------------------------
// External Classes
//---------------------------------------------------------
#include <string>
//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include <sysmlv2/interfaces/sysmlv2interfaces_global.h>
//---------------------------------------------------------
// Forwarding
//---------------------------------------------------------


namespace SysMLv2::REST {
    /**
     * Defines the interface for all SysMLv2 classes.
     * @class IEntity
     * @author Moritz Herzog
     * @version 1.0
     */
    class SYSMLV2INTERFACE_EXPORT IEntity {
    public:

        /**
         * Allows the serialization of the Object to a JSON String.
         * @return JSON String of the Object
         */
        virtual std::string serializeToJson() = 0;
    protected:
        /**
         * Deserializes an element and populates the given Instance.
         * Only called from the Constructor.
         * @param jsonString Should be the json string that is requried by the software to build the object. 
         */
        virtual void deserializeAndPopulate(const std::string& jsonString) = 0;

        /**
         * Describes the intent of nlohmanns json library.
         * @see nlohmann::json::dump
         */
        const int JSON_INTENT = 2;
    };
}

