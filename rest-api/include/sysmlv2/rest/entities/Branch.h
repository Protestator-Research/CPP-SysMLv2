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
#include <memory>
//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include <sysmlv2/rest/entities/CommitReference.h>
#include <sysmlv2/rest/sysmlv2rest_global.h>
//---------------------------------------------------------
// Forwarding
//---------------------------------------------------------

namespace SysMLv2::REST {
    class Commit;

    /**
     * Represents an Branch that is used for the SysMLv2 API
     * @class Branch
     * @author Moritz Herzog
     * @version 1.0
     */
    class SYSMLV2REST_EXPORT Branch : public CommitReference {
    public:
        /**
         * 
         * @param jsonStringOrName
         */
        Branch(std::string jsonStringOrName);

        /**
         * Compares the two Branches
         * @param other
         * @return
         */
        bool operator==(Branch& other);

        std::string serializeToJson() override;

        /**
         * Returns the Current head of the given Branch.
         * @return A Commit
         * @see SysMLv2::Entities::Commit
         */
        std::shared_ptr<Commit> getHead();

        void setHead(std::shared_ptr<Commit> head);
    protected:
        std::shared_ptr<Commit> Head;
    };
}
