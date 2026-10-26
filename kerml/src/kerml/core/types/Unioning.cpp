//
// Created by Moritz Herzog on 25.03.25.
//

#include <kerml/core/types/Unioning.h>
#include <stdexcept>
#include <kerml/KerML.h>
#include <nlohmann/json.hpp>
#include "../../model/JsonSupport.h"

namespace KerML::Entities
{
	Unioning::Unioning(std::shared_ptr<Type> typeUnioned, std::shared_ptr<Type> unioningType)
	{
		_dType = "Unioning";

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
		clearUnresolvedJsonReferences("typeUnioned");
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
		clearUnresolvedJsonReferences("unioningType");
		if (unioningType == nullptr)
			throw std::runtime_error("Unioning type is nott allowed to be null");
		UnioningType = unioningType;
	}
}

// BEGIN GENERATED JSON (kerml/tools/generate_json.py): do not edit, run the script instead.
namespace KerML::Entities {
    Unioning::Unioning(const std::string& nameOrJson) {
        _dType = "Unioning";
        if (Json::looksLikeJson(nameOrJson)) {
            deserializeAndPopulate(nameOrJson);
            captureJsonSource(nameOrJson);
        } else {
            setDeclaredName(nameOrJson);
        }
    }

    std::string Unioning::serializeToJson() {
        nlohmann::json json = nlohmann::json::parse(Relationship::serializeToJson());
        json["typeUnioned"] = Json::reference(unresolvedJsonReferences("typeUnioned"), Unioning::typeUnioned());
        json["unioningType"] = Json::reference(unresolvedJsonReferences("unioningType"), Unioning::unioningType());
        return applyJsonSource(json.dump(JSON_INTENT));
    }

    void Unioning::deserializeAndPopulate(const std::string& jsonString) {
        Relationship::deserializeAndPopulate(jsonString);
        const nlohmann::json json = nlohmann::json::parse(jsonString);
        std::vector<boost::uuids::uuid> ids;
        if (Json::readReferences(json, "typeUnioned", ids))
            setUnresolvedJsonReferences("typeUnioned", ids);
        if (Json::readReferences(json, "unioningType", ids))
            setUnresolvedJsonReferences("unioningType", ids);
    }

    void Unioning::resolveJsonReferences(const std::function<std::shared_ptr<Element>(const boost::uuids::uuid&)>& lookup) {
        Relationship::resolveJsonReferences(lookup);
        if (const auto ids = unresolvedJsonReferences("typeUnioned")) {
            try {
                if (auto target = std::dynamic_pointer_cast<KerML::Entities::Type>(lookup(ids->front()))) {
                    Unioning::setTypeUnioned(std::move(target));
                    clearUnresolvedJsonReferences("typeUnioned");
                }
            } catch (const std::exception&) {
                // The reference stays unresolved if the model refuses it.
                setUnresolvedJsonReferences("typeUnioned", *ids);
            }
        }
        if (const auto ids = unresolvedJsonReferences("unioningType")) {
            try {
                if (auto target = std::dynamic_pointer_cast<KerML::Entities::Type>(lookup(ids->front()))) {
                    Unioning::setUnioningType(std::move(target));
                    clearUnresolvedJsonReferences("unioningType");
                }
            } catch (const std::exception&) {
                // The reference stays unresolved if the model refuses it.
                setUnresolvedJsonReferences("unioningType", *ids);
            }
        }
    }
}
// END GENERATED JSON
