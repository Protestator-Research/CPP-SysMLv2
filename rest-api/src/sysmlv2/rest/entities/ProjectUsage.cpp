//
// Created by Moritz Herzog on 27.02.24.
//

#include <sysmlv2/rest/entities/ProjectUsage.h>
#include <sysmlv2/rest/entities/Commit.h>
#include <sysmlv2/rest/entities/Project.h>

namespace SysMLv2 {
    namespace REST {
        ProjectUsage::ProjectUsage() {

        }

        ProjectUsage::~ProjectUsage() {
        }

        std::shared_ptr<Project> ProjectUsage::getUsedProject() const {
            return UsedProjectCommit->getOwningProject();
        }

        void ProjectUsage::setUsedProjectCommit(std::shared_ptr<Commit> usedCommit) {
            UsedProjectCommit = usedCommit;
        }

        std::shared_ptr<Commit> ProjectUsage::getUsedProjectCommit() const {
            return UsedProjectCommit;
        }
    } // Entities
} // SysMLv2