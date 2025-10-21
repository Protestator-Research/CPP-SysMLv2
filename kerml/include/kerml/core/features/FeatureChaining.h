//
// Created by Moritz Herzog on 25.03.25.
//

#pragma once

#include <../../root/elements/Relationship.h>

namespace KerML::Entities {
    class Feature;
}

namespace KerML::Entities {
    class FeatureChaining : public Relationship {
    public:
        FeatureChaining() = delete;
        FeatureChaining(std::shared_ptr<Feature> chainingFeature, std::shared_ptr<Feature> featureChained, boost::uuids::uuid elementID = boost::uuids::random_generator()(), std::shared_ptr<Element> owner = nullptr);
        ~FeatureChaining() override = default;

        void setChainingFeature(std::shared_ptr<Feature> chainingFeature);
        [[nodiscard]] std::shared_ptr<Feature> chainingFeature() const;

    protected:
        void setFeatureChained(std::shared_ptr<Feature> featureChained);
        std::shared_ptr<Feature> featureChained() const;

    private:
        std::shared_ptr<Feature> ChainingFeature;
        std::shared_ptr<Feature> FeatureChained;
    };
}

