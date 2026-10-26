//
// Created by Moritz Herzog on 24.03.25.
//

#include <kerml/root/elements/Relationship.h>
#include <stdexcept>
#include <functional>
#include <algorithm>
#include <kerml/KerML.h>
#include <nlohmann/json.hpp>
#include "../../model/JsonSupport.h"

namespace KerML::Entities {
    Relationship::Relationship(boost::uuids::uuid elementID, std::shared_ptr<Element> owner) : Element(elementID, owner) {
        _dType = "Relationship";
    }

    Relationship::Relationship(std::string elementID, std::shared_ptr<Element> owner) : Element(Json::elementIdOf(elementID), owner) {
        _dType = "Relationship";
        if (Json::looksLikeJson(elementID)) {
            deserializeAndPopulate(elementID);
            captureJsonSource(elementID);
        }
    }

    void Relationship::setIsImplied(bool isImplied) {
        IsImplied = isImplied;
    }

    bool Relationship::isImplied() {
        return IsImplied;
    }

    void Relationship::appendElementToOwnedRelatedElement(std::shared_ptr<Element> element) {
        OwnedRelatedElements.push_back(element);
        sortOwnedRelatedElements();
    }

    std::shared_ptr<Namespace> Relationship::libraryNamespace() const {
        return Element::libraryNamespace();
    }

    void Relationship::setOwnedRelatedElements(std::vector<std::shared_ptr<Element>> elements) {
        clearUnresolvedJsonReferences("ownedRelatedElement");
        OwnedRelatedElements = elements;
        sortOwnedRelatedElements();
    }

    std::vector<std::shared_ptr<Element>> Relationship::ownedRelatedElement() const {
        return OwnedRelatedElements;
    }

    void Relationship::setOwningRelatedElement(std::shared_ptr<Element> owningRelatedElement) {
        clearUnresolvedJsonReferences("owningRelatedElement");
        OwningRelatedElement = owningRelatedElement;
    }

    std::shared_ptr<Element> Relationship::owningRelatedElement() const {
        return OwningRelatedElement;
    }

    void Relationship::sortOwnedRelatedElements() {
        // Preserve the order supplied by the model.
    }

    void Relationship::sortRelatedElements() {
        // Preserve the order supplied by the model.
    }

    void Relationship::sortSourceElements() {
        // Preserve the order supplied by the model.
    }

    void Relationship::sortTargetElements() {
        // Preserve the order supplied by the model.
    }

    void Relationship::setRelatedElements(std::vector<std::shared_ptr<Element>> relatedElements) {
        RelatedElements = std::move(relatedElements);
        sortRelatedElements();
    }

    std::vector<std::shared_ptr<Element>> Relationship::relatedElements() const {
        return RelatedElements;
    }

    void Relationship::appendElementToRelatedElements(std::shared_ptr<Element> element) {
        RelatedElements.push_back(element);
        sortRelatedElements();
    }
} // KerML::Entities

// BEGIN GENERATED JSON (kerml/tools/generate_json.py): do not edit, run the script instead.
namespace KerML::Entities {
    std::string Relationship::serializeToJson() {
        nlohmann::json json = nlohmann::json::parse(Element::serializeToJson());
        json["relatedElement"] = Json::reference(unresolvedJsonReferences("relatedElement"), Relationship::relatedElement());
        json["target"] = Json::reference(unresolvedJsonReferences("target"), Relationship::target());
        json["source"] = Json::reference(unresolvedJsonReferences("source"), Relationship::source());
        json["owningRelatedElement"] = Json::reference(unresolvedJsonReferences("owningRelatedElement"), Relationship::owningRelatedElement());
        json["ownedRelatedElement"] = Json::reference(unresolvedJsonReferences("ownedRelatedElement"), Relationship::ownedRelatedElement());
        json["isImplied"] = Json::value(Relationship::isImplied());
        return applyJsonSource(json.dump(JSON_INTENT));
    }

