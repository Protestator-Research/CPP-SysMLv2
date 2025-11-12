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
#include <sysmlv2/rest/entities/Data.h>

#include <iostream>


namespace SysMLv2::REST {
    Data::Data() {
        Id = boost::uuids::random_generator()();
    }

    Data::Data(boost::uuids::uuid id) {
        Id = id;
    }

    Data::Data(std::string jsonString) {
        Data::deserializeAndPopulate(jsonString);
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
        json["@id"] = boost::lexical_cast<std::string>(Id);
        json["@type"] = Type;
        return json.dump(JSON_INTENT);
    }

    void Data::deserializeAndPopulate(const std::string& jsonString)
    {
        nlohmann::json json = nlohmann::json::parse(jsonString);
        Id = boost::uuids::string_generator()(json["@id"].get<std::string>());
        Type = json["@type"].get<std::string>();
    }
}
