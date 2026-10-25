//
// Created by Moritz Herzog on 23.02.24.
//
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
//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include <sysmlv2/rest/entities/Record.h>
#include <sysmlv2/rest/sysmlv2rest_global.h>
//---------------------------------------------------------
// Forwarding
//---------------------------------------------------------

namespace SysMLv2::REST {
    class Data;
    class Constraint;
    class Project;
}

namespace SysMLv2::REST {
    /**
     * A Query of the SysML v2 API: a Record with select, scope, where, orderBy and the owning project. An empty scope
     * means the owning project. The scope is written as references {"@id": ...}.
     * @class Query
     * @author Moritz Herzog
     * @version 1.1
     */
    class SYSMLV2REST_EXPORT Query : public Record {
    public:
        Query() = delete;

        /**
         * @param name Name of the query.
         * @param select The properties that are returned.
         * @param scope The Data that is searched.
         * @param orderBy The properties that define the order of the result (the parameter was called "order" in earlier
         * versions, the meaning is the same).
         */
        Query(std::string name,std::vector<std::string> select, std::vector<std::shared_ptr<Data>> scope, std::vector<std::string> orderBy);

        /**
         * @param name Name of the query.
         * @param select The properties that are returned.
         * @param scope The Data that is searched.
         * @param orderBy The properties that define the order of the result.
         * @param where The constraint of the query, nullptr for none.
         * @param owningProject The project that owns the query, nullptr for none.
         */
        Query(std::string name, std::vector<std::string> select, std::vector<std::shared_ptr<Data>> scope,
              std::vector<std::string> orderBy, std::shared_ptr<Constraint> where, std::shared_ptr<Project> owningProject);

        /**
         * @param jsonStringOrName A JSON object (the text starts with '{') or the name of the query. The JSON field "order"
         * of earlier library versions is read as "orderBy" and warns once.
         * @throws std::invalid_argument If the text looks like JSON but is malformed or has values of a wrong type.
         */
        explicit Query(std::string jsonStringOrName);

        std::string serializeToJson() override;

        [[nodiscard]] std::vector<std::string> getSelect() const;
        void setSelect(std::vector<std::string> select);

        [[nodiscard]] std::vector<std::shared_ptr<Data>> getScope() const;
        void setScope(std::vector<std::shared_ptr<Data>> scope);

        [[nodiscard]] std::vector<std::string> getOrderBy() const;
        void setOrderBy(std::vector<std::string> orderBy);

        /** The constraint of the query or nullptr. */
        [[nodiscard]] std::shared_ptr<Constraint> getWhere() const;
        void setWhere(std::shared_ptr<Constraint> where);

        /** The owning project (identification only if read from JSON) or nullptr. */
        [[nodiscard]] std::shared_ptr<Project> getOwningProject() const;
        void setOwningProject(std::shared_ptr<Project> owningProject);

        ~Query() override = default;

    protected:
        void deserializeAndPopulate(const std::string &jsonString) override;

    private:
        std::vector<std::string> Select;
        std::vector<std::shared_ptr<Data>> Scope;
        std::vector<std::string> OrderBy;
        std::shared_ptr<Constraint> Where;
        std::shared_ptr<Project> OwningProject;
    };
}
