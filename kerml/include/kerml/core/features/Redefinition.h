//
// Created by Moritz Herzog on 25.03.25.
//

#pragma once

#include <kerml/core/features/Subsetting.h>

namespace KerML::Entities {
	class Feature;
	/**
	 * @class Redefinition
	 * @version 1.0 Beta 4
	 * 
	 */
	class KERML_EXPORT Redefinition : public Subsetting{
        friend struct ::KerML::Entities::ElementDisposer;
    public:
        Redefinition() = delete;
		Redefinition(std::shared_ptr<Feature> redefinedFeature, std::shared_ptr<Feature> redefiningFeature);
		~Redefinition() override = default;

		std::shared_ptr<Feature> redefinedFeature() const;
		void setRedefinedFeature(std::shared_ptr<Feature> redefinedFeature);

		std::shared_ptr<Feature> redefiningFeature() const;
		void setRedefiningFeature(std::shared_ptr<Feature> redefiningFeature);

    private:
		std::shared_ptr<Feature> RedefinedFeature;
		std::shared_ptr<Feature> RedefiningFeature;

    // BEGIN GENERATED JSON (kerml/tools/generate_json.py): do not edit, run the script instead.
    public:
        /**
         * Creates a Redefinition either from its JSON representation (if the string starts with '{') or with the given declared name.
         * Reading JSON only stores the ids of the referenced elements, see Element::resolveJsonReferences(). The type of the object stays "Redefinition".
         * @param nameOrJson The JSON representation of the Redefinition, or its declared name.
         */
        explicit Redefinition(const std::string& nameOrJson);

        /**
         * Serializes the Redefinition to JSON: all properties of the metaclass (stored and derived ones). References to other elements are
         * only written as identities ({"@id": "<uuid>"}), never recursively.
         * @return The JSON representation of the Redefinition.
         */
        std::string serializeToJson() override;

        /**
         * Resolves the references that were read from JSON to the elements (see Element::resolveJsonReferences()), for the properties
         * of Redefinition and of its base classes.
         * @param lookup Returns the element of an element id, or an empty pointer if it is not known.
         */
        void resolveJsonReferences(const std::function<std::shared_ptr<Element>(const boost::uuids::uuid&)>& lookup) override;

    protected:
        /**
         * Populates the Redefinition from its JSON representation; the stored properties of Redefinition and of its base classes are read,
         * computed derived properties are ignored, the derived references that the model keeps as collections are read like the stored ones,
         * and references are only stored as ids.
         * @param jsonString The JSON representation of the Redefinition.
         */
        void deserializeAndPopulate(const std::string& jsonString) override;
    // END GENERATED JSON
    };
}

