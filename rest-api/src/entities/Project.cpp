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
#include <boost/uuid/random_generator.hpp>
//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include "Project.h"
#include "DataIdentity.h"
#include "DataVersion.h"
#include "CommitReference.h"
#include "Commit.h"
#include "JSONEntities.h"
#include "Branch.h"
#include "ProjectUsage.h"
#include "Tag.h"
#include "Query.h"


namespace SysMLv2::Entities {
    Project::Project(Project &other) : Record(other) {
        Created = other.Created;

        Commits = other.Commits;

        CommitReferences = other.CommitReferences;

        DefaultBranch = other.DefaultBranch;
        Branches = other.Branches;

        Tags = other.Tags;

        ProjectUsages = other.ProjectUsages;

        Querries = other.Querries;
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
        }
    }

    Project::~Project() {
        Commits.clear();
        CommitReferences.clear();
        Branches.clear();
        Tags.clear();
        ProjectUsages.clear();
        Querries.clear();
    }

    std::shared_ptr<Branch> Project::getDefaultBranch() {
        return DefaultBranch;
    }

    std::string Project::serializeToJson() {
        nlohmann::json jsonDocument;
        if (IsForCreation)
        {
            jsonDocument[JSON_NAME_ENTITY] = Name;
            jsonDocument[JSON_DESCRIPTION_ENTITY] = Description;
            jsonDocument["defaultBranchName"] = DefaultBranch->getName();
        }else
        {
            return Record::serializeToJson();
        }
        return jsonDocument.dump(JSON_INTENT);
    }

    Project::Project(std::string projectName, std::string projectDescription, std::string branchName) : Record(projectName){
        Description = projectDescription;
        DefaultBranch = std::make_shared<Branch>(branchName);
        IsForCreation = true;
        Record::Id = boost::uuids::random_generator()();
    }
}
