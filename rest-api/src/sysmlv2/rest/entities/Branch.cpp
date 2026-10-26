//
// Created by Moritz Herzog on 23.02.24.
//

#include <sysmlv2/rest/entities/JSONEntities.h>
#include <sysmlv2/rest/entities/Branch.h>
#include <sysmlv2/rest/entities/Commit.h>
#include <optional>
#include <stdexcept>
#include "RestJson.h"
#include <nlohmann/json.hpp>

namespace SysMLv2::REST {
    Branch::Branch(std::string jsonStringOrName) : CommitReference(jsonStringOrName, "Branch")
    {
        Type = "Branch";
        if (Internal::looksLikeJson(jsonStringOrName))
            Branch::deserializeAndPopulate(jsonStringOrName);
    }

    bool Branch::operator==(Branch &other) {
        return CommitReference::operator==(other);
    }

    std::string Branch::serializeToJson() {
        nlohmann::json json = nlohmann::json::parse(CommitReference::serializeToJson());
        // A branch without head writes null.
        Internal::writeReference(json, JSON_HEAD_ID, Head != nullptr ? std::optional<boost::uuids::uuid>(Head->getId()) : std::nullopt);
        return json.dump(JSON_INTENT);
    }

    std::shared_ptr<Commit> Branch::getHead()
    {
        return Head;
    }

    void Branch::setHead(std::shared_ptr<Commit> head) {
        Head = head;
        ReferencedCommit = head;
    }

    void Branch::setReferencedCommit(std::shared_ptr<Commit> referencedCommit) {
        warnDeprecated("Branch::setReferencedCommit(commit)", "Branch::setHead(commit)");
        setHead(std::move(referencedCommit));
    }

    void Branch::deserializeAndPopulate(const std::string& jsonString)
    {
        const nlohmann::json parsedJson = Internal::parseObject(jsonString, "Branch");
        try {
            // "head" and "referencedCommit" describe the same commit. CommitReference has read the latter.
            if (const auto headId = Internal::readReference(parsedJson, JSON_HEAD_ID))
                Head = std::make_shared<Commit>(Internal::referenceObjectText(*headId));
            else
                Head = ReferencedCommit;
        } catch (const std::exception& ex) {
            throw std::invalid_argument(std::string("Branch: ") + ex.what());
        }
        // If both are given, the head is the one that counts.
        ReferencedCommit = Head;
    }
}
