//
// Created by Moritz Herzog on 25.03.25.
//

#include "../../../include/kerml/core/features/FeatureChaining.h"

namespace KerML::Entities {

    FeatureChaining::FeatureChaining(std::shared_ptr<Feature> chainingFeature, std::shared_ptr<Feature> featureChained,
                                     boost::uuids::uuid elementID, std::shared_ptr<Element> owner)
                                     : Relationship(elementID,owner){
        ChainingFeature = chainingFeature;
        FeatureChained = featureChained;
    }

    void FeatureChaining::setChainingFeature(std::shared_ptr<Feature> chainingFeature) {
        ChainingFeature = chainingFeature;
    }

    std::shared_ptr<Feature> FeatureChaining::chainingFeature() const {
        return ChainingFeature;
    }

    void FeatureChaining::setFeatureChained(std::shared_ptr<Feature> featureChained) {
        FeatureChained = featureChained;
    }

    std::shared_ptr<Feature> FeatureChaining::featureChained() const {
        return FeatureChained;
    }
}