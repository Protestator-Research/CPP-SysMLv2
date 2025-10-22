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
#include <memory>
//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include <sysmlv2/rest/entities/Record.h>
#include <sysmlv2/rest/sysmlv2rest_global.h>
//---------------------------------------------------------
// Forwarding
//---------------------------------------------------------
namespace SysMLv2::REST {
    class DataIdentity;
    class Data;
}


namespace SysMLv2::REST {
    /**
     * The class DataVersion represents a specific version of the Data in its lifecycle
     * @class DataVersion
     * @author Moritz Herzog
     * @version 1.0
     */
    class SYSMLV2REST_EXPORT DataVersion : public Record {
    public:
        DataVersion() = delete;

        DataVersion(std::shared_ptr<DataIdentity> identity, std::shared_ptr<Data> payload = nullptr);
        virtual ~DataVersion();

        std::shared_ptr<DataIdentity> getIdentity();
        void setPayload(std::shared_ptr<Data> payload);
        std::shared_ptr<Data> getPayload();
        boost::uuids::uuid getId();

        std::string serializeToJson();

    protected:
        std::shared_ptr<DataIdentity> Identity;

        std::shared_ptr<Data> Payload;
    };
}
