//
// Created by Moritz Herzog on 13.12.23.
//
//---------------------------------------------------------
// Constants, Definitions, Pragmas
//---------------------------------------------------------

//---------------------------------------------------------
// External Classes
//---------------------------------------------------------
#include <utility>
#include <entities/IEntity.h>
#include <entities/Project.h>
#include <entities/Commit.h>
#include <entities/Branch.h>
#include <entities/Element.h>
#include <boost/uuid/uuid_io.hpp>
#include <boost/lexical_cast.hpp>

//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include "BECommunicationService.h"
#include "online/APIImplementations/SysMLAPIImplementation.h"


namespace BACKEND_COMMUNICATION {
    CommunicationService::CommunicationService(std::string serverAddress) {
        ServerAddress = std::move(serverAddress);
    }

    std::vector<SysMLv2::Entities::Element*> CommunicationService::getAllElements(boost::uuids::uuid commitId, boost::uuids::uuid projectId) {
        auto entities = APIImplementation->getAllElementsFromCommit(boost::lexical_cast<std::string>(projectId),boost::lexical_cast<std::string>(commitId), BarrierString);
        std::vector<SysMLv2::Entities::Element*> elements;

        for(auto entitiy : entities)
            elements.push_back(dynamic_cast<SysMLv2::Entities::Element*>(entitiy));

        return elements;
    }

    std::vector<SysMLv2::Entities::Project*> CommunicationService::getAllProjects() {
        auto projects = APIImplementation->getAllProjects(BarrierString);
        std::vector<SysMLv2::Entities::Project*> returnValue;

        for(auto oldProject : projects)
            returnValue.push_back(dynamic_cast<SysMLv2::Entities::Project*>(oldProject));

        return returnValue;
    }

    SysMLv2::Entities::Commit* CommunicationService::getCommitWithId(boost::uuids::uuid , boost::uuids::uuid ) {
        return nullptr;
    }

    SysMLv2::Entities::Commit* CommunicationService::postCommitWithId(boost::uuids::uuid projectId,
	    SysMLv2::Entities::Commit* commit)
    {
        auto commi = APIImplementation->postCommit(boost::lexical_cast<std::string>(projectId), commit, BarrierString);

        SysMLv2::Entities::Commit* returnValue = dynamic_cast<SysMLv2::Entities::Commit*>(commi);
        return returnValue;
    }


    bool CommunicationService::setUserForLoginInBackend(std::string username, std::string password) {
        BarrierString = APIImplementation->loginUserWithPassword(username,password);
        return !BarrierString.empty();
    }

    std::vector<SysMLv2::Entities::Branch*> CommunicationService::getAllBranchesForProjectWithID(boost::uuids::uuid projectId) {
        auto elements = APIImplementation->getAllBrachesFroProject(boost::lexical_cast<std::string>(projectId), BarrierString);

        std::vector<SysMLv2::Entities::Branch*> returnValue;

        for (auto elem : elements)
            returnValue.push_back(dynamic_cast<SysMLv2::Entities::Branch*>(elem));

        return returnValue;
    }

    std::vector<SysMLv2::Entities::Element *>
    CommunicationService::getAllElementsOfCommit(boost::uuids::uuid projectId, boost::uuids::uuid commitId) {
        auto elements = APIImplementation->getAllElementsFromCommit(boost::lexical_cast<std::string>(projectId),boost::lexical_cast<std::string>(commitId), BarrierString);
        std::vector<SysMLv2::Entities::Element*> returnValue;

        for(auto elem : elements)
            returnValue.push_back(dynamic_cast<SysMLv2::Entities::Element*>(elem));

        return returnValue;
    }

    SysMLv2::Entities::Project *
    CommunicationService::postProject(std::string projectName, std::string projectDescription, std::string defaultBranchName) {
        SysMLv2::Entities::Project* project = new SysMLv2::Entities::Project(projectName,projectDescription, defaultBranchName);
        project = dynamic_cast<SysMLv2::Entities::Project*>(APIImplementation->postProject(project, BarrierString));
        return project;
    }


}