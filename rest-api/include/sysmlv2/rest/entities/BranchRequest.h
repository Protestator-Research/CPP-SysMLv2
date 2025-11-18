//
// Created by Moritz Herzog on 18.11.25.
//
#pragma once
#include <sysmlv2/rest/entities/IEntity.h>


namespace SysMLv2::REST {
    class Project;
    class Commit;

    class BranchRequest : public IEntity {
    public:
        BranchRequest(std::string name, std::shared_ptr<Project> project, std::shared_ptr<Commit> commit);
        BranchRequest(std::string jsonString);

        ~BranchRequest() override = default;

        std::string serializeToJson() override;

        std::string getName();
        std::shared_ptr<Project> getProject();
        std::shared_ptr<Commit> getHead();

    protected:
        void deserializeAndPopulate(const std::string &jsonString) override;

    private:
        std::string _dType;
        std::string Name;
        std::shared_ptr<Commit> Head;
        std::shared_ptr<Project> OwingProject;
    };
} // SysMLv2::REST
