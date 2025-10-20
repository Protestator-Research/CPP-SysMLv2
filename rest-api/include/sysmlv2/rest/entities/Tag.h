//
// Created by Moritz Herzog on 23.02.24.
//
//---------------------------------------------------------
// Constants, Definitions, Pragmas
//---------------------------------------------------------
#pragma once
//---------------------------------------------------------
// External Classes
//---------------------------------------------------------

//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include <sysmlv2/rest/entities/CommitReference.h>
#include <sysmlv2/rest/sysmlv2rest_global.h>
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
    class SYSMLV2REST_EXPORT Tag : public CommitReference {

    public:
        /**
         *
         * @param jsonStringOrName
         */
        Tag(std::string jsonStringOrName);

    };
}
