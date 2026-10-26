//
// Created by Moritz Herzog on 25.03.25.
//

#pragma once

#include <kerml/core/features/Subsetting.h>

namespace KerML::Entities {
	class Feature;
	/**
	 * @class ReferenceSubsetting
	 * @author Moritz Herzog <herzogm@rptu.de>
	 * @version 1.0 Beta 4
	 * 
	 */
	class KERML_EXPORT ReferenceSubsetting : public Subsetting {
        friend struct ::KerML::Entities::ElementDisposer;
	public:
		ReferenceSubsetting() = delete;
		ReferenceSubsetting(std::shared_ptr<Feature> referencedFeature, std::shared_ptr<Feature> referencingFeature);
		~ReferenceSubsetting() override = default;

		std::shared_ptr<Feature> referencedFeature() const;
		void setReferencedFeature(std::shared_ptr<Feature> referencedFeature);

	public:
		std::shared_ptr<Feature> referencingFeature() const;
		void setReferencingFeature(std::shared_ptr<Feature> referencingFeautre);

	private:
		std::shared_ptr<Feature> ReferencedFeature;
		std::shared_ptr<Feature> ReferencingFeature;


    // BEGIN GENERATED JSON (kerml/tools/generate_json.py): do not edit, run the script instead.
    public:
        /**
         * Creates a ReferenceSubsetting either from its JSON representation (if the string starts with '{') or with the given declared name.
         * Reading JSON only stores the ids of the referenced elements, see Element::resolveJsonReferences(). The type of the object stays "ReferenceSubsetting".
         * @param nameOrJson The JSON representation of the ReferenceSubsetting, or its declared name.
         */
        explicit ReferenceSubsetting(const std::string& nameOrJson);

        /**
         * Serializes the ReferenceSubsetting to JSON: all properties of the metaclass (stored and derived ones). References to other elements are
         * only written as identities ({"@id": "<uuid>"}), never recursively.
         * @return The JSON representation of the ReferenceSubsetting.
         */
        std::string serializeToJson() override;

        /**
         * Resolves the references that were read from JSON to the elements (see Element::resolveJsonReferences()), for the properties
         * of ReferenceSubsetting and of its base classes.
         * @param lookup Returns the element of an element id, or an empty pointer if it is not known.
         */
        void resolveJsonReferences(const std::function<std::shared_ptr<Element>(const boost::uuids::uuid&)>& lookup) override;

    protected:
        /**
         * Populates the ReferenceSubsetting from its JSON representation; the stored properties of ReferenceSubsetting and of its base classes are read,
         * computed derived properties are ignored, the derived references that the model keeps as collections are read like the stored ones,
         * and references are only stored as ids.
         * @param jsonString The JSON representation of the ReferenceSubsetting.
         */
        void deserializeAndPopulate(const std::string& jsonString) override;
    // END GENERATED JSON
    };
}
