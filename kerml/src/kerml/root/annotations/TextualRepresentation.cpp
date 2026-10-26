//
// Created by Moritz Herzog on 24.03.25.
//

#include <kerml/root/annotations/TextualRepresentation.h>
#include <nlohmann/json.hpp>
#include "../../model/JsonSupport.h"
#include <kerml/KerML.h>

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

    TextualRepresentation::TextualRepresentation(std::string nameOrJson) : AnnotatingElement(){
        _dType = "TextualRepresentation";
        if (Json::looksLikeJson(nameOrJson)) {
            deserializeAndPopulate(nameOrJson);
            captureJsonSource(nameOrJson);
        }
        else
            setDeclaredName(nameOrJson);
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

    std::string TextualRepresentation::body() {
        return Body;
    }
} // KerML::Entities

// BEGIN GENERATED JSON (kerml/tools/generate_json.py): do not edit, run the script instead.
namespace KerML::Entities {
    std::string TextualRepresentation::serializeToJson() {
        nlohmann::json json = nlohmann::json::parse(AnnotatingElement::serializeToJson());
        json["language"] = Json::value(TextualRepresentation::language());
        json["representedElement"] = Json::reference(unresolvedJsonReferences("representedElement"), TextualRepresentation::representedElement());
        json["body"] = Json::value(TextualRepresentation::body());
        return applyJsonSource(json.dump(JSON_INTENT));
    }

    void TextualRepresentation::deserializeAndPopulate(const std::string& jsonString) {
        AnnotatingElement::deserializeAndPopulate(jsonString);
        const nlohmann::json json = nlohmann::json::parse(jsonString);
        std::vector<boost::uuids::uuid> ids;
        {
            std::string value{};
            if (Json::readString(json, "language", value)) {
                try {
                    TextualRepresentation::setLanguage(value);
                } catch (const std::invalid_argument&) {
                    // A value the metaclass refuses (for example another operator than the fixed one) is ignored.
                }
            }
        }
        if (Json::readReferences(json, "representedElement", ids))
            setUnresolvedJsonReferences("representedElement", ids);
        {
            std::string value{};
            if (Json::readString(json, "body", value)) {
                try {
                    TextualRepresentation::setBody(value);
                } catch (const std::invalid_argument&) {
                    // A value the metaclass refuses (for example another operator than the fixed one) is ignored.
                }
            }
        }
    }

    void TextualRepresentation::resolveJsonReferences(const std::function<std::shared_ptr<Element>(const boost::uuids::uuid&)>& lookup) {
        AnnotatingElement::resolveJsonReferences(lookup);
        if (const auto ids = unresolvedJsonReferences("representedElement")) {
            try {
                if (auto target = std::dynamic_pointer_cast<KerML::Entities::Element>(lookup(ids->front()))) {
                    TextualRepresentation::setRepresentedElement(std::move(target));
                    clearUnresolvedJsonReferences("representedElement");
                }
            } catch (const std::exception&) {
                // The reference stays unresolved if the model refuses it.
                setUnresolvedJsonReferences("representedElement", *ids);
            }
        }
    }
}
// END GENERATED JSON
