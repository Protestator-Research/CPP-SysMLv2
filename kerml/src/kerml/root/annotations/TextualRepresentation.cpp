//
// Created by Moritz Herzog on 24.03.25.
//

#include <kerml/root/annotations/TextualRepresentation.h>

namespace KerML::Entities {
    TextualRepresentation::TextualRepresentation() {
        Language = "";
        Body = "";
    }

    TextualRepresentation::TextualRepresentation(std::string language, std::string body) {
        Language = language;
        Body = body;
    }

    std::string TextualRepresentation::language() {
        return Language;
    }

    void TextualRepresentation::setLanguage(std::string language) {
        Language = language;
    }

    void TextualRepresentation::setBody(std::string body) {
        body = Body;
    }

    std::string TextualRepresentation::body() {
        return Body;
    }
} // KerML::Entities