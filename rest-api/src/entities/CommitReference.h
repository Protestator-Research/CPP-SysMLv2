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
#pragma once
//---------------------------------------------------------
// External Classes
//---------------------------------------------------------
#include <chrono>
#include <memory>
//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include "Record.h"
#include "../sysmlv2rest_global.h"
//---------------------------------------------------------
// Forwarding
//---------------------------------------------------------
namespace SysMLv2::REST{
    class Commit;
}


namespace SysMLv2::REST {
    /**
     * Represents an abstract baseclass that is used for the SysMLv2 API
     * @class Record
     * @author Moritz Herzog
     * @version 1.0
     */
    class SYSMLV2REST_EXPORT CommitReference : public Record {
    public:

        /**
         * Constructor
         * @param jsonStringOrName
         */
        explicit CommitReference(std::string jsonStringOrName);

        /**
         *
         * @param other
         * @return
         */
        bool operator==(CommitReference& other);

        std::string serializeToJson() override;

        /**
         *
         * @param created
         */
        void setCreated(std::chrono::system_clock::time_point created);
        /**
         *
         * @return
         */
        std::chrono::system_clock::time_point created();
        /**
         *
         * @param deleted
         */
        void setDeleted(std::chrono::system_clock::time_point deleted);
        /**
         *
         * @return
         */
        std::chrono::system_clock::time_point deleted();

        /**
         * 
         * @return 
         */
        std::shared_ptr<Commit> referencedCommit();
        /**
         * 
         * @param referencedCommit 
         */
        void setReferencedCommit(std::shared_ptr<Commit> referencedCommit);
    protected:
        std::chrono::system_clock::time_point Created;
        std::chrono::system_clock::time_point Deleted;
        std::shared_ptr<Commit> ReferencedCommit;
    };
}
