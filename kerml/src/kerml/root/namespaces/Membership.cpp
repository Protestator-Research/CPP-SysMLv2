//
// Created by Moritz Herzog on 25.03.25.
//

#include <kerml/root/namespaces/Membership.h>
#include <boost/uuid/string_generator.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <kerml/KerML.h>
#include <nlohmann/json.hpp>
#include "../../model/JsonSupport.h"

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

// BEGIN GENERATED JSON (kerml/tools/generate_json.py): do not edit, run the script instead.
namespace KerML::Entities {
    Membership::Membership(const std::string& nameOrJson) :
        Membership() {
        _dType = "Membership";
        if (Json::looksLikeJson(nameOrJson)) {
            deserializeAndPopulate(nameOrJson);
            captureJsonSource(nameOrJson);
        } else {
            setDeclaredName(nameOrJson);
        }
    }

    std::string Membership::serializeToJson() {
        nlohmann::json json = nlohmann::json::parse(Relationship::serializeToJson());
        json["memberElementId"] = Json::idText(Membership::memberElementId(), unresolvedJsonReferences("memberElement"));
        json["membershipOwningNamespace"] = Json::reference(unresolvedJsonReferences("membershipOwningNamespace"), Membership::membershipOwningNamespace());
        json["memberShortName"] = Json::value(Membership::memberShortName());
        json["memberElement"] = Json::reference(unresolvedJsonReferences("memberElement"), Membership::memberElement());
        json["memberName"] = Json::value(Membership::memberName());
        json["visibility"] = Json::value(Membership::visibility());
        return applyJsonSource(json.dump(JSON_INTENT));
    }

    void Membership::deserializeAndPopulate(const std::string& jsonString) {
        Relationship::deserializeAndPopulate(jsonString);
        const nlohmann::json json = nlohmann::json::parse(jsonString);
        std::vector<boost::uuids::uuid> ids;
        if (Json::readReferences(json, "membershipOwningNamespace", ids))
            setUnresolvedJsonReferences("membershipOwningNamespace", ids);
        {
            std::string value{};
            if (Json::readString(json, "memberShortName", value)) {
                try {
                    Membership::setMemberShortName(value);
                } catch (const std::invalid_argument&) {
                    // A value the metaclass refuses (for example another operator than the fixed one) is ignored.
                }
            }
        }
        if (Json::readReferences(json, "memberElement", ids))
            setUnresolvedJsonReferences("memberElement", ids);
        {
            std::string value{};
            if (Json::readString(json, "memberName", value)) {
                try {
                    Membership::setMemberName(value);
                } catch (const std::invalid_argument&) {
                    // A value the metaclass refuses (for example another operator than the fixed one) is ignored.
                }
            }
        }
        {
            VisibilityKind value{};
            if (Json::readEnum(json, "visibility", value)) {
                try {
                    Membership::setVisibility(value);
                } catch (const std::invalid_argument&) {
                    // A value the metaclass refuses (for example another operator than the fixed one) is ignored.
                }
            }
        }
    }

    void Membership::resolveJsonReferences(const std::function<std::shared_ptr<Element>(const boost::uuids::uuid&)>& lookup) {
        Relationship::resolveJsonReferences(lookup);
        if (const auto ids = unresolvedJsonReferences("membershipOwningNamespace")) {
            try {
                if (auto target = std::dynamic_pointer_cast<KerML::Entities::Namespace>(lookup(ids->front()))) {
                    Membership::setMembershipOwningNamespace(std::move(target));
                    clearUnresolvedJsonReferences("membershipOwningNamespace");
                }
            } catch (const std::exception&) {
                // The reference stays unresolved if the model refuses it.
                setUnresolvedJsonReferences("membershipOwningNamespace", *ids);
            }
        }
        if (const auto ids = unresolvedJsonReferences("memberElement")) {
            try {
                if (auto target = std::dynamic_pointer_cast<KerML::Entities::Element>(lookup(ids->front()))) {
                    Membership::setMemberElement(std::move(target));
                    clearUnresolvedJsonReferences("memberElement");
                }
            } catch (const std::exception&) {
                // The reference stays unresolved if the model refuses it.
                setUnresolvedJsonReferences("memberElement", *ids);
            }
        }
    }
}
// END GENERATED JSON
