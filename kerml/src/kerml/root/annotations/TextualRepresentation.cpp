//
// Created by Moritz Herzog on 24.03.25.
//

#include <kerml/root/annotations/TextualRepresentation.h>
#include <nlohmann/json.hpp>

namespace KerML::Entities {
    TextualRepresentation::TextualRepresentation() : AnnotatingElement() {
        Language = "";
        Body = "";
        _dType = "TextualRepresentation";
    }

    TextualRepresentation::TextualRepresentation(std::string language, std::string body) : AnnotatingElement()  {
        Language = language;
        Body = body;
        _dType = "TextualRepresentation";
    }

    TextualRepresentation::TextualRepresentation(std::string jsonString) : AnnotatingElement(){
        _dType = "TextualRepresentation";
        deserializeAndPopulate(jsonString);
    }

    std::string TextualRepresentation::language() {
        return Language;
    }

    void TextualRepresentation::setLanguage(std::string language) {
        Language = language;
    }

    void TextualRepresentation::setBody(std::string body) {
        Body = body;
    }

    std::string TextualRepresentation::serializeToJson() {
        nlohmann::json json = nlohmann::json::parse(Element::serializeToJson());

        json["language"] = Language;
        json["body"] = Body;

        return json.dump(JSON_INTENT);
    }

    void TextualRepresentation::deserializeAndPopulate(const std::string &jsonString) {
        Element::deserializeAndPopulate(jsonString);
        nlohmann::json json = nlohmann::json::parse(jsonString);
        Language = json["language"].get<std::string>();
        Body = json["body"].get<std::string>();
    }

    std::string TextualRepresentation::body() {
        return Body;
    }
} // KerML::Entities