//
// Created by Moritz Herzog on 11.03.25.
//

#include "DataDifference.h"

namespace SysMLv2 {
    namespace Entities {
        DataDifference::DataDifference(std::shared_ptr<DataVersion> baseData, std::shared_ptr<DataVersion> comparedData) {
            BaseData = baseData;
            CompareData = comparedData;
        }

        std::shared_ptr<DataVersion> DataDifference::baseData() {
            return BaseData;
        }

        std::shared_ptr<DataVersion> DataDifference::comparedData() {
            return CompareData;
        }
    } // Entities
} // SysMLv2