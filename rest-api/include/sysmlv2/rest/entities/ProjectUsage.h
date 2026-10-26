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
         * Constructor for the JSON parsing. Reads "usedProjectCommit" and "usedProject" (references). The older field
         * "usedCommit" (an object, or the escaped JSON text of the commit like earlier library versions wrote it) is still
         * read and prints a deprecation warning.
         * @param jsonString The JSON object of the ProjectUsage.
         * @throws std::invalid_argument If the text is no valid JSON object or has values of a wrong type.
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
         * @return The project of the connected commit (usedProjectCommit.owningProject); if the commit does not know its
         * project, the project read from the JSON field "usedProject"; otherwise nullptr.
         */
        [[nodiscard]] std::shared_ptr<Project> getUsedProject() const;

        std::string serializeToJson() override;

    protected:
        void deserializeAndPopulate(const std::string &jsonString) override;

        std::shared_ptr<Commit> UsedProjectCommit;
        /** The project read from "usedProject"; used if the commit does not know its owning project. */
        std::shared_ptr<Project> UsedProject;

    };

} // SysMLv2
