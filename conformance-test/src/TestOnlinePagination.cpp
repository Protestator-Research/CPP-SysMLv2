//
// Tests of the pagination of the SysML v2 API client (Link header, RFC 8288): the parsing helpers and the paging of
// SysMLAPIImplementation against a tiny HTTP server on 127.0.0.1 that runs inside the test.
//

#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include <sysmlv2/service/online/LinkHeader.h>
#include <sysmlv2/service/online/SysMLAPIImplementation.h>
#include <sysmlv2/service/online/HttpException.h>
#include <sysmlv2/rest/entities/Project.h>

#ifndef _WIN32
#include <atomic>
#include <functional>
#include <map>
#include <mutex>
#include <thread>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <poll.h>
#include <sys/socket.h>
#include <unistd.h>
#endif

using namespace SysMLv2::API;
using nlohmann::json;

//---------------------------------------------------------
// Link header parsing
//---------------------------------------------------------
TEST(LinkHeader, ParsesRelativeAndAbsoluteTargets) {
    auto relative = detail::findNextLinkUrl("</projects?page[size]=1>; rel=\"next\"");
    ASSERT_TRUE(relative.has_value());
    EXPECT_EQ(*relative, "/projects?page[size]=1");

    auto absolute = detail::findNextLinkUrl("<http://host:8088/projects?page%5Bsize%5D=1&page%5Bafter%5D=abc>; rel=\"next\"");
    ASSERT_TRUE(absolute.has_value());
    EXPECT_EQ(*absolute, "http://host:8088/projects?page%5Bsize%5D=1&page%5Bafter%5D=abc");

    auto unquoted = detail::findNextLinkUrl("<x>; rel=next");
    ASSERT_TRUE(unquoted.has_value());
    EXPECT_EQ(*unquoted, "x");
}

TEST(LinkHeader, PicksNextAmongSeveralRelations) {
    auto next = detail::findNextLinkUrl("<http://h/p?a=1>; rel=\"prev\", <http://h/p?a=3>; rel=\"next\", <http://h/p?a=9>; rel=\"last\"");
    ASSERT_TRUE(next.has_value());
    EXPECT_EQ(*next, "http://h/p?a=3");

    auto multi = detail::findNextLinkUrl("<http://h/p?a=3>; REL=\"Last NEXT\"; title=\"a, b; c\"");
    ASSERT_TRUE(multi.has_value());
    EXPECT_EQ(*multi, "http://h/p?a=3");

    EXPECT_FALSE(detail::findNextLinkUrl("<http://h/p?a=1>; rel=\"prev\"").has_value());
    EXPECT_FALSE(detail::findNextLinkUrl("").has_value());
    EXPECT_FALSE(detail::findNextLinkUrl("<http://h/p>").has_value());
}

TEST(LinkHeader, RejectsBrokenHeaders) {
    EXPECT_THROW(detail::findNextLinkUrl("http://h/p; rel=\"next\""), std::runtime_error);
    EXPECT_THROW(detail::findNextLinkUrl("<http://h/p; rel=\"next\""), std::runtime_error);
    EXPECT_THROW(detail::findNextLinkUrl("<http://h/p>; rel=\"next"), std::runtime_error);
    EXPECT_THROW(detail::findNextLinkUrl("<http://h/p> garbage"), std::runtime_error);
}

TEST(LinkHeader, LastHeaderSetWins) {
    const std::string raw = "HTTP/1.1 100 Continue\r\nLink: <a>; rel=\"next\"\r\n\r\nHTTP/1.1 200 OK\r\nContent-Type: x\r\n\r\n";
    auto last = detail::lastHeaderSet(raw);
    EXPECT_EQ(last.find("Link"), std::string::npos);
    EXPECT_NE(last.find("200 OK"), std::string::npos);
    EXPECT_EQ(detail::lastHeaderSet("Link: x\r\n"), "Link: x\r\n");
}

