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
#include <kerml/root/elements/Element.h>
#include <optional>
//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include <kerml/root/namespaces/VisibilityKind.h>
#include <kerml/kerml_global.h>
//---------------------------------------------------------
// Forwarding
//---------------------------------------------------------
namespace KerML::Entities
{
    class Membership;
    class Import;
}

namespace KerML::Entities {
    /**
     * @class Namespace
     * @author Moritz Herzog
     * @version 1.0 Beta 4
     * Defines the Namespace Class accoding to the KerML Abstract Syntax.
     */
    class KERML_EXPORT Namespace : public virtual Element {
        friend struct ::KerML::Entities::ElementDisposer;
    public:
        /**
         * Constructor of the Element. This constructor does allow for an empty elementID.
         * @param elementID The Element ID of the Element. If no UUID is provided, a random UUID is provided by the Software.
         * @param owner The Element that owns this element. If no Element is provided the owning element is automatically set to null.
         */
        explicit Namespace(boost::uuids::uuid elementID = boost::uuids::random_generator()(), std::shared_ptr<Element> owner = nullptr);

        /**
         * Specialized Constructor for the namespace class, allowing to set the name of the namespace directly in the constructor.
         * @param namespaceName The name of the namespace. It saves the namespace name inside of the QualifiedName.
         * @param elementID The Element ID of this Element. If no Id is provided, the ID id is generated.
         * @param owner The owning Element if this specific namespace. If no Element is provided, this is set tu null.
         * If the string is a JSON object (it starts with '{') it is the JSON representation of the element, see serializeToJson(); otherwise it is the declared name.
         */
        explicit Namespace(std::string namespaceName, boost::uuids::uuid elementID = boost::uuids::random_generator()(), std::shared_ptr<Element> owner = nullptr);

        /**
         * Specialized Constructor, for creating Namespace for parser. This allowes to directly initializes Namespace with name, importation boolean and everything else that is needed.
         * @param namespaceName The name of the namespace. It saves the namespace name inside of the QualifiedName.
         * @param isImported Inidication if Namespace is imported, so the elements are loaded from the correct file.
         * @param elementID The Element ID of this Element. If no Id is provided, the ID id is generated.
         * @param owner The owning Element if this specific namespace. If no Element is provided, this is set tu null.
         */
        explicit Namespace(std::string namespaceName, bool isImported, boost::uuids::uuid elementID = boost::uuids::random_generator()(), std::shared_ptr<Element> owner = nullptr);

        ~Namespace() override = default;

        /**
         * This variable is only required by the parser to check it for the parser, since this has no Instance information.
         * @return True if the namespace is imported, false otherwise.
         */
        bool isImported();

        /**
         * This is required by the Parser, set the IsImported property.
         */
        void setIsImported(bool isImported);

        /**
         * 
         * @param element
         * @return
         */
        std::vector<std::string> namesOf(std::shared_ptr<Element> element);

        /**
         * 
         * @param mem
         * @return
         */
        VisibilityKind visibilityOff(std::shared_ptr<Membership> mem);

        /**
         *
         * @param excluded
         * @param isRecursive
         * @param includeAll
         * @return
         */
        virtual std::vector<std::shared_ptr<Membership>> visibleMemberships(std::vector<std::shared_ptr<Namespace>> excluded, bool isRecursive, bool includeAll);

        /**
         *
         * @param excluded
         * @return
         */
        std::vector<std::shared_ptr<Membership>> importedMemberships(std::vector<std::shared_ptr<Namespace>> excluded);

        /**
         *
         * @param visiblity
         * @param namespaces
         * @return
         */
        std::vector<std::shared_ptr<Membership>> membershipsOfVisibility(std::optional<VisibilityKind> visiblity, std::vector<std::shared_ptr<Namespace>> namespaces);

        /**
         *
         * @param qualifiedName
         * @return
         */
        std::optional<std::shared_ptr<Membership>> resolve(std::string qualifiedName);


        /**
         *
         * @param qualifiedName
         * @return
         */
        std::optional<std::shared_ptr<Membership>> resolveGlobal(std::string qualifiedName);

        /**
         *
         * @param name
         * @return
         */
        std::optional<std::shared_ptr<Membership>> resolveLocal(std::string name);

        /**
         *
         * @param name
         * @return
         */
        std::optional<std::shared_ptr<Membership>> resolveVisible(std::string name);

        /**
         *
         * @param qualifiedName
         * @return
         */
        std::string qualificationOf(std::string qualifiedName);

        /**
         *
         * @param qualifiedName
         * @return
         */
        std::string unqualifiedName(std::string qualifiedName);

    public:
        /**
         *
         * @return
         */
        std::vector<std::shared_ptr<Membership>> importedMemberships() const;

