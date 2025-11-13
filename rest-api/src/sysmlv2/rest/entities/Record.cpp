//
// Created by Moritz Herzog on 19.02.24.
//
//---------------------------------------------------------
// Constants, Definitions, Pragmas
//---------------------------------------------------------

//---------------------------------------------------------
// External Classes
//---------------------------------------------------------
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <nlohmann/json.hpp>
#include <iostream>
//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include <sysmlv2/rest/entities/JSONEntities.h>
#include <sysmlv2/rest/entities/Record.h>


namespace SysMLv2::REST {

    Record::Record(boost::uuids::uuid id, std::string name, std::string description) {
        Id=id;
        Alias = std::list<std::string>();
        Name = name;
        Alias.emplace_back(name);
        Description = description;
    }

    Record::Record(std::string jsonString) {
        try {
            Record::deserializeAndPopulate(jsonString);
        }
        catch (...) {
            Name = jsonString;
            Id = boost::uuids::random_generator()();
        }
    }

    bool Record::operator==(const Record &other) const {
        if(Id != other.Id)
            return false;
        if(Name != other.Name)
            return false;
        if(Description != other.Description)
            return false;
        if(Alias != other.Alias)
            return false;

        return true;
    }

    std::string Record::getName() const {
        return Name;
    }

    std::list<std::string> Record::getAlias() const {
        return Alias;
    }

    void Record::appendAlias(std::string& alias) {
        Alias.emplace_back(alias);
    }

    std::string Record::getDescription() const {
        return Description;
    }

    void Record::setDescription(std::string& description) {
        Description = description;
    }

    boost::uuids::uuid Record::getId() const {
        return Id;
    }

    std::string Record::serializeToJson() {
        nlohmann::json jsonGeneration;

        jsonGeneration[JSON_ID_ENTITY] = boost::uuids::to_string(Id);
        jsonGeneration[JSON_TYPE_ENTITY] = Type;

        if(!Name.empty())
            jsonGeneration[JSON_NAME_ENTITY] = Name;

        if(!Alias.empty())
            jsonGeneration[JSON_ALIAS_ENTITY] = Alias;

        if(!Description.empty())
            jsonGeneration[JSON_DESCRIPTION_ENTITY] = Description;

        return jsonGeneration.dump(JSON_INTENT);
    }

    std::string Record::serializeIdentification()
    {
        nlohmann::json jsonGeneration;
        jsonGeneration[JSON_ID_ENTITY] = boost::uuids::to_string(Id);
        return jsonGeneration.dump(JSON_INTENT);
    }

    void Record::deserializeAndPopulate(const std::string& jsonString)
    {
        nlohmann::json parsedJson = nlohmann::json::parse(jsonString);

        Id = boost::uuids::string_generator()(parsedJson[JSON_ID_ENTITY].get<std::string>());

        if (parsedJson.contains(JSON_TYPE_ENTITY))
            Type = parsedJson[JSON_TYPE_ENTITY];

        if (parsedJson.contains(JSON_NAME_ENTITY))
            Name = parsedJson[JSON_NAME_ENTITY];

        if (parsedJson.contains(JSON_ALIAS_ENTITY))
            Alias = parsedJson[JSON_ALIAS_ENTITY];

        if (parsedJson.contains(JSON_DESCRIPTION_ENTITY))
            Description = parsedJson[JSON_DESCRIPTION_ENTITY];
    }

    std::string Record::getType() const {
        return Type;
    }

    Record::~Record() {

    }

    void Record::setName(std::string name) {
        Name = name;
    }

}
