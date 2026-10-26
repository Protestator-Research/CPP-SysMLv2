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
#include <algorithm>
//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include <sysmlv2/rest/entities/JSONEntities.h>
#include <sysmlv2/rest/entities/Record.h>
#include "RestJson.h"


namespace SysMLv2::REST {

    Record::Record(boost::uuids::uuid id, std::string name, std::string description) {
        Id=id;
        Alias = std::list<std::string>();
        Name = name;
        if(!name.empty())
            Alias.emplace_back(name);
        Description = description;
    }

    Record::Record(const std::string& jsonString) : Record(jsonString, "Record") {
    }

    Record::Record(const std::string& jsonString, std::string context) : ErrorContext(std::move(context)) {
        if (Internal::looksLikeJson(jsonString)) {
            // Requests have no "@id", so the id stays nil unless the JSON contains one.
            Record::deserializeAndPopulate(jsonString);
            return;
        }
        Id = boost::uuids::random_generator()();
        Name = jsonString;
        if(!Name.empty())
            Alias.emplace_back(Name);
    }

    // ResourceIdentifier is intentionally not compared.
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

        // Requests have no id.
        if(!Id.is_nil())
            jsonGeneration[JSON_ID_ENTITY] = boost::uuids::to_string(Id);
        jsonGeneration[JSON_TYPE_ENTITY] = Type;

        if(!Name.empty())
            jsonGeneration[JSON_NAME_ENTITY] = Name;

        if(!Alias.empty())
            jsonGeneration[JSON_ALIAS_ENTITY] = Alias;

        if(!Description.empty())
            jsonGeneration[JSON_DESCRIPTION_ENTITY] = Description;

        if(!ResourceIdentifier.empty())
            jsonGeneration[JSON_RESOURCE_IDENTIFIER_ENTITY] = ResourceIdentifier;

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
        const nlohmann::json parsedJson = Internal::parseObject(jsonString, ErrorContext);

        try {
            // Requests do not have an "@id". Then the id is left as it is.
            if (const auto id = Internal::readOptionalId(parsedJson))
                Id = *id;

            if (parsedJson.contains(JSON_TYPE_ENTITY) && !parsedJson[JSON_TYPE_ENTITY].is_null()) {
                if (!parsedJson[JSON_TYPE_ENTITY].is_string())
                    throw std::invalid_argument("'@type' must be a string or null");
                Type = parsedJson[JSON_TYPE_ENTITY].get<std::string>();
            }

            Name = Internal::readOptionalString(parsedJson, JSON_NAME_ENTITY);
            Description = Internal::readOptionalString(parsedJson, JSON_DESCRIPTION_ENTITY);
            ResourceIdentifier = Internal::readOptionalString(parsedJson, JSON_RESOURCE_IDENTIFIER_ENTITY);

            Alias.clear();
            for (auto& entry : Internal::readStringList(parsedJson, JSON_ALIAS_ENTITY)) {
                if (entry.empty()) { // earlier library versions wrote [""]
                    warnDeprecated("JSON field \"alias\" with an empty entry", "no empty aliases");
                    continue;
                }
                Alias.emplace_back(std::move(entry));
            }
        } catch (const std::exception& ex) {
            throw std::invalid_argument(ErrorContext + ": " + ex.what());
        }

        // The human identifier is part of the aliases.
        if (!Name.empty() && std::find(Alias.begin(), Alias.end(), Name) == Alias.end())
            Alias.emplace_front(Name);
    }

    std::string Record::getType() const {
        return Type;
    }

    Record::~Record() {

    }

    void Record::setName(std::string name) {
        const auto oldName = std::find(Alias.begin(), Alias.end(), Name);
        const bool nameAlreadyAlias = !name.empty() && std::find(Alias.begin(), Alias.end(), name) != Alias.end();
        if (!Name.empty() && oldName != Alias.end()) {
            if (name.empty() || nameAlreadyAlias)
                Alias.erase(oldName);
            else
                *oldName = name;
        } else if (!name.empty() && !nameAlreadyAlias) {
            Alias.emplace_front(name);
        }
        Name = std::move(name);
    }

    std::string Record::getResourceIdentifier() const {
        return ResourceIdentifier;
    }

    void Record::setResourceIdentifier(std::string resourceIdentifier) {
        ResourceIdentifier = std::move(resourceIdentifier);
    }

}
