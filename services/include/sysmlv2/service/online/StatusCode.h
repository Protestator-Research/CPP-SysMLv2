//
// Created by Moritz Herzog on 24.04.24.
//

#ifndef DIGITALTWIN_STATUSCODE_H
#define DIGITALTWIN_STATUSCODE_H

#include <sysmlv2/service/sysmlv2service_global.h>

namespace SysMLv2::API {
    enum SYSMLV2SERVICE_EXPORT INTERNAL_STATUS_CODE {
        SUCCESS = 0,
        RE_DO,
        THROW_ERROR
    };
}

#endif //DIGITALTWIN_STATUSCODE_H
