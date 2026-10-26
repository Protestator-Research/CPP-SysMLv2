//---------------------------------------------------------
// Constants, Definitions, Pragmas
//---------------------------------------------------------
#pragma once
//---------------------------------------------------------
// External Classes
//---------------------------------------------------------
#include <algorithm>
#include <cctype>
#include <optional>
#include <stdexcept>
#include <string>
#include <vector>

namespace SysMLv2::API::detail {
    /**
     * Helpers for the pagination of the SysML v2 API (Link header, RFC 8288). Header-only and free of any libcurl
     * dependency so they can be tested without a server. Not part of the stable API.
     */

    /**
     * One entry of a Link header: the target URI reference and the relation types of its "rel" parameter.
     */
    struct LinkValue {
        std::string Url;
        std::vector<std::string> Relations; ///< lower case
    };

    inline std::string toLowerAscii(std::string text) {
        std::transform(text.begin(), text.end(), text.begin(),
                       [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
        return text;
    }

    /**
     * Returns the part of a raw header block that belongs to the last response in it (the block may contain several
     * header sets, e.g. "100 Continue" followed by the final response). The last line starting with "HTTP/" starts the
     * last set; without such a line the block is returned unchanged.
     */
    inline std::string lastHeaderSet(const std::string& rawHeaders) {
        std::size_t start = 0;
        std::size_t position = 0;
        while (position < rawHeaders.size()) {
            if (rawHeaders.compare(position, 5, "HTTP/") == 0)
                start = position;
            auto lineEnd = rawHeaders.find('\n', position);
            if (lineEnd == std::string::npos)
                break;
            position = lineEnd + 1;
        }
        return rawHeaders.substr(start);
    }

    /**
     * Parses the value of a Link header (comma separated list of "<uri>; param=value; ...").
     * @throws std::runtime_error if the value is malformed (missing '<' or '>', unterminated quoted string, ...).
     *         Malformed headers are rejected instead of being skipped, otherwise a pagination would be cut off silently.
     */
    inline std::vector<LinkValue> parseLinkHeader(const std::string& value) {
        std::vector<LinkValue> result;
        std::size_t i = 0;
        const std::size_t n = value.size();
        auto skipSpace = [&]() { while (i < n && (value[i] == ' ' || value[i] == '\t' || value[i] == '\r' || value[i] == '\n')) ++i; };

        skipSpace();
        while (i < n) {
            if (value[i] == ',') { ++i; skipSpace(); continue; }
            if (value[i] != '<')
                throw std::runtime_error("Malformed Link header: '<' expected.");
            auto close = value.find('>', i + 1);
            if (close == std::string::npos)
                throw std::runtime_error("Malformed Link header: missing '>'.");
            LinkValue link;
            link.Url = value.substr(i + 1, close - i - 1);
            i = close + 1;
            skipSpace();

            while (i < n && value[i] == ';') {
                ++i;
                skipSpace();
                auto nameStart = i;
                while (i < n && value[i] != '=' && value[i] != ';' && value[i] != ',') ++i;
                std::string name = toLowerAscii(value.substr(nameStart, i - nameStart));
                while (!name.empty() && std::isspace(static_cast<unsigned char>(name.back()))) name.pop_back();
                std::string paramValue;
                if (i < n && value[i] == '=') {
                    ++i;
                    skipSpace();
                    if (i < n && value[i] == '"') {
                        ++i;
                        bool closed = false;
                        while (i < n) {
                            if (value[i] == '\\' && i + 1 < n) { paramValue += value[i + 1]; i += 2; continue; }
                            if (value[i] == '"') { closed = true; ++i; break; }
                            paramValue += value[i++];
                        }
                        if (!closed)
                            throw std::runtime_error("Malformed Link header: unterminated quoted string.");
                    } else {
                        auto valueStart = i;
                        while (i < n && value[i] != ';' && value[i] != ',') ++i;
                        paramValue = value.substr(valueStart, i - valueStart);
                        while (!paramValue.empty() && std::isspace(static_cast<unsigned char>(paramValue.back()))) paramValue.pop_back();
                    }
                }
                if (name == "rel" && link.Relations.empty()) { // RFC 8288: only the first rel counts
                    std::string current;
                    for (char c : paramValue + ' ') {
                        if (c == ' ' || c == '\t') {
                            if (!current.empty()) link.Relations.push_back(toLowerAscii(current));
                            current.clear();
                        } else {
                            current += c;
                        }
                    }
                }
                skipSpace();
            }
            if (i < n && value[i] != ',')
                throw std::runtime_error("Malformed Link header: unexpected character after link.");
            result.push_back(std::move(link));
        }
        return result;
    }

    /**
     * Returns the URI of the first link with the relation "next", if any.
     * @throws std::runtime_error see parseLinkHeader.
     */
    inline std::optional<std::string> findNextLinkUrl(const std::string& linkHeaderValue) {
        for (const auto& link : parseLinkHeader(linkHeaderValue)) {
            if (std::find(link.Relations.begin(), link.Relations.end(), "next") != link.Relations.end())
                return link.Url;
        }
        return std::nullopt;
    }

    /**
     * True if a path has a segment "." or ".." also when written percent-encoded (%2e, %2E, ".%2e", ...).
     */
    inline bool hasDotSegment(const std::string& path) {
        std::size_t start = 0;
        while (start <= path.size()) {
            auto end = path.find('/', start);
            if (end == std::string::npos)
                end = path.size();
            std::string decoded;
            for (std::size_t i = start; i < end; ++i) {
                if (path[i] == '%' && i + 2 < end &&
                    std::isxdigit(static_cast<unsigned char>(path[i + 1])) &&
                    std::isxdigit(static_cast<unsigned char>(path[i + 2]))) {
                    decoded += static_cast<char>(std::stoi(path.substr(i + 1, 2), nullptr, 16));
                    i += 2;
                } else {
                    decoded += path[i];
                }
            }
            if (decoded == "." || decoded == "..")
                return true;
            start = end + 1;
        }
        return false;
    }

    /**
     * Turns the target of a Link into an endpoint relative to the configured server address (path and query, no
     * leading '/'), so that it can be requested with the same base URL and bearer token.
     * @param linkUrl Target of the link: absolute URL, scheme relative, absolute path, query only or relative path.
     * @param serverAddress The configured base URL, e.g. "http://host:8088/".
     * @param currentEndpoint The endpoint (relative to the base) that produced the link, used for relative references.
     * @throws std::runtime_error if the link points to a different scheme, host or port, outside of the base path or
     *         contains dot segments.
     */
    inline std::string resolveNextLinkTarget(std::string linkUrl, std::string serverAddress,
                                             const std::string& currentEndpoint) {
        if (serverAddress.empty() || serverAddress.back() != '/')
            serverAddress += '/';

        // RFC 3986: scheme = ALPHA *( ALPHA / DIGIT / "+" / "-" / "." ) ":" and only at the very beginning. Otherwise the
        // reference is relative, even if "://" appears later (e.g. in a query).
        auto splitUrl = [](const std::string& url, std::string& scheme, std::string& authority, std::string& rest) {
            std::size_t schemeEnd = 0;
            if (url.empty() || !std::isalpha(static_cast<unsigned char>(url[0])))
                return false;
            while (schemeEnd < url.size() && (std::isalnum(static_cast<unsigned char>(url[schemeEnd])) ||
                                              url[schemeEnd] == '+' || url[schemeEnd] == '-' || url[schemeEnd] == '.'))
                ++schemeEnd;
            if (url.compare(schemeEnd, 3, "://") != 0)
                return false;
            scheme = toLowerAscii(url.substr(0, schemeEnd));
            auto authorityEnd = url.find_first_of("/?#", schemeEnd + 3);
            authority = toLowerAscii(url.substr(schemeEnd + 3, authorityEnd == std::string::npos ? std::string::npos : authorityEnd - schemeEnd - 3));
            rest = authorityEnd == std::string::npos ? std::string() : url.substr(authorityEnd);
            return true;
        };
        auto normalizeAuthority = [](std::string scheme, std::string authority) {
            if (scheme == "http" && authority.size() > 3 && authority.compare(authority.size() - 3, 3, ":80") == 0)
                authority.resize(authority.size() - 3);
            if (scheme == "https" && authority.size() > 4 && authority.compare(authority.size() - 4, 4, ":443") == 0)
                authority.resize(authority.size() - 4);
            return authority;
        };

        std::string baseScheme, baseAuthority, baseRest;
        if (!splitUrl(serverAddress, baseScheme, baseAuthority, baseRest))
            throw std::runtime_error("The server address is no absolute URL.");
        std::string basePath = baseRest.substr(0, baseRest.find_first_of("?#"));
        if (basePath.empty() || basePath.back() != '/')
            basePath += '/';

        if (auto fragment = linkUrl.find('#'); fragment != std::string::npos)
            linkUrl.resize(fragment);

        std::string pathAndQuery; // starts with '/'
        std::string scheme, authority, rest;
        if (linkUrl.compare(0, 2, "//") == 0)
            linkUrl = baseScheme + ":" + linkUrl;
        if (splitUrl(linkUrl, scheme, authority, rest)) {
            if (scheme != baseScheme || normalizeAuthority(scheme, authority) != normalizeAuthority(baseScheme, baseAuthority))
                throw std::runtime_error("The Link header points to a different server than the configured one.");
            pathAndQuery = rest.empty() ? "/" : rest;
            if (pathAndQuery[0] == '?')
                pathAndQuery = "/" + pathAndQuery;
        } else if (!linkUrl.empty() && linkUrl[0] == '/') {
            pathAndQuery = linkUrl;
        } else {
            // relative reference: resolved against the URL of the request that produced the link
            std::string currentPath = currentEndpoint.substr(0, currentEndpoint.find('?'));
            while (!currentPath.empty() && currentPath[0] == '/') currentPath.erase(0, 1);
            if (!linkUrl.empty() && linkUrl[0] == '?') {
                pathAndQuery = basePath + currentPath + linkUrl;
            } else {
                auto slash = currentPath.rfind('/');
                pathAndQuery = basePath + (slash == std::string::npos ? std::string() : currentPath.substr(0, slash + 1)) + linkUrl;
            }
        }

        if (hasDotSegment(pathAndQuery.substr(0, pathAndQuery.find('?'))))
            throw std::runtime_error("The Link header contains dot segments.");
        if (pathAndQuery.compare(0, basePath.size(), basePath) != 0)
            throw std::runtime_error("The Link header points outside of the configured base URL.");

        return pathAndQuery.substr(basePath.size());
    }
}
