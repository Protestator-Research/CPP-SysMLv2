#include <kerml/core/features/CrossSubsetting.h>

#include <stdexcept>


namespace KerML::Entities {
    CrossSubsetting::CrossSubsetting(std::shared_ptr<Feature> crossedFeature, std::shared_ptr<Feature> crossingFeature)
    : Subsetting(crossedFeature, crossingFeature) {
        if(crossedFeature == nullptr)
            throw std::invalid_argument("Crossed feature is not allowed to be null");
        CrossedFeature = crossedFeature;

        if(crossingFeature == nullptr)
            throw std::invalid_argument("Crossing feature is not allowed to be null");
        CrossingFeature = crossingFeature;
    }

    void CrossSubsetting::setCrossedFeature(std::shared_ptr<Feature> crossedFeature) {
        if(crossedFeature == nullptr)
            throw std::invalid_argument("Crossed feature is not allowed to be null");
        CrossedFeature = crossedFeature;
    }

    std::shared_ptr<Feature> CrossSubsetting::crossedFeature() {
        return CrossedFeature;
    }

    void CrossSubsetting::setCrossingFeature(std::shared_ptr<Feature> crossingFeautre) {
        if(crossingFeautre == nullptr)
            throw std::invalid_argument("Crossing feature is not allowed to be null");
        CrossingFeature = crossingFeautre;
    }

    std::shared_ptr<Feature> CrossSubsetting::crossingFeatures() {
        return CrossingFeature;
    }
}
