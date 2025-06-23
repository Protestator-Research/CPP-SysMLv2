//
// Created by Moritz Herzog on 25.03.25.
//

#include <stdexcept>
#include "Conjugation.h"

namespace KerML::Entities
{
	Conjungation::Conjungation(std::shared_ptr<Type> originalType, std::shared_ptr<Type> conjugatedType)
	{
		if (originalType == nullptr)
			throw std::runtime_error("Original Type is not allowed to be a nullptr");

		if (conjungatedType == nullptr)
			throw std::runtime_error("Conjungated Type is not allowed to be a nullptr");

		OriginalType = originalType;
		ConjugatedType = conjugatedType;
	}

	std::shared_ptr<Type> Conjungation::originalType()
	{
		return OriginalType;
	}

	void Conjungation::setOrginalType(std::shared_ptr<Type> originalType)
	{
		if (originalType == nullptr)
			throw std::runtime_error("Original Type is not allowed to be a nullptr");

		OriginalType = originalType;
	}

	std::shared_ptr<Type> Conjungation::conjungatedType()
	{
		return ConjugatedType;
	}

	void Conjungation::setConjungatedType(std::shared_ptr<Type> conjungatedType)
	{
		if (conjungatedType == nullptr)
			throw std::runtime_error("Conjungated Type is not allowed to be a nullptr");
		ConjugatedType = conjungatedType;
	}

	std::shared_ptr<Type> Conjungation::owningType()
	{
		return OwningType;
	}

	void Conjungation::setOwningType(std::shared_ptr<Type> owningType)
	{
		OwningType = owningType;
	}
}
