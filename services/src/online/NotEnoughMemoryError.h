//
// Created by Moritz Herzog on 05.01.24.
//

#pragma once

#include <stdexcept>


namespace SysMLv2::API::EXCEPTIONS {
    class NotEnoughMemoryError : public std::runtime_error {
    public:
        NotEnoughMemoryError();
        ~NotEnoughMemoryError();
    };
}
