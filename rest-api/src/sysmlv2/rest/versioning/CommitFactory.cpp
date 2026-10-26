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
#include <chrono>
#include <set>
#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/string_generator.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <nlohmann/json.hpp>
//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include <kerml/root/elements/Relationship.h>
#include <sysmlv2/rest/entities/Commit.h>
#include <sysmlv2/rest/entities/Data.h>
#include <sysmlv2/rest/entities/DataIdentity.h>
#include <sysmlv2/rest/entities/DataVersion.h>
#include <sysmlv2/rest/entities/JSONEntities.h>
#include <sysmlv2/rest/entities/Project.h>
#include <sysmlv2/rest/versioning/CommitFactory.h>
#include <sysmlv2/rest/versioning/ElementReferences.h>
#include <sysmlv2/rest/versioning/Merge.h>
#include "VersioningDetail.h"

namespace SysMLv2::REST::Versioning {
    namespace {
        /**
         * Completes the deletions of the change, transitively, until nothing is left that belongs to deleted data:
         * - a Relationship of the base state that ends at a deleted element, or that is owned by one (owningRelatedElement) is deleted;
         * - the elements that a deleted Relationship owns (ownedRelatedElement) are deleted. A deleted Package therefore takes its
         *   membership and, through it, the whole subtree with it.
         * @param listed The identities the change already lists (they are left alone, whatever the client sent for them).
         */
        void cascadeDeletions(const VersionedData& baseState, std::set<boost::uuids::uuid>& listed,
                              std::vector<std::shared_ptr<DataVersion>>& change) {
            std::set<boost::uuids::uuid> deleted;
            for (const auto& version : change) {
                if (version->getPayload() == nullptr)
                    deleted.insert(version->getId());
            }
            if (deleted.empty())
                return;

            struct RelationshipInfo {
                boost::uuids::uuid Identity;
                std::set<boost::uuids::uuid> Ends;
                std::vector<boost::uuids::uuid> Owners;
                std::vector<boost::uuids::uuid> Owned;
            };
            std::vector<RelationshipInfo> relationships;
            for (const auto& [identity, version] : baseState) {
                if (std::dynamic_pointer_cast<KerML::Entities::Relationship>(version->getPayload()) == nullptr)
                    continue;
                const auto ends = relationshipEnds(version->getPayload());
                std::set<boost::uuids::uuid> endIds(ends.source.begin(), ends.source.end());
                endIds.insert(ends.target.begin(), ends.target.end());
                endIds.insert(ends.relatedElement.begin(), ends.relatedElement.end());
                relationships.push_back({identity, std::move(endIds), ends.owningRelatedElement, ends.ownedRelatedElement});
            }

            const auto addDeletion = [&](const boost::uuids::uuid& identity) {
                change.push_back(std::make_shared<DataVersion>(nullptr, std::make_shared<DataIdentity>(identity)));
                listed.insert(identity);
                deleted.insert(identity);
            };
            const auto touchesDeleted = [&deleted](const RelationshipInfo& info) {
                const auto isDeleted = [&deleted](const boost::uuids::uuid& id) { return deleted.find(id) != deleted.end(); };
                return std::any_of(info.Ends.begin(), info.Ends.end(), isDeleted) || std::any_of(info.Owners.begin(), info.Owners.end(), isDeleted);
            };

            bool added = true;
            while (added) {
                added = false;
                for (const auto& info : relationships) {
                    if (deleted.find(info.Identity) == deleted.end()) {
                        if (listed.find(info.Identity) == listed.end() && touchesDeleted(info)) {
                            addDeletion(info.Identity);
                            added = true;
                        }
                    }
                    if (deleted.find(info.Identity) != deleted.end()) {
                        for (const auto& owned : info.Owned) {
                            if (baseState.find(owned) != baseState.end() && listed.find(owned) == listed.end()) {
                                addDeletion(owned);
                                added = true;
                            }
                        }
                    }
                }
            }
        }

        /**
         * A reference to a commit (a commit that has only its id), so the DataVersions do not own the commit that owns them.
         */
        std::shared_ptr<Commit> referenceTo(const std::shared_ptr<Commit>& commit) {
            return std::make_shared<Commit>(nlohmann::json{{JSON_ID_ENTITY, boost::uuids::to_string(commit->getId())}}.dump());
        }
    }

