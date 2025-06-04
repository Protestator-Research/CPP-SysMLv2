//
// Created by Moritz Herzog on 24.03.25.
//
//---------------------------------------------------------
// Constants, Definitions, Pragmas
//---------------------------------------------------------
#ifndef SYSMLV2_TEXTUALREPRESENTATION_H
#define SYSMLV2_TEXTUALREPRESENTATION_H
//---------------------------------------------------------
// External Classes
//---------------------------------------------------------
#include "AnnotatingElement.h"
#include <string>
//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include "../../kerml_global.h"
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

#endif //SYSMLV2_TEXTUALREPRESENTATION_H
