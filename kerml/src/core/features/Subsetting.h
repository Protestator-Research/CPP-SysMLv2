//
// Created by Moritz Herzog on 25.03.25.
//

#pragma once

#include <core/types/Specialization.h>

namespace KerML::Entities {
    class Feature;

    /**
     * @class Subsetting
     * @version 1.0 Beta 4
     * @author Moritz Herzog <herzogm@rptu.de>
     * @brief
     */
    class Subsetting : public Specialization{
    public:
        Subsetting(std::shared_ptr<Feature> subsettedFeature, std::shared_ptr<Feature> subsettingFeature);
        Subsetting() = delete;
        ~Subsetting() override = default;

        std::shared_ptr<Feature> subsettedFeature() const;
        void setSubsettedFeature(std::shared_ptr<Feature> subsetted);

        std::shared_ptr<Feature> subsettingFeature() const;
        void setSubsettingFeature(std::shared_ptr<Feature> subsettingFeature);


    protected:
        std::shared_ptr<Feature> owningFeature() const;
        void setOwningFeature(std::shared_ptr<Feature> owningFeature);

    private:
        std::shared_ptr<Feature> SubsettedFeature;
        std::shared_ptr<Feature> SubsettingFeature;
        std::shared_ptr<Feature> OwningFeature;

    };
}
