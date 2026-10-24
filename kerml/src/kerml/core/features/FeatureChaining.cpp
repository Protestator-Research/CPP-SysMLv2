//
// Created by Moritz Herzog on 25.03.25.
//

#include <kerml/core/features/FeatureChaining.h>

#include <kerml/core/features/Feature.h>
#include <kerml/KerML.h>
#include <nlohmann/json.hpp>
#include "../../model/JsonSupport.h"

namespace KerML::Entities {

    FeatureChaining::FeatureChaining(std::shared_ptr<Feature> chainingFeature, std::shared_ptr<Feature> featureChained,
                                     boost::uuids::uuid elementID, std::shared_ptr<Element> owner)
                                     : Element(elementID, owner), Relationship(elementID,owner){
        _dType = "FeatureChaining";

        ChainingFeature = chainingFeature;
        FeatureChained = featureChained;
    }

    void FeatureChaining::setChainingFeature(std::shared_ptr<Feature> chainingFeature) {
        clearUnresolvedJsonReferences("chainingFeature");
        ChainingFeature = chainingFeature;
    }

    std::shared_ptr<Feature> FeatureChaining::chainingFeature() const {
        return ChainingFeature;
    }

    void FeatureChaining::setFeatureChained(std::shared_ptr<Feature> featureChained) {
        clearUnresolvedJsonReferences("featureChained");
        FeatureChained = featureChained;
    }

    std::shared_ptr<Feature> FeatureChaining::featureChained() const {
        return FeatureChained;
    }
}

// BEGIN GENERATED JSON (kerml/tools/generate_json.py): do not edit, run the script instead.
namespace KerML::Entities {
    FeatureChaining::FeatureChaining(const std::string& nameOrJson) {
        _dType = "FeatureChaining";
        if (Json::looksLikeJson(nameOrJson)) {
            deserializeAndPopulate(nameOrJson);
            captureJsonSource(nameOrJson);
        } else {
            setDeclaredName(nameOrJson);
        }
    }

    std::string FeatureChaining::serializeToJson() {
        nlohmann::json json = nlohmann::json::parse(Relationship::serializeToJson());
        json["chainingFeature"] = Json::reference(unresolvedJsonReferences("chainingFeature"), FeatureChaining::chainingFeature());
        json["featureChained"] = Json::reference(unresolvedJsonReferences("featureChained"), FeatureChaining::featureChained());
        return applyJsonSource(json.dump(JSON_INTENT));
    }

    void FeatureChaining::deserializeAndPopulate(const std::string& jsonString) {
        Relationship::deserializeAndPopulate(jsonString);
        const nlohmann::json json = nlohmann::json::parse(jsonString);
        std::vector<boost::uuids::uuid> ids;
        if (Json::readReferences(json, "chainingFeature", ids))
            setUnresolvedJsonReferences("chainingFeature", ids);
        if (Json::readReferences(json, "featureChained", ids))
            setUnresolvedJsonReferences("featureChained", ids);
    }

    void FeatureChaining::resolveJsonReferences(const std::function<std::shared_ptr<Element>(const boost::uuids::uuid&)>& lookup) {
        Relationship::resolveJsonReferences(lookup);
        if (const auto ids = unresolvedJsonReferences("chainingFeature")) {
            try {
                if (auto target = std::dynamic_pointer_cast<KerML::Entities::Feature>(lookup(ids->front()))) {
                    FeatureChaining::setChainingFeature(std::move(target));
                    clearUnresolvedJsonReferences("chainingFeature");
                }
            } catch (const std::exception&) {
                // The reference stays unresolved if the model refuses it.
                setUnresolvedJsonReferences("chainingFeature", *ids);
            }
        }
        if (const auto ids = unresolvedJsonReferences("featureChained")) {
            try {
                if (auto target = std::dynamic_pointer_cast<KerML::Entities::Feature>(lookup(ids->front()))) {
                    FeatureChaining::setFeatureChained(std::move(target));
                    clearUnresolvedJsonReferences("featureChained");
                }
            } catch (const std::exception&) {
                // The reference stays unresolved if the model refuses it.
                setUnresolvedJsonReferences("featureChained", *ids);
            }
        }
    }
}
// END GENERATED JSON
