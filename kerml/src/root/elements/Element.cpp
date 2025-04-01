//
// Created by Moritz Herzog on 20.03.25.
//

#include "Element.h"
#include "Relationship.h"

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

    Element::~Element() {    }

    std::string Element::elementId() const{
        return boost::lexical_cast<std::string>(ElementId);
    }

    void Element::setAliasIds(std::vector<std::string> aliasIds) {
        AliasIds = aliasIds;
        orderAliasIds();
    }

    void Element::appendAliasId(std::string& aliasId) {
        AliasIds.push_back(aliasId);
        orderAliasIds();
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
        return std::string();
    }

    std::string Element::effectiveName() const{
        return std::string();
    }

    std::shared_ptr<Namespace> Element::libraryNamespace() const{
        return std::shared_ptr<Namespace>();
    }

    void Element::orderAliasIds() {

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

    void Element::orderOwnedRelationships() {
        std::function<bool(std::shared_ptr<Element> lhs, std::shared_ptr<Element> rhs)>  comparisonFunction=
                [](std::shared_ptr<Element> lhs, std::shared_ptr<Element> rhs){
                    return  (*lhs) < (*rhs);
                };
        std::sort(OwnedRelationships.begin(), OwnedRelationships.end(), comparisonFunction);
    }

    void Element::orderOwnedElements() {
        std::function<bool(std::shared_ptr<Element> lhs, std::shared_ptr<Element> rhs)>  comparisonFunction=
                [](std::shared_ptr<Element> lhs, std::shared_ptr<Element> rhs){
            return  (*lhs) < (*rhs);
        };
        std::sort(OwnedElements.begin(), OwnedElements.end(), comparisonFunction);
    }

} // KerML::Entities
