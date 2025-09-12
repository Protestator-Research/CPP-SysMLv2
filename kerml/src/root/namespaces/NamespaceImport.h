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
//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include "Import.h"
#include "../elements/Relationship.h"
#include "VisibilityKind.h"
#include "../../kerml_global.h"
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
     * @version 1.0 Beta 3
     * 
     */
    class KERML_EXPORT NamespaceImport : public Import {
    public:
        explicit NamespaceImport(boost::uuids::uuid elementID = boost::uuids::random_generator()(), std::shared_ptr<Element> owner = nullptr);
        explicit NamespaceImport(std::string elementID, std::shared_ptr<Element> owner = nullptr);
        NamespaceImport(VisibilityKind visibility, bool isRecursive, bool isImportAll, std::shared_ptr<Namespace> importOwningNamespace, std::shared_ptr<Namespace> importedNamespace, boost::uuids::uuid elementID = boost::uuids::random_generator()(), std::shared_ptr<Element> owner = nullptr);

        ~NamespaceImport() override = default;

        std::shared_ptr<Namespace> importedNamespace();
        void setImportedNamespace(std::shared_ptr<Namespace> importedNamespace);

        std::vector<std::shared_ptr<Membership>> importedMemberships(std::vector<std::shared_ptr<Namespace>> excluded) override;
    private:

        std::shared_ptr<Namespace> ImportedNamespace;
    };
}

