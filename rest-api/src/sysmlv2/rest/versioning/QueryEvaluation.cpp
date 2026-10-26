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
// External Classes
//---------------------------------------------------------
#include <algorithm>
#include <cmath>
#include <deque>
#include <set>
#include <boost/uuid/string_generator.hpp>
#include <boost/uuid/uuid_io.hpp>
//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include <kerml/root/elements/Element.h>
#include <kerml/root/elements/Relationship.h>
#include <sysmlv2/rest/entities/Constraint.h>
#include <sysmlv2/rest/entities/Data.h>
#include <sysmlv2/rest/entities/DataVersion.h>
#include <sysmlv2/rest/entities/JSONEntities.h>
#include <sysmlv2/rest/entities/Query.h>
#include <sysmlv2/rest/entities/QueryRequest.h>
#include <sysmlv2/rest/versioning/QueryEvaluation.h>

namespace SysMLv2::REST::Versioning {
    namespace {
        /** The values a property has in the JSON: a path with dots is followed, arrays are flattened. Missing gives none. */
        void collectValues(const nlohmann::json& json, const std::string& path, std::vector<nlohmann::json>& values) {
            if (json.is_array()) {
                for (const auto& entry : json)
                    collectValues(entry, path, values);
                return;
            }
            if (!json.is_object())
                return;
            const auto exact = json.find(path);
            if (exact != json.end()) {
                if (exact->is_array()) {
                    for (const auto& entry : *exact)
                        values.push_back(entry);
                } else {
                    values.push_back(*exact);
                }
                return;
            }
            const auto dot = path.find('.');
            if (dot == std::string::npos)
                return;
            const auto head = json.find(path.substr(0, dot));
            if (head != json.end())
                collectValues(*head, path.substr(dot + 1), values);
        }

        /** A reference {"@id": X} is its id, everything else stays as it is. */
        nlohmann::json plain(const nlohmann::json& value) {
            if (value.is_object()) {
                const auto id = value.find(JSON_ID_ENTITY);
                if (id != value.end())
                    return *id;
            }
            return value;
        }

        bool equals(const nlohmann::json& property, const nlohmann::json& value) {
            if (property.is_number() && value.is_number())
                return property.get<double>() == value.get<double>();
            return property == value;
        }

        /** Orders two values of the same kind (numbers, strings). Returns false if they can not be compared. */
        bool compare(const nlohmann::json& property, const nlohmann::json& value, int& result) {
            if (property.is_number() && value.is_number()) {
                const double left = property.get<double>();
                const double right = value.get<double>();
                result = left < right ? -1 : (left > right ? 1 : 0);
                return true;
            }
            if (property.is_string() && value.is_string()) {
                const int order = property.get<std::string>().compare(value.get<std::string>());
                result = order < 0 ? -1 : (order > 0 ? 1 : 0);
                return true;
            }
            return false;
        }

        bool isInstanceOf(const std::string& type, const nlohmann::json& payload, const std::shared_ptr<Data>& data) {
            const auto own = payload.is_object() && payload.contains(JSON_TYPE_ENTITY) && payload[JSON_TYPE_ENTITY].is_string()
                ? payload[JSON_TYPE_ENTITY].get<std::string>() : std::string();
            if (own == type || type == "Data")
                return true;
            if (data == nullptr)
                return false;
            if (type == "Element")
                return std::dynamic_pointer_cast<KerML::Entities::Element>(data) != nullptr;
            if (type == "Relationship")
                return std::dynamic_pointer_cast<KerML::Entities::Relationship>(data) != nullptr;
            return false;
        }

