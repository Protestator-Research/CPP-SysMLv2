//
// Created by Moritz Herzog on 10.03.25.
//
//---------------------------------------------------------
// Constants, Definitions, Pragmas
//---------------------------------------------------------
#ifndef CPP_SYSMLV2_PROJECTUSAGESERVICE_H
#define CPP_SYSMLV2_PROJECTUSAGESERVICE_H
//---------------------------------------------------------
// External Classes
//---------------------------------------------------------
#include <boost/uuid/uuid.hpp>
#include <vector>
//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include "../sysmlv2service_global.h"
//---------------------------------------------------------
// Forwarding
//---------------------------------------------------------
namespace SysMLv2::REST{
    class Commit;
    class Project;
    class Branch;
    class ProjectUsage;
}

namespace SysMLv2::API {
    /**
     * @class IProjectUsageService
     * This class represents an interface definition of the ProjectUsageService according to the SysMLv2 Standard Version: 1.0 Beta 3.
     * @author Moritz Herzog
     * @version 1.0 Beta 3
     * @see SysMLv2::REST::Commit
     * @see SysMLv2::REST::Project
     * @see SysMLv2::REST::ProjectUsage
     * @see boost::uuids::uuid
     */
    class SYSMLV2SERVICE_EXPORT IProjectUsageService {
    public:
        virtual ~IProjectUsageService() = default;

        /**
         * This is the interface implementation of the method, that gets all the project usages in the given project.
         * @param project The project that is given by the project. If this variable is null, it might result in a segmentation fault or a exception.
         * @param commit The commit that is given to get the project usage. If this variable is null, it might result is a segmentation fault or a exception.
         * @return All the project usages, that are stored in the project.
         */
        virtual std::vector<std::shared_ptr<SysMLv2::REST::ProjectUsage>> getProjectUsage(std::shared_ptr<SysMLv2::REST::Project> project, std::shared_ptr<SysMLv2::REST::Commit> commit) = 0;

        /**
         *  Interface for the method that deletes the project usage with the given id from the given project at the head commit of the given branch.
         * @param project The project that is given by the User. If this is null it might result in a segmentation fault or exception.
         * @param branch The branch that is given by the User. This variable might be null, then the default branch is assumed.
         * @param projectUsageId The ID (UUID) of the project usage that is deleted.
         * @return returns a new commit with the given project usage.
         * @see boost::uuids::uuid
         */
        virtual std::shared_ptr<SysMLv2::REST::Commit> deleteProjectUsage(std::shared_ptr<SysMLv2::REST::Project> project, std::shared_ptr<SysMLv2::REST::Branch> branch, boost::uuids::uuid& projectUsageId) = 0;

        /**
         * Interface of the method that creates a new project usage in the given project at the head of the given branch.
         * @param project The project that is given. Please remember this could lead to segmentation fault or exception if null.
         * @param branch The branch that is given. This can be null, if this is null the internal default branch is used.
         * @param projectUsage The given project usage for the new Commit.
         * @return The new commit is now part of the project.
         */
        virtual std::shared_ptr<SysMLv2::REST::Commit> createProjectUsage(std::shared_ptr<SysMLv2::REST::Project> project, std::shared_ptr<SysMLv2::REST::Branch> branch, std::shared_ptr<SysMLv2::REST::ProjectUsage> projectUsage) = 0;
    };
}

#endif //CPP_SYSMLV2_PROJECTUSAGESERVICE_H
