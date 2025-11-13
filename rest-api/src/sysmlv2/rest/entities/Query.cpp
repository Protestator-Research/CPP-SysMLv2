//
// Created by Moritz Herzog on 23.02.24.
//

#include <boost/uuid/random_generator.hpp>
#include <sysmlv2/rest/entities/Query.h>
#include <nlohmann/json.hpp>

#include <sysmlv2/rest/entities/JSONEntities.h>

namespace SysMLv2::REST {
    Query::Query(std::string name, std::vector<std::string> select, std::vector<std::shared_ptr<Data>> scope,
        std::vector<std::string> order) : Record(boost::uuids::random_generator()(),name){
        Record::Type = "Query";
        Select = select;
        Scope = scope;
        Order = order;
    }

    Query::Query(std::string jsonString) : Record(jsonString) {
        Record::Type = "Query";
        try {
            Query::deserializeAndPopulate(jsonString);
        }catch(...) {        }
    }

    std::string Query::serializeToJson() {
        nlohmann::json json = nlohmann::json::parse(Record::serializeToJson());

        json[JSON_SELECT_ENTITY] = Select;



        json[JSON_ORDER_ENTITY] = Order;

        return json.dump(JSON_INTENT);
    }

    void Query::deserializeAndPopulate(const std::string &jsonString) {
        nlohmann::json json = nlohmann::json::parse(jsonString);
        Select = json[JSON_SELECT_ENTITY];



        Order = json[JSON_ORDER_ENTITY];
    }
}
