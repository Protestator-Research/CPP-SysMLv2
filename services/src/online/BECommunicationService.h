//---------------------------------------------------------
// Created by Moritz Herzog on 13.12.23.
//---------------------------------------------------------
//---------------------------------------------------------
// Constants, Definitions, Pragmas
//---------------------------------------------------------
#pragma once
//---------------------------------------------------------
// External Classes
//---------------------------------------------------------
#include <vector>
#include <string>
#include <boost/uuid/uuid.hpp>
//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
//---------------------------------------------------------
// Forwarding
//---------------------------------------------------------
namespace SysMLv2::Entities {
    class IEntity;
    class Commit;
    class Branch;
    class Project;
    class DigitalTwin;
    class Element;
}

namespace BACKEND_COMMUNICATION{
    class SysMLAPIImplementation;
}

namespace BACKEND_COMMUNICATION {
    /**
     * Abstracts the communication to an interface for the programmer. Allows the communication with the backend.
     * Hereby a connection to the server is opened. With this connection the REST protocol is generated and sent.
     * REST API Specification is here <a href="https://github.com/Systems-Modeling/SysML-v2-API-Services">https://github.com/Systems-Modeling/SysML-v2-API-Services</a>
     * @author Moritz Herzog <herzogm@rptu.de>
     * @version 1.0
     */
    class CommunicationService {
    public:
        /**
         * Constructor allows for the settings for the connection to the AGILA Backend.
         * @param serverAddress Address of the Server including the port and folder. The server address can be an IP address or a url.
         */
        CommunicationService(std::string serverAddress);
        /**
        * Constructor allows for the settings for the connection to the AGILA Backend.
        * @param serverAddress Address of the Server. The server address can be an IP address or a url.
        * @param serverFolder Folder where the Backend is directed to.
        */
        CommunicationService(std::string serverAddress, std::string serverFolder);

        /**
         * D-Tor
         */
        virtual ~CommunicationService() = default;

        /**
         * Creates a connection to the REST endpoint of the given AGILA Backend server,  to get all Elements of a Commit and Project, distinguished by its uuid.
         * @param commitId UUID of the commit
         * @param projectId UUID of the project
         * @return An std::vector of the Elements
         * @see uuid_t
         * @see std::vector
         * @see ENTITIES::Element
         */
        std::vector<SysMLv2::Entities::Element*> getAllElements(boost::uuids::uuid commitId, boost::uuids::uuid projectId);

        /**
         * Creates a connection to the REST endpoint of the given AGILA Backend sever, to get all saved projects within the instance of the Backend
         * @return An std::vector of the Projects
         */
        std::vector<SysMLv2::Entities::Project*> getAllProjects();

        /**
         * Creates online a project with the given Properties.
         * @param projectName The name of the Project.
         * @param projectDescription
         * @param defaultBranchName
         * @return
         */
        SysMLv2::Entities::Project* postProject(std::string projectName, std::string projectDescription, std::string defaultBranchName);

        /**
         * Download all branches for a project, with the projects id.
         * @param projectId UUID ("@id") of the project.
         * @return All Branches of the Project.
         */
        std::vector<SysMLv2::Entities::Branch*> getAllBranchesForProjectWithID(boost::uuids::uuid projectId);

        /**
         * Download the commits with its commit id and project id identifying the specific commit.
         * @param projectId UUID ("@id") of the project.
         * @param commitId UUID ("@id") of the commit.
         * @return The complete Commit
         * @see ENTITIES::Commit
         */
        SysMLv2::Entities::Commit* getCommitWithId(boost::uuids::uuid projectId, boost::uuids::uuid commitId);

        /**
         * Posts a new Commit to the Backend.
         * @param projectId 
         * @param commit 
         * @return 
         */
        SysMLv2::Entities::Commit* postCommitWithId(boost::uuids::uuid projectId, SysMLv2::Entities::Commit* commit);


        /**
         * Downloads all the elements of a specific commit.
         * @param projectId UUID ("@id") of the project.
         * @param commitId UUID ("@id") of the commit.
         * @return All elements of the specific commit.
         * @see ENTITIES::Element
         */
        std::vector<SysMLv2::Entities::Element*> getAllElementsOfCommit(boost::uuids::uuid projectId, boost::uuids::uuid commitId);

        /**
         * Sets and checks internally the user, that the server is connected to.
         * @param username The username or email of the user to login.
         * @param password The password of the user to login.
         * @return
         */
        bool setUserForLoginInBackend(std::string username, std::string password);

    private:
        std::string ServerAddress;

        std::string BarrierString;

        SysMLAPIImplementation* APIImplementation;
    };
}
