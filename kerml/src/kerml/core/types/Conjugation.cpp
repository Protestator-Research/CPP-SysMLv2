//
// Created by Moritz Herzog on 25.03.25.
//

#include <stdexcept>
#include <kerml/core/types/Conjugation.h>
#include <kerml/KerML.h>
#include <nlohmann/json.hpp>
#include "../../model/JsonSupport.h"

namespace KerML::Entities
{
	Conjugation::Conjugation()
	{
		_dType = "Conjugation";
	}

	Conjugation::Conjugation(std::shared_ptr<Type> originalType, std::shared_ptr<Type> conjugatedType)
	{
		_dType = "Conjugation";

		if (originalType == nullptr)
			throw std::runtime_error("Original Type is not allowed to be a nullptr");

		if (conjugatedType == nullptr)
			throw std::runtime_error("Conjungated Type is not allowed to be a nullptr");

		OriginalType = originalType;
		ConjugatedType = conjugatedType;
	}

	std::shared_ptr<Type> Conjugation::originalType()
	{
		return OriginalType;
	}

	void Conjugation::setOrginalType(std::shared_ptr<Type> originalType)
	{
		clearUnresolvedJsonReferences("originalType");
		if (originalType == nullptr)
			throw std::runtime_error("Original Type is not allowed to be a nullptr");

		OriginalType = originalType;
	}

	std::shared_ptr<Type> Conjugation::conjungatedType()
	{
		return ConjugatedType;
	}

	void Conjugation::setConjungatedType(std::shared_ptr<Type> conjungatedType)
	{
		clearUnresolvedJsonReferences("conjugatedType");
		if (conjungatedType == nullptr)
			throw std::runtime_error("Conjungated Type is not allowed to be a nullptr");
		ConjugatedType = conjungatedType;
	}

	std::shared_ptr<Type> Conjugation::owningType()
	{
		return OwningType;
	}

	void Conjugation::setOwningType(std::shared_ptr<Type> owningType)
	{
		clearUnresolvedJsonReferences("owningType");
		OwningType = owningType;
	}
}

// BEGIN GENERATED JSON (kerml/tools/generate_json.py): do not edit, run the script instead.
namespace KerML::Entities {
    Conjugation::Conjugation(const std::string& nameOrJson) :
        Conjugation() {
        _dType = "Conjugation";
        if (Json::looksLikeJson(nameOrJson)) {
            deserializeAndPopulate(nameOrJson);
            captureJsonSource(nameOrJson);
        } else {
            setDeclaredName(nameOrJson);
        }
    }

    std::string Conjugation::serializeToJson() {
        nlohmann::json json = nlohmann::json::parse(Relationship::serializeToJson());
        json["originalType"] = Json::reference(unresolvedJsonReferences("originalType"), Conjugation::originalType());
        json["conjugatedType"] = Json::reference(unresolvedJsonReferences("conjugatedType"), Conjugation::conjugatedType());
        json["owningType"] = Json::reference(unresolvedJsonReferences("owningType"), Conjugation::owningType());
        return applyJsonSource(json.dump(JSON_INTENT));
    }

    void Conjugation::deserializeAndPopulate(const std::string& jsonString) {
        Relationship::deserializeAndPopulate(jsonString);
        const nlohmann::json json = nlohmann::json::parse(jsonString);
        std::vector<boost::uuids::uuid> ids;
        if (Json::readReferences(json, "originalType", ids))
            setUnresolvedJsonReferences("originalType", ids);
        if (Json::readReferences(json, "conjugatedType", ids))
            setUnresolvedJsonReferences("conjugatedType", ids);
        if (Json::readReferences(json, "owningType", ids))
            setUnresolvedJsonReferences("owningType", ids);
    }

    void Conjugation::resolveJsonReferences(const std::function<std::shared_ptr<Element>(const boost::uuids::uuid&)>& lookup) {
        Relationship::resolveJsonReferences(lookup);
        if (const auto ids = unresolvedJsonReferences("originalType")) {
            try {
                if (auto target = std::dynamic_pointer_cast<KerML::Entities::Type>(lookup(ids->front()))) {
                    Conjugation::setOrginalType(std::move(target));
                    clearUnresolvedJsonReferences("originalType");
                }
            } catch (const std::exception&) {
                // The reference stays unresolved if the model refuses it.
                setUnresolvedJsonReferences("originalType", *ids);
            }
        }
        if (const auto ids = unresolvedJsonReferences("conjugatedType")) {
            try {
                if (auto target = std::dynamic_pointer_cast<KerML::Entities::Type>(lookup(ids->front()))) {
                    Conjugation::setConjungatedType(std::move(target));
                    clearUnresolvedJsonReferences("conjugatedType");
                }
            } catch (const std::exception&) {
                // The reference stays unresolved if the model refuses it.
                setUnresolvedJsonReferences("conjugatedType", *ids);
            }
        }
        if (const auto ids = unresolvedJsonReferences("owningType")) {
            try {
                if (auto target = std::dynamic_pointer_cast<KerML::Entities::Type>(lookup(ids->front()))) {
                    Conjugation::setOwningType(std::move(target));
                    clearUnresolvedJsonReferences("owningType");
                }
            } catch (const std::exception&) {
                // The reference stays unresolved if the model refuses it.
                setUnresolvedJsonReferences("owningType", *ids);
            }
        }
    }
}
// END GENERATED JSON
