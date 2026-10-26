//
// Created by Moritz Herzog on 25.03.25.
//

#include <kerml/core/types/Disjoining.h>

#include <stdexcept>
#include <kerml/KerML.h>
#include <nlohmann/json.hpp>
#include "../../model/JsonSupport.h"

namespace KerML::Entities {
	Disjoining::Disjoining(std::shared_ptr<Type> typeDisjoined, std::shared_ptr<Type> disjoiningType) :
	Relationship()
	{
		_dType = "Disjoining";

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
		clearUnresolvedJsonReferences("typeDisjoined");
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
		clearUnresolvedJsonReferences("disjoiningType");
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
		clearUnresolvedJsonReferences("owningType");
		OwningType = owningType;
	}
}

// BEGIN GENERATED JSON (kerml/tools/generate_json.py): do not edit, run the script instead.
namespace KerML::Entities {
    Disjoining::Disjoining(const std::string& nameOrJson) {
        _dType = "Disjoining";
        if (Json::looksLikeJson(nameOrJson)) {
            deserializeAndPopulate(nameOrJson);
            captureJsonSource(nameOrJson);
        } else {
            setDeclaredName(nameOrJson);
        }
    }

    std::string Disjoining::serializeToJson() {
        nlohmann::json json = nlohmann::json::parse(Relationship::serializeToJson());
        json["typeDisjoined"] = Json::reference(unresolvedJsonReferences("typeDisjoined"), Disjoining::typeDisjoined());
        json["disjoiningType"] = Json::reference(unresolvedJsonReferences("disjoiningType"), Disjoining::disjoiningType());
        json["owningType"] = Json::reference(unresolvedJsonReferences("owningType"), Disjoining::owningType());
        return applyJsonSource(json.dump(JSON_INTENT));
    }

    void Disjoining::deserializeAndPopulate(const std::string& jsonString) {
        Relationship::deserializeAndPopulate(jsonString);
        const nlohmann::json json = nlohmann::json::parse(jsonString);
        std::vector<boost::uuids::uuid> ids;
        if (Json::readReferences(json, "typeDisjoined", ids))
            setUnresolvedJsonReferences("typeDisjoined", ids);
        if (Json::readReferences(json, "disjoiningType", ids))
            setUnresolvedJsonReferences("disjoiningType", ids);
        if (Json::readReferences(json, "owningType", ids))
            setUnresolvedJsonReferences("owningType", ids);
    }

    void Disjoining::resolveJsonReferences(const std::function<std::shared_ptr<Element>(const boost::uuids::uuid&)>& lookup) {
        Relationship::resolveJsonReferences(lookup);
        if (const auto ids = unresolvedJsonReferences("typeDisjoined")) {
            try {
                if (auto target = std::dynamic_pointer_cast<KerML::Entities::Type>(lookup(ids->front()))) {
                    Disjoining::setTypeDisjoined(std::move(target));
                    clearUnresolvedJsonReferences("typeDisjoined");
                }
            } catch (const std::exception&) {
                // The reference stays unresolved if the model refuses it.
                setUnresolvedJsonReferences("typeDisjoined", *ids);
            }
        }
        if (const auto ids = unresolvedJsonReferences("disjoiningType")) {
            try {
                if (auto target = std::dynamic_pointer_cast<KerML::Entities::Type>(lookup(ids->front()))) {
                    Disjoining::setDisjoiningType(std::move(target));
                    clearUnresolvedJsonReferences("disjoiningType");
                }
            } catch (const std::exception&) {
                // The reference stays unresolved if the model refuses it.
                setUnresolvedJsonReferences("disjoiningType", *ids);
            }
        }
        if (const auto ids = unresolvedJsonReferences("owningType")) {
            try {
                if (auto target = std::dynamic_pointer_cast<KerML::Entities::Type>(lookup(ids->front()))) {
                    Disjoining::setOwningType(std::move(target));
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
