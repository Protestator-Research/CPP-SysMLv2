//
// Created by Moritz Herzog on 10.03.25.
//
//---------------------------------------------------------
// Constants, Definitions, Pragmas
//---------------------------------------------------------
#ifndef CPP_SYSMLV2_LIB_IPROJECTVERSIONINGSERVICE_H
#define CPP_SYSMLV2_LIB_IPROJECTVERSIONINGSERVICE_H
//---------------------------------------------------------
// External Classes
//---------------------------------------------------------
#include <vector>
#include <string>
#include <boost/uuid/uuid.hpp>
//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include <entities/ChangeType.h>
#include "../sysmlv2service_global.h"
//---------------------------------------------------------
// Forwarding
//---------------------------------------------------------
namespace SysMLv2::REST {
    class Commit;
    class Project;
    class Branch;
    class DataVersion;
    class Tag;
    class MergeResult;
    class Data;
    class DataDifference;
}

namespace SysMLv2::API {
    /**
     * @class IProjectVersioningService
     * Interface of the Project Versioning Service from the SysMLv2 Standard
     * @version 1.0 Beta 3
     * @author Moritz Herzog
     * @see SysMLv2::Entities::Commit
     * @see SysMlv2::Entities::Project
     * @see SysMLv2::Entities::Branch
     * @see SysMLv2::Entities::DataVersion
     * @see SysMLv2::Entities::Tag
     * @see SysMlv2::Entities::MergeResult
     * @see SysMLv2::Entities::Data
     * @see SysMLv2::Entities::DataDifference
     */
    class SYSMLV2SERVICE_EXPORT IProjectVersioningService{
        /**
         * Gets all the commits from the given project.
         * @param project The given project, where the commits are returned.
         * @return A vector of the commits that are given.
         */
        virtual std::vector<std::shared_ptr<SysMLv2::REST::Commit>> getCommits(std::shared_ptr<SysMLv2::REST::Project> project) = 0;

        /**
         * Gets the head commit of the branch that is given and placed inside of the project.
         * @param project The project where the branch is located.
         * @param branch The branch that is inside of the project. If this is not specified (null) then the default branch is chosen.
         * @return The head commit of the branch as a pointer.
         */
        virtual std::shared_ptr<SysMLv2::REST::Commit> getHeadCommit(std::shared_ptr<SysMLv2::REST::Project> project, std::shared_ptr<SysMLv2::REST::Branch> branch) = 0;

        /**
         * Gets the specific commit from the project with the given UUID.
         * @param project The project where the commit is located.
         * @param commitId The id of the commit.
         * @return The specified commit by the project and the commit id.
         */
        virtual std::shared_ptr<SysMLv2::REST::Commit> getCommitById(std::shared_ptr<SysMLv2::REST::Project> project, boost::uuids::uuid commitId) = 0;

        /**
         *
         * @param change
         * @param branch
         * @param previousCommits
         * @param project
         * @return
         */
        virtual std::shared_ptr<SysMLv2::REST::Commit> createCommit(std::shared_ptr<SysMLv2::REST::DataVersion> change, std::shared_ptr<SysMLv2::REST::Branch> branch, std::vector<std::shared_ptr<SysMLv2::REST::Commit>> previousCommits, std::shared_ptr<SysMLv2::REST::Project> project) = 0;

        /**
         *
         * @param change
         * @param branch
         * @param project
         * @return
         */
        virtual std::shared_ptr<SysMLv2::REST::Commit> createCommit(std::shared_ptr<SysMLv2::REST::DataVersion> change, std::shared_ptr<SysMLv2::REST::Branch> branch, std::shared_ptr<SysMLv2::REST::Project> project) = 0;

        /**
         *
         * @param change
         * @param previousCommits
         * @param project
         * @return
         */
        virtual std::shared_ptr<SysMLv2::REST::Commit> createCommit(std::shared_ptr<SysMLv2::REST::DataVersion> change, std::vector<std::shared_ptr<SysMLv2::REST::Commit>> previousCommits, std::shared_ptr<SysMLv2::REST::Project> project) = 0;

