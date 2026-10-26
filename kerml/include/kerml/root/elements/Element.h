//
// Created by Moritz Herzog on 20.03.25.
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
#include <functional>
#include <map>
#include <stdexcept>
#include <string>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/random_generator.hpp>
#include <vector>
#include <optional>
#include <sysmlv2/rest/entities/Data.h>
//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include <kerml/kerml_global.h>
//---------------------------------------------------------
// Forwarding
//---------------------------------------------------------
namespace KerML::Entities {
    class Namespace;
    class Documentation;
    class Annotation;
    class Relationship;
    class TextualRepresentation;
    struct ElementDisposer;
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
    class KERML_EXPORT Element : public SysMLv2::REST::Data{
        friend struct ::KerML::Entities::ElementDisposer;
    public:
        /**
         * Constructor of the Element. This constructor does allow for an empty elementID.
         * @param elementID The Element ID of the Element. If no UUID is provided, a random UUID is provided by the Software.
         * @param owner The Element that owns this element. If no Element is provided the owning element is automatically set to null.
         */
        explicit Element(boost::uuids::uuid elementID = boost::uuids::random_generator()(), std::shared_ptr<Element> owner = nullptr);

        /**
         * Constructor of the Element. This constructor does not allow for an empty elementID.
         * If the string is a JSON object (its first character that is no whitespace is '{') it is the JSON representation of
         * the Element (see serializeToJson()): the Element is created with a random id and populated from the JSON (the id is read
         * from "@id" or "elementId").
         * @param elementID The Element ID of the Element as string, or the JSON representation of the Element.
         * @param owner The Element that owns this element. If no Element is provided the owning element is automatically set to null.
         * @throws std::runtime_error If the string is neither JSON nor a valid UUID.
         * @throws nlohmann::json::parse_error If the string looks like JSON but is not valid JSON.
         */
        explicit Element(std::string elementID, std::shared_ptr<Element> owner = nullptr);

        /**
         * Destructor. An implementation is not required, since shared pointers are used.
         */
        ~Element() override = default;

        /**
         * Gives access to the ElementId as a string.
         * @return String of the element Id.
         */
        [[nodiscard]] std::string elementId() const;

        /**
         * Replaces the generated element id by the id of an imported model (for example the elementId of an XMI file). The id of an
         * element is fixed by definition once it is part of a model: call this directly after the creation of the element, before it is
         * stored anywhere by id.
         * @param elementId The wanted element id.
         */
        void assignElementId(const boost::uuids::uuid& elementId);

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
        void appendAliasId(const std::string& aliasId);

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
        void setDeclaredShortName(const std::string& declaredShortName);

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
        void setDeclaredName(const std::string& declaredName);

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

        /**
         * Creates an Element from its JSON representation (as produced by serializeToJson() or by a SysML v2 API server).
         * This is a factory, because a second constructor taking a std::string would be ambiguous to
         * Element(std::string elementID, ...). It is used for every element type that has no dedicated C++ class in the
         * deserialization (e.g. "Package" or "Feature" payloads of a commit), so the result is always a plain Element.
         *
         * The following keys are read: "@id" (required), "@type" (the original type is kept, getType() returns e.g.
         * "Package"), "elementId" (falls back to "@id" if missing, empty or no valid UUID), "name", "declaredName",
         * "declaredShortName", "shortName", "qualifiedName", "aliasIds", "isLibraryElement" and "isImpliedIncluded".
         * Missing keys, empty strings, nulls and values of a wrong JSON type are tolerated and keep the default.
         *
         * Lossless round trip: the (normalized) JSON is stored and returned unchanged by serializeToJson(), as long as
         * the Element is created by this function. The relations (owner, owned elements, relationships, documentation,
         * annotations, ...) are NOT reconstructed as objects; they are only kept inside this stored JSON. Changing the
         * Element by its setters afterwards does not change the stored JSON.
         * @param jsonString The JSON representation of the element.
         * @return The populated Element.
         * @throws std::invalid_argument If the JSON is no object or "@id" is missing or no valid UUID.
         * @throws nlohmann::json::parse_error If the string is no valid JSON.
         */
        static std::shared_ptr<Element> fromJson(const std::string& jsonString);

