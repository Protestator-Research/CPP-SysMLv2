//
// Created by Moritz Herzog on 25.03.25.
//

#include <kerml/core/features/Multiplicity.h>

namespace KerML::Entities {
	Multiplicity::Multiplicity(unsigned minimum)
	{
		MinimumNumber = minimum;
		MaximumNumber = MinimumNumber;
	}

	Multiplicity::Multiplicity(unsigned minimum, unsigned maximum)
	{
		MinimumNumber = minimum;
		MaximumNumber = maximum;
	}

	Multiplicity::Multiplicity(unsigned minimum, bool unlimited)
	{
		MinimumNumber = minimum;
		setIsUnlimited(unlimited);
	}

	unsigned Multiplicity::minimum() const
	{
		return MinimumNumber;
	}

	void Multiplicity::setMinimum(unsigned minimum)
	{
		MinimumNumber = minimum;
	}

	unsigned Multiplicity::maximum() const
	{
		return MaximumNumber;
	}

	void Multiplicity::setMaximum(unsigned maximum)
	{
		MaximumNumber = maximum;
	}

	bool Multiplicity::isUnlimited() const
	{
		return MaximumNumber == MinimumNumber;
	}

	void Multiplicity::setIsUnlimited(bool isUnlimited)
	{
		if (isUnlimited)
			MaximumNumber = MinimumNumber;
	}
}
