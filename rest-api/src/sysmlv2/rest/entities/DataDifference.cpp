//
// Created by Moritz Herzog on 11.03.25.
//

#include <sysmlv2/rest/entities/DataDifference.h>

namespace SysMLv2 {
    namespace REST {
        DataDifference::DataDifference(std::shared_ptr<DataVersion> baseData, std::shared_ptr<DataVersion> comparedData) : Query() {

            //TODO Needs Implementing
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