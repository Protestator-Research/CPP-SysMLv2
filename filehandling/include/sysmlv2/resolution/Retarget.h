//
// Redirects the relationships of the model from a placeholder to the element a reference resolved to.
// Most relationship classes keep the target in several (redundant) fields of their class hierarchy; these helpers
// update all of them.
//
#pragma once

#include <kerml/core/classifiers/Subclassification.h>
#include <kerml/core/features/CrossSubsetting.h>
#include <kerml/core/features/FeatureTyping.h>
#include <kerml/core/features/Redefinition.h>
#include <kerml/core/features/ReferenceSubsetting.h>
#include <kerml/core/features/Subsetting.h>
#include <kerml/core/types/Specialization.h>

#include <memory>

namespace SysMLv2::Files::Retarget {

    inline void generalization(KerML::Entities::Specialization& relationship, const std::shared_ptr<KerML::Entities::Type>& general) {
        relationship.setGeneral(general);
    }

    inline void featureTyping(KerML::Entities::FeatureTyping& relationship, const std::shared_ptr<KerML::Entities::Type>& type) {
        relationship.setType(type);
    }

    inline void subclassification(KerML::Entities::Subclassification& relationship, const std::shared_ptr<KerML::Entities::Classifier>& superclassifier) {
        relationship.setSuperclassifier(superclassifier);
        relationship.setGeneral(superclassifier);
    }

    inline void subsetting(KerML::Entities::Subsetting& relationship, const std::shared_ptr<KerML::Entities::Feature>& feature) {
        relationship.setSubsettedFeature(feature);
        relationship.setGeneral(feature);
    }

    inline void redefinition(KerML::Entities::Redefinition& relationship, const std::shared_ptr<KerML::Entities::Feature>& feature) {
        relationship.setRedefinedFeature(feature);
        relationship.setSubsettedFeature(feature);
        relationship.setGeneral(feature);
    }

    inline void referenceSubsetting(KerML::Entities::ReferenceSubsetting& relationship, const std::shared_ptr<KerML::Entities::Feature>& feature) {
        relationship.setReferencedFeature(feature);
        relationship.setSubsettedFeature(feature);
        relationship.setGeneral(feature);
    }

    inline void crossSubsetting(KerML::Entities::CrossSubsetting& relationship, const std::shared_ptr<KerML::Entities::Feature>& feature) {
        relationship.setCrossedFeature(feature);
        relationship.setSubsettedFeature(feature);
        relationship.setGeneral(feature);
    }
}
