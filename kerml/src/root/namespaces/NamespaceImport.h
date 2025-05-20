//
// Created by Moritz Herzog on 25.03.25.
//

#ifndef SYSMLV2_NAMESPACEIMPORT_H
#define SYSMLV2_NAMESPACEIMPORT_H

#include "Import.h"
#include "VisibilityKind.h"

namespace KerML::Entities {
    class Namespace;
    /**
     * @class NamespaceImport
     * @author Moritz Herzog
     * @version 1.0 Beta 3
     *
     */
    class NamespaceImport : public Import {
    public:
        NamespaceImport(boost::uuids::uuid elementID = boost::uuids::random_generator()(), std::shared_ptr<Element> owner = nullptr);
        NamespaceImport(std::string elementID, std::shared_ptr<Element> owner = nullptr);
        NamespaceImport(VisibilityKind visibility, bool isRecursive, bool isImportAll, std::shared_ptr<Namespace> importOwningNamespace, std::shared_ptr<Namespace> importedNamespace, boost::uuids::uuid elementID = boost::uuids::random_generator()(), std::shared_ptr<Element> owner = nullptr);

        ~NamespaceImport() override = default;

        std::shared_ptr<Namespace> import();
        void setImport(std::shared_ptr<Namespace> import);

        std::vector<std::shared_ptr<Membership>> importedMemberships(std::shared_ptr<Namespace> excluded) override;
    private:
        std::shared_ptr<Namespace> Import;
    };
}


#endif //SYSMLV2_NAMESPACEIMPORT_H
