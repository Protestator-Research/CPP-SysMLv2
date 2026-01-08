//
// Created by Moritz Herzog on 25.03.25.
//

#include <kerml/root/namespaces/Membership.h>
#include <boost/uuid/string_generator.hpp>
#include <boost/uuid/uuid_io.hpp>

namespace KerML::Entities {
    Membership::Membership() {
        Visibility = PUBLIC;
        _dType = "Membership";
    }

    VisibilityKind Membership::visibility() {
        return Visibility;
    }

    void Membership::setVisibility(VisibilityKind visibility) {
        Visibility = visibility;
    }

    void Membership::setMemberShortName(std::string memberShortName) {
        MemberShortName = memberShortName;
    }

    std::optional<std::string> Membership::memberShortName() {
        if(!MemberShortName.empty())
            return MemberShortName;
        else
            return {};
    }

    void Membership::setMemberName(std::string memberName) {
        MemberName = memberName;
    }

    std::optional<std::string> Membership::memberName() {
        if(!MemberName.empty())
            return MemberName;
        else
            return {};
    }

    void Membership::setElementId(boost::uuids::uuid elementId) {
        ElementId = elementId;
    }

    void Membership::setElementId(std::string elementId) {
        ElementId = boost::uuids::string_generator()(elementId);
    }

    std::string Membership::elementId() {
        return boost::uuids::to_string(ElementId);
    }

    boost::uuids::uuid Membership::elementUId() {
        return ElementId;
    }
} // KerML::Entities