//
// Request to create a Query (body of POST projects/{projectId}/queries).
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
}

namespace SysMLv2::REST {
    /**
     * The request that creates a Query: a Query without "@id" and without "owningProject" (the project is given by the
     * URL). "@type" is "Query". The id is nil and never written; an "@id" or "owningProject" in the read JSON is ignored.
     * @class QueryRequest
     */
    class SYSMLV2REST_EXPORT QueryRequest : public Record {
    public:
        QueryRequest() = delete;

        QueryRequest(std::string name, std::vector<std::string> select, std::vector<std::shared_ptr<Data>> scope,
                     std::vector<std::string> orderBy, std::shared_ptr<Constraint> where = nullptr);

        /**
         * @param jsonString A JSON object of a Query request (the text starts with '{'), or any other text, which is taken
         * as the name of the request (no select, scope, orderBy or where). The old field "order" is read as "orderBy" and warns once.
         * @throws std::invalid_argument If the text is no JSON object, has values of a wrong type or another "@type" than "Query".
         */
        explicit QueryRequest(const std::string& jsonString);

        std::string serializeToJson() override;

        [[nodiscard]] std::vector<std::string> getSelect() const;
        [[nodiscard]] std::vector<std::shared_ptr<Data>> getScope() const;
        [[nodiscard]] std::vector<std::string> getOrderBy() const;
        [[nodiscard]] std::shared_ptr<Constraint> getWhere() const;

        ~QueryRequest() override = default;

    protected:
        void deserializeAndPopulate(const std::string& jsonString) override;

    private:
        std::vector<std::string> Select;
        std::vector<std::shared_ptr<Data>> Scope;
        std::vector<std::string> OrderBy;
        std::shared_ptr<Constraint> Where;
    };
}
