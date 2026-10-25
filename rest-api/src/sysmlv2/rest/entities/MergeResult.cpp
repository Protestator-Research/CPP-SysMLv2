//
// Created by Moritz Herzog on 11.03.25.
//

#include <nlohmann/json.hpp>
#include <stdexcept>
#include <sysmlv2/rest/entities/MergeResult.h>
#include <sysmlv2/rest/entities/Commit.h>
#include <sysmlv2/rest/entities/DataIdentity.h>
#include <sysmlv2/rest/entities/JSONEntities.h>
#include "RestJson.h"

namespace SysMLv2::REST{

    MergeResult::MergeResult(std::shared_ptr<Commit> mergeCommit, std::vector<std::shared_ptr<DataIdentity>> conflict) {
        MergeCommit = mergeCommit;
        Conflict = conflict;
    }

    MergeResult::MergeResult(const MergeResult& other) : IEntity(), MergeCommit(other.MergeCommit), Conflict(other.Conflict) {
    }

    MergeResult::MergeResult(MergeResult&& other) noexcept :
        IEntity(), MergeCommit(std::move(other.MergeCommit)), Conflict(std::move(other.Conflict)) {
    }

    MergeResult& MergeResult::operator=(const MergeResult& other) {
        MergeCommit = other.MergeCommit;
        Conflict = other.Conflict;
        return *this;
    }

    MergeResult& MergeResult::operator=(MergeResult&& other) noexcept {
        MergeCommit = std::move(other.MergeCommit);
        Conflict = std::move(other.Conflict);
        return *this;
    }

    MergeResult MergeResult::fromJson(const std::string& jsonString) {
        MergeResult result;
        result.deserializeAndPopulate(jsonString);
        return result;
    }

    std::vector<std::shared_ptr<DataIdentity>> MergeResult::conflict() const {
        return Conflict;
    }

    std::shared_ptr<Commit> MergeResult::mergeCommit() const {
        return MergeCommit;
    }

    std::string MergeResult::serializeToJson() {
        if (MergeCommit != nullptr)
            return MergeCommit->serializeToJson();

        nlohmann::json conflicts = nlohmann::json::array();
        for (const auto& identity : Conflict) {
            if (identity != nullptr)
                conflicts.push_back(nlohmann::json::parse(identity->serializeToJson()));
        }
        return conflicts.dump(JSON_INTENT);
    }

    void MergeResult::deserializeAndPopulate(const std::string& jsonString) {
        nlohmann::json json;
        try {
            json = nlohmann::json::parse(jsonString);
        } catch (const nlohmann::json::exception& ex) {
            throw std::invalid_argument(std::string("MergeResult: invalid JSON: ") + ex.what());
        }

        MergeCommit = nullptr;
        Conflict.clear();
        if (json.is_object()) {
            MergeCommit = std::make_shared<Commit>(json.dump());
        } else if (json.is_array()) {
            for (const auto& entry : json) {
                if (!entry.is_object())
                    throw std::invalid_argument("MergeResult: the conflicts must be DataIdentity objects");
                Conflict.push_back(std::make_shared<DataIdentity>(entry.dump()));
            }
        } else {
            throw std::invalid_argument("MergeResult: a Commit object or an array of DataIdentity expected");
        }
    }
} // SysMLv2