        /**
         *
         * @param importedMemberships
         */
        void setImportedMemberships(std::vector<std::shared_ptr<Membership>> importedMemberships);

        /**
         *
         * @param importedMembership
         */
        void appendImportedMemberships(std::shared_ptr<Membership> importedMembership);

        /**
         *
         * @param importedMemberships
         */
        void appendImportedMemberships(std::vector<std::shared_ptr<Membership>> importedMemberships);

        /**
         *
         * @return
         */
        std::vector<std::shared_ptr<Element>> member() const;

        /**
         *
         * @param member
         */
        void setMember(std::vector<std::shared_ptr<Element>> member);

        /**
         *
         * @param member
         */
        void appendMember(std::shared_ptr<Element> member);

        /**
         *
         * @param member
         */
        void appendMember(std::vector<std::shared_ptr<Element>> member);

        /**
         *
         * @return
         */
        std::vector<std::shared_ptr<Membership>> memberships() const;

        /**
         *
         * @param memberships
         */
        void setMemberships(std::vector<std::shared_ptr<Membership>> memberships);

        /**
         *
         * @param membership
         */
        void appendMembership(std::shared_ptr<Membership> membership);

        /**
         *
         * @param memberhsips
         */
        void appendMembership(std::vector<std::shared_ptr<Membership>> memberhsips);

        /**
         *
         * @return
         */
        std::vector<std::shared_ptr<Import>> ownedImport() const;

        /**
         *
         * @param ownedImports
         */
        void setOwnedImport(std::vector<std::shared_ptr<Import>> ownedImports);

        /**
         *
         * @param ownedImport
         */
        void appendOwnedImport(std::shared_ptr<Import> ownedImport);

        /**
         *
         * @param ownedImport
         */
        void appendOwnedImport(std::vector<std::shared_ptr<Import>> ownedImport);

        /**
         *
         * @return
         */
        std::vector<std::shared_ptr<Element>> ownedMember() const;

        /**
         *
         * @param ownedMemeber
         */
        void setOwnedMember(std::vector<std::shared_ptr<Element>> ownedMemeber);

        /**
         *
         * @param ownedMember
         */
        void appendOwnedMember(std::shared_ptr<Element> ownedMember);

        /**
         *
         * @param ownedMember
         */
        void appendOwnedMember(std::vector<std::shared_ptr<Element>> ownedMember);

        /**
         *
         * @return
         */
        std::vector<std::shared_ptr<Membership>> ownedMembership() const;

        /**
         *
         * @param ownedMembership
         */
        void setOwnedMembership(std::vector<std::shared_ptr<Membership>> ownedMembership);

        /**
         *
         * @param ownedMembership
         */
        void appendOwnedMembership(std::shared_ptr<Membership> ownedMembership);

        /**
         *
         * @param ownedMembership
         */
        void appendOwnedMembership(std::vector<std::shared_ptr<Membership>> ownedMembership);
    private:
        /**
         * Is Imported is only a variable that might be subject to change since this is a variable to indicate an instance,
         * that this namespace is imported.
         */
        bool IsImported;

        std::vector<std::shared_ptr<Membership>> ImportedMemberships;
        std::vector<std::shared_ptr<Element>> Member;
        std::vector<std::shared_ptr<Membership>> Memberships;
        std::vector<std::shared_ptr<Import>> OwnedImport;
        std::vector<std::shared_ptr<Element>> OwnedMember;
        std::vector<std::shared_ptr<Membership>> OwnedMembership;


    public:
        std::vector<std::shared_ptr<Membership>> membership() const;
        std::vector<std::shared_ptr<Membership>> importedMembership() const;

    // BEGIN GENERATED JSON (kerml/tools/generate_json.py): do not edit, run the script instead.
    public:
        /**
         * Serializes the Namespace to JSON: all properties of the metaclass (stored and derived ones). References to other elements are
         * only written as identities ({"@id": "<uuid>"}), never recursively.
         * @return The JSON representation of the Namespace.
         */
        std::string serializeToJson() override;

        /**
         * Resolves the references that were read from JSON to the elements (see Element::resolveJsonReferences()), for the properties
         * of Namespace and of its base classes.
         * @param lookup Returns the element of an element id, or an empty pointer if it is not known.
         */
        void resolveJsonReferences(const std::function<std::shared_ptr<Element>(const boost::uuids::uuid&)>& lookup) override;

    protected:
        /**
         * Populates the Namespace from its JSON representation; the stored properties of Namespace and of its base classes are read,
         * computed derived properties are ignored, the derived references that the model keeps as collections are read like the stored ones,
         * and references are only stored as ids.
         * @param jsonString The JSON representation of the Namespace.
         */
        void deserializeAndPopulate(const std::string& jsonString) override;
    // END GENERATED JSON
    };
} // KerML::Entities
