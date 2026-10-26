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

#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>
#include <nlohmann/detail/meta/std_fs.hpp>
#include <string>
#include <boost/uuid/uuid_io.hpp>

#include <sysmlv2/rest/entities/Project.h>
#include <sysmlv2/rest/entities/DataVersion.h>
#include <sysmlv2/rest/entities/JSONEntities.h>

#include <sysmlv2/rest/serialization/Utilities.h>
#include "RestJson.h"


namespace SysMLv2::REST{
    Commit::Commit(boost::uuids::uuid id, std::string description, std::shared_ptr<Project> owningProject, std::vector<std::shared_ptr<Commit>> previusCommits) : Record(id,"",description){
        Type = "Commit";
        PreviousCommits = previusCommits;
        OwningProject = owningProject;
        Created = std::chrono::system_clock::now();
    }

    Commit::Commit(std::string description, std::shared_ptr<Project> owningProject, std::vector<std::shared_ptr<Commit>> previusCommits) :
            Record(boost::uuids::random_generator()(), std::string(), description) {
        Type = "Commit";
    	OwningProject = owningProject;
        PreviousCommits = previusCommits;
        Created = std::chrono::system_clock::now();
    }

    Commit::Commit(std::string jsonString) : Record(jsonString, "Commit") {
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

    std::vector<std::shared_ptr<DataVersion>> Commit::getChange() const {
        return Change;
    }

    std::vector<std::shared_ptr<DataVersion>> Commit::getDataVersion() {
        warnDeprecated("Commit::getDataVersion()", "Commit::getChange()");
        return Change;
    }

    std::vector<std::shared_ptr<Commit>> Commit::getPreviousCommits() const {
        return PreviousCommits;
    }

    std::vector<std::shared_ptr<Commit>> Commit::getPreviusCommits() const {
        warnDeprecated("Commit::getPreviusCommits()", "Commit::getPreviousCommits()");
        return PreviousCommits;
    }

    std::string Commit::serializeToJson() {
        nlohmann::json json = nlohmann::json::parse(Record::serializeToJson());

        nlohmann::json changes = nlohmann::json::array();
        for (const auto& change : Change) {
            if (change != nullptr)
                changes.push_back(nlohmann::json::parse(change->serializeToJson()));
        }
        json[JSON_CHANGE_ENTITY] = changes;

        Internal::writeOptionalTimestamp(json, JSON_CREATED_ENTITY, Created);

        // A commit without project writes null.
        Internal::writeReference(json, JSON_OWNING_PROJECT,
                                 OwningProject != nullptr ? std::optional<boost::uuids::uuid>(OwningProject->getId()) : std::nullopt);

        std::vector<boost::uuids::uuid> previousIds;
        for (const auto& previous : PreviousCommits) {
            if (previous != nullptr)
                previousIds.push_back(previous->getId());
        }
        Internal::writeReferences(json, JSON_PREVIOUS_COMMITS_ENTITY, previousIds);

        return json.dump(JSON_INTENT);
    }

    std::chrono::system_clock::time_point Commit::getCreated() const {
        return Created.value_or(std::chrono::system_clock::time_point{});
    }

    void Commit::setCreated(std::chrono::system_clock::time_point created) {
        Created = created;
    }

    void Commit::deserializeAndPopulate(const std::string& jsonString)
    {
        const nlohmann::json parsedElement = Internal::parseObject(jsonString, "Commit");
        try {
            Change.clear();
            const auto changeEntry = parsedElement.find(JSON_CHANGE_ENTITY);
            if (changeEntry != parsedElement.end() && !changeEntry->is_null()) {
                if (!changeEntry->is_array())
                    throw std::invalid_argument("'" + JSON_CHANGE_ENTITY + "' must be an array or null");
                // Null entries are skipped, like in the other arrays.
                for (const auto& value : *changeEntry)
                    if (!value.is_null())
                        Change.push_back(std::make_shared<DataVersion>(value.dump()));
            }

            // "timestamp" is the name of earlier library versions and of Annex B of the specification.
            Created = Internal::readOptionalTimestamp(parsedElement, JSON_CREATED_ENTITY, JSON_TIMESTAMP_ENTITY);

            if (const auto projectId = Internal::readReference(parsedElement, JSON_OWNING_PROJECT))
                OwningProject = std::make_shared<Project>(Internal::referenceObjectText(*projectId));

            // "previousCommit" (array, single object or null) is the name of earlier library versions.
            PreviousCommits.clear();
            for (const auto& id : Internal::readReferences(parsedElement, JSON_PREVIOUS_COMMITS_ENTITY, JSON_PREV_COMMITS))
                PreviousCommits.push_back(std::make_shared<Commit>(Internal::referenceObjectText(id)));
        } catch (const std::exception& ex) {
            throw std::invalid_argument(std::string("Commit: ") + ex.what());
        }
    }
}
