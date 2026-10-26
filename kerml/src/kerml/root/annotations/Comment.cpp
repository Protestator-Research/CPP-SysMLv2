//
// Created by Moritz Herzog on 24.03.25.
//

#include <kerml/root/annotations/Comment.h>
#include <kerml/KerML.h>
#include <nlohmann/json.hpp>
#include "../../model/JsonSupport.h"

namespace KerML::Entities {

    Comment::Comment() {
        _dType = "Comment";
    }

    Comment::Comment(std::string locale, std::string body) {
        Locale = locale;
        Body = body;
        _dType = "Comment";
    }

    std::string Comment::locale() {
        return Locale;
    }

    void Comment::setLocale(std::string locale) {
        Locale = locale;
    }

    std::string Comment::body() {
        return Body;
    }

    void Comment::setBody(std::string body) {
        Body = body;
    }
} // KerML::Entities

// BEGIN GENERATED JSON (kerml/tools/generate_json.py): do not edit, run the script instead.
namespace KerML::Entities {
    Comment::Comment(const std::string& nameOrJson) :
        Comment() {
        _dType = "Comment";
        if (Json::looksLikeJson(nameOrJson)) {
            deserializeAndPopulate(nameOrJson);
            captureJsonSource(nameOrJson);
        } else {
            setDeclaredName(nameOrJson);
        }
    }

    std::string Comment::serializeToJson() {
        nlohmann::json json = nlohmann::json::parse(AnnotatingElement::serializeToJson());
        json["locale"] = Json::value(Comment::locale());
        json["body"] = Json::value(Comment::body());
        return applyJsonSource(json.dump(JSON_INTENT));
    }

    void Comment::deserializeAndPopulate(const std::string& jsonString) {
        AnnotatingElement::deserializeAndPopulate(jsonString);
        const nlohmann::json json = nlohmann::json::parse(jsonString);
        {
            std::string value{};
            if (Json::readString(json, "locale", value)) {
                try {
                    Comment::setLocale(value);
                } catch (const std::invalid_argument&) {
                    // A value the metaclass refuses (for example another operator than the fixed one) is ignored.
                }
            }
        }
        {
            std::string value{};
            if (Json::readString(json, "body", value)) {
                try {
                    Comment::setBody(value);
                } catch (const std::invalid_argument&) {
                    // A value the metaclass refuses (for example another operator than the fixed one) is ignored.
                }
            }
        }
    }

    void Comment::resolveJsonReferences(const std::function<std::shared_ptr<Element>(const boost::uuids::uuid&)>& lookup) {
        AnnotatingElement::resolveJsonReferences(lookup);
    }
}
// END GENERATED JSON
