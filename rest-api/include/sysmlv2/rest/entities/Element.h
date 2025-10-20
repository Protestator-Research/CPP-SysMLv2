//
// Created by Moritz Herzog on 27.02.24.
//
//---------------------------------------------------------
// Constants, Definitions, Pragmas
//---------------------------------------------------------
#pragma once
//---------------------------------------------------------
// External Classes
//---------------------------------------------------------
#include <vector>
#include <string>
#include <nlohmann/json.hpp>
//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include <sysmlv2/rest/entities/Data.h>
#include <sysmlv2/rest/sysmlv2rest_global.h>
//---------------------------------------------------------
// Forwarding
//---------------------------------------------------------

namespace SysMLv2::REST {
    class Identification;
}

namespace SysMLv2::REST {
    /**
     * This class is not an exact, but a compatible Representation of the SysMLv2 Element class. This implementation
     * stems from the AGILA Backend implementation of the Element class.
     * @version 1.0
     * @author Moritz Herzog
     * @class Element
     * @deprecated This should be a representation of the KerML Element Class, therefore see
     */
    class SYSMLV2REST_EXPORT Element : public Data {
    public:
        /**
         * C-Tor
         */
         Element();

        /**
         * C-Tor for the parsing.
         * @param jsonString JSON string to
         */
         Element(std::string jsonString);

        /**
         * D-Tor
         */
         ~Element() override;

         std::string serializeToJson() override;

         void setName(std::string name);
         std::string name();

         void setShortName(std::string shortName);
         std::string shortName();

         void setDeclaredName(std::string declaredName);
         std::string declaredName();

         void setDeclaredShortName(std::string declaredShortName);
         std::string getDeclaredShortName();

         std::vector<std::shared_ptr<Identification>> ownedElements();
         std::shared_ptr<Identification> owner() const;
         std::shared_ptr<Identification> owningMembership() const;
         std::shared_ptr<Identification> owningNamespace() const;
         std::shared_ptr<Identification> owningRelationship() const;

         std::string direction();
         std::string importedMemberName();
         std::string importedNamespace();

         std::string valueString();

         void setLanguage(std::string language);
         std::string language();
         void setBody(std::string body);
         std::string body();

         bool isImplied();
         bool isImpliedIncluded();
         bool isStandard();
         bool isLibrary();

         std::shared_ptr<Identification> documentation() const;

         std::vector<std::shared_ptr<Identification>> textualRepresentation();

        std::vector<std::shared_ptr<Identification>> source();
        std::vector<std::shared_ptr<Identification>> target();

        std::string getMarkdownString();

    protected:
        void serializeNullString(nlohmann::json& json, const std::string& value, const std::string& entity_value);

        std::string Name;
        std::string ShortName;
        std::string DeclaredName;
        std::string DeclaredShortName;

        std::vector<std::shared_ptr<Identification>> OwnedElements;
        std::shared_ptr<Identification> Owner = nullptr;
        std::shared_ptr<Identification> OwningMembership = nullptr;
        std::shared_ptr<Identification> OwningNamespace = nullptr;
        std::shared_ptr<Identification> OwningRelationship = nullptr;

        std::string Direction;
        std::string ImportedMemberName;
        std::string ImportedNamespace;

        /**
         * Value String only there for the Compatibility to the AGILA Backend Version 2
         */
        std::string ValueStr;

        std::string Language;
        std::string Body;

        bool IsImplied = false;
        bool IsImpliedIncluded = false;
        bool IsStandard = false;
        bool IsLibraryElement = false;

        std::shared_ptr<Identification> Documentation = nullptr;
        std::vector<std::shared_ptr<Identification>> TextualRepresentation;

        std::vector<std::shared_ptr<Identification>> Source;
        std::vector<std::shared_ptr<Identification>> Target;
    };
} // SysMLv2::Entities
