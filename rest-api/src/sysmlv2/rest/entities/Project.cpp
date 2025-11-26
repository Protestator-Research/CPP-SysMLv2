//
// Created by Moritz Herzog on 20.02.24.
//
//---------------------------------------------------------
// Constants, Definitions, Pragmas
//---------------------------------------------------------

//---------------------------------------------------------
// External Classes
//---------------------------------------------------------
#include <nlohmann/json.hpp>
#include <vector>
#include <sstream>
#include <date/date.h>
#include <boost/uuid/string_generator.hpp>
#include <iostream>
#include <boost/uuid/random_generator.hpp>
//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include <sysmlv2/rest/entities/Project.h>
#include <sysmlv2/rest/entities/DataIdentity.h>
#include <sysmlv2/rest/entities/DataVersion.h>
#include <sysmlv2/rest/entities/CommitReference.h>
#include <sysmlv2/rest/entities/Commit.h>
#include <sysmlv2/rest/entities/JSONEntities.h>
#include <sysmlv2/rest/entities/Branch.h>
#include <sysmlv2/rest/entities/ProjectUsage.h>
#include <sysmlv2/rest/entities/Tag.h>
#include <sysmlv2/rest/entities/Query.h>


namespace SysMLv2::REST {
    Project::Project(Project &other) : Record(other) {
        Type = other.Type;
        Created = other.Created;

        Commits = other.Commits;

        CommitReferences = other.CommitReferences;

        DefaultBranch = other.DefaultBranch;
        Branches = other.Branches;

        Tags = other.Tags;

        ProjectUsages = other.ProjectUsages;

        Queries = other.Queries;
        m_DataVersion = other.m_DataVersion;
    }

    Project::Project(std::string JsonString) : Record(JsonString) {
        try {
            nlohmann::json parsedJson = nlohmann::json::parse(JsonString);

            const auto branch = parsedJson[JSON_DEFAULT_BRANCH_ENTITY];
            if(!branch.empty())
                DefaultBranch = std::make_shared<Branch>(branch.dump());

        }
        catch (...) {
            Name = JsonString;
            Type = "Project";
        }
    }

    Project::~Project() {
        Commits.clear();
        CommitReferences.clear();
        Branches.clear();
        Tags.clear();
        ProjectUsages.clear();
        Queries.clear();
    }

    std::shared_ptr<Branch> Project::getDefaultBranch() {
        return DefaultBranch;
    }

    std::string Project::serializeToJson() {
        return Record::serializeToJson();
    }

    Project::Project(std::string projectName, std::string projectDescription, std::string branchName) : Record(projectName){
        Type = "Project";
        Description = projectDescription;
        DefaultBranch = std::make_shared<Branch>(branchName);
        Record::Id = boost::uuids::random_generator()();
    }

    void Project::setDefaultBranch(std::shared_ptr<Branch> branch) {
        DefaultBranch = branch;
        Branches.push_back(branch);
    }
}
