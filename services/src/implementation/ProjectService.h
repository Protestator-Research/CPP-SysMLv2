//
// Created by Moritz Herzog on 09.04.25.
//

#ifndef SYSML_PROJECTSERVICE_H
#define SYSML_PROJECTSERVICE_H

#include "../interfaces/IProjectService.h"
#include <vector>
#include <map>
#include <memory>
#include <boost/uuid/uuid.hpp>

namespace SysMLv2::API {
    /**
     *
     */
    class ProjectService : public IProjectService{
    public:
        ProjectService();
        virtual ~ProjectService() = default;

        std::vector<std::shared_ptr<SysMLv2::Entities::Project>> getProjects() override;

        std::shared_ptr<SysMLv2::Entities::Project> getProjectById(boost::uuids::uuid projectId) override;

        std::shared_ptr<SysMLv2::Entities::Project> createProject(std::string projectName, std::string description = "") override;

        std::shared_ptr<SysMLv2::Entities::Project> updateProject(boost::uuids::uuid projectId, std::string projectName = "", std::string description = "", SysMLv2::Entities::Branch* branch = nullptr) override;

        std::shared_ptr<SysMLv2::Entities::Project> deleteProject(boost::uuids::uuid projectId) override;
    protected:
        std::map<boost::uuids::uuid,std::shared_ptr<SysMLv2::Entities::Project>> ProjectMap;
    };
}

#endif //SYSML_PROJECTSERVICE_H
