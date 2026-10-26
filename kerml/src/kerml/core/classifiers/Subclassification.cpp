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
#include <kerml/core/classifiers/Subclassification.h>
#include <kerml/core/classifiers/Classifier.h>
#include <kerml/KerML.h>
#include <nlohmann/json.hpp>
#include "../../model/JsonSupport.h"
//---------------------------------------------------------
// Forwarding
//---------------------------------------------------------

//---------------------------------------------------------
namespace KerML::Entities
{
	Subclassification::Subclassification(std::shared_ptr<Classifier> superclassifier, std::shared_ptr<Classifier> subclassifier)
		: Specialization(superclassifier,subclassifier)
	{
		_dType = "Subclassification";

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
		clearUnresolvedJsonReferences("superclassifier");
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
		clearUnresolvedJsonReferences("subclassifier");
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
		clearUnresolvedJsonReferences("owningClassifier");
		if (owningClassifier.has_value() && (owningClassifier.value() != nullptr))
			OwningClassifier = owningClassifier.value();
	}
}

// BEGIN GENERATED JSON (kerml/tools/generate_json.py): do not edit, run the script instead.
namespace KerML::Entities {
    Subclassification::Subclassification(const std::string& nameOrJson) {
        _dType = "Subclassification";
        if (Json::looksLikeJson(nameOrJson)) {
            deserializeAndPopulate(nameOrJson);
            captureJsonSource(nameOrJson);
        } else {
            setDeclaredName(nameOrJson);
        }
    }

    std::string Subclassification::serializeToJson() {
        nlohmann::json json = nlohmann::json::parse(Specialization::serializeToJson());
        json["superclassifier"] = Json::reference(unresolvedJsonReferences("superclassifier"), Subclassification::superclassifier());
        json["subclassifier"] = Json::reference(unresolvedJsonReferences("subclassifier"), Subclassification::subclassifier());
        json["owningClassifier"] = Json::reference(unresolvedJsonReferences("owningClassifier"), Subclassification::owningClassifier());
        return applyJsonSource(json.dump(JSON_INTENT));
    }

    void Subclassification::deserializeAndPopulate(const std::string& jsonString) {
        Specialization::deserializeAndPopulate(jsonString);
        const nlohmann::json json = nlohmann::json::parse(jsonString);
        std::vector<boost::uuids::uuid> ids;
        if (Json::readReferences(json, "superclassifier", ids))
            setUnresolvedJsonReferences("superclassifier", ids);
        if (Json::readReferences(json, "subclassifier", ids))
            setUnresolvedJsonReferences("subclassifier", ids);
        if (Json::readReferences(json, "owningClassifier", ids))
            setUnresolvedJsonReferences("owningClassifier", ids);
    }

    void Subclassification::resolveJsonReferences(const std::function<std::shared_ptr<Element>(const boost::uuids::uuid&)>& lookup) {
        Specialization::resolveJsonReferences(lookup);
        if (const auto ids = unresolvedJsonReferences("superclassifier")) {
            try {
                if (auto target = std::dynamic_pointer_cast<KerML::Entities::Classifier>(lookup(ids->front()))) {
                    Subclassification::setSuperclassifier(std::move(target));
                    clearUnresolvedJsonReferences("superclassifier");
                }
            } catch (const std::exception&) {
                // The reference stays unresolved if the model refuses it.
                setUnresolvedJsonReferences("superclassifier", *ids);
            }
        }
        if (const auto ids = unresolvedJsonReferences("subclassifier")) {
            try {
                if (auto target = std::dynamic_pointer_cast<KerML::Entities::Classifier>(lookup(ids->front()))) {
                    Subclassification::setSubclassifier(std::move(target));
                    clearUnresolvedJsonReferences("subclassifier");
                }
            } catch (const std::exception&) {
                // The reference stays unresolved if the model refuses it.
                setUnresolvedJsonReferences("subclassifier", *ids);
            }
        }
        if (const auto ids = unresolvedJsonReferences("owningClassifier")) {
            try {
                if (auto target = std::dynamic_pointer_cast<KerML::Entities::Classifier>(lookup(ids->front()))) {
                    Subclassification::setOwningClassifier(std::move(target));
                    clearUnresolvedJsonReferences("owningClassifier");
                }
            } catch (const std::exception&) {
                // The reference stays unresolved if the model refuses it.
                setUnresolvedJsonReferences("owningClassifier", *ids);
            }
        }
    }
}
// END GENERATED JSON
