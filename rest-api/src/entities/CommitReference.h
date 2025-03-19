//
// Created by Moritz Herzog on 23.02.24.
//
//---------------------------------------------------------
// Constants, Definitions, Pragmas
//---------------------------------------------------------
#ifndef DIGITALTWIN_COMMITREFERENCE_H
#define DIGITALTWIN_COMMITREFERENCE_H
//---------------------------------------------------------
// External Classes
//---------------------------------------------------------
#include <chrono>
//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include "Record.h"

//---------------------------------------------------------
// Forwarding
//---------------------------------------------------------
namespace SysMLv2::Entities{
    class Commit;
}


namespace SysMLv2::Entities {
    /**
     * Represents an abstract baseclass that is used for the SysMLv2 API
     * @class Record
     * @author Moritz Herzog
     * @version 1.0
     */
    class CommitReference : public Record {
    public:

        /**
         *
         * @param jsonStringOrName
         */
        CommitReference(std::string jsonStringOrName);

        /**
         *
         * @param other
         * @return
         */
        bool operator==(CommitReference& other);

        std::string serializeToJson() override;
    protected:
        std::chrono::system_clock::time_point Created;
        Commit* ReferencedCommit;
    };
}

#endif //DIGITALTWIN_COMMITREFERENCE_H
