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
#include <iostream>
//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include <sysmlv2/rest/entities/Data.h>
#include <sysmlv2/rest/entities/JSONEntities.h>



namespace SysMLv2::REST {
    Data::Data() {
        _dId = boost::uuids::random_generator()();
    }

    Data::Data(boost::uuids::uuid id) {
        _dId = id;
    }

    Data::Data(std::string jsonString) {
        Data::deserializeAndPopulate(jsonString);
    }

    boost::uuids::uuid Data::getId() {
        return _dId;
    }

    std::string Data::getType() {
        return _dType;
    }

    std::string Data::serializeToJson() {
        std::cout<<"Data::serializeToJson"<<std::endl;
        nlohmann::json json;
        json[JSON_ID_ENTITY] = boost::lexical_cast<std::string>(_dId);
        json[JSON_TYPE_ENTITY] = _dType;
        return json.dump(JSON_INTENT);
    }

    void Data::deserializeAndPopulate(const std::string& jsonString)
    {
        nlohmann::json json = nlohmann::json::parse(jsonString);
        _dId = boost::uuids::string_generator()(json[JSON_ID_ENTITY].get<std::string>());
        _dType = json[JSON_TYPE_ENTITY].get<std::string>();
    }
}
