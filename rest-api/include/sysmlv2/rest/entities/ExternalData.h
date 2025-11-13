//
// Created by Moritz Herzog on 27.02.24.
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
#include <sysmlv2/rest/entities/Data.h>
#include <sysmlv2/rest/sysmlv2rest_global.h>
//---------------------------------------------------------
// Forwarding
//---------------------------------------------------------

namespace SysMLv2::REST {
    class SYSMLV2REST_EXPORT ExternalData : public Data {
    public:
        ExternalData() = delete;
        explicit ExternalData(std::string jsonStringOrIRI);
        ~ExternalData() override = default;

        void setResourceIdentifier(std::string resourceIdentifier);
        std::string resourceIdentifier() const;

        std::string serializeToJson() override;

    protected:
        void deserializeAndPopulate(const std::string &jsonString) override;

    private:
        std::string ResourceIdentifier;

    };
} // SysMLv2
