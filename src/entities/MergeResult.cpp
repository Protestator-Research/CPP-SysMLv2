//
// Created by Moritz Herzog on 11.03.25.
//

#include "MergeResult.h"

namespace SysMLv2::Entities{

    MergeResult::MergeResult(Commit *mergeCommit, std::vector<DataIdentity *> conflict) {
        MergeCommit = mergeCommit;
        Conflict = conflict;
    }

    std::vector<DataIdentity *> MergeResult::conflict() {
        return Conflict;
    }

    Commit *MergeResult::mergeCommit() {
        return MergeCommit;
    }
} // SysMLv2