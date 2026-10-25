//
// Created by Moritz Herzog on 11.03.25.
//

#include <nlohmann/json.hpp>
#include <stdexcept>
#include <sysmlv2/rest/entities/DataDifference.h>
#include <sysmlv2/rest/entities/JSONEntities.h>
#include "RestJson.h"

namespace SysMLv2::REST {
    namespace {
        nlohmann::json versionToJson(const std::shared_ptr<DataVersion>& version) {
            return version != nullptr ? nlohmann::json::parse(version->serializeToJson()) : nlohmann::json(nullptr);
        }

        std::shared_ptr<DataVersion> readVersion(const nlohmann::json& json, const std::string& key) {
            const auto found = json.find(key);
            if (found == json.end() || found->is_null())
                return nullptr;
            if (!found->is_object())
                throw std::invalid_argument("'" + key + "' must be a DataVersion object or null");
            return std::make_shared<DataVersion>(found->dump());
        }
    }

    DataDifference::DataDifference(std::shared_ptr<DataVersion> baseData, std::shared_ptr<DataVersion> compareData) {
        BaseData = std::move(baseData);
        CompareData = std::move(compareData);
    }

    DataDifference::DataDifference(std::nullptr_t) {
    }

    DataDifference::DataDifference(const std::string& jsonString) {
        DataDifference::deserializeAndPopulate(jsonString);
    }

    DataDifference::DataDifference(const DataDifference& other) : IEntity(), BaseData(other.BaseData), CompareData(other.CompareData) {
    }

    DataDifference::DataDifference(DataDifference&& other) noexcept :
        IEntity(), BaseData(std::move(other.BaseData)), CompareData(std::move(other.CompareData)) {
    }

    DataDifference& DataDifference::operator=(const DataDifference& other) {
        BaseData = other.BaseData;
        CompareData = other.CompareData;
        return *this;
    }

    DataDifference& DataDifference::operator=(DataDifference&& other) noexcept {
        BaseData = std::move(other.BaseData);
        CompareData = std::move(other.CompareData);
        return *this;
    }

    std::shared_ptr<DataVersion> DataDifference::baseData() const {
        return BaseData;
    }

    std::shared_ptr<DataVersion> DataDifference::compareData() const {
        return CompareData;
    }

    std::shared_ptr<DataVersion> DataDifference::comparedData() const {
        warnDeprecated("DataDifference::comparedData() const", "DataDifference::compareData() const");
        return CompareData;
    }

    std::string DataDifference::serializeToJson() {
        nlohmann::json json = nlohmann::json::object();
        json[JSON_TYPE_ENTITY] = "DataDifference";
        json[JSON_BASE_DATA_ENTITY] = versionToJson(BaseData);
        json[JSON_COMPARE_DATA_ENTITY] = versionToJson(CompareData);
        return json.dump(JSON_INTENT);
    }

    void DataDifference::deserializeAndPopulate(const std::string& jsonString) {
        const nlohmann::json json = Internal::parseObject(jsonString, "DataDifference");
        try {
            BaseData = readVersion(json, JSON_BASE_DATA_ENTITY);
            CompareData = readVersion(json, JSON_COMPARE_DATA_ENTITY);
        } catch (const std::exception& ex) {
            throw std::invalid_argument(std::string("DataDifference: ") + ex.what());
        }
    }
}