        /**
         * Replaces the references to other elements that were read from JSON and are not resolved yet by the elements themselves.
         * Reading JSON (the constructors that take a JSON string) only knows the ids of the referenced elements, because they are
         * delivered as separate JSON objects. The ids are kept until this function is called; serializeToJson() writes them as
         * long as the property is not resolved, so parsing and serializing again does not lose them. Every metaclass overrides this
         * function for its own properties (and calls the function of its base classes first).
         * The stored properties and the derived references that the model keeps as collections or caches (owner, ownedElement, type, ...) are
         * resolved, as far as the JSON holds them; the other derived properties are computed. This only links the elements with each other: the
         * derived properties that the JSON does not hold are rebuilt by linkElements() / createElementsFromJson(), see ElementLinker.h.
         * A reference stays unresolved if the lookup returns no element or an element of a type the property does not accept. A many-valued
         * property is only resolved if all its elements are found.
         * @param lookup Returns the element of an element id, or an empty pointer if it is not known.
         */
        virtual void resolveJsonReferences(const std::function<std::shared_ptr<Element>(const boost::uuids::uuid&)>& lookup);

        /**
         * Tells if references that were read from JSON are still not resolved (see resolveJsonReferences()).
         * @return True if there is at least one reference that is not resolved.
         */
        [[nodiscard]] bool hasUnresolvedJsonReferences() const;

        /**
         * Forgets the JSON the element was created from. An element that was created from JSON (by the constructors that take a
         * JSON string, or by createElementFromJson()) returns the properties of that JSON that it can not reproduce itself (derived
         * properties that are not rebuilt, unknown keys) unchanged as long as the property was not changed after the creation; so a payload of
         * a server is not damaged by reading and writing it. After this call serializeToJson() only reflects the state of the object.
         */
        void discardSourceJson();

        /**
         * Gives the JSON the element was created from, as far as it is still known (see discardSourceJson()). Used when the derived properties
         * are rebuilt: a derived property that the JSON delivered is not rebuilt.
         * @return The JSON, or an empty string if the element was not created from JSON.
         */
        [[nodiscard]] std::string sourceJson() const;

        /**
         * Serializes the Element to JSON. If the Element was created by fromJson() the stored JSON is returned
         * unchanged, otherwise the JSON is generated from the members of the Element.
         * @return The JSON representation of the Element.
         */
        std::string serializeToJson() override;
    protected:
        /**
         *
         * @return
         */
        std::vector<std::shared_ptr<Relationship>> ownedRelationships();

        /**
         * Populates the Element from its JSON representation. Reads only the stored properties; the derived properties (for example
         * ownedElement or owner) are recomputed and ignored. Missing keys, nulls and values of a wrong JSON type are tolerated. The references
         * are only stored as ids, see resolveJsonReferences().
         * @param jsonString The JSON representation of the element.
         */
        void deserializeAndPopulate(const std::string &jsonString) override;

        /**
         * Gives the ids of the elements the property refers to, if they were read from JSON and are not resolved yet.
         * @param property The name of the property of the metamodel.
         * @return The ids, or no value if there are none.
         */
        [[nodiscard]] std::optional<std::vector<boost::uuids::uuid>> unresolvedJsonReferences(const std::string& property) const;

        /**
         * Stores the ids of the elements the property refers to until they are resolved (an empty vector removes the entry).
         * @param property The name of the property of the metamodel.
         * @param ids The ids of the referenced elements.
         */
        void setUnresolvedJsonReferences(const std::string& property, std::vector<boost::uuids::uuid> ids);

        /**
         * Removes the unresolved references of a property, because they are resolved.
         * @param property The name of the property of the metamodel.
         */
        void clearUnresolvedJsonReferences(const std::string& property);

        /**
         * Resolves a single-valued reference that is kept in a cache (see resolveJsonReferences()).
         * @param property The name of the property.
         * @param lookup Finds the elements by their id.
         * @param apply Sets the resolved element.
         */
        template <class T, class Apply>
        void resolveCache(const std::string& property, const std::function<std::shared_ptr<Element>(const boost::uuids::uuid&)>& lookup, Apply&& apply) {
            const auto ids = unresolvedJsonReferences(property);
            if (!ids)
                return;
            try {
                if (auto target = std::dynamic_pointer_cast<T>(lookup(ids->front()))) {
                    apply(std::move(target));
                    clearUnresolvedJsonReferences(property);
                }
            } catch (const std::exception&) {
                // The reference stays unresolved if the model refuses it.
                setUnresolvedJsonReferences(property, *ids);
            }
        }

