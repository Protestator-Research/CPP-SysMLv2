//
// Created by Moritz Herzog on 24.04.24.
//

#include "HttpException.h"

BACKEND_COMMUNICATION::EXCEPTIONS::HTTPException::HTTPException(long httpErrorCode) :
        HttpErrorCode(httpErrorCode)
{

}

const char *BACKEND_COMMUNICATION::EXCEPTIONS::HTTPException::what() const noexcept {
    return exception::what();
}

long BACKEND_COMMUNICATION::EXCEPTIONS::HTTPException::httpErrorCode() {
    return HttpErrorCode;
}
