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
#include <iostream>
//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include <nlohmann/json.hpp>
#include <sysmlv2/rest/entities/CommitReference.h>
#include <sysmlv2/rest/entities/Commit.h>
#include <sysmlv2/rest/entities/JSONEntities.h>

#include <sysmlv2/rest/serialization/Utilities.h>
//---------------------------------------------------------
// Forwarding
//---------------------------------------------------------


namespace SysMLv2::REST {
    CommitReference::CommitReference(const std::string& jsonStringOrName) : Record(jsonStringOrName)
    {
        Type = "CommitReference";
        try {
            CommitReference::deserializeAndPopulate(jsonStringOrName);
        }catch (...)
        {
            Created = std::chrono::system_clock::now();
            Deleted = std::chrono::time_point<std::chrono::system_clock>::min();
        }
    }

    bool CommitReference::operator==(CommitReference &other) {
        if(Record::operator==(other))
        {
            if((*(this->ReferencedCommit))==(*(other.ReferencedCommit))){
                return this->Created==other.Created;
            }
        }
        return false;
    }

    std::string CommitReference::serializeToJson() {
        nlohmann::json generatingJson = nlohmann::json::parse(Record::serializeToJson());

        generatingJson[JSON_CREATED_ENTITY] = Utilities::toIso8601(Created);
        generatingJson[JSON_DELETED_ENTITY] = Utilities::toIso8601(Deleted);

        generatingJson[JSON_REFERENCE_COMMIT] = ReferencedCommit->serializeIdentification();

        return generatingJson.dump(JSON_INTENT);
    }

    void CommitReference::setDeleted(std::chrono::system_clock::time_point deleted) {
        Deleted = deleted;
    }

    std::chrono::system_clock::time_point CommitReference::deleted() {
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

    void CommitReference::deserializeAndPopulate(const std::string& jsonString)
    {
        nlohmann::json parsedJson = nlohmann::json::parse(jsonString);
        if (parsedJson.contains(JSON_CREATED_ENTITY))
            Created = Utilities::fromIso8601(parsedJson[JSON_CREATED_ENTITY]);
        try {
            if (parsedJson.contains(JSON_DELETED_ENTITY))
                Deleted = Utilities::fromIso8601(parsedJson[JSON_DELETED_ENTITY]);
        }catch (std::exception& ex)
        {
            std::cerr << "CommitReference::Deleted caused Error:" << std::endl << ex.what() << std::endl;
        }
        if (parsedJson.contains(JSON_REFERENCE_COMMIT))
            ReferencedCommit = std::make_shared<Commit>(parsedJson[JSON_REFERENCE_COMMIT]);

    }

    std::chrono::system_clock::time_point CommitReference::created() {
        return Created;
    }

    void CommitReference::setCreated(std::chrono::system_clock::time_point created) {
        Created = created;
    }
}