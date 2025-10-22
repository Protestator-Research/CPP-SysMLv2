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
#include <sysmlv2/rest/entities/CommitReference.h>
#include <sysmlv2/rest/entities/Commit.h>
//---------------------------------------------------------
// Forwarding
//---------------------------------------------------------


namespace SysMLv2::REST {
    CommitReference::CommitReference(std::string jsonStringOrName) : Record(jsonStringOrName)
    {
        Created = std::chrono::system_clock::now();
        Deleted = std::chrono::time_point<std::chrono::system_clock>::min();
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
        return Record::serializeToJson();
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

    std::chrono::system_clock::time_point CommitReference::created() {
        return Created;
    }

    void CommitReference::setCreated(std::chrono::system_clock::time_point created) {
        Created = created;
    }
}