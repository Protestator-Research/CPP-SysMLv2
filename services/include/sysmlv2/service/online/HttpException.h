//
// Created by Moritz Herzog on 24.04.24.
//

#ifndef DIGITALTWIN_HTTPEXCEPTION_H
#define DIGITALTWIN_HTTPEXCEPTION_H

#include <stdexcept>
#include <string>

#include <sysmlv2/service/sysmlv2service_global.h>

namespace SysMLv2::API::EXCEPTIONS {
    /**
     * Thrown if the server answered a request with a HTTP status outside of 2xx.
     * The exception keeps the status, the response body and the optional Retry-After header, so that clients can
     * react to e.g. 401 (token expired), 403 (password change required) or 429 (login throttled).
     */
    class SYSMLV2SERVICE_EXPORT HTTPException : public std::runtime_error {
    public:
        HTTPException() = delete;

        /**
         * @param httpErrorCode The HTTP status code of the response.
         * @param responseBody The body of the response (may be empty).
         * @param retryAfter The raw value of the Retry-After response header (empty if not sent). It is interpreted
         *                   as a number of seconds, other formats (HTTP date) are ignored.
         */
        explicit HTTPException(long httpErrorCode, std::string responseBody = "", std::string retryAfter = "");

        /**
         * @return The HTTP status code.
         */
        long httpErrorCode() const noexcept;

        /**
         * @return The raw response body, may be empty.
         */
        const std::string& responseBody() const noexcept;

        /**
         * @return The value of the string field "error" if the body is a JSON object, otherwise an empty string.
         *         Never throws.
         */
        std::string serverErrorCode() const;

        /**
         * @return The Retry-After value in seconds, or -1 if the header was missing or not a number of seconds.
         */
        long retryAfterSeconds() const noexcept;

    private:
        long HttpErrorCode;
        std::string ResponseBody;
        long RetryAfterSeconds;
    };
}

#endif //DIGITALTWIN_HTTPEXCEPTION_H
