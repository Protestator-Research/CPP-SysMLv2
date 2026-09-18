//
// Created by Moritz Herzog on 24.03.25.
//

#include <kerml/root/elements/Relationship.h>
#include <stdexcept>
#include <functional>
#include <algorithm>

namespace KerML::Entities {
    Relationship::Relationship(boost::uuids::uuid elementID, std::shared_ptr<Element> owner) : Element(elementID, owner) {
        _dType = "Relationship";
    }

    Relationship::Relationship(std::string elementID, std::shared_ptr<Element> owner) : Element(elementID, owner) {
        _dType = "Relationship";
    }

    void Relationship::setIsImplied(bool isImplied) {
        IsImplied = isImplied;
    }

    bool Relationship::isImplied() {
        return IsImplied;
    }

    void Relationship::appendElementToOwnedRelatedElement(std::shared_ptr<Element> element) {
        OwnedRelatedElements.push_back(element);
        sortOwnedRelatedElements();
    }

    std::shared_ptr<Namespace> Relationship::libraryNamespace() const {
        return Element::libraryNamespace();
    }

    void Relationship::setOwnedRelatedElements(std::vector<std::shared_ptr<Element>> elements) {
        OwnedRelatedElements = elements;
        sortOwnedRelatedElements();
    }

    std::vector<std::shared_ptr<Element>> Relationship::ownedRelatedElement() const {
        return OwnedRelatedElements;
    }

    void Relationship::setOwningRelatedElement(std::shared_ptr<Element> owningRelatedElement) {
        OwningRelatedElement = owningRelatedElement;
    }

    std::shared_ptr<Element> Relationship::owningRelatedElement() const {
        return OwningRelatedElement;
    }

    void Relationship::sortOwnedRelatedElements() {
        // Preserve the order supplied by the model.
    }

    void Relationship::sortRelatedElements() {
        // Preserve the order supplied by the model.
    }

    void Relationship::sortSourceElements() {
        // Preserve the order supplied by the model.
    }

    void Relationship::sortTargetElements() {
        // Preserve the order supplied by the model.
    }

    void Relationship::setRelatedElements(std::vector<std::shared_ptr<Element>> relatedElements) {
        RelatedElements = std::move(relatedElements);
        sortRelatedElements();
    }

    std::vector<std::shared_ptr<Element>> Relationship::relatedElements() const {
        return RelatedElements;
    }

    void Relationship::appendElementToRelatedElements(std::shared_ptr<Element> element) {
        RelatedElements.push_back(element);
        sortRelatedElements();
    }
} // KerML::Entities