//
// Created by Moritz Herzog on 20.03.25.
//

#include <kerml/root/elements/Element.h>
#include <kerml/root/elements/Relationship.h>
#include <kerml/root/namespaces/Namespace.h>
#include <kerml/root/annotations/Documentation.h>
#include <sysmlv2/rest/entities/JSONEntities.h>

#include <utility>
#include <stdexcept>
#include <functional>
#include <boost/uuid/string_generator.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/lexical_cast.hpp>
#include <nlohmann/json.hpp>

#include "kerml/root/annotations/Annotation.h"
#include "kerml/root/annotations/TextualRepresentation.h"
#include <kerml/root/namespaces/OwningMembership.h>
#include "../../model/JsonSupport.h"


namespace KerML::Entities {
    Element::Element(boost::uuids::uuid elementID, std::shared_ptr<Element> owner) :
        Data(elementID),
        ElementId(elementID)
    {
        _dType = "Element";
        Owner = std::move(owner);
        IsLibraryElement = false;
    }

    std::string Element::elementId() const{
        return boost::lexical_cast<std::string>(ElementId);
    }

    void Element::setAliasIds(std::vector<std::string> aliasIds) {
        AliasIds = aliasIds;
        sortAliasIds();
    }

    void Element::appendAliasId(const std::string& aliasId) {
        AliasIds.push_back(aliasId);
        sortAliasIds();
    }

    std::vector<std::string> Element::aliasIds() const{
        return AliasIds;
    }

    void Element::setDeclaredShortName(const std::string& declaredShortName) {
        DeclaredShortName = declaredShortName;
    }

    std::optional<std::string> Element::declaredShortName() const {
        if (DeclaredShortName.empty())
            return {};
        return DeclaredShortName;
    }

    void Element::setDeclaredName(const std::string& declaredName) {
        DeclaredName = declaredName;
    }

    std::optional<std::string> Element::declaredName() const{
        if (DeclaredName.empty())
            return {};
        return DeclaredName;
    }

    void Element::setImpliedIncluded(bool& isImpliedIncluded) {
        IsImpliedIncluded = isImpliedIncluded;
    }

    bool Element::isImpliedIncluded() const{
        return IsImpliedIncluded;
    }

    std::optional<std::string> Element::escapedName() const{
        return std::string();
    }

    std::optional<std::string> Element::effectiveShortName() const{
        if(DeclaredShortName.empty())
            return ShortName.empty() ? std::optional<std::string>{} : ShortName;

        return DeclaredShortName;
    }

    std::optional<std::string> Element::effectiveName() const{
        if (DeclaredName.empty() && Name.empty() && QualifiedName.empty())
            return {};

    	if((DeclaredName.empty())&&(Name.empty()))
            return QualifiedName;

        if(DeclaredName.empty())
            return Name;
        
        return DeclaredName;
    }

    std::shared_ptr<Namespace> Element::libraryNamespace() const{
        if (OwningRelationship != nullptr)
            return OwningRelationship->libraryNamespace();
        return nullptr;
    }

    void Element::deserializeAndPopulate(const std::string &jsonString) {
        const nlohmann::json json = nlohmann::json::parse(jsonString);
        if (!json.is_object())
            throw std::invalid_argument("The JSON of an Element must be an object.");

        // The element id is the "@id"; "elementId" is only used if there is no valid "@id". Both are kept the same.
        std::optional<boost::uuids::uuid> id;
        for (const char* key : {"@id", "elementId"}) {
            const auto it = json.find(key);
            if (it != json.end() && it->is_string())
                id = Json::parseIdentity(*it);
            if (id)
                break;
        }
        if (id)
            assignElementId(*id);

        Json::readStringArray(json, SysMLv2::REST::JSON_ALIAS_ID_ENTITY.c_str(), AliasIds);
        sortAliasIds();
        Json::readString(json, SysMLv2::REST::JSON_DECLARED_NAME_ENTITY.c_str(), DeclaredName);
        Json::readString(json, SysMLv2::REST::JSON_DECLARED_SHORT_NAME_ENTITY.c_str(), DeclaredShortName);
        // (name, shortName and qualifiedName are derived: they feed effectiveName() and would change the name of the element)
        Json::readBool(json, SysMLv2::REST::JSON_IS_IMPLIED_INCLUDED_ENTITY.c_str(), IsImpliedIncluded);
        Json::readBool(json, SysMLv2::REST::JSON_IS_LIBRARY_ELEMENT_ENTITY.c_str(), IsLibraryElement);

        std::vector<boost::uuids::uuid> ids;
        // (older versions wrote the property as "ownedRelationships")
        if (Json::readReferences(json, "ownedRelationship", ids) || Json::readReferences(json, "ownedRelationships", ids))
            setUnresolvedJsonReferences("ownedRelationship", ids);
        if (Json::readReferences(json, "owningRelationship", ids))
            setUnresolvedJsonReferences("owningRelationship", ids);
        // The derived references that Element keeps as caches (see the generated code of the other classes).
        for (const char* key : {"owner", "ownedElement", "documentation", "ownedAnnotation", "textualRepresentation"}) {
            if (Json::readReferences(json, key, ids))
                setUnresolvedJsonReferences(key, ids);
        }
    }

