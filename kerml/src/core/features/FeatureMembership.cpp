//
// Created by Moritz Herzog on 25.03.25.
//

#include <memory>

#include "FeatureMembership.h"

#include "../types/Type.h"
#include "Feature.h"

namespace KerML::Entities {
    FeatureMembership::FeatureMembership(std::shared_ptr<Feature> ownedMemberFeature,
                                         std::shared_ptr<Type> owningType,
                                         std::vector<std::shared_ptr<Type>> type) {
        OwnedMemberFeature = ownedMemberFeature;
        OwningType = owningType;
        _Type = type;
    }

    void FeatureMembership::setOwnedMemberFeature(std::shared_ptr<Feature> ownedMemberFeature) {
        OwnedMemberFeature = ownedMemberFeature;
    }

    std::shared_ptr<Feature> FeatureMembership::ownedMemberFeature() const {
        return OwnedMemberFeature;
    }

    void FeatureMembership::setOwningType(std::shared_ptr<Type> owningType) {
        OwningType = owningType;
    }

    std::shared_ptr<Type> FeatureMembership::owningType() const {
        return OwningType;
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