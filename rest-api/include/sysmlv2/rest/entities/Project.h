//
// Created by Moritz Herzog on 20.02.24.
//
//---------------------------------------------------------
// Constants, Definitions, Pragmas
//---------------------------------------------------------
#pragma once
//---------------------------------------------------------
// External Classes
//---------------------------------------------------------
#include <boost/uuid/uuid.hpp>
#include <chrono>
#include <string>
#include <memory>
#include <vector>
//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include <sysmlv2/rest/entities/Record.h>
#include <sysmlv2/rest/sysmlv2rest_global.h>
//---------------------------------------------------------
// Forwarding
//---------------------------------------------------------
namespace SysMLv2::REST {
    class DataVersion;
    class DataIdentity;
    class Commit;
    class CommitReference;
    class Branch;
    class ProjectUsage;
    class Tag;
    class Query;
}


namespace SysMLv2::REST {
    /**
     * Represents the object of the Project entity.
     * @class Project
     * @author Moritz Herzog
     * @version 1.0
     */
    class SYSMLV2REST_EXPORT Project  : public Record {
    public:
        /**
         * Constructor
         */
        Project() = delete;

        /**
         * Copy constructor
         * @param other
         */
        Project(Project &other);

        /**
         * Generates a Project object from a JSON string. This will be used for the JSON interface of the Parser.
         * @param JsonString
         */
        explicit Project(const std::string& JsonString);

        /**
         * Creates a project from the given elements.
         * @param projectName The name of the Project that is given by the user.
         * @param projectDescription The description of the Project, given by the user.
         * @param branchName The default branch name, that can be changed.
         */
        Project(std::string projectName, std::string projectDescription, std::string branchName);

        /**
         * Destructor.
         */
        ~Project() override;

        /**
         * Allows to get the default branch.
         * @return
         */
        std::shared_ptr<Branch> getDefaultBranch();
        void setDefaultBranch(std::shared_ptr<Branch> branch);

        std::string serializeToJson() override;

    protected:
        std::shared_ptr<DataVersion> m_DataVersion;


        std::chrono::system_clock::time_point Created;

        std::vector<std::shared_ptr<Commit>> Commits;
        std::vector<std::shared_ptr<CommitReference>> CommitReferences;
        std::vector<std::shared_ptr<Branch>> Branches;
        std::shared_ptr<Branch> DefaultBranch;
        std::vector<std::shared_ptr<Tag>> Tags;
        std::vector<std::shared_ptr<ProjectUsage>> ProjectUsages;
        std::vector<std::shared_ptr<Query>> Queries;
    };
}
