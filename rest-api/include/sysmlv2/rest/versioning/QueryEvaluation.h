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
#include <string>
#include <vector>
#include <boost/uuid/uuid.hpp>
#include <nlohmann/json.hpp>

//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include <sysmlv2/rest/versioning/VersionedData.h>
#include <sysmlv2/rest/sysmlv2rest_global.h>
//---------------------------------------------------------
// Forwarding
//---------------------------------------------------------
namespace SysMLv2::REST {
    class Constraint;
    class Data;
    class Query;
    class QueryRequest;
}

/**
 * Evaluation of a Query (7.1.4, 7.2.4) on the Data of a commit, without any dependency on a transport or a database.
 *
 * - The properties are read from the JSON of the payload ("@id", "@type" and every other key, also derived ones). A key that
 *   is written as a path with dots ("a.b") is followed through objects; an array matches if one of its entries does.
 * - A reference {"@id": X} is compared with a value by the id X.
 * - instanceOf: the library has no type hierarchy of the metaclasses. A payload is an instance of its own "@type", of
 *   "Data", of "Element" if it is a KerML element and of "Relationship" if it is a KerML relationship. Any other
 *   supertype (for example "Type" for a "PartDefinition") is not known and does not match.
 */
namespace SysMLv2::REST::Versioning {
    /**
     * True if the payload JSON satisfies the constraint.
     * @param constraint A PrimitiveConstraint or a CompositeConstraint.
     * @param payload The JSON of one Data object.
     * @param payloadData The Data object the JSON was taken from; used for instanceOf. May be nullptr.
     */
    SYSMLV2REST_EXPORT bool satisfies(const Constraint& constraint, const nlohmann::json& payload,
                                      const std::shared_ptr<Data>& payloadData = nullptr);

    /**
     * The identities that belong to the scope: the given ones and everything they own, transitively. Ownership is read from
     * the JSON of the payloads: ownedElement, ownedRelationship and ownedRelatedElement of an element, and, for the case that
     * a client sent only the other direction, the owner, owningRelationship and owningRelatedElement of the elements.
     * Identities that are not part of the state are not part of the result.
     */
    SYSMLV2REST_EXPORT std::vector<boost::uuids::uuid> scopeClosure(const std::vector<boost::uuids::uuid>& scope,
                                                                    const VersionedData& state);

    /**
     * executeQuery: the Data of the state that satisfy the constraint, within the scope, sorted by orderBy, reduced to the
     * selected properties.
     * @param select Properties to keep; "@id" and "@type" are always kept. Empty keeps all properties.
     * @param scope Identities that limit the query, with everything they own. Empty is the whole state (the project).
     * @param orderBy Properties to sort by, ascending, in the order of the list. Missing and null values come first, then
     *                booleans, numbers and strings; a reference sorts by its id. Equal rows stay in the order of identity.
     * @param where The constraint. nullptr selects everything.
     * @return One JSON object per Data object.
     */
    SYSMLV2REST_EXPORT std::vector<nlohmann::json> executeQuery(const std::vector<std::string>& select,
                                                                 const std::vector<boost::uuids::uuid>& scope,
                                                                 const std::vector<std::string>& orderBy,
                                                                 const std::shared_ptr<Constraint>& where,
                                                                 const VersionedData& state);

    /** executeQuery with the parts of a stored Query. */
    SYSMLV2REST_EXPORT std::vector<nlohmann::json> executeQuery(const Query& query, const VersionedData& state);

    /** executeQuery with the parts of a QueryRequest (a query that is not stored). */
    SYSMLV2REST_EXPORT std::vector<nlohmann::json> executeQuery(const QueryRequest& query, const VersionedData& state);
}
