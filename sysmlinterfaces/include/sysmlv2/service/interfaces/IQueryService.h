//
// Created by Moritz Herzog on 10.03.25.
//

#ifndef CPP_SYSMLV2_LIB_IQUERYSERVICE_H
#define CPP_SYSMLV2_LIB_IQUERYSERVICE_H

#include <vector>
#include <boost/uuid/uuid.hpp>
#include <string>
#include <memory>
#include <sysmlv2/interfaces/sysmlv2interfaces_global.h>

namespace SysMLv2::REST {
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
    class SYSMLV2INTERFACE_EXPORT IQueryService {
    public:
        /**
         * 
         * @param project
         * @return
         */
        virtual std::vector<std::shared_ptr<SysMLv2::REST::Query>> getQueries(std::shared_ptr<SysMLv2::REST::Project> project) = 0;

        /**
         *
         * @param project
         * @param queryId
         * @return
         */
        virtual std::shared_ptr<SysMLv2::REST::Query> getQueryById(std::shared_ptr<SysMLv2::REST::Project> project, boost::uuids::uuid queryId) = 0;

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
        virtual std::shared_ptr<SysMLv2::REST::Query> createQuery(std::string name, std::shared_ptr<SysMLv2::REST::Project> project, std::vector<std::string> select, std::vector<std::shared_ptr<SysMLv2::REST::Data>> scope, std::shared_ptr<SysMLv2::REST::Constraint> where, std::vector<std::string> orderBy) = 0;

        /**
         *
         * @param project
         * @param updatedQuery
         * @return
         */
        virtual std::shared_ptr<SysMLv2::REST::Query> updateQuery(std::shared_ptr<SysMLv2::REST::Project> project, std::shared_ptr<SysMLv2::REST::Query> updatedQuery) = 0;

        /**
         *
         * @param project
         * @param queryId
         * @return
         */
        virtual std::shared_ptr<SysMLv2::REST::Query> deleteQuery(std::shared_ptr<SysMLv2::REST::Project> project, boost::uuids::uuid queryId) = 0;

        /**
         *
         * @param queryId
         * @param commit
         * @return
         */
        virtual std::vector<std::shared_ptr<SysMLv2::REST::Data>> executeQueryById(boost::uuids::uuid queryId, std::shared_ptr<SysMLv2::REST::Commit> commit) = 0;

        /**
         *
         * @param query
         * @param commit
         * @return
         */
        virtual std::vector<std::shared_ptr<SysMLv2::REST::Data>> executeQuery(std::shared_ptr<SysMLv2::REST::Query> query, std::shared_ptr<SysMLv2::REST::Commit> commit) = 0;
    };
}

#endif //CPP_SYSMLV2_LIB_IQUERYSERVICE_H
