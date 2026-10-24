//
// Created by Moritz Herzog on 24.03.25.
//

#include <kerml/root/annotations/Annotation.h>
#include <kerml/KerML.h>
#include <nlohmann/json.hpp>
#include "../../model/JsonSupport.h"

namespace KerML::Entities {

    Annotation::Annotation(boost::uuids::uuid elementID, std::shared_ptr<Element> owner) :
    Element(elementID, owner), Relationship(elementID, owner) {
        _dType = "Annotation";
    }

    Annotation::Annotation(std::string nameOrJson, std::shared_ptr<Element> owner) :
    Element(boost::uuids::random_generator()(), owner), Relationship(boost::uuids::random_generator()(), owner) {
        _dType = "Annotation";
        if (Json::looksLikeJson(nameOrJson)) {
            deserializeAndPopulate(nameOrJson);
            captureJsonSource(nameOrJson);
        } else {
            setDeclaredName(nameOrJson);
        }
    }

    std::shared_ptr<Element> Annotation::owningAnnotatedElement() const {
        return OwningAnnotatedElement;
    }

    void Annotation::setOwningAnnotatedElement(std::shared_ptr<Element> owningAnnotatedElement) {
        clearUnresolvedJsonReferences("owningAnnotatedElement");
        OwningAnnotatedElement = owningAnnotatedElement;
    }

    std::shared_ptr<AnnotatingElement> Annotation::annotatingElement() const {
        return _AnnotatingElement;
    }

    void Annotation::setAnnotatingElement(std::shared_ptr<AnnotatingElement> annotatingElement) {
        clearUnresolvedJsonReferences("annotatingElement");
        _AnnotatingElement = annotatingElement;
    }

    std::shared_ptr<AnnotatingElement> Annotation::ownedAnnotatingElement() const {
        return std::shared_ptr<AnnotatingElement>();
    }

    void Annotation::setOwnedAnnotatingElement(std::shared_ptr<AnnotatingElement> ownedAnnotatingElement) {
        clearUnresolvedJsonReferences("ownedAnnotatingElement");
        OwnedAnnotatingElement = ownedAnnotatingElement;
    }

    std::shared_ptr<AnnotatingElement> Annotation::owningAnnotatingElement() const {
        return OwningAnnotatingElement;
    }

    void Annotation::setOwningAnnotatingElement(std::shared_ptr<AnnotatingElement> owningAnnotatingElement) {
        clearUnresolvedJsonReferences("owningAnnotatingElement");
        OwningAnnotatingElement = owningAnnotatingElement;
    }

    std::shared_ptr<Element> Annotation::annotatedElement() {
        return AnnotatedElement;
    }

    void Annotation::setAnnotatedElement(std::shared_ptr<Element> annotatedElement) {
        clearUnresolvedJsonReferences("annotatedElement");
        AnnotatedElement = annotatedElement;
    }

} // KerML::Entities

// BEGIN GENERATED JSON (kerml/tools/generate_json.py): do not edit, run the script instead.
namespace KerML::Entities {
    std::string Annotation::serializeToJson() {
        nlohmann::json json = nlohmann::json::parse(Relationship::serializeToJson());
        json["annotatingElement"] = Json::reference(unresolvedJsonReferences("annotatingElement"), Annotation::annotatingElement());
        json["annotatedElement"] = Json::reference(unresolvedJsonReferences("annotatedElement"), Annotation::annotatedElement());
        json["owningAnnotatedElement"] = Json::reference(unresolvedJsonReferences("owningAnnotatedElement"), Annotation::owningAnnotatedElement());
        json["owningAnnotatingElement"] = Json::reference(unresolvedJsonReferences("owningAnnotatingElement"), Annotation::owningAnnotatingElement());
        json["ownedAnnotatingElement"] = Json::reference(unresolvedJsonReferences("ownedAnnotatingElement"), Annotation::ownedAnnotatingElement());
        return applyJsonSource(json.dump(JSON_INTENT));
    }

