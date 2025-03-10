//
// Created by Moritz Herzog on 05.09.24.
//
//---------------------------------------------------------
// Constants, Definitions, Pragmas
//---------------------------------------------------------

//---------------------------------------------------------
// External Classes
//---------------------------------------------------------

//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include "Identification.h"
#include "JSONEntities.h"


namespace SysMLv2::Entities {

    Identification::Identification(boost::uuids::uuid id) {
        Id = id;
    }

    Identification::Identification(std::string JSONstring) {
        nlohmann::json json = nlohmann::json::parse(JSONstring);
        if(!json[JSON_ID_ENTITY].is_null())
            Id = boost::uuids::string_generator()(json[JSON_ID_ENTITY].get<std::string>());
        else
            Id = boost::uuids::random_generator()();
    }

    std::string Identification::serializeToJson() {
        nlohmann::json json;
        json[JSON_ID_ENTITY] = boost::lexical_cast<std::string>(Id);
        return json.dump();
    }

    boost::uuids::uuid Identification::getID() const {
        return Id;
    }

    Identification& Identification::operator=(const Identification &other) {
        Id = other.Id;
        return *this;
    }
}


