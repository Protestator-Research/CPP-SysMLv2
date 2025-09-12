//
// Created by Moritz Herzog on 09.04.25.
//

#include "ProjectUsageService.h"

namespace SysMLv2::API {
    std::vector<std::shared_ptr<SysMLv2::REST::ProjectUsage>> ProjectUsageService::getProjectUsage( std::shared_ptr<SysMLv2::REST::Project> project, std::shared_ptr<SysMLv2::REST::Commit> commit) {

    }

    std::shared_ptr<SysMLv2::REST::Commit> ProjectUsageService::deleteProjectUsage(std::shared_ptr<SysMLv2::REST::Project> project, std::shared_ptr<SysMLv2::REST::Branch> branch, boost::uuids::uuid &projectUsageId) {

    }

    std::shared_ptr<SysMLv2::REST::Commit> ProjectUsageService::createProjectUsage(std::shared_ptr<SysMLv2::REST::Project> project, std::shared_ptr<SysMLv2::REST::Branch> branch, std::shared_ptr<SysMLv2::REST::ProjectUsage> projectUsage) {

    }
}