    void Annotation::deserializeAndPopulate(const std::string& jsonString) {
        Relationship::deserializeAndPopulate(jsonString);
        const nlohmann::json json = nlohmann::json::parse(jsonString);
        std::vector<boost::uuids::uuid> ids;
        if (Json::readReferences(json, "annotatingElement", ids))
            setUnresolvedJsonReferences("annotatingElement", ids);
        if (Json::readReferences(json, "annotatedElement", ids))
            setUnresolvedJsonReferences("annotatedElement", ids);
        if (Json::readReferences(json, "owningAnnotatedElement", ids))
            setUnresolvedJsonReferences("owningAnnotatedElement", ids);
        if (Json::readReferences(json, "owningAnnotatingElement", ids))
            setUnresolvedJsonReferences("owningAnnotatingElement", ids);
        if (Json::readReferences(json, "ownedAnnotatingElement", ids))
            setUnresolvedJsonReferences("ownedAnnotatingElement", ids);
    }

    void Annotation::resolveJsonReferences(const std::function<std::shared_ptr<Element>(const boost::uuids::uuid&)>& lookup) {
        Relationship::resolveJsonReferences(lookup);
        if (const auto ids = unresolvedJsonReferences("annotatingElement")) {
            try {
                if (auto target = std::dynamic_pointer_cast<KerML::Entities::AnnotatingElement>(lookup(ids->front()))) {
                    Annotation::setAnnotatingElement(std::move(target));
                    clearUnresolvedJsonReferences("annotatingElement");
                }
            } catch (const std::exception&) {
                // The reference stays unresolved if the model refuses it.
                setUnresolvedJsonReferences("annotatingElement", *ids);
            }
        }
        if (const auto ids = unresolvedJsonReferences("annotatedElement")) {
            try {
                if (auto target = std::dynamic_pointer_cast<KerML::Entities::Element>(lookup(ids->front()))) {
                    Annotation::setAnnotatedElement(std::move(target));
                    clearUnresolvedJsonReferences("annotatedElement");
                }
            } catch (const std::exception&) {
                // The reference stays unresolved if the model refuses it.
                setUnresolvedJsonReferences("annotatedElement", *ids);
            }
        }
        if (const auto ids = unresolvedJsonReferences("owningAnnotatedElement")) {
            try {
                if (auto target = std::dynamic_pointer_cast<KerML::Entities::Element>(lookup(ids->front()))) {
                    Annotation::setOwningAnnotatedElement(std::move(target));
                    clearUnresolvedJsonReferences("owningAnnotatedElement");
                }
            } catch (const std::exception&) {
                // The reference stays unresolved if the model refuses it.
                setUnresolvedJsonReferences("owningAnnotatedElement", *ids);
            }
        }
        if (const auto ids = unresolvedJsonReferences("owningAnnotatingElement")) {
            try {
                if (auto target = std::dynamic_pointer_cast<KerML::Entities::AnnotatingElement>(lookup(ids->front()))) {
                    Annotation::setOwningAnnotatingElement(std::move(target));
                    clearUnresolvedJsonReferences("owningAnnotatingElement");
                }
            } catch (const std::exception&) {
                // The reference stays unresolved if the model refuses it.
                setUnresolvedJsonReferences("owningAnnotatingElement", *ids);
            }
        }
        if (const auto ids = unresolvedJsonReferences("ownedAnnotatingElement")) {
            try {
                if (auto target = std::dynamic_pointer_cast<KerML::Entities::AnnotatingElement>(lookup(ids->front()))) {
                    Annotation::setOwnedAnnotatingElement(std::move(target));
                    clearUnresolvedJsonReferences("ownedAnnotatingElement");
                }
            } catch (const std::exception&) {
                // The reference stays unresolved if the model refuses it.
                setUnresolvedJsonReferences("ownedAnnotatingElement", *ids);
            }
        }
    }
}
// END GENERATED JSON
