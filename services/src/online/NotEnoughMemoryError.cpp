//
// Created by Moritz Herzog on 05.01.24.
//

#include "NotEnoughMemoryError.h"

namespace SysMLv2::API::EXCEPTIONS {

    NotEnoughMemoryError::~NotEnoughMemoryError() {

    }

    NotEnoughMemoryError::NotEnoughMemoryError() :
    runtime_error("Not Enough Memory to initialize Connection.") {

    }
}