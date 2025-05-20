//
// Created by Moritz Herzog on 25.03.25.
//

#include "Import.h"

namespace KerML {
    namespace Entities {
        Import::Import(boost::uuids::uuid elementID, std::shared_ptr<Element> owner) : Relationship(elementID, owner) { }

        Import::Import(std::string elementID, std::shared_ptr<Element> owner) : Relationship(elementID, owner) { }

        Import::Import(VisibilityKind visibility, bool isRecursive, bool isImportAll,
                       std::shared_ptr<Namespace> importOwningNamespace, boost::uuids::uuid elementID,
                       std::shared_ptr<Element> owner) : Relationship(elementID,owner){
            Visibility = visibility;
            IsImportAll = isImportAll;
            IsRecursive = isRecursive;
            ImportOwningNamespace = importOwningNamespace;
        }

        void Import::setVisibility(VisibilityKind visibility) {
            Visibility = visibility;
        }

        VisibilityKind Import::visibility() const {
            return Visibility;
        }

        bool Import::isImportAll() const {
            return IsImportAll;
        }

        void Import::setIsImportAll(bool isImportAll) {
            IsImportAll = isImportAll;
        }

        bool Import::isRecursive() const {
            return IsRecursive;
        }

        void Import::setIsRecursive(bool isRecursive) {
            IsRecursive = isRecursive;
        }

        std::shared_ptr<Namespace> Import::importOwningNamespace() const {
            return ImportOwningNamespace;
        }

        void Import::setImportOwningNamespace(std::shared_ptr<Namespace> importOwningNamespace) {
            ImportOwningNamespace = importOwningNamespace;
        }
    } // Entities
} // KerML