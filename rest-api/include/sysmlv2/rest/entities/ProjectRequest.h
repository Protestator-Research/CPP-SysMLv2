//
// Created by Moritz Herzog on 13.11.25.
//

#ifndef PROJECTREQUEST_H
#define PROJECTREQUEST_H

#include <optional>
#include <string>
#include <boost/uuid/uuid.hpp>
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

        /**
         * Creates a request in the format of the SysML v2 API: the default branch is written as reference {"@id": ...}.
         * @param name Name of the project.
         * @param description Description of the project.
         * @param defaultBranch Id of the default branch. Without a value the field "defaultBranch" is omitted.
         */
        ProjectRequest(const std::string& name, const std::string& description, std::optional<boost::uuids::uuid> defaultBranch);

        /**
         * Creates a request with the name of the default branch. A name can not be converted into the id the API needs,
         * so "defaultBranch" is still written as string.
         * @deprecated Use the constructor with the id of the default branch.
         */
        [[deprecated("Use ProjectRequest(name, description, std::optional<boost::uuids::uuid>).")]]
        ProjectRequest(const std::string& name, const std::string& description, const std::string& defaultBranch = "main");

        /**
         * Reads a request from JSON. "description" and "defaultBranch" are optional. "defaultBranch" is a reference
         * {"@id": ...}; the string of earlier library versions is still read and prints a deprecation warning.
         * @throws std::invalid_argument If the text is no valid JSON object or has values of a wrong type.
         */
        explicit ProjectRequest(const std::string& jsonString);

        [[nodiscard]] std::string name() const;
        [[nodiscard]] std::string description() const;

        /**
         * The id of the default branch, empty if there is none (or only a branch name was given).
         */
        [[nodiscard]] std::optional<boost::uuids::uuid> defaultBranchId() const;

        /**
         * The name of the default branch of earlier library versions. Empty if the request has none.
         * @deprecated Use defaultBranchId.
         */
        [[deprecated("Use ProjectRequest::defaultBranchId().")]]
        [[nodiscard]] std::string defaultBranch() const;

        std::string serializeToJson() override;

    protected:
        void deserializeAndPopulate(const std::string &jsonString) override;

    private:
        std::string _dType;
        std::string Name;
        std::string Description;
        /** Id of the default branch (format of the API). */
        std::optional<boost::uuids::uuid> DefaultBranchId;
        /** Name of the default branch (format of earlier library versions, written as string). */
        std::optional<std::string> DefaultBranchName;
    };
}



#endif //PROJECTREQUEST_H
