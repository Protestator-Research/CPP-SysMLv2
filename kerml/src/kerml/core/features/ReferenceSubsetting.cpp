//
// Created by Moritz Herzog on 25.03.25.
//

#include "../../../include/kerml/core/features/ReferenceSubsetting.h"

namespace KerML::Entities
{
	ReferenceSubsetting::ReferenceSubsetting(std::shared_ptr<Feature> referencedFeature,
		std::shared_ptr<Feature> referencingFeature) :
	Subsetting(referencedFeature,referencingFeature)
	{
		if (referencedFeature == nullptr)
			throw std::invalid_argument("Referenced Feature is not allowed to be null. This is declared in the standard");
		ReferencedFeature = referencedFeature;

		if (referencingFeature == nullptr)
			throw std::invalid_argument("Referencing Feature to be null is not allowed, according to the standard.");
		ReferencingFeature = referencingFeature;

	}

	std::shared_ptr<Feature> ReferenceSubsetting::referencedFeature() const
	{
		return ReferencedFeature;
	}

	void ReferenceSubsetting::setReferencedFeature(std::shared_ptr<Feature> referencedFeature)
	{
		if (referencedFeature == nullptr)
			throw std::invalid_argument("Referenced Feature is not allowed to be null. This is declared in the standard");
		ReferencedFeature = referencedFeature;
	}

	std::shared_ptr<Feature> ReferenceSubsetting::referencingFeature() const
	{
		return ReferencingFeature;
	}

	void ReferenceSubsetting::setReferencingFeature(std::shared_ptr<Feature> referencingFeature)
	{
		if (referencingFeature == nullptr)
			throw std::invalid_argument("Referencing Feature to be null is not allowed, according to the standard.");
		ReferencingFeature = referencingFeature;
	}
}
