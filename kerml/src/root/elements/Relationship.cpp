//
// Created by Moritz Herzog on 24.03.25.
//

#include "Relationship.h"

namespace KerML::Entities {
    Relationship::Relationship(boost::uuids::uuid elementID, std::shared_ptr<Element> owner) : Element(elementID,
                                                                                                       owner) {

    }

    Relationship::~Relationship() {

    }

    void Relationship::setIsImplied(bool isImplied) {

    }

    bool Relationship::isImplied() {
        return false;
    }

    void Relationship::appendElementToOwnedRelatedElement(std::shared_ptr<Element> element) {

    }

    std::shared_ptr<Namespace> Relationship::libraryNamespace() {
        return Element::libraryNamespace();
    }

    void Relationship::setOwnedRelatedElements(std::vector<std::shared_ptr<Element>> elements) {

    }

    std::vector<std::shared_ptr<Element>> Relationship::ownedRelatedElement() {
        return std::vector<std::shared_ptr<Element>>();
    }

    void Relationship::sortOwnedRelatedElements() {

    }
} // KerML::Entities