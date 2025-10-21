//
// Created by Moritz Herzog on 25.03.25.
//

#include <kerml/core/types/Intersecting.h>
#include <stdexcept>

namespace KerML::Entities
{
	Intersecting::Intersecting(std::shared_ptr<Type> typeIntersecting, std::shared_ptr<Type> intersectingType)
	{
		if (typeIntersecting == nullptr)
			throw std::runtime_error("Type intersecting is according to the standard not allowed to be null.");

		TypeIntersected = typeIntersecting;

		if (intersectingType == nullptr)
			throw std::runtime_error("Intersecting type is according to the standard not allowed to be null.");

		IntersectingType = intersectingType;
	}

	std::shared_ptr<Type> Intersecting::intersectingType()
	{
		return IntersectingType;
	}

	void Intersecting::setIntersectingType(std::shared_ptr<Type> intersectingType)
	{
		if (intersectingType == nullptr)
			throw std::runtime_error("Intersecting type is according to the standard not allowed to be null.");
		IntersectingType = intersectingType;
	}

	std::shared_ptr<Type> Intersecting::typeIntersecting()
	{
		return TypeIntersected;
	}

	void Intersecting::setTypeIntersecting(std::shared_ptr<Type> typeIntersecting)
	{
		if (typeIntersecting == nullptr)
			throw std::runtime_error("Type intersecting is according to the standard not allowed to be null.");
		TypeIntersected = typeIntersecting;
	}
}
