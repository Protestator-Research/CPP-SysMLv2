//
// Created by Moritz Herzog on 09.04.25.
//

#include "sysmlv2/service/implementation/ProjectVersioningService.h"

#include <algorithm>
#include <deque>
#include <functional>
#include <set>
#include <boost/uuid/nil_generator.hpp>

#include <sysmlv2/rest/entities/Project.h>
#include <sysmlv2/rest/entities/Branch.h>
#include <sysmlv2/rest/entities/Commit.h>
#include <sysmlv2/rest/entities/Data.h>
#include <sysmlv2/rest/entities/DataVersion.h>
#include <sysmlv2/rest/entities/Tag.h>

namespace SysMLv2::API {
    std::vector<std::shared_ptr<SysMLv2::REST::Commit>> ProjectVersioningService::getCommits(std::shared_ptr<SysMLv2::REST::Project> project) {
        return ProjectIdCommitMap[project->getId()];
    }

    std::shared_ptr<SysMLv2::REST::Commit> ProjectVersioningService::getHeadCommit(std::shared_ptr<SysMLv2::REST::Project>, std::shared_ptr<SysMLv2::REST::Branch> branch) {
        return branch->getHead();
    }

    std::shared_ptr<SysMLv2::REST::Commit> ProjectVersioningService::getCommitById(std::shared_ptr<SysMLv2::REST::Project> project, boost::uuids::uuid commitId) {
        const auto projectEntry = ProjectIdCommitMap.find(project->getId());
        if (projectEntry == ProjectIdCommitMap.end())
            return nullptr;
        for (const auto& commit:projectEntry->second)
        {
            if (commit->getId() == commitId)
                return commit;
        }
        return nullptr;
    }

    std::shared_ptr<SysMLv2::REST::Commit> ProjectVersioningService::createCommit(std::shared_ptr<SysMLv2::REST::DataVersion> change, std::shared_ptr<SysMLv2::REST::Branch> branch, std::vector<std::shared_ptr<SysMLv2::REST::Commit>> previousCommits, std::shared_ptr<SysMLv2::REST::Project> project) {
        const auto commit = std::make_shared<SysMLv2::REST::Commit>("", project, previousCommits);
        commit->addChange(change);

        ProjectIdCommitMap[project->getId()].push_back(commit);
        branch->setHead(commit);

        return commit;
    }

    std::shared_ptr<SysMLv2::REST::Commit> ProjectVersioningService::createCommit(std::shared_ptr<SysMLv2::REST::DataVersion> change, std::shared_ptr<SysMLv2::REST::Branch> branch, std::shared_ptr<SysMLv2::REST::Project> project) {
        const auto commit = std::make_shared<SysMLv2::REST::Commit>( "", project);
        commit->addChange(change);

        ProjectIdCommitMap[project->getId()].push_back(commit);
        branch->setHead(commit);

        return commit;
    }

    std::shared_ptr<SysMLv2::REST::Commit> ProjectVersioningService::createCommit(std::shared_ptr<SysMLv2::REST::DataVersion> change, std::vector<std::shared_ptr<SysMLv2::REST::Commit>> previousCommits, std::shared_ptr<SysMLv2::REST::Project> project) {
        const auto commit = std::make_shared<SysMLv2::REST::Commit>("", project, previousCommits);
        commit->addChange(change);

        ProjectIdCommitMap[project->getId()].push_back(commit);
        project->getDefaultBranch()->setHead(commit);

        return commit;
    }

    std::shared_ptr<SysMLv2::REST::Commit> ProjectVersioningService::createCommit(std::shared_ptr<SysMLv2::REST::DataVersion> change, std::shared_ptr<SysMLv2::REST::Project> project) {
        const auto commit = std::make_shared<SysMLv2::REST::Commit>( "", project);
        commit->addChange(change);

        ProjectIdCommitMap[project->getId()].push_back(commit);
        project->getDefaultBranch()->setHead(commit);

        return commit;
    }

