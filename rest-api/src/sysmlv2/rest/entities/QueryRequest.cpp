//
// Request to create a Query.
//
#include <sysmlv2/rest/entities/QueryRequest.h>
#include <sysmlv2/rest/entities/Constraint.h>
#include <sysmlv2/rest/entities/Data.h>
#include <sysmlv2/rest/entities/JSONEntities.h>
#include <nlohmann/json.hpp>
#include "QueryJson.h"

namespace SysMLv2::REST {
    QueryRequest::QueryRequest(std::string name, std::vector<std::string> select, std::vector<std::shared_ptr<Data>> scope,
                               std::vector<std::string> orderBy, std::shared_ptr<Constraint> where) :
        Record(boost::uuids::uuid{}, std::move(name)), Select(std::move(select)), Scope(std::move(scope)),
        OrderBy(std::move(orderBy)), Where(std::move(where)) {
        Type = "Query";
    }

    QueryRequest::QueryRequest(const std::string& jsonString) : Record(jsonString, "QueryRequest") {
        Type = "Query";
        if (Internal::looksLikeJson(jsonString))
            QueryRequest::deserializeAndPopulate(jsonString);
        // A request has no id (a name creates a random one in Record).
        Id = boost::uuids::uuid{};
    }

    std::string QueryRequest::serializeToJson() {
        nlohmann::json json = nlohmann::json::parse(Record::serializeToJson());
        Internal::writeQueryFields(json, Select, Scope, OrderBy, Where);
        return json.dump(JSON_INTENT);
    }

    std::vector<std::string> QueryRequest::getSelect() const {
        return Select;
    }

    std::vector<std::shared_ptr<Data>> QueryRequest::getScope() const {
        return Scope;
    }

    std::vector<std::string> QueryRequest::getOrderBy() const {
        return OrderBy;
    }

    std::shared_ptr<Constraint> QueryRequest::getWhere() const {
        return Where;
    }

    void QueryRequest::deserializeAndPopulate(const std::string& jsonString) {
        const nlohmann::json json = Internal::parseObject(jsonString, "QueryRequest");
        try {
            const auto type = json.find(JSON_TYPE_ENTITY);
            if (type != json.end() && !type->is_null() && (!type->is_string() || !Internal::equalsIgnoreCase(type->get<std::string>(), "Query")))
                throw std::invalid_argument("'@type' must be \"Query\"");

            auto fields = Internal::readQueryFields(json);
            Select = std::move(fields.Select);
            Scope = std::move(fields.Scope);
            OrderBy = std::move(fields.OrderBy);
            Where = std::move(fields.Where);
        } catch (const std::exception& ex) {
            throw std::invalid_argument(std::string("QueryRequest: ") + ex.what());
        }
        Type = "Query";
        // A request has no id.
        Id = boost::uuids::uuid{};
    }
}
