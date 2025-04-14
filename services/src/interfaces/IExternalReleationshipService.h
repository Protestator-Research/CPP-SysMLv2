//
// Created by Moritz Herzog on 10.03.25.
//
//---------------------------------------------------------
// Constants, Definitions, Pragmas
//---------------------------------------------------------
#ifndef CPP_SYSMLV2_LIB_IEXTERNALRELEATIONSHIPSERVICE_H
#define CPP_SYSMLV2_LIB_IEXTERNALRELEATIONSHIPSERVICE_H
//---------------------------------------------------------
// External Classes
//---------------------------------------------------------
#include <boost/uuid/uuid.hpp>
#include <vector>
#include <memory>
//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include "../sysmlv2service_global.h"
//---------------------------------------------------------
// Forwarding
//---------------------------------------------------------
namespace SysMLv2::Entities{
    class Commit;
    class Project;
    class Branch;
    class ExternalRelationship;
}

namespace SysMLv2::API {
    /**
     * @class IExternalRelationShipService
     * This class represents an interface definition of the ExternalRelationshipService according to the SysMLv2 Standard Version: 1.0 Beta 3.
     * @version 1.0 Beta 3
     * @author Moritz Herzog
     * @see SysMLv2::Entities::Project
     * @see SysMLv2::Entities::Commit
     * @see SysMLv2::Entities::Branch
     * @see SysMLv2::Entities::ExternalRelationship
     */
    class SYSMLV2SERVICE_EXPORT IExternalRelationshipService {
    public:
        /**
         * This is a interface for the method implementation that returns all all the external relationships for one specific commit in one project.
         * @param project The project where the commit and the external relationships are located.
         * @param commit The commit where the external relationships are located.
         * @return A vector of all external relationships.
         * @see std::vector
         */
        virtual std::vector<std::shared_ptr<SysMLv2::Entities::ExternalRelationship>> getExternalRelationships(std::shared_ptr<SysMLv2::Entities::Project> project, std::shared_ptr<SysMLv2::Entities::Commit> commit) = 0;

        /**
         * This is a interface for the method that get all the external relationships in the given commit where the id of the end element equals the given id.
         * @param project The given project, where the commit is located.
         * @param commit The given commit that in which it is looked.
         * @param elementId The given element id, for which is searched.
         * @return A vector of all matching external relationships.
         */
        virtual std::vector<std::shared_ptr<SysMLv2::Entities::ExternalRelationship>> getExternalRelationshipsByElement(std::shared_ptr<SysMLv2::Entities::Project> project, std::shared_ptr<SysMLv2::Entities::Commit> commit, boost::uuids::uuid elementId) = 0;

        /**
         * Get the external relationship with the given id, which is located in the given project and commit.
         * @param project The given project, where the commit is located.
         * @param commit The given commit, where the external relationship is located.
         * @param externalRelationshipId The id of the external relationship, that is searched for.
         * @return Can be null, if no external relationship is found, otherwise a pointer to the external relationship.
         */
        virtual std::shared_ptr<SysMLv2::Entities::ExternalRelationship> getExternalRelationshipById(std::shared_ptr<SysMLv2::Entities::Project> project, std::shared_ptr<SysMLv2::Entities::Commit> commit, boost::uuids::uuid externalRelationshipId) = 0;

        /**
         * Creates the eternal relationship in the given project and branch.
         * @param project The given project where the external relationship is required.
         * @param branch The given branch, where the commit is located. If is given as null, the program will resort to the default branch.
         * @param externalRelationship The external relationship that is filled by the program. Can not be null.
         */
        virtual void createExternalRelationship(std::shared_ptr<SysMLv2::Entities::Project> project, std::shared_ptr<SysMLv2::Entities::Branch> branch, std::shared_ptr<SysMLv2::Entities::ExternalRelationship> externalRelationship) = 0;

        /**
         * Deletes the external relationship, in the given project and branch and commit.
         * @param project The project where the external relationship is located.
         * @param branch The branch where the external relationship is located. If this is null, the program resorts to the default branch.
         * @param externalRelationshipId The if of the external relationship, that is deleted.
         */
        virtual void deleteExternalRelationship(std::shared_ptr<SysMLv2::Entities::Project> project, std::shared_ptr<SysMLv2::Entities::Branch> branch, boost::uuids::uuid externalRelationshipId) = 0;
    };
}
#endif //CPP_SYSMLV2_LIB_IEXTERNALRELEATIONSHIPSERVICE_H
