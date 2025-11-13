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
namespace SysMLv2::REST{
    class Project;
    class DataVersion;
}


namespace SysMLv2::REST {

    /**
     * Represents an abstract baseclass that is used for the SysMLv2 API
     * @class Commit
     * @author Moritz Herzog
     * @version 1.0
     */
    class SYSMLV2REST_EXPORT Commit final : public Record {
    public:
        /**
         * Generalized Constructor is deleted, according to the SysMLv2 standard.
         */
        Commit() = delete;

        /**
         *
         * @param id
         * @param description
         * @param owningProject
         * @param previusCommits
         */
        Commit(boost::uuids::uuid id, std::string description, std::shared_ptr<Project> owningProject, std::vector<std::shared_ptr<Commit>> previusCommits = std::vector<std::shared_ptr<Commit>>());

        /**
         *
         * @param description
         * @param owningProject
         * @param previusCommits
         */
        Commit(std::string description, std::shared_ptr<Project> owningProject, std::vector<std::shared_ptr<Commit>> previusCommits = std::vector<std::shared_ptr<Commit>>());

        /**
         * Constructor for Parsing an Commit from the REST API, according to the SysMLv2 Standard.
         * @param jsonString The JSON String that is received by the REST Client
         */
        explicit Commit(std::string jsonString);

        /**
         * Destructor
         */
        virtual ~Commit() = default;

        /**
         *
         * @param change
         */
        void setChange(std::vector<std::shared_ptr<DataVersion>> change);

        /**
         *
         * @param dataVersion
         */
        void addChange(std::shared_ptr<DataVersion> dataVersion);

        /**
         *
         * @return
         */
        std::vector<std::shared_ptr<DataVersion>> getDataVersion();

        /**
         *
         * @return
         */
        [[nodiscard]] std::vector<std::shared_ptr<Commit>> getPreviusCommits() const;

        /**
         *
         * @return
         */
        [[nodiscard]] std::shared_ptr<Project> getOwningProject() const;

        void setOwningProject(std::shared_ptr<Project> owningProject);

        std::string serializeToJson() override;

        [[nodiscard]] std::chrono::system_clock::time_point getCreated() const;

protected:
        void deserializeAndPopulate(const std::string& jsonString) override;

        /**
         *
         */
        std::vector<std::shared_ptr<Commit>> PreviusCommits;
        /**
         *
         */
        std::shared_ptr<Project> OwningProject;
        /**
         *
         */
        std::vector<std::shared_ptr<DataVersion>> Change;
        /**
         *
         */
        std::chrono::system_clock::time_point Created;
    };
}
