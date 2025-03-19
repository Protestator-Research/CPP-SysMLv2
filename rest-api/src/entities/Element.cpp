//
// Created by Moritz Herzog on 27.02.24.
//

#include <nlohmann/json.hpp>

#include "Element.h"
#include "JSONEntities.h"
#include "Identification.h"

namespace SysMLv2 {
    namespace Entities {
        Element::Element() : Data()
        {
            Type = "TextualRepresentation";
        }

        Element::Element(std::string jsonString) : Data(jsonString) {
            nlohmann::json json = nlohmann::json::parse(jsonString);


            if(!json[JSON_NAME_ENTITY].is_null())
                Name = json[JSON_NAME_ENTITY];

            if(!json[JSON_SHORT_NAME_ENTITY].is_null())
                ShortName = json[JSON_SHORT_NAME_ENTITY];

            if(!json[JSON_DECLARED_NAME_ENTITY].is_null())
                DeclaredName = json[JSON_DECLARED_NAME_ENTITY];

            if(!json[JSON_DECLARED_SHORT_NAME_ENTITY].is_null())
                DeclaredShortName = json[JSON_DECLARED_SHORT_NAME_ENTITY];

            if(!json[JSON_OWNED_ELEMENTS_ENTITY].is_null()){
                std::vector<nlohmann::json> values = json[JSON_OWNED_ELEMENTS_ENTITY];

                for(const auto& elementToParse : values) {
                    auto identity = new Identification();
                    from_json(elementToParse,*identity);
                    OwnedElements.push_back(identity);
                }
            }

            if(!json[JSON_OWNER_ENTITY].is_null())
                Owner = new Identification(json[JSON_OWNER_ENTITY].dump());

            if(!json[JSON_OWNING_MEMBERSHIP_ENTITY].is_null())
                OwningMembership = new Identification(json[JSON_OWNING_MEMBERSHIP_ENTITY].dump());

            if(!json[JSON_OWNING_NAMESPACE_ENTITY].is_null())
                OwningNamespace = new Identification(json[JSON_OWNING_NAMESPACE_ENTITY].dump());

            if(!json[JSON_OWNING_RELATIONSHIP_ENTITY].is_null())
                OwningRelationship = new Identification(json[JSON_OWNING_RELATIONSHIP_ENTITY].dump());

            if(!json[JSON_DIRECTION_ENTITY].is_null())
                Direction = json[JSON_DIRECTION_ENTITY];

            if(!json[JSON_VALUE_STRING_ENTITY].is_null())
                ValueStr = json[JSON_VALUE_STRING_ENTITY];

            if(!json[JSON_IMPORTED_MEMBER_NAME_ENTITY].is_null())
                ImportedMemberName = json[JSON_IMPORTED_MEMBER_NAME_ENTITY];

            if(!json[JSON_IMPORTED_NAMESPACE_ENTITY].is_null())
                ImportedNamespace = json[JSON_IMPORTED_NAMESPACE_ENTITY];

            if(!json[JSON_LANGUAGE_ENTITY].is_null())
                Language = json[JSON_LANGUAGE_ENTITY];

            if(!json[JSON_BODY_ENTITY].is_null())
                Body = json[JSON_BODY_ENTITY];

            if(!json[JSON_IS_IMPLIED_ELEMENT_ENTITY].is_null())
                IsImplied = json[JSON_IS_IMPLIED_ELEMENT_ENTITY];

            if(!json[JSON_IS_IMPLIED_INCLUDED_ENTITY].is_null())
                IsImpliedIncluded = json[JSON_IS_IMPLIED_INCLUDED_ENTITY];

            if(!json[JSON_IS_STANDARD_ENTITY].is_null())
                IsStandard = json[JSON_IS_STANDARD_ENTITY];

            if(!json[JSON_IS_LIBRARY_ELEMENT_ENTITY].is_null())
                IsLibraryElement = json[JSON_IS_LIBRARY_ELEMENT_ENTITY];

            if(!json[JSON_DOCUMENTATION_ENTITY].is_null())
                Documentation = new Identification(json[JSON_DOCUMENTATION_ENTITY].dump());

            if(!json[JSON_TEXTUAL_REPRESENTATION_ENTITY].is_null()) {
                std::vector<nlohmann::json> values = json[JSON_TEXTUAL_REPRESENTATION_ENTITY];

                for (const auto &elementToParse: values) {
                    auto identity = new Identification();
                    from_json(elementToParse,*identity);
                    TextualRepresentation.push_back(identity);
                }
            }

            if(!json[JSON_SOURCE_ENTITY].is_null()){
                std::vector<nlohmann::json> values = json[JSON_SOURCE_ENTITY];

                for(const auto& elementToParse : values) {
                    auto identity = new Identification();
                    from_json(elementToParse,*identity);
                    Source.push_back(identity);
                }
            }

            if(!json[JSON_TARGET_ENTITY].is_null()){
                std::vector<nlohmann::json> values = json[JSON_TARGET_ENTITY];

                for(const auto& elementToParse : values){
                    auto identity = new Identification();
                    from_json(elementToParse,*identity);
                    Target.push_back(identity);
                }
            }
        }

        Element::~Element() {
            for(auto elem : OwnedElements)
                delete elem;
            OwnedElements.clear();

            delete Owner;
            delete OwningMembership;
            delete OwningNamespace;
            delete OwningRelationship;

            delete Documentation;

            for(auto elem : TextualRepresentation)
                delete elem;
            TextualRepresentation.clear();

            for(auto elem : Source)
                delete elem;
            Source.clear();

            for(auto elem : Target)
                delete elem;
            Target.clear();
        }

