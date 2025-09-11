//
// Created by Moritz Herzog on 09.04.25.
//

#include "ProjectVersioningService.h"

#include <boost/uuid/nil_generator.hpp>

#include "entities/Project.h"
#include "entities/Branch.h"
#include "entities/Commit.h"
#include "entities/Data.h"
#include "entities/DataVersion.h"
#include "entities/Tag.h"

namespace SysMLv2::API {
    std::vector<std::shared_ptr<SysMLv2::REST::Commit>> ProjectVersioningService::getCommits(std::shared_ptr<SysMLv2::REST::Project> project) {
        return ProjectIdCommitMap[project->getId()];
    }

    std::shared_ptr<SysMLv2::REST::Commit> ProjectVersioningService::getHeadCommit(std::shared_ptr<SysMLv2::REST::Project> project, std::shared_ptr<SysMLv2::REST::Branch> branch) {
        return branch->getHead();
    }

    std::shared_ptr<SysMLv2::REST::Commit> ProjectVersioningService::getCommitById(std::shared_ptr<SysMLv2::REST::Project> project, boost::uuids::uuid commitId) {
        const auto projectCommits = ProjectIdCommitMap[project->getId()];
        for (const auto& commit:projectCommits)
        {
            if (commit->getId() == commitId)
                return commit;
        }
        return nullptr;
    }

    std::shared_ptr<SysMLv2::REST::Commit> ProjectVersioningService::createCommit(std::shared_ptr<SysMLv2::REST::DataVersion> change, std::shared_ptr<SysMLv2::REST::Branch> branch, std::vector<std::shared_ptr<SysMLv2::REST::Commit>> previousCommits, std::shared_ptr<SysMLv2::REST::Project> project) {
        const auto commit = std::make_shared<SysMLv2::REST::Commit>("", "", project, previousCommits);
        commit->addChange(change);

        ProjectIdCommitMap[project->getId()].push_back(commit);
        branch->setHead(commit);

        return commit;
    }

    std::shared_ptr<SysMLv2::REST::Commit> ProjectVersioningService::createCommit(std::shared_ptr<SysMLv2::REST::DataVersion> change, std::shared_ptr<SysMLv2::REST::Branch> branch, std::shared_ptr<SysMLv2::REST::Project> project) {
        const auto commit = std::make_shared<SysMLv2::REST::Commit>("", "", project);
        commit->addChange(change);

        ProjectIdCommitMap[project->getId()].push_back(commit);
        branch->setHead(commit);

        return commit;
    }

    std::shared_ptr<SysMLv2::REST::Commit> ProjectVersioningService::createCommit(std::shared_ptr<SysMLv2::REST::DataVersion> change, std::vector<std::shared_ptr<SysMLv2::REST::Commit>> previousCommits, std::shared_ptr<SysMLv2::REST::Project> project) {
        const auto commit = std::make_shared<SysMLv2::REST::Commit>("", "", project, previousCommits);
        commit->addChange(change);

        ProjectIdCommitMap[project->getId()].push_back(commit);
        project->getDefaultBranch()->setHead(commit);

        return commit;
    }

    std::shared_ptr<SysMLv2::REST::Commit> ProjectVersioningService::createCommit(std::shared_ptr<SysMLv2::REST::DataVersion> change, std::shared_ptr<SysMLv2::REST::Project> project) {
        const auto commit = std::make_shared<SysMLv2::REST::Commit>("", "", project);
        commit->addChange(change);

        ProjectIdCommitMap[project->getId()].push_back(commit);
        project->getDefaultBranch()->setHead(commit);

        return commit;
    }

    std::vector<std::shared_ptr<SysMLv2::REST::DataVersion>> ProjectVersioningService::getCommitChange(std::shared_ptr<SysMLv2::REST::Project> project, std::shared_ptr<SysMLv2::REST::Commit> commit, std::vector<SysMLv2::REST::ChangeType> changeType) {
        std::vector<std::shared_ptr<SysMLv2::REST::DataVersion>> returnValue;

        uint8_t filter = 0x00;

        for (const auto change : changeType)
            filter |= (uint8_t)change;

        for (const auto& dataVersion : commit->getDataVersion())
        {
            if ((REST::ChangeType::CREATED & filter)&&(dataVersion->getPayload()->getId()==boost::uuids::nil_uuid()))
        }

        return returnValue;
    }

    std::shared_ptr<SysMLv2::REST::DataVersion> ProjectVersioningService::getCommitChangeById(std::shared_ptr<SysMLv2::REST::Project> project, std::shared_ptr<SysMLv2::REST::Commit> commit, boost::uuids::uuid &changeId) {
        for (const auto& change : commit->getDataVersion())
        {
            if (change->getId() == changeId)
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

        for (const auto branch : branchesList)
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
        ProjectIdBranchMap.at(project->getId()).erase(std::remove(ProjectIdBranchMap.at(project->getId()).begin(), ProjectIdBranchMap.at(project->getId()).end(), branch));
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

    std::shared_ptr<SysMLv2::REST::Commit> ProjectVersioningService::getTaggedCommit(std::shared_ptr<SysMLv2::REST::Project> project, std::shared_ptr<SysMLv2::REST::Tag> tag) {
        return tag->referencedCommit();
    }

    std::shared_ptr<SysMLv2::REST::Tag> ProjectVersioningService::createTag(std::shared_ptr<SysMLv2::REST::Project> project, std::string &tagName, std::shared_ptr<SysMLv2::REST::Commit> taggedCommit) {
        const auto newTag = std::make_shared<SysMLv2::REST::Tag>(tagName);
        newTag->setReferencedCommit(taggedCommit);
        ProjectIdTagMap[project->getId()].push_back(newTag);
        return newTag;
    }

    std::shared_ptr<SysMLv2::REST::MergeResult> ProjectVersioningService::mergeIntoBranch(std::shared_ptr<SysMLv2::REST::Branch>, std::vector<std::shared_ptr<SysMLv2::REST::Commit>>, std::shared_ptr<SysMLv2::REST::Data>, std::string&) {
        return nullptr;
    }

    std::vector<std::shared_ptr<SysMLv2::REST::DataDifference>> ProjectVersioningService::diffCommits(std::shared_ptr<SysMLv2::REST::Commit> baseCommit, std::shared_ptr<SysMLv2::REST::Commit> compareCommit, std::vector<SysMLv2::REST::ChangeType> changeType) {
        return std::vector<std::shared_ptr<SysMLv2::REST::DataDifference>>();
    }
}
