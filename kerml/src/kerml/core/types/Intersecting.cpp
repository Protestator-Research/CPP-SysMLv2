//
// Created by Moritz Herzog on 25.03.25.
//

#include <kerml/core/types/Intersecting.h>
#include <stdexcept>
#include <kerml/KerML.h>
#include <nlohmann/json.hpp>
#include "../../model/JsonSupport.h"

namespace KerML::Entities
{
	Intersecting::Intersecting(std::shared_ptr<Type> typeIntersecting, std::shared_ptr<Type> intersectingType)
	{
		_dType = "Intersecting";

		if (typeIntersecting == nullptr)
			throw std::runtime_error("Type intersecting is according to the standard not allowed to be null.");

		TypeIntersected = typeIntersecting;

		if (intersectingType == nullptr)
			throw std::runtime_error("Intersecting type is according to the standard not allowed to be null.");

		IntersectingType = intersectingType;
	}

	std::shared_ptr<Type> Intersecting::intersectingType()
	{
		return IntersectingType;
	}

	void Intersecting::setIntersectingType(std::shared_ptr<Type> intersectingType)
	{
		clearUnresolvedJsonReferences("intersectingType");
		if (intersectingType == nullptr)
			throw std::runtime_error("Intersecting type is according to the standard not allowed to be null.");
		IntersectingType = intersectingType;
	}

	std::shared_ptr<Type> Intersecting::typeIntersecting()
	{
		return TypeIntersected;
	}

	void Intersecting::setTypeIntersecting(std::shared_ptr<Type> typeIntersecting)
	{
		if (typeIntersecting == nullptr)
			throw std::runtime_error("Type intersecting is according to the standard not allowed to be null.");
		TypeIntersected = typeIntersecting;
	}
}

// BEGIN GENERATED JSON (kerml/tools/generate_json.py): do not edit, run the script instead.
namespace KerML::Entities {
    Intersecting::Intersecting(const std::string& nameOrJson) {
        _dType = "Intersecting";
        if (Json::looksLikeJson(nameOrJson)) {
            deserializeAndPopulate(nameOrJson);
            captureJsonSource(nameOrJson);
        } else {
            setDeclaredName(nameOrJson);
        }
    }

    std::string Intersecting::serializeToJson() {
        nlohmann::json json = nlohmann::json::parse(Relationship::serializeToJson());
        json["typeIntersected"] = Json::reference(unresolvedJsonReferences("typeIntersected"), Intersecting::typeIntersected());
        json["intersectingType"] = Json::reference(unresolvedJsonReferences("intersectingType"), Intersecting::intersectingType());
        return applyJsonSource(json.dump(JSON_INTENT));
    }

    void Intersecting::deserializeAndPopulate(const std::string& jsonString) {
        Relationship::deserializeAndPopulate(jsonString);
        const nlohmann::json json = nlohmann::json::parse(jsonString);
        std::vector<boost::uuids::uuid> ids;
        if (Json::readReferences(json, "intersectingType", ids))
            setUnresolvedJsonReferences("intersectingType", ids);
    }

    void Intersecting::resolveJsonReferences(const std::function<std::shared_ptr<Element>(const boost::uuids::uuid&)>& lookup) {
        Relationship::resolveJsonReferences(lookup);
        if (const auto ids = unresolvedJsonReferences("intersectingType")) {
            try {
                if (auto target = std::dynamic_pointer_cast<KerML::Entities::Type>(lookup(ids->front()))) {
                    Intersecting::setIntersectingType(std::move(target));
                    clearUnresolvedJsonReferences("intersectingType");
                }
            } catch (const std::exception&) {
                // The reference stays unresolved if the model refuses it.
                setUnresolvedJsonReferences("intersectingType", *ids);
            }
        }
    }
}
// END GENERATED JSON