    std::shared_ptr<Commit> prepareCommit(const std::shared_ptr<Project>& project, const std::string& description,
                                          const std::vector<std::shared_ptr<DataVersion>>& requestedChanges,
                                          const std::vector<std::shared_ptr<Commit>>& previousCommits,
                                          const CommitResolver& resolver, VersionedDataCache* cache) {
        if (project == nullptr)
            throw InvalidCommitException("A commit needs a project.");

        std::vector<std::shared_ptr<Commit>> previous;
        std::set<boost::uuids::uuid> seenPrevious;
        for (const auto& reference : previousCommits) {
            if (reference == nullptr || !seenPrevious.insert(reference->getId()).second)
                continue;
            const auto stored = resolver ? resolver(reference->getId()) : reference;
            if (stored == nullptr)
                throw InvalidCommitException("The previous commit " + boost::uuids::to_string(reference->getId()) + " does not exist.");
            const auto owner = stored->getOwningProject();
            if (owner != nullptr && owner->getId() != project->getId())
                throw InvalidCommitException("The previous commit " + boost::uuids::to_string(reference->getId()) +
                                             " belongs to another project.");
            previous.push_back(stored);
        }

        // A previous commit that is an ancestor of another one adds nothing; with it the union of the versionedData would bring
        // back what the later commit deleted or changed.
        if (previous.size() > 1) {
            std::vector<std::set<boost::uuids::uuid>> ancestors;
            for (const auto& parent : previous) {
                std::set<boost::uuids::uuid> ids;
                for (const auto& ancestor : ancestorsOf(parent, resolver)) {
                    if (ancestor->getId() != parent->getId())
                        ids.insert(ancestor->getId());
                }
                ancestors.push_back(std::move(ids));
            }
            std::vector<std::shared_ptr<Commit>> kept;
            for (std::size_t index = 0; index < previous.size(); ++index) {
                bool redundant = false;
                for (std::size_t other = 0; other < previous.size() && !redundant; ++other)
                    redundant = other != index && ancestors[other].find(previous[index]->getId()) != ancestors[other].end();
                if (!redundant)
                    kept.push_back(previous[index]);
            }
            previous = std::move(kept);
        }

        const auto baseState = unionOfVersionedData(previous, resolver, cache);
        const auto commit = std::make_shared<Commit>(description, project, previous);

        std::vector<std::shared_ptr<DataVersion>> change;
        std::set<boost::uuids::uuid> listed;
        for (const auto& requested : requestedChanges) {
            if (requested == nullptr)
                throw InvalidCommitException("A change without data version.");
            const auto identity = requested->getId();
            if (identity.is_nil())
                throw InvalidCommitException("A change without identity.");
            if (!listed.insert(identity).second)
                throw InvalidCommitException("The identity " + boost::uuids::to_string(identity) + " is listed twice in the change.");
            const auto payload = requested->getPayload();
            if (payload == nullptr && baseState.find(identity) == baseState.end())
                throw InvalidCommitException("The data " + boost::uuids::to_string(identity) +
                                             " can not be deleted, because it does not exist in the previous commits.");

            auto version = std::make_shared<DataVersion>(payload, requested->getIdentity(), boost::uuids::random_generator()());
            change.push_back(std::move(version));
        }

        // Parents that diverge: the commit has to resolve them (7.1.2), or the union of their versionedData would bring back what one
        // side deleted. The change of the client is the resolution; what it does not cover is taken over from the merge.
        if (previous.size() > 1) {
            std::vector<std::shared_ptr<Data>> resolution;
            std::vector<boost::uuids::uuid> resolvedAsDeleted;
            for (const auto& version : change) {
                if (version->getPayload() != nullptr)
                    resolution.push_back(version->getPayload());
                else
                    resolvedAsDeleted.push_back(version->getId());
            }
            const std::vector<std::shared_ptr<Commit>> others(previous.begin() + 1, previous.end());
            const auto analysis = analyzeMerge(previous.front(), others, resolution, resolver, cache, resolvedAsDeleted);
            if (!analysis.conflicts.empty()) {
                std::string ids;
                for (const auto& conflict : analysis.conflicts)
                    ids += (ids.empty() ? "" : ", ") + boost::uuids::to_string(conflict->getId());
                throw InvalidCommitException("The previous commits changed these data differently and the change does not resolve it: " + ids);
            }
            for (const auto& merged : analysis.changes) {
                // Only what the plain union of the parents would get wrong needs a change: data that one side deleted, and data
                // that the parents changed differently. What the union already gives correctly stays out, so the change stays as sent.
                const auto inUnion = baseState.find(merged->getId());
                const bool unionIsRight = merged->getPayload() == nullptr
                    ? inUnion == baseState.end()
                    : inUnion != baseState.end() && samePayload(inUnion->second, merged);
                if (unionIsRight || !listed.insert(merged->getId()).second)
                    continue;
                change.push_back(std::make_shared<DataVersion>(merged->getPayload(), merged->getIdentity(), boost::uuids::random_generator()()));
            }
        }

        cascadeDeletions(baseState, listed, change);

        const auto commitReference = referenceTo(commit);
        for (const auto& version : change)
            version->setCommit(commitReference);
        commit->setChange(change);

        // The JSON writes microseconds, so the strict order has to hold for them.
        auto created = std::chrono::floor<std::chrono::microseconds>(std::chrono::system_clock::now());
        for (const auto& stored : previous) {
            const auto storedCreated = std::chrono::floor<std::chrono::microseconds>(stored->getCreated());
            if (created <= storedCreated)
                created = storedCreated + std::chrono::microseconds(1);
        }
        commit->setCreated(created);

        versionedData(commit, resolver, cache);
        return commit;
    }
}