        /**
         *
         * @param change
         * @param project
         * @return
         */
        virtual std::shared_ptr<SysMLv2::REST::Commit> createCommit(std::shared_ptr<SysMLv2::REST::DataVersion> change, std::shared_ptr<SysMLv2::REST::Project> project) = 0;

        /**
         *
         * @param project
         * @param commit
         * @return
         */
        virtual std::vector<std::shared_ptr<SysMLv2::REST::DataVersion>> getCommitChange(std::shared_ptr<SysMLv2::REST::Project> project, std::shared_ptr<SysMLv2::REST::Commit> commit, std::vector<SysMLv2::REST::ChangeType> ) = 0 ;

        /**
         *
         * @param project
         * @param commit
         * @param changeId
         * @return
         */
        virtual std::shared_ptr<SysMLv2::REST::DataVersion> getCommitChangeById(SysMLv2::REST::Project* project, SysMLv2::REST::Commit* commit, boost::uuids::uuid changeId ) = 0;

        /**
         *
         * @param project
         * @return
         */
        virtual std::vector<std::shared_ptr<SysMLv2::REST::Branch>> getBranches( SysMLv2::REST::Project* project ) = 0;

        /**
         *
         * @param project
         * @param branchId
         * @return
         */
        virtual std::shared_ptr<SysMLv2::REST::Branch> getBranchById(SysMLv2::REST::Project* project, boost::uuids::uuid branchId) = 0;

        /**
         *
         * @param project
         * @return
         */
        virtual std::shared_ptr<SysMLv2::REST::Branch> getDefaultBranch(SysMLv2::REST::Project* project) = 0;

        /**
         *
         * @param project
         * @param branchId
         * @return
         */
        virtual std::shared_ptr<SysMLv2::REST::Project> setDefaultBranch(SysMLv2::REST::Project* project, boost::uuids::uuid branchId) = 0;

        /**
         *
         * @param project
         * @param branchName
         * @param head
         * @return
         */
        virtual std::shared_ptr<SysMLv2::REST::Branch> createBranch(SysMLv2::REST::Project* project, std::string branchName, SysMLv2::REST::Commit* head) = 0;

        /**
         *
         * @param project
         * @param branchId
         * @return
         */
        virtual std::shared_ptr<SysMLv2::REST::Branch> deleteBranch(SysMLv2::REST::Project* project, boost::uuids::uuid branchId) = 0;

        /**
         *
         * @param project
         * @return
         */
        virtual std::vector<std::shared_ptr<SysMLv2::REST::Tag>> getTags(SysMLv2::REST::Project* project) = 0;

        /**
         *
         * @param project
         * @param tagId
         * @return
         */
        virtual std::shared_ptr<SysMLv2::REST::Tag> getTagById(SysMLv2::REST::Project* project, boost::uuids::uuid tagId) = 0;

        /**
         *
         * @param project
         * @param tag
         * @return
         */
        virtual std::shared_ptr<SysMLv2::REST::Commit> getTaggedCommit(SysMLv2::REST::Project* project, SysMLv2::REST::Tag* tag) = 0;

        /**
         *
         * @param project
         * @param tagName
         * @param taggedCommit
         * @return
         */
        virtual std::shared_ptr<SysMLv2::REST::Tag> createTag(SysMLv2::REST::Project* project, std::string tagName, SysMLv2::REST::Commit* taggedCommit) = 0;

        /**
         *
         * @param baseBranch
         * @param commitsToMerge
         * @param resolution
         * @param description
         * @return
         */
        virtual std::shared_ptr<SysMLv2::REST::MergeResult> mergeIntoBranch(SysMLv2::REST::Branch* baseBranch, std::vector<SysMLv2::REST::Commit> commitsToMerge, SysMLv2::REST::Data* resolution, std::string description) = 0;

        /**
         *
         * @param baseCommit
         * @param compareCommit
         * @param changeType
         * @return
         */
        virtual std::vector<std::shared_ptr<SysMLv2::REST::DataDifference>> diffCommits(SysMLv2::REST::Commit* baseCommit, SysMLv2::REST::Commit* compareCommit, std::vector<SysMLv2::REST::ChangeType> changeType) = 0;
    };
}
#endif //CPP_SYSMLV2_LIB_IPROJECTVERSIONINGSERVICE_H
