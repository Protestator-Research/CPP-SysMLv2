//
// Created by Moritz Herzog on 23.02.24.
//

#include <nlohmann/json.hpp>
#include <sysmlv2/rest/entities/Tag.h>

#include "sysmlv2/rest/entities/JSONEntities.h"
#include "sysmlv2/rest/entities/Project.h"

namespace SysMLv2::REST {
    Tag::Tag(std::string jsonStringOrName) : CommitReference(jsonStringOrName) {
        try {
            Tag::deserializeAndPopulate(jsonStringOrName);
        }catch (std::exception& e) {}
    }

    Tag::Tag(std::string name, std::shared_ptr<Project> owningProject, std::shared_ptr<Commit> referencedCommit) : CommitReference(name) {
        OwningProject = owningProject;
        ReferencedCommit = referencedCommit;
    }

    std::shared_ptr<Project> Tag::owningProject() const {
        return OwningProject;
    }

    void Tag::setOwningProject(std::shared_ptr<Project> owningProject) {
        OwningProject = owningProject;
    }

    std::string Tag::serializeToJson() {
        nlohmann::json json = nlohmann::json::parse(CommitReference::serializeToJson());

        json[JSON_OWNING_PROJECT] = nlohmann::json::parse(OwningProject->serializeIdentification());

        return json.dump(JSON_INTENT);
    }

    void Tag::deserializeAndPopulate(const std::string &jsonString) {
        nlohmann::json json = nlohmann::json::parse(jsonString);
        if (json.contains(JSON_OWNING_PROJECT)) {
            OwningProject = std::make_shared<Project>(json[JSON_OWNING_PROJECT].dump());
        }
    }
}
