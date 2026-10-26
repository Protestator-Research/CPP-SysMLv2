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
#include <memory>
#include <sysmlv2/rest/entities/Data.h>
#include <sysmlv2/rest/entities/ExternalData.h>
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

        /**
         * @param jsonString The JSON object of the ExternalRelationship. specification and language are optional.
         * @throws std::invalid_argument If the text is no valid JSON object or has values of a wrong type.
         */
        explicit ExternalRelationship(std::string jsonString);

        /**
         * A relationship without ends; specification and language may be empty.
         */
        ExternalRelationship(std::string specification, std::string language);

        /**
         * Note: ExternalRelationship(nullptr, nullptr) is ambiguous with the (specification, language) constructor; pass
         * typed pointers.
         * @param elementEnd The Element that is linked to the external data.
         * @param externalDataEnd The ExternalData the element is linked to.
         * @param specification Optional specification, e.g. a query on the external data (omitted from the JSON if empty).
         * @param language Optional language of the specification (omitted from the JSON if empty).
         */
        ExternalRelationship(std::shared_ptr<Data> elementEnd, std::shared_ptr<ExternalData> externalDataEnd,
                             std::string specification = "", std::string language = "");
        ~ExternalRelationship() override = default;

        void setLanguage(std::string lanuage);
        std::string language() const;
        void setSpecification(std::string specification);
        std::string specification() const;

        /**
         * The Element at the element end. Read from JSON it is a Data that only knows its id (a reference).
         */
        [[nodiscard]] std::shared_ptr<Data> elementEnd() const;
        void setElementEnd(std::shared_ptr<Data> elementEnd);

        /**
         * The ExternalData at the end of the external data. Read from JSON it only knows its id (a reference).
         */
        [[nodiscard]] std::shared_ptr<ExternalData> externalDataEnd() const;
        void setExternalDataEnd(std::shared_ptr<ExternalData> externalDataEnd);

        std::string serializeToJson() override;

    protected:
        void deserializeAndPopulate(const std::string &jsonString) override;

    private:
        std::string Specification;
        std::string Language;
        std::shared_ptr<Data> ElementEnd;
        std::shared_ptr<ExternalData> ExternalDataEnd;
    };
} // SysMLv2
