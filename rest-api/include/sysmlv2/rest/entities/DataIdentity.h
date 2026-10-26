//
// Created by Moritz Herzog on 19.02.24.
//
//---------------------------------------------------------
// Constants, Definitions, Pragmas
//---------------------------------------------------------
#pragma once
//---------------------------------------------------------
// External Classes
//---------------------------------------------------------
#include <boost/uuid/uuid.hpp>
#include <vector>
#include <chrono>
#include <memory>
#include <optional>

//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include <sysmlv2/rest/entities/Record.h>
#include <sysmlv2/rest/sysmlv2rest_global.h>
//---------------------------------------------------------
// Forwarding
//---------------------------------------------------------
namespace SysMLv2::REST {
    class Commit;
    class DataVersion;
    class Project;
}


namespace SysMLv2::REST {
    /**
     * The class Data Identity is a subclass of Record that represents a unique, version-independent representation of
     * Data through its lifecycle. A Data Identity is associated with 1 or more Data Version records that represent
     * different versions of the same Data. Its id is the id of the Data (Data::getId).
     *
     * The JSON contains the Record fields and, if known, the derived references "createdAt" and "deletedAt" to the
     * commits that created and deleted the Data (as {"@id": ...}). A minimal {"@id": ..., "@type": "DataIdentity"} is valid.
     * The older fields "dataVersions", "created" and "deleted" of earlier library versions are still read and print a
     * deprecation warning; they are no longer written.
     * @class DataIdentity
     * @author Moritz Herzog
     * @version 1.0
     * @see boost::uuids::uuid
     * @see SysMLv2::Entities::Record
     */
    class SYSMLV2REST_EXPORT DataIdentity : public Record {
    public:
        /**
         * Default constructor is delted.
         */
        DataIdentity() = delete;

        /**
         * Constructor. Generates a DataIdentity for the Data with the given id.
         * @param id The id of the Data.
         */
        explicit DataIdentity(boost::uuids::uuid id);

        /**
         * Constuctor for JSON Parsing
         * @param jsonStringOrName A JSON object (the text starts with '{') or the name of the identity.
         * @throws std::invalid_argument If the text looks like JSON but is malformed or has values of a wrong type.
         */
        explicit DataIdentity(std::string jsonStringOrName);


        /**
         * Destructor
         */
        ~DataIdentity() override = default;

        /**
         * The DataVersions of this identity that are known in memory. They are not part of the JSON.
         */
        std::vector<std::shared_ptr<DataVersion>> getDataVersions() const;
        void setDataVersions(std::vector<std::shared_ptr<DataVersion>> versions);

        /**
         * Returns the creation date of the data. This translations to the point in time, where the first commit is
         * created, representing then the creation of the specified Dataset. This is the creation time of the commit
         * getCreatedAt() if it is known, otherwise the value of the older JSON field "created", otherwise the epoch.
         * @return Data creation date.
         */
        std::chrono::system_clock::time_point createdAt() const;

        /**
         * Returns the date, where the data is deleted. Thus this represents the commit, that deletes the data set.
         * This is the creation time of the commit getDeletedAt() if it is known, otherwise the value of the older JSON
         * field "deleted", otherwise the epoch.
         * @return The time, where the data is delted.
         */
        std::chrono::system_clock::time_point deletedAt() const;

        /**
         * The commit that created the Data (the derived property createdAt of the SysML v2 API). nullptr if unknown.
         */
        [[nodiscard]] std::shared_ptr<Commit> getCreatedAt() const;

        /**
         * Sets the commit that created the Data.
         */
        void setCreatedAt(std::shared_ptr<Commit> commit);

        /**
         * The commit that deleted the Data (the derived property deletedAt of the SysML v2 API). nullptr if the Data is not
         * known to be deleted.
         */
        [[nodiscard]] std::shared_ptr<Commit> getDeletedAt() const;

        /**
         * Sets the commit that deleted the Data.
         */
        void setDeletedAt(std::shared_ptr<Commit> commit);

        std::string serializeToJson() override;

        bool operator==(DataIdentity const &other);

protected:
        void deserializeAndPopulate(const std::string& jsonString) override;

        std::vector<std::shared_ptr<DataVersion>> Version;
        /** Deletion time of the older JSON format (field "deleted"). */
        std::optional<std::chrono::system_clock::time_point> Deleted;
        /** Creation time of the older JSON format (field "created"). */
        std::optional<std::chrono::system_clock::time_point> Created;
        std::shared_ptr<Commit> CreatedAt;
        std::shared_ptr<Commit> DeletedAt;
    };
}
