//
// Created by Moritz Herzog on 11.03.25.
//

#ifndef CPP_SYSMLV2_LIB_DATADIFFERENCE_H
#define CPP_SYSMLV2_LIB_DATADIFFERENCE_H

#include <memory>
#include "DataVersion.h"
#include "../sysmlv2rest_global.h"

namespace SysMLv2 ::Entities {
    class DataVersion;

    class SYSMLV2REST_EXPORT DataDifference {
    public:
        explicit DataDifference(std::shared_ptr<DataVersion> baseData = nullptr, std::shared_ptr<DataVersion> comparedData = nullptr);

        virtual ~DataDifference() = default;

        std::shared_ptr<DataVersion> baseData();
        std::shared_ptr<DataVersion> comparedData();

    private:
        std::shared_ptr<DataVersion> BaseData = nullptr;
        std::shared_ptr<DataVersion> CompareData = nullptr;
    };
} // SysMLv2

#endif //CPP_SYSMLV2_LIB_DATADIFFERENCE_H
