//
// Created by Moritz Herzog on 25.03.25.
//
//---------------------------------------------------------
// Constants, Definitions, Pragmas
//---------------------------------------------------------
#pragma once
#include <kerml/model/Forward.h>
//---------------------------------------------------------
// External Classes
//---------------------------------------------------------
#include <boost/uuid/uuid.hpp>
#include <string>
#include <optional>
//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------

#include <kerml/root/elements/Relationship.h>
#include <kerml/root/namespaces/VisibilityKind.h>
#include <kerml/kerml_global.h>
//---------------------------------------------------------
// Forwarding
//---------------------------------------------------------


namespace KerML::Entities {
    class KERML_EXPORT Membership : public Relationship {
    public:
        Membership();
        ~Membership() override = default;

        VisibilityKind visibility();
        void setVisibility(VisibilityKind visibility);

        void setMemberShortName(std::string memberShortName);
        std::optional<std::string> memberShortName();

        void setMemberName(std::string memberName);
        std::optional<std::string> memberName();

    protected:
        void setElementId(boost::uuids::uuid elementId);
        void setElementId(std::string elementId);
        std::string elementId();
        boost::uuids::uuid elementUId();

    private:
        VisibilityKind Visibility;
        /**
         * Within the Standard the Element Id should be saved as a string. For better comparison, we will save it as the original id Type.
         */
        boost::uuids::uuid ElementId;

        std::string MemberShortName;
        std::string MemberName;
    public:
        std::shared_ptr<Element> memberElement() const;
        void setMemberElement(std::shared_ptr<Element> value);
        std::shared_ptr<Namespace> membershipOwningNamespace() const;
        void setMembershipOwningNamespace(std::shared_ptr<Namespace> value);
        std::string memberElementId() const;

    // BEGIN GENERATED JSON (kerml/tools/generate_json.py): do not edit, run the script instead.
    public:
        /**
         * Creates a Membership either from its JSON representation (if the string starts with '{') or with the given declared name.
         * Reading JSON only stores the ids of the referenced elements, see Element::resolveJsonReferences(). The type of the object stays "Membership".
         * @param nameOrJson The JSON representation of the Membership, or its declared name.
         */
        explicit Membership(const std::string& nameOrJson);

        /**
         * Serializes the Membership to JSON: all properties of the metaclass (stored and derived ones). References to other elements are
         * only written as identities ({"@id": "<uuid>"}), never recursively.
         * @return The JSON representation of the Membership.
         */
        std::string serializeToJson() override;

        /**
         * Resolves the references that were read from JSON to the elements (see Element::resolveJsonReferences()), for the properties
         * of Membership and of its base classes.
         * @param lookup Returns the element of an element id, or an empty pointer if it is not known.
         */
        void resolveJsonReferences(const std::function<std::shared_ptr<Element>(const boost::uuids::uuid&)>& lookup) override;

    protected:
        /**
         * Populates the Membership from its JSON representation; the stored properties of Membership and of its base classes are read,
         * computed derived properties are ignored, the derived references that the model keeps as collections are read like the stored ones,
         * and references are only stored as ids.
         * @param jsonString The JSON representation of the Membership.
         */
        void deserializeAndPopulate(const std::string& jsonString) override;
    // END GENERATED JSON
    };
} // KerML::Entities
