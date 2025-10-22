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

//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include <kerml/root/namespaces/Import.h>
#include <kerml/kerml_global.h>
//---------------------------------------------------------
// Forwarding
//---------------------------------------------------------

namespace KerML::Entities {
    class Membership;

    class KERML_EXPORT MembershipImport : public Import {
    public:
        MembershipImport();
        ~MembershipImport() override = default;

        std::vector<std::shared_ptr <Membership>> importedMemberships(std::vector<std::shared_ptr<Namespace>> excluded) override;

        std::shared_ptr<Membership> importedMembership() const;
        void setImportedMembership(std::shared_ptr<Membership> importedMembership);
    private:
        std::shared_ptr<Membership> ImportedMembership;
    };
} // KerML::Entities
