//
// Created by Moritz Herzog on 25.03.25.
//

#pragma once


#include <kerml/core/features/Feature.h>
#include <kerml/kerml_global.h>

namespace KerML::Entities {
	/**
	 * @class Multiplicity
	 * @version 1.0
	 * @author Moritz Herzog <herzogm@rptu.de>
	 * @brief Represents the Multiplicity Elements of a KerML Classifier.
	 * Since the is only rare documentation for the multiplicity, this is a interpretation of the standard.
	 */
	class KERML_EXPORT Multiplicity : public Feature {
    public:
		Multiplicity() : Multiplicity(0u, true) {}
		Multiplicity(unsigned minimum);
		Multiplicity(unsigned minimum, unsigned maximum);
		Multiplicity(unsigned minimum, bool unlimited);
		~Multiplicity() = default;

		unsigned minimum() const;
		void setMinimum(unsigned minimum);
		unsigned maximum() const;
		void setMaximum(unsigned maximum);
		bool isUnlimited() const;
		void setIsUnlimited(bool isUnlimited);
		
    private:
        unsigned MinimumNumber;
        unsigned MaximumNumber;

    // BEGIN GENERATED JSON (kerml/tools/generate_json.py): do not edit, run the script instead.
    public:
        /**
         * Creates a Multiplicity either from its JSON representation (if the string starts with '{') or with the given declared name.
         * Reading JSON only stores the ids of the referenced elements, see Element::resolveJsonReferences(). The type of the object stays "Multiplicity".
         * @param nameOrJson The JSON representation of the Multiplicity, or its declared name.
         */
        explicit Multiplicity(const std::string& nameOrJson);

        /**
         * Serializes the Multiplicity to JSON: all properties of the metaclass (stored and derived ones). References to other elements are
         * only written as identities ({"@id": "<uuid>"}), never recursively.
         * @return The JSON representation of the Multiplicity.
         */
        std::string serializeToJson() override;

        /**
         * Resolves the references that were read from JSON to the elements (see Element::resolveJsonReferences()), for the properties
         * of Multiplicity and of its base classes.
         * @param lookup Returns the element of an element id, or an empty pointer if it is not known.
         */
        void resolveJsonReferences(const std::function<std::shared_ptr<Element>(const boost::uuids::uuid&)>& lookup) override;

    protected:
        /**
         * Populates the Multiplicity from its JSON representation; the stored properties of Multiplicity and of its base classes are read,
         * computed derived properties are ignored, the derived references that the model keeps as collections are read like the stored ones,
         * and references are only stored as ids.
         * @param jsonString The JSON representation of the Multiplicity.
         */
        void deserializeAndPopulate(const std::string& jsonString) override;
    // END GENERATED JSON
    };
}

