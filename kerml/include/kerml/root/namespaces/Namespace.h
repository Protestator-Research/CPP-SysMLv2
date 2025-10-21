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
     * @version 1.0 Beta 3
     * Defines the Namespace Class accoding to the KerML Abstract Syntax.
     */
    class KERML_EXPORT Namespace : public Element {
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
         */
        explicit Namespace(std::string namespaceName, boost::uuids::uuid elementID = boost::uuids::random_generator()(), std::shared_ptr<Element> owner = nullptr);

        /**
         *
         * @param namespaceName
         * @param isImported
         * @param elementID
         * @param owner
         */
        explicit Namespace(std::string namespaceName, bool isImported, boost::uuids::uuid elementID = boost::uuids::random_generator()(), std::shared_ptr<Element> owner = nullptr);

        ~Namespace() override = default;

        /**
         * This variable is only required by the parser to check it for the parser, since this has no Instance information.
         * @return True if the namespace is imported, false otherwise.
         */
        bool isImported();

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

    protected:
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


    };
} // KerML::Entities
