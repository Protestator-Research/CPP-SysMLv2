//
// Created by Moritz Herzog on 14.12.23.
//
//---------------------------------------------------------
// Constants, Definitions, Pragmas
//---------------------------------------------------------

//---------------------------------------------------------
// External Classes
//---------------------------------------------------------
#include <algorithm>
#include <cctype>
#include <memory>
#include <mutex>
#include <optional>
#include <set>
#include <stdexcept>
#include <curl/curl.h>
#include <nlohmann/json.hpp>


//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include <sysmlv2/service/online/SysMLAPIImplementation.h>
#include <sysmlv2/service/online/NotEnoughMemoryError.h>
#include <sysmlv2/service/online/ConnectionError.h>
#include <sysmlv2/service/online/HttpException.h>
#include <sysmlv2/service/online/LinkHeader.h>
#include <sysmlv2/rest/serialization/SysMLv2Deserializer.h>
#include <sysmlv2/rest/entities/Project.h>
#include <sysmlv2/rest/entities/Commit.h>
#include <sysmlv2/rest/entities/CommitRequest.h>
#include <sysmlv2/rest/entities/ProjectRequest.h>


namespace SysMLv2::API {

    namespace {
        struct CurlDeleter {
            void operator()(CURL* handle) const { curl_easy_cleanup(handle); }
        };
        struct CurlSlistDeleter {
            void operator()(curl_slist* list) const { curl_slist_free_all(list); }
        };
        using CurlHandle = std::unique_ptr<CURL, CurlDeleter>;
        using CurlHeaderList = std::unique_ptr<curl_slist, CurlSlistDeleter>;

        std::once_flag CurlGlobalInitFlag;

        /**
         * Searches the header (case-insensitive) in the raw header block and returns the trimmed values of all its lines.
         */
        std::vector<std::string> findHeaderValues(const std::string& rawHeaders, const std::string& name) {
            std::vector<std::string> values;
            std::size_t position = 0;
            while (position < rawHeaders.size()) {
                auto lineEnd = rawHeaders.find('\n', position);
                if (lineEnd == std::string::npos)
                    lineEnd = rawHeaders.size();
                std::string line = rawHeaders.substr(position, lineEnd - position);
                position = lineEnd + 1;

                auto colon = line.find(':');
                if (colon != name.size())
                    continue;
                bool matches = std::equal(name.begin(), name.end(), line.begin(), [](char a, char b) {
                    return std::tolower(static_cast<unsigned char>(a)) == std::tolower(static_cast<unsigned char>(b));
                });
                if (!matches)
                    continue;
                auto first = line.find_first_not_of(" \t", colon + 1);
                auto last = line.find_last_not_of(" \t\r");
                values.push_back((first == std::string::npos || last < first) ? "" : line.substr(first, last - first + 1));
            }
            return values;
        }

        std::string findHeaderValue(const std::string& rawHeaders, const std::string& name) {
            auto values = findHeaderValues(rawHeaders, name);
            return values.empty() ? std::string() : values.back();
        }

        /// All lines of a header joined with ", " (RFC 9110: several lines are equivalent to one comma separated line).
        std::string joinedHeaderValue(const std::string& rawHeaders, const std::string& name) {
            std::string joined;
            for (const auto& value : findHeaderValues(rawHeaders, name)) {
                if (value.empty())
                    continue;
                joined += (joined.empty() ? "" : ", ") + value;
            }
            return joined;
        }
    }

    SysMLAPIImplementation::SysMLAPIImplementation(std::string serverAddress) :
            ServerAddress(std::move(serverAddress)) {
        // curl_global_init is not thread safe and must not be paired with curl_global_cleanup per instance, since
        // other instances (or other libcurl users in the process) would be broken. Thus it is done once per process.
        std::call_once(CurlGlobalInitFlag, []() { curl_global_init(CURL_GLOBAL_ALL); });
    }

    std::string SysMLAPIImplementation::loginUserWithPassword(std::string const& username, std::string const& password) {
        nlohmann::json jsonData;
        jsonData["username"] = username;
        jsonData["password"] = password;

        auto response = performRequest("POST", "login", jsonData.dump(), "");

        auto resultJson = nlohmann::json::parse(response.Body, nullptr, false);
        if (!resultJson.is_object() || !resultJson.contains("bearer") || !resultJson["bearer"].is_string())
            throw std::runtime_error("Login response does not contain a bearer token.");

        return resultJson["bearer"].get<std::string>();
    }

    std::vector<std::shared_ptr<SysMLv2::REST::IEntity>> SysMLAPIImplementation::getAllProjects(std::string barrierString) {
        return SysMLv2::SysMLv2Deserializer::deserializeJsonArray(performPagedGet("projects", barrierString));
    }

