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


namespace SysMLv2::REST{
    Commit::Commit(boost::uuids::uuid id, std::string name, std::string description, std::shared_ptr<Project> owningProject, std::vector<std::shared_ptr<Commit>> previusCommits) : Record(id,name,description){
        Type = "Commit";
        PreviusCommits = previusCommits;
        OwningProject = owningProject;
        Created = std::chrono::system_clock::now();
    }

    Commit::Commit(std::string name, std::string description, std::shared_ptr<Project> owningProject, std::vector<std::shared_ptr<Commit>> previusCommits) :
            Record(boost::uuids::random_generator()(), name, description){
        Type = "Commit";
    	OwningProject = owningProject;
        PreviusCommits = previusCommits;
        Created = std::chrono::system_clock::now();
    }

    Commit::Commit(std::string jsonString) : Record(jsonString) {
        Type = "Commit";
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
        std::cout << "Record already done." << std::endl;
        json.erase(JSON_ID_ENTITY);
        std::cout << "ID Erased" << std::endl;
        std::string jsonElements = "[\r\n";
        for (size_t i = 0; i < Change.size(); i++) {
            std::cout << "Adding JSON ELEMENT "<< i << std::endl;
            jsonElements += Change[i]->serializeToJson();
            std::cout << "\r" << jsonElements << std::endl;

            if (i != (Change.size()-1))
                jsonElements += ",\r\n";
        }
        jsonElements += "]\r\n";

        json[JSON_CHANGE_ENTITY] = nlohmann::json::parse(jsonElements);
        std::cout << "JSON elements added" << std::endl;
        std::string jsonString = json.dump(JSON_INTENT);
        std::cout << "Json String created." << std::endl;
        return jsonString;
    }

    std::chrono::system_clock::time_point Commit::getCreated() const {
        return Created;
    }
}

