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
#include <sysmlv2/rest/entities/Identification.h>
#include <sysmlv2/rest/entities/JSONEntities.h>


namespace SysMLv2::REST {

    Identification::Identification(boost::uuids::uuid id) {
        Id = id;
    }

    Identification::Identification(std::string JSONstring) {
        Identification::deserializeAndPopulate(JSONstring);
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

    void Identification::deserializeAndPopulate(const std::string &jsonString) {
        nlohmann::json json = nlohmann::json::parse(jsonString);
        if(!json[JSON_ID_ENTITY].is_null())
            Id = boost::uuids::string_generator()(json[JSON_ID_ENTITY].get<std::string>());
        else
            Id = boost::uuids::random_generator()();
    }
}


