//
// Created by Moritz Herzog on 11.03.25.
//

#ifndef CPP_SYSMLV2_LIB_MERGERESULT_H
#define CPP_SYSMLV2_LIB_MERGERESULT_H

#include <vector>
#include <memory>
#include "../sysmlv2rest_global.h"

namespace SysMLv2::REST {
    class Commit;
    class DataIdentity;

    class SYSMLV2REST_EXPORT MergeResult {
    public:
        MergeResult(std::shared_ptr<Commit> mergeCommit = nullptr, std::vector<std::shared_ptr<DataIdentity>> conflict = std::vector<std::shared_ptr<DataIdentity>>());

        virtual ~MergeResult() = default;

        std::vector<std::shared_ptr<DataIdentity>> conflict();
        std::shared_ptr<Commit> mergeCommit();

    private:
        std::shared_ptr<Commit> MergeCommit = nullptr;
        std::vector<std::shared_ptr<DataIdentity>> Conflict;
    };
} // SysMLv2

#endif //CPP_SYSMLV2_LIB_MERGERESULT_H
