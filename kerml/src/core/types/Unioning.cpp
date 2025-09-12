//
// Created by Moritz Herzog on 25.03.25.
//

#include "Unioning.h"
#include <stdexcept>

namespace KerML::Entities
{
	Unioning::Unioning(std::shared_ptr<Type> typeUnioned, std::shared_ptr<Type> unioningType)
	{
		if (typeUnioned == nullptr)
			throw std::runtime_error("Type unioned is not allowed to be null");
		TypeUnionioned = typeUnioned;

		if (unioningType == nullptr)
			throw std::runtime_error("Unioning type is nott allowed to be null");
		UnioningType = unioningType;
	}

	std::shared_ptr<Type> Unioning::typeUnioned()
	{
		return TypeUnionioned;
	}

	void Unioning::setTypeUnioned(std::shared_ptr<Type> typeUnioned)
	{
		if (typeUnioned == nullptr)
			throw std::runtime_error("Type unioned is not allowed to be null");
		TypeUnionioned = typeUnioned;
	}

	std::shared_ptr<Type> Unioning::unioningType()
	{
		return UnioningType;
	}

	void Unioning::setUnioningType(std::shared_ptr<Type> unioningType)
	{
		if (unioningType == nullptr)
			throw std::runtime_error("Unioning type is nott allowed to be null");
		UnioningType = unioningType;
	}
}