    std::vector<std::shared_ptr<SysMLv2::REST::IEntity>>
    SysMLAPIImplementation::getAllElementsFromCommit(std::string projectId, std::string commitId, std::string barrierString) {
        return SysMLv2::SysMLv2Deserializer::deserializeJsonArray(
                performPagedGet("projects/" + projectId + "/commits/" + commitId + "/elements", barrierString));
    }

    std::string SysMLAPIImplementation::getVersionOfBackend(const std::string& barrierString) {
        return performRequest("GET", "version", "", barrierString).Body;
    }

    std::vector<std::shared_ptr<SysMLv2::REST::IEntity>> SysMLAPIImplementation::getAllBranchesFroProject(const std::string& projectId, std::string barrierString)
    {
        return SysMLv2::SysMLv2Deserializer::deserializeJsonArray(
                performPagedGet("projects/" + projectId + "/branches", barrierString));
    }

    std::shared_ptr<SysMLv2::REST::IEntity>
    SysMLAPIImplementation::postProject(std::shared_ptr<SysMLv2::REST::ProjectRequest> project, std::string barrierString, std::string owningGroup) {
        std::string payload = project->serializeToJson();

        if (!owningGroup.empty()) {
            auto json = nlohmann::json::parse(payload);
            json["owningGroup"] = owningGroup;
            payload = json.dump();
        }

        auto response = performRequest("POST", "projects", payload, barrierString);
        return SysMLv2::SysMLv2Deserializer::deserializeJsonString(response.Body);
    }

    std::shared_ptr<SysMLv2::REST::IEntity> SysMLAPIImplementation::postCommit(std::string projectId,
	    std::shared_ptr<SysMLv2::REST::CommitRequest> commit, std::string barrierString)
    {
        auto response = performRequest("POST", "projects/" + projectId + "/commits", commit->serializeToJson(),
                                       barrierString);
        return SysMLv2::SysMLv2Deserializer::deserializeJsonString(response.Body);
    }

    std::shared_ptr<SysMLv2::REST::IEntity>
    SysMLAPIImplementation::getCommit(std::string projectId, std::string commitId, std::string barrierString) {
        auto response = performRequest("GET", "projects/" + projectId + "/commits/" + commitId, "", barrierString);
        return SysMLv2::SysMLv2Deserializer::deserializeJsonString(response.Body);
    }

    std::string SysMLAPIImplementation::postCustomRequest(std::string const &endpoint, std::string const &payload,
                                                          std::string const &barrierString) {
        return performRequest("POST", endpoint, payload, barrierString).Body;
    }

    std::string SysMLAPIImplementation::getCustomRequest(std::string const &endpoint, std::string const &barrierString) {
        return performPagedGet(endpoint, barrierString, true);
    }

    std::string SysMLAPIImplementation::performPagedGet(const std::string& endpoint, const std::string& barrierString,
                                                        bool onlyIfArray) {
        constexpr std::size_t MaxPages = 10000;

        // All Link lines of the last header set of the answer; empty if there is none.
        auto linkHeader = [](const HttpResponse& response) {
            return joinedHeaderValue(detail::lastHeaderSet(response.Headers), "Link");
        };
        auto nextTarget = [&](const HttpResponse& response, const std::string& currentEndpoint)
                -> std::optional<std::string> {
            auto link = linkHeader(response);
            if (link.empty())
                return std::nullopt;
            auto next = detail::findNextLinkUrl(link);
            if (!next)
                return std::nullopt;
            return detail::resolveNextLinkTarget(*next, ServerAddress, currentEndpoint);
        };

        auto response = performRequest("GET", endpoint, "", barrierString);
        if (linkHeader(response).empty())
            return response.Body;

        auto firstPage = nlohmann::json::parse(response.Body, nullptr, false);
        if (!firstPage.is_array()) {
            // Not a list: returned unchanged, whatever the Link header looks like (custom requests only).
            if (onlyIfArray)
                return response.Body;
        }
        auto target = nextTarget(response, endpoint);
        if (!target)
            return response.Body;
        if (!firstPage.is_array())
            throw std::runtime_error("A paginated answer must be a JSON array.");

        nlohmann::json merged = std::move(firstPage);
        std::set<std::string> visited;
        visited.insert(endpoint.substr((std::min)(endpoint.find_first_not_of('/'), endpoint.size()))); // same form as the targets
        std::size_t pages = 1;
        while (target) {
            if (++pages > MaxPages)
                throw std::runtime_error("The server announced more than 10000 pages.");
            if (!visited.insert(*target).second)
                throw std::runtime_error("The pagination of the server loops: a page was announced twice.");
            const std::string currentEndpoint = *target;
            response = performRequest("GET", currentEndpoint, "", barrierString);
            auto page = nlohmann::json::parse(response.Body, nullptr, false);
            if (!page.is_array())
                throw std::runtime_error("A paginated answer must be a JSON array.");
            for (auto& element : page)
                merged.push_back(std::move(element));
            target = nextTarget(response, currentEndpoint);
        }
        return merged.dump();
    }

