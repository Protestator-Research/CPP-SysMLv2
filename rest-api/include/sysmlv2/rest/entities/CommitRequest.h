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
     * This CommitRequest is required by the SysML v2 Standard. But not documented; thus this can diverge per implementation,
     * meaning that the parsing needs to correct for erros.
     * @class CommitRequest
     * @author Moritz Herzog
     * @version 1.0
     */
    class SYSMLV2REST_EXPORT CommitRequest : public IEntity {
    public:
	    /**
	     * @brief Constructor Deleted.
	     */
	    CommitRequest() = delete;
	    /**
	     * @brief Constructor that is used to parse the given JSON string.
	     * This constructor allows to set the Description, but can also be used to set the JSON string to be parsed.
	     * @param jsonStringOrDescription Can be the JSON string or the description of the CommitRequest.
	     */
	    CommitRequest(const std::string& jsonStringOrDescription);
	    /**
	     * @brief Constructor for the initialization of the commit.
	     * This constructor allows to set the description and the requested change.
	     * @param description The given string that is used to describe the changes of the given commit.
	     * @param changeRequested The given requested change, that can be implemented in the project.
	     */
	    CommitRequest(const std::string& description, const std::vector<std::shared_ptr<DataVersion>>& changeRequested);
	    /**
	     * @brief DTor
	     * DTor
	     */
	    ~CommitRequest() = default;

    	std::string serializeToJson() override;

	    /**
	     * @brief Gives access to the requested change.
	     * @return A vector of DataVersions
	     * @see SysMLv2::REST::DataVersion
	     */
	    std::vector<std::shared_ptr<DataVersion>> changeRequested();

	    /**
	     * @brief Gives access to the description of the Commit.
	     * @return String of the description.
	     */
	    std::string description();

    protected:
        void deserializeAndPopulate(const std::string& jsonValue) override;

    private:
        const std::string Type;
        std::string Description;
        std::vector<std::shared_ptr<DataVersion>> ChangeRequested;
    };
}