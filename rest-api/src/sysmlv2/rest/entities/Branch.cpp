//
// Created by Moritz Herzog on 23.02.24.
//

#include <sysmlv2/rest/entities/JSONEntities.h>
#include <sysmlv2/rest/entities/Branch.h>
#include <sysmlv2/rest/entities/Commit.h>
#include <iostream>
#include <nlohmann/json.hpp>

namespace SysMLv2::REST {
    Branch::Branch(std::string jsonStringOrName) : CommitReference(jsonStringOrName) {
        try {
            Branch::deserializeAndPopulate(jsonStringOrName);
        }
        catch (...) {
            Name = jsonStringOrName;
        }
    }

    bool Branch::operator==(Branch &other) {
        return (CommitReference)(*this)==other;
    }

    std::string Branch::serializeToJson() {
        nlohmann::json json = nlohmann::json::parse(CommitReference::serializeToJson());
        json[JSON_HEAD_ID] = Head->serializeIdentification();
        return json.dump(JSON_INTENT);
    }

    std::shared_ptr<Commit> Branch::getHead()
    {
        return Head;
    }

    void Branch::setHead(std::shared_ptr<Commit> head) {
        Head = head;
    }

    void Branch::deserializeAndPopulate(const std::string& jsonString)
    {
        nlohmann::json parsedJson = nlohmann::json::parse(jsonString);

        const auto commit = parsedJson[JSON_HEAD_ID];
        if (!commit.empty())
            Head = std::make_shared<Commit>(commit.dump());
    }
}
