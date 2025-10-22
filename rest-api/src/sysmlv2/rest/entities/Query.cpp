//
// Created by Moritz Herzog on 23.02.24.
//

#include <sysmlv2/rest/entities/Query.h>

namespace SysMLv2::REST {
    Query::Query(std::string jsonString) : Record(jsonString) {

    }

    std::string Query::serializeToJson() {
        return Record::serializeToJson();
    }
}