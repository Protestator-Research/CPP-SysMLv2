//
// Created by Moritz Herzog on 25.03.25.
//
#pragma once

#include <kerml/core/features/Featuring.h>
#include <kerml/kerml_global.h>

namespace KerML::Entities {
    class Feature;
    class Type;

    /**
     * Defines the Typefeatureing
     * @version 1.0 SysML v2 Release March 2026
     * @author Moritz Herzog <herzogm@rptu.de>
     * @date 02.06.2026
     */
    class KERML_EXPORT TypeFeaturing : public Relationship {
    public:
        TypeFeaturing() = delete;
        TypeFeaturing(const std::shared_ptr<Type>& typeFeaturingOfType, const std::shared_ptr<Feature>& featureOfType, const std::shared_ptr<Feature>& owningFeatureOfType = nullptr);
        ~TypeFeaturing() = default;

        void setFeaturingType(const std::shared_ptr<Type>& typeFeaturingOfType);
        std::shared_ptr<Type> featuringType() const;

        void setFeatureOfType(const std::shared_ptr<Feature>& featureOfType);
        std::shared_ptr<Feature> featureOfType() const;

    protected:
        void setOwningFeatureOfType(const std::shared_ptr<Feature>& owningFeatureOfType);
        std::shared_ptr<Feature> owningFeatureOfType();


    private:
        std::shared_ptr<Type> TypeFeaturingOfType;
        std::shared_ptr<Feature> FeatureOfType;
        std::shared_ptr<Feature> OwningFeatureOfType;
    };
}
