//
// Created by Moritz Herzog on 25.03.25.
//

#pragma once

#include "FeatureMembership.h"

namespace KerML::Entities {
    class EndFeatureMembership : public FeatureMembership {
    public:
        EndFeatureMembership() = delete;
        EndFeatureMembership(std::shared_ptr<Feature> ownedMemberFeature, std::shared_ptr<Type> owningType,  std::vector<std::shared_ptr<Type>> type);
        ~EndFeatureMembership() override = default;

        bool isEnd();
    };
}
