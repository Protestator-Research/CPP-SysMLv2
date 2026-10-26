//
// Created by Moritz Herzog on 11.03.25.
//
#pragma once

#include <cstddef>
#include <memory>
#include <string>
#include <sysmlv2/rest/entities/DataVersion.h>
#include <sysmlv2/rest/entities/IEntity.h>
#include <sysmlv2/rest/sysmlv2rest_global.h>
#include <sysmlv2/rest/entities/Query.h>

namespace SysMLv2::REST {
    class DataVersion;

    /**
     * The difference of the Data between two commits (DataDifference of the SysML v2 API): the DataVersion in the
     * base commit and the one in the compared commit. A missing version (nullptr, JSON null) means that the Data does
     * not exist in this commit.
     */
    class SYSMLV2REST_EXPORT DataDifference : public IEntity {
    public:
        explicit DataDifference(std::shared_ptr<DataVersion> baseData = nullptr, std::shared_ptr<DataVersion> compareData = nullptr);

        /**
         * Both versions are empty. Needed because nullptr would be ambiguous between the versions and the JSON text.
         */
        explicit DataDifference(std::nullptr_t);

        /**
         * Constructor for the JSON parsing.
         * @param jsonString A JSON object {"@type": "DataDifference", "baseData": ..., "compareData": ...}.
         * @throws std::invalid_argument If the text is no valid JSON object or has values of a wrong type.
         */
        explicit DataDifference(const std::string& jsonString);

        DataDifference(const DataDifference& other);
        DataDifference(DataDifference&& other) noexcept;
        DataDifference& operator=(const DataDifference& other);
        DataDifference& operator=(DataDifference&& other) noexcept;

        ~DataDifference() override = default;

        std::shared_ptr<DataVersion> baseData() const;

        /**
         * The DataVersion in the compared commit.
         */
        std::shared_ptr<DataVersion> compareData() const;

        /**
         * The DataVersion in the compared commit.
         * @deprecated Use compareData (the name of the SysML v2 API).
         */
        [[deprecated("Use DataDifference::compareData().")]]
        std::shared_ptr<DataVersion> comparedData() const;

        std::string serializeToJson() override;

    protected:
        void deserializeAndPopulate(const std::string& jsonString) override;

        std::shared_ptr<DataVersion> BaseData = nullptr;
        std::shared_ptr<DataVersion> CompareData = nullptr;
    };
} // SysMLv2
