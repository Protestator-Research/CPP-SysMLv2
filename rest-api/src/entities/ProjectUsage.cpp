//
// Created by Moritz Herzog on 27.02.24.
//

#include "ProjectUsage.h"
#include "Commit.h"
#include "Project.h"

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