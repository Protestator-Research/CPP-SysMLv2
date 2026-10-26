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

//---------------------------------------------------------
// Constants, Definitions, Pragmas
//---------------------------------------------------------
#pragma once
//---------------------------------------------------------
// External Classes
//---------------------------------------------------------
#include <memory>
#include <vector>
#include <boost/uuid/uuid.hpp>

//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include <sysmlv2/rest/sysmlv2rest_global.h>
//---------------------------------------------------------
// Forwarding
//---------------------------------------------------------
namespace SysMLv2::REST {
    class Data;
}

namespace SysMLv2::REST::Versioning {
    /**
     * The elements a Relationship refers to, as ids. They are read from the JSON of the payload, because the references of a
     * deserialized element are resolved lazily and source(), target() or owner() can be empty (a payload is deserialized on its
     * own, without the elements it refers to).
     */
    struct SYSMLV2REST_EXPORT RelationshipEnds {
        /** False if the payload is no KerML Relationship. The other members are empty then. */
        bool isRelationship = false;
        std::vector<boost::uuids::uuid> source;
        std::vector<boost::uuids::uuid> target;
        std::vector<boost::uuids::uuid> relatedElement;
        std::vector<boost::uuids::uuid> ownedRelatedElement;
        std::vector<boost::uuids::uuid> owningRelatedElement;
    };

    /**
     * The ends of the payload if it is a KerML Relationship.
     */
    SYSMLV2REST_EXPORT RelationshipEnds relationshipEnds(const std::shared_ptr<Data>& payload);

    /**
     * True if the JSON of the payload names an owner: a non-empty owner, owningRelationship or owningRelatedElement.
     */
    SYSMLV2REST_EXPORT bool declaresOwner(const std::shared_ptr<Data>& payload);
}
