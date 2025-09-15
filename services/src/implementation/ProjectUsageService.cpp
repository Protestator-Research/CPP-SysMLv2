//
// Created by Moritz Herzog on 09.04.25.
//

#include "ProjectUsageService.h"

#include "entities/Branch.h"
#include "entities/Project.h"
#include "entities/Commit.h"
#include "entities/DataIdentity.h"
#include "entities/DataVersion.h"
#include "entities/ProjectUsage.h"

#include <boost/uuid/random_generator.hpp>

namespace SysMLv2::API {
    std::vector<std::shared_ptr<SysMLv2::REST::ProjectUsage>> ProjectUsageService::getProjectUsage( std::shared_ptr<SysMLv2::REST::Project> project, std::shared_ptr<SysMLv2::REST::Commit>) {
        return ProjectIdProjectUsageMap.at(project->getId());
    }

    std::shared_ptr<SysMLv2::REST::Commit> ProjectUsageService::deleteProjectUsage(std::shared_ptr<SysMLv2::REST::Project> project, std::shared_ptr<SysMLv2::REST::Branch> branch, boost::uuids::uuid &projectUsageId) {
        std::shared_ptr<SysMLv2::REST::ProjectUsage> requested_usage;
        const auto& usages = ProjectIdProjectUsageMap.at(project->getId());
        for (const auto& usage : usages) {
            if (usage->getId() == projectUsageId) {
                requested_usage = usage;
            }
        }

        ProjectIdProjectUsageMap.at(project->getId()).erase(std::remove(ProjectIdProjectUsageMap.at(project->getId()).begin(), ProjectIdProjectUsageMap.at(project->getId()).end(), requested_usage));

        auto returnValue = std::make_shared<REST::Commit>("Adding Project Usage for " + project->getName(),"Adding Project Usage for " + project->getName(),project);
        auto change = std::make_shared<REST::DataVersion>(std::make_shared<REST::DataIdentity>(projectUsageId), nullptr);
        returnValue->addChange(change);
        return returnValue;
    }

    std::shared_ptr<SysMLv2::REST::Commit> ProjectUsageService::createProjectUsage(std::shared_ptr<SysMLv2::REST::Project> project, std::shared_ptr<SysMLv2::REST::Branch> branch, std::shared_ptr<SysMLv2::REST::ProjectUsage> projectUsage) {
        ProjectIdProjectUsageMap.at(project->getId()).push_back(projectUsage);
        auto returnValue = std::make_shared<REST::Commit>("Adding Project Usage for " + project->getName(),"Adding Project Usage for " + project->getName(),project);
        auto change = std::make_shared<REST::DataVersion>(std::make_shared<REST::DataIdentity>(boost::uuids::random_generator()()), projectUsage);
        returnValue->addChange(change);
        return returnValue;
    }
}
