//
// Created by Moritz Herzog on 09.04.25.
//

#include "ProjectService.h"
#include <entities/Project.h>

namespace SysMLv2::API {
    ProjectService::ProjectService() {

    }

    std::vector<std::shared_ptr<SysMLv2::Entities::Project>> ProjectService::getProjects() {
        std::vector<std::shared_ptr<SysMLv2::Entities::Project>> returnValue;
        for(const auto & value : ProjectMap) {
            returnValue.push_back(value.second);
        }
        return returnValue;
    }

    std::shared_ptr<SysMLv2::Entities::Project> ProjectService::getProjectById(boost::uuids::uuid id) {
        if(ProjectMap.count(id)>0)
            return ProjectMap[id];
        else
            return nullptr;
    }

    std::shared_ptr<SysMLv2::Entities::Project>
    ProjectService::createProject(std::string projectName, std::string description) {
        auto project = std::make_shared<SysMLv2::Entities::Project>(projectName,description,"main");
        ProjectMap[project->getId()] = project;
        return project;
    }

    std::shared_ptr<SysMLv2::Entities::Project>
    ProjectService::updateProject(boost::uuids::uuid id, std::string name, std::string description, std::shared_ptr<SysMLv2::Entities::Branch> defaultBranch) {
        if(ProjectMap.count(id)>0) {
            auto& project = ProjectMap[id];
            project->setName(name);
            if(!description.empty())
                project->setDescription(description);
            if(defaultBranch!= nullptr)
                project->setDefaultBranch(defaultBranch);
            return project;
        }
        else
            return nullptr;
    }

    std::shared_ptr<SysMLv2::Entities::Project> ProjectService::deleteProject(boost::uuids::uuid id) {
        auto project = ProjectMap[id];
        ProjectMap.erase(id);
        return project;
    }

}
