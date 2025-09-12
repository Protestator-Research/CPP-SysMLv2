//
// Created by Moritz Herzog on 20.03.25.
//
//---------------------------------------------------------
// Constants, Definitions, Pragmas
//---------------------------------------------------------
#pragma once
//---------------------------------------------------------
// External Classes
//---------------------------------------------------------
#include <memory>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/random_generator.hpp>
#include <vector>
#include <optional>
//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include "../../kerml_global.h"
//---------------------------------------------------------
// Forwarding
//---------------------------------------------------------
namespace KerML::Entities {
    class Namespace;
    class Documentation;
    class Annotation;
    class Relationship;
    class TextualRepresentation;
}
//---------------------------------------------------------

namespace KerML::Entities {
    /**
     * @class Element
     * @author Moritz Herzog
     * @version 1.0 Beta 4
     * @brief This part of the model allows the identification of all elements.
     * This part of the model allows the identification of all elements. This is a core concept of the KerML and SysML syntax.
     * Also this class is required for the REST-API and the parsing of the models.
     */
    class KERML_EXPORT Element {
    public:
        /**
         * Constructor of the Element. This constructor does allow for an empty elementID.
         * @param elementID The Element ID of the Element. If no UUID is provided, a random UUID is provided by the Software.
         * @param owner The Element that owns this element. If no Element is provided the owning element is automatically set to null.
         */
        explicit Element(boost::uuids::uuid elementID = boost::uuids::random_generator()(), std::shared_ptr<Element> owner = nullptr);

        /**
         * Constructor of the Element. This constructor does not allow for an empty elementID.
         * @param elementID The Element ID of the Element as string.
         * @param owner The Element that owns this element. If no Element is provided the owning element is automatically set to null.
         */
        explicit Element(std::string elementID, std::shared_ptr<Element> owner = nullptr);

        /**
         * Destructor. An implementation is not required, since shared pointers are used.
         */
        virtual ~Element() = default;

        /**
         * Gives access to the ElementId as a string.
         * @return String of the element Id.
         */
        [[nodiscard]] std::string elementId() const;

        /**
         * Gives acces to the ElementId as a uuid. This makes the internal comparison eayser.
         * @return Element id of the Element as a uuid.
         */
        [[nodiscard]] boost::uuids::uuid elementIdAsUUID() const;

        /**
         * Sets the various alternative Identifiers and overrides them with the given value.
         * @param aliasIds The given AliasIds.
         */
        void setAliasIds(std::vector<std::string> aliasIds);

        /**
         * Add another alternative Identifier.
         * @param aliasId the given alternative Identifier.
         */
        void appendAliasId(std::string& aliasId);

        /**
         * Gives access to the alternative Identifiers for one specific element.
         * @return A vector of the values. Not possible to set values via this function.
         */
        [[nodiscard]] std::vector<std::string> aliasIds() const;

        /**
         * Sets the declared short name, this is an optional alternative name of the Element. This may act as a modeller-
         * specific identifier.
         * @param declaredShortName The wanted declared short name.
         */
        void setDeclaredShortName(std::string& declaredShortName);

        /**
         * Returns the declared short name. This is a modeller-specific primary name. It has the responsibility of beeing
         * unique in the specific context or within a model.
         * @return The declared short name.
         */
        [[nodiscard]] std::optional<std::string> declaredShortName() const;

        /**
         * Sets the declared name of the Element.
         * @param declaredName declared name of the Element.
         */
        void setDeclaredName(std::string& declaredName);

        /**
         * Gives access to the declared name.
         * @return The internally stored declared name.
         */
        [[nodiscard]] std::optional<std::string> declaredName() const;

        /**
         * Sets if element is included in a implied.
         * @param isImpliedIncluded
         */
        void setImpliedIncluded(bool& isImpliedIncluded);

        /**
         * Defines if the relationships to / from this element are implied by the relationships.
         * @return True if any relationship to this element is implied.
         */
        [[nodiscard]] bool isImpliedIncluded() const;

        /**
         * 
         * @return
         */
        [[nodiscard]] std::optional<std::string> escapedName() const;

        /**
         * Returns the effective ShortName of this Element. By default it is the DeclaredShortName.
         * @return The effective short name of this Element.
         */
        [[nodiscard]] virtual std::optional<std::string> effectiveShortName() const;

        /**
         * This method returns the effective name of a element. By default this is the declaredName().
         * @return The effective name that is available.
         */
        [[nodiscard]] virtual std::optional<std::string> effectiveName() const;

        /**
         * If this Element has a owningRelationship, the Namespace of this Relationship is returned.
         * @return Namespace of the  owningRelationship, if available.
         */
        [[nodiscard]] virtual std::shared_ptr<Namespace> libraryNamespace() const;

        /**
         * This operator is deleted, because the ElementId can not be reset by definition.
         * @param other The element that one wants to set this element to.
         * @return This element.
         */
        Element& operator=(const Element& other) = delete;

        /**
         * Compares the equality of the elements. This is mainly done by the ElementId, because of the properties of the UUID.
         * @param other The other Element, that is to compare with this element.
         * @return If the Element is the same as the other Element.
         */
        virtual bool operator==(const Element& other);

