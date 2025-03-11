//
// Created by Moritz Herzog on 11.03.25.
//

#ifndef CPP_SYSMLV2_LIB_DATADIFFERENCE_H
#define CPP_SYSMLV2_LIB_DATADIFFERENCE_H


#include "DataVersion.h"

namespace SysMLv2 ::Entities {
    class DataVersion;

    class DataDifference {
    public:
        explicit DataDifference(DataVersion *baseData = nullptr, DataVersion* comparedData = nullptr);

        virtual ~DataDifference() = default;

        DataVersion* baseData();
        DataVersion* comparedData();

    private:
        DataVersion* BaseData = nullptr;
        DataVersion* CompareData = nullptr;
    };
} // SysMLv2

#endif //CPP_SYSMLV2_LIB_DATADIFFERENCE_H
