//
// Created by Moritz Herzog on 10.03.25.
//

#ifndef CPP_SYSMLV2_LIB_IQUERYSERVICE_H
#define CPP_SYSMLV2_LIB_IQUERYSERVICE_H

#include <vector>
#include <boost/uuid/uuid.hpp>
#include <string>
#include <memory>

namespace SysMLv2::Entities {
    class Query;
    class Project;
    class Data;
    class Constraint;
    class Commit;
}

namespace SysMLv2::API {
    /**
     *
     */
    class IQueryService {
    public:
        /**
         *
         * @param project
         * @return
         */
        virtual std::vector<std::shared_ptr<SysMLv2::Entities::Query>> getQueries(std::shared_ptr<SysMLv2::Entities::Project> project) = 0;

        /**
         *
         * @param project
         * @param queryId
         * @return
         */
        virtual std::shared_ptr<SysMLv2::Entities::Query> getQueryById(std::shared_ptr<SysMLv2::Entities::Project> project, boost::uuids::uuid queryId) = 0;

        /**
         *
         * @param name
         * @param project
         * @param select
         * @param scope
         * @param where
         * @param orderBy
         * @return
         */
        virtual std::shared_ptr<SysMLv2::Entities::Query> createQuery(std::string name, std::shared_ptr<SysMLv2::Entities::Project> project, std::vector<std::string> select, std::vector<std::shared_ptr<SysMLv2::Entities::Data>> scope, std::shared_ptr<SysMLv2::Entities::Constraint> where, std::vector<std::string> orderBy) = 0;

        /**
         *
         * @param project
         * @param updatedQuery
         * @return
         */
        virtual std::shared_ptr<SysMLv2::Entities::Query> updateQuery(std::shared_ptr<SysMLv2::Entities::Project> project, std::shared_ptr<SysMLv2::Entities::Query> updatedQuery) = 0;

        /**
         *
         * @param project
         * @param queryId
         * @return
         */
        virtual std::shared_ptr<SysMLv2::Entities::Query> deleteQuery(std::shared_ptr<SysMLv2::Entities::Project> project, boost::uuids::uuid queryId) = 0;

        /**
         *
         * @param queryId
         * @param commit
         * @return
         */
        virtual std::vector<std::shared_ptr<SysMLv2::Entities::Data>> executeQueryById(boost::uuids::uuid queryId, std::shared_ptr<SysMLv2::Entities::Commit> commit) = 0;

        /**
         *
         * @param query
         * @param commit
         * @return
         */
        virtual std::vector<std::shared_ptr<SysMLv2::Entities::Data>> executeQuery(std::shared_ptr<SysMLv2::Entities::Query> query, std::shared_ptr<SysMLv2::Entities::Commit> commit) = 0;
    };
}

#endif //CPP_SYSMLV2_LIB_IQUERYSERVICE_H
