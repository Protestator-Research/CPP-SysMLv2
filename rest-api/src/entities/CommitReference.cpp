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

#include "CommitReference.h"
#include "Commit.h"

namespace SysMLv2::Entities {
    CommitReference::CommitReference(std::string jsonStringOrName) : Record(jsonStringOrName) { }

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

    std::chrono::system_clock::time_point CommitReference::created() {
        return Created;
    }

    void CommitReference::setCreated(std::chrono::system_clock::time_point created) {
        Created = created;
    }
}