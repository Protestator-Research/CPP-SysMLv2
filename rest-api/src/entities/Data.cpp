//
// Created by Moritz Herzog on 27.02.24.
//
//---------------------------------------------------------
// Constants, Definitions, Pragmas
//---------------------------------------------------------

//---------------------------------------------------------
// External Classes
//---------------------------------------------------------
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/lexical_cast.hpp>
#include <nlohmann/json.hpp>

//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include "Data.h"

#include <iostream>

#include "JSONEntities.h"

namespace SysMLv2::REST {
    Data::Data() {
        Id = boost::uuids::random_generator()();
    }

    Data::Data(boost::uuids::uuid id) {
        Id = id;
    }

    Data::Data(std::string jsonString) {
        nlohmann::json json = nlohmann::json::parse(jsonString);
        Id = boost::uuids::string_generator()(json[JSON_ID_ENTITY].get<std::string>());
        Type = json[JSON_TYPE_ENTITY].get<std::string>();
    }

    boost::uuids::uuid Data::getId() {
        return Id;
    }

    std::string Data::getType() {
        return Type;
    }

    std::string Data::serializeToJson() {
        std::cout<<"Data::serializeToJson"<<std::endl;
        nlohmann::json json;
        json[JSON_ID_ENTITY] = boost::lexical_cast<std::string>(Id);
        json[JSON_TYPE_ENTITY] = Type;
        return json.dump(JSON_INTENT);
    }

}
