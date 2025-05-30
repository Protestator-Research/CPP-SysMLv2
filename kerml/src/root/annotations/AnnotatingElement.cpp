//
// Created by Moritz Herzog on 24.03.25.
//

#include "AnnotatingElement.h"

namespace KerML::Entities {

    AnnotatingElement::AnnotatingElement() : Element(){
        OwningAnnotatingRelationship = nullptr;
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
        OwningAnnotatingRelationship = annotation;
    }

    void AnnotatingElement::sortAnnotatedElements() {

    }
}