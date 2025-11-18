//
// Created by Moritz Herzog on 20.03.25.
//

#include <kerml/root/elements/Element.h>
#include <kerml/root/elements/Relationship.h>
#include <kerml/root/namespaces/Namespace.h>
#include <kerml/root/annotations/Documentation.h>
#include <sysmlv2/rest/entities/JSONEntities.h>

#include <utility>
#include <functional>
#include <boost/uuid/string_generator.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/lexical_cast.hpp>
#include <nlohmann/json.hpp>

#include "kerml/root/annotations/Annotation.h"
#include "kerml/root/annotations/TextualRepresentation.h"


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

    void Element::appendAliasId(std::string& aliasId) {
        AliasIds.push_back(aliasId);
        sortAliasIds();
    }

    std::vector<std::string> Element::aliasIds() const{
        return AliasIds;
    }

    void Element::setDeclaredShortName(std::string& declaredShortName) {
        DeclaredShortName = declaredShortName;
    }

    std::optional<std::string> Element::declaredShortName() const {
        if (DeclaredName.empty())
            return {};
        return DeclaredShortName;
    }

    void Element::setDeclaredName(std::string& declaredName) {
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
            return ShortName;

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
        Data::deserializeAndPopulate(jsonString);
    }

    void Element::sortAliasIds() {

    }

    Element::Element(std::string elementID, std::shared_ptr<Element> owner) :
        Data(boost::uuids::string_generator()(elementID)),
        ElementId(boost::uuids::string_generator()(elementID)) {
        _dType = "Element";
        Owner = owner;
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
        std::function<bool(std::shared_ptr<Element> lhs, std::shared_ptr<Element> rhs)>  comparisonFunction=
                [](std::shared_ptr<Element> lhs, std::shared_ptr<Element> rhs){
                    return  (*lhs) < (*rhs);
                };
        std::sort(OwnedRelationships.begin(), OwnedRelationships.end(), comparisonFunction);
    }

    void Element::sortOwnedElements() {
        std::function<bool(std::shared_ptr<Element> lhs, std::shared_ptr<Element> rhs)>  comparisonFunction=
                [](std::shared_ptr<Element> lhs, std::shared_ptr<Element> rhs){
            return  (*lhs) < (*rhs);
        };
        std::sort(OwnedElements.begin(), OwnedElements.end(), comparisonFunction);
    }

    std::shared_ptr<Element> Element::owner() const {
        return Owner;
    }

    void Element::setOwner(std::shared_ptr<Element> owner) {
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

    std::string Element::serializeToJson() {
        nlohmann::json json = nlohmann::json::parse(Data::serializeToJson());

        json[SysMLv2::REST::JSON_ELEMENT_ID_ENTITY] = ElementId;
        json[SysMLv2::REST::JSON_ALIAS_ID_ENTITY] = AliasIds;

        json[SysMLv2::REST::JSON_NAME_ENTITY] = Name;
        json[SysMLv2::REST::JSON_DECLARED_NAME_ENTITY] = DeclaredName;
        json[SysMLv2::REST::JSON_DECLARED_SHORT_NAME_ENTITY] = DeclaredShortName;

        std::string ownedRelationshipsString = "[\r\n";
        for (size_t i = 0; i < OwnedRelationships.size(); i++) {
            ownedRelationshipsString += OwnedRelationships[i]->serializeAsIdentity();
            if (i != (OwnedRelationships.size()-1))
                ownedRelationshipsString += ",\r\n";
        }
        ownedRelationshipsString += "]\r\n";
        json[SysMLv2::REST::JSON_OWNED_RELATIONSHIPS_ENTITY] = nlohmann::json::parse(ownedRelationshipsString);

        json[SysMLv2::REST::JSON_IS_IMPLIED_INCLUDED_ENTITY] = IsImpliedIncluded;
        json[SysMLv2::REST::JSON_OWNER_ENTITY] = Owner->serializeAsIdentity();

        std::string ownedElementsString = "[\r\n";
        for (size_t i = 0; i < OwnedElements.size(); i++) {
            ownedElementsString += OwnedElements[i]->serializeAsIdentity();
            if (i != (OwnedElements.size()-1))
                ownedElementsString += ",\r\n";
        }
        ownedElementsString += "]\r\n";
        json[SysMLv2::REST::JSON_OWNED_ELEMENTS_ENTITY] = nlohmann::json::parse(ownedElementsString);

        json[SysMLv2::REST::JSON_SHORT_NAME_ENTITY] = ShortName;
        json[SysMLv2::REST::JSON_QUALIFIED_NAME_ENTITY] = QualifiedName;
        json[SysMLv2::REST::JSON_IS_LIBRARY_ELEMENT_ENTITY] = IsLibraryElement;

        std::string docuementationsString = "[\r\n";
        for (size_t i = 0; i < Documentations.size(); i++) {
            docuementationsString += Documentations[i]->serializeAsIdentity();
            if (i != (Documentations.size()-1))
                docuementationsString += ",\r\n";
        }
        docuementationsString += "]\r\n";
        json[SysMLv2::REST::JSON_DOCUMENTATION_ENTITY] = nlohmann::json::parse(docuementationsString);

        std::string ownedAnnotationsString = "[\r\n";
        for (size_t i = 0; i < OwnedAnnotations.size(); i++) {
            ownedAnnotationsString += OwnedAnnotations[i]->serializeAsIdentity();
            if (i != (OwnedAnnotations.size()-1))
                ownedAnnotationsString += ",\r\n";
        }
        ownedAnnotationsString += "]\r\n";
        json[SysMLv2::REST::JSON_OWNED_ANNOTATION_ENTITY] = nlohmann::json::parse(ownedAnnotationsString);

        std::string textualRepresentationString = "[\r\n";
        for (size_t i = 0; i < TextualRepresentations.size(); i++) {
            textualRepresentationString += TextualRepresentations[i]->serializeAsIdentity();
            if (i != (TextualRepresentations.size()-1))
                textualRepresentationString += ",\r\n";
        }
        textualRepresentationString += "]\r\n";
        json[SysMLv2::REST::JSON_TEXTUAL_REPRESENTATION_ENTITY] = nlohmann::json::parse(textualRepresentationString);

        json[SysMLv2::REST::JSON_OWNING_RELATIONSHIP_ENTITY] = nlohmann::json::parse(OwningRelationship->serializeAsIdentity());

        return json.dump(JSON_INTENT);
    }
} // KerML::Entities
