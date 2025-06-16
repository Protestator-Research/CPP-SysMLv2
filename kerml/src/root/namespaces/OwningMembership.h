//
// Created by Moritz Herzog on 25.03.25.
//
//---------------------------------------------------------
// Constants, Definitions, Pragmas
//---------------------------------------------------------
#ifndef SYSMLV2_OWNINGMEMBERSHIP_H
#define SYSMLV2_OWNINGMEMBERSHIP_H
//---------------------------------------------------------
// External Classes
//---------------------------------------------------------
#include <boost/uuid/uuid.hpp>
#include <string>
//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include "../../kerml_global.h"
#include "Membership.h"
//---------------------------------------------------------
// Forwarding
//---------------------------------------------------------

namespace KerML::Entities{
    class KERML_EXPORT OwningMembership : public Membership {
    public:
        OwningMembership();
        ~OwningMembership() override = default;

        std::string path() override;


    protected:
        std::string ownedMemberElementId();
        boost::uuids::uuid ownedMemberElementIdAsUuid();
        void setOwnedMemberElementId(std::string ownedMemeberElementId);
        void setOwnedMemberElementId(boost::uuids::uuid ownedMemeberElementId);

        std::string ownedMemberShortName();
        void setOwnedMemberShortName(std::string ownedMemberShortName);

        std::string ownedMemberName();
        void setOwnedMemberName(std::string ownedMemberName);

    private:
        boost::uuids::uuid OwnedMemberElementId;

        std::string OwnedMemberShortName;
        std::string OwnedMemberName;
    };
}

#endif //SYSMLV2_OWNINGMEMBERSHIP_H
