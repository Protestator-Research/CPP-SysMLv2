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
#include <sysmlv2/rest/sysmlv2rest_global.h>
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
    class SYSMLV2REST_EXPORT IEntity {
    public:

        /**
         * Allows the serialization of the Object to a JSON String.
         * @return JSON String of the Object
         */
        virtual std::string serializeToJson() = 0;
    protected:
        /**
         * Describes the intent of nlohmanns json library.
         * @see nlohmann::json::dump
         */
        const int JSON_INTENT = 2;
    };
}