    void Relationship::deserializeAndPopulate(const std::string& jsonString) {
        Element::deserializeAndPopulate(jsonString);
        const nlohmann::json json = nlohmann::json::parse(jsonString);
        std::vector<boost::uuids::uuid> ids;
        if (Json::readReferences(json, "target", ids))
            setUnresolvedJsonReferences("target", ids);
        if (Json::readReferences(json, "source", ids))
            setUnresolvedJsonReferences("source", ids);
        if (Json::readReferences(json, "owningRelatedElement", ids))
            setUnresolvedJsonReferences("owningRelatedElement", ids);
        if (Json::readReferences(json, "ownedRelatedElement", ids))
            setUnresolvedJsonReferences("ownedRelatedElement", ids);
        {
            bool value{};
            if (Json::readBool(json, "isImplied", value)) {
                try {
                    Relationship::setIsImplied(value);
                } catch (const std::invalid_argument&) {
                    // A value the metaclass refuses (for example another operator than the fixed one) is ignored.
                }
            }
        }
    }

    void Relationship::resolveJsonReferences(const std::function<std::shared_ptr<Element>(const boost::uuids::uuid&)>& lookup) {
        Element::resolveJsonReferences(lookup);
        if (const auto ids = unresolvedJsonReferences("target")) {
            try {
                std::vector<std::shared_ptr<KerML::Entities::Element>> resolved;
                for (const auto& id : *ids) {
                    auto target = std::dynamic_pointer_cast<KerML::Entities::Element>(lookup(id));
                    if (!target)
                        break;
                    resolved.push_back(std::move(target));
                }
                // (the setter forgets the ids, see clearUnresolvedJsonReferences)
                if (resolved.size() == ids->size()) {
                    Relationship::setTarget(std::move(resolved));
                    clearUnresolvedJsonReferences("target");
                }
            } catch (const std::exception&) {
                // The reference stays unresolved if the model refuses it.
                setUnresolvedJsonReferences("target", *ids);
            }
        }
        if (const auto ids = unresolvedJsonReferences("source")) {
            try {
                std::vector<std::shared_ptr<KerML::Entities::Element>> resolved;
                for (const auto& id : *ids) {
                    auto target = std::dynamic_pointer_cast<KerML::Entities::Element>(lookup(id));
                    if (!target)
                        break;
                    resolved.push_back(std::move(target));
                }
                // (the setter forgets the ids, see clearUnresolvedJsonReferences)
                if (resolved.size() == ids->size()) {
                    Relationship::setSource(std::move(resolved));
                    clearUnresolvedJsonReferences("source");
                }
            } catch (const std::exception&) {
                // The reference stays unresolved if the model refuses it.
                setUnresolvedJsonReferences("source", *ids);
            }
        }
        if (const auto ids = unresolvedJsonReferences("owningRelatedElement")) {
            try {
                if (auto target = std::dynamic_pointer_cast<KerML::Entities::Element>(lookup(ids->front()))) {
                    Relationship::setOwningRelatedElement(std::move(target));
                    clearUnresolvedJsonReferences("owningRelatedElement");
                }
            } catch (const std::exception&) {
                // The reference stays unresolved if the model refuses it.
                setUnresolvedJsonReferences("owningRelatedElement", *ids);
            }
        }
        if (const auto ids = unresolvedJsonReferences("ownedRelatedElement")) {
            try {
                std::vector<std::shared_ptr<KerML::Entities::Element>> resolved;
                for (const auto& id : *ids) {
                    auto target = std::dynamic_pointer_cast<KerML::Entities::Element>(lookup(id));
                    if (!target)
                        break;
                    resolved.push_back(std::move(target));
                }
                // (the setter forgets the ids, see clearUnresolvedJsonReferences)
                if (resolved.size() == ids->size()) {
                    Relationship::setOwnedRelatedElements(std::move(resolved));
                    clearUnresolvedJsonReferences("ownedRelatedElement");
                }
            } catch (const std::exception&) {
                // The reference stays unresolved if the model refuses it.
                setUnresolvedJsonReferences("ownedRelatedElement", *ids);
            }
        }
    }
}
// END GENERATED JSON
