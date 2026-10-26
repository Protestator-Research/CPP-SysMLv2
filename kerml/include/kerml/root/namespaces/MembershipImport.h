//
// Created by Moritz Herzog on 25.03.25.
//
//---------------------------------------------------------
// Constants, Definitions, Pragmas
//---------------------------------------------------------
#pragma once
//---------------------------------------------------------
// External Classes
//---------------------------------------------------------

//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include <kerml/root/namespaces/Import.h>
#include <kerml/kerml_global.h>
//---------------------------------------------------------
// Forwarding
//---------------------------------------------------------

namespace KerML::Entities {
    class Membership;

    class KERML_EXPORT MembershipImport : public virtual Import {
        friend struct ::KerML::Entities::ElementDisposer;
    public:
        MembershipImport();
        ~MembershipImport() override = default;

        std::vector<std::shared_ptr <Membership>> importedMemberships(std::vector<std::shared_ptr<Namespace>> excluded) override;

        std::shared_ptr<Membership> importedMembership() const;
        void setImportedMembership(std::shared_ptr<Membership> importedMembership);
    private:
        std::shared_ptr<Membership> ImportedMembership;

    // BEGIN GENERATED JSON (kerml/tools/generate_json.py): do not edit, run the script instead.
    public:
        /**
         * Creates a MembershipImport either from its JSON representation (if the string starts with '{') or with the given declared name.
         * Reading JSON only stores the ids of the referenced elements, see Element::resolveJsonReferences(). The type of the object stays "MembershipImport".
         * @param nameOrJson The JSON representation of the MembershipImport, or its declared name.
         */
        explicit MembershipImport(const std::string& nameOrJson);

        /**
         * Serializes the MembershipImport to JSON: all properties of the metaclass (stored and derived ones). References to other elements are
         * only written as identities ({"@id": "<uuid>"}), never recursively.
         * @return The JSON representation of the MembershipImport.
         */
        std::string serializeToJson() override;

        /**
         * Resolves the references that were read from JSON to the elements (see Element::resolveJsonReferences()), for the properties
         * of MembershipImport and of its base classes.
         * @param lookup Returns the element of an element id, or an empty pointer if it is not known.
         */
        void resolveJsonReferences(const std::function<std::shared_ptr<Element>(const boost::uuids::uuid&)>& lookup) override;

    protected:
        /**
         * Populates the MembershipImport from its JSON representation; the stored properties of MembershipImport and of its base classes are read,
         * computed derived properties are ignored, the derived references that the model keeps as collections are read like the stored ones,
         * and references are only stored as ids.
         * @param jsonString The JSON representation of the MembershipImport.
         */
        void deserializeAndPopulate(const std::string& jsonString) override;
    // END GENERATED JSON
    };
} // KerML::Entities
