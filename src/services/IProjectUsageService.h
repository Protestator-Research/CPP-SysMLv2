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

//---------------------------------------------------------
// Forwarding
//---------------------------------------------------------
namespace SysMLv2::Entities{
    class Commit;
    class Project;
    class Branch;
    class ProjectUsage;
}

namespace SysMLv2::API {
    /**
     * @class IProjectUsageService
     * This class represents an interface definition according to the SysMLv2 Standard Version: 1.0 Beta 3.
     * @author Moritz Herzog
     * @version 1.0 Beta 3
     * @see SysMLv2::Entities::Commit
     * @see SysMLv2::Entities::ProjectUsage
     */
    class IProjectUsageService {
    public:
        /**
         * This is the interface implementation of the method, that gets all the project usages in the given project.
         * @param project The project that is given by the project. If this variable is null, it might result in a segmentation fault or a exception.
         * @param commit The commit that is given to get the project usage. If this variable is null, it might result is a segmentation fault or a exception.
         * @return All the project usages, that are stored in the project.
         */
        virtual std::vector<SysMLv2::Entities::ProjectUsage*> getProjectUsage(SysMLv2::Entities::Project* project, SysMLv2::Entities::Commit* commit) = 0;

        /**
         *  Interface for the method that deletes the project usage with the given id from the given project at the head commit of the given branch.
         * @param project The project that is given by the User. If this is null it might result in a segmentation fault or exception.
         * @param branch The branch that is given by the User. This variable might be null, then the default branch is assumed.
         * @param projectUsageId The ID (UUID) of the project usage that is deleted.
         * @return returns a new commit with the given project usage.
         * @see boost::uuids::uuid
         */
        virtual SysMLv2::Entities::Commit* deleteProjectUsage(SysMLv2::Entities::Project* project, SysMLv2::Entities::Branch* branch, boost::uuids::uuid projectUsageId) = 0;

        /**
         * Interface of the method that creates a new project usage in the given project at the head of the given branch.
         * @param project The project that is given. Please remember this could lead to segmentation fault or exception if null.
         * @param branch The branch that is given. This can be null, if this is null the internal default branch is used.
         * @param projectUsage The given project usage for the new Commit.
         * @return The new commit is now part of the project.
         */
        virtual SysMLv2::Entities::Commit* createProjectUsage(SysMLv2::Entities::Project* project, SysMLv2::Entities::Branch* branch, SysMLv2::Entities::ProjectUsage* projectUsage) = 0;
    };
}

#endif //CPP_SYSMLV2_PROJECTUSAGESERVICE_H
