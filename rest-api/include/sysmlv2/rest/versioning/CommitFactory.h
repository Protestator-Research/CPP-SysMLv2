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
#include <memory>
#include <string>
#include <vector>

//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include <sysmlv2/rest/versioning/VersionedData.h>
#include <sysmlv2/rest/sysmlv2rest_global.h>
//---------------------------------------------------------
// Forwarding
//---------------------------------------------------------
namespace SysMLv2::REST {
    class Project;
}

namespace SysMLv2::REST::Versioning {
    /**
     * Builds a new commit from a requested change (createCommit, 7.2.3) and checks the invariants of 7.1.2. The commit is not
     * stored anywhere and not attached to a branch; that is up to the caller.
     *
     * - The previous commits are the given ones without duplicates (by id). The caller adds the head of the branch.
     * - Every entry of the change is replaced by a new DataVersion with the same payload and identity, an own random id and
     *   the commit as its commit. The entries of the request are not modified.
     * - Deleting Data (an entry without payload) is only valid for an identity that exists in the union of the versionedData
     *   of the previous commits.
     * - An identity may appear once in the change.
     * - Deleting an Element also deletes the Relationships in the base state that have the Element as source, target or
     *   related element (7.2.3). The deletion of such a Relationship is added to the change, transitively (a Relationship
     *   can be the end of another Relationship). A Relationship that the change already lists is left as the client sent it.
     * - Commit.created is strictly newer than the created of every previous commit (microsecond resolution, the resolution
     *   of the JSON).
     * - The versionedData of the new commit is added to the cache.
     *
     * A payload whose identity exists in the base state is an update, any other payload is a creation. The identity of a
     * DataVersion is always the id of its payload, so the two can not be told apart by the request; both are accepted.
     * @param project The owning project.
     * @param description The description of the commit.
     * @param requestedChanges The requested change.
     * @param previousCommits The previous commits. They have to belong to @p project.
     * @param resolver Finds the stored commits (see CommitResolver).
     * @param cache Optional cache of the versionedData.
     * @throws InvalidCommitException If an invariant is violated.
     */
    SYSMLV2REST_EXPORT std::shared_ptr<Commit> prepareCommit(const std::shared_ptr<Project>& project,
                                                              const std::string& description,
                                                              const std::vector<std::shared_ptr<DataVersion>>& requestedChanges,
                                                              const std::vector<std::shared_ptr<Commit>>& previousCommits,
                                                              const CommitResolver& resolver,
                                                              VersionedDataCache* cache = nullptr);
}