    std::optional<std::vector<boost::uuids::uuid>> Element::unresolvedJsonReferences(const std::string& property) const {
        const auto it = UnresolvedJsonReferences.find(property);
        if (it == UnresolvedJsonReferences.end())
            return std::nullopt;
        return it->second;
    }

    void Element::setUnresolvedJsonReferences(const std::string& property, std::vector<boost::uuids::uuid> ids) {
        if (ids.empty())
            UnresolvedJsonReferences.erase(property);
        else
            UnresolvedJsonReferences[property] = std::move(ids);
    }

    void Element::clearUnresolvedJsonReferences(const std::string& property) {
        UnresolvedJsonReferences.erase(property);
    }

    bool Element::hasUnresolvedJsonReferences() const {
        return !UnresolvedJsonReferences.empty();
    }

    void Element::resolveJsonReferences(const std::function<std::shared_ptr<Element>(const boost::uuids::uuid&)>& lookup) {
        if (const auto ids = unresolvedJsonReferences("ownedRelationship")) {
            try {
                std::vector<std::shared_ptr<Relationship>> resolved;
                for (const auto& id : *ids) {
                    auto target = std::dynamic_pointer_cast<Relationship>(lookup(id));
                    if (!target)
                        break;
                    resolved.push_back(std::move(target));
                }
                if (resolved.size() == ids->size()) {
                    setOwnedRelationship(std::move(resolved));
                    clearUnresolvedJsonReferences("ownedRelationship");
                }
            } catch (const std::exception&) {
                // The references stay unresolved if the model refuses them.
                setUnresolvedJsonReferences("ownedRelationship", *ids);
            }
        }
        if (const auto ids = unresolvedJsonReferences("owningRelationship")) {
            try {
                if (auto target = std::dynamic_pointer_cast<Relationship>(lookup(ids->front()))) {
                    setOwningRelationship(std::move(target));
                    clearUnresolvedJsonReferences("owningRelationship");
                }
            } catch (const std::exception&) {
                setUnresolvedJsonReferences("owningRelationship", *ids);
            }
        }
        resolveCache<Element>("owner", lookup, [this](std::shared_ptr<Element> value) { setOwner(std::move(value)); });
        resolveCaches<Element>("ownedElement", lookup, [this](std::vector<std::shared_ptr<Element>> value) { setOwnedElement(std::move(value)); });
        resolveCaches<Documentation>("documentation", lookup, [this](std::vector<std::shared_ptr<Documentation>> value) { setDocumentation(std::move(value)); });
        resolveCaches<Annotation>("ownedAnnotation", lookup, [this](std::vector<std::shared_ptr<Annotation>> value) { setOwnedAnnotation(std::move(value)); });
        resolveCaches<TextualRepresentation>("textualRepresentation", lookup, [this](std::vector<std::shared_ptr<TextualRepresentation>> value) { setTextualRepresentation(std::move(value)); });
    }

    std::string Element::sourceJson() const {
        return SourceJson;
    }

    void Element::sortAliasIds() {

    }

    Element::Element(std::string elementID, std::shared_ptr<Element> owner) :
        Element(Json::elementIdOf(elementID), std::move(owner)) {
        if (Json::looksLikeJson(elementID)) {
            Element::deserializeAndPopulate(elementID);
            // a plain Element keeps the type of the JSON, like fromJson()
            std::string type;
            if (Json::readString(nlohmann::json::parse(elementID), SysMLv2::REST::JSON_TYPE_ENTITY.c_str(), type) && !type.empty())
                _dType = type;
            captureJsonSource(elementID);
        }
    }

