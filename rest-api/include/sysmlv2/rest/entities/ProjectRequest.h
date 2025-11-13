//
// Created by Moritz Herzog on 13.11.25.
//

#ifndef PROJECTREQUEST_H
#define PROJECTREQUEST_H
#include <string>
#include <sysmlv2/rest/entities/IEntity.h>


namespace SysMLv2::REST {
    class ProjectRequest : public IEntity {
    public:
        ProjectRequest() = delete;
        ProjectRequest(std::string name, std::string description, std::string defaultBranch = "main");

        std::string name() const;
        std::string description() const;
        std::string defaultBranch() const;

        std::string serializeToJson() override;

    protected:
        void deserializeAndPopulate(const std::string &jsonString) override;

    private:
        std::string Name;
        std::string Description;
        std::string DefaultBranchName;
    };
}



#endif //PROJECTREQUEST_H
