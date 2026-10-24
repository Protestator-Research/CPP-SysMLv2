//
// Created by Moritz Herzog on 24.03.25.
//
//---------------------------------------------------------
// Constants, Definitions, Pragmas
//---------------------------------------------------------
#pragma once
#include <kerml/model/Forward.h>
//---------------------------------------------------------
// External Classes
//---------------------------------------------------------
#include <kerml/root/annotations/AnnotatingElement.h>
#include <string>
//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include <kerml/kerml_global.h>
//---------------------------------------------------------
// Forwarding
//---------------------------------------------------------

namespace KerML::Entities {
    /**
     * @class TextualRepresentation
     * @author Moritz Herzog
     */
    class KERML_EXPORT TextualRepresentation : public AnnotatingElement{
    public:
        TextualRepresentation();
        TextualRepresentation(std::string  language, std::string body);

        /**
         * Creates a TextualRepresentation either from its JSON representation (if the string starts with '{') or with a declared name.
         * @param nameOrJson The JSON representation or the declared name.
         */
        TextualRepresentation(std::string nameOrJson);

        ~TextualRepresentation() override = default;

        std::string language();
        void setLanguage(std::string language);

        std::string body();
        void setBody(std::string body);

    private:
        std::string Language;
        std::string Body;
    public:
        std::shared_ptr<Element> representedElement() const;
        void setRepresentedElement(std::shared_ptr<Element> value);

    // BEGIN GENERATED JSON (kerml/tools/generate_json.py): do not edit, run the script instead.
    public:
        /**
         * Serializes the TextualRepresentation to JSON: all properties of the metaclass (stored and derived ones). References to other elements are
         * only written as identities ({"@id": "<uuid>"}), never recursively.
         * @return The JSON representation of the TextualRepresentation.
         */
        std::string serializeToJson() override;

        /**
         * Resolves the references that were read from JSON to the elements (see Element::resolveJsonReferences()), for the properties
         * of TextualRepresentation and of its base classes.
         * @param lookup Returns the element of an element id, or an empty pointer if it is not known.
         */
        void resolveJsonReferences(const std::function<std::shared_ptr<Element>(const boost::uuids::uuid&)>& lookup) override;

    protected:
        /**
         * Populates the TextualRepresentation from its JSON representation; the stored properties of TextualRepresentation and of its base classes are read,
         * computed derived properties are ignored, the derived references that the model keeps as collections are read like the stored ones,
         * and references are only stored as ids.
         * @param jsonString The JSON representation of the TextualRepresentation.
         */
        void deserializeAndPopulate(const std::string& jsonString) override;
    // END GENERATED JSON
    };
} // KerML::Entities
