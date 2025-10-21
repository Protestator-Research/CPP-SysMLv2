//
// Created by Moritz Herzog on 25.03.25.
//

#include <stdexcept>
#include "../../../include/kerml/core/features/FeatureInverting.h"

namespace KerML::Entities {

    FeatureInverting::FeatureInverting(std::shared_ptr<Feature> featureInverted, std::shared_ptr<Feature> invertingFeature, boost::uuids::uuid elementID, std::shared_ptr<Element> owner) :
            Relationship(elementID, owner)
    {
        if(featureInverted == nullptr)
            throw std::invalid_argument("Feature inverted is not allowed to be null, according to the standard.");
        FeatureInverted = featureInverted;

        if(invertingFeature == nullptr)
            throw std::invalid_argument("Inverting feature is not allowed to be null, according to the standard.");
        InvertingFeature = invertingFeature;

    }

    void FeatureInverting::setFeatureInverted(std::shared_ptr<Feature> featureInverting) {
        FeatureInverted = featureInverting;
    }

    std::shared_ptr<Feature> FeatureInverting::featureInverted() const {
        return FeatureInverted;
    }

    void FeatureInverting::setInvertingFeature(std::shared_ptr<Feature> invertingFeature) {
        InvertingFeature = invertingFeature;
    }

    std::shared_ptr<Feature> FeatureInverting::invertingFeature() const {
        return InvertingFeature;
    }

    void FeatureInverting::setOwningFeature(std::shared_ptr<Feature> owningFeature) {
        OwningFeature = owningFeature;
    }

    std::shared_ptr<Feature> FeatureInverting::owningFeature() const {
        return OwningFeature;
    }


}