    void Element::captureJsonSource(const std::string& jsonString) {
        SourceJson.clear();
        BaselineJson = serializeToJson();
        SourceJson = nlohmann::json::parse(jsonString).dump();
    }

    void Element::discardSourceJson() {
        SourceJson.clear();
        BaselineJson.clear();
    }

    std::string Element::applyJsonSource(const std::string& produced) {
        if (SourceJson.empty())
            return produced;
        nlohmann::json result = nlohmann::json::parse(produced);
        const nlohmann::json source = nlohmann::json::parse(SourceJson);
        const nlohmann::json baseline = nlohmann::json::parse(BaselineJson);
        for (auto it = source.begin(); it != source.end(); ++it) {
            const auto current = result.find(it.key());
            if (current == result.end()) {
                result[it.key()] = it.value();
                continue;
            }
            const auto original = baseline.find(it.key());
            if (original != baseline.end() && *original == *current)
                *current = it.value();
        }
        return result.dump(JSON_INTENT);
    }

    void Element::assignElementId(const boost::uuids::uuid& elementId) {
        ElementId = elementId;
        _dId = elementId;
    }

    boost::uuids::uuid Element::elementIdAsUUID() const {
        return ElementId;
    }

    bool Element::operator==(const Element &other) {
        return elementId() == other.elementId();
    }


    bool Element::operator<(const Element &other) {
        return elementId()<other.elementId();
    }

    bool Element::operator>(const Element &other) {
        return elementId()>other.elementId();
    }

    bool Element::operator<=(const Element &other) {
        return elementId()<=other.elementId();;
    }

    bool Element::operator>=(const Element &other) {
        return elementId()>=other.elementId();
    }

    void Element::sortOwnedRelationships() {
        // Ordered metamodel collections preserve insertion order.
    }

    void Element::sortOwnedElements() {
        // Ordered metamodel collections preserve insertion order.
    }

    std::shared_ptr<Element> Element::owner() const {
        return Owner;
    }

    void Element::setOwner(std::shared_ptr<Element> owner) {
        clearUnresolvedJsonReferences("owner");
        Owner = owner;
    }

    void Element::appendOwnedElements(std::vector<std::shared_ptr<Element>> ownedElements) {
        OwnedElements.insert(OwnedElements.end(),ownedElements.begin(), ownedElements.end());
        sortOwnedElements();
    }

    void Element::setOwnedElements(std::vector<std::shared_ptr<Element>> ownedElements) {
        OwnedElements = ownedElements;
        sortOwnedElements();
    }

    void Element::appendOwnedElement(std::shared_ptr<Element> ownedElement) {
        OwnedElements.push_back(ownedElement);
        sortOwnedElements();
    }

    std::vector<std::shared_ptr<Element>> Element::ownedElements(){
        return OwnedElements;
    }

    std::string Element::path()
    {
        if (libraryNamespace())
            return libraryNamespace()->path() + "::" + escapedName().value();
        else
            return escapedName().value();
    }

    bool Element::includes(std::shared_ptr<Element>) {
        return false;
    }

