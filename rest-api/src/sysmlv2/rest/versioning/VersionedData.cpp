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
#include <sysmlv2/rest/entities/DataDifference.h>
#include <sysmlv2/rest/entities/DataVersion.h>
#include <sysmlv2/rest/versioning/VersionedData.h>
#include "VersioningDetail.h"

namespace SysMLv2::REST::Versioning {
    InvalidCommitException::InvalidCommitException(const std::string& message) : std::invalid_argument(message) {
    }

    namespace Detail {
        std::shared_ptr<Commit> resolveCommit(const std::shared_ptr<Commit>& reference, const CommitResolver& resolver) {
            if (!resolver)
                return reference;
            auto stored = resolver(reference->getId());
            if (stored == nullptr)
                throw std::runtime_error("The commit " + boost::uuids::to_string(reference->getId()) + " of the history is unknown.");
            return stored;
        }

        std::shared_ptr<Commit> resolveOrSelf(const std::shared_ptr<Commit>& commit, const CommitResolver& resolver) {
            if (commit == nullptr || !resolver)
                return commit;
            auto stored = resolver(commit->getId());
            return stored != nullptr ? stored : commit;
        }

        bool sameState(const std::shared_ptr<DataVersion>& first, const std::shared_ptr<DataVersion>& second) {
            return samePayload(first, second);
        }
    }

    bool samePayload(const std::shared_ptr<DataVersion>& first, const std::shared_ptr<DataVersion>& second) {
        const auto firstPayload = first != nullptr ? first->getPayload() : nullptr;
        const auto secondPayload = second != nullptr ? second->getPayload() : nullptr;
        if (firstPayload == nullptr || secondPayload == nullptr)
            return firstPayload == secondPayload;
        if (firstPayload == secondPayload)
            return true;
        return firstPayload->serializeToJson() == secondPayload->serializeToJson();
    }

    std::shared_ptr<const VersionedData> versionedData(const std::shared_ptr<Commit>& commit, const CommitResolver& resolver,
                                                       VersionedDataCache* cache) {
        if (commit == nullptr)
            return std::make_shared<const VersionedData>();

        const auto start = Detail::resolveOrSelf(commit, resolver);
        if (cache != nullptr) {
            const auto cached = cache->find(start->getId());
            if (cached != cache->end())
                return cached->second;
        }

        const auto cached = [&cache](const boost::uuids::uuid& id) -> std::shared_ptr<const VersionedData> {
            if (cache == nullptr)
                return nullptr;
            const auto found = cache->find(id);
            return found != cache->end() ? found->second : nullptr;
        };

        // Step 1: the commits of the history whose state is not cached, and how many of the commits that are walked refer to
        // each of them. The count lets step 2 release a state as soon as the last commit that needs it has been computed, so
        // a long history does not keep a copy of the state for every commit.
        std::map<boost::uuids::uuid, std::shared_ptr<Commit>> reachable;
        std::map<boost::uuids::uuid, std::size_t> uses;
        std::deque<std::shared_ptr<Commit>> pending{start};
        while (!pending.empty()) {
            const auto current = pending.front();
            pending.pop_front();
            if (!reachable.emplace(current->getId(), current).second)
                continue;
            for (const auto& previous : current->getPreviousCommits()) {
                if (previous == nullptr)
                    continue;
                ++uses[previous->getId()];
                if (cached(previous->getId()) == nullptr && reachable.find(previous->getId()) == reachable.end())
                    pending.push_back(Detail::resolveCommit(previous, resolver));
            }
        }

        // Step 2: compute the states, previous commits first. An explicit stack instead of recursion, so a deep history can not
        // overflow the stack. A frame is visited twice: first to push the previous commits that are not computed yet, then,
        // when they all are, to compute its own state.
        std::map<boost::uuids::uuid, std::shared_ptr<const VersionedData>> computed;
        const auto known = [&](const boost::uuids::uuid& id) -> std::shared_ptr<const VersionedData> {
            if (const auto fromCache = cached(id))
                return fromCache;
            const auto found = computed.find(id);
            return found != computed.end() ? found->second : nullptr;
        };

        struct Frame {
            boost::uuids::uuid Id;
            bool Expanded;
        };
        std::vector<Frame> stack{{start->getId(), false}};
        std::set<boost::uuids::uuid> inProgress;

        while (!stack.empty()) {
            const auto id = stack.back().Id;
            const auto& current = reachable.at(id);

            if (!stack.back().Expanded) {
                if (known(id) != nullptr) {
                    stack.pop_back();
                    continue;
                }
                if (!inProgress.insert(id).second)
                    throw std::runtime_error("The history of the commit " + boost::uuids::to_string(id) + " has a cycle.");
                stack.back().Expanded = true;
                for (const auto& previous : current->getPreviousCommits()) {
                    if (previous != nullptr && known(previous->getId()) == nullptr)
                        stack.push_back({previous->getId(), false});
                }
                continue;
            }

            stack.pop_back();
            inProgress.erase(id);

            const auto change = current->getChange();
            std::set<boost::uuids::uuid> updatedIdentities;
            for (const auto& version : change) {
                if (version != nullptr)
                    updatedIdentities.insert(version->getId());
            }

            auto state = std::make_shared<VersionedData>();
            // retained: the first DataVersion of every identity that the previous commits list and this commit does not change
            for (const auto& previous : current->getPreviousCommits()) {
                if (previous == nullptr)
                    continue;
                for (const auto& [identity, version] : *known(previous->getId())) {
                    if (updatedIdentities.find(identity) == updatedIdentities.end())
                        state->emplace(identity, version);
                }
            }
            // updatedNotDeleted
            for (const auto& version : change) {
                if (version != nullptr && version->getPayload() != nullptr)
                    (*state)[version->getId()] = version;
            }
            computed[id] = std::move(state);

            for (const auto& previous : current->getPreviousCommits()) {
                if (previous != nullptr && --uses[previous->getId()] == 0)
                    computed.erase(previous->getId());
            }
        }

        auto result = computed.at(start->getId());
        if (cache != nullptr)
            (*cache)[start->getId()] = result;
        return result;
    }

