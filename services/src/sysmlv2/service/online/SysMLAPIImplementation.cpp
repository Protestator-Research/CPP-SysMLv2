//
// Created by Moritz Herzog on 14.12.23.
//
//---------------------------------------------------------
// Constants, Definitions, Pragmas
//---------------------------------------------------------

//---------------------------------------------------------
// External Classes
//---------------------------------------------------------
#include <sstream>
#include <iostream>
#include <fstream>
#include <cstring>
#include <curl/curl.h>
#include <nlohmann/json.hpp>


//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include <sysmlv2/service/online/SysMLAPIImplementation.h>
#include <sysmlv2/service/online/NotEnoughMemoryError.h>
#include <sysmlv2/service/online/ConnectionError.h>
#include <sysmlv2/service/online/HttpReturnCodes.h>
#include <sysmlv2/service/online/HttpException.h>
#include <sysmlv2/rest/serialization/SysMLv2Deserializer.h>
#include <sysmlv2/rest/entities/Project.h>
#include <sysmlv2/rest/entities/Commit.h>


namespace SysMLv2::API {

    SysMLAPIImplementation::SysMLAPIImplementation(std::string serverAddress) {
        curl_global_init(CURL_GLOBAL_ALL);

        ServerAddress = serverAddress;
    }

    SysMLAPIImplementation::~SysMLAPIImplementation() {
        curl_global_cleanup();
    }

    std::string SysMLAPIImplementation::loginUserWithPassword(std::string const& username, std::string const& passwod) {
        if(getVersionOfBackend()=="2.X")
            return loginToBackendVersion2(username,passwod);
        else
            return loginToBackendVersion3(username,passwod);
    }

    std::vector<std::shared_ptr<SysMLv2::REST::IEntity>> SysMLAPIImplementation::getAllProjects(std::string barrierString) {
        std::vector<std::shared_ptr<SysMLv2::REST::IEntity>> returnValue;
        CURLcode ServerResult;
        //std::cout << "getAllProjects: "<<ServerAddress<<"projects"<<std::endl;
        auto serverConnection = setUpServerConnection("projects", barrierString.c_str(), "");
        //std::cout<<"setUpServerConnection"<<std::endl;
        ServerResult = curl_easy_perform(serverConnection);
        //std::cout<<"curl_easy_perform: " << ServerResult<<std::endl;
        if (ServerResult == CURLE_OK) {
            long httpResult;
            curl_easy_getinfo(serverConnection, CURLINFO_RESPONSE_CODE, &httpResult);
            //std::cout<<"curl_easy_getinfo: " << httpResult<<std::endl;

            if(tryToResolveHTTPError(httpResult, serverConnection)==INTERNAL_STATUS_CODE::SUCCESS){
                //std::cout<<"getAllProjects: "<<Data<<std::endl;
                returnValue = SysMLv2::SysMLv2Deserializer::deserializeJsonArray(Data);
            }

        } else {
            throw SysMLv2::API::EXCEPTIONS::ConnectionError(
                    static_cast<SysMLv2::API::EXCEPTIONS::CONNECTION_ERROR_TYPE>(ServerResult));
        }
        curl_slist_free_all(HeaderList);
        curl_easy_cleanup(serverConnection);

        return returnValue;
    }

    CURL *SysMLAPIImplementation::setUpServerConnection(const char* urlAppendix, const char* barrierString, const char* postPayload) {
        ReturnedHeaderData = "";
        Data = "";
        HeaderList = NULL;

        CURL* serverConnection = curl_easy_init();

        if(!serverConnection)
            throw SysMLv2::API::EXCEPTIONS::NotEnoughMemoryError();

        char authorizationHeaderBeginning[] ="Authorization: Bearer ";
        char * authorizationHeader = new char[std::strlen(authorizationHeaderBeginning)+std::strlen(barrierString)+1];
        std::strcpy(authorizationHeader,authorizationHeaderBeginning);
        std::strcat(authorizationHeader,barrierString);

        const char* serverAddress = ServerAddress.c_str();
        char* completeServerAddress = new char[std::strlen(serverAddress)+std::strlen(urlAppendix)+1];
        
        std::strcpy(completeServerAddress,serverAddress);
        std::strcat(completeServerAddress,urlAppendix);

        std::cout << "Server Address: " << completeServerAddress << std::endl;

        if(std::strcmp(barrierString, "")!=0)
            HeaderList = curl_slist_append(HeaderList, authorizationHeader);

        HeaderList = curl_slist_append(HeaderList,"Content-Type: application/json");

        curl_easy_setopt(serverConnection, CURLOPT_URL, completeServerAddress);
        curl_easy_setopt(serverConnection, CURLOPT_WRITEFUNCTION, WriteBufferCallback);
        curl_easy_setopt(serverConnection, CURLOPT_WRITEDATA, &Data);
        curl_easy_setopt(serverConnection, CURLOPT_HEADERFUNCTION, WriteBufferCallback);
        curl_easy_setopt(serverConnection, CURLOPT_HEADERDATA, &ReturnedHeaderData);
        curl_easy_setopt(serverConnection, CURLOPT_HTTPHEADER, HeaderList);

        if(std::strcmp(postPayload, "")!=0) {
            char* payload = new char[std::strlen(postPayload)+1];
            std::strcpy(payload,postPayload);
            curl_easy_setopt(serverConnection, CURLOPT_POSTFIELDS, payload);
        }

        return serverConnection;
    }