        bool satisfiesPrimitive(const PrimitiveConstraint& constraint, const nlohmann::json& payload, const std::shared_ptr<Data>& data) {
            std::vector<nlohmann::json> found;
            collectValues(payload, constraint.getProperty(), found);
            std::vector<nlohmann::json> properties;
            for (const auto& value : found)
                properties.push_back(plain(value));
            // a missing property is null
            if (properties.empty())
                properties.push_back(nullptr);

            const auto op = constraint.getOperator();
            bool result = false;
            // The values of a constraint are alternatives: one matching value is enough, like one matching entry of an array.
            for (const auto& property : properties) {
                for (const auto& value : constraint.getValues()) {
                    int order = 0;
                    switch (op) {
                        case Operator::Equal:
                        case Operator::In:
                            result = equals(property, value);
                            break;
                        case Operator::Less:
                            result = compare(property, value, order) && order < 0;
                            break;
                        case Operator::LessOrEqual:
                            result = compare(property, value, order) && order <= 0;
                            break;
                        case Operator::Greater:
                            result = compare(property, value, order) && order > 0;
                            break;
                        case Operator::GreaterOrEqual:
                            result = compare(property, value, order) && order >= 0;
                            break;
                        case Operator::InstanceOf:
                            result = value.is_string() && (constraint.getProperty() == JSON_TYPE_ENTITY
                                ? isInstanceOf(value.get<std::string>(), payload, data) : equals(property, value));
                            break;
                    }
                    if (result)
                        break;
                }
                if (result)
                    break;
            }
            return constraint.isInverse() ? !result : result;
        }

        int rank(const nlohmann::json& value) {
            if (value.is_null()) return 0;
            if (value.is_boolean()) return 1;
            if (value.is_number()) return 2;
            if (value.is_string()) return 3;
            return 4;
        }

        /** Missing and null first, then booleans, numbers, strings; other values by their text. */
        int compareForSort(const nlohmann::json& left, const nlohmann::json& right) {
            const int leftRank = rank(left);
            const int rightRank = rank(right);
            if (leftRank != rightRank)
                return leftRank < rightRank ? -1 : 1;
            switch (leftRank) {
                case 0: return 0;
                case 1: return static_cast<int>(left.get<bool>()) - static_cast<int>(right.get<bool>());
                case 2: {
                    const double a = left.get<double>();
                    const double b = right.get<double>();
                    return a < b ? -1 : (a > b ? 1 : 0);
                }
                case 3: {
                    const int order = left.get<std::string>().compare(right.get<std::string>());
                    return order < 0 ? -1 : (order > 0 ? 1 : 0);
                }
                default: {
                    const int order = left.dump().compare(right.dump());
                    return order < 0 ? -1 : (order > 0 ? 1 : 0);
                }
            }
        }

        nlohmann::json sortKey(const nlohmann::json& payload, const std::string& property) {
            std::vector<nlohmann::json> values;
            collectValues(payload, property, values);
            return values.empty() ? nlohmann::json(nullptr) : plain(values.front());
        }

        std::vector<boost::uuids::uuid> idsOf(const nlohmann::json& json, const char* key) {
            std::vector<boost::uuids::uuid> ids;
            const auto entry = json.find(key);
            if (entry == json.end())
                return ids;
            const auto add = [&ids](const nlohmann::json& reference) {
                if (!reference.is_object())
                    return;
                const auto id = reference.find(JSON_ID_ENTITY);
                if (id == reference.end() || !id->is_string())
                    return;
                try {
                    ids.push_back(boost::uuids::string_generator()(id->get<std::string>()));
                } catch (const std::exception&) {
                    // not an id
                }
            };
            if (entry->is_array()) {
                for (const auto& reference : *entry)
                    add(reference);
            } else {
                add(*entry);
            }
            return ids;
        }
    }

    bool satisfies(const Constraint& constraint, const nlohmann::json& payload, const std::shared_ptr<Data>& payloadData) {
        if (const auto* primitive = dynamic_cast<const PrimitiveConstraint*>(&constraint))
            return satisfiesPrimitive(*primitive, payload, payloadData);
        if (const auto* composite = dynamic_cast<const CompositeConstraint*>(&constraint)) {
            const auto children = composite->getConstraints();
            if (composite->getOperator() == JoinOperator::And)
                return std::all_of(children.begin(), children.end(), [&](const std::shared_ptr<Constraint>& child) {
                    return satisfies(*child, payload, payloadData);
                });
            return std::any_of(children.begin(), children.end(), [&](const std::shared_ptr<Constraint>& child) {
                return satisfies(*child, payload, payloadData);
            });
        }
        return false;
    }

