//
// Created by Moritz Herzog on 14.12.23.
//
//---------------------------------------------------------
// Constants, Definitions, Pragmas
//---------------------------------------------------------
#pragma once
//---------------------------------------------------------
// External Classes
//---------------------------------------------------------
#include <vector>
#include <string>
#include <memory>
//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include <sysmlv2/service/online/StatusCode.h>
#include <sysmlv2/service/sysmlv2service_global.h>


//---------------------------------------------------------
// Forwarding
//---------------------------------------------------------
namespace SysMLv2::REST {
    class IEntity;
    class Project;
    class Commit;
    class ProjectRequest;
    class CommitRequest;
}

namespace SysMLv2::API {
    /**
     * Implements the Protocol of the SysMLv2 API Standard.
     *
     * All requests are performed with a bearer token that is obtained by loginUserWithPassword. Every method that
     * talks to the server throws SysMLv2::API::EXCEPTIONS::ConnectionError if the connection itself fails and
     * SysMLv2::API::EXCEPTIONS::HTTPException if the server answers with a status outside of 2xx. No state of a
     * request is kept between calls, thus the const-free methods are safe to be called one after another from the
     * same instance.
     * @version 2.0
     * @author Moritz Herzog <herzogm@rptu.de>
     */
    class SYSMLV2SERVICE_EXPORT SysMLAPIImplementation {
    public:
        /**
         * Deleted Constructorr
         */
        SysMLAPIImplementation() = delete;

        /**
         * The constructor that allows the needed server address. The libcurl global initialization is performed
         * exactly once per process (std::call_once) and is intentionally never cleaned up, because
         * curl_global_cleanup is not thread safe and would break other instances or other libcurl users.
         * @param serverAddress Server address as a string, e.g. "http://host:8088/". A missing trailing '/' is added.
         */
        SysMLAPIImplementation(std::string serverAddress);

        /**
         * D-TOR
         */
        virtual ~SysMLAPIImplementation() = default;

        /**
         * Returns a std::vector of all projects that are available within the backend.
         * The data is returned as elements from type std::vector<SysMLv2:Entities:Project*>, please consider the
         * polimorphism of all SysMLV2 elements.
         * @param barrierString The barrier authentication that is provided by the server.
         * @return A list of all Projects.
         * @throws EXCEPTIONS::HTTPException on a non 2xx answer.
         */
        std::vector<std::shared_ptr<SysMLv2::REST::IEntity>> getAllProjects(std::string barrierString);

        /**
         * Uploads a project to the Backend. The owner of the project is always the logged in user, the server ignores
         * an owner given by the client.
         * @param project The new Project you want to upload.
         * @param barrierString The string required for authentication.
         * @param owningGroup The optional group that owns the project. It is sent as "owningGroup" in the JSON body.
         * @return The new Project as the class IEntity
         * @throws EXCEPTIONS::HTTPException on a non 2xx answer.
         * @see SysMLv2::Rest::IEntity
         */
        std::shared_ptr<SysMLv2::REST::IEntity> postProject(std::shared_ptr<SysMLv2::REST::ProjectRequest> project, std::string barrierString, std::string owningGroup = "");

        /**
         * Posts a commit to the Backend to add changes to a project or a branch.
         * @param projectId The UUID of the project.
         * @param commit The commit that is uploaded.
         * @param barrierString The Barrier-String given after login.
         * @return The created commit.
         * @throws EXCEPTIONS::HTTPException on a non 2xx answer.
         */
        std::shared_ptr<SysMLv2::REST::IEntity> postCommit(std::string projectId, std::shared_ptr<SysMLv2::REST::CommitRequest> commit, std::string barrierString);

        /**
         * Downloads a single commit.
         * @param projectId The UUID of the project.
         * @param commitId The UUID of the commit.
         * @param barrierString The Barrier-String given after login.
         * @return The commit.
         * @throws EXCEPTIONS::HTTPException on a non 2xx answer.
         */
        std::shared_ptr<SysMLv2::REST::IEntity> getCommit(std::string projectId, std::string commitId, std::string barrierString);

        /**
         * Downloads and returns all elements of a commit from a specific project.
         * @param projectId The UUID of the Project as a String
         * @param commitId The UUID of the Commit as a String
         * @param barrierString The Barrier-String given after login.
         * @return All elements received from the backend.
         * @throws EXCEPTIONS::HTTPException on a non 2xx answer.
         */
        std::vector<std::shared_ptr<SysMLv2::REST::IEntity>> getAllElementsFromCommit(std::string projectId,std::string commitId, std::string barrierString);

