//
// Created by Moritz Herzog on 25.03.25.
//

#include <kerml/core/features/Subsetting.h>

#include <kerml/core/features/Feature.h>
#include <exception>

namespace KerML::Entities
{
	Subsetting::Subsetting(std::shared_ptr<Feature> subsettedFeature, std::shared_ptr<Feature> subsettingFeature) :
	Specialization(subsettedFeature, subsettingFeature)
	{
		if (subsettedFeature == nullptr)
			throw std::invalid_argument("The subsetted feature is not allowed to be null. This is defined by the standard.");
		SubsettedFeature = subsettedFeature;

		if (subsettingFeature == nullptr)
			throw std::invalid_argument("The subsetting feature is not allowed to be null. This is defined by the standard.");
		SubsettingFeature = subsettingFeature;

	}

	std::shared_ptr<Feature> Subsetting::subsettedFeature() const
	{
		return SubsettedFeature;
	}

	void Subsetting::setSubsettedFeature(std::shared_ptr<Feature> subsettedFeature)
	{
		if (subsettedFeature == nullptr)
			throw std::invalid_argument("The subsetted feature is not allowed to be null. This is defined by the standard.");
		SubsettedFeature = subsettedFeature;

	}

	std::shared_ptr<Feature> Subsetting::subsettingFeature() const
	{
		return SubsettingFeature;
	}

	void Subsetting::setSubsettingFeature(std::shared_ptr<Feature> subsettingFeature)
	{
		if (subsettingFeature == nullptr)
			throw std::invalid_argument("The subsetting feature is not allowed to be null. This is defined by the standard.");
		SubsettingFeature = subsettingFeature;

	}

	std::shared_ptr<Feature> Subsetting::owningFeature() const
	{
		return OwningFeature;
	}

	void Subsetting::setOwningFeature(std::shared_ptr<Feature> owningFeature)
	{
		OwningFeature = owningFeature;
	}
}
