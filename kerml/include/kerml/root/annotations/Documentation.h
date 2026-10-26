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
#include <kerml/root/annotations/Comment.h>
#include <kerml/root/elements/Element.h>
//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include <kerml/kerml_global.h>
//---------------------------------------------------------
// Forwarding
//---------------------------------------------------------


namespace KerML::Entities {
	/**
	 * @class Documentation
	 * @author Moritz Herzog
	 * @version 1.0 Beta 3
	 * @brief Abstract representation of the Documentation element.
	 * 
	 */
	class KERML_EXPORT Documentation : public Comment {
        friend struct ::KerML::Entities::ElementDisposer;
    public:
		explicit Documentation(std::shared_ptr<Element> documentedElement = nullptr, std::string locale = "", std::string body = "");

		/**
		 * Keeps Documentation(nullptr) unambiguous next to the constructor that takes a name or JSON: no documented element.
		 */
		Documentation(std::nullptr_t);

        ~Documentation() override = default;

        std::shared_ptr<Element> documentedElement();

        void setDocumentedElement(std::shared_ptr<Element> documentedElement);

    private:
        std::shared_ptr<Element> DocumentedElement;

    // BEGIN GENERATED JSON (kerml/tools/generate_json.py): do not edit, run the script instead.
    public:
        /**
         * Creates a Documentation either from its JSON representation (if the string starts with '{') or with the given declared name.
         * Reading JSON only stores the ids of the referenced elements, see Element::resolveJsonReferences(). The type of the object stays "Documentation".
         * @param nameOrJson The JSON representation of the Documentation, or its declared name.
         */
        explicit Documentation(const std::string& nameOrJson);

        /**
         * Serializes the Documentation to JSON: all properties of the metaclass (stored and derived ones). References to other elements are
         * only written as identities ({"@id": "<uuid>"}), never recursively.
         * @return The JSON representation of the Documentation.
         */
        std::string serializeToJson() override;

        /**
         * Resolves the references that were read from JSON to the elements (see Element::resolveJsonReferences()), for the properties
         * of Documentation and of its base classes.
         * @param lookup Returns the element of an element id, or an empty pointer if it is not known.
         */
        void resolveJsonReferences(const std::function<std::shared_ptr<Element>(const boost::uuids::uuid&)>& lookup) override;

    protected:
        /**
         * Populates the Documentation from its JSON representation; the stored properties of Documentation and of its base classes are read,
         * computed derived properties are ignored, the derived references that the model keeps as collections are read like the stored ones,
         * and references are only stored as ids.
         * @param jsonString The JSON representation of the Documentation.
         */
        void deserializeAndPopulate(const std::string& jsonString) override;
    // END GENERATED JSON
    };
} // KerML::Entities
