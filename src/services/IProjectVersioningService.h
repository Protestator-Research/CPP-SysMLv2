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
#include "../entities/ChangeType.h"
//---------------------------------------------------------
// Forwarding
//---------------------------------------------------------
namespace SysMLv2::Entities {
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
    class IProjectVersioningService{
        /**
         * Gets all the commits from the given project.
         * @param project The given project, where the commits are returned.
         * @return A vector of the commits that are given.
         */
        virtual std::vector<SysMLv2::Entities::Commit*> getCommits(SysMLv2::Entities::Project* project) = 0;

        /**
         * Gets the head commit of the branch that is given and placed inside of the project.
         * @param project The project where the branch is located.
         * @param branch The branch that is inside of the project. If this is not specified (null) then the default branch is chosen.
         * @return The head commit of the branch as a pointer.
         */
        virtual SysMLv2::Entities::Commit* getHeadCommit(SysMLv2::Entities::Project* project, SysMLv2::Entities::Branch* branch) = 0;

        /**
         *
         * @param project
         * @param commitId
         * @return
         */
        virtual SysMLv2::Entities::Commit* getCommitById(SysMLv2::Entities::Project* project, boost::uuids::uuid commitId) = 0;

        /**
         *
         * @param change
         * @param branch
         * @param previousCommits
         * @param project
         * @return
         */
        virtual SysMLv2::Entities::Commit* createCommit(SysMLv2::Entities::DataVersion* change, SysMLv2::Entities::Branch* branch, std::vector<SysMLv2::Entities::Commit*> previousCommits, SysMLv2::Entities::Project* project) = 0;

        /**
         *
         * @param change
         * @param branch
         * @param project
         * @return
         */
        virtual SysMLv2::Entities::Commit* createCommit(SysMLv2::Entities::DataVersion* change, SysMLv2::Entities::Branch* branch, SysMLv2::Entities::Project* project) = 0;

        /**
         *
         * @param change
         * @param previousCommits
         * @param project
         * @return
         */
        virtual SysMLv2::Entities::Commit* createCommit(SysMLv2::Entities::DataVersion* change, std::vector<SysMLv2::Entities::Commit*> previousCommits, SysMLv2::Entities::Project* project) = 0;

        /**
         *
         * @param change
         * @param project
         * @return
         */
        virtual SysMLv2::Entities::Commit* createCommit(SysMLv2::Entities::DataVersion* change, SysMLv2::Entities::Project* project) = 0;

        /**
         *
         * @param project
         * @param commit
         * @return
         */
        virtual std::vector<SysMLv2::Entities::DataVersion*> getCommitChange(SysMLv2::Entities::Project* project, SysMLv2::Entities::Commit* commit, std::vector<SysMLv2::Entities::ChangeType> ) = 0 ;

        /**
         *
         * @param project
         * @param commit
         * @param changeId
         * @return
         */
        virtual SysMLv2::Entities::DataVersion* getCommitChangeById(SysMLv2::Entities::Project* project, SysMLv2::Entities::Commit* commit, boost::uuids::uuid changeId ) = 0;

        /**
         *
         * @param project
         * @return
         */
        virtual std::vector<SysMLv2::Entities::Branch*> getBranches( SysMLv2::Entities::Project* project ) = 0;

        /**
         *
         * @param project
         * @param branchId
         * @return
         */
        virtual SysMLv2::Entities::Branch* getBranchById(SysMLv2::Entities::Project* project, boost::uuids::uuid branchId) = 0;

        /**
         *
         * @param project
         * @return
         */
        virtual SysMLv2::Entities::Branch* getDefaultBranch(SysMLv2::Entities::Project* project) = 0;

        /**
         *
         * @param project
         * @param branchId
         * @return
         */
        virtual SysMLv2::Entities::Project* setDefaultBranch(SysMLv2::Entities::Project* project, boost::uuids::uuid branchId) = 0;

        /**
         *
         * @param project
         * @param branchName
         * @param head
         * @return
         */
        virtual SysMLv2::Entities::Branch* createBranch(SysMLv2::Entities::Project* project, std::string branchName, SysMLv2::Entities::Commit* head);

        /**
         *
         * @param project
         * @param branchId
         * @return
         */
        virtual SysMLv2::Entities::Branch* deleteBranch(SysMLv2::Entities::Project* project, boost::uuids::uuid branchId) = 0;

        /**
         *
         * @param project
         * @return
         */
        virtual std::vector<SysMLv2::Entities::Tag*> getTags(SysMLv2::Entities::Project* project) = 0;

        /**
         *
         * @param project
         * @param tagId
         * @return
         */
        virtual SysMLv2::Entities::Tag* getTagById(SysMLv2::Entities::Project* project, boost::uuids::uuid tagId) = 0;

        /**
         *
         * @param project
         * @param tag
         * @return
         */
        virtual SysMLv2::Entities::Commit* getTaggedCommit(SysMLv2::Entities::Project* project, SysMLv2::Entities::Tag* tag) = 0;

        /**
         *
         * @param project
         * @param tagName
         * @param taggedCommit
         * @return
         */
        virtual SysMLv2::Entities::Tag* createTag(SysMLv2::Entities::Project* project, std::string tagName, SysMLv2::Entities::Commit* taggedCommit) = 0;

        /**
         *
         * @param baseBranch
         * @param commitsToMerge
         * @param resolution
         * @param description
         * @return
         */
        virtual SysMLv2::Entities::MergeResult* mergeIntoBranch(SysMLv2::Entities::Branch* baseBranch, std::vector<SysMLv2::Entities::Commit> commitsToMerge, SysMLv2::Entities::Data* resolution, std::string description) = 0;

        /**
         *
         * @param baseCommit
         * @param compareCommit
         * @param changeType
         * @return
         */
        virtual std::vector<SysMLv2::Entities::DataDifference*> diffCommits(SysMLv2::Entities::Commit* baseCommit, SysMLv2::Entities::Commit* compareCommit, std::vector<SysMLv2::Entities::ChangeType> changeType) = 0;
    };
}
#endif //CPP_SYSMLV2_LIB_IPROJECTVERSIONINGSERVICE_H
