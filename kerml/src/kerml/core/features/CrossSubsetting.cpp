#include <kerml/core/features/CrossSubsetting.h>

#include <stdexcept>
#include <kerml/KerML.h>
#include <nlohmann/json.hpp>
#include "../../model/JsonSupport.h"


namespace KerML::Entities {
    CrossSubsetting::CrossSubsetting(std::shared_ptr<Feature> crossedFeature, std::shared_ptr<Feature> crossingFeature)
    : Subsetting(crossedFeature, crossingFeature) {
        _dType = "CrossSubsetting";

        if(crossedFeature == nullptr)
            throw std::invalid_argument("Crossed feature is not allowed to be null");
        CrossedFeature = crossedFeature;

        if(crossingFeature == nullptr)
            throw std::invalid_argument("Crossing feature is not allowed to be null");
        CrossingFeature = crossingFeature;
    }

    void CrossSubsetting::setCrossedFeature(std::shared_ptr<Feature> crossedFeature) {
        clearUnresolvedJsonReferences("crossedFeature");
        if(crossedFeature == nullptr)
            throw std::invalid_argument("Crossed feature is not allowed to be null");
        CrossedFeature = crossedFeature;
    }

    std::shared_ptr<Feature> CrossSubsetting::crossedFeature() {
        return CrossedFeature;
    }

    void CrossSubsetting::setCrossingFeature(std::shared_ptr<Feature> crossingFeautre) {
        clearUnresolvedJsonReferences("crossingFeature");
        if(crossingFeautre == nullptr)
            throw std::invalid_argument("Crossing feature is not allowed to be null");
        CrossingFeature = crossingFeautre;
    }

    std::shared_ptr<Feature> CrossSubsetting::crossingFeatures() {
        return CrossingFeature;
    }
}

// BEGIN GENERATED JSON (kerml/tools/generate_json.py): do not edit, run the script instead.
namespace KerML::Entities {
    CrossSubsetting::CrossSubsetting(const std::string& nameOrJson) :
        Subsetting(JsonTag{}) {
        _dType = "CrossSubsetting";
        if (Json::looksLikeJson(nameOrJson)) {
            deserializeAndPopulate(nameOrJson);
            captureJsonSource(nameOrJson);
        } else {
            setDeclaredName(nameOrJson);
        }
    }

    std::string CrossSubsetting::serializeToJson() {
        nlohmann::json json = nlohmann::json::parse(Subsetting::serializeToJson());
        json["crossedFeature"] = Json::reference(unresolvedJsonReferences("crossedFeature"), CrossSubsetting::crossedFeature());
        json["crossingFeature"] = Json::reference(unresolvedJsonReferences("crossingFeature"), CrossSubsetting::crossingFeature());
        return applyJsonSource(json.dump(JSON_INTENT));
    }

    void CrossSubsetting::deserializeAndPopulate(const std::string& jsonString) {
        Subsetting::deserializeAndPopulate(jsonString);
        const nlohmann::json json = nlohmann::json::parse(jsonString);
        std::vector<boost::uuids::uuid> ids;
        if (Json::readReferences(json, "crossedFeature", ids))
            setUnresolvedJsonReferences("crossedFeature", ids);
        if (Json::readReferences(json, "crossingFeature", ids))
            setUnresolvedJsonReferences("crossingFeature", ids);
    }

    void CrossSubsetting::resolveJsonReferences(const std::function<std::shared_ptr<Element>(const boost::uuids::uuid&)>& lookup) {
        Subsetting::resolveJsonReferences(lookup);
        if (const auto ids = unresolvedJsonReferences("crossedFeature")) {
            try {
                if (auto target = std::dynamic_pointer_cast<KerML::Entities::Feature>(lookup(ids->front()))) {
                    CrossSubsetting::setCrossedFeature(std::move(target));
                    clearUnresolvedJsonReferences("crossedFeature");
                }
            } catch (const std::exception&) {
                // The reference stays unresolved if the model refuses it.
                setUnresolvedJsonReferences("crossedFeature", *ids);
            }
        }
        if (const auto ids = unresolvedJsonReferences("crossingFeature")) {
            try {
                if (auto target = std::dynamic_pointer_cast<KerML::Entities::Feature>(lookup(ids->front()))) {
                    CrossSubsetting::setCrossingFeature(std::move(target));
                    clearUnresolvedJsonReferences("crossingFeature");
                }
            } catch (const std::exception&) {
                // The reference stays unresolved if the model refuses it.
                setUnresolvedJsonReferences("crossingFeature", *ids);
            }
        }
    }
}
// END GENERATED JSON
