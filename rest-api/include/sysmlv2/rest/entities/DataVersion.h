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
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/random_generator.hpp>
#include <memory>
#include <string>
//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include <sysmlv2/rest/entities/DataIdentity.h>
#include <sysmlv2/rest/entities/Record.h>
#include <sysmlv2/rest/sysmlv2rest_global.h>
//---------------------------------------------------------
// Forwarding
//---------------------------------------------------------
namespace SysMLv2::REST {
    class Commit;
    class Data;
}


namespace SysMLv2::REST {
    /**
     * The class DataVersion represents a specific version of the Data in its lifecycle. According to the SysML v2 API it
     * is a Record with the identity [1] (the DataIdentity of the Data), the payload [0..1] (the Data in this version;
     * no payload means that the Data is deleted in the commit) and the optional commit.
     *
     * Ids: The id of the DataVersion itself (getVersionId) is a fresh random UUID. The id of the Data is the id of
     * its identity (getIdentity()->getId(), which is Data::getId of the payload). getId() returns the id of the Data, like in
     * earlier versions of the library.
     * Ownership: the links DataVersion::commit <-> Commit::change and DataIdentity::versions <-> DataVersion::identity are
     * std::shared_ptr in both directions. Do not link both directions permanently, because that creates a reference
     * cycle and leaks the objects (the library never sets the back link on its own).
     * @class DataVersion
     * @author Moritz Herzog
     * @version 1.0
     */
    class SYSMLV2REST_EXPORT DataVersion : public Record {
    public:
        /**
         * Creates a DataVersion of the SysML v2 API.
         * @param payload The Data in this version. nullptr means that the Data is deleted; then the identity is required.
         * @param identity The identity of the Data. If it is nullptr, DataIdentity(payload->getId()) is used and the
         * version is a creation in a commit request (see serializeAsRequest). Pass the identity for an update or a deletion.
         * @param id The id of the DataVersion, a new random UUID by default.
         * @throws std::invalid_argument If payload and identity are both nullptr, or if both are given and their ids differ
         * (DataIdentity.id == Data.id).
         */
        explicit DataVersion(std::shared_ptr<Data> payload, std::shared_ptr<DataIdentity> identity = nullptr,
                             boost::uuids::uuid id = boost::uuids::random_generator()());

        /**
         * Constructor of earlier versions of the library. If the payload is nullptr (deletion), the uuid is the id of
         * the Data (the identity). Otherwise the uuid is ignored and the identity is DataIdentity(payload->getId()). The
         * DataVersion gets a new random id. A default constructed DataVersion is a deletion of a random id.
         * @deprecated Use DataVersion(payload, identity, id). It is not ambiguous: the first parameter of the new
         * constructor is the payload, the one of this constructor is the uuid.
         */
        [[deprecated("Use DataVersion(payload, identity, id).")]]
        DataVersion(boost::uuids::uuid id = boost::uuids::random_generator()(), std::shared_ptr<Data> payload = nullptr);

        /**
         * Constructor for the JSON parsing. The JSON of earlier library versions (no "identity", "@id" is the id of the
         * payload) is still read and prints a deprecation warning.
         * @param jsonValue A JSON object of a DataVersion.
         * @throws std::invalid_argument If the text is no valid JSON object, has values of a wrong type or neither has a
         * payload nor an identity.
         */
        DataVersion(std::string jsonValue);
        virtual ~DataVersion();

        /**
         * Sets the payload. If the identity was not given explicitly, it is derived from the new payload.
         */
        void setPayload(std::shared_ptr<Data> payload);
        std::shared_ptr<Data> getPayload();

        /**
         * The id of the Data: the id of the identity, the id of the payload if there is no identity, otherwise the nil
         * UUID. It never fails for a deletion (payload == nullptr). Use getVersionId() for the id of the DataVersion.
         */
        boost::uuids::uuid getId() const;

        /**
         * The id of the DataVersion itself (the "@id" of its JSON). Nil for a version read from a request without "@id".
         */
        [[nodiscard]] boost::uuids::uuid getVersionId() const;

        /**
         * The identity of the Data of this version. Never nullptr.
         */
        [[nodiscard]] std::shared_ptr<DataIdentity> getIdentity() const;

        /**
         * The commit this version belongs to (optional reference, nullptr if unknown).
         */
        [[nodiscard]] std::shared_ptr<Commit> getCommit() const;
        void setCommit(std::shared_ptr<Commit> commit);

        std::string serializeToJson() override;

        /**
         * Serializes the version as an entry of the change list of a CommitRequest: without "@id". The identity is
         * omitted for a creation (it was not given explicitly) and written as {"@id": ...} otherwise. The payload is
         * written in full or null for a deletion.
         */
        std::string serializeAsRequest();

protected:
        void deserializeAndPopulate(const std::string& jsonString) override;

        std::shared_ptr<Data> Payload;
        std::shared_ptr<DataIdentity> Identity;
        /** True if the identity was given by the caller or the JSON and is not derived from the payload. */
        bool IdentityGiven = false;
        std::shared_ptr<Commit> OwningCommit;
    };
}
