//
// Created by Moritz Herzog on 24.03.25.
//

#include <kerml/root/annotations/AnnotatingElement.h>
#include <kerml/KerML.h>
#include <nlohmann/json.hpp>
#include "../../model/JsonSupport.h"

namespace KerML::Entities {

    AnnotatingElement::AnnotatingElement() : Element(){
        OwningAnnotatingRelationship = nullptr;
        _dType = "AnnotatingElement";
    }

    std::vector<std::shared_ptr<Element>> AnnotatingElement::annotatedElements() {
        return AnnotatedElements;
    }

    void AnnotatingElement::appendAnnotatedElement(std::shared_ptr<Element> element) {
        AnnotatedElements.push_back(element);
        setOwner(element);
    }

    void AnnotatingElement::appendAnnotatedElements(std::vector<std::shared_ptr<Element>> elements) {
        AnnotatedElements.insert(AnnotatedElements.end(), elements.begin(), elements.end());
        for(auto element : elements) {
            setOwner(element);
        }
    }

    std::vector<std::shared_ptr<Annotation>> AnnotatingElement::annotations() {
        return Annotations;
    }

    void AnnotatingElement::appendAnnotation(std::shared_ptr<Annotation> annotation) {
        Annotations.push_back(annotation);
    }

    void AnnotatingElement::appendAnnotations(std::vector<std::shared_ptr<Annotation>> annotations) {
        Annotations.insert(Annotations.end(), annotations.begin(), annotations.end());
    }

    std::vector<std::shared_ptr<Annotation>> AnnotatingElement::ownedAnnotatingRelationships() {
        return OwnedAnnotatingRelationship;
    }

    void AnnotatingElement::appendAnnotatingRelationship(std::shared_ptr<Annotation> annotation) {
        OwnedAnnotatingRelationship.push_back(annotation);
    }

    void AnnotatingElement::appendAnnotatingRelationships(std::vector<std::shared_ptr<Annotation>> annotations) {
        OwnedAnnotatingRelationship.insert(OwnedAnnotatingRelationship.end(), annotations.begin(), annotations.end());
    }

    std::shared_ptr<Annotation> AnnotatingElement::owningAnnotatingRelationship() {
        return OwningAnnotatingRelationship;
    }

    void AnnotatingElement::setOwningAnnotatingRelationship(std::shared_ptr<Annotation> annotation) {
        clearUnresolvedJsonReferences("owningAnnotatingRelationship");
        OwningAnnotatingRelationship = annotation;
    }

    void AnnotatingElement::sortAnnotatedElements() {

    }
}

// BEGIN GENERATED JSON (kerml/tools/generate_json.py): do not edit, run the script instead.
namespace KerML::Entities {
    AnnotatingElement::AnnotatingElement(const std::string& nameOrJson) :
        AnnotatingElement() {
        _dType = "AnnotatingElement";
        if (Json::looksLikeJson(nameOrJson)) {
            deserializeAndPopulate(nameOrJson);
            captureJsonSource(nameOrJson);
        } else {
            setDeclaredName(nameOrJson);
        }
    }

    std::string AnnotatingElement::serializeToJson() {
        nlohmann::json json = nlohmann::json::parse(Element::serializeToJson());
        json["annotatedElement"] = Json::reference(unresolvedJsonReferences("annotatedElement"), AnnotatingElement::annotatedElement());
        json["ownedAnnotatingRelationship"] = Json::reference(unresolvedJsonReferences("ownedAnnotatingRelationship"), AnnotatingElement::ownedAnnotatingRelationship());
        json["owningAnnotatingRelationship"] = Json::reference(unresolvedJsonReferences("owningAnnotatingRelationship"), AnnotatingElement::owningAnnotatingRelationship());
        json["annotation"] = Json::reference(unresolvedJsonReferences("annotation"), AnnotatingElement::annotation());
        return applyJsonSource(json.dump(JSON_INTENT));
    }

    void AnnotatingElement::deserializeAndPopulate(const std::string& jsonString) {
        Element::deserializeAndPopulate(jsonString);
        const nlohmann::json json = nlohmann::json::parse(jsonString);
        std::vector<boost::uuids::uuid> ids;
        if (Json::readReferences(json, "owningAnnotatingRelationship", ids))
            setUnresolvedJsonReferences("owningAnnotatingRelationship", ids);
    }

    void AnnotatingElement::resolveJsonReferences(const std::function<std::shared_ptr<Element>(const boost::uuids::uuid&)>& lookup) {
        Element::resolveJsonReferences(lookup);
        if (const auto ids = unresolvedJsonReferences("owningAnnotatingRelationship")) {
            try {
                if (auto target = std::dynamic_pointer_cast<KerML::Entities::Annotation>(lookup(ids->front()))) {
                    AnnotatingElement::setOwningAnnotatingRelationship(std::move(target));
                    clearUnresolvedJsonReferences("owningAnnotatingRelationship");
                }
            } catch (const std::exception&) {
                // The reference stays unresolved if the model refuses it.
                setUnresolvedJsonReferences("owningAnnotatingRelationship", *ids);
            }
        }
    }
}
// END GENERATED JSON