    std::string SysMLAPIImplementation::putCustomRequest(std::string const &endpoint, std::string const &payload,
                                                         std::string const &barrierString) {
        return performRequest("PUT", endpoint, payload, barrierString).Body;
    }

    std::string SysMLAPIImplementation::deleteCustomRequest(std::string const &endpoint,
                                                            std::string const &barrierString) {
        return performRequest("DELETE", endpoint, "", barrierString).Body;
    }

    SysMLAPIImplementation::HttpResponse
    SysMLAPIImplementation::performRequest(const std::string& method, const std::string& endpoint,
                                           const std::string& payload, const std::string& barrierString) {
        HttpResponse response;

        CurlHandle serverConnection(curl_easy_init());
        if (!serverConnection)
            throw SysMLv2::API::EXCEPTIONS::NotEnoughMemoryError();

        std::string url = ServerAddress;
        if (url.empty() || url.back() != '/')
            url += '/';
        auto firstChar = endpoint.find_first_not_of('/');
        url += (firstChar == std::string::npos) ? std::string() : endpoint.substr(firstChar);

        CurlHeaderList headerList;
        auto appendHeader = [&headerList](const std::string& header) {
            curl_slist* extended = curl_slist_append(headerList.get(), header.c_str());
            if (!extended)
                throw SysMLv2::API::EXCEPTIONS::NotEnoughMemoryError();
            headerList.release();
            headerList.reset(extended);
        };
        appendHeader("Content-Type: application/json");
        appendHeader("Accept: application/json");
        appendHeader("Expect:"); // no "Expect: 100-continue" stall on larger POST/PUT bodies
        if (!barrierString.empty())
            appendHeader("Authorization: Bearer " + barrierString);

        CURL* handle = serverConnection.get();
        curl_easy_setopt(handle, CURLOPT_URL, url.c_str());
        curl_easy_setopt(handle, CURLOPT_CUSTOMREQUEST, method.c_str());
        curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, WriteBufferCallback);
        curl_easy_setopt(handle, CURLOPT_WRITEDATA, &response.Body);
        curl_easy_setopt(handle, CURLOPT_HEADERFUNCTION, WriteBufferCallback);
        curl_easy_setopt(handle, CURLOPT_HEADERDATA, &response.Headers);
        curl_easy_setopt(handle, CURLOPT_HTTPHEADER, headerList.get());
        curl_easy_setopt(handle, CURLOPT_SSL_OPTIONS, (long)CURLSSLOPT_NATIVE_CA);
        curl_easy_setopt(handle, CURLOPT_FOLLOWLOCATION, 0L);
        curl_easy_setopt(handle, CURLOPT_CONNECTTIMEOUT, 10L);
        curl_easy_setopt(handle, CURLOPT_TIMEOUT, 120L);
        curl_easy_setopt(handle, CURLOPT_NOSIGNAL, 1L);

        if (method == "POST" || method == "PUT") {
            curl_easy_setopt(handle, CURLOPT_POSTFIELDSIZE, static_cast<long>(payload.size()));
            curl_easy_setopt(handle, CURLOPT_POSTFIELDS, payload.c_str());
        }

        CURLcode serverResult = curl_easy_perform(handle);
        if (serverResult != CURLE_OK) {
            throw SysMLv2::API::EXCEPTIONS::ConnectionError(
                    static_cast<SysMLv2::API::EXCEPTIONS::CONNECTION_ERROR_TYPE>(serverResult));
        }

        curl_easy_getinfo(handle, CURLINFO_RESPONSE_CODE, &response.Status);

        if (response.Status < 200 || response.Status >= 300) {
            throw SysMLv2::API::EXCEPTIONS::HTTPException(response.Status, response.Body,
                                                          findHeaderValue(response.Headers, "Retry-After"));
        }

        return response;
    }

    size_t SysMLAPIImplementation::WriteBufferCallback(char *contents, size_t size, size_t nmemb, void* userp){
        static_cast<std::string*>(userp)->append(contents, size * nmemb);
        return size * nmemb;
    }
}
