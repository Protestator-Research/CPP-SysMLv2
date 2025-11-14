//
// Created by Moritz Herzog on 27.02.24.
//

#include <nlohmann/json.hpp>
#include <sysmlv2/rest/entities/ProjectUsage.h>
#include <sysmlv2/rest/entities/Commit.h>
#include <sysmlv2/rest/entities/Project.h>
#include <sysmlv2/rest/entities/JSONEntities.h>

namespace SysMLv2 {
    namespace REST {
        ProjectUsage::ProjectUsage(const std::shared_ptr<SysMLv2::REST::Commit>& commit) : Data(){
            _dType="ProjectUsage";
            UsedProjectCommit = commit;
        }

        ProjectUsage::ProjectUsage(std::string jsonString) : Data(jsonString) {
            _dType="ProjectUsage";
            ProjectUsage::deserializeAndPopulate(jsonString);
        }

        std::shared_ptr<Project> ProjectUsage::getUsedProject() const {
            return UsedProjectCommit->getOwningProject();
        }

        std::string ProjectUsage::serializeToJson() {
            nlohmann::json json = nlohmann::json::parse(Data::serializeToJson());
            json[JSON_USED_COMMIT_ENTITY] = UsedProjectCommit->serializeToJson();
            return json.dump(JSON_INTENT);
        }

        void ProjectUsage::deserializeAndPopulate(const std::string &jsonString) {
            Data::deserializeAndPopulate(jsonString);
        }

        void ProjectUsage::setUsedProjectCommit(const std::shared_ptr<Commit>& usedCommit) {
            UsedProjectCommit = usedCommit;
        }

        std::shared_ptr<Commit> ProjectUsage::getUsedProjectCommit() const {
            return UsedProjectCommit;
        }
    } // Entities
} // SysMLv2