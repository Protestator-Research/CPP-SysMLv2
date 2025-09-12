//
// Created by Moritz Herzog on 25.03.25.
//

#include "Redefinition.h"

namespace KerML::Entities
{
	Redefinition::Redefinition(std::shared_ptr<Feature> redefinedFeature, std::shared_ptr<Feature> redefiningFeature) :
	Subsetting(redefinedFeature,redefiningFeature)
	{
		if (redefinedFeature == nullptr)
			throw std::invalid_argument("The redefined Feature is not allowed to be null. This is accroding to the Standard");
		RedefinedFeature = redefinedFeature;

		if (redefiningFeature == nullptr)
			throw std::invalid_argument("The redefining Feature is not allowed to be null. This is according to the Standard.");
		RedefiningFeature = redefiningFeature;
	}

	std::shared_ptr<Feature> Redefinition::redefinedFeature() const
	{
		return RedefinedFeature;
	}

	void Redefinition::setRedefinedFeature(std::shared_ptr<Feature> redefinedFeature)
	{
		if (redefinedFeature == nullptr)
			throw std::invalid_argument("The redefined Feature is not allowed to be null. This is accroding to the Standard");
		RedefinedFeature = redefinedFeature;
	}

	std::shared_ptr<Feature> Redefinition::redefiningFeature() const
	{
		return RedefiningFeature;
	}

	void Redefinition::setRedefiningFeature(std::shared_ptr<Feature> redefiningFeature)
	{
		if (redefiningFeature == nullptr)
			throw std::invalid_argument("The redefining Feature is not allowed to be null. This is according to the Standard.");
		RedefiningFeature = redefiningFeature;
	}
}
