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
        friend struct ::KerML::Entities::ElementDisposer;
    public:
        /**
         * Constructor of the Relationship. This constructor does allow for an empty elementID.
         * @param elementID The Element ID of the Relationship. If no UUID is provided, a random UUID is provided by the Software.
         * @param owner The Element that owns this Relationship. If no Element is provided the owning element is automatically set to null.
         */
        explicit Annotation(boost::uuids::uuid elementID = boost::uuids::random_generator()(), std::shared_ptr<Element> owner = nullptr);
        /**
         * Constructor of the Relationship. The element gets a random element id.
         * @param nameOrJson The declared name of the Relationship, or its JSON representation.
         * @param owner The Element that owns this relationship. If no Element is provided the owning element is automatically set to null.
         * If the string is a JSON object (it starts with '{') it is the JSON representation of the element, see serializeToJson(); otherwise it is the declared name.
         */
        explicit Annotation(std::string nameOrJson, std::shared_ptr<Element> owner = nullptr);

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

    // BEGIN GENERATED JSON (kerml/tools/generate_json.py): do not edit, run the script instead.
    public:
        /**
         * Serializes the Annotation to JSON: all properties of the metaclass (stored and derived ones). References to other elements are
         * only written as identities ({"@id": "<uuid>"}), never recursively.
         * @return The JSON representation of the Annotation.
         */
        std::string serializeToJson() override;

        /**
         * Resolves the references that were read from JSON to the elements (see Element::resolveJsonReferences()), for the properties
         * of Annotation and of its base classes.
         * @param lookup Returns the element of an element id, or an empty pointer if it is not known.
         */
        void resolveJsonReferences(const std::function<std::shared_ptr<Element>(const boost::uuids::uuid&)>& lookup) override;

    protected:
        /**
         * Populates the Annotation from its JSON representation; the stored properties of Annotation and of its base classes are read,
         * computed derived properties are ignored, the derived references that the model keeps as collections are read like the stored ones,
         * and references are only stored as ids.
         * @param jsonString The JSON representation of the Annotation.
         */
        void deserializeAndPopulate(const std::string& jsonString) override;
    // END GENERATED JSON
    };
} // KerML::Entities
