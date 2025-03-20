//
// Created by Moritz Herzog on 27.02.24.
//
//---------------------------------------------------------
// Constants, Definitions, Pragmas
//---------------------------------------------------------
#ifndef DIGITALTWIN_PROJECTUSAGE_H
#define DIGITALTWIN_PROJECTUSAGE_H
//---------------------------------------------------------
// External Classes
//---------------------------------------------------------
#include <memory>
//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include "Data.h"
//---------------------------------------------------------
// Forwarding
//---------------------------------------------------------
namespace SysMLv2::Entities {
    class Commit;
    class Project;
}

namespace SysMLv2::Entities {
    /**
     * Defines the Project Usage according to the SysML v2 Standard
     * @author Moritz Herzog
     */
    class ProjectUsage : public Data {
    public:
        /**
         * Constructor
         */
        ProjectUsage();

        ~ProjectUsage() override;

        /**
         * Returns the commit of the given Project.
         * @return the Related Commit
         */
        std::shared_ptr<Commit> getUsedProjectCommit() const;

        /**
         * Allows to set the used Project commit.
         * @param usedCommit used Project commit.
         */
        void setUsedProjectCommit(std::shared_ptr<Commit> usedCommit);

        /**
         * Returns the connected project according to the SysML v2 Standard
         * @see Commit
         * @return The project from the connected commit.
         */
        std::shared_ptr<Project> getUsedProject() const;
    private:
        std::shared_ptr<Commit> UsedProjectCommit;

    };

} // SysMLv2

#endif //DIGITALTWIN_PROJECTUSAGE_H