    namespace {
        /**
         * Tells if the Data exists in the previous commits of the commit. Every path through the previous commits is followed
         * breadth-first up to the nearest version of the Data: a version with a payload means the Data exists on that path,
         * a version without payload (deletion) ends the path as "does not exist". For a merge commit the Data exists if it
         * exists on the path of any parent. The search stops as soon as one path shows that the Data exists.
         * @param resolve Maps a commit to the commit whose changes are used (a commit that is only known by reference is
         * replaced by the stored one).
         */
        bool existsInPreviousCommits(const std::shared_ptr<SysMLv2::REST::Commit>& commit, const boost::uuids::uuid& dataId,
                                     const std::function<std::shared_ptr<SysMLv2::REST::Commit>(const std::shared_ptr<SysMLv2::REST::Commit>&)>& resolve) {
            std::set<boost::uuids::uuid> visited;
            std::deque<std::shared_ptr<SysMLv2::REST::Commit>> pending;
            for (const auto& previous : commit->getPreviousCommits())
                pending.push_back(previous);
            while (!pending.empty()) {
                const auto current = resolve(pending.front());
                pending.pop_front();
                if (current == nullptr || !visited.insert(current->getId()).second)
                    continue;
                bool found = false;
                for (const auto& version : current->getChange()) {
                    if (version == nullptr || version->getId() != dataId)
                        continue;
                    if (version->getPayload() != nullptr)
                        return true;
                    found = true;
                }
                if (found)
                    continue; // deleted on this path
                for (const auto& previous : current->getPreviousCommits())
                    pending.push_back(previous);
            }
            return false;
        }
    }

    // ChangeType::CREATED is 0, so the values of the filter can not be combined as bit flags. The vector is a set of
    // ChangeType values (other values are ignored); an empty vector means no filter (all changes).
    // DELETED: no payload. CREATED: a payload and the Data does not exist in the previous commits, i.e. there is no
    // version of it, or the nearest version is a deletion (a re-creation). UPDATED: a payload and the Data exists there.
    // A commit that is only known by reference (no changes) is replaced by the stored commit of the project.
    std::vector<std::shared_ptr<SysMLv2::REST::DataVersion>> ProjectVersioningService::getCommitChange(std::shared_ptr<SysMLv2::REST::Project> project, std::shared_ptr<SysMLv2::REST::Commit> commit, std::vector<int> changeType) {
        std::vector<std::shared_ptr<SysMLv2::REST::DataVersion>> returnValue;

        const auto wanted = [&changeType](REST::ChangeType type) {
            return changeType.empty() || std::find(changeType.begin(), changeType.end(), static_cast<int>(type)) != changeType.end();
        };

        const auto resolve = [this, &project](const std::shared_ptr<SysMLv2::REST::Commit>& reference) {
            if (reference == nullptr || project == nullptr || !reference->getChange().empty() || !reference->getPreviousCommits().empty())
                return reference;
            const auto stored = getCommitById(project, reference->getId());
            return stored != nullptr ? stored : reference;
        };

        for (const auto& dataVersion : commit->getChange())
        {
            if (dataVersion == nullptr)
                continue;
            if (dataVersion->getPayload() == nullptr) {
                if (wanted(REST::ChangeType::DELETED))
                    returnValue.push_back(dataVersion);
            } else if (wanted(REST::ChangeType::CREATED) || wanted(REST::ChangeType::UPDATED)) {
                const bool exists = existsInPreviousCommits(commit, dataVersion->getId(), resolve);
                if (wanted(exists ? REST::ChangeType::UPDATED : REST::ChangeType::CREATED))
                    returnValue.push_back(dataVersion);
            }
        }

        return returnValue;
    }

    std::shared_ptr<SysMLv2::REST::DataVersion> ProjectVersioningService::getCommitChangeById(std::shared_ptr<SysMLv2::REST::Project>, std::shared_ptr<SysMLv2::REST::Commit> commit, boost::uuids::uuid &changeId) {
        for (const auto& change : commit->getChange())
        {
            // The id of the change is the id of the DataVersion; the id of the Data is accepted as well (earlier versions
            // of the library used it).
            if (change->getVersionId() == changeId || change->getId() == changeId)
                return change;
        }
        return nullptr;
    }

    std::vector<std::shared_ptr<SysMLv2::REST::Branch>> ProjectVersioningService::getBranches(std::shared_ptr<SysMLv2::REST::Project> project) {
        return ProjectIdBranchMap.at(project->getId());
    }

    std::shared_ptr<SysMLv2::REST::Branch> ProjectVersioningService::getBranchById(std::shared_ptr<SysMLv2::REST::Project> project, boost::uuids::uuid &branchId) {
        const auto branchesList = ProjectIdBranchMap.at(project->getId());

        for (const auto& branch : branchesList)
            if (branch->getId() == branchId)
                return branch;

        return nullptr;
    }

