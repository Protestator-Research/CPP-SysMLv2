//
// Created by Moritz Herzog on 23.02.24.
//
//---------------------------------------------------------
// Constants, Definitions, Pragmas
//---------------------------------------------------------
#pragma once
//---------------------------------------------------------
// External Classes
//---------------------------------------------------------

//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include <sysmlv2/rest/entities/CommitReference.h>
#include <sysmlv2/rest/sysmlv2rest_global.h>
//---------------------------------------------------------
// Forwarding
//---------------------------------------------------------

namespace SysMLv2::REST {
    class Project;
    /**
     * Represents a Tag of the SysMLv2 API: a named, immutable reference to a commit. The tagged commit is the referenced
     * commit of the CommitReference, both are always equal.
     * @class Tag
     * @author Moritz Herzog
     * @version 1.0
     */
    class SYSMLV2REST_EXPORT Tag : public CommitReference {

    public:
        /**
         * @param jsonStringOrName A JSON object (the text starts with '{') or the name of the tag.
         * @throws std::invalid_argument If the text looks like JSON but is malformed or has values of a wrong type.
         */
        Tag(std::string jsonStringOrName);

        /**
         * Creates a tag. The tagged commit can not be changed afterwards.
         */
        Tag(std::string name, std::shared_ptr<Project> owningProject, std::shared_ptr<Commit> referencedCommit);

        /**
         * The project that owns the tag (same as getOwningProject()).
         */
        [[nodiscard]] std::shared_ptr<Project> owningProject() const;

        /**
         * The tagged commit (same as referencedCommit()).
         */
        [[nodiscard]] std::shared_ptr<Commit> taggedCommit() const;

        /**
         * Changes the tagged commit of the tag.
         * @deprecated A Tag is immutable; pass the commit to the constructor instead.
         */
        [[deprecated("A Tag is immutable. Pass the tagged commit to the constructor.")]]
        void setReferencedCommit(std::shared_ptr<Commit> referencedCommit);

        std::string serializeToJson() override;
    protected:
        void deserializeAndPopulate(const std::string &jsonString) override;
    };
}
