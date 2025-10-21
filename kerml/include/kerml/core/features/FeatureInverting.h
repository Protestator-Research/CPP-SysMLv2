//
// Created by Moritz Herzog on 25.03.25.
//

#pragma once

#include <../../root/elements/Relationship.h>

namespace KerML::Entities {
    class Feature;
}

namespace KerML::Entities {
    /**
     * @class FeatureInverting
     * @version 1.0 Beta 4
     * @author Moritz Herzog
     * @brief Representation of the FeatureInverting of the KerML standard.
     *
     */
    class FeatureInverting : public Relationship{
    public:
        /**
         *
         */
        FeatureInverting() = delete;
        FeatureInverting(std::shared_ptr<Feature> featureInverted,std::shared_ptr<Feature> invertingFeature, boost::uuids::uuid elementID = boost::uuids::random_generator()(), std::shared_ptr<Element> owner = nullptr);
        ~FeatureInverting() override = default;

        void setFeatureInverted(std::shared_ptr<Feature> featureInverting);
        [[nodiscard]] std::shared_ptr<Feature> featureInverted() const;

        void setInvertingFeature(std::shared_ptr<Feature> invertingFeature);
        [[nodiscard]] std::shared_ptr<Feature> invertingFeature() const;

    protected:
        void setOwningFeature(std::shared_ptr<Feature> owningFeature);
        [[nodiscard]] std::shared_ptr<Feature> owningFeature() const;
    private:
        std::shared_ptr<Feature> FeatureInverted;
        std::shared_ptr<Feature> InvertingFeature;
        std::shared_ptr<Feature> OwningFeature;
    };
}