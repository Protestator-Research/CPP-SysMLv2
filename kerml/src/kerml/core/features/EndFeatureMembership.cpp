//
// Created by Moritz Herzog on 25.03.25.
//

#include "../../../include/kerml/core/features/EndFeatureMembership.h"

namespace  KerML::Entities {

    EndFeatureMembership::EndFeatureMembership(std::shared_ptr<Feature> ownedMemberFeature,
                                               std::shared_ptr<Type> owningType,
                                               std::vector<std::shared_ptr<Type>> type)
            : FeatureMembership(ownedMemberFeature, owningType, type) {

    }

    bool EndFeatureMembership::isEnd() {
        return true;
    }
}