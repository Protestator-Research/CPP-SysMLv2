//
// Created by Moritz Herzog on 10.03.25.
//
//---------------------------------------------------------
// Constants, Definitions, Pragmas
//---------------------------------------------------------
#ifndef CPP_SYSMLV2_LIB_ELEMENTNAVIGATIONSERVIEC_H
#define CPP_SYSMLV2_LIB_ELEMENTNAVIGATIONSERVIEC_H
//---------------------------------------------------------
// External Classes
//---------------------------------------------------------
#include <vector>
#include <boost/uuid/uuid.hpp>
//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include "../entities/Direction.h"
//---------------------------------------------------------
// Forwarding
//---------------------------------------------------------
namespace SysMLv2::Entities{
    class Commit;
    class Project;
    class Element;
    class Relationship;
}

namespace SysMLv2::API {
    /**
     * @class IElementNavigationService
     * This represents the interface definition for the element navigation service.
     * @author Moritz Herzog
     * @version 1.0 Beta 3
     * @see SysMLv2::Entities::Commit
     * @see SysMlv2::Entities::Project
     * @see SysMLv2::Entities::Element
     * @see SysMLv2::Entities::Relationship
     */
    class IElementNavigationService {
    public:
        /**
         * Gets all the elements in a given project at a given commit.
         * @param project The given project.
         * @param commit The given commit inside of the project.
         * @return All the given that are available as a vector.
         */
        virtual std::vector<SysMLv2::Entities::Element*> getElements(SysMLv2::Entities::Project* project, SysMLv2::Entities::Commit* commit) = 0;

        /**
         * Gets an element with the project and commit it belongs to and its specific id.
         * @param project The project, where the element is located in.
         * @param commit The commit where the element is located in.
         * @param elementId The id of the specific element.
         * @return The element that is located. Can be null if no element is found.
         */
        virtual SysMLv2::Entities::Element* getElementById(SysMLv2::Entities::Project* project, SysMLv2::Entities::Commit* commit, boost::uuids::uuid elementId) = 0;

        /**
         * Gets the relationships that are incoming, outgoing, or both relative to the related element.
         * @param project The project where the element is located.
         * @param commit The commit where the element is located.
         * @param elementId The element id, allowing to specify the element to locate it.
         * @param direction The direction of the relationship. Defined with the enum and can ether be in, out, or both.
         * @return A vector of the relationships that are found.
         */
        virtual std::vector<SysMLv2::Entities::Relationship*> getRelationshipsByRelatedElement(SysMLv2::Entities::Project* project, SysMLv2::Entities::Commit* commit, boost::uuids::uuid elementId, SysMLv2::Entities::Direction direction) = 0;

        /**
         * Gets all root elements in the given project at the given commit.
         * @param project The project where the root elements are coming from.
         * @param commit The commit where the root elements are located.
         * @return A vector of all root elements available in the project and commit.
         */
        virtual std::vector<SysMLv2::Entities::Element*> getRootElements(SysMLv2::Entities::Project* project, SysMLv2::Entities::Commit* commit) = 0;
    };
}

#endif //CPP_SYSMLV2_LIB_ELEMENTNAVIGATIONSERVIEC_H
