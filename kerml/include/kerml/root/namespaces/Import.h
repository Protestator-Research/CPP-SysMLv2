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
#include <memory>
#include <boost/uuid/uuid.hpp>
//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include <kerml/root/elements/Relationship.h>
#include <kerml/root/namespaces/VisibilityKind.h>

#include <kerml/kerml_global.h>
//---------------------------------------------------------
// Forwarding
//---------------------------------------------------------
namespace KerML::Entities
{
    class Namespace;
    class Membership;
}


namespace KerML::Entities {
    /**
     * @class Import
     * @author Moritz Herzog
     * @version 1.0 Beta 3
     *
     */
    class KERML_EXPORT Import : public Relationship{
        friend struct ::KerML::Entities::ElementDisposer;
    public:
        /**
         *
         * @param elementID
         * @param owner
         */
        explicit Import(boost::uuids::uuid elementID = boost::uuids::random_generator()(), std::shared_ptr<Element> owner = nullptr);
        /**
         *
         * @param elementID
         * @param owner
         * If the string is a JSON object (it starts with '{') it is the JSON representation of the element, see serializeToJson(); otherwise it is the declared name.
         */
        explicit Import(std::string nameOrJson, std::shared_ptr<Element> owner = nullptr);
        /**
         *
         * @param visibility
         * @param isRecursive
         * @param isImportAll
         * @param importOwningNamespace
         * @param elementID
         * @param owner
         */
        Import(VisibilityKind visibility, bool isRecursive, bool isImportAll, std::shared_ptr<Namespace> importOwningNamespace, boost::uuids::uuid elementID = boost::uuids::random_generator()(), std::shared_ptr<Element> owner = nullptr);

        /**
         * Destructor
         */
        virtual ~Import() = default;

        /**
         *
         * @return
         */
        VisibilityKind visibility() const;
        void setVisibility(VisibilityKind visibility);

        bool isRecursive() const;
        void setIsRecursive(bool isRecursive);

        bool isImportAll() const;
        void setIsImportAll(bool isImportAll);

        virtual std::vector<std::shared_ptr<Membership>> importedMemberships(std::vector<std::shared_ptr<Namespace>> excluded) = 0;

    
        std::shared_ptr<Namespace> importOwningNamespace() const;
        void setImportOwningNamespace(const std::shared_ptr<Namespace>& importOwningNamespace);

    private:
        VisibilityKind Visibility;
        bool IsRecursive;
        bool IsImportAll;
        std::shared_ptr<Namespace> ImportOwningNamespace;
    public:
        std::shared_ptr<Element> importedElement() const;

    // BEGIN GENERATED JSON (kerml/tools/generate_json.py): do not edit, run the script instead.
    public:
        /**
         * Serializes the Import to JSON: all properties of the metaclass (stored and derived ones). References to other elements are
         * only written as identities ({"@id": "<uuid>"}), never recursively.
         * @return The JSON representation of the Import.
         */
        std::string serializeToJson() override;

        /**
         * Resolves the references that were read from JSON to the elements (see Element::resolveJsonReferences()), for the properties
         * of Import and of its base classes.
         * @param lookup Returns the element of an element id, or an empty pointer if it is not known.
         */
        void resolveJsonReferences(const std::function<std::shared_ptr<Element>(const boost::uuids::uuid&)>& lookup) override;

    protected:
        /**
         * Populates the Import from its JSON representation; the stored properties of Import and of its base classes are read,
         * computed derived properties are ignored, the derived references that the model keeps as collections are read like the stored ones,
         * and references are only stored as ids.
         * @param jsonString The JSON representation of the Import.
         */
        void deserializeAndPopulate(const std::string& jsonString) override;
    // END GENERATED JSON
    };
} // KerML::Entities
