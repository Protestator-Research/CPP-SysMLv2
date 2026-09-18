//
// Created by Moritz Herzog on 24.03.25.
//
//---------------------------------------------------------
// Constants, Definitions, Pragmas
//---------------------------------------------------------
#pragma once
#include <kerml/model/Forward.h>
//---------------------------------------------------------
// External Classes
//---------------------------------------------------------
#include <kerml/root/annotations/AnnotatingElement.h>
#include <string>
//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include <kerml/kerml_global.h>
//---------------------------------------------------------
// Forwarding
//---------------------------------------------------------

namespace KerML::Entities {
    /**
     * @class TextualRepresentation
     * @author Moritz Herzog
     */
    class KERML_EXPORT TextualRepresentation : public AnnotatingElement{
    public:
        TextualRepresentation();
        TextualRepresentation(std::string  language, std::string body);
        TextualRepresentation(std::string jsonString);

        ~TextualRepresentation() override = default;

        std::string language();
        void setLanguage(std::string language);

        std::string body();
        void setBody(std::string body);

        std::string serializeToJson() override;

    protected:
        void deserializeAndPopulate(const std::string &jsonString) override;

    private:
        std::string Language;
        std::string Body;
    public:
        std::shared_ptr<Element> representedElement() const;
        void setRepresentedElement(std::shared_ptr<Element> value);
    };
} // KerML::Entities