    INTERNAL_STATUS_CODE SysMLAPIImplementation::tryToResolveHTTPError(long httpErrorCode, void* instance) {
        if(httpErrorCode>STANDARDS::HTTP::HTTP_PROPRIATARY)
            throw SysMLv2::API::EXCEPTIONS::HTTPException(httpErrorCode);

        switch (httpErrorCode) {
            case STANDARDS::HTTP::HTTP_CONTINUE:
            case STANDARDS::HTTP::HTTP_PROTOCOL_SWITCH:
            case STANDARDS::HTTP::HTTP_PROCESSING:
            case STANDARDS::HTTP::HTTP_EARLY_HINTS:
            case STANDARDS::HTTP::HTTP_OK:
            case STANDARDS::HTTP::HTTP_CREATED:
            case STANDARDS::HTTP::HTTP_ACCEPTED:
            case STANDARDS::HTTP::HTTP_NON_AUTHORITATIVE_INFORMATION:
            case STANDARDS::HTTP::HTTP_NO_CONTENT:
            case STANDARDS::HTTP::HTTP_PARTIAL_CONTENT:
            case STANDARDS::HTTP::HTTP_IM_USED:
                return INTERNAL_STATUS_CODE::SUCCESS;

            case STANDARDS::HTTP::HTTP_MULTI_STATUS:
            case STANDARDS::HTTP::HTTP_RESET_CONTENT:
                return INTERNAL_STATUS_CODE::RE_DO;

            case STANDARDS::HTTP::HTTP_MULTIPLE_CHOICES:
            case STANDARDS::HTTP::HTTP_MOVED_PERMANENTLY:
            case STANDARDS::HTTP::HTTP_FOUND:
            case STANDARDS::HTTP::HTTP_SEE_OTHER:
            case STANDARDS::HTTP::HTTP_TEMPORARY_REDIRECT:
            case STANDARDS::HTTP::HTTP_PERMANENT_REDIRECT:
                curl_easy_getinfo(instance, CURLINFO_REDIRECT_URL, &ServerAddress);
                return INTERNAL_STATUS_CODE::RE_DO;

            case STANDARDS::HTTP::HTTP_NOT_MODIFIED:
                return INTERNAL_STATUS_CODE::SUCCESS;

            case STANDARDS::HTTP::HTTP_USE_PROXY:
            case STANDARDS::HTTP::HTTP_SWITCH_PROXY:
                //TODO Needs more consideration
                break;

            case STANDARDS::HTTP::HTTP_ALREADY_REPORTED:
            case STANDARDS::HTTP::HTTP_BAD_REQUEST:
            case STANDARDS::HTTP::HTTP_UNAUTHORIZED:
            case STANDARDS::HTTP::HTTP_PAYMENT_REQUIRED:
            case STANDARDS::HTTP::HTTP_FORBIDDEN:
            case STANDARDS::HTTP::HTTP_NOT_FOUND:
            case STANDARDS::HTTP::HTTP_METHOD_NOT_ALLOWED:
            case STANDARDS::HTTP::HTTP_NOT_ACCEPTABLE:
            case STANDARDS::HTTP::HTTP_PROXY_AUTHENTICATION_REQUIRED:
            case STANDARDS::HTTP::HTTP_REQUEST_TIMEOUT:
            case STANDARDS::HTTP::HTTP_CONFLICT:
            case STANDARDS::HTTP::HTTP_GONE:
            case STANDARDS::HTTP::HTTP_LENGTH_REQUIRED:
            case STANDARDS::HTTP::HTTP_PRECONDITION_FIELD:
            case STANDARDS::HTTP::HTTP_PAYLOAD_TOO_LARGE:
            case STANDARDS::HTTP::HTTP_URI_TOO_LONG:
            case STANDARDS::HTTP::HTTP_UNSUPPORTED_MEDIA_TYPE:
            case STANDARDS::HTTP::HTTP_RANGE_NOT_SATISFIABLE:
            case STANDARDS::HTTP::HTTP_EXPECTATION_FAILED:
            case STANDARDS::HTTP::HTTP_MISDIRECTED_REQUEST:
            case STANDARDS::HTTP::HTTP_UNPROCESSABLE_ENTITY:
            case STANDARDS::HTTP::HTTP_LOCKED:
            case STANDARDS::HTTP::HTTP_FAILED_DEPENDENCY:
            case STANDARDS::HTTP::HTTP_TOO_EARLY:
            case STANDARDS::HTTP::HTTP_UPGRADE_REQUIRED:
            case STANDARDS::HTTP::HTTP_PRECONDITION_REQUIRED:
            case STANDARDS::HTTP::HTTP_TOO_MANY_REQUESTS:
            case STANDARDS::HTTP::HTTP_REQUEST_HEADER_FIELDS:
            case STANDARDS::HTTP::HTTP_UNAVAILABLE_FOR_LEGAL_REASONS:
            case STANDARDS::HTTP::HTTP_INTERNAL_SERVER_ERROR:
            case STANDARDS::HTTP::HTTP_NOT_IMPLEMENTED:
            case STANDARDS::HTTP::HTTP_BAD_GATEWAY:
            case STANDARDS::HTTP::HTTP_SERVICE_UNAVAILABLE:
            case STANDARDS::HTTP::HTTP_GATEWAY_TIMEOUT:
            case STANDARDS::HTTP::HTTP_VERSION_NOT_SUPPORTED:
            case STANDARDS::HTTP::HTTP_VARIANT_ALSO_NEGOTIATES:
            case STANDARDS::HTTP::HTTP_INSUFFCIENT_STORAGE:
            case STANDARDS::HTTP::HTTP_LOOP_DETECTED:
            case STANDARDS::HTTP::HTTP_BANDWIDTH_LIMIT:
            case STANDARDS::HTTP::HTTP_NOT_EXTENDED:
            case STANDARDS::HTTP::HTTP_NETWORK_AUTHENTICATION_REQUIRED:
                throw SysMLv2::API::EXCEPTIONS::HTTPException(httpErrorCode);
        }

        return INTERNAL_STATUS_CODE::THROW_ERROR;
    }

