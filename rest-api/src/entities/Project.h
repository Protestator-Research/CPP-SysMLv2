//
// Created by Moritz Herzog on 20.02.24.
//
//---------------------------------------------------------
// Constants, Definitions, Pragmas
//---------------------------------------------------------
#ifndef DIGITALTWIN_PROJECT_H
#define DIGITALTWIN_PROJECT_H
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
#include "Record.h"
//---------------------------------------------------------
// Forwarding
//---------------------------------------------------------
namespace SysMLv2::Entities {
    class DataVersion;
    class DataIdentity;
    class Commit;
    class CommitReference;
    class Branch;
    class ProjectUsage;
    class Tag;
    class Query;
}


namespace SysMLv2::Entities {
    /**
     * Represents the object of the Project entity.
     * @class Project
     * @author Moritz Herzog
     * @version 1.0
     */
    class Project  : public Record {
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
        explicit Project(std::string JsonString);

        Project(std::string projectName, std::string projectDescription, std::string branchName);

        virtual ~Project();

        std::shared_ptr<Branch> getDefaultBranch();
        void setDefaultBranch(std::shared_ptr<Branch> branch);

        std::string serializeToJson() override;

    private:
        std::shared_ptr<DataVersion> m_DataVersion;


        std::chrono::system_clock::time_point Created;

        std::vector<std::shared_ptr<Commit>> Commits;
        std::vector<std::shared_ptr<CommitReference>> CommitReferences;
        std::vector<std::shared_ptr<Branch>> Branches;
        std::shared_ptr<Branch> DefaultBranch;
        std::vector<std::shared_ptr<Tag>> Tags;
        std::vector<std::shared_ptr<ProjectUsage>> ProjectUsages;
        std::vector<std::shared_ptr<Query>> Querries;
    };
}

#endif //DIGITALTWIN_PROJECT_H
