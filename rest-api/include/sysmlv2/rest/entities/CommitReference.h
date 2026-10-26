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
#include <optional>
#include <string>
//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include <sysmlv2/rest/entities/Record.h>
#include <sysmlv2/rest/sysmlv2rest_global.h>

//---------------------------------------------------------
// Forwarding
//---------------------------------------------------------
namespace SysMLv2::REST{
    class Commit;
    class Project;
}


namespace SysMLv2::REST {
    /**
     * Represents an abstract baseclass that is used for the SysMLv2 API.
     * @class CommitReference
     * @author Moritz Herzog
     * @version 1.0
     */
    class SYSMLV2REST_EXPORT CommitReference : public Record {
    public:

        /**
         * Constructor
         * @param jsonStringOrName A JSON object (the text starts with '{') or the name of the reference.
         * @throws std::invalid_argument If the text looks like JSON but is malformed or has values of a wrong type.
         */
        explicit CommitReference(const std::string& jsonStringOrName);

        /**
         * Operator that allows to compare two CommitReferences with each other.
         * @param other Second CommitReference
         * @return True if the two CommitReferences are identical.
         */
        bool operator==(CommitReference& other);

        std::string serializeToJson() override;

        /**
         * Sets the creation time of the reference.
         * @param created
         */
        void setCreated(std::chrono::system_clock::time_point created);

        /**
         * The creation time of the reference. A reference read from JSON without "created" returns time_point{}.
         */
        std::chrono::system_clock::time_point created();

        /**
         * Marks the reference as deleted at the given time.
         * @param deleted
         */
        void setDeleted(std::chrono::system_clock::time_point deleted);

        /**
         * The deletion time as plain time point. A reference that is not deleted returns time_point{} (the epoch); use
         * isDeleted() or deletedAt() to tell the two cases apart.
         */
        std::chrono::system_clock::time_point deleted();

        /**
         * True if the reference has a deletion time.
         */
        [[nodiscard]] bool isDeleted() const;

        /**
         * The deletion time, empty if the reference is not deleted. Only a set value is serialized as "deleted".
         */
        [[nodiscard]] std::optional<std::chrono::system_clock::time_point> deletedAt() const;

        /**
         * The commit that is referenced (the head of a Branch, the tagged commit of a Tag). Can be empty.
         */
        std::shared_ptr<Commit> referencedCommit();

        /**
         * The project that owns the reference. Can be empty.
         */
        [[nodiscard]] std::shared_ptr<Project> getOwningProject() const;

        /**
         * Sets the project that owns the reference.
         */
        void setOwningProject(std::shared_ptr<Project> owningProject);
    protected:
        /**
         * Constructor for the subclasses, so that error messages name the concrete class.
         * @param className Name of the concrete class, e.g. "Branch".
         */
        CommitReference(const std::string& jsonStringOrName, std::string className);

        /**
         * Sets the referenced commit. Protected, because the commit of a Tag is immutable and the one of a Branch is set
         * via Branch::setHead.
         */
        void setReferencedCommit(std::shared_ptr<Commit> referencedCommit);

        void deserializeAndPopulate(const std::string& jsonString) override;

        /**
         * Name of the concrete class for error messages.
         */
        std::string ClassName;
        std::optional<std::chrono::system_clock::time_point> Created;
        std::optional<std::chrono::system_clock::time_point> Deleted;
        std::shared_ptr<Commit> ReferencedCommit;
        std::shared_ptr<Project> OwningProject;
    };
}
