//
// Created by Moritz Herzog on 07.11.2025.
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
#include <list>
#include <vector>
#include <memory>

//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include <sysmlv2/rest/entities/Record.h>
#include <sysmlv2/rest/sysmlv2rest_global.h>
//---------------------------------------------------------
// Forwarding
//---------------------------------------------------------
namespace SysMLv2::REST
{
    class DataVersion;
}

namespace SysMLv2::REST {

    /**
     * 
     * @class CommitRequest
     * @author Moritz Herzog
     * @version 1.0
     */
    class SYSMLV2REST_EXPORT CommitRequest : public IEntity {
    public:
        CommitRequest() = delete;
        CommitRequest(std::string jsonStringOrName);
        CommitRequest(std::string description, std::vector<std::shared_ptr<DataVersion>> changeRequested);
	    ~CommitRequest() = default;

    	std::string serializeToJson() override;

        std::vector<std::shared_ptr<DataVersion>> changeRequested();

        std::string description();

    private:
        std::string Description;
        std::vector<std::shared_ptr<DataVersion>> ChangeRequested;
    };
}