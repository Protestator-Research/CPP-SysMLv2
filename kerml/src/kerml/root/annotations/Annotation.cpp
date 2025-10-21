//
// Created by Moritz Herzog on 24.03.25.
//

#include <kerml/root/annotations/Annotation.h>

namespace KerML::Entities {

    Annotation::Annotation(boost::uuids::uuid elementID, std::shared_ptr<Element> owner) :
    Relationship(elementID, owner) {

    }

    Annotation::Annotation(std::string elementID, std::shared_ptr<Element> owner) :
    Relationship(elementID, owner) {

    }

    std::shared_ptr<Element> Annotation::owningAnnotatedElement() const {
        return OwningAnnotatedElement;
    }

    void Annotation::setOwningAnnotatedElement(std::shared_ptr<Element> owningAnnotatedElement) {
        OwningAnnotatedElement = owningAnnotatedElement;
    }

    std::shared_ptr<AnnotatingElement> Annotation::annotatingElement() const {
        return _AnnotatingElement;
    }

    void Annotation::setAnnotatingElement(std::shared_ptr<AnnotatingElement> annotatingElement) {
        _AnnotatingElement = annotatingElement;
    }

    std::shared_ptr<AnnotatingElement> Annotation::ownedAnnotatingElement() const {
        return std::shared_ptr<AnnotatingElement>();
    }

    void Annotation::setOwnedAnnotatingElement(std::shared_ptr<AnnotatingElement> ownedAnnotatingElement) {
        OwnedAnnotatingElement = ownedAnnotatingElement;
    }

    std::shared_ptr<AnnotatingElement> Annotation::owningAnnotatingElement() const {
        return OwningAnnotatingElement;
    }

    void Annotation::setOwningAnnotatingElement(std::shared_ptr<AnnotatingElement> owningAnnotatingElement) {
        OwningAnnotatingElement = owningAnnotatingElement;
    }

    std::shared_ptr<Element> Annotation::annotatedElement() {
        return AnnotatedElement;
    }

    void Annotation::setAnnotatedElement(std::shared_ptr<Element> annotatedElement) {
        AnnotatedElement = annotatedElement;
    }

} // KerML::Entities