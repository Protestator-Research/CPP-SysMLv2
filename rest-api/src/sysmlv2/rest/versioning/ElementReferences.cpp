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
#include <boost/uuid/string_generator.hpp>
#include <nlohmann/json.hpp>
//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include <kerml/root/elements/Relationship.h>
#include <sysmlv2/rest/entities/Data.h>
#include <sysmlv2/rest/entities/JSONEntities.h>
#include <sysmlv2/rest/versioning/ElementReferences.h>

namespace SysMLv2::REST::Versioning {
    namespace {
        nlohmann::json payloadJson(const std::shared_ptr<Data>& payload) {
            if (payload == nullptr)
                return nlohmann::json();
            return nlohmann::json::parse(payload->serializeToJson(), nullptr, false);
        }

        /** The ids of a reference ({"@id"}) or of an array of references. Entries that are no references are skipped. */
        std::vector<boost::uuids::uuid> referencedIds(const nlohmann::json& json, const char* key) {
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
                    // not an id of an element
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

    RelationshipEnds relationshipEnds(const std::shared_ptr<Data>& payload) {
        RelationshipEnds ends;
        if (std::dynamic_pointer_cast<KerML::Entities::Relationship>(payload) == nullptr)
            return ends;
        const auto json = payloadJson(payload);
        if (!json.is_object())
            return ends;
        ends.isRelationship = true;
        ends.source = referencedIds(json, "source");
        ends.target = referencedIds(json, "target");
        ends.relatedElement = referencedIds(json, "relatedElement");
        ends.ownedRelatedElement = referencedIds(json, "ownedRelatedElement");
        ends.owningRelatedElement = referencedIds(json, "owningRelatedElement");
        return ends;
    }

    bool declaresOwner(const std::shared_ptr<Data>& payload) {
        const auto json = payloadJson(payload);
        if (!json.is_object())
            return false;
        for (const char* key : {"owner", "owningRelationship", "owningRelatedElement"}) {
            if (!referencedIds(json, key).empty())
                return true;
        }
        return false;
    }
}
