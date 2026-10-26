//
// Created by Moritz Herzog on 25.03.25.
//

#include <stdexcept>
#include <kerml/core/features/FeatureInverting.h>
#include <kerml/KerML.h>
#include <nlohmann/json.hpp>
#include "../../model/JsonSupport.h"

namespace KerML::Entities {

    FeatureInverting::FeatureInverting(std::shared_ptr<Feature> featureInverted, std::shared_ptr<Feature> invertingFeature, boost::uuids::uuid elementID, std::shared_ptr<Element> owner) :
            Element(elementID, owner), Relationship(elementID, owner)
    {
        _dType = "FeatureInverting";

        if(featureInverted == nullptr)
            throw std::invalid_argument("Feature inverted is not allowed to be null, according to the standard.");
        FeatureInverted = featureInverted;

        if(invertingFeature == nullptr)
            throw std::invalid_argument("Inverting feature is not allowed to be null, according to the standard.");
        InvertingFeature = invertingFeature;

    }

    void FeatureInverting::setFeatureInverted(std::shared_ptr<Feature> featureInverting) {
        clearUnresolvedJsonReferences("featureInverted");
        FeatureInverted = featureInverting;
    }

    std::shared_ptr<Feature> FeatureInverting::featureInverted() const {
        return FeatureInverted;
    }

    void FeatureInverting::setInvertingFeature(std::shared_ptr<Feature> invertingFeature) {
        clearUnresolvedJsonReferences("invertingFeature");
        InvertingFeature = invertingFeature;
    }

    std::shared_ptr<Feature> FeatureInverting::invertingFeature() const {
        return InvertingFeature;
    }

    void FeatureInverting::setOwningFeature(std::shared_ptr<Feature> owningFeature) {
        clearUnresolvedJsonReferences("owningFeature");
        OwningFeature = owningFeature;
    }

    std::shared_ptr<Feature> FeatureInverting::owningFeature() const {
        return OwningFeature;
    }


}

// BEGIN GENERATED JSON (kerml/tools/generate_json.py): do not edit, run the script instead.
namespace KerML::Entities {
    FeatureInverting::FeatureInverting(const std::string& nameOrJson) {
        _dType = "FeatureInverting";
        if (Json::looksLikeJson(nameOrJson)) {
            deserializeAndPopulate(nameOrJson);
            captureJsonSource(nameOrJson);
        } else {
            setDeclaredName(nameOrJson);
        }
    }

    std::string FeatureInverting::serializeToJson() {
        nlohmann::json json = nlohmann::json::parse(Relationship::serializeToJson());
        json["featureInverted"] = Json::reference(unresolvedJsonReferences("featureInverted"), FeatureInverting::featureInverted());
        json["invertingFeature"] = Json::reference(unresolvedJsonReferences("invertingFeature"), FeatureInverting::invertingFeature());
        json["owningFeature"] = Json::reference(unresolvedJsonReferences("owningFeature"), FeatureInverting::owningFeature());
        return applyJsonSource(json.dump(JSON_INTENT));
    }

    void FeatureInverting::deserializeAndPopulate(const std::string& jsonString) {
        Relationship::deserializeAndPopulate(jsonString);
        const nlohmann::json json = nlohmann::json::parse(jsonString);
        std::vector<boost::uuids::uuid> ids;
        if (Json::readReferences(json, "featureInverted", ids))
            setUnresolvedJsonReferences("featureInverted", ids);
        if (Json::readReferences(json, "invertingFeature", ids))
            setUnresolvedJsonReferences("invertingFeature", ids);
        if (Json::readReferences(json, "owningFeature", ids))
            setUnresolvedJsonReferences("owningFeature", ids);
    }

    void FeatureInverting::resolveJsonReferences(const std::function<std::shared_ptr<Element>(const boost::uuids::uuid&)>& lookup) {
        Relationship::resolveJsonReferences(lookup);
        if (const auto ids = unresolvedJsonReferences("featureInverted")) {
            try {
                if (auto target = std::dynamic_pointer_cast<KerML::Entities::Feature>(lookup(ids->front()))) {
                    FeatureInverting::setFeatureInverted(std::move(target));
                    clearUnresolvedJsonReferences("featureInverted");
                }
            } catch (const std::exception&) {
                // The reference stays unresolved if the model refuses it.
                setUnresolvedJsonReferences("featureInverted", *ids);
            }
        }
        if (const auto ids = unresolvedJsonReferences("invertingFeature")) {
            try {
                if (auto target = std::dynamic_pointer_cast<KerML::Entities::Feature>(lookup(ids->front()))) {
                    FeatureInverting::setInvertingFeature(std::move(target));
                    clearUnresolvedJsonReferences("invertingFeature");
                }
            } catch (const std::exception&) {
                // The reference stays unresolved if the model refuses it.
                setUnresolvedJsonReferences("invertingFeature", *ids);
            }
        }
        if (const auto ids = unresolvedJsonReferences("owningFeature")) {
            try {
                if (auto target = std::dynamic_pointer_cast<KerML::Entities::Feature>(lookup(ids->front()))) {
                    FeatureInverting::setOwningFeature(std::move(target));
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
