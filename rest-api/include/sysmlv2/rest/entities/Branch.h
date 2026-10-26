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
         * @param jsonStringOrName A JSON object (the text starts with '{') or the name of the branch.
         * @throws std::invalid_argument If the text looks like JSON but is malformed or has values of a wrong type.
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

        /**
         * Sets the head. The referenced commit of the CommitReference is kept equal to the head.
         */
        void setHead(std::shared_ptr<Commit> head);

        /**
         * Sets the head (the referenced commit of a branch).
         * @deprecated Use setHead.
         */
        [[deprecated("Use Branch::setHead.")]]
        void setReferencedCommit(std::shared_ptr<Commit> referencedCommit);

protected:
        void deserializeAndPopulate(const std::string& jsonString) override;

        std::shared_ptr<Commit> Head;
    };
}
