//
// Created by Moritz Herzog on 23.02.24.
//
//---------------------------------------------------------
// Constants, Definitions, Pragmas
//---------------------------------------------------------

//---------------------------------------------------------
// External Classes
//---------------------------------------------------------
#include <boost/uuid/uuid_generators.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_serialize.hpp>
#include <boost/uuid/uuid.hpp>

//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include "Commit.h"

#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>
#include <nlohmann/detail/meta/std_fs.hpp>
#include <string>
#include <boost/uuid/uuid_io.hpp>

#include "Project.h"
#include "DataVersion.h"
#include "JSONEntities.h"


namespace SysMLv2::Entities{
    Commit::Commit(boost::uuids::uuid id, std::string name, std::string description, std::shared_ptr<Project> owningProject, std::vector<std::shared_ptr<Commit>> previusCommits) : Record(id,name,description){
        Type = "Commit";
        PreviusCommits = previusCommits;
        OwningProject = owningProject;
    }

    Commit::Commit(std::string name, std::string description, std::shared_ptr<Project> owningProject, std::vector<std::shared_ptr<Commit>> previusCommits) :
            Record(boost::uuids::random_generator()(), name, description){
        Type = "Commit";
    	OwningProject = owningProject;
        PreviusCommits = previusCommits;
    }

    Commit::Commit(std::string jsonString) : Record(jsonString) {
        Type = "Commit";
    }

    Commit::~Commit() {

    }

    void Commit::setChange(std::vector<std::shared_ptr<DataVersion>> change)
    {
        Change = change;
    }

    std::shared_ptr<Project> Commit::getOwningProject() const {
        return OwningProject;
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

        json.erase(JSON_ID_ENTITY);
        std::string jsonElements = "[\r\n";
        for (size_t i = 0; i < Change.size(); i++) {
            jsonElements += Change[i]->serializeToJson();

            if (i != (Change.size()-1))
                jsonElements += ",\r\n";
        }
        jsonElements += "]\r\n";

        json[JSON_CHANGE_ENTITY] = nlohmann::json::parse(jsonElements);
        return json.dump(JSON_INTENT);
    }

}

