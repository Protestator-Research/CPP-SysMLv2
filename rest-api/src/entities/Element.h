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
     * @deprecated This should be a representation of the KerML Element Class, therefore see
     */
    class Element : public Data {
    public:
        /**
         * C-Tor
         */
        [[deprecated]] Element();

        /**
         * C-Tor for the parsing.
         * @param jsonString JSON string to
         */
        [[deprecated]] Element(std::string jsonString);

        /**
         * D-Tor
         */
        [[deprecated]] ~Element() override;

        [[deprecated]] std::string serializeToJson() override;

        [[deprecated]] void setName(std::string name);
        [[deprecated]] std::string name();

        [[deprecated]] void setShortName(std::string shortName);
        [[deprecated]] std::string shortName();

        [[deprecated]] void setDeclaredName(std::string declaredName);
        [[deprecated]] std::string declaredName();

        [[deprecated]] void setDeclaredShortName(std::string declaredShortName);
        [[deprecated]] std::string getDeclaredShortName();

        [[deprecated]] std::vector<std::shared_ptr<Identification>> ownedElements();
        [[deprecated]] std::shared_ptr<Identification> owner() const;
        [[deprecated]] std::shared_ptr<Identification> owningMembership() const;
        [[deprecated]] std::shared_ptr<Identification> owningNamespace() const;
        [[deprecated]] std::shared_ptr<Identification> owningRelationship() const;

        [[deprecated]] std::string direction();
        [[deprecated]] std::string importedMemberName();
        [[deprecated]] std::string importedNamespace();

        [[deprecated]] std::string valueString();

        [[deprecated]] void setLanguage(std::string language);
        [[deprecated]] std::string language();
        [[deprecated]] void setBody(std::string body);
        [[deprecated]] std::string body();

        [[deprecated]] bool isImplied();
        [[deprecated]] bool isImpliedIncluded();
        [[deprecated]] bool isStandard();
        [[deprecated]] bool isLibrary();

        [[deprecated]] std::shared_ptr<Identification> documentation() const;

        [[deprecated]] std::vector<std::shared_ptr<Identification>> textualRepresentation();

        [[deprecated]] std::vector<std::shared_ptr<Identification>> source();
        [[deprecated]] std::vector<std::shared_ptr<Identification>> target();

        [[deprecated]] std::string getMarkdownString();
    protected:

    private:
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
} // SysMLv2

#endif //DIGITALTWIN_ELEMENT_H
