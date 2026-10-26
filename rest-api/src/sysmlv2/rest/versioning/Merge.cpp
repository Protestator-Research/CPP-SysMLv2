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

//---------------------------------------------------------
// External Classes
//---------------------------------------------------------
#include <algorithm>
#include <deque>
#include <set>
#include <boost/uuid/uuid_io.hpp>
//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include <sysmlv2/rest/entities/Commit.h>
#include <sysmlv2/rest/entities/Data.h>
#include <sysmlv2/rest/entities/DataIdentity.h>
#include <sysmlv2/rest/entities/DataVersion.h>
#include <sysmlv2/rest/versioning/Merge.h>
#include "VersioningDetail.h"

namespace SysMLv2::REST::Versioning {
    namespace {
        using AncestorMap = std::map<boost::uuids::uuid, std::shared_ptr<Commit>>;

        AncestorMap ancestorMapOf(const std::shared_ptr<Commit>& commit, const CommitResolver& resolver) {
            AncestorMap ancestors;
            std::deque<std::shared_ptr<Commit>> pending;
            pending.push_back(Detail::resolveOrSelf(commit, resolver));
            while (!pending.empty()) {
                const auto current = pending.front();
                pending.pop_front();
                if (!ancestors.emplace(current->getId(), current).second)
                    continue;
                for (const auto& previous : current->getPreviousCommits()) {
                    if (previous != nullptr)
                        pending.push_back(Detail::resolveCommit(previous, resolver));
                }
            }
            return ancestors;
        }

        std::shared_ptr<DataVersion> find(const VersionedData& state, const boost::uuids::uuid& identity) {
            const auto found = state.find(identity);
            return found != state.end() ? found->second : nullptr;
        }
    }

    std::vector<std::shared_ptr<Commit>> ancestorsOf(const std::shared_ptr<Commit>& commit, const CommitResolver& resolver) {
        std::vector<std::shared_ptr<Commit>> result;
        if (commit == nullptr)
            return result;
        for (const auto& [id, ancestor] : ancestorMapOf(commit, resolver))
            result.push_back(ancestor);
        return result;
    }

    MergeAnalysis analyzeMerge(const std::shared_ptr<Commit>& head, const std::vector<std::shared_ptr<Commit>>& commitsToMerge,
                               const std::vector<std::shared_ptr<Data>>& resolution, const CommitResolver& resolver,
                               VersionedDataCache* cache, const std::vector<boost::uuids::uuid>& resolvedAsDeleted) {
        MergeAnalysis analysis;

        // Side 0 is the head, the others are the commits to merge. A branch without head is an empty side.
        std::vector<std::shared_ptr<Commit>> sides{Detail::resolveOrSelf(head, resolver)};
        std::set<boost::uuids::uuid> seen;
        if (sides[0] != nullptr)
            seen.insert(sides[0]->getId());
        for (const auto& commit : commitsToMerge) {
            if (commit != nullptr && seen.insert(commit->getId()).second)
                sides.push_back(Detail::resolveOrSelf(commit, resolver));
        }

        // The nearest common ancestor: of all commits, the common ancestor that was created last. It has no descendant among
        // the common ancestors, because a commit is created strictly after its previous commits. Without a head there is no
        // common history to take into account.
        if (sides[0] != nullptr) {
            AncestorMap common = ancestorMapOf(sides[0], resolver);
            for (std::size_t index = 1; index < sides.size() && !common.empty(); ++index) {
                const auto ancestors = ancestorMapOf(sides[index], resolver);
                for (auto it = common.begin(); it != common.end();) {
                    if (ancestors.find(it->first) == ancestors.end())
                        it = common.erase(it);
                    else
                        ++it;
                }
            }
            for (const auto& [id, candidate] : common) {
                if (analysis.commonAncestor == nullptr || candidate->getCreated() > analysis.commonAncestor->getCreated())
                    analysis.commonAncestor = candidate;
            }
        }

        const VersionedData ancestorState = analysis.commonAncestor != nullptr
            ? *versionedData(analysis.commonAncestor, resolver, cache) : VersionedData();
        std::vector<std::shared_ptr<const VersionedData>> sideStates;
        for (const auto& side : sides)
            sideStates.push_back(versionedData(side, resolver, cache));

        std::set<boost::uuids::uuid> identities;
        for (const auto& [identity, version] : ancestorState)
            identities.insert(identity);
        for (const auto& state : sideStates)
            for (const auto& [identity, version] : *state)
                identities.insert(identity);

        std::map<boost::uuids::uuid, std::shared_ptr<Data>> resolved;
        for (const auto& data : resolution) {
            if (data != nullptr)
                resolved[data->getId()] = data;
        }

        // The merged DataVersion of every identity; nullptr means the identity does not exist after the merge.
        std::map<boost::uuids::uuid, std::shared_ptr<DataVersion>> merged;
        for (const auto& identity : identities) {
            const auto ancestorVersion = find(ancestorState, identity);
            std::vector<std::shared_ptr<DataVersion>> changedStates;
            std::shared_ptr<DataVersion> unchangedVersion;
            for (const auto& state : sideStates) {
                const auto version = find(*state, identity);
                if (!Detail::sameState(version, ancestorVersion))
                    changedStates.push_back(version);
                else if (unchangedVersion == nullptr)
                    unchangedVersion = version; // the head is the first side
            }

            if (changedStates.empty()) {
                merged[identity] = unchangedVersion != nullptr ? unchangedVersion : ancestorVersion;
                continue;
            }

            const bool allEqual = std::all_of(changedStates.begin(), changedStates.end(), [&changedStates](const std::shared_ptr<DataVersion>& state) {
                return Detail::sameState(state, changedStates.front());
            });
            if (allEqual) {
                merged[identity] = changedStates.front();
                continue;
            }

            if (std::find(resolvedAsDeleted.begin(), resolvedAsDeleted.end(), identity) != resolvedAsDeleted.end()) {
                merged[identity] = nullptr;
                continue;
            }
            const auto resolvedData = resolved.find(identity);
            if (resolvedData == resolved.end()) {
                analysis.conflicts.push_back(std::make_shared<DataIdentity>(identity));
                continue;
            }
            merged[identity] = std::make_shared<DataVersion>(resolvedData->second);
        }

        if (!analysis.conflicts.empty())
            return analysis;

        // The change of the merge commit: every identity where the result differs from the head, or from a commit that is merged
        // (7.1.2: the change lists the identities of the previous commits whose DataVersion is not part of the result).
        const auto& headState = *sideStates.front();
        for (const auto& [identity, mergedVersion] : merged) {
            bool differs = !Detail::sameState(mergedVersion, find(headState, identity));
            for (std::size_t index = 1; index < sideStates.size() && !differs; ++index) {
                const auto other = find(*sideStates[index], identity);
                differs = other != nullptr && !Detail::sameState(other, mergedVersion);
            }
            if (!differs)
                continue;
            if (mergedVersion != nullptr && mergedVersion->getPayload() != nullptr)
                analysis.changes.push_back(std::make_shared<DataVersion>(mergedVersion->getPayload(), mergedVersion->getIdentity()));
            else
                analysis.changes.push_back(std::make_shared<DataVersion>(nullptr, std::make_shared<DataIdentity>(identity)));
        }
        return analysis;
    }
}
