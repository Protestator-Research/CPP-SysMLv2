//
// Created by Moritz Herzog on 25.03.25.
//

#include "NamespaceImport.h"
#include "Namespace.h"

namespace KerML::Entities {
    NamespaceImport::NamespaceImport(boost::uuids::uuid elementID, std::shared_ptr<Element> owner) :
    Import(elementID, owner) {
        ImportedNamespace = nullptr;
    }

    NamespaceImport::NamespaceImport(std::string elementID, std::shared_ptr<Element> owner) :
    Import(elementID, owner) {
        ImportedNamespace = nullptr;
    }

    std::vector<std::shared_ptr<Membership>> NamespaceImport::importedMemberships(std::shared_ptr<Namespace> excluded) {
        if( ImportedNamespace == excluded )
            return {nullptr};

        //TODO: Implement
        return std::vector<std::shared_ptr<Membership>>();
    }

    NamespaceImport::NamespaceImport(VisibilityKind visibility, bool isRecursive, bool isImportAll, std::shared_ptr<Namespace> importOwningNamespace, std::shared_ptr<Namespace> importedNamespace, boost::uuids::uuid elementID, std::shared_ptr<Element> owner) :
     Import(visibility, isRecursive, isImportAll, importOwningNamespace, elementID, owner) {
        ImportedNamespace = importedNamespace;
    }

    std::shared_ptr<Namespace> NamespaceImport::importedNamespace() {
        return ImportedNamespace;
    }

    void NamespaceImport::setImportedNamespace(std::shared_ptr<Namespace> importedNamespace) {
        ImportedNamespace = importedNamespace;
    }
}
