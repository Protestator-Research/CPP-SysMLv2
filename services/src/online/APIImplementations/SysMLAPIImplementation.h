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
#include <curl/curl.h>
//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include "StatusCode.h"

//---------------------------------------------------------
// Forwarding
//---------------------------------------------------------
namespace SysMLv2::Entities {
    class IEntity;
    class Project;
    class Commit;
}

namespace BACKEND_COMMUNICATION {
    /**
     * Implements the Protocol of the SysMLv2 API Standard.
     * @version 1.1
     * @author Moritz Herzog <herzogm@rptu.de>
     */
    class SysMLAPIImplementation {
    public:
        /**
         * Deleted Constructorr
         */
        SysMLAPIImplementation() = delete;

        /**
         * The constructor that allows the needed server address.
         * @param serverAddress Server address as a string.
         */
        SysMLAPIImplementation(std::string serverAddress);

        /**
         * D-TOR
         */
        virtual ~SysMLAPIImplementation();

        /**
         * Returns a std::vector of all projects that are available within the backend.
         * The data is returned as elements from type std::vector<SysMLv2:Entities:Project*>, please consider the
         * polimorphism of all SysMLV2 elements.
         * @param barrierString The barrier authentication that is provided by the server.
         * @return A list of all Projects.
         */
        std::vector<std::shared_ptr<SysMLv2::Entities::IEntity>> getAllProjects(std::string barrierString);

        /**
         *
         * @param project 
         * @param barrierString 
         * @return 
         */
        std::shared_ptr<SysMLv2::Entities::IEntity> postProject(std::shared_ptr<SysMLv2::Entities::Project> project, std::string barrierString);

        /**
         * 
         * @param projectId 
         * @param commit 
         * @param barrierString 
         * @return 
         */
        std::shared_ptr<SysMLv2::Entities::IEntity> postCommit(std::string projectId, std::shared_ptr<SysMLv2::Entities::Commit> commit, std::string barrierString);

        /**
         * Downloads and returns all elements of a commit from a specific project.
         * @param projectId The UUID of the Project as a String
         * @param commitId The UUID of the Commit as a String
         * @param barrierString The Barrier-String given after login.
         * @return All elements received from the backend.
         */
        std::vector<std::shared_ptr<SysMLv2::Entities::IEntity>> getAllElementsFromCommit(std::string projectId,std::string commitId, std::string barrierString);

        /**
         * Performs the login of the digital twin client and server at the backend. This login is also automatically
         * algorithmically changed dependent on the version of the Backend.
         * @param username The username as a string.
         * @param password Password of the user.
         * @return Barrier string after the login.
         */
        std::string loginUserWithPassword(const std::string& username,const std::string& password);

        /**
         * Downloads the version of the backend. Version 3 of the backend has an endpoint to download the version of
         * the Backend. Whereas the backend Version 2.X does not have the option. Thus the error is returning version 2.x.
         * @return The version of the Backend.
         */
        std::string getVersionOfBackend();

        /**
         * Downloads all the Branches that belong to a specific project with a specific ID.
         * @param projectId Displays the string of the Project UUID
         * @return JSON of the all the Branches.
         */
        std::vector<std::shared_ptr<SysMLv2::Entities::IEntity>> getAllBranchesFroProject(const std::string& projectId, std::string barrierString);

    protected:
        /**
         * Sets up the server connection and creates the necessary CURL calls.
         * @param urlAppendix The appendix to the url that is required to access the different folders for the Standard.
         * @param barrierString The Barrier login string, this string might be required for login.
         * @param postPayload The payload that is posted to the server.
         * @return The CURL connection resulting from the properties.
         */
        CURL* setUpServerConnection(const char* urlAppendix, const char* barrierString, const char* postPayload);

        /**
         * In this method a internal resolvement of the HTTP connection error is tried. If this fails the exception is rethrown.
         * @param httpErrorCode The HTTP error code that was thrown.
         * @param instance The curl instance pointer.
         * @return Returns an internal status code that can be referenced externally.
         */
        INTERNAL_STATUS_CODE tryToResolveHTTPError(long httpErrorCode, void* instance);

        /**
         * Performs the login in to the AGILA backend from Version 3 and upwards
         * @param username The username given as a string.
         * @param passwod The password of the user given as a string.
         * @return The barrier string from the server.
         */
        std::string loginToBackendVersion3(std::string const& username, std::string const& passwod);

    private:
        static size_t WriteBufferCallback(char *contents, size_t size, size_t nmemb, void* userp);

        std::string ServerAddress;
        std::string ReturnedHeaderData;
        std::string Data;
        struct curl_slist *HeaderList = NULL;
    };
}

