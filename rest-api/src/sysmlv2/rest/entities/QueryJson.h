//
// JSON of the properties that Query and QueryRequest share (private to the rest-api library, not installed).
//
#pragma once

#include <memory>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include <sysmlv2/rest/entities/Constraint.h>
#include <sysmlv2/rest/entities/Data.h>
#include "RestJson.h"

namespace SysMLv2::REST::Internal {
    struct QueryFields {
        std::vector<std::string> Select;
        std::vector<std::shared_ptr<Data>> Scope;
        std::vector<std::string> OrderBy;
        std::shared_ptr<Constraint> Where;
    };

    /**
     * Reads select, scope, orderBy (or the old "order", which warns) and where.
     * The scope entries are references {"@id": ...}. Entries that hold more than "@id" (the full Data JSON that earlier
     * library versions wrote) are still read and warn once.
     * @throws std::invalid_argument For values of a wrong type.
     */
    inline QueryFields readQueryFields(const nlohmann::json& json) {
        QueryFields fields;
        fields.Select = readStringList(json, JSON_SELECT_ENTITY);
        fields.OrderBy = readStringList(json, JSON_ORDER_BY_ENTITY, JSON_ORDER_ENTITY);

        const auto scope = json.find(JSON_SCOPE_ENTITY);
        if (scope != json.end() && !scope->is_null()) {
            std::vector<nlohmann::json> entries;
            if (scope->is_array())
                entries.assign(scope->begin(), scope->end());
            else
                entries.push_back(*scope);
            for (const auto& entry : entries) {
                const auto id = referenceId(entry, JSON_SCOPE_ENTITY);
                if (!id.has_value())
                    continue;
                if (entry.size() > 1)
                    warnDeprecated("JSON \"scope\" with the full Data JSON of the elements", "references {\"@id\": ...}");
                if (entry.contains(JSON_TYPE_ENTITY) && entry[JSON_TYPE_ENTITY].is_string())
                    fields.Scope.push_back(std::make_shared<Data>(entry.dump()));
                else
                    fields.Scope.push_back(std::make_shared<Data>(*id));
            }
        }

        const auto where = json.find(JSON_WHERE_ENTITY);
        if (where != json.end() && !where->is_null())
            fields.Where = Constraint::fromJsonValue(*where);
        return fields;
    }

    /**
     * Writes select, scope (as references), orderBy and, if set, where.
     */
    inline void writeQueryFields(nlohmann::json& json, const std::vector<std::string>& select,
                                 const std::vector<std::shared_ptr<Data>>& scope, const std::vector<std::string>& orderBy,
                                 const std::shared_ptr<Constraint>& where) {
        json[JSON_SELECT_ENTITY] = select;
        std::vector<boost::uuids::uuid> scopeIds;
        for (const auto& data : scope) {
            if (data != nullptr)
                scopeIds.push_back(data->getId());
        }
        writeReferences(json, JSON_SCOPE_ENTITY, scopeIds);
        json[JSON_ORDER_BY_ENTITY] = orderBy;
        if (where != nullptr)
            json[JSON_WHERE_ENTITY] = nlohmann::json::parse(where->serializeToJson());
    }
}
