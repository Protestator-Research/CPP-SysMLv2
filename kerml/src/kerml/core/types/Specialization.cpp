//
// Created by Moritz Herzog on 25.03.25.
//
//---------------------------------------------------------
// Constants, Definitions, Pragmas
//---------------------------------------------------------

//---------------------------------------------------------
// External Classes
//---------------------------------------------------------
#include <stdexcept>
//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include <kerml/core/types/Type.h>
#include <kerml/core/types/Specialization.h>
//---------------------------------------------------------
// Forwarding
//---------------------------------------------------------

//---------------------------------------------------------
namespace KerML::Entities
{
	Specialization::Specialization(std::shared_ptr<Type> general, std::shared_ptr<Type> specific)
	{
		if (general == nullptr)
			throw std::runtime_error("General type is not allowed to be null");
		General = general;

		if (specific == nullptr)
			throw std::runtime_error("Specific type is not allowed to be null");
		Specific = specific;
	}

	std::shared_ptr<Type> Specialization::general() const
	{
		return General;
	}

	void Specialization::setGeneral(std::shared_ptr<Type> general)
	{
		if (general == nullptr)
			throw std::runtime_error("General type is not allowed to be null");

		General = general;
	}

	std::shared_ptr<Type> Specialization::specific() const
	{
		return Specific;
	}

	void Specialization::setSpecific(std::shared_ptr<Type> specific)
	{
		if (specific == nullptr)
			throw std::runtime_error("Specific type is not allowed to be null");

		Specific = specific;
	}
}
