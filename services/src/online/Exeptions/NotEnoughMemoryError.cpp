//
// Created by Moritz Herzog on 05.01.24.
//

#include "NotEnoughMemoryError.h"

namespace BACKEND_COMMUNICATION::EXCEPTIONS {

    NotEnoughMemoryError::~NotEnoughMemoryError() {

    }

    NotEnoughMemoryError::NotEnoughMemoryError() :
    runtime_error("Not Enough Memory to initialize Connection.") {

    }
}