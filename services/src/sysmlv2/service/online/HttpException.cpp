//
// Created by Moritz Herzog on 24.04.24.
//

#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <utility>

#include <nlohmann/json.hpp>

#include "sysmlv2/service/online/HttpException.h"

namespace {
    /**
     * Extracts the string field "error" of a JSON object body. Never throws.
     */
    std::string extractServerErrorCode(const std::string& body) {
        try {
            if (body.empty() || !nlohmann::json::accept(body))
                return "";
            auto json = nlohmann::json::parse(body, nullptr, false);
            if (json.is_object()) {
                auto it = json.find("error");
                if (it != json.end() && it->is_string())
                    return it->get<std::string>();
            }
        } catch (...) {
        }
        return "";
    }

    long parseSeconds(const std::string& value) {
        auto first = value.find_first_not_of(" \t\r\n");
        if (first == std::string::npos)
            return -1;
        auto last = value.find_last_not_of(" \t\r\n");
        std::string trimmed = value.substr(first, last - first + 1);
        if (trimmed.size() > 9 || !std::all_of(trimmed.begin(), trimmed.end(),
                                               [](unsigned char c) { return std::isdigit(c); }))
            return -1;
        return std::strtol(trimmed.c_str(), nullptr, 10);
    }

    std::string buildMessage(long code, const std::string& body) {
        std::string message = "HTTP " + std::to_string(code);
        auto serverError = extractServerErrorCode(body);
        if (!serverError.empty())
            message += ": " + serverError;
        return message;
    }
}

SysMLv2::API::EXCEPTIONS::HTTPException::HTTPException(long httpErrorCode, std::string responseBody,
                                                       std::string retryAfter) :
        std::runtime_error(buildMessage(httpErrorCode, responseBody)),
        HttpErrorCode(httpErrorCode),
        ResponseBody(std::move(responseBody)),
        RetryAfterSeconds(parseSeconds(retryAfter))
{

}

long SysMLv2::API::EXCEPTIONS::HTTPException::httpErrorCode() const noexcept {
    return HttpErrorCode;
}

const std::string& SysMLv2::API::EXCEPTIONS::HTTPException::responseBody() const noexcept {
    return ResponseBody;
}

std::string SysMLv2::API::EXCEPTIONS::HTTPException::serverErrorCode() const {
    return extractServerErrorCode(ResponseBody);
}

long SysMLv2::API::EXCEPTIONS::HTTPException::retryAfterSeconds() const noexcept {
    return RetryAfterSeconds;
}
