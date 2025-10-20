//
// Created by Moritz Herzog on 09.04.25.
//

#ifndef SYSML_PROJECTVERSIONINGSERVICE_H
#define SYSML_PROJECTVERSIONINGSERVICE_H

#include <sysmlv2/service/interfaces/IProjectVersioningService.h>
#include "entities/ChangeType.h"
#include <map>
#include <boost/uuid/uuid.hpp>

namespace SysMLv2::API {
    class ProjectVersioningService : public SysMLv2::API::IProjectVersioningService{
    public:
        ProjectVersioningService() = default;
        ~ProjectVersioningService() override = default;

        std::vector<std::shared_ptr<SysMLv2::REST::Commit>> getCommits(std::shared_ptr<SysMLv2::REST::Project> project) override;

        std::shared_ptr<SysMLv2::REST::Commit> getHeadCommit(std::shared_ptr<SysMLv2::REST::Project> project, std::shared_ptr<SysMLv2::REST::Branch> branch) override;

        std::shared_ptr<SysMLv2::REST::Commit> getCommitById(std::shared_ptr<SysMLv2::REST::Project> project, boost::uuids::uuid commitId) override;

        std::shared_ptr<SysMLv2::REST::Commit> createCommit(std::shared_ptr<SysMLv2::REST::DataVersion> change, std::shared_ptr<SysMLv2::REST::Branch> branch, std::vector<std::shared_ptr<SysMLv2::REST::Commit>> previousCommits, std::shared_ptr<SysMLv2::REST::Project> project) override;

        std::shared_ptr<SysMLv2::REST::Commit> createCommit(std::shared_ptr<SysMLv2::REST::DataVersion> change, std::shared_ptr<SysMLv2::REST::Branch> branch, std::shared_ptr<SysMLv2::REST::Project> project) override;

        std::shared_ptr<SysMLv2::REST::Commit> createCommit(std::shared_ptr<SysMLv2::REST::DataVersion> change, std::vector<std::shared_ptr<SysMLv2::REST::Commit>> previousCommits, std::shared_ptr<SysMLv2::REST::Project> project) override;

        std::shared_ptr<SysMLv2::REST::Commit> createCommit(std::shared_ptr<SysMLv2::REST::DataVersion> change, std::shared_ptr<SysMLv2::REST::Project> project) override;

        std::vector<std::shared_ptr<SysMLv2::REST::DataVersion>> getCommitChange(std::shared_ptr<SysMLv2::REST::Project> project, std::shared_ptr<SysMLv2::REST::Commit> commit, std::vector<SysMLv2::REST::ChangeType>) override;

        std::shared_ptr<SysMLv2::REST::DataVersion> getCommitChangeById(std::shared_ptr<SysMLv2::REST::Project> project, std::shared_ptr<SysMLv2::REST::Commit> commit, boost::uuids::uuid &changeId) override;

        std::vector<std::shared_ptr<SysMLv2::REST::Branch>> getBranches(std::shared_ptr<SysMLv2::REST::Project> project) override;

        std::shared_ptr<SysMLv2::REST::Branch> getBranchById(std::shared_ptr<SysMLv2::REST::Project> project, boost::uuids::uuid &branchId) override;

        std::shared_ptr<SysMLv2::REST::Branch> getDefaultBranch(std::shared_ptr<SysMLv2::REST::Project> project) override;

        std::shared_ptr<SysMLv2::REST::Project> setDefaultBranch(std::shared_ptr<SysMLv2::REST::Project> project, boost::uuids::uuid &branchId) override;

        std::shared_ptr<SysMLv2::REST::Branch> createBranch(std::shared_ptr<SysMLv2::REST::Project> project, std::string branchName, std::shared_ptr<SysMLv2::REST::Commit> head) override;

        std::shared_ptr<SysMLv2::REST::Branch> deleteBranch(std::shared_ptr<SysMLv2::REST::Project> project, boost::uuids::uuid &branchId) override;

        std::vector<std::shared_ptr<SysMLv2::REST::Tag>> getTags(std::shared_ptr<SysMLv2::REST::Project> project) override;

        std::shared_ptr<SysMLv2::REST::Tag> getTagById(std::shared_ptr<SysMLv2::REST::Project> project, boost::uuids::uuid &tagId) override;

        std::shared_ptr<SysMLv2::REST::Commit> getTaggedCommit(std::shared_ptr<SysMLv2::REST::Project> project, std::shared_ptr<SysMLv2::REST::Tag> tag) override;

        std::shared_ptr<SysMLv2::REST::Tag> createTag(std::shared_ptr<SysMLv2::REST::Project> project, std::string &tagName, std::shared_ptr<SysMLv2::REST::Commit> taggedCommit) override;

        std::shared_ptr<SysMLv2::REST::MergeResult> mergeIntoBranch(std::shared_ptr<SysMLv2::REST::Branch> baseBranch, std::vector<std::shared_ptr<SysMLv2::REST::Commit>> commitsToMerge, std::shared_ptr<SysMLv2::REST::Data> resolution, std::string &description) override;

        std::vector<std::shared_ptr<SysMLv2::REST::DataDifference>> diffCommits(std::shared_ptr<SysMLv2::REST::Commit> baseCommit, std::shared_ptr<SysMLv2::REST::Commit> compareCommit, std::vector<SysMLv2::REST::ChangeType> changeType) override;

    protected:
        std::map<boost::uuids::uuid, std::vector<std::shared_ptr<SysMLv2::REST::Commit>>> ProjectIdCommitMap;
        std::map<boost::uuids::uuid, std::vector<std::shared_ptr<SysMLv2::REST::Branch>>> ProjectIdBranchMap;
        std::map<boost::uuids::uuid, std::vector<std::shared_ptr<SysMLv2::REST::Tag>>> ProjectIdTagMap;
    };
}


#endif //SYSML_PROJECTVERSIONINGSERVICE_H