    std::vector<std::shared_ptr<SysMLv2::REST::IEntity>>
    SysMLAPIImplementation::getAllElementsFromCommit(std::string projectId, std::string commitId, std::string barrierString) {

        std::vector<std::shared_ptr<SysMLv2::REST::IEntity>> returnValue;
        CURLcode ServerResult;

        std::string urlAppendix = "projects/" + projectId + "/commits/" + commitId + "/elements";

        auto serverConnection = setUpServerConnection(urlAppendix.c_str(), barrierString.c_str(), "");

        ServerResult = curl_easy_perform(serverConnection);

        if (ServerResult == CURLE_OK) {
            long httpResult;
            curl_easy_getinfo(serverConnection, CURLINFO_RESPONSE_CODE, &httpResult);

            if(tryToResolveHTTPError(httpResult, serverConnection)==INTERNAL_STATUS_CODE::SUCCESS){
                returnValue = SysMLv2::SysMLv2Deserializer::deserializeJsonArray(Data);
            }

        } else {
            throw SysMLv2::API::EXCEPTIONS::ConnectionError(
                    static_cast<SysMLv2::API::EXCEPTIONS::CONNECTION_ERROR_TYPE>(ServerResult));
        }
        curl_slist_free_all(HeaderList);
        curl_easy_cleanup(serverConnection);

        return returnValue;
    }

    std::string SysMLAPIImplementation::getVersionOfBackend() {
        std::string returnValue = "2.X";

        CURLcode ServerResult;

        std::string urlAppendix = "version";

        auto serverConnection = setUpServerConnection(urlAppendix.c_str(), "", "");
        ServerResult = curl_easy_perform(serverConnection);
        std::cout << "Server Result at get Version:" << ServerResult <<std::endl;
        if(ServerResult == CURLE_OK) {
            long httpResult;
            curl_easy_getinfo(serverConnection, CURLINFO_RESPONSE_CODE, &httpResult);

            std::cout << "data at get Version:" << Data << std::endl;

            if(httpResult==STANDARDS::HTTP::HTTP_OK)
                returnValue = Data;
        }

        if (returnValue == "2.X")
            ServerAddress += "agila-server/";

        curl_slist_free_all(HeaderList);
        curl_easy_cleanup(serverConnection);

        return returnValue;
    }