    std::vector<boost::uuids::uuid> scopeClosure(const std::vector<boost::uuids::uuid>& scope, const VersionedData& state) {
        // The owned elements per owner, from both directions of the ownership.
        std::map<boost::uuids::uuid, std::set<boost::uuids::uuid>> owned;
        for (const auto& [identity, version] : state) {
            const auto payload = version->getPayload();
            if (payload == nullptr)
                continue;
            const auto json = nlohmann::json::parse(payload->serializeToJson(), nullptr, false);
            if (!json.is_object())
                continue;
            for (const char* key : {"ownedElement", "ownedRelationship", "ownedRelatedElement"}) {
                for (const auto& child : idsOf(json, key))
                    owned[identity].insert(child);
            }
            for (const char* key : {"owner", "owningRelationship", "owningRelatedElement"}) {
                for (const auto& parent : idsOf(json, key))
                    owned[parent].insert(identity);
            }
        }

        std::set<boost::uuids::uuid> closure;
        std::deque<boost::uuids::uuid> pending(scope.begin(), scope.end());
        while (!pending.empty()) {
            const auto current = pending.front();
            pending.pop_front();
            if (state.find(current) == state.end() || !closure.insert(current).second)
                continue;
            const auto children = owned.find(current);
            if (children != owned.end())
                pending.insert(pending.end(), children->second.begin(), children->second.end());
        }
        return std::vector<boost::uuids::uuid>(closure.begin(), closure.end());
    }

    std::vector<nlohmann::json> executeQuery(const std::vector<std::string>& select, const std::vector<boost::uuids::uuid>& scope,
                                             const std::vector<std::string>& orderBy, const std::shared_ptr<Constraint>& where,
                                             const VersionedData& state) {
        std::set<boost::uuids::uuid> inScope;
        if (!scope.empty()) {
            const auto closure = scopeClosure(scope, state);
            inScope.insert(closure.begin(), closure.end());
        }

        std::vector<nlohmann::json> rows;
        for (const auto& [identity, version] : state) {
            const auto payload = version->getPayload();
            if (payload == nullptr || (!scope.empty() && inScope.find(identity) == inScope.end()))
                continue;
            auto json = nlohmann::json::parse(payload->serializeToJson(), nullptr, false);
            if (!json.is_object())
                continue;
            if (where != nullptr && !satisfies(*where, json, payload))
                continue;
            rows.push_back(std::move(json));
        }

        if (!orderBy.empty()) {
            std::stable_sort(rows.begin(), rows.end(), [&orderBy](const nlohmann::json& left, const nlohmann::json& right) {
                for (const auto& property : orderBy) {
                    const int order = compareForSort(sortKey(left, property), sortKey(right, property));
                    if (order != 0)
                        return order < 0;
                }
                return false;
            });
        }

        if (!select.empty()) {
            for (auto& row : rows) {
                nlohmann::json reduced = nlohmann::json::object();
                for (const auto& [key, value] : row.items()) {
                    if (key == JSON_ID_ENTITY || key == JSON_TYPE_ENTITY || std::find(select.begin(), select.end(), key) != select.end())
                        reduced[key] = value;
                }
                row = std::move(reduced);
            }
        }
        return rows;
    }

    namespace {
        std::vector<boost::uuids::uuid> scopeIds(const std::vector<std::shared_ptr<Data>>& scope) {
            std::vector<boost::uuids::uuid> ids;
            for (const auto& data : scope) {
                if (data != nullptr)
                    ids.push_back(data->getId());
            }
            return ids;
        }
    }

    std::vector<nlohmann::json> executeQuery(const Query& query, const VersionedData& state) {
        return executeQuery(query.getSelect(), scopeIds(query.getScope()), query.getOrderBy(), query.getWhere(), state);
    }

    std::vector<nlohmann::json> executeQuery(const QueryRequest& query, const VersionedData& state) {
        return executeQuery(query.getSelect(), scopeIds(query.getScope()), query.getOrderBy(), query.getWhere(), state);
    }
}
