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
#include <algorithm>
#include <stdexcept>
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
#include "RestJson.h"


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

    Project::Project(const std::string& JsonString) : Record(JsonString, "Project") {
        Type = "Project";
        // A text that is no JSON is the name of the project and was handled by Record.
        if (Internal::looksLikeJson(JsonString))
            Project::deserializeAndPopulate(JsonString);
        else
            Created = std::chrono::system_clock::now();
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
        nlohmann::json json = nlohmann::json::parse(Record::serializeToJson());

        Internal::writeOptionalTimestamp(json, JSON_CREATED_ENTITY, Created);
        // A project without default branch writes null.
        Internal::writeReference(json, JSON_DEFAULT_BRANCH_ENTITY,
                                 DefaultBranch != nullptr ? std::optional<boost::uuids::uuid>(DefaultBranch->getId()) : std::nullopt);

        return json.dump(JSON_INTENT);
    }

    void Project::deserializeAndPopulate(const std::string& jsonString) {
        const nlohmann::json parsedJson = Internal::parseObject(jsonString, "Project");
        try {
            Created = Internal::readOptionalTimestamp(parsedJson, JSON_CREATED_ENTITY);
            if (const auto branchId = Internal::readReference(parsedJson, JSON_DEFAULT_BRANCH_ENTITY)) {
                setDefaultBranch(std::make_shared<Branch>(Internal::referenceObjectText(*branchId)));
            }
        } catch (const std::exception& ex) {
            throw std::invalid_argument(std::string("Project: ") + ex.what());
        }
    }

    Project::Project(std::string projectName, std::string projectDescription, std::string branchName) : Record(projectName){
        Type = "Project";
        Description = projectDescription;
        Created = std::chrono::system_clock::now();
        Record::Id = boost::uuids::random_generator()();
        setDefaultBranch(std::make_shared<Branch>(branchName));
    }

    void Project::setDefaultBranch(std::shared_ptr<Branch> branch) {
        DefaultBranch = branch;
        if (branch == nullptr)
            return;
        // The default branch is one of the branches. It is added only once.
        const auto alreadyContained = std::any_of(Branches.begin(), Branches.end(), [&branch](const std::shared_ptr<Branch>& other) {
            return other == branch || (other != nullptr && !branch->getId().is_nil() && other->getId() == branch->getId());
        });
        if (!alreadyContained)
            Branches.push_back(branch);
    }

    std::vector<std::shared_ptr<Branch>> Project::getBranches() const {
        return Branches;
    }

    std::optional<std::chrono::system_clock::time_point> Project::getCreated() const {
        return Created;
    }
}
