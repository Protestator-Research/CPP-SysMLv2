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
#include <vector>
#include <boost/uuid/uuid.hpp>

//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include <sysmlv2/rest/versioning/VersionedData.h>
#include <sysmlv2/rest/sysmlv2rest_global.h>
//---------------------------------------------------------
// Forwarding
//---------------------------------------------------------
namespace SysMLv2::REST {
    class Commit;
    class Data;
    class DataIdentity;
    class DataVersion;
}

namespace SysMLv2::REST::Versioning {
    /**
     * The outcome of the analysis of a merge.
     */
    struct SYSMLV2REST_EXPORT MergeAnalysis {
        /** The nearest common ancestor of all merged commits. nullptr if the histories have nothing in common. */
        std::shared_ptr<Commit> commonAncestor;

        /** Identities that were changed differently on several sides and that the resolution does not resolve. */
        std::vector<std::shared_ptr<DataIdentity>> conflicts;

        /**
         * The change of the merge commit if there are no conflicts: all differences between the merged state and the head and
         * between the merged state and the other commits (7.1.2: a commit resolves the conflicts of its parents). The
         * entries are not yet normalized; pass them to prepareCommit.
         */
        std::vector<std::shared_ptr<DataVersion>> changes;
    };

    /**
     * Analyses the merge of commits into a branch (mergeIntoBranch, 7.2.3) as a three-way merge.
     * - The common ancestor is the common ancestor of the head and all commits to merge with the newest created.
     * - A side has changed an identity if its state differs from the state of the ancestor (the payload JSON, or existence).
     * - If several sides changed an identity and the results differ, it is a conflict, unless the resolution has a payload
     *   with the id of the identity. That payload then is the merged state.
     * - Otherwise the merged state of the identity is the state of the side that changed it, or the head's.
     * @param head The head of the base branch. nullptr for a branch without head.
     * @param commitsToMerge The commits to merge.
     * @param resolution Data that resolve conflicts, by their id. May be empty.
     * @param resolver Finds the stored commits (see CommitResolver).
     * @param cache Optional cache of the versionedData.
     * @param resolvedAsDeleted Identities whose conflict is resolved by deleting them (a resolution has no payload for that).
     */
    SYSMLV2REST_EXPORT MergeAnalysis analyzeMerge(const std::shared_ptr<Commit>& head,
                                                   const std::vector<std::shared_ptr<Commit>>& commitsToMerge,
                                                   const std::vector<std::shared_ptr<Data>>& resolution,
                                                   const CommitResolver& resolver,
                                                   VersionedDataCache* cache = nullptr,
                                                   const std::vector<boost::uuids::uuid>& resolvedAsDeleted = {});

    /**
     * All commits that can be reached from the commit through the previous commits, including the commit itself.
     */
    SYSMLV2REST_EXPORT std::vector<std::shared_ptr<Commit>> ancestorsOf(const std::shared_ptr<Commit>& commit,
                                                                         const CommitResolver& resolver);
}
