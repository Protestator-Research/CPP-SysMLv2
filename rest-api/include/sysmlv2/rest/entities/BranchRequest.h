//
// Created by Moritz Herzog on 18.11.25.
//
#pragma once
#include <sysmlv2/rest/entities/IEntity.h>
#include <sysmlv2/rest/sysmlv2rest_global.h>

namespace SysMLv2::REST {
    class Project;
    class Commit;

    class SYSMLV2REST_EXPORT BranchRequest : public IEntity {
    public:
        /**
         * Creates a branch request from its parts.
         * @param name Name of the branch to be created.
         * @param project The owning project, may be nullptr.
         * @param commit The head commit of the new branch, may be nullptr.
         */
        BranchRequest(std::string name, std::shared_ptr<Project> project, std::shared_ptr<Commit> commit);

        /**
         * Creates a branch request from the JSON, as it is sent by a client.
         * @param jsonString The JSON of the request.
         * @throws std::invalid_argument If the JSON is not an object, the name is missing or empty, or head / owningProject are malformed. A missing head is still accepted (earlier library versions), but prints a deprecation warning.
         */
        BranchRequest(std::string jsonString);

        ~BranchRequest() override = default;

        /**
         * Serializes the request. Head and owningProject are only written as identification objects, if they are set.
         * @return The JSON representation.
         */
        std::string serializeToJson() override;

        /** @return The name of the branch. */
        std::string getName();

        /** @return The owning project (identification only) or nullptr. */
        std::shared_ptr<Project> getProject();

        /** @return The head commit (identification only) or nullptr. */
        std::shared_ptr<Commit> getHead();

    protected:
        /**
         * Populates the request from JSON.
         * @param jsonString The JSON of the request.
         * @throws std::invalid_argument If the JSON is not an object, the name is missing or empty, or head / owningProject are malformed. A missing head is still accepted (earlier library versions), but prints a deprecation warning.
         */
        void deserializeAndPopulate(const std::string &jsonString) override;

    private:
        std::string _dType;
        std::string Name;
        std::shared_ptr<Commit> Head;
        std::shared_ptr<Project> OwingProject;
    };
} // SysMLv2::REST