        /**
         * Compares one element to the other and decides which one is smaller. 
         * This is required for the std::map, therefore a comparison between the elements is required. Not part of the Standard!
         * To compare the two elements the compare function of boost::uuids::uuid is used.
         * @param other The other Element that is compared against.
         * @return True if the current element has a smaller UUID than the other element.
         * @see boost::uuids::uuid::operator<
         */
        virtual bool operator<(const Element& other);

        /**
         * Compares one element to the other and decides which one is bigger.
         * This is required for the std::map, therefore a comparison between the elements is required. Not part of the Standard!
         * To compare the two elements the compare function of boost::uuids::uuid is used.
         * @param other The other Element that is compared against.
         * @return True if the current element has a bigger UUID than the other element.
         * @see boost::uuids::uuid::operator>
         */
        virtual bool operator>(const Element& other);

        /**
         *
         * @param other
         * @return
         */
        virtual bool operator<=(const Element& other);

        /**
         *
         * @param other
         * @return
         */
        virtual bool operator>=(const Element& other);

        /**
         * Returns the owning Element. The owner is the element referenced in the owningRelationship as the owningRelatedElement.
         * @return Shared pointer of the Owner.
         */
        [[nodiscard]] std::shared_ptr<Element> owner() const;

        /**
         * Sets the owner. The owner is the element referenced in the owningRelationship as the owningRelatedElement.
         * @param owner The related Element, that is represended as owningRelatedElement in the owning Relationship.
         */
        void setOwner(std::shared_ptr<Element> owner);

        /**
         * This method overwrites the Elements of the owned elements. Warning this method deletes the old vector of owned Elements.
         * If you want to append the elements of another vector please refer to Element::appendOwnedElements(std::vector<std::shared_ptr<Element>> ownedElements).
         * @param ownedElements The new owned elements of the element.
         */
        void setOwnedElements(std::vector<std::shared_ptr<Element>> ownedElements);

        /**
         * This methods appends one owned element to the vector of the owned elements and sorts it, because the owned elements should be sorted
         * @param ownedElement The element that is appended to the ownedElements.
         */
        void appendOwnedElement(std::shared_ptr<Element> ownedElement);

        /**
         * Appends owned elements to the internally managed ownedElements and sorts them afterwards.
         * @param ownedElements The vector that is integrated into the ownedElements
         */
        void appendOwnedElements(std::vector<std::shared_ptr<Element>> ownedElements);

        /**
         * Returns the complete vector copy of the owned Elements.
         * @return A copy of the Owned Elements.
         */
        std::vector<std::shared_ptr<Element>> ownedElements();


        /**
         * Returns a unique description of the location of this specific element. Herby the conatining Structure is to consider.
         * @return Description where the element is to be found.
         */
        virtual std::string path();

        /**
         * 
         * @param element 
         * @return 
         */
        virtual bool includes(std::shared_ptr<Element> element);
    protected:
        std::vector<std::shared_ptr<Relationship>> ownedRelationships();




    private:
        /**
        * Orders the AliasIds in their Array. Is per definition required to have the AliasIds always ordered.
        */
        void sortAliasIds();

        /**
         * Represents the global unique Identifier.
         * In this case the ElementId is stored as a UUID, against the standard. Allowing us to address even more elements in an
         * ElementId is according to the KerML standard not allowed to change.
         */
        const boost::uuids::uuid ElementId;

        /**
         * Alternative descriptors of the specific element.
         */
        std::vector<std::string> AliasIds;

        /**
         * An optional alternative name of the 
         */
        std::string DeclaredShortName;

        /**
         * 
         */
        std::string DeclaredName;

        /**
         * Represents the Relationships for which this Element is the owning related Element.
         */
        std::vector<std::shared_ptr<Relationship>> OwnedRelationships;

        /**
         * Displays if a relationship is not included in the OwnedRelationships of the element.
         */
        bool IsImpliedIncluded = false;

        /**
         * The owner is the element referenced in the owningRelationship as the owningRelatedElement.
         */
        std::shared_ptr<Element> Owner = nullptr;


        std::vector<std::shared_ptr<Element>> OwnedElements;
        std::string ShortName;
        std::string Name;
        std::string QualifiedName;

        /**
         * Is true if the Element is contained in an ownership tree of a library.
         */
        bool IsLibraryElement = false;

        /**
         * Represents the documentation, shared by this Element. This List needs to be ordered
         */
        std::vector<std::shared_ptr<Documentation>> Documentations;

        /**
         *
         */
        std::vector<std::shared_ptr<Annotation>> OwnedAnnotations;

        /**
         *
         */
        std::vector<std::shared_ptr<TextualRepresentation>> TextualRepresentations;

        /**
        * Orders the OwnedRelationships in their Array. This is reuired per definition and needs to be called with
        * with every adding of a relationship.
        */
        void sortOwnedRelationships();

        /**
         * Orders the Owned Elements. This is per definition required. With every adding and removing of one OwnedElements
         * this function needs to be called.
         */
        void sortOwnedElements();

        /**
         * 
         */
        std::shared_ptr<Relationship> OwningRelationship;
    };

} // KerML::Entities