TEST(LinkHeader, ResolvesTargetsRelativeToTheBaseUrl) {
    const std::string base = "http://host:8088/";
    EXPECT_EQ(detail::resolveNextLinkTarget("http://host:8088/projects?page%5Bsize%5D=1&page%5Bafter%5D=a", base, "projects"),
              "projects?page%5Bsize%5D=1&page%5Bafter%5D=a");
    EXPECT_EQ(detail::resolveNextLinkTarget("HTTP://HOST:8088/projects?x=1#frag", base, "projects"), "projects?x=1");
    EXPECT_EQ(detail::resolveNextLinkTarget("/projects?x=1", base, "projects"), "projects?x=1");
    EXPECT_EQ(detail::resolveNextLinkTarget("//host:8088/projects?x=1", base, "projects"), "projects?x=1");
    EXPECT_EQ(detail::resolveNextLinkTarget("?x=2", base, "projects/1/branches?x=1"), "projects/1/branches?x=2");
    EXPECT_EQ(detail::resolveNextLinkTarget("elements?x=2", base, "projects/1/elements?x=1"), "projects/1/elements?x=2");
    // base without trailing slash and with a path prefix
    EXPECT_EQ(detail::resolveNextLinkTarget("http://host/api/projects?x=1", "http://host/api", "projects"), "projects?x=1");
    EXPECT_EQ(detail::resolveNextLinkTarget("http://host:80/projects", "http://host/", "projects"), "projects");
}

TEST(LinkHeader, SchemeIsOnlyRecognisedAtTheStart) {
    const std::string base = "http://host:8088/";
    // "://" inside the query does not make the reference absolute
    EXPECT_EQ(detail::resolveNextLinkTarget("/projects?q=http://x", base, "projects"), "projects?q=http://x");
    EXPECT_EQ(detail::resolveNextLinkTarget("?q=http://evil/", base, "projects"), "projects?q=http://evil/");
    EXPECT_EQ(detail::resolveNextLinkTarget("p?redirect=https://evil.example/a", base, "projects"), "p?redirect=https://evil.example/a");
}

TEST(LinkHeader, PercentEncodedDotSegmentsAreRejected) {
    const std::string base = "http://host:8088/";
    EXPECT_THROW(detail::resolveNextLinkTarget("/projects/%2e%2e/secret", base, "projects"), std::runtime_error);
    EXPECT_THROW(detail::resolveNextLinkTarget("/projects/%2E%2E/secret", base, "projects"), std::runtime_error);
    EXPECT_THROW(detail::resolveNextLinkTarget("/projects/.%2e/secret", base, "projects"), std::runtime_error);
    EXPECT_THROW(detail::resolveNextLinkTarget("/projects/%2e/x", base, "projects"), std::runtime_error);
    EXPECT_THROW(detail::resolveNextLinkTarget("http://host:8088/projects/%2E%2e", base, "projects"), std::runtime_error);
    EXPECT_EQ(detail::resolveNextLinkTarget("/projects/a%2Eb?x=%2e%2e", base, "projects"), "projects/a%2Eb?x=%2e%2e");
}

TEST(LinkHeader, RejectsForeignTargets) {
    const std::string base = "http://host:8088/";
    EXPECT_THROW(detail::resolveNextLinkTarget("http://evil:8088/projects", base, "projects"), std::runtime_error);
    EXPECT_THROW(detail::resolveNextLinkTarget("http://host:9999/projects", base, "projects"), std::runtime_error);
    EXPECT_THROW(detail::resolveNextLinkTarget("https://host:8088/projects", base, "projects"), std::runtime_error);
    EXPECT_THROW(detail::resolveNextLinkTarget("//evil/projects", base, "projects"), std::runtime_error);
    EXPECT_THROW(detail::resolveNextLinkTarget("http://host:8088@evil/projects", base, "projects"), std::runtime_error);
    EXPECT_THROW(detail::resolveNextLinkTarget("/other/projects", "http://host/api/", "projects"), std::runtime_error);
    EXPECT_THROW(detail::resolveNextLinkTarget("/projects/../secret", base, "projects"), std::runtime_error);
}

