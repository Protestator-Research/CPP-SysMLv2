//
// Created by Moritz Herzog on 25.03.25.
//

#include <kerml/core/features/EndFeatureMembership.h>
#include <kerml/KerML.h>
#include <nlohmann/json.hpp>
#include "../../model/JsonSupport.h"

namespace  KerML::Entities {

    EndFeatureMembership::EndFeatureMembership(std::shared_ptr<Feature> ownedMemberFeature,
                                               std::shared_ptr<Type> owningType,
                                               std::vector<std::shared_ptr<Type>> type)
            : FeatureMembership(ownedMemberFeature, owningType, type) {
        _dType = "EndFeatureMembership";
    }

    bool EndFeatureMembership::isEnd() {
        return true;
    }
}

// BEGIN GENERATED JSON (kerml/tools/generate_json.py): do not edit, run the script instead.
namespace KerML::Entities {
    EndFeatureMembership::EndFeatureMembership(const std::string& nameOrJson) {
        _dType = "EndFeatureMembership";
        if (Json::looksLikeJson(nameOrJson)) {
            deserializeAndPopulate(nameOrJson);
            captureJsonSource(nameOrJson);
        } else {
            setDeclaredName(nameOrJson);
        }
    }

    std::string EndFeatureMembership::serializeToJson() {
        nlohmann::json json = nlohmann::json::parse(FeatureMembership::serializeToJson());
        json["ownedMemberFeature"] = Json::reference(unresolvedJsonReferences("ownedMemberFeature"), FeatureMembership::ownedMemberFeature());
        return applyJsonSource(json.dump(JSON_INTENT));
    }

    void EndFeatureMembership::deserializeAndPopulate(const std::string& jsonString) {
        FeatureMembership::deserializeAndPopulate(jsonString);
        const nlohmann::json json = nlohmann::json::parse(jsonString);
        std::vector<boost::uuids::uuid> ids;
        if (Json::readReferences(json, "ownedMemberFeature", ids))
            setUnresolvedJsonReferences("ownedMemberFeature", ids);
    }

    void EndFeatureMembership::resolveJsonReferences(const std::function<std::shared_ptr<Element>(const boost::uuids::uuid&)>& lookup) {
        FeatureMembership::resolveJsonReferences(lookup);
        if (const auto ids = unresolvedJsonReferences("ownedMemberFeature")) {
            try {
                if (auto target = std::dynamic_pointer_cast<KerML::Entities::Feature>(lookup(ids->front()))) {
                    FeatureMembership::setOwnedMemberFeature(std::move(target));
                    clearUnresolvedJsonReferences("ownedMemberFeature");
                }
            } catch (const std::exception&) {
                // The reference stays unresolved if the model refuses it.
                setUnresolvedJsonReferences("ownedMemberFeature", *ids);
            }
        }
    }
}
// END GENERATED JSON
