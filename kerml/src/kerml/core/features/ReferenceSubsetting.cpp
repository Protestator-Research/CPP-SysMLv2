//
// Created by Moritz Herzog on 25.03.25.
//

#include <kerml/core/features/ReferenceSubsetting.h>
#include <kerml/KerML.h>
#include <nlohmann/json.hpp>
#include "../../model/JsonSupport.h"

namespace KerML::Entities
{
	ReferenceSubsetting::ReferenceSubsetting(std::shared_ptr<Feature> referencedFeature,
		std::shared_ptr<Feature> referencingFeature) :
	Subsetting(referencedFeature,referencingFeature)
	{
		_dType = "ReferenceSubsetting";
		if (referencedFeature == nullptr)
			throw std::invalid_argument("Referenced Feature is not allowed to be null. This is declared in the standard");
		ReferencedFeature = referencedFeature;

		if (referencingFeature == nullptr)
			throw std::invalid_argument("Referencing Feature to be null is not allowed, according to the standard.");
		ReferencingFeature = referencingFeature;

	}

	std::shared_ptr<Feature> ReferenceSubsetting::referencedFeature() const
	{
		return ReferencedFeature;
	}

	void ReferenceSubsetting::setReferencedFeature(std::shared_ptr<Feature> referencedFeature)
	{
		clearUnresolvedJsonReferences("referencedFeature");
		if (referencedFeature == nullptr)
			throw std::invalid_argument("Referenced Feature is not allowed to be null. This is declared in the standard");
		ReferencedFeature = referencedFeature;
	}

	std::shared_ptr<Feature> ReferenceSubsetting::referencingFeature() const
	{
		return ReferencingFeature;
	}

	void ReferenceSubsetting::setReferencingFeature(std::shared_ptr<Feature> referencingFeature)
	{
		clearUnresolvedJsonReferences("referencingFeature");
		if (referencingFeature == nullptr)
			throw std::invalid_argument("Referencing Feature to be null is not allowed, according to the standard.");
		ReferencingFeature = referencingFeature;
	}
}

// BEGIN GENERATED JSON (kerml/tools/generate_json.py): do not edit, run the script instead.
namespace KerML::Entities {
    ReferenceSubsetting::ReferenceSubsetting(const std::string& nameOrJson) :
        Subsetting(JsonTag{}) {
        _dType = "ReferenceSubsetting";
        if (Json::looksLikeJson(nameOrJson)) {
            deserializeAndPopulate(nameOrJson);
            captureJsonSource(nameOrJson);
        } else {
            setDeclaredName(nameOrJson);
        }
    }

    std::string ReferenceSubsetting::serializeToJson() {
        nlohmann::json json = nlohmann::json::parse(Subsetting::serializeToJson());
        json["referencedFeature"] = Json::reference(unresolvedJsonReferences("referencedFeature"), ReferenceSubsetting::referencedFeature());
        json["referencingFeature"] = Json::reference(unresolvedJsonReferences("referencingFeature"), ReferenceSubsetting::referencingFeature());
        return applyJsonSource(json.dump(JSON_INTENT));
    }

    void ReferenceSubsetting::deserializeAndPopulate(const std::string& jsonString) {
        Subsetting::deserializeAndPopulate(jsonString);
        const nlohmann::json json = nlohmann::json::parse(jsonString);
        std::vector<boost::uuids::uuid> ids;
        if (Json::readReferences(json, "referencedFeature", ids))
            setUnresolvedJsonReferences("referencedFeature", ids);
        if (Json::readReferences(json, "referencingFeature", ids))
            setUnresolvedJsonReferences("referencingFeature", ids);
    }

    void ReferenceSubsetting::resolveJsonReferences(const std::function<std::shared_ptr<Element>(const boost::uuids::uuid&)>& lookup) {
        Subsetting::resolveJsonReferences(lookup);
        if (const auto ids = unresolvedJsonReferences("referencedFeature")) {
            try {
                if (auto target = std::dynamic_pointer_cast<KerML::Entities::Feature>(lookup(ids->front()))) {
                    ReferenceSubsetting::setReferencedFeature(std::move(target));
                    clearUnresolvedJsonReferences("referencedFeature");
                }
            } catch (const std::exception&) {
                // The reference stays unresolved if the model refuses it.
                setUnresolvedJsonReferences("referencedFeature", *ids);
            }
        }
        if (const auto ids = unresolvedJsonReferences("referencingFeature")) {
            try {
                if (auto target = std::dynamic_pointer_cast<KerML::Entities::Feature>(lookup(ids->front()))) {
                    ReferenceSubsetting::setReferencingFeature(std::move(target));
                    clearUnresolvedJsonReferences("referencingFeature");
                }
            } catch (const std::exception&) {
                // The reference stays unresolved if the model refuses it.
                setUnresolvedJsonReferences("referencingFeature", *ids);
            }
        }
    }
}
// END GENERATED JSON
