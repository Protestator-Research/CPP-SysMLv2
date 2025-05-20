//
// Created by Moritz Herzog on 25.03.25.
//

#include "NamespaceImport.h"

namespace KerML::Entities {

    std::vector<std::shared_ptr<Membership>> NamespaceImport::importedMemberships(std::shared_ptr<Namespace> excluded) {
        //TODO: Implement
        return std::vector<std::shared_ptr<Membership>>();
    }

    NamespaceImport::NamespaceImport(boost::uuids::uuid elementID, std::shared_ptr<Element> owner) : Import(elementID,
                                                                                                             owner) {

    }

    NamespaceImport::NamespaceImport(std::string elementID, std::shared_ptr<Element> owner) : Import(elementID,
                                                                                                      owner) {
    }

    NamespaceImport::NamespaceImport(VisibilityKind visibility, bool isRecursive, bool isImportAll,
                                     std::shared_ptr<Namespace> importOwningNamespace, std::shared_ptr<Namespace> importedNamespace, boost::uuids::uuid elementID,
                                     std::shared_ptr<Element> owner) : Import(visibility, isRecursive, isImportAll,
                                                                              importOwningNamespace, elementID, owner) {
        Import = importedNamespace
    }

    std::shared_ptr<Namespace> NamespaceImport::import() {
        return std::shared_ptr<Namespace>();
    }

    void NamespaceImport::setImport(std::shared_ptr<Namespace> import) {

    }
}
