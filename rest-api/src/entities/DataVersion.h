//
// Created by Moritz Herzog on 23.02.24.
//
//---------------------------------------------------------
// Constants, Definitions, Pragmas
//---------------------------------------------------------
#ifndef DIGITALTWIN_DATAVERSION_H
#define DIGITALTWIN_DATAVERSION_H
//---------------------------------------------------------
// External Classes
//---------------------------------------------------------
#include <boost/uuid/uuid.hpp>
#include <memory>
//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include "Record.h"
//---------------------------------------------------------
// Forwarding
//---------------------------------------------------------
namespace SysMLv2::Entities {
    class DataIdentity;
    class Data;
}


namespace SysMLv2::Entities {
    /**
     * The class DataVersion represents a specific version of the Data in its lifecycle
     * @class DataVersion
     * @author Moritz Herzog
     * @version 1.0
     */
    class DataVersion : public Record {
    public:
        DataVersion() = delete;

        DataVersion(std::shared_ptr<DataIdentity> identity, std::shared_ptr<Data> payload = nullptr);
        virtual ~DataVersion();

        std::shared_ptr<DataIdentity> getIdentity();
        void setPayload(std::shared_ptr<Data> payload);
        std::shared_ptr<Data> getPayload();
        boost::uuids::uuid getId();

        std::string serializeToJson();

    private:
        std::shared_ptr<DataIdentity> Identity;

        std::shared_ptr<Data> Payload;
    };
}

#endif //DIGITALTWIN_DATAVERSION_H
