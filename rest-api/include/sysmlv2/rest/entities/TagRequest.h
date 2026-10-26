//
// Request to create a Tag (body of POST projects/{projectId}/tags).
//
//---------------------------------------------------------
// Constants, Definitions, Pragmas
//---------------------------------------------------------
#pragma once
//---------------------------------------------------------
// External Classes
//---------------------------------------------------------
#include <memory>
#include <string>
#include <boost/uuid/uuid.hpp>
//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include <sysmlv2/rest/entities/IEntity.h>
#include <sysmlv2/rest/sysmlv2rest_global.h>
//---------------------------------------------------------
// Forwarding
//---------------------------------------------------------
namespace SysMLv2::REST {
    class Commit;
}

namespace SysMLv2::REST {
    /**
     * The request that creates a Tag: {"@type": "Tag", "name": ..., "taggedCommit": {"@id": ...}}.
     * @class TagRequest
     */
    class SYSMLV2REST_EXPORT TagRequest : public IEntity {
    public:
        TagRequest() = delete;

        /**
         * @param name Name of the new tag.
         * @param taggedCommit The commit that is tagged (only its id is written).
         */
        TagRequest(std::string name, std::shared_ptr<Commit> taggedCommit);

        /**
         * @param name Name of the new tag.
         * @param taggedCommitId Id of the commit that is tagged.
         */
        TagRequest(std::string name, const boost::uuids::uuid& taggedCommitId);

        /**
         * Reads a TagRequest from JSON.
         * @throws std::invalid_argument If the text is no JSON object, "name" is missing or empty, "taggedCommit" is
         * missing, null or no reference {"@id": ...}, or "@type" is something else than "Tag".
         */
        explicit TagRequest(const std::string& jsonString);

        ~TagRequest() override = default;

        std::string serializeToJson() override;

        [[nodiscard]] std::string getName() const;

        /**
         * The tagged commit (identification only) or nullptr if none was given to the constructor.
         */
        [[nodiscard]] std::shared_ptr<Commit> getTaggedCommit() const;

    protected:
        void deserializeAndPopulate(const std::string& jsonString) override;

    private:
        std::string Name;
        std::shared_ptr<Commit> TaggedCommit;
    };
}
