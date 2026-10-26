//
// Created by Moritz Herzog on 24.03.25.
//
//---------------------------------------------------------
// Constants, Definitions, Pragmas
//---------------------------------------------------------
#pragma once
#include <kerml/model/Forward.h>
//---------------------------------------------------------
// External Classes
//---------------------------------------------------------
#include <memory>
//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include <kerml/root/elements/Element.h>
#include <kerml/kerml_global.h>
//---------------------------------------------------------
// Forwarding
//---------------------------------------------------------
namespace KerML::Entities
{
    class Namespace;
}

namespace KerML::Entities {
    /**
     * @class Relationship
     * @author Moritz Herzog
     * @version 1.0 Beta 2
     * A Relationship is an Element that relates two elements to each other.
     */
    class KERML_EXPORT Relationship : public virtual Element {
        friend struct ::KerML::Entities::ElementDisposer;
    public:
        /**
         * Constructor of the Relationship. This constructor does allow for an empty elementID.
         * @param elementID The Element ID of the Relationship. If no UUID is provided, a random UUID is provided by the Software.
         * @param owner The Element that owns this Relationship. If no Element is provided the owning element is automatically set to null.
         */
        explicit Relationship(boost::uuids::uuid elementID = boost::uuids::random_generator()(), std::shared_ptr<Element> owner = nullptr);
        /**
        * Constructor of the Relationship. This constructor does not allow for an empty elementID.
        * @param elementID The Element ID of the Relationship as string.
        * @param owner The Element that owns this relationship. If no Element is provided the owning element is automatically set to null.
        * If the string is a JSON object (it starts with '{') it is the JSON representation of the element, see serializeToJson(); otherwise it is the element id.
        */
        explicit Relationship(std::string elementID, std::shared_ptr<Element> owner = nullptr);

        /**
         * Destructor. An implementation is not required, since shared pointer are used.
         */
        virtual ~Relationship() = default;

        /**
         * Sets the Implied option. This should be set true if the relationship is implied by the elements.
         * @param isImplied Is set by most tools, to meet semantic rules.
         */
        void setIsImplied(bool isImplied);
        /**
         * Returns the is Implied option. This option is set by tools, to meet semantic standards.
         * @return The is Implied option.
         */
        bool isImplied();

        /**
         *
         * @return
         */
        std::shared_ptr<Namespace> libraryNamespace() const override;

        /**
         * Appends one Element to the Owned Related Element list.
         * @param element Shared pointer of an element.
         */
        void appendElementToOwnedRelatedElement(std::shared_ptr<Element> element);

        /**
         *
         * @param elements
         */
        void setOwnedRelatedElements(std::vector<std::shared_ptr<Element>> elements);

        /**
         *
         * @return
         */
        [[nodiscard]] std::vector<std::shared_ptr<Element>> ownedRelatedElement() const;

        /**
         * Sets the owning related element. This is the element that owns this specific relationship.
         * This can also be null. This method checks also, if the given element is contained inside of the ownedRelatedElements.
         * @param owningRelatedElement The element that owns this relationship as shared pointer.
         * @throw std::exception If the element is not in the ownedRelatedElements list an exception is thrown.
         */
        void setOwningRelatedElement(std::shared_ptr<Element> owningRelatedElement);

        /**
         * Returns the owning related Element. It is to remember that the owning related Element can be NULL per definition.
         * @return The owningRelatedElement, if available.
         */
        [[nodiscard]] std::shared_ptr<Element> owningRelatedElement() const;


    public:
        /**
         * Allows to set the related Elements in bulk.
         * @param relatedElements The given list of related Elements.
         */
        void setRelatedElements(std::vector<std::shared_ptr<Element>> relatedElements);

        /**
         * Returns the full and sorted list of the related elements.
         * @return Returns the vectors of the related Elements.
         */
        [[nodiscard]] std::vector<std::shared_ptr<Element>> relatedElements() const;

        /**
         * Appends one element to the related elements vector.
         * @param element A shared pointer to the related element.
         */
        void appendElementToRelatedElements(std::shared_ptr<Element> element);

    private:
        void sortOwnedRelatedElements();
        void sortRelatedElements();
        void sortSourceElements();
        void sortTargetElements();

        bool IsImplied=false;
        std::vector<std::shared_ptr<Element>> OwnedRelatedElements;
        std::shared_ptr<Element> OwningRelatedElement = nullptr;
        std::vector<std::shared_ptr<Element>> RelatedElements;
        std::vector<std::shared_ptr<Element>> Source;
        std::vector<std::shared_ptr<Element>> Target;
    public:
        std::vector<std::shared_ptr<Element>> source() const;
        void setSource(std::vector<std::shared_ptr<Element>> value);
        std::vector<std::shared_ptr<Element>> target() const;
        void setTarget(std::vector<std::shared_ptr<Element>> value);
        std::vector<std::shared_ptr<Element>> relatedElement() const;

    // BEGIN GENERATED JSON (kerml/tools/generate_json.py): do not edit, run the script instead.
    public:
        /**
         * Serializes the Relationship to JSON: all properties of the metaclass (stored and derived ones). References to other elements are
         * only written as identities ({"@id": "<uuid>"}), never recursively.
         * @return The JSON representation of the Relationship.
         */
        std::string serializeToJson() override;

        /**
         * Resolves the references that were read from JSON to the elements (see Element::resolveJsonReferences()), for the properties
         * of Relationship and of its base classes.
         * @param lookup Returns the element of an element id, or an empty pointer if it is not known.
         */
        void resolveJsonReferences(const std::function<std::shared_ptr<Element>(const boost::uuids::uuid&)>& lookup) override;

    protected:
        /**
         * Populates the Relationship from its JSON representation; the stored properties of Relationship and of its base classes are read,
         * computed derived properties are ignored, the derived references that the model keeps as collections are read like the stored ones,
         * and references are only stored as ids.
         * @param jsonString The JSON representation of the Relationship.
         */
        void deserializeAndPopulate(const std::string& jsonString) override;
    // END GENERATED JSON
    };
} // KerML::Entities
