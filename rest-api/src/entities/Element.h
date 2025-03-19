//
// Created by Moritz Herzog on 27.02.24.
//
//---------------------------------------------------------
// Constants, Definitions, Pragmas
//---------------------------------------------------------
#ifndef DIGITALTWIN_ELEMENT_H
#define DIGITALTWIN_ELEMENT_H
//---------------------------------------------------------
// External Classes
//---------------------------------------------------------
#include <vector>
#include <string>
#include <nlohmann/json.hpp>
//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include "Data.h"

//---------------------------------------------------------
// Forwarding
//---------------------------------------------------------

namespace SysMLv2::Entities {
    class Identification;
}

namespace SysMLv2::Entities {
    /**
     * This class is not an exact, but a compatible Representation of the SysMLv2 Element class. This implementation
     * stems from the AGILA Backend implementation of the Element class.
     * @version 1.0
     * @author Moritz Herzog
     * @class Element
     */
    class Element : public Data {
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

        std::vector<Identification*> ownedElements();
        Identification* owner() const;
        Identification* owningMembership() const;
        Identification* owningNamespace() const;
        Identification* owningRelationship() const;

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

        Identification* documentation() const;

        std::vector<Identification*> textualRepresentation();

        std::vector<Identification*> source();
        std::vector<Identification*> target();

        std::string getMarkdownString();
    protected:

    private:
        void serializeNullString(nlohmann::json& json, const std::string& value, const std::string& entity_value);

        std::string Name;
        std::string ShortName;
        std::string DeclaredName;
        std::string DeclaredShortName;

        std::vector<Identification*> OwnedElements;
        Identification* Owner = nullptr;
        Identification* OwningMembership = nullptr;
        Identification* OwningNamespace = nullptr;
        Identification* OwningRelationship = nullptr;

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

        Identification* Documentation = nullptr;
        std::vector<Identification*> TextualRepresentation;

        std::vector<Identification*> Source;
        std::vector<Identification*> Target;
    };
} // SysMLv2

#endif //DIGITALTWIN_ELEMENT_H
