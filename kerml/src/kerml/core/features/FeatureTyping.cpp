//
// Created by Moritz Herzog on 25.03.25.
//

#include <kerml/core/features/FeatureTyping.h>
#include <kerml/core/features/Feature.h>
#include <kerml/core/types/Type.h>
#include <kerml/KerML.h>
#include <nlohmann/json.hpp>
#include "../../model/JsonSupport.h"

namespace KerML::Entities
{
	FeatureTyping::FeatureTyping() : Specialization()
	{
		_dType = "FeatureTyping";
	}

	FeatureTyping::FeatureTyping(const std::shared_ptr<KerML::Entities::Type>& type,
		const std::shared_ptr<KerML::Entities::Feature>& typedFeature) : Specialization(type, typedFeature), TypedFeature(typedFeature), Type(type)
	{
		_dType = "FeatureTyping";
	}

	FeatureTyping::FeatureTyping(std::nullptr_t) : FeatureTyping(std::shared_ptr<KerML::Entities::Type>(), nullptr)
	{
	}

	std::shared_ptr<KerML::Entities::Feature> FeatureTyping::typedFeature()
	{
		return TypedFeature;
	}

	void FeatureTyping::setTypedFeature(const std::shared_ptr<KerML::Entities::Feature>& typedFeature)
	{
		clearUnresolvedJsonReferences("typedFeature");
		TypedFeature = typedFeature;
		Specialization::setSpecific(typedFeature);
	}

	std::shared_ptr<KerML::Entities::Type> FeatureTyping::type()
	{
		return Type;
	}

	void FeatureTyping::setType(const std::shared_ptr<KerML::Entities::Type>& type)
	{
		clearUnresolvedJsonReferences("type");
		Type = type;
		Specialization::setGeneral(type);
	}
}

// BEGIN GENERATED JSON (kerml/tools/generate_json.py): do not edit, run the script instead.
namespace KerML::Entities {
    FeatureTyping::FeatureTyping(const std::string& nameOrJson) :
        FeatureTyping() {
        _dType = "FeatureTyping";
        if (Json::looksLikeJson(nameOrJson)) {
            deserializeAndPopulate(nameOrJson);
            captureJsonSource(nameOrJson);
        } else {
            setDeclaredName(nameOrJson);
        }
    }

    std::string FeatureTyping::serializeToJson() {
        nlohmann::json json = nlohmann::json::parse(Specialization::serializeToJson());
        json["typedFeature"] = Json::reference(unresolvedJsonReferences("typedFeature"), FeatureTyping::typedFeature());
        json["type"] = Json::reference(unresolvedJsonReferences("type"), FeatureTyping::type());
        json["owningFeature"] = Json::reference(unresolvedJsonReferences("owningFeature"), FeatureTyping::owningFeature());
        return applyJsonSource(json.dump(JSON_INTENT));
    }

    void FeatureTyping::deserializeAndPopulate(const std::string& jsonString) {
        Specialization::deserializeAndPopulate(jsonString);
        const nlohmann::json json = nlohmann::json::parse(jsonString);
        std::vector<boost::uuids::uuid> ids;
        if (Json::readReferences(json, "typedFeature", ids))
            setUnresolvedJsonReferences("typedFeature", ids);
        if (Json::readReferences(json, "type", ids))
            setUnresolvedJsonReferences("type", ids);
        if (Json::readReferences(json, "owningFeature", ids))
            setUnresolvedJsonReferences("owningFeature", ids);
    }

    void FeatureTyping::resolveJsonReferences(const std::function<std::shared_ptr<Element>(const boost::uuids::uuid&)>& lookup) {
        Specialization::resolveJsonReferences(lookup);
        if (const auto ids = unresolvedJsonReferences("typedFeature")) {
            try {
                if (auto target = std::dynamic_pointer_cast<KerML::Entities::Feature>(lookup(ids->front()))) {
                    FeatureTyping::setTypedFeature(std::move(target));
                    clearUnresolvedJsonReferences("typedFeature");
                }
            } catch (const std::exception&) {
                // The reference stays unresolved if the model refuses it.
                setUnresolvedJsonReferences("typedFeature", *ids);
            }
        }
        if (const auto ids = unresolvedJsonReferences("type")) {
            try {
                if (auto target = std::dynamic_pointer_cast<KerML::Entities::Type>(lookup(ids->front()))) {
                    FeatureTyping::setType(std::move(target));
                    clearUnresolvedJsonReferences("type");
                }
            } catch (const std::exception&) {
                // The reference stays unresolved if the model refuses it.
                setUnresolvedJsonReferences("type", *ids);
            }
        }
        if (const auto ids = unresolvedJsonReferences("owningFeature")) {
            try {
                if (auto target = std::dynamic_pointer_cast<KerML::Entities::Feature>(lookup(ids->front()))) {
                    FeatureTyping::setOwningFeature(std::move(target));
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
