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
//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include "../../kerml_global.h"
#include "Membership.h"
//---------------------------------------------------------
// Forwarding
//---------------------------------------------------------

namespace KerML::Entities{
    class KERML_EXPORT OwningMembership : public Membership {
    public:
        OwningMembership();
        ~OwningMembership() override = default;

        std::string path() override;


    public:
        std::string ownedMemberElementId();
        boost::uuids::uuid ownedMemberElementIdAsUuid();
        void setOwnedMemberElementId(std::string ownedMemeberElementId);
        void setOwnedMemberElementId(boost::uuids::uuid ownedMemeberElementId);

        std::string ownedMemberShortName();
        void setOwnedMemberShortName(std::string ownedMemberShortName);

        std::string ownedMemberName();
        void setOwnedMemberName(std::string ownedMemberName);

    private:
        boost::uuids::uuid OwnedMemberElementId{};

        std::string OwnedMemberShortName;
        std::string OwnedMemberName;
    public:
        std::shared_ptr<Element> ownedMemberElement() const;
        void setOwnedMemberElement(std::shared_ptr<Element> value);

    // BEGIN GENERATED JSON (kerml/tools/generate_json.py): do not edit, run the script instead.
    public:
        /**
         * Creates a OwningMembership either from its JSON representation (if the string starts with '{') or with the given declared name.
         * Reading JSON only stores the ids of the referenced elements, see Element::resolveJsonReferences(). The type of the object stays "OwningMembership".
         * @param nameOrJson The JSON representation of the OwningMembership, or its declared name.
         */
        explicit OwningMembership(const std::string& nameOrJson);

        /**
         * Serializes the OwningMembership to JSON: all properties of the metaclass (stored and derived ones). References to other elements are
         * only written as identities ({"@id": "<uuid>"}), never recursively.
         * @return The JSON representation of the OwningMembership.
         */
        std::string serializeToJson() override;

        /**
         * Resolves the references that were read from JSON to the elements (see Element::resolveJsonReferences()), for the properties
         * of OwningMembership and of its base classes.
         * @param lookup Returns the element of an element id, or an empty pointer if it is not known.
         */
        void resolveJsonReferences(const std::function<std::shared_ptr<Element>(const boost::uuids::uuid&)>& lookup) override;

    protected:
        /**
         * Populates the OwningMembership from its JSON representation; the stored properties of OwningMembership and of its base classes are read,
         * computed derived properties are ignored, the derived references that the model keeps as collections are read like the stored ones,
         * and references are only stored as ids.
         * @param jsonString The JSON representation of the OwningMembership.
         */
        void deserializeAndPopulate(const std::string& jsonString) override;
    // END GENERATED JSON
    };
}
