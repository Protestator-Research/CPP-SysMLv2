//
// Created by Moritz Herzog on 11.03.25.
//

#ifndef CPP_SYSMLV2_LIB_MERGERESULT_H
#define CPP_SYSMLV2_LIB_MERGERESULT_H

#include <vector>

namespace SysMLv2::Entities {
    class Commit;
    class DataIdentity;

    class MergeResult {
    public:
        MergeResult(Commit* mergeCommit = nullptr, std::vector<DataIdentity*> conflict = std::vector<DataIdentity*>());

        virtual ~MergeResult() = default;

        std::vector<DataIdentity*> conflict();
        Commit* mergeCommit();

    private:
        Commit* MergeCommit = nullptr;
        std::vector<DataIdentity*> Conflict;
    };
} // SysMLv2

#endif //CPP_SYSMLV2_LIB_MERGERESULT_H
