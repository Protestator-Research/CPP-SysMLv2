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
#include <optional>
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
         * Generates a Project object from a JSON string or from a plain name. This will be used for the JSON interface of the Parser.
         * @param JsonString A JSON object (the text starts with '{') or the name of the Project.
         * @throws std::invalid_argument If the text looks like JSON but is malformed or has values of a wrong type.
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

        /**
         * Sets the default branch. The branch is also added to the branches of the project, if it is not contained yet.
         * @param branch The new default branch.
         */
        void setDefaultBranch(std::shared_ptr<Branch> branch);

        /**
         * All branches of the project. The default branch is contained.
         */
        [[nodiscard]] std::vector<std::shared_ptr<Branch>> getBranches() const;

        /**
         * The creation time of the project. Empty if the project was read from JSON without "created".
         */
        [[nodiscard]] std::optional<std::chrono::system_clock::time_point> getCreated() const;

        std::string serializeToJson() override;

    protected:
        void deserializeAndPopulate(const std::string& jsonString) override;

        std::shared_ptr<DataVersion> m_DataVersion;


        std::optional<std::chrono::system_clock::time_point> Created;

        std::vector<std::shared_ptr<Commit>> Commits;
        std::vector<std::shared_ptr<CommitReference>> CommitReferences;
        std::vector<std::shared_ptr<Branch>> Branches;
        std::shared_ptr<Branch> DefaultBranch;
        std::vector<std::shared_ptr<Tag>> Tags;
        std::vector<std::shared_ptr<ProjectUsage>> ProjectUsages;
        std::vector<std::shared_ptr<Query>> Queries;
    };
}
