//
// Created by Moritz Herzog on 11.03.25.
//

#include "MergeResult.h"

namespace SysMLv2::Entities{

    MergeResult::MergeResult(std::shared_ptr<Commit> mergeCommit, std::vector<std::shared_ptr<DataIdentity>> conflict) {
        MergeCommit = mergeCommit;
        Conflict = conflict;
    }

    std::vector<std::shared_ptr<DataIdentity>> MergeResult::conflict() {
        return Conflict;
    }

    std::shared_ptr<Commit> MergeResult::mergeCommit() {
        return MergeCommit;
    }
} // SysMLv2