//
// Created by Moritz Herzog on 10.03.25.
//
//---------------------------------------------------------
// Constants, Definitions, Pragmas
//---------------------------------------------------------
#ifndef CPP_SYSMLV2_LIB_IPROJECTSERVICE_H
#define CPP_SYSMLV2_LIB_IPROJECTSERVICE_H
//---------------------------------------------------------
// External Classes
//---------------------------------------------------------
#include <vector>
#include <boost/uuid/uuid.hpp>
//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------

//---------------------------------------------------------
// Forwarding
//---------------------------------------------------------
namespace SysMLv2::Entities {
    class Project;
    class Branch;
}

namespace SysMLv2::API {
    /**
     * @class IProjectService
     * This represents the interface definition for the ProjectService according to the SysMLv2 Standard Version: 1.0 Beta 3.
     * @author Moritz Herzog
     * @version 1.0 Beta 3
     * @see SysMLv2::Entities::Project
     * @see SysMLv2::Entities::Branch
     * @see boost::uuids::uuid
     */
    class IProjectService {
    public:
        /**
         * Gets all Projects
         * @return A vector with all projects as pointer.
         * @see std::vector<T>
         */
        virtual std::vector<std::shared_ptr<SysMLv2::Entities::Project>> getProjects() =  0;

        /**
         * Gets a project from the given UUID.
         * @param projectId the project id of the project to search for.
         * @return A pointer to the given project.
         */
        virtual std::shared_ptr<SysMLv2::Entities::Project> getProjectById(boost::uuids::uuid projectId) = 0;

        /**
         * Creates a project with the given name and description.
         * @param projectName Name of the project as std::string
         * @param description Description of the project as std::string
         * @return A Pointer to the new project.
         */
        virtual std::shared_ptr<SysMLv2::Entities::Project> createProject(std::string projectName, std::string description) = 0;

        /**
         * Updates a project with the given branch. This can be update with the project Name, Description and default branch.
         * @param projectId The given project ID.
         * @param projectName The new project name.
         * @param description The new project description.
         * @param branch Pointer to the new default branch.
         * @return A Pointer to the updated project.
         */
        virtual std::shared_ptr<SysMLv2::Entities::Project> updateProject(boost::uuids::uuid projectId, std::string projectName = "", std::string description = "", SysMLv2::Entities::Branch* branch = nullptr) = 0;

        /**
         * Deletes a project. It is to remember that elements inside of a project should also be deleted to, except they are used inside of references
         * @param projectId The id of the project, that is to be deleted
         * @return The project that is now deleted inside of the controller. You should delete the project it self.
         */
        virtual std::shared_ptr<SysMLv2::Entities::Project> deleteProject(boost::uuids::uuid projectId) = 0;
    };
}

#endif //CPP_SYSMLV2_LIB_IPROJECTSERVICE_H
