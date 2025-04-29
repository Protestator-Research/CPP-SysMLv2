//
// Created by Moritz Herzog on 11.03.25.
//

#include "../sysmlv2rest_global.h"

#ifndef CPP_SYSMLV2_LIB_CHANGETYPE_H
#define CPP_SYSMLV2_LIB_CHANGETYPE_H
namespace SysMLv2::Entities{
    enum SYSMLV2REST_EXPORT ChangeType {
        CREATED,
        UPDATED,
        DELETED
    };
}
#endif //CPP_SYSMLV2_LIB_CHANGETYPE_H
