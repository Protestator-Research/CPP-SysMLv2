//
// Created by Moritz Herzog on 25.03.25.
//

#ifndef SYSMLV2_NAMESPACEIMPORT_H
#define SYSMLV2_NAMESPACEIMPORT_H

#include "Import.h"
#include "../elements/Relationship.h"
#include "VisibilityKind.h"

#include <boost/uuid/uuid.hpp>

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
        explicit NamespaceImport(boost::uuids::uuid elementID = boost::uuids::random_generator()(), std::shared_ptr<Element> owner = nullptr);
        explicit NamespaceImport(std::string elementID, std::shared_ptr<Element> owner = nullptr);
        NamespaceImport(VisibilityKind visibility, bool isRecursive, bool isImportAll, std::shared_ptr<Namespace> importOwningNamespace, std::shared_ptr<Namespace> importedNamespace, boost::uuids::uuid elementID = boost::uuids::random_generator()(), std::shared_ptr<Element> owner = nullptr);

        ~NamespaceImport() override = default;

        std::shared_ptr<Namespace> importedNamespace();
        void setImportedNamespace(std::shared_ptr<Namespace> importedNamespace);

        std::vector<std::shared_ptr<Membership>> importedMemberships(std::shared_ptr<Namespace> excluded) override;
    private:

        std::shared_ptr<Namespace> ImportedNamespace;
    };
}


#endif //SYSMLV2_NAMESPACEIMPORT_H
