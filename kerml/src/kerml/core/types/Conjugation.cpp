//
// Created by Moritz Herzog on 25.03.25.
//

#include <stdexcept>
#include <kerml/core/types/Conjugation.h>

namespace KerML::Entities
{
	Conjugation::Conjugation(std::shared_ptr<Type> originalType, std::shared_ptr<Type> conjugatedType)
	{
		_dType = "Conjugation";

		if (originalType == nullptr)
			throw std::runtime_error("Original Type is not allowed to be a nullptr");

		if (conjugatedType == nullptr)
			throw std::runtime_error("Conjungated Type is not allowed to be a nullptr");

		OriginalType = originalType;
		ConjugatedType = conjugatedType;
	}

	std::shared_ptr<Type> Conjugation::originalType()
	{
		return OriginalType;
	}

	void Conjugation::setOrginalType(std::shared_ptr<Type> originalType)
	{
		if (originalType == nullptr)
			throw std::runtime_error("Original Type is not allowed to be a nullptr");

		OriginalType = originalType;
	}

	std::shared_ptr<Type> Conjugation::conjungatedType()
	{
		return ConjugatedType;
	}

	void Conjugation::setConjungatedType(std::shared_ptr<Type> conjungatedType)
	{
		if (conjungatedType == nullptr)
			throw std::runtime_error("Conjungated Type is not allowed to be a nullptr");
		ConjugatedType = conjungatedType;
	}

	std::shared_ptr<Type> Conjugation::owningType()
	{
		return OwningType;
	}

	void Conjugation::setOwningType(std::shared_ptr<Type> owningType)
	{
		OwningType = owningType;
	}
}
