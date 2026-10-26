//
// Created by Moritz Herzog on 27.02.24.
//

#include <nlohmann/json.hpp>
#include <boost/uuid/random_generator.hpp>
#include <sysmlv2/rest/entities/ProjectUsage.h>
#include <sysmlv2/rest/entities/Commit.h>
#include <sysmlv2/rest/entities/Project.h>
#include <sysmlv2/rest/entities/JSONEntities.h>
#include "RestJson.h"

namespace SysMLv2 {
    namespace REST {
        namespace {
            /** The "@id" of the JSON text, or a message that names the class. */
            boost::uuids::uuid idOfJson(const std::string& jsonString) {
                const auto json = Internal::parseObject(jsonString, "ProjectUsage");
                try {
                    return Internal::readId(json);
                } catch (const std::exception& ex) {
                    throw std::invalid_argument(std::string("ProjectUsage: ") + ex.what());
                }
            }
        }

        ProjectUsage::ProjectUsage(const std::shared_ptr<SysMLv2::REST::Commit>& commit) : Data(boost::uuids::random_generator()(), "ProjectUsage"){
            UsedProjectCommit = commit;
        }

        ProjectUsage::ProjectUsage(std::string jsonString) : Data(idOfJson(jsonString), "ProjectUsage") {
            ProjectUsage::deserializeAndPopulate(jsonString);
        }

        std::shared_ptr<Project> ProjectUsage::getUsedProject() const {
            if (UsedProjectCommit != nullptr) {
                if (auto project = UsedProjectCommit->getOwningProject())
                    return project;
            }
            return UsedProject;
        }

        std::string ProjectUsage::serializeToJson() {
            nlohmann::json json = nlohmann::json::parse(Data::serializeToJson());
            Internal::writeReference(json, JSON_USED_PROJECT_COMMIT_ENTITY,
                                     UsedProjectCommit != nullptr ? std::optional<boost::uuids::uuid>(UsedProjectCommit->getId()) : std::nullopt);
            if (const auto project = getUsedProject())
                Internal::writeReference(json, JSON_USED_PROJECT_ENTITY, project->getId());
            return json.dump(JSON_INTENT);
        }

        void ProjectUsage::deserializeAndPopulate(const std::string &jsonString) {
            const nlohmann::json json = Internal::parseObject(jsonString, "ProjectUsage");
            try {
                if (const auto id = Internal::readOptionalId(json))
                    _dId = *id;
                _dType = "ProjectUsage";

                UsedProjectCommit.reset();
                UsedProject.reset();

                // "usedCommit" is the field of earlier library versions; they wrote the commit as escaped JSON text.
                const auto* commitEntry = Internal::findWithFallback(json, JSON_USED_PROJECT_COMMIT_ENTITY, JSON_USED_COMMIT_ENTITY);
                if (commitEntry != nullptr && !commitEntry->is_null()) {
                    if (commitEntry->is_string()) {
                        const auto commitJson = Internal::parseObject(commitEntry->get<std::string>(), "usedCommit");
                        UsedProjectCommit = std::make_shared<Commit>(commitJson.dump());
                    } else if (commitEntry->is_object()) {
                        UsedProjectCommit = std::make_shared<Commit>(commitEntry->dump());
                    } else {
                        throw std::invalid_argument("'" + JSON_USED_PROJECT_COMMIT_ENTITY + "' must be a reference or null");
                    }
                }

                if (const auto projectId = Internal::readReference(json, JSON_USED_PROJECT_ENTITY))
                    UsedProject = std::make_shared<Project>(Internal::referenceObjectText(*projectId));
            } catch (const std::exception& ex) {
                throw std::invalid_argument(std::string("ProjectUsage: ") + ex.what());
            }
        }

        void ProjectUsage::setUsedProjectCommit(const std::shared_ptr<Commit>& usedCommit) {
            UsedProjectCommit = usedCommit;
            // usedProject is derived from the commit again.
            UsedProject.reset();
        }

        std::shared_ptr<Commit> ProjectUsage::getUsedProjectCommit() const {
            return UsedProjectCommit;
        }
    } // Entities
} // SysMLv2
