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

//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include "Record.h"
#include "../sysmlv2rest_global.h"
//---------------------------------------------------------
// Forwarding
//---------------------------------------------------------
namespace SysMLv2::Entities {
    class DataVersion;
    class Project;
}


namespace SysMLv2::Entities {
    /**
     * The class Data Identity is a subclass of Record that represents a unique, version-independent representation of
     * Data through its lifecycle.A Data Identity is associated with 1 or more Data Version records that represent
     * different versions of the same Data.
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
         * Constructor. Generates a
         * @param id
         */
        explicit DataIdentity(boost::uuids::uuid id);

        /**
         * Constuctor for JSON Parsing
         * @param jsonStringOrName
         */
        explicit DataIdentity(std::string jsonStringOrName);


        /**
         * Destructor
         */
        virtual ~DataIdentity();

        std::vector<std::shared_ptr<DataVersion>> getDataVersions() const;
        void setDataVersions(std::vector<std::shared_ptr<DataVersion>> versions);

        /**
         * Returns the creation date of the data. This translations to the point in time, where the first commit is
         * created, representing then the creation of the specified Dataset.
         * @return Data creation date.
         */
        std::chrono::system_clock::time_point createdAt();

        /**
         * Returns the date, where the data is deleted. Thus this represents the commit, that deletes the data set.
         * @return The time, where the data is delted.
         */
        std::chrono::system_clock::time_point deletedAt();

        std::string serializeToJson() override;

        bool operator==(DataIdentity const &other);

    private:
        std::vector<std::shared_ptr<DataVersion>> Version;
    };
}