        /**
         * Resolves a many-valued reference that is kept in a cache; it is resolved if all elements are found (see resolveJsonReferences()).
         * @param property The name of the property.
         * @param lookup Finds the elements by their id.
         * @param apply Sets the resolved elements.
         */
        template <class T, class Apply>
        void resolveCaches(const std::string& property, const std::function<std::shared_ptr<Element>(const boost::uuids::uuid&)>& lookup, Apply&& apply) {
            const auto ids = unresolvedJsonReferences(property);
            if (!ids)
                return;
            try {
                std::vector<std::shared_ptr<T>> resolved;
                for (const auto& id : *ids) {
                    auto target = std::dynamic_pointer_cast<T>(lookup(id));
                    if (!target)
                        break;
                    resolved.push_back(std::move(target));
                }
                if (resolved.size() == ids->size()) {
                    apply(std::move(resolved));
                    clearUnresolvedJsonReferences(property);
                }
            } catch (const std::exception&) {
                // The references stay unresolved if the model refuses them.
                setUnresolvedJsonReferences(property, *ids);
            }
        }

        /**
         * Remembers the JSON the element was created from, see discardSourceJson(). Called by the constructors that populate the element from
         * JSON, as the last step (the object is complete then).
         * @param jsonString The JSON the element was populated from.
         */
        void captureJsonSource(const std::string& jsonString);

        /**
         * Completes the JSON that serializeToJson() of a class produced: the properties of the source JSON that the element did not change
         * since it was created are replaced by the values of the source JSON, and its keys that the class does not produce are added.
         * Every serializeToJson() of the metaclasses ends with this call.
         * @param produced The JSON the class produced.
         * @return The completed JSON.
         */
        std::string applyJsonSource(const std::string& produced);

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
        boost::uuids::uuid ElementId;

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

    private:
        /**
         * 
         */
        std::shared_ptr<Relationship> OwningRelationship;

        /**
         * The normalized JSON the Element was created from by fromJson(). If it is not empty, serializeToJson() returns it.
         */
        std::string OriginalJson;

        /**
         * The ids of the references that were read from JSON and are not resolved yet, by the name of the property.
         */
        std::map<std::string, std::vector<boost::uuids::uuid>> UnresolvedJsonReferences;

        /**
         * The JSON the element was populated from (see captureJsonSource()) and what the element serialized right after that. Empty if the
         * element was not created from JSON.
         */
        std::string SourceJson;
        std::string BaselineJson;
    public:
        std::vector<std::shared_ptr<Relationship>> ownedRelationship() const;
        void setOwnedRelationship(std::vector<std::shared_ptr<Relationship>> value);
        std::vector<std::shared_ptr<Element>> ownedElement() const;
        void setOwnedElement(std::vector<std::shared_ptr<Element>> value);
        std::vector<std::shared_ptr<Documentation>> documentation() const;
        void setDocumentation(std::vector<std::shared_ptr<Documentation>> value);
        std::vector<std::shared_ptr<Annotation>> ownedAnnotation() const;
        void setOwnedAnnotation(std::vector<std::shared_ptr<Annotation>> value);
        std::vector<std::shared_ptr<TextualRepresentation>> textualRepresentation() const;
        void setTextualRepresentation(std::vector<std::shared_ptr<TextualRepresentation>> value);
        std::shared_ptr<Relationship> owningRelationship() const;
        void setOwningRelationship(std::shared_ptr<Relationship> value);
        std::shared_ptr<OwningMembership> owningMembership() const;
        std::shared_ptr<Namespace> owningNamespace() const;
        std::optional<std::string> shortName() const;
        std::optional<std::string> name() const;
        std::optional<std::string> qualifiedName() const;
        void setQualifiedName(std::optional<std::string> value);
        bool isLibraryElement() const;
        void setIsLibraryElement(bool value);
    };


    /**
     * Breaks the reference cycles of one element. An element refers to its owner, owned elements, relationships, types and
     * features through std::shared_ptr in both directions, so a model that is no longer used is not freed by itself. This clears
     * those links of @p element (owner, owned elements and relationships, related elements, memberships, features, types, ...);
     * call it for every element of a model that is thrown away. The element is detached afterwards and must not be used.
     * Elements of the standard classes are covered by kerml/src/kerml/model/ElementDisposer.cpp, which is generated by
     * kerml/tools/generate_dispose.py.
     */
    KERML_EXPORT void disposeLinks(Element& element);
} // KerML::Entities

