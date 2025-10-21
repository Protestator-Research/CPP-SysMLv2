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
#include "../../../include/kerml/core/classifiers/Subclassification.h"
#include "../../../include/kerml/core/classifiers/Classifier.h"
//---------------------------------------------------------
// Forwarding
//---------------------------------------------------------

//---------------------------------------------------------
namespace KerML::Entities
{
	Subclassification::Subclassification(std::shared_ptr<Classifier> superclassifier, std::shared_ptr<Classifier> subclassifier)
		: Specialization(superclassifier,subclassifier)
	{
		if (superclassifier == nullptr)
			throw std::invalid_argument("Superclassifier is not allowed to be null.");
		Superclassifier = superclassifier;

		if (subclassifier == nullptr)
			throw std::invalid_argument("Subclassifier is not allowed to be null");
		Subclassifier = subclassifier;
	}

	std::shared_ptr<Classifier> Subclassification::superclassifier() const
	{
		return Superclassifier;
	}

	void Subclassification::setSuperclassifier(std::shared_ptr<Classifier> superclassifier)
	{
		if (superclassifier == nullptr)
			throw std::invalid_argument("Superclassifier is not allowed to be null.");
		Superclassifier = superclassifier;
	}

	std::shared_ptr<Classifier> Subclassification::subclassifier() const
	{
		return Subclassifier;
	}

	void Subclassification::setSubclassifier(std::shared_ptr<Classifier> subclassifier)
	{
		if (subclassifier == nullptr)
			throw std::invalid_argument("Subclassifier is not allowed to be null");
		Subclassifier = subclassifier;
	}

	std::optional<std::shared_ptr<Classifier>> Subclassification::owningClassifier() const
	{
		if (OwningClassifier == nullptr)
			return {};
        return OwningClassifier;
	}

	void Subclassification::setOwningClassifier(std::optional<std::shared_ptr<Classifier>> owningClassifier)
	{
		if (owningClassifier.has_value() && (owningClassifier.value() != nullptr))
			OwningClassifier = owningClassifier.value();
	}
}
