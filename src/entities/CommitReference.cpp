//
// Created by Moritz Herzog on 23.02.24.
//

#include "CommitReference.h"
#include "Commit.h"

namespace SysMLv2::Entities {
    CommitReference::CommitReference(std::string jsonStringOrName) : Record(jsonStringOrName) { }

    bool CommitReference::operator==(CommitReference &other) {
        if(Record::operator==(other))
        {
            if((*(this->ReferencedCommit))==(*(other.ReferencedCommit))){
                return this->Created==other.Created;
            }
        }
        return false;
    }

    std::string CommitReference::serializeToJson() {
        return Record::serializeToJson();
    }
}