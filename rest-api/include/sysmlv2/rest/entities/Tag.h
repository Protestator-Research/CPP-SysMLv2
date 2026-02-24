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
    class Project;
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

        Tag(std::string name, std::shared_ptr<Project> owningProject, std::shared_ptr<Commit> referencedCommit);

        [[nodiscard]] std::shared_ptr<Project> owningProject() const;
        void setOwningProject(std::shared_ptr<Project> owningProject);

        std::string serializeToJson() override;
    protected:
        void deserializeAndPopulate(const std::string &jsonString) override;

    private:
        std::shared_ptr<Project> OwningProject;
    };
}
