//
// Created by Moritz Herzog on 27.02.24.
//
//---------------------------------------------------------
// Constants, Definitions, Pragmas
//---------------------------------------------------------
#pragma once
//---------------------------------------------------------
// External Classes
//---------------------------------------------------------
#include <memory>
//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include <sysmlv2/rest/entities/Data.h>
#include <sysmlv2/rest/sysmlv2rest_global.h>
//---------------------------------------------------------
// Forwarding
//---------------------------------------------------------
namespace SysMLv2::REST {
    class Commit;
    class Project;
}

namespace SysMLv2::REST {
    /**
     * Defines the Project Usage according to the SysML v2 Standard
     * @author Moritz Herzog
     */
    class SYSMLV2REST_EXPORT ProjectUsage : public Data {
    public:
        /**
         * Constructor
         */
        ProjectUsage() = delete;

        /**
         *
         * @param commit
         */
        explicit ProjectUsage(const std::shared_ptr<SysMLv2::REST::Commit>& commit);

        /**
         *
         * @param jsonString
         */
        ProjectUsage(std::string jsonString);

        ~ProjectUsage() override = default;

        /**
         * Returns the commit of the given Project.
         * @return the Related Commit
         */
        [[nodiscard]] std::shared_ptr<Commit> getUsedProjectCommit() const;

        /**
         * Allows to set the used Project commit.
         * @param usedCommit used Project commit.
         */
        void setUsedProjectCommit(const std::shared_ptr<Commit>& usedCommit);

        /**
         * Returns the connected project according to the SysML v2 Standard
         * @see Commit
         * @return The project from the connected commit.
         */
        [[nodiscard]] std::shared_ptr<Project> getUsedProject() const;

        std::string serializeToJson() override;

    protected:
        void deserializeAndPopulate(const std::string &jsonString) override;

        std::shared_ptr<Commit> UsedProjectCommit;

    };

} // SysMLv2
