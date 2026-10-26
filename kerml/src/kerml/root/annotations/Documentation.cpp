//
// Created by Moritz Herzog on 24.03.25.
//

#include <kerml/root/annotations/Documentation.h>
#include <kerml/KerML.h>
#include <nlohmann/json.hpp>
#include "../../model/JsonSupport.h"

namespace KerML::Entities {

    Documentation::Documentation(std::shared_ptr<Element> documentedElement, std::string locale, std::string body) :
	Comment(locale, body){
        DocumentedElement = documentedElement;
        _dType = "Documentation";
    }

    Documentation::Documentation(std::nullptr_t) : Documentation(std::shared_ptr<Element>()) {
    }

    std::shared_ptr<Element> Documentation::documentedElement() {
        return DocumentedElement;
    }

    void Documentation::setDocumentedElement(std::shared_ptr<Element> documentedElement) {
        clearUnresolvedJsonReferences("documentedElement");
        DocumentedElement = documentedElement;
    }
} // KerML::Entities

// BEGIN GENERATED JSON (kerml/tools/generate_json.py): do not edit, run the script instead.
namespace KerML::Entities {
    Documentation::Documentation(const std::string& nameOrJson) :
        Documentation() {
        _dType = "Documentation";
        if (Json::looksLikeJson(nameOrJson)) {
            deserializeAndPopulate(nameOrJson);
            captureJsonSource(nameOrJson);
        } else {
            setDeclaredName(nameOrJson);
        }
    }

    std::string Documentation::serializeToJson() {
        nlohmann::json json = nlohmann::json::parse(Comment::serializeToJson());
        json["documentedElement"] = Json::reference(unresolvedJsonReferences("documentedElement"), Documentation::documentedElement());
        return applyJsonSource(json.dump(JSON_INTENT));
    }

    void Documentation::deserializeAndPopulate(const std::string& jsonString) {
        Comment::deserializeAndPopulate(jsonString);
        const nlohmann::json json = nlohmann::json::parse(jsonString);
        std::vector<boost::uuids::uuid> ids;
        if (Json::readReferences(json, "documentedElement", ids))
            setUnresolvedJsonReferences("documentedElement", ids);
    }

    void Documentation::resolveJsonReferences(const std::function<std::shared_ptr<Element>(const boost::uuids::uuid&)>& lookup) {
        Comment::resolveJsonReferences(lookup);
        if (const auto ids = unresolvedJsonReferences("documentedElement")) {
            try {
                if (auto target = std::dynamic_pointer_cast<KerML::Entities::Element>(lookup(ids->front()))) {
                    Documentation::setDocumentedElement(std::move(target));
                    clearUnresolvedJsonReferences("documentedElement");
                }
            } catch (const std::exception&) {
                // The reference stays unresolved if the model refuses it.
                setUnresolvedJsonReferences("documentedElement", *ids);
            }
        }
    }
}
// END GENERATED JSON