        /**
         * Performs the login at the backend (POST login). Every login creates a separate token on the server, which
         * expires after inactivity. The token and the response are never logged.
         * @param username The username as a string.
         * @param password Password of the user.
         * @return Barrier string (token) after the login.
         * @throws EXCEPTIONS::HTTPException on a non 2xx answer, e.g. 401 for wrong credentials (empty body) or 429
         *         if the login is throttled (see HTTPException::retryAfterSeconds).
         * @throws std::runtime_error if the answer is 2xx but is no JSON object with a string field "bearer".
         */
        std::string loginUserWithPassword(const std::string& username,const std::string& password);

        /**
         * Downloads the version of the backend. The endpoint requires authentication.
         * @param barrierString The Barrier-String given after login.
         * @return The version of the Backend (body of the response).
         * @throws EXCEPTIONS::HTTPException on a non 2xx answer.
         */
        std::string getVersionOfBackend(const std::string& barrierString);

        /**
         * Downloads all the Branches that belong to a specific project with a specific ID.
         * @param projectId Displays the string of the Project UUID
         * @param barrierString The Barrier-String given after login.
         * @return All the Branches.
         * @throws EXCEPTIONS::HTTPException on a non 2xx answer.
         */
        std::vector<std::shared_ptr<SysMLv2::REST::IEntity>> getAllBranchesFroProject(const std::string& projectId, std::string barrierString);

        /**
         * Posts a custom request to the Server.
         * @param endpoint The endpoint everything is pushed to (leading '/' are ignored).
         * @param payload The given payload for the push
         * @param barrierString The current Barrierstring.
         * @return The body of the response.
         * @throws EXCEPTIONS::HTTPException on a non 2xx answer (behavior change: formerly the body was returned).
         */
        std::string postCustomRequest(std::string const& endpoint, std::string const& payload, std::string const& barrierString);

        /**
         * Performs a custom GET request.
         * @param endpoint The endpoint (leading '/' are ignored).
         * @param barrierString The current Barrierstring.
         * @return The body of the response.
         * @throws EXCEPTIONS::HTTPException on a non 2xx answer (behavior change: formerly the body was returned).
         */
        std::string getCustomRequest(std::string const& endpoint, std::string const& barrierString);

        /**
         * Performs a custom PUT request.
         * @param endpoint The endpoint (leading '/' are ignored).
         * @param payload The payload of the request.
         * @param barrierString The current Barrierstring.
         * @return The body of the response.
         * @throws EXCEPTIONS::HTTPException on a non 2xx answer.
         */
        std::string putCustomRequest(std::string const& endpoint, std::string const& payload, std::string const& barrierString);

        /**
         * Performs a custom DELETE request.
         * @param endpoint The endpoint (leading '/' are ignored).
         * @param barrierString The current Barrierstring.
         * @return The body of the response.
         * @throws EXCEPTIONS::HTTPException on a non 2xx answer.
         */
        std::string deleteCustomRequest(std::string const& endpoint, std::string const& barrierString);

    private:
        /**
         * The result of a finished HTTP request.
         */
        struct HttpResponse {
            long Status = 0;
            std::string Body;
            std::string Headers;
        };

        /**
         * The single place where a HTTP request is performed. All state (buffers, curl handle, header list) is local
         * to the call and released by RAII, also if an exception is thrown.
         * @param method "GET", "POST", "PUT" or "DELETE". POST and PUT send the payload, GET and DELETE do not.
         * @param endpoint The endpoint relative to the server address, leading '/' are removed.
         * @param payload The body of the request (POST, PUT).
         * @param barrierString The bearer token, the Authorization header is only sent if it is not empty.
         * @return The response if the status is 2xx.
         * @throws EXCEPTIONS::ConnectionError if curl fails.
         * @throws EXCEPTIONS::HTTPException if the status is outside of 2xx.
         */
        HttpResponse performRequest(const std::string& method, const std::string& endpoint,
                                    const std::string& payload, const std::string& barrierString);

        static size_t WriteBufferCallback(char *contents, size_t size, size_t nmemb, void* userp);

        std::string ServerAddress;
    };
}