    VersionedData unionOfVersionedData(const std::vector<std::shared_ptr<Commit>>& commits, const CommitResolver& resolver,
                                       VersionedDataCache* cache) {
        VersionedData result;
        for (const auto& commit : commits) {
            if (commit == nullptr)
                continue;
            const auto state = versionedData(commit, resolver, cache);
            for (const auto& [identity, version] : *state)
                result.emplace(identity, version);
        }
        return result;
    }

    ChangeType classifyChange(const std::shared_ptr<DataVersion>& change, const VersionedData& baseState) {
        if (change->getPayload() == nullptr)
            return DELETED;
        return baseState.find(change->getId()) != baseState.end() ? UPDATED : CREATED;
    }

    namespace {
        bool wanted(const std::vector<ChangeType>& changeTypes, ChangeType type) {
            return changeTypes.empty() || std::find(changeTypes.begin(), changeTypes.end(), type) != changeTypes.end();
        }
    }

    std::vector<std::shared_ptr<DataVersion>> getCommitChange(const std::shared_ptr<Commit>& commit,
                                                              const std::vector<ChangeType>& changeTypes,
                                                              const CommitResolver& resolver, VersionedDataCache* cache) {
        std::vector<std::shared_ptr<DataVersion>> result;
        if (commit == nullptr)
            return result;
        const auto stored = Detail::resolveOrSelf(commit, resolver);

        std::vector<std::shared_ptr<Commit>> previousCommits;
        for (const auto& previous : stored->getPreviousCommits()) {
            if (previous != nullptr)
                previousCommits.push_back(Detail::resolveCommit(previous, resolver));
        }
        const auto baseState = unionOfVersionedData(previousCommits, resolver, cache);

        for (const auto& version : stored->getChange()) {
            if (version != nullptr && wanted(changeTypes, classifyChange(version, baseState)))
                result.push_back(version);
        }
        return result;
    }

    std::vector<std::shared_ptr<DataDifference>> diffCommits(const std::shared_ptr<Commit>& baseCommit,
                                                              const std::shared_ptr<Commit>& compareCommit,
                                                              const std::vector<ChangeType>& changeTypes,
                                                              const CommitResolver& resolver, VersionedDataCache* cache) {
        const auto baseState = versionedData(baseCommit, resolver, cache);
        const auto compareState = versionedData(compareCommit, resolver, cache);

        std::vector<std::shared_ptr<DataDifference>> result;
        auto baseIt = baseState->begin();
        auto compareIt = compareState->begin();
        // Both maps are ordered by identity, so one pass over both gives the differences in that order.
        while (baseIt != baseState->end() || compareIt != compareState->end()) {
            const bool baseOnly = compareIt == compareState->end() || (baseIt != baseState->end() && baseIt->first < compareIt->first);
            const bool compareOnly = baseIt == baseState->end() || (compareIt != compareState->end() && compareIt->first < baseIt->first);
            if (baseOnly) {
                if (wanted(changeTypes, DELETED))
                    result.push_back(std::make_shared<DataDifference>(baseIt->second, std::shared_ptr<DataVersion>()));
                ++baseIt;
            } else if (compareOnly) {
                if (wanted(changeTypes, CREATED))
                    result.push_back(std::make_shared<DataDifference>(std::shared_ptr<DataVersion>(), compareIt->second));
                ++compareIt;
            } else {
                if (wanted(changeTypes, UPDATED) && !samePayload(baseIt->second, compareIt->second))
                    result.push_back(std::make_shared<DataDifference>(baseIt->second, compareIt->second));
                ++baseIt;
                ++compareIt;
            }
        }
        return result;
    }
}
