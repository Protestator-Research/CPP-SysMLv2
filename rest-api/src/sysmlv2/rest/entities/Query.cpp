//
// Created by Moritz Herzog on 23.02.24.
//

#include <boost/uuid/random_generator.hpp>
#include <sysmlv2/rest/entities/Query.h>
#include <nlohmann/json.hpp>

#include <sysmlv2/rest/entities/JSONEntities.h>
#include <sysmlv2/rest/entities/Constraint.h>
#include <sysmlv2/rest/entities/Data.h>
#include <sysmlv2/rest/entities/Project.h>
#include "QueryJson.h"

namespace SysMLv2::REST {
    Query::Query(std::string name, std::vector<std::string> select, std::vector<std::shared_ptr<Data>> scope,
        std::vector<std::string> orderBy) : Record(boost::uuids::random_generator()(),std::move(name)){
        Record::Type = "Query";
        Select = std::move(select);
        Scope = std::move(scope);
        OrderBy = std::move(orderBy);
    }

    Query::Query(std::string name, std::vector<std::string> select, std::vector<std::shared_ptr<Data>> scope,
        std::vector<std::string> orderBy, std::shared_ptr<Constraint> where, std::shared_ptr<Project> owningProject) :
        Query(std::move(name), std::move(select), std::move(scope), std::move(orderBy)) {
        Where = std::move(where);
        OwningProject = std::move(owningProject);
    }

    Query::Query(std::string jsonStringOrName) : Record(jsonStringOrName, "Query") {
        Record::Type = "Query";
        if (Internal::looksLikeJson(jsonStringOrName))
            Query::deserializeAndPopulate(jsonStringOrName);
    }

    std::string Query::serializeToJson() {
        nlohmann::json json = nlohmann::json::parse(Record::serializeToJson());
        Internal::writeReference(json, JSON_OWNING_PROJECT,
                                 OwningProject != nullptr ? std::optional<boost::uuids::uuid>(OwningProject->getId()) : std::nullopt);
        Internal::writeQueryFields(json, Select, Scope, OrderBy, Where);
        return json.dump(JSON_INTENT);
    }

    void Query::deserializeAndPopulate(const std::string &jsonString) {
        const nlohmann::json json = Internal::parseObject(jsonString, "Query");
        try {
            const auto type = json.find(JSON_TYPE_ENTITY);
            if (type != json.end() && !type->is_null() && (!type->is_string() || !Internal::equalsIgnoreCase(type->get<std::string>(), "Query")))
                throw std::invalid_argument("'@type' must be \"Query\"");

            auto fields = Internal::readQueryFields(json);
            const auto projectId = Internal::readReference(json, JSON_OWNING_PROJECT);

            Select = std::move(fields.Select);
            Scope = std::move(fields.Scope);
            OrderBy = std::move(fields.OrderBy);
            Where = std::move(fields.Where);
            OwningProject = projectId.has_value() ? std::make_shared<Project>(Internal::referenceObjectText(*projectId)) : nullptr;
        } catch (const std::exception& ex) {
            throw std::invalid_argument(std::string("Query: ") + ex.what());
        }
    }

    std::vector<std::string> Query::getSelect() const {
        return Select;
    }

    void Query::setSelect(std::vector<std::string> select) {
        Select = std::move(select);
    }

    std::vector<std::shared_ptr<Data>> Query::getScope() const {
        return Scope;
    }

    void Query::setScope(std::vector<std::shared_ptr<Data>> scope) {
        Scope = std::move(scope);
    }

    std::vector<std::string> Query::getOrderBy() const {
        return OrderBy;
    }

    void Query::setOrderBy(std::vector<std::string> orderBy) {
        OrderBy = std::move(orderBy);
    }

    std::shared_ptr<Constraint> Query::getWhere() const {
        return Where;
    }

    void Query::setWhere(std::shared_ptr<Constraint> where) {
        Where = std::move(where);
    }

    std::shared_ptr<Project> Query::getOwningProject() const {
        return OwningProject;
    }

    void Query::setOwningProject(std::shared_ptr<Project> owningProject) {
        OwningProject = std::move(owningProject);
    }
}