        std::string Element::serializeToJson() {
            nlohmann::json json = nlohmann::json ::parse(Data::serializeToJson());

            serializeNullString(json,Name,JSON_NAME_ENTITY);
            serializeNullString(json,ShortName,JSON_SHORT_NAME_ENTITY);
            serializeNullString(json,DeclaredName,JSON_DECLARED_NAME_ENTITY);
            serializeNullString(json,DeclaredShortName,JSON_DECLARED_SHORT_NAME_ENTITY);

            for(const auto elem : OwnedElements){
                nlohmann::json json_elem;
                to_json(json_elem,elem);
                json[JSON_OWNED_ELEMENTS_ENTITY].push_back(json_elem);
            }

            to_json(json[JSON_OWNER_ENTITY],Owner);
            to_json(json[JSON_OWNING_MEMBERSHIP_ENTITY], OwningMembership);
            to_json(json[JSON_OWNING_NAMESPACE_ENTITY], OwningNamespace);
            to_json(json[JSON_OWNING_RELATIONSHIP_ENTITY], OwningRelationship);

            serializeNullString(json,Direction,JSON_DIRECTION_ENTITY);
            serializeNullString(json,ImportedMemberName,JSON_IMPORTED_MEMBER_NAME_ENTITY);
            serializeNullString(json,ImportedNamespace,JSON_IMPORTED_NAMESPACE_ENTITY);
            

            serializeNullString(json,ValueStr,JSON_VALUE_STRING_ENTITY);
            serializeNullString(json,Language,JSON_LANGUAGE_ENTITY);
            serializeNullString(json,Body,JSON_BODY_ENTITY);

            json[JSON_IS_IMPLIED_ELEMENT_ENTITY] = IsImplied;
            json[JSON_IS_IMPLIED_INCLUDED_ENTITY] = IsImpliedIncluded;
            json[JSON_IS_STANDARD_ENTITY] = IsStandard;
            json[JSON_IS_LIBRARY_ELEMENT_ENTITY] = IsLibraryElement;

            to_json(json[JSON_DOCUMENTATION_ENTITY], Documentation);

            for(const auto elem : TextualRepresentation){
                nlohmann::json json_elem;
                to_json(json_elem,elem);
                json[JSON_TEXTUAL_REPRESENTATION_ENTITY].push_back(json_elem);
            }

            for(const auto elem : Source){
                nlohmann::json json_elem;
                to_json(json_elem,elem);
                json[JSON_SOURCE_ENTITY].push_back(json_elem);
            }

            for(const auto elem : Target){
                nlohmann::json json_elem;
                to_json(json_elem,elem);
                json[JSON_TARGET_ENTITY].push_back(json_elem);
            }

            return json.dump();
        }

        void Element::serializeNullString(nlohmann::json &json, const std::string &value, const std::string &entity_value) {
            if(!value.empty())
                json[entity_value] = value;
            else
                json[entity_value] = NULL;
        }

        void Element::setBody(std::string body) {
            Body = body;
        }

        void Element::setLanguage(std::string language) {
            Language = language;
        }

        void Element::setName(std::string name) {
            Name = name;
        }

        std::string Element::name() {
            return Name;
        }

        void Element::setShortName(std::string shortName) {
            ShortName = shortName;
        }

        std::string Element::shortName() {
            return ShortName;
        }

        void Element::setDeclaredName(std::string declaredName) {
            DeclaredName = declaredName;
        }

        std::string Element::declaredName() {
            return DeclaredName;
        }

        void Element::setDeclaredShortName(std::string declaredShortName) {
            DeclaredShortName = declaredShortName;
        }

        std::string Element::getDeclaredShortName() {
            return DeclaredShortName;
        }

        std::vector<Identification *> Element::ownedElements() {
            return OwnedElements;
        }

        Identification *Element::owner() const {
            return Owner;
        }

        Identification *Element::owningMembership() const {
            return OwningMembership;
        }

        Identification *Element::owningNamespace() const {
            return OwningNamespace;
        }

        Identification *Element::owningRelationship() const {
            return OwningRelationship;
        }

        std::string Element::direction() {
            return Direction;
        }

        std::string Element::importedMemberName() {
            return ImportedMemberName;
        }

        std::string Element::importedNamespace() {
            return ImportedNamespace;
        }

        std::string Element::valueString() {
            return ValueStr;
        }

        std::string Element::language() {
            return Language;
        }

        std::string Element::body() {
            return Body;
        }

        bool Element::isImplied() {
            return IsImplied;
        }

        bool Element::isImpliedIncluded() {
            return IsImpliedIncluded;
        }

        bool Element::isStandard() {
            return IsStandard;
        }

        bool Element::isLibrary() {
            return IsLibraryElement;
        }

        Identification *Element::documentation() const {
            return Documentation;
        }

        std::vector<Identification *> Element::textualRepresentation() {
            return TextualRepresentation;
        }

        std::vector<Identification *> Element::source() {
            return Source;
        }

        std::vector<Identification *> Element::target() {
            return Target;
        }

        std::string Element::getMarkdownString() {
            if(body().empty()||(Language==""))
                return "";

            if(Language=="Markdown") {
                return "\r\n" + body() + "\r\n";
            } else {
                return "\r\n```" + Language + "\r\n" + body() + "\r\n```\r\n";
            }
        }


    } // Entities
} // SysMLv2