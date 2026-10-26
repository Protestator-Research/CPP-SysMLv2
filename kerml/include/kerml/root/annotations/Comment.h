//
// Created by Moritz Herzog on 24.03.25.
//
//---------------------------------------------------------
// Constants, Definitions, Pragmas
//---------------------------------------------------------
#pragma once
//---------------------------------------------------------
// External Classes
//---------------------------------------------------------
#include <string>
//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include <kerml/kerml_global.h>
#include <kerml/root/annotations/AnnotatingElement.h>
//---------------------------------------------------------
// Forwarding
//---------------------------------------------------------


namespace KerML::Entities {
    class KERML_EXPORT Comment  : public AnnotatingElement{
    public:
        Comment();
        Comment(std::string locale, std::string body);
        ~Comment() override = default;

        std::string locale();
        void setLocale(std::string locale);

        std::string body();
        void setBody(std::string body);

    protected:

    private:
        std::string Locale;
        std::string Body;

    // BEGIN GENERATED JSON (kerml/tools/generate_json.py): do not edit, run the script instead.
    public:
        /**
         * Creates a Comment either from its JSON representation (if the string starts with '{') or with the given declared name.
         * Reading JSON only stores the ids of the referenced elements, see Element::resolveJsonReferences(). The type of the object stays "Comment".
         * @param nameOrJson The JSON representation of the Comment, or its declared name.
         */
        explicit Comment(const std::string& nameOrJson);

        /**
         * Serializes the Comment to JSON: all properties of the metaclass (stored and derived ones). References to other elements are
         * only written as identities ({"@id": "<uuid>"}), never recursively.
         * @return The JSON representation of the Comment.
         */
        std::string serializeToJson() override;

        /**
         * Resolves the references that were read from JSON to the elements (see Element::resolveJsonReferences()), for the properties
         * of Comment and of its base classes.
         * @param lookup Returns the element of an element id, or an empty pointer if it is not known.
         */
        void resolveJsonReferences(const std::function<std::shared_ptr<Element>(const boost::uuids::uuid&)>& lookup) override;

    protected:
        /**
         * Populates the Comment from its JSON representation; the stored properties of Comment and of its base classes are read,
         * computed derived properties are ignored, the derived references that the model keeps as collections are read like the stored ones,
         * and references are only stored as ids.
         * @param jsonString The JSON representation of the Comment.
         */
        void deserializeAndPopulate(const std::string& jsonString) override;
    // END GENERATED JSON
    };
} // KerML::Entities
