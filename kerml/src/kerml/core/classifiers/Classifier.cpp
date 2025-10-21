//
// Created by Moritz Herzog on 25.03.25.
//
//---------------------------------------------------------
// Constants, Definitions, Pragmas
//---------------------------------------------------------

//---------------------------------------------------------
// External Classes
//---------------------------------------------------------

//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include "../../../include/kerml/core/classifiers/Classifier.h"
//---------------------------------------------------------
// Forwarding
//---------------------------------------------------------

namespace KerML::Entities {
	Classifier::Classifier(boost::uuids::uuid elementID, std::shared_ptr<Element> owner) :
		Type(elementID, owner)
	{ 	}

	Classifier::Classifier(std::string namespaceName, boost::uuids::uuid elementID, std::shared_ptr<Element> owner) :
	Type(namespaceName,elementID,owner)
	{	}

	void Classifier::setOwnedSubsclassification(std::vector<std::shared_ptr<Subclassification>> ownedSubclassification)
	{
		OwnedSubclassification = ownedSubclassification;
	}

	std::vector<std::shared_ptr<Subclassification>> Classifier::ownedSubclassification() const
	{
		return OwnedSubclassification;
	}

	void Classifier::appendOwnedSubclassification(
		std::vector<std::shared_ptr<Subclassification>> ownedSubclassification)
	{
		OwnedSubclassification.insert(OwnedSubclassification.end(), ownedSubclassification.begin(), ownedSubclassification.end());
	}

	void Classifier::appendOwnedSubclassification(std::shared_ptr<Subclassification> ownedSubclassification)
	{
		OwnedSubclassification.push_back(ownedSubclassification);
	}
}
