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
#include <boost/uuid/uuid.hpp>
#include <kerml/root/elements/Relationship.h>
//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include <kerml/root/namespaces/Import.h>
#include <kerml/root/namespaces/VisibilityKind.h>
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
     * @class NamespaceImport
     * @author Moritz Herzog
     * @version 1.0 Beta 4
     * 
     */
    class KERML_EXPORT NamespaceImport : public virtual Import {
        friend struct ::KerML::Entities::ElementDisposer;
    public:
        explicit NamespaceImport(boost::uuids::uuid elementID = boost::uuids::random_generator()(), std::shared_ptr<Element> owner = nullptr);
        explicit NamespaceImport(std::string nameOrJson, std::shared_ptr<Element> owner = nullptr);
        NamespaceImport(VisibilityKind visibility, bool isRecursive, bool isImportAll, std::shared_ptr<Namespace> importOwningNamespace, std::shared_ptr<Namespace> importedNamespace, boost::uuids::uuid elementID = boost::uuids::random_generator()(), std::shared_ptr<Element> owner = nullptr);

        ~NamespaceImport() override = default;

        std::shared_ptr<Namespace> importedNamespace();
        void setImportedNamespace(std::shared_ptr<Namespace> importedNamespace);
        
        std::vector<std::shared_ptr<Membership>> importedMemberships(std::vector<std::shared_ptr<Namespace>> excluded) override;
    private:
        std::shared_ptr<Namespace> ImportedNamespace;

    // BEGIN GENERATED JSON (kerml/tools/generate_json.py): do not edit, run the script instead.
    public:
        /**
         * Serializes the NamespaceImport to JSON: all properties of the metaclass (stored and derived ones). References to other elements are
         * only written as identities ({"@id": "<uuid>"}), never recursively.
         * @return The JSON representation of the NamespaceImport.
         */
        std::string serializeToJson() override;

        /**
         * Resolves the references that were read from JSON to the elements (see Element::resolveJsonReferences()), for the properties
         * of NamespaceImport and of its base classes.
         * @param lookup Returns the element of an element id, or an empty pointer if it is not known.
         */
        void resolveJsonReferences(const std::function<std::shared_ptr<Element>(const boost::uuids::uuid&)>& lookup) override;

    protected:
        /**
         * Populates the NamespaceImport from its JSON representation; the stored properties of NamespaceImport and of its base classes are read,
         * computed derived properties are ignored, the derived references that the model keeps as collections are read like the stored ones,
         * and references are only stored as ids.
         * @param jsonString The JSON representation of the NamespaceImport.
         */
        void deserializeAndPopulate(const std::string& jsonString) override;
    // END GENERATED JSON
    };
}