#ifndef _WIN32
//---------------------------------------------------------
// Paging against a local HTTP server
//---------------------------------------------------------
namespace {
    struct FakeRequest {
        std::string Method;
        std::string Target;
        std::string Authorization;
    };
    struct FakeResponse {
        int Status = 200;
        std::string Body = "[]";
        std::string Link; ///< value of the Link header, empty: none
        std::string ExtraHeaders;
    };

    /// Minimal HTTP/1.1 server (one request per connection) on 127.0.0.1 with a free port.
    class FakeServer {
    public:
        using Handler = std::function<FakeResponse(const FakeRequest&)>;

        explicit FakeServer(Handler handler) : HandlerFunction(std::move(handler)) {
            ListenFd = ::socket(AF_INET, SOCK_STREAM, 0);
            if (ListenFd < 0)
                throw std::runtime_error("socket failed");
            int yes = 1;
            ::setsockopt(ListenFd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));
            sockaddr_in address{};
            address.sin_family = AF_INET;
            address.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
            address.sin_port = 0;
            if (::bind(ListenFd, reinterpret_cast<sockaddr*>(&address), sizeof(address)) != 0 || ::listen(ListenFd, 16) != 0)
                throw std::runtime_error("bind/listen failed");
            socklen_t length = sizeof(address);
            ::getsockname(ListenFd, reinterpret_cast<sockaddr*>(&address), &length);
            Port = ntohs(address.sin_port);
            Worker = std::thread([this] { run(); });
        }
        ~FakeServer() {
            Stop = true;
            Worker.join();
            ::close(ListenFd);
        }
        FakeServer(const FakeServer&) = delete;
        FakeServer& operator=(const FakeServer&) = delete;

        std::string baseUrl() const { return "http://127.0.0.1:" + std::to_string(Port) + "/"; }
        int port() const { return Port; }
        std::vector<FakeRequest> requests() {
            std::lock_guard<std::mutex> lock(Mutex);
            return Requests;
        }

    private:
        void run() {
            while (!Stop) {
                pollfd descriptor{ListenFd, POLLIN, 0};
                if (::poll(&descriptor, 1, 50) <= 0)
                    continue;
                int client = ::accept(ListenFd, nullptr, nullptr);
                if (client < 0)
                    continue;
                serve(client);
                ::close(client);
            }
        }
        void serve(int client) {
            std::string data;
            char buffer[2048];
            timeval timeout{5, 0};
            ::setsockopt(client, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
            while (data.find("\r\n\r\n") == std::string::npos) {
                auto count = ::recv(client, buffer, sizeof(buffer), 0);
                if (count <= 0)
                    return;
                data.append(buffer, static_cast<std::size_t>(count));
            }
            FakeRequest request;
            auto firstEnd = data.find("\r\n");
            auto firstSpace = data.find(' ');
            auto secondSpace = data.find(' ', firstSpace + 1);
            request.Method = data.substr(0, firstSpace);
            request.Target = data.substr(firstSpace + 1, secondSpace - firstSpace - 1);
            auto auth = data.find("\r\nAuthorization: ");
            if (auth != std::string::npos && auth < data.find("\r\n\r\n")) {
                auto start = auth + 17;
                request.Authorization = data.substr(start, data.find("\r\n", start) - start);
            }
            (void)firstEnd;
            {
                std::lock_guard<std::mutex> lock(Mutex);
                Requests.push_back(request);
            }
            FakeResponse response = HandlerFunction(request);
            std::string text = "HTTP/1.1 " + std::to_string(response.Status) + " X\r\nContent-Type: application/json\r\n";
            if (!response.Link.empty())
                text += "Link: " + response.Link + "\r\n";
            text += response.ExtraHeaders;
            text += "Content-Length: " + std::to_string(response.Body.size()) + "\r\nConnection: close\r\n\r\n" + response.Body;
            std::size_t sent = 0;
            while (sent < text.size()) {
                auto count = ::send(client, text.data() + sent, text.size() - sent, MSG_NOSIGNAL);
                if (count <= 0)
                    return;
                sent += static_cast<std::size_t>(count);
            }
        }

        Handler HandlerFunction;
        int ListenFd = -1;
        int Port = 0;
        std::atomic<bool> Stop{false};
        std::thread Worker;
        std::mutex Mutex;
        std::vector<FakeRequest> Requests;
    };

