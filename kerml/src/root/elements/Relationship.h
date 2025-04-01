//
// Created by Moritz Herzog on 24.03.25.
//

#ifndef SYSMLV2_RELATIONSHIP_H
#define SYSMLV2_RELATIONSHIP_H

#include "Element.h"
#include <memory>

namespace KerML::Entities {
    class Namespace;
    /**
     * @class Relationship
     * @author Moritz Herzog
     * @version 1.0 Beta 2
     *
     *
     */
    class Relationship : public Element {
    public:
        Relationship(boost::uuids::uuid elementID = boost::uuids::random_generator()(), std::shared_ptr<Element> owner = nullptr);
        virtual ~Relationship();

        void setIsImplied(bool isImplied);
        bool isImplied();

        std::shared_ptr<Namespace> libraryNamespace() override;

        void appendElementToOwnedRelatedElement(std::shared_ptr<Element> element);

        void setOwnedRelatedElements(std::vector<std::shared_ptr<Element>> elements);

        std::vector<std::shared_ptr<Element>> ownedRelatedElement();

    protected:


    private:
        void sortOwnedRelatedElements();
        bool IsImplied=false;
        std::vector<std::shared_ptr<Element>> OwnedRelatedElements;
        std::shared_ptr<Element> OwningRelatedElement;

    };
} // KerML::Entities

#endif //SYSMLV2_RELATIONSHIP_H
