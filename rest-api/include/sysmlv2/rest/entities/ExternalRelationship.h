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
    /**
     * Representation of the ExternalRelationship from the SysMLv2 Standard
     * @version 1.0
     * @author Moritz Herzog
     */
    class SYSMLV2REST_EXPORT ExternalRelationship : public Data {
    public:
        ExternalRelationship() = delete;
        explicit ExternalRelationship(std::string jsonString);
        ExternalRelationship(std::string specification, std::string language);
        ~ExternalRelationship() override = default;

        void setLanguage(std::string lanuage);
        std::string language();
        void setSpecification(std::string specification);
        std::string specification();

        std::string serializeToJson() override;

    protected:
        void deserializeAndPopulate(const std::string &jsonString) override;

    private:
        std::string Specification;
        std::string Language;
    };
} // SysMLv2
