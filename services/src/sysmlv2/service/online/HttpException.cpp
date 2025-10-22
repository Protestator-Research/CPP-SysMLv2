//
// Created by Moritz Herzog on 24.04.24.
//

#include "sysmlv2/service/online/HttpException.h"

SysMLv2::API::EXCEPTIONS::HTTPException::HTTPException(long httpErrorCode) :
        HttpErrorCode(httpErrorCode)
{

}

const char *SysMLv2::API::EXCEPTIONS::HTTPException::what() const noexcept {
    return exception::what();
}

long SysMLv2::API::EXCEPTIONS::HTTPException::httpErrorCode() {
    return HttpErrorCode;
}
