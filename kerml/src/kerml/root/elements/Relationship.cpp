//
// Created by Moritz Herzog on 24.03.25.
//

#include <kerml/root/elements/Relationship.h>
#include <stdexcept>
#include <functional>
#include <algorithm>

namespace KerML::Entities {
    Relationship::Relationship(boost::uuids::uuid elementID, std::shared_ptr<Element> owner) : Element(elementID, owner) {

    }

    Relationship::Relationship(std::string elementID, std::shared_ptr<Element> owner) : Element(elementID, owner) {

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
        if (std::find(OwnedRelatedElements.begin(), OwnedRelatedElements.end(), owningRelatedElement)==OwnedRelatedElements.end())
            throw std::runtime_error("Owning related element has to be inside of the owned related elements.");

        OwningRelatedElement = owningRelatedElement;
    }

    std::shared_ptr<Element> Relationship::owningRelatedElement() const {
        return OwningRelatedElement;
    }

    void Relationship::sortOwnedRelatedElements() {
        std::function<bool(std::shared_ptr<Element> lhs, std::shared_ptr<Element> rhs)>  comparisonFunction=
                [](std::shared_ptr<Element> lhs, std::shared_ptr<Element> rhs){
                    return  (*lhs) < (*rhs);
                };
        std::sort(OwnedRelatedElements.begin(), OwnedRelatedElements.end(), comparisonFunction);
    }

    void Relationship::sortRelatedElements() {
        std::function<bool(std::shared_ptr<Element> lhs, std::shared_ptr<Element> rhs)>  comparisonFunction=
                [](std::shared_ptr<Element> lhs, std::shared_ptr<Element> rhs){
                    return  (*lhs) < (*rhs);
                };
        std::sort(RelatedElements.begin(), RelatedElements.end(), comparisonFunction);
    }

    void Relationship::sortSourceElements() {
        std::function<bool(std::shared_ptr<Element> lhs, std::shared_ptr<Element> rhs)>  comparisonFunction=
                [](std::shared_ptr<Element> lhs, std::shared_ptr<Element> rhs){
                    return  (*lhs) < (*rhs);
                };
        std::sort(Source.begin(), Source.end(), comparisonFunction);
    }

    void Relationship::sortTargetElements() {
        std::function<bool(std::shared_ptr<Element> lhs, std::shared_ptr<Element> rhs)>  comparisonFunction=
                [](std::shared_ptr<Element> lhs, std::shared_ptr<Element> rhs){
                    return  (*lhs) < (*rhs);
                };
        std::sort(Target.begin(), Target.end(), comparisonFunction);
    }

    void Relationship::setRelatedElements(std::vector<std::shared_ptr<Element>> relatedElements) {
        RelatedElements.insert( RelatedElements.end(), relatedElements.begin(), relatedElements.end() );
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