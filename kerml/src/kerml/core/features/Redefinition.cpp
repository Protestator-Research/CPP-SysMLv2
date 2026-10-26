//
// Created by Moritz Herzog on 25.03.25.
//

#include <kerml/core/features/Redefinition.h>
#include <kerml/KerML.h>
#include <nlohmann/json.hpp>
#include "../../model/JsonSupport.h"

namespace KerML::Entities
{
	Redefinition::Redefinition(std::shared_ptr<Feature> redefinedFeature, std::shared_ptr<Feature> redefiningFeature) :
	Subsetting(redefinedFeature,redefiningFeature)
	{
		_dType = "Redefinition";
		if (redefinedFeature == nullptr)
			throw std::invalid_argument("The redefined Feature is not allowed to be null. This is accroding to the Standard");
		RedefinedFeature = redefinedFeature;

		if (redefiningFeature == nullptr)
			throw std::invalid_argument("The redefining Feature is not allowed to be null. This is according to the Standard.");
		RedefiningFeature = redefiningFeature;
	}

	std::shared_ptr<Feature> Redefinition::redefinedFeature() const
	{
		return RedefinedFeature;
	}

	void Redefinition::setRedefinedFeature(std::shared_ptr<Feature> redefinedFeature)
	{
		clearUnresolvedJsonReferences("redefinedFeature");
		if (redefinedFeature == nullptr)
			throw std::invalid_argument("The redefined Feature is not allowed to be null. This is accroding to the Standard");
		RedefinedFeature = redefinedFeature;
	}

	std::shared_ptr<Feature> Redefinition::redefiningFeature() const
	{
		return RedefiningFeature;
	}

	void Redefinition::setRedefiningFeature(std::shared_ptr<Feature> redefiningFeature)
	{
		clearUnresolvedJsonReferences("redefiningFeature");
		if (redefiningFeature == nullptr)
			throw std::invalid_argument("The redefining Feature is not allowed to be null. This is according to the Standard.");
		RedefiningFeature = redefiningFeature;
	}
}

// BEGIN GENERATED JSON (kerml/tools/generate_json.py): do not edit, run the script instead.
namespace KerML::Entities {
    Redefinition::Redefinition(const std::string& nameOrJson) :
        Subsetting(JsonTag{}) {
        _dType = "Redefinition";
        if (Json::looksLikeJson(nameOrJson)) {
            deserializeAndPopulate(nameOrJson);
            captureJsonSource(nameOrJson);
        } else {
            setDeclaredName(nameOrJson);
        }
    }

    std::string Redefinition::serializeToJson() {
        nlohmann::json json = nlohmann::json::parse(Subsetting::serializeToJson());
        json["redefiningFeature"] = Json::reference(unresolvedJsonReferences("redefiningFeature"), Redefinition::redefiningFeature());
        json["redefinedFeature"] = Json::reference(unresolvedJsonReferences("redefinedFeature"), Redefinition::redefinedFeature());
        return applyJsonSource(json.dump(JSON_INTENT));
    }

    void Redefinition::deserializeAndPopulate(const std::string& jsonString) {
        Subsetting::deserializeAndPopulate(jsonString);
        const nlohmann::json json = nlohmann::json::parse(jsonString);
        std::vector<boost::uuids::uuid> ids;
        if (Json::readReferences(json, "redefiningFeature", ids))
            setUnresolvedJsonReferences("redefiningFeature", ids);
        if (Json::readReferences(json, "redefinedFeature", ids))
            setUnresolvedJsonReferences("redefinedFeature", ids);
    }

    void Redefinition::resolveJsonReferences(const std::function<std::shared_ptr<Element>(const boost::uuids::uuid&)>& lookup) {
        Subsetting::resolveJsonReferences(lookup);
        if (const auto ids = unresolvedJsonReferences("redefiningFeature")) {
            try {
                if (auto target = std::dynamic_pointer_cast<KerML::Entities::Feature>(lookup(ids->front()))) {
                    Redefinition::setRedefiningFeature(std::move(target));
                    clearUnresolvedJsonReferences("redefiningFeature");
                }
            } catch (const std::exception&) {
                // The reference stays unresolved if the model refuses it.
                setUnresolvedJsonReferences("redefiningFeature", *ids);
            }
        }
        if (const auto ids = unresolvedJsonReferences("redefinedFeature")) {
            try {
                if (auto target = std::dynamic_pointer_cast<KerML::Entities::Feature>(lookup(ids->front()))) {
                    Redefinition::setRedefinedFeature(std::move(target));
                    clearUnresolvedJsonReferences("redefinedFeature");
                }
            } catch (const std::exception&) {
                // The reference stays unresolved if the model refuses it.
                setUnresolvedJsonReferences("redefinedFeature", *ids);
            }
        }
    }
}
// END GENERATED JSON
