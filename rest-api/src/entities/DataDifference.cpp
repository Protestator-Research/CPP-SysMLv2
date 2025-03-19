//
// Created by Moritz Herzog on 11.03.25.
//

#include "DataDifference.h"

namespace SysMLv2 {
    namespace Entities {
        DataDifference::DataDifference(DataVersion *baseData, DataVersion *comparedData) {
            BaseData = baseData;
            CompareData = comparedData;
        }

        DataVersion *DataDifference::baseData() {
            return BaseData;
        }

        DataVersion *DataDifference::comparedData() {
            return CompareData;
        }
    } // Entities
} // SysMLv2