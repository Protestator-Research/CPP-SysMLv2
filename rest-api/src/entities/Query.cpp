//
// Created by Moritz Herzog on 23.02.24.
//

#include "Query.h"

namespace SysMLv2::Entities {
    Query::Query(std::string jsonString) : Record(jsonString) {

    }

    std::string Query::serializeToJson() {
        return Record::serializeToJson();
    }
}