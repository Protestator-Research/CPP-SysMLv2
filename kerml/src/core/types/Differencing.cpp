//
// Created by Moritz Herzog on 25.03.25.
//

#include "Differencing.h"
#include <stdexcept>

namespace KerML::Entities
{
	Differencing::Differencing(std::shared_ptr<Type> typeDifferenced, std::shared_ptr<Type> differencingType)
	{
		if (typeDifferenced == nullptr)
			std::runtime_error("Type Differenced is not allowed to be null");


		TypeDifferenced = typeDifferenced;

		if (differencingType == nullptr)
			std::runtime_error("Differencing type is not allwed to be null");

		DifferencingType = differencingType;
	}

	std::shared_ptr<Type> Differencing::differencingType()
	{
		return DifferencingType;
	}

	void Differencing::setDifferencingType(std::shared_ptr<Type> differencingType)
	{
		if (differencingType == nullptr)
			std::runtime_error("Differencing type is not allwed to be null");

		DifferencingType = differencingType;
	}

	std::shared_ptr<Type> Differencing::typeDifferenced()
	{
		return TypeDifferenced;
	}

	void Differencing::setTypeDifferenced(std::shared_ptr<Type> typeDifferenced)
	{
		if (differencingType == nullptr)
			std::runtime_error("Differencing type is not allwed to be null");

		TypeDifferenced = typeDifferenced;
	}
}
