//
// Created by Moritz Herzog on 24.03.25.
//

#ifndef SYSMLV2_TEXTUALREPRESENTATION_H
#define SYSMLV2_TEXTUALREPRESENTATION_H

#include "AnnotatingElement.h"
#include <string>


namespace KerML::Entities {
    /**
     * @class TextualRepresentation
     * @author Moritz Herzog
     */
    class TextualRepresentation : public AnnotatingElement{
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
