//
// Created by Moritz Herzog on 25.03.25.
//
//---------------------------------------------------------
// Constants, Definitions, Pragmas
//---------------------------------------------------------
#ifndef SYSMLV2_MEMBERSHIP_H
#define SYSMLV2_MEMBERSHIP_H
//---------------------------------------------------------
// External Classes
//---------------------------------------------------------
#include <boost/uuid/uuid.hpp>
#include <string>
#include <optional>
//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include "../elements/Relationship.h"
#include "VisibilityKind.h"
#include "../../kerml_global.h"
//---------------------------------------------------------
// Forwarding
//---------------------------------------------------------


namespace KerML::Entities {
    class KERML_EXPORT Membership : public Relationship {
    public:
        Membership();
        ~Membership() override = default;

        VisibilityKind visibility();
        void setVisibility(VisibilityKind visibility);

        void setMemberShortName(std::string memberShortName);
        std::optional<std::string> memberShortName();

        void setMemberName(std::string memberName);
        std::optional<std::string> memberName();

    protected:
        void setElementId(boost::uuids::uuid elementId);
        void setElementId(std::string elementId);
        std::string elementId();
        boost::uuids::uuid elementUId();

    private:
        VisibilityKind Visibility;
        /**
         * Within the Standard the Element Id should be saved as a string. For better comparison, we will save it as the original id Type.
         */
        boost::uuids::uuid ElementId;

        std::string MemberShortName;
        std::string MemberName;
    };
} // KerML::Entities

#endif //SYSMLV2_MEMBERSHIP_H
