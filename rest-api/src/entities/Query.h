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
#include "Record.h"
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
    class SYSMLV2REST_EXPORT Query : public Record {
    public:
        explicit Query(std::string jsonString);

        std::string serializeToJson() override;
    };
}
