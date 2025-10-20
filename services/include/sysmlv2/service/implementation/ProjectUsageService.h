//
// Created by Moritz Herzog on 09.04.25.
//

#ifndef SYSML_PROJECTUSAGESERVICE_H
#define SYSML_PROJECTUSAGESERVICE_H

#include <sysmlv2/service/interfaces/IProjectUsageService.h>
#include <boost/uuid/uuid.hpp>
#include <map>

namespace SysMLv2::API {
    class ProjectUsageService : public IProjectUsageService {
    public:
        ProjectUsageService() = default;
        ~ProjectUsageService() override = default;

        std::vector<std::shared_ptr<SysMLv2::REST::ProjectUsage>> getProjectUsage(std::shared_ptr<SysMLv2::REST::Project> project, std::shared_ptr<SysMLv2::REST::Commit> commit) override;

        std::shared_ptr<SysMLv2::REST::Commit> deleteProjectUsage(std::shared_ptr<SysMLv2::REST::Project> project, std::shared_ptr<SysMLv2::REST::Branch> branch, boost::uuids::uuid& projectUsageId) override;

        std::shared_ptr<SysMLv2::REST::Commit> createProjectUsage(std::shared_ptr<SysMLv2::REST::Project> project, std::shared_ptr<SysMLv2::REST::Branch> branch, std::shared_ptr<SysMLv2::REST::ProjectUsage> projectUsage) override;

    protected:
        std::map<boost::uuids::uuid, std::vector<std::shared_ptr<SysMLv2::REST::ProjectUsage>>> ProjectIdProjectUsageMap;
    };
}

#endif //SYSML_PROJECTUSAGESERVICE_H