    std::shared_ptr<Element> Element::fromJson(const std::string& jsonString) {
        const nlohmann::json json = nlohmann::json::parse(jsonString);
        if (!json.is_object())
            throw std::invalid_argument("The JSON of an Element must be an object.");

        const auto stringValue = [&json](const std::string& key) -> std::string {
            const auto it = json.find(key);
            return (it != json.end() && it->is_string()) ? it->get<std::string>() : std::string();
        };
        const auto boolValue = [&json](const std::string& key) -> bool {
            const auto it = json.find(key);
            return it != json.end() && it->is_boolean() && it->get<bool>();
        };

        boost::uuids::uuid id;
        try {
            id = boost::uuids::string_generator()(stringValue(SysMLv2::REST::JSON_ID_ENTITY));
        } catch (const std::exception&) {
            throw std::invalid_argument("The JSON of an Element requires a valid \"@id\".");
        }

        boost::uuids::uuid elementId = id;
        try {
            const std::string elementIdString = stringValue(SysMLv2::REST::JSON_ELEMENT_ID_ENTITY);
            if (!elementIdString.empty())
                elementId = boost::uuids::string_generator()(elementIdString);
        } catch (const std::exception&) {
            elementId = id;
        }

        auto element = std::make_shared<Element>(elementId);
        element->_dId = id;
        const std::string type = stringValue(SysMLv2::REST::JSON_TYPE_ENTITY);
        if (!type.empty())
            element->_dType = type;

        const auto aliasIds = json.find(SysMLv2::REST::JSON_ALIAS_ID_ENTITY);
        if (aliasIds != json.end() && aliasIds->is_array()) {
            for (const auto& alias : *aliasIds) {
                if (alias.is_string())
                    element->AliasIds.push_back(alias.get<std::string>());
            }
        }

        element->Name = stringValue(SysMLv2::REST::JSON_NAME_ENTITY);
        element->DeclaredName = stringValue(SysMLv2::REST::JSON_DECLARED_NAME_ENTITY);
        element->DeclaredShortName = stringValue(SysMLv2::REST::JSON_DECLARED_SHORT_NAME_ENTITY);
        element->ShortName = stringValue(SysMLv2::REST::JSON_SHORT_NAME_ENTITY);
        element->QualifiedName = stringValue(SysMLv2::REST::JSON_QUALIFIED_NAME_ENTITY);
        element->IsLibraryElement = boolValue(SysMLv2::REST::JSON_IS_LIBRARY_ELEMENT_ENTITY);
        element->IsImpliedIncluded = boolValue(SysMLv2::REST::JSON_IS_IMPLIED_INCLUDED_ENTITY);

        element->OriginalJson = json.dump(element->JSON_INTENT);
        return element;
    }

    std::string Element::serializeToJson() {
        if (!OriginalJson.empty())
            return OriginalJson;

        nlohmann::json json = nlohmann::json::parse(Data::serializeToJson());

        json[SysMLv2::REST::JSON_ELEMENT_ID_ENTITY] = boost::uuids::to_string(ElementId);
        json[SysMLv2::REST::JSON_ALIAS_ID_ENTITY] = AliasIds;

        json[SysMLv2::REST::JSON_NAME_ENTITY] = Json::value(name());
        json[SysMLv2::REST::JSON_DECLARED_NAME_ENTITY] = Json::value(declaredName());
        json[SysMLv2::REST::JSON_DECLARED_SHORT_NAME_ENTITY] = Json::value(declaredShortName());
        json[SysMLv2::REST::JSON_SHORT_NAME_ENTITY] = Json::value(shortName());
        json[SysMLv2::REST::JSON_QUALIFIED_NAME_ENTITY] = Json::value(qualifiedName());
        json[SysMLv2::REST::JSON_IS_IMPLIED_INCLUDED_ENTITY] = IsImpliedIncluded;
        json[SysMLv2::REST::JSON_IS_LIBRARY_ELEMENT_ENTITY] = IsLibraryElement;

        json["ownedRelationship"] = Json::reference(unresolvedJsonReferences("ownedRelationship"), OwnedRelationships);
        json["owningRelationship"] = Json::reference(unresolvedJsonReferences("owningRelationship"), OwningRelationship);
        json["owningMembership"] = Json::identity(owningMembership());
        json["owningNamespace"] = Json::identity(owningNamespace());
        json[SysMLv2::REST::JSON_OWNER_ENTITY] = Json::reference(unresolvedJsonReferences("owner"), Owner);
        json["ownedElement"] = Json::reference(unresolvedJsonReferences("ownedElement"), OwnedElements);
        json[SysMLv2::REST::JSON_DOCUMENTATION_ENTITY] = Json::reference(unresolvedJsonReferences("documentation"), Documentations);
        json[SysMLv2::REST::JSON_OWNED_ANNOTATION_ENTITY] = Json::reference(unresolvedJsonReferences("ownedAnnotation"), OwnedAnnotations);
        json[SysMLv2::REST::JSON_TEXTUAL_REPRESENTATION_ENTITY] = Json::reference(unresolvedJsonReferences("textualRepresentation"), TextualRepresentations);

        return applyJsonSource(json.dump(JSON_INTENT));
    }
} // KerML::Entities

namespace KerML::Entities {
std::vector<std::shared_ptr<Relationship>> Element::ownedRelationships() { return OwnedRelationships; }
}