    const std::string Token = "test-token";

    json projectJson(int number) {
        char id[40];
        snprintf(id, sizeof(id), "6e701bf8-7793-49de-9b0e-%012d", number);
        return {{"@id", id}, {"@type", "Project"}, {"name", "P" + std::to_string(number)}};
    }

    /// Serves `total` objects, `pageSize` per page, with an absolute and percent-encoded rel="next" link.
    FakeServer::Handler pagedHandler(FakeServer*& self, int total, int pageSize, std::string path, bool absolute = true) {
        return [&self, total, pageSize, path, absolute](const FakeRequest& request) {
            FakeResponse response;
            int offset = 0;
            auto pos = request.Target.find("page%5Bafter%5D=");
            if (pos != std::string::npos)
                offset = std::stoi(request.Target.substr(pos + 16));
            json page = json::array();
            for (int i = offset; i < std::min(total, offset + pageSize); ++i)
                page.push_back(projectJson(i));
            response.Body = page.dump();
            if (offset + pageSize < total) {
                std::string target = path + "?page%5Bsize%5D=" + std::to_string(pageSize) + "&page%5Bafter%5D=" +
                                     std::to_string(offset + pageSize);
                std::string url = absolute ? "http://127.0.0.1:" + std::to_string(self->port()) + "/" + target : "/" + target;
                response.Link = "<" + url + ">; rel=\"next\"";
            }
            return response;
        };
    }
}

TEST(OnlinePagination, GetAllProjectsFollowsAbsolutePercentEncodedLinks) {
    FakeServer* self = nullptr;
    FakeServer server(pagedHandler(self, 7, 3, "projects"));
    self = &server;
    SysMLAPIImplementation api(server.baseUrl());

    auto projects = api.getAllProjects(Token);
    ASSERT_EQ(projects.size(), 7u);
    for (std::size_t i = 0; i < projects.size(); ++i)
        EXPECT_EQ(std::dynamic_pointer_cast<SysMLv2::REST::Project>(projects[i])->getName(), "P" + std::to_string(i));

    auto requests = server.requests();
    ASSERT_EQ(requests.size(), 3u);
    EXPECT_EQ(requests[0].Target, "/projects");
    EXPECT_EQ(requests[1].Target, "/projects?page%5Bsize%5D=3&page%5Bafter%5D=3");
    for (const auto& request : requests) {
        EXPECT_EQ(request.Method, "GET");
        EXPECT_EQ(request.Authorization, "Bearer " + Token);
    }
}

TEST(OnlinePagination, ElementsAndBranchesArePaged) {
    FakeServer* self = nullptr;
    FakeServer server([&self](const FakeRequest& request) {
        // both resources are served with the same two page layout; the path of the first request decides the link target
        const std::string path = request.Target.substr(1, request.Target.find('?') - 1);
        bool second = request.Target.find("page%5Bafter%5D=") != std::string::npos;
        FakeResponse response;
        response.Body = json::array({projectJson(second ? 1 : 0)}).dump();
        if (!second)
            response.Link = "</" + path + "?page%5Bafter%5D=1>; rel=\"next\"";
        return response;
    });
    self = &server;
    SysMLAPIImplementation api(server.baseUrl());

    EXPECT_EQ(api.getAllElementsFromCommit("p1", "c1", Token).size(), 2u);
    EXPECT_EQ(api.getAllBranchesFroProject("p1", Token).size(), 2u);
    auto requests = server.requests();
    ASSERT_EQ(requests.size(), 4u);
    EXPECT_EQ(requests[1].Target, "/projects/p1/commits/c1/elements?page%5Bafter%5D=1");
    EXPECT_EQ(requests[3].Target, "/projects/p1/branches?page%5Bafter%5D=1");
}

