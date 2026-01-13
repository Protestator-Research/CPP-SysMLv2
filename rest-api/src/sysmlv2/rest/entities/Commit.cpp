//
// Created by Moritz Herzog on 23.02.24.
//
//---------------------------------------------------------
// Constants, Definitions, Pragmas
//---------------------------------------------------------

//---------------------------------------------------------
// External Classes
//---------------------------------------------------------
#include <sysmlv2/rest/entities/JSONEntities.h>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_serialize.hpp>
#include <boost/uuid/uuid.hpp>

//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include <sysmlv2/rest/entities/Commit.h>

#include <iostream>
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>
#include <nlohmann/detail/meta/std_fs.hpp>
#include <string>
#include <boost/uuid/uuid_io.hpp>

#include <sysmlv2/rest/entities/Project.h>
#include <sysmlv2/rest/entities/DataVersion.h>
#include <sysmlv2/rest/entities/JSONEntities.h>

#include <sysmlv2/rest/serialization/Utilities.h>


namespace SysMLv2::REST{
    Commit::Commit(boost::uuids::uuid id, std::string description, std::shared_ptr<Project> owningProject, std::vector<std::shared_ptr<Commit>> previusCommits) : Record(id,"",description){
        Type = "Commit";
        PreviusCommits = previusCommits;
        OwningProject = owningProject;
        Created = std::chrono::system_clock::now();
    }

    Commit::Commit(std::string description, std::shared_ptr<Project> owningProject, std::vector<std::shared_ptr<Commit>> previusCommits) :
            Record(boost::uuids::random_generator()(), std::string(), description) {
        Type = "Commit";
    	OwningProject = owningProject;
        PreviusCommits = previusCommits;
        Created = std::chrono::system_clock::now();
    }

    Commit::Commit(std::string jsonString) : Record(jsonString) {
        Type = "Commit";
        Commit::deserializeAndPopulate(jsonString);
    }

    void Commit::setChange(std::vector<std::shared_ptr<DataVersion>> change)
    {
        Change = change;
    }

    std::shared_ptr<Project> Commit::getOwningProject() const {
        return OwningProject;
    }

    void Commit::setOwningProject(std::shared_ptr<Project> owningProject)
    {
        OwningProject = owningProject;
    }

    void Commit::addChange(std::shared_ptr<DataVersion> dataVersion) {
        Change.push_back(dataVersion);
    }

    std::vector<std::shared_ptr<DataVersion>> Commit::getDataVersion() {
        return Change;
    }

    std::vector<std::shared_ptr<Commit>> Commit::getPreviusCommits() const {
        return PreviusCommits;
    }

    std::string Commit::serializeToJson() {
        nlohmann::json json = nlohmann::json::parse(Record::serializeToJson());

        std::string jsonElements = "[\r\n";
        for (size_t i = 0; i < Change.size(); i++) {
            jsonElements += Change[i]->serializeToJson();

            if (i != (Change.size()-1))
                jsonElements += ",\r\n";
        }
        jsonElements += "]\r\n";

        json[JSON_CHANGE_ENTITY] = nlohmann::json::parse(jsonElements);
        json[JSON_TIMESTAMP_ENTITY ] = Utilities::toIso8601(Created);

        json[JSON_OWNING_PROJECT] = nlohmann::json::parse(OwningProject->serializeIdentification());

        std::string jsonElementsPrevCommits = "[\r\n";
        for (size_t i = 0; i < PreviusCommits.size(); i++) {
            jsonElementsPrevCommits += PreviusCommits[i]->serializeIdentification();

            if (i != (PreviusCommits.size() - 1))
                jsonElementsPrevCommits += ",\r\n";
        }
        jsonElementsPrevCommits += "]\r\n";

        json[JSON_PREV_COMMITS] = jsonElementsPrevCommits;

        return json.dump(JSON_INTENT);
    }

    std::chrono::system_clock::time_point Commit::getCreated() const {
        return Created;
    }

    void Commit::deserializeAndPopulate(const std::string& jsonString)
    {
        nlohmann::json parsedElement = nlohmann::json::parse(jsonString);
        Description = parsedElement[JSON_DESCRIPTION_ENTITY];

    	std::vector<nlohmann::json> arrayValues = parsedElement[JSON_CHANGE_ENTITY].get<std::vector<nlohmann::json>>();
        for (const auto& value : arrayValues)
        {
            auto changeToBeAdded = std::make_shared<DataVersion>(value.dump());
            Change.push_back(changeToBeAdded);
        }

    	Created = Utilities::fromIso8601(parsedElement[JSON_TIMESTAMP_ENTITY]);
        OwningProject = std::make_shared<Project>(parsedElement[JSON_OWNING_PROJECT]);

        std::vector<nlohmann::json> arrayValuesPrevCommits = parsedElement[JSON_PREV_COMMITS].get<std::vector<nlohmann::json>>();
        for (const auto& value : arrayValuesPrevCommits)
        {
            auto changeToBeAdded = std::make_shared<Commit>(value.dump());
            PreviusCommits.push_back(changeToBeAdded);
        }
    }
}

