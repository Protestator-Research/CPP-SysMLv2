//
// Created by Moritz Herzog on 25.03.25.
//

#include <memory>

#include <kerml/core/features/FeatureMembership.h>

#include <kerml/core/types/Type.h>
#include <kerml/core/features/Feature.h>
#include <kerml/KerML.h>
#include <nlohmann/json.hpp>
#include "../../model/JsonSupport.h"

namespace KerML::Entities {
    FeatureMembership::FeatureMembership() {
        _dType = "FeatureMembership";
    }

    FeatureMembership::FeatureMembership(std::shared_ptr<Feature> ownedMemberFeature,
                                         std::shared_ptr<Type> owningType,
                                         std::vector<std::shared_ptr<Type>> type) {
        _dType = "FeatureMembership";

        setOwnedMemberElement(ownedMemberFeature);
        setMembershipOwningNamespace(owningType);
        _Type = type;
    }

    void FeatureMembership::setOwnedMemberFeature(std::shared_ptr<Feature> ownedMemberFeature) {
        clearUnresolvedJsonReferences("ownedMemberFeature");
        setOwnedMemberElement(ownedMemberFeature);
    }

    std::shared_ptr<Feature> FeatureMembership::ownedMemberFeature() const {
        return std::dynamic_pointer_cast<Feature>(ownedMemberElement());
    }

    void FeatureMembership::setOwningType(std::shared_ptr<Type> owningType) {
        clearUnresolvedJsonReferences("owningType");
        setMembershipOwningNamespace(owningType);
    }

    std::shared_ptr<Type> FeatureMembership::owningType() const {
        return std::dynamic_pointer_cast<Type>(membershipOwningNamespace());
    }

    void FeatureMembership::setType(std::vector<std::shared_ptr<Type>> type) {
        _Type = type;
    }

    std::vector<std::shared_ptr<Type>> FeatureMembership::type() const {
        return _Type;
    }

    void FeatureMembership::appendType(std::vector<std::shared_ptr<Type>> type) {
        _Type.insert(_Type.end(), type.begin(), type.end());
    }

    void FeatureMembership::appendType(std::shared_ptr<Type> type) {
        _Type.push_back(type);
    }
}

// BEGIN GENERATED JSON (kerml/tools/generate_json.py): do not edit, run the script instead.
namespace KerML::Entities {
    FeatureMembership::FeatureMembership(const std::string& nameOrJson) :
        FeatureMembership() {
        _dType = "FeatureMembership";
        if (Json::looksLikeJson(nameOrJson)) {
            deserializeAndPopulate(nameOrJson);
            captureJsonSource(nameOrJson);
        } else {
            setDeclaredName(nameOrJson);
        }
    }

    std::string FeatureMembership::serializeToJson() {
        nlohmann::json json = nlohmann::json::parse(OwningMembership::serializeToJson());
        json["owningType"] = Json::reference(unresolvedJsonReferences("owningType"), FeatureMembership::owningType());
        json["ownedMemberFeature"] = Json::reference(unresolvedJsonReferences("ownedMemberFeature"), FeatureMembership::ownedMemberFeature());
        return applyJsonSource(json.dump(JSON_INTENT));
    }

    void FeatureMembership::deserializeAndPopulate(const std::string& jsonString) {
        OwningMembership::deserializeAndPopulate(jsonString);
        const nlohmann::json json = nlohmann::json::parse(jsonString);
        std::vector<boost::uuids::uuid> ids;
        if (Json::readReferences(json, "owningType", ids))
            setUnresolvedJsonReferences("owningType", ids);
        if (Json::readReferences(json, "ownedMemberFeature", ids))
            setUnresolvedJsonReferences("ownedMemberFeature", ids);
    }

    void FeatureMembership::resolveJsonReferences(const std::function<std::shared_ptr<Element>(const boost::uuids::uuid&)>& lookup) {
        OwningMembership::resolveJsonReferences(lookup);
        if (const auto ids = unresolvedJsonReferences("owningType")) {
            try {
                if (auto target = std::dynamic_pointer_cast<KerML::Entities::Type>(lookup(ids->front()))) {
                    FeatureMembership::setOwningType(std::move(target));
                    clearUnresolvedJsonReferences("owningType");
                }
            } catch (const std::exception&) {
                // The reference stays unresolved if the model refuses it.
                setUnresolvedJsonReferences("owningType", *ids);
            }
        }
        if (const auto ids = unresolvedJsonReferences("ownedMemberFeature")) {
            try {
                if (auto target = std::dynamic_pointer_cast<KerML::Entities::Feature>(lookup(ids->front()))) {
                    FeatureMembership::setOwnedMemberFeature(std::move(target));
                    clearUnresolvedJsonReferences("ownedMemberFeature");
                }
            } catch (const std::exception&) {
                // The reference stays unresolved if the model refuses it.
                setUnresolvedJsonReferences("ownedMemberFeature", *ids);
            }
        }
    }
}
// END GENERATED JSON