TEST(OnlinePagination, CustomGetMergesArraysAndKeepsOtherAnswers) {
    FakeServer* self = nullptr;
    FakeServer paged(pagedHandler(self, 5, 2, "twins", false));
    self = &paged;
    SysMLAPIImplementation api(paged.baseUrl());
    auto merged = json::parse(api.getCustomRequest("/twins", Token));
    ASSERT_TRUE(merged.is_array());
    EXPECT_EQ(merged.size(), 5u);
    EXPECT_EQ(merged[4]["name"], "P4");

    // no Link header: body returned byte for byte
    const std::string body = "[ {\"a\" :1} ,\n {\"b\":2} ]";
    FakeServer plain([&body](const FakeRequest&) { FakeResponse r; r.Body = body; return r; });
    EXPECT_EQ(SysMLAPIImplementation(plain.baseUrl()).getCustomRequest("anything", Token), body);
    EXPECT_EQ(plain.requests().size(), 1u);

    // Link header but no JSON array: unchanged, no further request
    const std::string object = "{\"version\": 1}";
    FakeServer notArray([&object](const FakeRequest&) { FakeResponse r; r.Body = object; r.Link = "</x?page=2>; rel=\"next\""; return r; });
    EXPECT_EQ(SysMLAPIImplementation(notArray.baseUrl()).getCustomRequest("version", Token), object);
    EXPECT_EQ(notArray.requests().size(), 1u);

    // a Link without rel="next" is ignored
    FakeServer lastOnly([&body](const FakeRequest&) { FakeResponse r; r.Body = body; r.Link = "</x?page=1>; rel=\"last\""; return r; });
    EXPECT_EQ(SysMLAPIImplementation(lastOnly.baseUrl()).getCustomRequest("x", Token), body);
    EXPECT_EQ(lastOnly.requests().size(), 1u);
}

TEST(OnlinePagination, SeveralLinkLinesAreCombined) {
    FakeServer server([](const FakeRequest& request) {
        FakeResponse r;
        bool second = request.Target.find("page%5Bafter%5D=") != std::string::npos;
        r.Body = json::array({projectJson(second ? 1 : 0)}).dump();
        if (!second)
            r.ExtraHeaders = "Link: </projects?page%5Bafter%5D=0>; rel=\"prev\"\r\n"
                             "Link: </projects?page%5Bafter%5D=1>; rel=\"next\"\r\n";
        return r;
    });
    auto merged = json::parse(SysMLAPIImplementation(server.baseUrl()).getCustomRequest("projects", Token));
    EXPECT_EQ(merged.size(), 2u);
    EXPECT_EQ(server.requests().size(), 2u);
}

TEST(OnlinePagination, NonArrayAnswerIsReturnedEvenWithBrokenOrForeignLink) {
    const std::string object = "{\"version\": 1}";
    FakeServer foreign([](const FakeRequest&) { return FakeResponse{}; });
    FakeServer broken([&object](const FakeRequest&) { FakeResponse r; r.Body = object; r.Link = "</x?page=2; rel=\"next\""; return r; });
    EXPECT_EQ(SysMLAPIImplementation(broken.baseUrl()).getCustomRequest("version", Token), object);

    FakeServer other([&object, &foreign](const FakeRequest&) {
        FakeResponse r;
        r.Body = object;
        r.Link = "<http://127.0.0.1:" + std::to_string(foreign.port()) + "/x>; rel=\"next\"";
        return r;
    });
    EXPECT_EQ(SysMLAPIImplementation(other.baseUrl()).getCustomRequest("version", Token), object);
    EXPECT_TRUE(foreign.requests().empty());
}

