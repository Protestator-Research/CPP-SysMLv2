//
// Created by Moritz Herzog on 24.03.25.
//
//---------------------------------------------------------
// Constants, Definitions, Pragmas
//---------------------------------------------------------
#pragma once
//---------------------------------------------------------
// External Classes
//---------------------------------------------------------
#include <kerml/root/elements/Relationship.h>
#include <memory>
//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include "../../kerml_global.h"
//---------------------------------------------------------
// Forwarding
//---------------------------------------------------------

namespace KerML::Entities {
    class Element;
    class AnnotatingElement;
    /**
     *
     */
    class KERML_EXPORT Annotation : public Relationship {
    public:
        /**
         * Constructor of the Relationship. This constructor does allow for an empty elementID.
         * @param elementID The Element ID of the Relationship. If no UUID is provided, a random UUID is provided by the Software.
         * @param owner The Element that owns this Relationship. If no Element is provided the owning element is automatically set to null.
         */
        explicit Annotation(boost::uuids::uuid elementID = boost::uuids::random_generator()(), std::shared_ptr<Element> owner = nullptr);
        /**
         * Constructor of the Relationship. This constructor does not allow for an empty elementID.
         * @param elementID The Element ID of the Relationship as string.
         * @param owner The Element that owns this relationship. If no Element is provided the owning element is automatically set to null.
         */
        explicit Annotation(std::string elementID, std::shared_ptr<Element> owner = nullptr);

        [[nodiscard]] std::shared_ptr<Element> owningAnnotatedElement() const;
        void setOwningAnnotatedElement(std::shared_ptr<Element> owningAnnotatedElement);

        [[nodiscard]] std::shared_ptr<Element> annotatedElement();
        void setAnnotatedElement(std::shared_ptr<Element> annotatedElement);

        [[nodiscard]] std::shared_ptr<AnnotatingElement> annotatingElement() const;
        void setAnnotatingElement(std::shared_ptr<AnnotatingElement> annotatingElement);

        [[nodiscard]] std::shared_ptr<AnnotatingElement> ownedAnnotatingElement() const;
        void setOwnedAnnotatingElement(std::shared_ptr<AnnotatingElement> ownedAnnotatingElement);

        [[nodiscard]] std::shared_ptr<AnnotatingElement> owningAnnotatingElement() const;
        void setOwningAnnotatingElement(std::shared_ptr<AnnotatingElement> owningAnnotatingElement);

    private:
        std::shared_ptr<Element> OwningAnnotatedElement;
        std::shared_ptr<Element> AnnotatedElement;

        std::shared_ptr<AnnotatingElement> _AnnotatingElement;
        std::shared_ptr<AnnotatingElement> OwnedAnnotatingElement;
        std::shared_ptr<AnnotatingElement> OwningAnnotatingElement;
    };
} // KerML::Entities
