//
// Created by Moritz Herzog on 10.03.25.
//
// SysMLv2 C++ Library Implementation
// Copyright (C) 2025  Moritz Herzog
//
//This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
//This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
//---------------------------------------------------------
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
#include <memory>
//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include <sysmlv2/interfaces/sysmlv2interfaces_global.h>
//---------------------------------------------------------
// Forwarding
//---------------------------------------------------------
namespace SysMLv2::REST{
    class Commit;
    class Project;
}

namespace KerML::Entities {
    class Element;
    class Relationship;
}

namespace SysMLv2::API {
    /**
     * @class IElementNavigationService
     * This represents the interface definition for the element navigation service.
     * @author Moritz Herzog
     * @version 1.0 Beta 3
     * @see SysMLv2::REST::Commit
     * @see SysMlv2::REST::Project
     * @see SysMLv2::REST::Element
     * @see SysMLv2::REST::Relationship
     */
    class SYSMLV2INTERFACE_EXPORT IElementNavigationService {
    public:
        /**
         * Gets all the elements in a given project at a given commit.
         * @param project The given project.
         * @param commit The given commit inside of the project.
         * @return All the given that are available as a vector.
         */
        virtual std::vector<std::shared_ptr<KerML::Entities::Element>> getElements(std::shared_ptr<SysMLv2::REST::Project> project, std::shared_ptr<SysMLv2::REST::Commit> commit) = 0;

        /**
         * Gets an element with the project and commit it belongs to and its specific id.
         * @param project The project, where the element is located in.
         * @param commit The commit where the element is located in.
         * @param elementId The id of the specific element.
         * @return The element that is located. Can be null if no element is found.
         */
        virtual std::shared_ptr<KerML::Entities::Element> getElementById(std::shared_ptr<SysMLv2::REST::Project> project, std::shared_ptr<SysMLv2::REST::Commit> commit, boost::uuids::uuid elementId) = 0;

        /**
         * Gets the relationships that are incoming, outgoing, or both relative to the related element.
         * @param project The project where the element is located.
         * @param commit The commit where the element is located.
         * @param elementId The element id, allowing to specify the element to locate it.
         * @param direction The direction of the relationship. Defined with the enum and can ether be in, out, or both.
         * @return A vector of the relationships that are found.
         */
        virtual std::vector<std::shared_ptr<KerML::Entities::Relationship>> getRelationshipsByRelatedElement(std::shared_ptr<SysMLv2::REST::Project> project, std::shared_ptr<SysMLv2::REST::Commit> commit, boost::uuids::uuid elementId, int direction) = 0;

        /**
         * Gets all root elements in the given project at the given commit.
         * @param project The project where the root elements are coming from.
         * @param commit The commit where the root elements are located.
         * @return A vector of all root elements available in the project and commit.
         */
        virtual std::vector<std::shared_ptr<KerML::Entities::Element>> getRootElements(std::shared_ptr<SysMLv2::REST::Project> project, std::shared_ptr<SysMLv2::REST::Commit> commit) = 0;
    };
}

#endif //CPP_SYSMLV2_LIB_ELEMENTNAVIGATIONSERVIEC_H