TEST(OnlinePagination, FirstEndpointWithAndWithoutLeadingSlashCountsTheSame) {
    FakeServer server([](const FakeRequest&) {
        FakeResponse r;
        r.Body = json::array({projectJson(0)}).dump();
        r.Link = "</twins>; rel=\"next\"";
        return r;
    });
    EXPECT_THROW(SysMLAPIImplementation(server.baseUrl()).getCustomRequest("/twins", Token), std::runtime_error);
    EXPECT_EQ(server.requests().size(), 1u);
}

TEST(OnlinePagination, ForeignHostIsNeverContacted) {
    FakeServer foreign([](const FakeRequest&) { return FakeResponse{}; });
    FakeServer origin([&foreign](const FakeRequest&) {
        FakeResponse r;
        r.Body = json::array({projectJson(0)}).dump();
        r.Link = "<http://127.0.0.1:" + std::to_string(foreign.port()) + "/projects?page%5Bafter%5D=1>; rel=\"next\"";
        return r;
    });
    SysMLAPIImplementation api(origin.baseUrl());
    EXPECT_THROW(api.getAllProjects(Token), std::runtime_error);
    EXPECT_EQ(origin.requests().size(), 1u);
    EXPECT_TRUE(foreign.requests().empty());
}

TEST(OnlinePagination, LoopsBrokenHeadersAndBadPagesAreErrors) {
    FakeServer loop([](const FakeRequest&) {
        FakeResponse r;
        r.Body = json::array({projectJson(0)}).dump();
        r.Link = "</projects?page%5Bafter%5D=same>; rel=\"next\"";
        return r;
    });
    EXPECT_THROW(SysMLAPIImplementation(loop.baseUrl()).getAllProjects(Token), std::runtime_error);
    EXPECT_LE(loop.requests().size(), 3u);

    FakeServer broken([](const FakeRequest&) {
        FakeResponse r;
        r.Body = "[]";
        r.Link = "</projects?page=2; rel=\"next\"";
        return r;
    });
    EXPECT_THROW(SysMLAPIImplementation(broken.baseUrl()).getAllProjects(Token), std::runtime_error);

    FakeServer badPage([](const FakeRequest& request) {
        FakeResponse r;
        if (request.Target.find("page") == std::string::npos) {
            r.Body = "[]";
            r.Link = "</projects?page=2>; rel=\"next\"";
        } else {
            r.Body = "{\"not\":\"an array\"}";
        }
        return r;
    });
    EXPECT_THROW(SysMLAPIImplementation(badPage.baseUrl()).getAllProjects(Token), std::runtime_error);
}

TEST(OnlinePagination, ErrorOnLaterPageIsReported) {
    FakeServer server([](const FakeRequest& request) {
        FakeResponse r;
        if (request.Target.find("page") == std::string::npos) {
            r.Body = "[]";
            r.Link = "</projects?page=2>; rel=\"next\"";
        } else {
            r.Status = 500;
            r.Body = "{\"error\":\"boom\"}";
        }
        return r;
    });
    EXPECT_THROW(SysMLAPIImplementation(server.baseUrl()).getAllProjects(Token), SysMLv2::API::EXCEPTIONS::HTTPException);
}

TEST(OnlinePagination, WithoutLinkHeaderBehaviourIsUnchanged) {
    FakeServer server([](const FakeRequest&) {
        FakeResponse r;
        r.Body = json::array({projectJson(0), projectJson(1)}).dump();
        return r;
    });
    SysMLAPIImplementation api(server.baseUrl());
    EXPECT_EQ(api.getAllProjects(Token).size(), 2u);
    EXPECT_EQ(server.requests().size(), 1u);
}
#endif
