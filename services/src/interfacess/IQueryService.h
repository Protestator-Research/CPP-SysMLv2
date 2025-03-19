//
// Created by Moritz Herzog on 10.03.25.
//

#ifndef CPP_SYSMLV2_LIB_IQUERYSERVICE_H
#define CPP_SYSMLV2_LIB_IQUERYSERVICE_H

#include <vector>
#include <boost/uuid/uuid.hpp>
#include <string>

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
        virtual std::vector<SysMLv2::Entities::Query*> getQueries(SysMLv2::Entities::Project* project) = 0;

        /**
         *
         * @param project
         * @param queryId
         * @return
         */
        virtual SysMLv2::Entities::Query* getQueryById(SysMLv2::Entities::Project* project, boost::uuids::uuid* queryId) = 0;

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
        virtual SysMLv2::Entities::Query* createQuery(std::string name, SysMLv2::Entities::Project* project, std::vector<std::string> select, std::vector<SysMLv2::Entities::Data*> scope, SysMLv2::Entities::Constraint* where, std::vector<std::string> orderBy) = 0;

        /**
         *
         * @param project
         * @param updatedQuery
         * @return
         */
        virtual SysMLv2::Entities::Query* updateQuery(SysMLv2::Entities::Project* project, SysMLv2::Entities::Query* updatedQuery) = 0;

        /**
         *
         * @param project
         * @param queryId
         * @return
         */
        virtual SysMLv2::Entities::Query* deleteQuery(SysMLv2::Entities::Project* project, boost::uuids::uuid queryId) = 0;

        /**
         *
         * @param queryId
         * @param commit
         * @return
         */
        virtual std::vector<SysMLv2::Entities::Data*> executeQueryById(boost::uuids::uuid queryId, SysMLv2::Entities::Commit* commit) = 0;

        /**
         *
         * @param query
         * @param commit
         * @return
         */
        virtual std::vector<SysMLv2::Entities::Data*> executeQuery(SysMLv2::Entities::Query* query, SysMLv2::Entities::Commit* commit) = 0;
    };
}

#endif //CPP_SYSMLV2_LIB_IQUERYSERVICE_H
