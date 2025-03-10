//
// Created by Moritz Herzog on 27.02.24.
//

#include "ProjectUsage.h"
#include "Commit.h"
#include "Project.h"

namespace SysMLv2 {
    namespace Entities {
        ProjectUsage::ProjectUsage() {

        }

        ProjectUsage::~ProjectUsage() {
        }

        Project * ProjectUsage::getUsedProject() const {
            return UsedProjectCommit->getOwningProject();
        }

        void ProjectUsage::setUsedProjectCommit(SysMLv2::Entities::Commit *usedCommit) {
            UsedProjectCommit = usedCommit;
        }

        Commit* ProjectUsage::getUsedProjectCommit() const {
            return UsedProjectCommit;
        }
    } // Entities
} // SysMLv2