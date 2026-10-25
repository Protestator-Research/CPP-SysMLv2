//
// Created by Moritz Herzog on 23.02.24.
//

#include <nlohmann/json.hpp>
#include <stdexcept>
#include <sysmlv2/rest/entities/Tag.h>

#include "sysmlv2/rest/entities/Commit.h"
#include "sysmlv2/rest/entities/JSONEntities.h"
#include "sysmlv2/rest/entities/Project.h"
#include "RestJson.h"

namespace SysMLv2::REST {
    Tag::Tag(std::string jsonStringOrName) : CommitReference(jsonStringOrName, "Tag") {
        Type = "Tag";
        if (Internal::looksLikeJson(jsonStringOrName))
            Tag::deserializeAndPopulate(jsonStringOrName);
    }

    Tag::Tag(std::string name, std::shared_ptr<Project> owningProject, std::shared_ptr<Commit> referencedCommit) :
        CommitReference(name, "Tag") {
        Type = "Tag";
        OwningProject = owningProject;
        ReferencedCommit = referencedCommit;
    }

    std::shared_ptr<Project> Tag::owningProject() const {
        return OwningProject;
    }

    std::shared_ptr<Commit> Tag::taggedCommit() const {
        return ReferencedCommit;
    }

    void Tag::setReferencedCommit(std::shared_ptr<Commit> referencedCommit) {
        warnDeprecated("Tag::setReferencedCommit(commit)", "the Tag constructor with the tagged commit (a Tag is immutable)");
        CommitReference::setReferencedCommit(std::move(referencedCommit));
    }

    std::string Tag::serializeToJson() {
        nlohmann::json json = nlohmann::json::parse(CommitReference::serializeToJson());
        // The tagged commit and the referenced commit are the same.
        Internal::writeReference(json, JSON_TAGGED_COMMIT_ENTITY,
                                 ReferencedCommit != nullptr ? std::optional<boost::uuids::uuid>(ReferencedCommit->getId()) : std::nullopt);
        return json.dump(JSON_INTENT);
    }

    void Tag::deserializeAndPopulate(const std::string &jsonString) {
        const nlohmann::json json = Internal::parseObject(jsonString, "Tag");
        try {
            // If both "taggedCommit" and "referencedCommit" are given, the tagged commit is the one that counts.
            if (const auto taggedId = Internal::readReference(json, JSON_TAGGED_COMMIT_ENTITY))
                ReferencedCommit = std::make_shared<Commit>(Internal::referenceObjectText(*taggedId));
        } catch (const std::exception& ex) {
            throw std::invalid_argument(std::string("Tag: ") + ex.what());
        }
    }
}
