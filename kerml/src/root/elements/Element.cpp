//
// Created by Moritz Herzog on 20.03.25.
//

#include "Element.h"
#include "Relationship.h"
#include "../namespaces/Namespace.h"

#include <utility>
#include <boost/uuid/string_generator.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/lexical_cast.hpp>


namespace KerML::Entities {
    Element::Element(boost::uuids::uuid elementID, std::shared_ptr<Element> owner) :
        ElementId(elementID)
    {
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

    std::string Element::declaredShortName() const {
        return DeclaredShortName;
    }

    void Element::setDeclaredName(std::string& declaredName) {
        DeclaredName = declaredName;
    }

    std::string Element::declaredName() const{
        return DeclaredName;
    }

    void Element::setImpliedIncluded(bool& isImpliedIncluded) {
        IsImpliedIncluded = isImpliedIncluded;
    }

    bool Element::isImpliedIncluded() const{
        return IsImpliedIncluded;
    }

    std::string Element::escapedName() const{
        return std::string();
    }

    std::string Element::effectiveShortName() const{
        if(DeclaredShortName.empty())
            return ShortName;

        return DeclaredShortName;
    }

    std::string Element::effectiveName() const{
        if((DeclaredName.empty())&&(Name.empty()))
            return QualifiedName;

        if(DeclaredName.empty())
            return Name;

        return DeclaredName;
    }

    std::shared_ptr<Namespace> Element::libraryNamespace() const{
        return std::shared_ptr<Namespace>();
    }

    void Element::sortAliasIds() {

    }

    Element::Element(std::string elementID, std::shared_ptr<Element> owner) :
        ElementId(boost::uuids::string_generator()(elementID)){
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

    void Element::setOwningNamespace(std::shared_ptr<Namespace> owningNamespace) {
        OwningNamespace = owningNamespace;
    }

    std::shared_ptr<Namespace> Element::owningNamespace() {
        return OwningNamespace;
    }

    std::string Element::path()
    {
        if (libraryNamespace())
            return libraryNamespace()->path() + "::" + escapedName();
        else
            return escapedName();
    }
} // KerML::Entities
