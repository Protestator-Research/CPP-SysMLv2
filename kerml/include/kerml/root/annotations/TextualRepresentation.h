//
// Created by Moritz Herzog on 24.03.25.
//
//---------------------------------------------------------
// Constants, Definitions, Pragmas
//---------------------------------------------------------
#pragma once
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

        ~TextualRepresentation() override = default;

        std::string language();
        void setLanguage(std::string language);

        std::string body();
        void setBody(std::string body);
    private:
        std::string Language;
        std::string Body;
    };
} // KerML::Entities
