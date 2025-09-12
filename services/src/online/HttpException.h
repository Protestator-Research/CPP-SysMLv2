//
// Created by Moritz Herzog on 24.04.24.
//

#ifndef DIGITALTWIN_HTTPEXCEPTION_H
#define DIGITALTWIN_HTTPEXCEPTION_H

#include <exception>
#include "../sysmlv2service_global.h"

#include "../sysmlv2service_global.h"

namespace SysMLv2::API::EXCEPTIONS {
    class SYSMLV2SERVICE_EXPORT HTTPException : std::exception {
    public:
        HTTPException() = delete;
        HTTPException(long httpErrorCode);

        const char * what() const noexcept override;
        long httpErrorCode();
    private:
        long HttpErrorCode;
    };
}

#endif //DIGITALTWIN_HTTPEXCEPTION_H
