//
// Created by Moritz Herzog on 25.03.25.
//

#pragma once

#include <kerml/core/types/Specialization.h>
#include <kerml/kerml_global.h>

namespace KerML::Entities {
    class Type;
    class Feature;

    class KERML_EXPORT FeatureTyping : public Specialization{
    public:
        FeatureTyping();
        FeatureTyping(const std::shared_ptr<KerML::Entities::Type>& type, const std::shared_ptr<KerML::Entities::Feature>& typedFeature = nullptr);
        ~FeatureTyping() = default;

        std::shared_ptr<KerML::Entities::Feature> typedFeature();
        void setTypedFeature(const std::shared_ptr<KerML::Entities::Feature>& typedFeature);

        std::shared_ptr<KerML::Entities::Type> type();
        void setType(const std::shared_ptr<KerML::Entities::Type>& type);

    private:
        std::shared_ptr<KerML::Entities::Feature> TypedFeature;
        std::shared_ptr<KerML::Entities::Type> Type;
    };
}