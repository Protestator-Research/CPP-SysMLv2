//
// Created by Moritz Herzog on 25.03.25.
//

#include <kerml/core/types/Differencing.h>
#include <stdexcept>
#include <kerml/KerML.h>
#include <nlohmann/json.hpp>
#include "../../model/JsonSupport.h"

namespace KerML::Entities
{
	Differencing::Differencing(std::shared_ptr<Type> typeDifferenced, std::shared_ptr<Type> differencingType)
	{
		_dType = "Differencing";

		if (typeDifferenced == nullptr)
			std::runtime_error("Type Differenced is not allowed to be null");


		TypeDifferenced = typeDifferenced;

		if (differencingType == nullptr)
			std::runtime_error("Differencing type is not allwed to be null");

		DifferencingType = differencingType;
	}

	std::shared_ptr<Type> Differencing::differencingType()
	{
		return DifferencingType;
	}

	void Differencing::setDifferencingType(std::shared_ptr<Type> differencingType)
	{
		clearUnresolvedJsonReferences("differencingType");
		if (differencingType == nullptr)
			std::runtime_error("Differencing type is not allwed to be null");

		DifferencingType = differencingType;
	}

	std::shared_ptr<Type> Differencing::typeDifferenced()
	{
		return TypeDifferenced;
	}

	void Differencing::setTypeDifferenced(std::shared_ptr<Type> typeDifferenced)
	{
		clearUnresolvedJsonReferences("typeDifferenced");
		if (typeDifferenced == nullptr)
			std::runtime_error("Type differenced is not allwed to be null");

		TypeDifferenced = typeDifferenced;
	}
}

// BEGIN GENERATED JSON (kerml/tools/generate_json.py): do not edit, run the script instead.
namespace KerML::Entities {
    Differencing::Differencing(const std::string& nameOrJson) {
        _dType = "Differencing";
        if (Json::looksLikeJson(nameOrJson)) {
            deserializeAndPopulate(nameOrJson);
            captureJsonSource(nameOrJson);
        } else {
            setDeclaredName(nameOrJson);
        }
    }

    std::string Differencing::serializeToJson() {
        nlohmann::json json = nlohmann::json::parse(Relationship::serializeToJson());
        json["typeDifferenced"] = Json::reference(unresolvedJsonReferences("typeDifferenced"), Differencing::typeDifferenced());
        json["differencingType"] = Json::reference(unresolvedJsonReferences("differencingType"), Differencing::differencingType());
        return applyJsonSource(json.dump(JSON_INTENT));
    }

    void Differencing::deserializeAndPopulate(const std::string& jsonString) {
        Relationship::deserializeAndPopulate(jsonString);
        const nlohmann::json json = nlohmann::json::parse(jsonString);
        std::vector<boost::uuids::uuid> ids;
        if (Json::readReferences(json, "typeDifferenced", ids))
            setUnresolvedJsonReferences("typeDifferenced", ids);
        if (Json::readReferences(json, "differencingType", ids))
            setUnresolvedJsonReferences("differencingType", ids);
    }

    void Differencing::resolveJsonReferences(const std::function<std::shared_ptr<Element>(const boost::uuids::uuid&)>& lookup) {
        Relationship::resolveJsonReferences(lookup);
        if (const auto ids = unresolvedJsonReferences("typeDifferenced")) {
            try {
                if (auto target = std::dynamic_pointer_cast<KerML::Entities::Type>(lookup(ids->front()))) {
                    Differencing::setTypeDifferenced(std::move(target));
                    clearUnresolvedJsonReferences("typeDifferenced");
                }
            } catch (const std::exception&) {
                // The reference stays unresolved if the model refuses it.
                setUnresolvedJsonReferences("typeDifferenced", *ids);
            }
        }
        if (const auto ids = unresolvedJsonReferences("differencingType")) {
            try {
                if (auto target = std::dynamic_pointer_cast<KerML::Entities::Type>(lookup(ids->front()))) {
                    Differencing::setDifferencingType(std::move(target));
                    clearUnresolvedJsonReferences("differencingType");
                }
            } catch (const std::exception&) {
                // The reference stays unresolved if the model refuses it.
                setUnresolvedJsonReferences("differencingType", *ids);
            }
        }
    }
}
// END GENERATED JSON
