//
// Created by Moritz Herzog on 23.02.24.
//

#include "JSONEntities.h"
#include "Branch.h"
#include "Commit.h"
#include <iostream>
#include <nlohmann/json.hpp>

namespace SysMLv2::REST {
    Branch::Branch(std::string jsonStringOrName) : CommitReference(jsonStringOrName) {
        try {
            nlohmann::json parsedJson = nlohmann::json::parse(jsonStringOrName);

            const auto commit = parsedJson[JSON_HEAD_ID];
            if(!commit.empty())
                Head = std::make_shared<Commit>(commit.dump());

        }
        catch (...) {
            Name = jsonStringOrName;
        }
    }

    bool Branch::operator==(Branch &other) {
        return (CommitReference)(*this)==other;
    }

    std::string Branch::serializeToJson() {
        return CommitReference::serializeToJson();
    }

    std::shared_ptr<Commit> Branch::getHead()
    {
        return Head;
    }

    void Branch::setHead(std::shared_ptr<Commit> head) {
        Head = head;
    }
}
