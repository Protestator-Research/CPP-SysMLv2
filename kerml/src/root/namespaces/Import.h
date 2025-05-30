//
// Created by Moritz Herzog on 25.03.25.
//

#ifndef SYSMLV2_IMPORT_H
#define SYSMLV2_IMPORT_H

#include "../elements/Relationship.h"
#include "VisibilityKind.h"
#include <memory>
#include <boost/uuid/uuid.hpp>

namespace KerML::Entities {
    class Namespace;
    class Membership;
    /**
     * @class Import
     * @author Moritz Herzog
     * @version 1.0 Beta 3
     *
     */
    class Import : public Relationship{
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
         */
        explicit Import(std::string elementID, std::shared_ptr<Element> owner = nullptr);
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

    protected:
        std::shared_ptr<Namespace> importOwningNamespace() const;
        void setImportOwningNamespace(std::shared_ptr<Namespace> importOwningNamespace);

    private:
        VisibilityKind Visibility;
        bool IsRecursive;
        bool IsImportAll;
        std::shared_ptr<Namespace> ImportOwningNamespace;
    };
} // KerML::Entities

#endif //SYSMLV2_IMPORT_H