    std::string
    SysMLAPIImplementation::loginToBackendVersion3(const std::string &username, const std::string &passwod) {
        std::cout << "Login Version 3" << std::endl;
        std::string barrierString = "";

        CURLcode ServerResult;
        nlohmann::json jsonData;
        jsonData["username"] = username;
        jsonData["password"] = passwod;


        auto serverConnection = setUpServerConnection("login", "", jsonData.dump().c_str());

        ServerResult = curl_easy_perform(serverConnection);
        std::cout << "Server Result: " << ServerResult << std::endl;
        if (ServerResult == CURLE_OK) {
            std::cout << "Server result at Login" << Data << std::endl;
            nlohmann::json resultJson = nlohmann::json::parse(Data);
            barrierString = resultJson["barrierString"];
        } else {
            throw SysMLv2::API::EXCEPTIONS::ConnectionError(
                    static_cast<SysMLv2::API::EXCEPTIONS::CONNECTION_ERROR_TYPE>(ServerResult));
        }

        curl_easy_cleanup(serverConnection);
        return barrierString;
    }

    std::vector<std::shared_ptr<SysMLv2::REST::IEntity>> SysMLAPIImplementation::getAllBranchesFroProject(const std::string& projectId, std::string barrierString)
    {
        std::vector<std::shared_ptr<SysMLv2::REST::IEntity>> returnValue;
        CURLcode ServerResult;

        std::string urlAppendix = "projects/" + projectId + "/branches";

        auto serverConnection = setUpServerConnection(urlAppendix.c_str(), barrierString.c_str(), "");

        ServerResult = curl_easy_perform(serverConnection);

        if (ServerResult == CURLE_OK) {
            long httpResult;
            curl_easy_getinfo(serverConnection, CURLINFO_RESPONSE_CODE, &httpResult);

            if (tryToResolveHTTPError(httpResult, serverConnection) == INTERNAL_STATUS_CODE::SUCCESS) {
                returnValue = SysMLv2::SysMLv2Deserializer::deserializeJsonArray(Data);
            }

        }
        else {
            throw SysMLv2::API::EXCEPTIONS::ConnectionError(
                static_cast<SysMLv2::API::EXCEPTIONS::CONNECTION_ERROR_TYPE>(ServerResult));
        }
        curl_slist_free_all(HeaderList);
        curl_easy_cleanup(serverConnection);

        return returnValue;
    }

    std::shared_ptr<SysMLv2::REST::IEntity>
    SysMLAPIImplementation::postProject(std::shared_ptr<SysMLv2::REST::Project> project, std::string barrierString) {
        std::shared_ptr<SysMLv2::REST::IEntity> returnValue = nullptr;
        CURLcode ServerResult;

        std::string urlAppendix = "projects";

        auto serverConnection = setUpServerConnection(urlAppendix.c_str(), barrierString.c_str(), project->serializeToJson().c_str());

        ServerResult = curl_easy_perform(serverConnection);

        if (ServerResult == CURLE_OK) {
            long httpResult;
            curl_easy_getinfo(serverConnection, CURLINFO_RESPONSE_CODE, &httpResult);

            if (tryToResolveHTTPError(httpResult, serverConnection) == INTERNAL_STATUS_CODE::SUCCESS) {
                returnValue = SysMLv2::SysMLv2Deserializer::deserializeJsonString(Data);
            }

        }
        else {
            throw SysMLv2::API::EXCEPTIONS::ConnectionError(
                    static_cast<SysMLv2::API::EXCEPTIONS::CONNECTION_ERROR_TYPE>(ServerResult));
        }
        curl_slist_free_all(HeaderList);
        curl_easy_cleanup(serverConnection);

        return returnValue;

    }

