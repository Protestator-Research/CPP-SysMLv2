//
// Created by Moritz Herzog on 23.02.24.
//

#include <sysmlv2/rest/entities/Tag.h>

namespace SysMLv2::REST {
    Tag::Tag(std::string jsonStringOrName) : CommitReference(jsonStringOrName) {

    }
}