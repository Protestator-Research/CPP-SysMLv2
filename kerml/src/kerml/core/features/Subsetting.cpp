//
// Created by Moritz Herzog on 25.03.25.
//

#include <kerml/core/features/Subsetting.h>

#include <kerml/core/features/Feature.h>
#include <exception>
#include <kerml/KerML.h>
#include <nlohmann/json.hpp>
#include "../../model/JsonSupport.h"

namespace KerML::Entities
{
	Subsetting::Subsetting(std::shared_ptr<Feature> subsettedFeature, std::shared_ptr<Feature> subsettingFeature) :
	Specialization(subsettedFeature, subsettingFeature)
	{
		_dType = "Subsetting";

		if (subsettedFeature == nullptr)
			throw std::invalid_argument("The subsetted feature is not allowed to be null. This is defined by the standard.");
		SubsettedFeature = subsettedFeature;

		if (subsettingFeature == nullptr)
			throw std::invalid_argument("The subsetting feature is not allowed to be null. This is defined by the standard.");
		SubsettingFeature = subsettingFeature;

	}

	Subsetting::Subsetting(JsonTag) : Specialization()
	{
		_dType = "Subsetting";
	}

	std::shared_ptr<Feature> Subsetting::subsettedFeature() const
	{
		return SubsettedFeature;
	}

	void Subsetting::setSubsettedFeature(std::shared_ptr<Feature> subsettedFeature)
	{
		clearUnresolvedJsonReferences("subsettedFeature");
		if (subsettedFeature == nullptr)
			throw std::invalid_argument("The subsetted feature is not allowed to be null. This is defined by the standard.");
		SubsettedFeature = subsettedFeature;

	}

	std::shared_ptr<Feature> Subsetting::subsettingFeature() const
	{
		return SubsettingFeature;
	}

	void Subsetting::setSubsettingFeature(std::shared_ptr<Feature> subsettingFeature)
	{
		clearUnresolvedJsonReferences("subsettingFeature");
		if (subsettingFeature == nullptr)
			throw std::invalid_argument("The subsetting feature is not allowed to be null. This is defined by the standard.");
		SubsettingFeature = subsettingFeature;

	}

	std::shared_ptr<Feature> Subsetting::owningFeature() const
	{
		return OwningFeature;
	}

	void Subsetting::setOwningFeature(std::shared_ptr<Feature> owningFeature)
	{
		clearUnresolvedJsonReferences("owningFeature");
		OwningFeature = owningFeature;
	}
}

// BEGIN GENERATED JSON (kerml/tools/generate_json.py): do not edit, run the script instead.
namespace KerML::Entities {
    Subsetting::Subsetting(const std::string& nameOrJson) {
        _dType = "Subsetting";
        if (Json::looksLikeJson(nameOrJson)) {
            deserializeAndPopulate(nameOrJson);
            captureJsonSource(nameOrJson);
        } else {
            setDeclaredName(nameOrJson);
        }
    }

    std::string Subsetting::serializeToJson() {
        nlohmann::json json = nlohmann::json::parse(Specialization::serializeToJson());
        json["subsettedFeature"] = Json::reference(unresolvedJsonReferences("subsettedFeature"), Subsetting::subsettedFeature());
        json["subsettingFeature"] = Json::reference(unresolvedJsonReferences("subsettingFeature"), Subsetting::subsettingFeature());
        json["owningFeature"] = Json::reference(unresolvedJsonReferences("owningFeature"), Subsetting::owningFeature());
        return applyJsonSource(json.dump(JSON_INTENT));
    }

    void Subsetting::deserializeAndPopulate(const std::string& jsonString) {
        Specialization::deserializeAndPopulate(jsonString);
        const nlohmann::json json = nlohmann::json::parse(jsonString);
        std::vector<boost::uuids::uuid> ids;
        if (Json::readReferences(json, "subsettedFeature", ids))
            setUnresolvedJsonReferences("subsettedFeature", ids);
        if (Json::readReferences(json, "subsettingFeature", ids))
            setUnresolvedJsonReferences("subsettingFeature", ids);
        if (Json::readReferences(json, "owningFeature", ids))
            setUnresolvedJsonReferences("owningFeature", ids);
    }

    void Subsetting::resolveJsonReferences(const std::function<std::shared_ptr<Element>(const boost::uuids::uuid&)>& lookup) {
        Specialization::resolveJsonReferences(lookup);
        if (const auto ids = unresolvedJsonReferences("subsettedFeature")) {
            try {
                if (auto target = std::dynamic_pointer_cast<KerML::Entities::Feature>(lookup(ids->front()))) {
                    Subsetting::setSubsettedFeature(std::move(target));
                    clearUnresolvedJsonReferences("subsettedFeature");
                }
            } catch (const std::exception&) {
                // The reference stays unresolved if the model refuses it.
                setUnresolvedJsonReferences("subsettedFeature", *ids);
            }
        }
        if (const auto ids = unresolvedJsonReferences("subsettingFeature")) {
            try {
                if (auto target = std::dynamic_pointer_cast<KerML::Entities::Feature>(lookup(ids->front()))) {
                    Subsetting::setSubsettingFeature(std::move(target));
                    clearUnresolvedJsonReferences("subsettingFeature");
                }
            } catch (const std::exception&) {
                // The reference stays unresolved if the model refuses it.
                setUnresolvedJsonReferences("subsettingFeature", *ids);
            }
        }
        if (const auto ids = unresolvedJsonReferences("owningFeature")) {
            try {
                if (auto target = std::dynamic_pointer_cast<KerML::Entities::Feature>(lookup(ids->front()))) {
                    Subsetting::setOwningFeature(std::move(target));
                    clearUnresolvedJsonReferences("owningFeature");
                }
            } catch (const std::exception&) {
                // The reference stays unresolved if the model refuses it.
                setUnresolvedJsonReferences("owningFeature", *ids);
            }
        }
    }
}
// END GENERATED JSON
