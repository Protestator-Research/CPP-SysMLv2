//
// Created by Moritz Herzog on 25.03.25.
//

#include <kerml/core/features/TypeFeaturing.h>
#include <kerml/core/features/Feature.h>
#include <kerml/core/types/Type.h>
#include <kerml/KerML.h>
#include <nlohmann/json.hpp>
#include "../../model/JsonSupport.h"

namespace KerML::Entities {
	TypeFeaturing::TypeFeaturing(const std::shared_ptr<Type>& typeFeaturingOfType,
		const std::shared_ptr<Feature>& featureOfType, const std::shared_ptr<Feature>& owningFeatureOfType) :
	Relationship(boost::uuids::random_generator()(), owningFeatureOfType)
	{
		_dType = "TypeFeaturing";
		OwningFeatureOfType = owningFeatureOfType;
		FeatureOfType = featureOfType;
		TypeFeaturingOfType = typeFeaturingOfType;
	}

	void TypeFeaturing::setFeaturingType(const std::shared_ptr<Type>& typeFeaturingOfType)
	{
		clearUnresolvedJsonReferences("featuringType");
		TypeFeaturingOfType = typeFeaturingOfType;
	}

	std::shared_ptr<Type> TypeFeaturing::featuringType() const
	{
		return TypeFeaturingOfType;
	}

	void TypeFeaturing::setFeatureOfType(const std::shared_ptr<Feature>& featureOfType)
	{
		clearUnresolvedJsonReferences("featureOfType");
		FeatureOfType = featureOfType;
	}

	std::shared_ptr<Feature> TypeFeaturing::featureOfType() const
	{
		return FeatureOfType;
	}

	void TypeFeaturing::setOwningFeatureOfType(const std::shared_ptr<Feature>& owningFeatureOfType)
	{
		clearUnresolvedJsonReferences("owningFeatureOfType");
		OwningFeatureOfType = owningFeatureOfType;
	}

	std::shared_ptr<Feature> TypeFeaturing::owningFeatureOfType()
	{
		return OwningFeatureOfType;
	}
}

// BEGIN GENERATED JSON (kerml/tools/generate_json.py): do not edit, run the script instead.
namespace KerML::Entities {
    TypeFeaturing::TypeFeaturing(const std::string& nameOrJson) {
        _dType = "TypeFeaturing";
        if (Json::looksLikeJson(nameOrJson)) {
            deserializeAndPopulate(nameOrJson);
            captureJsonSource(nameOrJson);
        } else {
            setDeclaredName(nameOrJson);
        }
    }

    std::string TypeFeaturing::serializeToJson() {
        nlohmann::json json = nlohmann::json::parse(Relationship::serializeToJson());
        json["featureOfType"] = Json::reference(unresolvedJsonReferences("featureOfType"), TypeFeaturing::featureOfType());
        json["featuringType"] = Json::reference(unresolvedJsonReferences("featuringType"), TypeFeaturing::featuringType());
        json["owningFeatureOfType"] = Json::reference(unresolvedJsonReferences("owningFeatureOfType"), TypeFeaturing::owningFeatureOfType());
        return applyJsonSource(json.dump(JSON_INTENT));
    }

    void TypeFeaturing::deserializeAndPopulate(const std::string& jsonString) {
        Relationship::deserializeAndPopulate(jsonString);
        const nlohmann::json json = nlohmann::json::parse(jsonString);
        std::vector<boost::uuids::uuid> ids;
        if (Json::readReferences(json, "featureOfType", ids))
            setUnresolvedJsonReferences("featureOfType", ids);
        if (Json::readReferences(json, "featuringType", ids))
            setUnresolvedJsonReferences("featuringType", ids);
        if (Json::readReferences(json, "owningFeatureOfType", ids))
            setUnresolvedJsonReferences("owningFeatureOfType", ids);
    }

    void TypeFeaturing::resolveJsonReferences(const std::function<std::shared_ptr<Element>(const boost::uuids::uuid&)>& lookup) {
        Relationship::resolveJsonReferences(lookup);
        if (const auto ids = unresolvedJsonReferences("featureOfType")) {
            try {
                if (auto target = std::dynamic_pointer_cast<KerML::Entities::Feature>(lookup(ids->front()))) {
                    TypeFeaturing::setFeatureOfType(std::move(target));
                    clearUnresolvedJsonReferences("featureOfType");
                }
            } catch (const std::exception&) {
                // The reference stays unresolved if the model refuses it.
                setUnresolvedJsonReferences("featureOfType", *ids);
            }
        }
        if (const auto ids = unresolvedJsonReferences("featuringType")) {
            try {
                if (auto target = std::dynamic_pointer_cast<KerML::Entities::Type>(lookup(ids->front()))) {
                    TypeFeaturing::setFeaturingType(std::move(target));
                    clearUnresolvedJsonReferences("featuringType");
                }
            } catch (const std::exception&) {
                // The reference stays unresolved if the model refuses it.
                setUnresolvedJsonReferences("featuringType", *ids);
            }
        }
        if (const auto ids = unresolvedJsonReferences("owningFeatureOfType")) {
            try {
                if (auto target = std::dynamic_pointer_cast<KerML::Entities::Feature>(lookup(ids->front()))) {
                    TypeFeaturing::setOwningFeatureOfType(std::move(target));
                    clearUnresolvedJsonReferences("owningFeatureOfType");
                }
            } catch (const std::exception&) {
                // The reference stays unresolved if the model refuses it.
                setUnresolvedJsonReferences("owningFeatureOfType", *ids);
            }
        }
    }
}
// END GENERATED JSON
