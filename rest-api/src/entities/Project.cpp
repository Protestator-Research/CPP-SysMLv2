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
        _DataVersion = other._DataVersion;
    }

    Project::Project(std::string JsonString) : Record(JsonString) {
        try {
            nlohmann::json parsedJson = nlohmann::json::parse(JsonString);

            const auto branch = parsedJson[JSON_DEFAULT_BRANCH_ENTITY];
            if(!branch.empty())
                DefaultBranch = new Branch(branch.dump());

        }
        catch (...) {
            Name = JsonString;
        }
    }

    Project::~Project() {

        for(auto elem : Commits)
            delete elem;
        Commits.clear();

        for(auto elem : CommitReferences)
            delete elem;
        CommitReferences.clear();

        for(auto elem : Branches)
            delete elem;
        Branches.clear();

//        if(DefaultBranch != nullptr)
//            delete DefaultBranch;

        for(auto elem : Tags)
            delete elem;
        Tags.clear();

        for(auto elem : ProjectUsages)
            delete elem;
        ProjectUsages.clear();

        for(auto elem : Querries)
            delete elem;
        Querries.clear();
    }

    Branch *Project::getDefaultBranch() {
        return nullptr;
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
        DefaultBranch = new Branch(branchName);
        IsForCreation = true;
    }
}
