//
// Created by Moritz Herzog on 25.03.25.
//

#include <kerml/core/types/Disjoining.h>

#include <stdexcept>

namespace KerML::Entities {
	Disjoining::Disjoining(std::shared_ptr<Type> typeDisjoined, std::shared_ptr<Type> disjoiningType) :
	Relationship()
	{
		if (typeDisjoined == nullptr)
			throw std::runtime_error("Empty TypeDisjoined is not allowed");
		TypeDisjoined = typeDisjoined;

		if (disjoiningType == nullptr)
			throw std::runtime_error("Empty DisjoiningType is not allowed");
		DisjoiningType = disjoiningType;

	}

	std::shared_ptr<Type> Disjoining::typeDisjoined()
	{
		return TypeDisjoined;
	}

	void Disjoining::setTypeDisjoined(std::shared_ptr<Type> typeDisjoined)
	{
		if (typeDisjoined == nullptr)
			throw std::runtime_error("Empty TypeDisjoined is not allowed");

		TypeDisjoined = typeDisjoined;
	}

	std::shared_ptr<Type> Disjoining::disjoiningType()
	{
		return DisjoiningType;
	}

	void Disjoining::setDisjoiningType(std::shared_ptr<Type> disjoiningType)
	{
		if (disjoiningType == nullptr)
			throw std::runtime_error("Empty DisjoiningType is not allowed");

		DisjoiningType = disjoiningType;
	}

	std::shared_ptr<Type> Disjoining::owningType()
	{
		return OwningType;
	}

	void Disjoining::setOwningType(std::shared_ptr<Type> owningType)
	{
		OwningType = owningType;
	}
}
