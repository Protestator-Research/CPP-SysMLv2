//
// Links elements that were created from JSON.
//
//---------------------------------------------------------
// Constants, Definitions, Pragmas
//---------------------------------------------------------
#pragma once
//---------------------------------------------------------
// External Classes
//---------------------------------------------------------
#include <memory>
#include <vector>
//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include <kerml/root/elements/Element.h>
#include <kerml/kerml_global.h>
//---------------------------------------------------------
// Forwarding
//---------------------------------------------------------
namespace KerML::Entities {
    class Relationship;
}
//---------------------------------------------------------

namespace KerML::Entities {
    /**
     * Resolves the references of elements that were created from JSON to each other (Element::resolveJsonReferences(), the elements are looked
     * up by their id among @p elements) and rebuilds the derived properties afterwards (rebuildDerivedProperties()). Use this for the elements
     * that belong together, for example the elements of one commit.
     * @param elements The elements, for example created by createElementFromJson().
     */
    KERML_EXPORT void linkElements(const std::vector<std::shared_ptr<Element>>& elements);

    /**
     * Rebuilds the derived properties that the elements keep as collections and caches (owner, ownedElement, the members, memberships and
     * imports of the namespaces, the owned features, specializations, typings, ... of the types and features, the typed ends of the
     * memberships) from the stored properties (owningRelationship, ownedRelationship, owningRelatedElement, the ends of the relationships, ...).
     * This is what the parsers do while they create a model. A derived property that the JSON of the element delivered is not touched (it is
     * resolved by Element::resolveJsonReferences()), only the missing ones are rebuilt; the same holds for an element that was created without
     * JSON: everything is rebuilt. The function can be called repeatedly: an entry is only added if it is missing.
     * @param elements The elements of the model.
     */
    KERML_EXPORT void rebuildDerivedProperties(const std::vector<std::shared_ptr<Element>>& elements);

    /**
     * Registers a relationship at the element that owns it: in the typed collections of that element (ownedRedefinition, ownedTyping,
     * ownedSpecialization, ...) and with the owning end of the relationship. Does nothing if the relationship has no owning related element.
     * Used by rebuildDerivedProperties() and by the XMI reader.
     * @param relationship The relationship.
     */
    KERML_EXPORT void registerOwnedRelationship(const std::shared_ptr<Relationship>& relationship);
} // KerML::Entities