    std::shared_ptr<SysMLv2::REST::IEntity> SysMLAPIImplementation::postCommit(std::string projectId,
	    std::shared_ptr<SysMLv2::REST::Commit> commit, std::string barrierString)
    {
        std::shared_ptr<SysMLv2::REST::IEntity> returnValue = nullptr;
        CURLcode ServerResult;

        std::string urlAppendix = "projects/" + projectId + "/commits";
        std::string jsonDump = commit->serializeToJson();
        std::cout << "Commit Data" << jsonDump << std::endl;

        auto serverConnection = setUpServerConnection(urlAppendix.c_str(), barrierString.c_str(), jsonDump.c_str());

        ServerResult = curl_easy_perform(serverConnection);

        if (ServerResult == CURLE_OK) {
            long httpResult;
            curl_easy_getinfo(serverConnection, CURLINFO_RESPONSE_CODE, &httpResult);
            std::cout<<"Data Result: "<<Data<<std::endl;
            if (tryToResolveHTTPError(httpResult, serverConnection) == INTERNAL_STATUS_CODE::SUCCESS) {
                returnValue = SysMLv2::SysMLv2Deserializer::deserializeJsonString(Data);
            }

        }
        else {
            throw SysMLv2::API::EXCEPTIONS::ConnectionError(
                static_cast<SysMLv2::API::EXCEPTIONS::CONNECTION_ERROR_TYPE>(ServerResult));
        }
        curl_slist_free_all(HeaderList);
        curl_easy_cleanup(serverConnection);

        return returnValue;
    }

    size_t SysMLAPIImplementation::WriteBufferCallback(char *contents, size_t size, size_t nmemb, void* userp){
        ((std::string*)userp)->append((char*)contents, size * nmemb);
        return size * nmemb;
    }

    std::shared_ptr<SysMLv2::REST::IEntity>
    SysMLAPIImplementation::getCommit(std::string projectId, std::string commitId, std::string barrierString) {
        std::shared_ptr<SysMLv2::REST::IEntity> returnValue;
        CURLcode ServerResult;

        std::string urlAppendix = "projects/" + projectId + "/commits/" + commitId;

        auto serverConnection = setUpServerConnection(urlAppendix.c_str(), barrierString.c_str(), "");

        ServerResult = curl_easy_perform(serverConnection);

        if (ServerResult == CURLE_OK) {
            long httpResult;
            curl_easy_getinfo(serverConnection, CURLINFO_RESPONSE_CODE, &httpResult);

            if (tryToResolveHTTPError(httpResult, serverConnection) == INTERNAL_STATUS_CODE::SUCCESS) {
                returnValue = SysMLv2::SysMLv2Deserializer::deserializeJsonString(Data);
            }

        }
        else {
            throw SysMLv2::API::EXCEPTIONS::ConnectionError(
                    static_cast<SysMLv2::API::EXCEPTIONS::CONNECTION_ERROR_TYPE>(ServerResult));
        }
        curl_slist_free_all(HeaderList);
        curl_easy_cleanup(serverConnection);

        return returnValue;
    }

    std::string
    SysMLAPIImplementation::loginToBackendVersion2(const std::string &username, const std::string &password) {
        std::cout << "Version 2 Login" <<std::endl;
        std::string barrierString;

        CURLcode ServerResult;
        nlohmann::json jsonData;
        jsonData["email"] = username;
        jsonData["password"] = password;


        auto serverConnection = setUpServerConnection("users/login", "", jsonData.dump().c_str());

        ServerResult = curl_easy_perform(serverConnection);
        if (ServerResult == CURLE_OK) {
            auto splittedAnswer = splittString(Data, ' ');
            barrierString = splittedAnswer[2];
        } else {
            throw SysMLv2::API::EXCEPTIONS::ConnectionError(
                    static_cast<SysMLv2::API::EXCEPTIONS::CONNECTION_ERROR_TYPE>(ServerResult));
        }

        curl_easy_cleanup(serverConnection);
        return barrierString;
    }

    std::string SysMLAPIImplementation::postCustomRequest(std::string const &endpoint, std::string const &payload,
        std::string const &barrierString) {
        CURLcode ServerResult;

        auto serverConnection = setUpServerConnection(endpoint.c_str(), barrierString.c_str(), payload.c_str());

        ServerResult = curl_easy_perform(serverConnection);

        if (ServerResult == CURLE_OK) {
            long httpResult;
            curl_easy_getinfo(serverConnection, CURLINFO_RESPONSE_CODE, &httpResult);
        }
        else {
            throw SysMLv2::API::EXCEPTIONS::ConnectionError(
                    static_cast<SysMLv2::API::EXCEPTIONS::CONNECTION_ERROR_TYPE>(ServerResult));
        }
        curl_slist_free_all(HeaderList);
        curl_easy_cleanup(serverConnection);

        return Data;
    }

    std::vector<std::string> SysMLAPIImplementation::splittString(std::string value, char delimiter) {
        std::vector<std::string> returnValue;
        std::istringstream stream(value);
        std::string internal;

        while(std::getline(stream,internal, delimiter))
            returnValue.push_back(internal);

        return returnValue;
    }
}