    std::shared_ptr<SysMLv2::REST::Branch> ProjectVersioningService::getDefaultBranch(std::shared_ptr<SysMLv2::REST::Project> project) {
        return project->getDefaultBranch();
    }

    std::shared_ptr<SysMLv2::REST::Project> ProjectVersioningService::setDefaultBranch(std::shared_ptr<SysMLv2::REST::Project> project, boost::uuids::uuid &branchId) {
        const auto branchesList = ProjectIdBranchMap.at(project->getId());

        for (const auto& branch : branchesList)
        {
            if (branch->getId()==branchId)
            {
                project->setDefaultBranch(branch);
                return project;
            }
        }
        throw std::runtime_error("Branch not found.");
    }

    std::shared_ptr<SysMLv2::REST::Branch> ProjectVersioningService::createBranch(std::shared_ptr<SysMLv2::REST::Project> project, std::string branchName, std::shared_ptr<SysMLv2::REST::Commit> head) {
        const auto newBranch = std::make_shared<SysMLv2::REST::Branch>(branchName);
        newBranch->setHead(head);
        newBranch->setOwningProject(project);
        ProjectIdBranchMap.at(project->getId()).push_back(newBranch);
        return newBranch;
    }

    std::shared_ptr<SysMLv2::REST::Branch> ProjectVersioningService::deleteBranch(std::shared_ptr<SysMLv2::REST::Project> project, boost::uuids::uuid &branchId) {
        auto& branchesList = ProjectIdBranchMap.at(project->getId());
        std::shared_ptr<SysMLv2::REST::Branch> branch;
        for (size_t i = 0; i< branchesList.size(); i++)
        {
            if (branchesList[i]->getId() == branchId)
                branch = branchesList[i];
        }
        ProjectIdBranchMap.at(project->getId()).erase(std::remove(ProjectIdBranchMap.at(project->getId()).begin(), ProjectIdBranchMap.at(project->getId()).end(), branch), ProjectIdBranchMap.at(project->getId()).end());
        return branch;
    }

    std::vector<std::shared_ptr<SysMLv2::REST::Tag>> ProjectVersioningService::getTags(std::shared_ptr<SysMLv2::REST::Project> project) {
        return ProjectIdTagMap.at(project->getId());
    }

    std::shared_ptr<SysMLv2::REST::Tag> ProjectVersioningService::getTagById(std::shared_ptr<SysMLv2::REST::Project> project, boost::uuids::uuid &tagId) {
        auto& tagList = ProjectIdTagMap.at(project->getId());
        for (const auto& tag : tagList)
        {
            if (tag->getId() == tagId)
                return tag;
        }
        return nullptr;
    }

    std::shared_ptr<SysMLv2::REST::Commit> ProjectVersioningService::getTaggedCommit(std::shared_ptr<SysMLv2::REST::Project>, std::shared_ptr<SysMLv2::REST::Tag> tag) {
        return tag->referencedCommit();
    }

    std::shared_ptr<SysMLv2::REST::Tag> ProjectVersioningService::createTag(std::shared_ptr<SysMLv2::REST::Project> project, std::string &tagName, std::shared_ptr<SysMLv2::REST::Commit> taggedCommit) {
        // A Tag is immutable: the tagged commit is passed to the constructor.
        const auto newTag = std::make_shared<SysMLv2::REST::Tag>(tagName, project, taggedCommit);
        ProjectIdTagMap[project->getId()].push_back(newTag);
        return newTag;
    }

    std::shared_ptr<SysMLv2::REST::MergeResult> ProjectVersioningService::mergeIntoBranch(std::shared_ptr<SysMLv2::REST::Branch>, std::vector<std::shared_ptr<SysMLv2::REST::Commit>>, std::shared_ptr<SysMLv2::REST::Data>, std::string&) {
        return nullptr;
    }

    std::vector<std::shared_ptr<SysMLv2::REST::DataDifference>> ProjectVersioningService::diffCommits(std::shared_ptr<SysMLv2::REST::Commit> , std::shared_ptr<SysMLv2::REST::Commit> , std::vector<int> ) {
        return std::vector<std::shared_ptr<SysMLv2::REST::DataDifference>>();
    }
}
