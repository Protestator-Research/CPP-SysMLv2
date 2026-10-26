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
#include <functional>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>
#include <boost/uuid/uuid.hpp>

//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include <sysmlv2/rest/entities/ChangeType.h>
#include <sysmlv2/rest/sysmlv2rest_global.h>
//---------------------------------------------------------
// Forwarding
//---------------------------------------------------------
namespace SysMLv2::REST {
    class Commit;
    class DataVersion;
    class DataDifference;
}

/**
 * The versioning logic of the Project Data Versioning Service (SysML v2 API and Services, 7.1.2 and 7.2.3) without any
 * dependency on a transport or a database. A service stores the commits of its projects itself; the functions only need a
 * CommitResolver that finds a stored commit by its id, because commits that are read from a database refer to their
 * previous commits by id only (stubs without changes).
 */
namespace SysMLv2::REST::Versioning {
    /**
     * Finds the stored commit with the given id. Returns nullptr if there is none. If the resolver is empty, the commits that
     * are linked by Commit::getPreviousCommits() are used as they are (an object graph that is complete in memory).
     */
    using CommitResolver = std::function<std::shared_ptr<Commit>(const boost::uuids::uuid&)>;

    /**
     * Commit.versionedData: the DataVersion (with payload) that exists at a commit, by the id of its DataIdentity.
     */
    using VersionedData = std::map<boost::uuids::uuid, std::shared_ptr<DataVersion>>;

    /**
     * Remembers the VersionedData of commits by the id of the commit. Commits are immutable, so an entry never becomes
     * invalid. The cache is not synchronized; a caller that shares it between threads has to lock it.
     */
    using VersionedDataCache = std::map<boost::uuids::uuid, std::shared_ptr<const VersionedData>>;

    /**
     * Thrown if a commit violates the invariants of 7.1.2 (e.g. a deletion of Data that does not exist, a duplicate identity
     * in the change, a previous commit of another project).
     */
    class SYSMLV2REST_EXPORT InvalidCommitException : public std::invalid_argument {
    public:
        explicit InvalidCommitException(const std::string& message);
    };

    /**
     * Computes Commit.versionedData with the algorithm of 7.1.2 (the OCL expression): the changes without deletions plus the
     * versionedData of all previous commits without the identities that the commit changes. The previous commits are
     * resolved by their id, the history is walked iteratively (no recursion, so a deep history can not overflow the stack).
     * @param commit The commit. nullptr gives an empty result (the state of a branch without head).
     * @param resolver Finds the stored commits.
     * @param cache Optional. Entries are used for every commit of the history and the result for @p commit is added.
     *              Intermediate results are not kept, which bounds the memory.
     * @throws std::runtime_error If a previous commit is unknown to the resolver or the history has a cycle.
     */
    SYSMLV2REST_EXPORT std::shared_ptr<const VersionedData> versionedData(const std::shared_ptr<Commit>& commit,
                                                                           const CommitResolver& resolver,
                                                                           VersionedDataCache* cache = nullptr);

    /**
     * The union of the versionedData of the commits, one DataVersion per identity (the first one in the order of the
     * commits). This is the state against which the change of a commit with these previous commits is checked.
     */
    SYSMLV2REST_EXPORT VersionedData unionOfVersionedData(const std::vector<std::shared_ptr<Commit>>& commits,
                                                           const CommitResolver& resolver,
                                                           VersionedDataCache* cache = nullptr);

    /**
     * Classifies one entry of a change against the state before the commit: DELETED if it has no payload, UPDATED if the
     * identity exists in @p baseState, otherwise CREATED.
     */
    SYSMLV2REST_EXPORT ChangeType classifyChange(const std::shared_ptr<DataVersion>& change, const VersionedData& baseState);

    /**
     * getCommitChange: the change of a commit, filtered by the kind of the change.
     * @param changeTypes The wanted kinds. An empty vector is no filter (all changes), like in the specification.
     */
    SYSMLV2REST_EXPORT std::vector<std::shared_ptr<DataVersion>> getCommitChange(const std::shared_ptr<Commit>& commit,
                                                                                  const std::vector<ChangeType>& changeTypes,
                                                                                  const CommitResolver& resolver,
                                                                                  VersionedDataCache* cache = nullptr);

    /**
     * diffCommits: compareCommit.versionedData against baseCommit.versionedData. The result has one DataDifference per
     * identity that is only in the compare commit (CREATED: baseData is empty), only in the base commit (DELETED:
     * compareData is empty) or in both with a different payload (UPDATED: both are set). The payloads are different if their
     * JSON is different. The order is the order of the identities.
     * @param changeTypes The wanted kinds. An empty vector is no filter.
     */
    SYSMLV2REST_EXPORT std::vector<std::shared_ptr<DataDifference>> diffCommits(const std::shared_ptr<Commit>& baseCommit,
                                                                                 const std::shared_ptr<Commit>& compareCommit,
                                                                                 const std::vector<ChangeType>& changeTypes,
                                                                                 const CommitResolver& resolver,
                                                                                 VersionedDataCache* cache = nullptr);

    /**
     * True if both versions have the same payload (the same JSON), or both have none.
     */
    SYSMLV2REST_EXPORT bool samePayload(const std::shared_ptr<DataVersion>& first, const std::shared_ptr<DataVersion>& second);
}
