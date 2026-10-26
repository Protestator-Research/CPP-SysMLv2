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
#include <kerml/core/classifiers/Classifier.h>
#include <kerml/KerML.h>
#include <nlohmann/json.hpp>
#include "../../model/JsonSupport.h"
//---------------------------------------------------------
// Forwarding
//---------------------------------------------------------

namespace KerML::Entities {
	Classifier::Classifier(boost::uuids::uuid elementID, std::shared_ptr<Element> owner) :
		Element(elementID, owner), Type(elementID, owner)
	{
		_dType = "Classifier";
	}

	Classifier::Classifier(std::string namespaceName, boost::uuids::uuid elementID, std::shared_ptr<Element> owner) :
	Element(elementID, owner), Type(Json::looksLikeJson(namespaceName) ? std::string() : namespaceName, elementID, owner)
	{
		_dType = "Classifier";
		if (Json::looksLikeJson(namespaceName)) {
		    deserializeAndPopulate(namespaceName);
		    captureJsonSource(namespaceName);
		}
	}

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

// BEGIN GENERATED JSON (kerml/tools/generate_json.py): do not edit, run the script instead.
namespace KerML::Entities {
    std::string Classifier::serializeToJson() {
        nlohmann::json json = nlohmann::json::parse(Type::serializeToJson());
        json["ownedSubclassification"] = Json::reference(unresolvedJsonReferences("ownedSubclassification"), Classifier::ownedSubclassification());
        return applyJsonSource(json.dump(JSON_INTENT));
    }

    void Classifier::deserializeAndPopulate(const std::string& jsonString) {
        Type::deserializeAndPopulate(jsonString);
    }

    void Classifier::resolveJsonReferences(const std::function<std::shared_ptr<Element>(const boost::uuids::uuid&)>& lookup) {
        Type::resolveJsonReferences(lookup);
    }
}
// END GENERATED JSON
