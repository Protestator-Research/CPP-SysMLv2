//
// Created by Moritz Herzog on 13.11.25.
//

#ifndef PROJECTREQUEST_H
#define PROJECTREQUEST_H

#include <string>
#include <sysmlv2/rest/entities/IEntity.h>
#include <sysmlv2/rest/sysmlv2rest_global.h>


namespace SysMLv2::REST {
    /**
     * ProjectRequest is not part of the SysML v2 Standard, but it helps with working on the REST requests.
     * @class ProjectRequest
     * @
     */
    class SYSMLV2REST_EXPORT ProjectRequest : public IEntity {
    public:
        ProjectRequest() = delete;
        ProjectRequest(const std::string& name,const std::string& description, const std::string& defaultBranch = "main");
        explicit ProjectRequest(const std::string& jsonString);

        [[nodiscard]] std::string name() const;
        [[nodiscard]] std::string description() const;
        [[nodiscard]] std::string defaultBranch() const;

        std::string serializeToJson() override;

    protected:
        void deserializeAndPopulate(const std::string &jsonString) override;

    private:
        std::string _dType;
        std::string Name;
        std::string Description;
        std::string DefaultBranchName;
    };
}



#endif //PROJECTREQUEST_H
