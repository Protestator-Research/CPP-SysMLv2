//
// Created by Moritz Herzog on 05.01.24.
//

#pragma once

#include <stdexcept>

#include "../sysmlv2service_global.h"

namespace SysMLv2::API::EXCEPTIONS {
    class SYSMLV2SERVICE_EXPORT NotEnoughMemoryError : public std::runtime_error {
    public:
        NotEnoughMemoryError();
        ~NotEnoughMemoryError();
    };
}
