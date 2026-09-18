//
// Created by Moritz Herzog on 25.03.25.
//

#include <memory>

#include <kerml/core/features/FeatureMembership.h>

#include <kerml/core/types/Type.h>
#include <kerml/core/features/Feature.h>

namespace KerML::Entities {
    FeatureMembership::FeatureMembership(std::shared_ptr<Feature> ownedMemberFeature,
                                         std::shared_ptr<Type> owningType,
                                         std::vector<std::shared_ptr<Type>> type) {
        _dType = "FeatureMembership";

        setOwnedMemberElement(ownedMemberFeature);
        setMembershipOwningNamespace(owningType);
        _Type = type;
    }

    void FeatureMembership::setOwnedMemberFeature(std::shared_ptr<Feature> ownedMemberFeature) {
        setOwnedMemberElement(ownedMemberFeature);
    }

    std::shared_ptr<Feature> FeatureMembership::ownedMemberFeature() const {
        return std::dynamic_pointer_cast<Feature>(ownedMemberElement());
    }

    void FeatureMembership::setOwningType(std::shared_ptr<Type> owningType) {
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