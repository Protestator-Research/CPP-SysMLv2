//
// Created by Moritz Herzog on 23.02.24.
//
// SysMLv2 C++ Library Implementation
// Copyright (C) 2025  Moritz Herzog
//
//This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
//This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
//---------------------------------------------------------
//---------------------------------------------------------
// Constants, Definitions, Pragmas
//---------------------------------------------------------

//---------------------------------------------------------
// External Classes
//---------------------------------------------------------
//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include <nlohmann/json.hpp>
#include <sysmlv2/rest/entities/CommitReference.h>
#include <sysmlv2/rest/entities/Commit.h>
#include <sysmlv2/rest/entities/Project.h>
#include "RestJson.h"
#include <sysmlv2/rest/entities/JSONEntities.h>

#include <sysmlv2/rest/serialization/Utilities.h>
//---------------------------------------------------------
// Forwarding
//---------------------------------------------------------


namespace SysMLv2::REST {
    namespace {
        /**
         * Reads "deleted". Earlier library versions always wrote the field: the epoch or the overflowed value of
         * time_point::min() meant "not deleted". Both are read as not deleted (and reported).
         */
        std::optional<std::chrono::system_clock::time_point> readDeleted(const nlohmann::json& json) {
            const auto found = json.find(JSON_DELETED_ENTITY);
            if (found != json.end() && found->is_string()) {
                const auto text = found->get<std::string>();
                // The prefix match intentionally treats any value with these prefixes (e.g. 1970-01-01T00:00:00.5Z) as
                // "not deleted", since such deletion times cannot occur in practice.
                // time_point::min() overflowed to 1677-09-21T00:12:44.-854775 (a negative fraction) on GCC/Linux.
                if (text.rfind("1970-01-01T00:00:00", 0) == 0 || text.rfind("2262-04-11T23:47:16", 0) == 0 ||
                    text.rfind("1677-09-21T00:12:44", 0) == 0 || text.find(".-") != std::string::npos) {
                    warnDeprecated("JSON field \"deleted\" with a placeholder value for a reference that is not deleted",
                                   "an absent 'deleted' field");
                    return std::nullopt;
                }
            }
            return Internal::readOptionalTimestamp(json, JSON_DELETED_ENTITY);
        }
    }

    CommitReference::CommitReference(const std::string& jsonStringOrName) : CommitReference(jsonStringOrName, "CommitReference")
    {
    }

    CommitReference::CommitReference(const std::string& jsonStringOrName, std::string className) :
        Record(jsonStringOrName, className), ClassName(std::move(className))
    {
        Type = "CommitReference";
        if (Internal::looksLikeJson(jsonStringOrName))
            CommitReference::deserializeAndPopulate(jsonStringOrName);
        else
            Created = std::chrono::system_clock::now();
    }

    bool CommitReference::operator==(CommitReference &other) {
        if(Record::operator==(other))
        {
            const bool sameCommit = (ReferencedCommit == other.ReferencedCommit) ||
                                    (ReferencedCommit != nullptr && other.ReferencedCommit != nullptr &&
                                     (*ReferencedCommit) == (*other.ReferencedCommit));
            if(sameCommit)
                return this->Created==other.Created;
        }
        return false;
    }

    std::string CommitReference::serializeToJson() {
        nlohmann::json generatingJson = nlohmann::json::parse(Record::serializeToJson());
        Internal::writeOptionalTimestamp(generatingJson, JSON_CREATED_ENTITY, Created);
        // "deleted" is written only for a deleted reference.
        Internal::writeOptionalTimestamp(generatingJson, JSON_DELETED_ENTITY, Deleted);

        Internal::writeReference(generatingJson, JSON_REFERENCE_COMMIT,
                                 ReferencedCommit != nullptr ? std::optional<boost::uuids::uuid>(ReferencedCommit->getId()) : std::nullopt);
        Internal::writeReference(generatingJson, JSON_OWNING_PROJECT,
                                 OwningProject != nullptr ? std::optional<boost::uuids::uuid>(OwningProject->getId()) : std::nullopt);

        return generatingJson.dump(JSON_INTENT);
    }

    void CommitReference::setDeleted(std::chrono::system_clock::time_point deleted) {
        Deleted = deleted;
    }

    std::chrono::system_clock::time_point CommitReference::deleted() {
        return Deleted.value_or(std::chrono::system_clock::time_point{});
    }

    bool CommitReference::isDeleted() const {
        return Deleted.has_value();
    }

    std::optional<std::chrono::system_clock::time_point> CommitReference::deletedAt() const {
        return Deleted;
    }

    std::shared_ptr<Commit> CommitReference::referencedCommit()
    {
        return ReferencedCommit;
    }

    void CommitReference::setReferencedCommit(std::shared_ptr<Commit> referencedCommit)
    {
        ReferencedCommit = referencedCommit;
    }

    std::shared_ptr<Project> CommitReference::getOwningProject() const {
        return OwningProject;
    }

    void CommitReference::setOwningProject(std::shared_ptr<Project> owningProject) {
        OwningProject = owningProject;
    }

    void CommitReference::deserializeAndPopulate(const std::string& jsonString)
    {
        const nlohmann::json parsedJson = Internal::parseObject(jsonString, ClassName);
        try {
            Created = Internal::readOptionalTimestamp(parsedJson, JSON_CREATED_ENTITY);
            Deleted = readDeleted(parsedJson);
            if (const auto commitId = Internal::readReference(parsedJson, JSON_REFERENCE_COMMIT))
                ReferencedCommit = std::make_shared<Commit>(Internal::referenceObjectText(*commitId));
            if (const auto projectId = Internal::readReference(parsedJson, JSON_OWNING_PROJECT))
                OwningProject = std::make_shared<Project>(Internal::referenceObjectText(*projectId));
        } catch (const std::exception& ex) {
            throw std::invalid_argument(ClassName + ": " + ex.what());
        }
    }

    std::chrono::system_clock::time_point CommitReference::created() {
        return Created.value_or(std::chrono::system_clock::time_point{});
    }

    void CommitReference::setCreated(std::chrono::system_clock::time_point created) {
        Created = created;
    }
}
