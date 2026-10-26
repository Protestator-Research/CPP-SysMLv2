//
// Created by Moritz Herzog on 25.03.25.
//
//---------------------------------------------------------
// Constants, Definitions, Pragmas
//---------------------------------------------------------
#pragma once
//---------------------------------------------------------
// External Classes
//---------------------------------------------------------

//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include <kerml/core/features/Subsetting.h>
//---------------------------------------------------------
// Forwarding
//---------------------------------------------------------
namespace KerML::Entities
{
	class Feature;
}
//---------------------------------------------------------

namespace KerML::Entities {
	/**
	 * @class CrossSubsetting
	 * @version 1.0 Beta 4
	 * @author Moritz Herzog
	 * @brief Representation of the CrossSubsetting
	 */
	class KERML_EXPORT CrossSubsetting : public Subsetting
	{
        friend struct ::KerML::Entities::ElementDisposer;
	public:
		/**
		 * Constructor is deleted, because the standard requires to have a crossing feature and crossed feature;
		 */
		CrossSubsetting() = delete;

		/**
		 * Constructor for Crossed Feature
		 * @param crossedFeature The required parameter is the crossed feature.
		 * @param crossingFeature The required parameter is the crossing feature.
		 */
		CrossSubsetting(std::shared_ptr<Feature> crossedFeature, std::shared_ptr<Feature> crossingFeature);

		/**
		 * Sets the crossed feature of the CrossSubsetting.
		 * @param crossedFeature
		 */
		void setCrossedFeature(std::shared_ptr<Feature> crossedFeature);
		/**
		 * 
		 * @return 
		 */
		std::shared_ptr<Feature> crossedFeature();

	public:
        /**
         *
         * @param crossingFeautre
         */
		void setCrossingFeature(std::shared_ptr<Feature> crossingFeautre);
		/**
		 *
		 * @return
		 */
        std::shared_ptr<Feature> crossingFeatures();
        std::shared_ptr<Feature> crossingFeature() { return crossingFeatures(); }

	private:
		std::shared_ptr<Feature> CrossedFeature;
		std::shared_ptr<Feature> CrossingFeature;

    // BEGIN GENERATED JSON (kerml/tools/generate_json.py): do not edit, run the script instead.
    public:
        /**
         * Creates a CrossSubsetting either from its JSON representation (if the string starts with '{') or with the given declared name.
         * Reading JSON only stores the ids of the referenced elements, see Element::resolveJsonReferences(). The type of the object stays "CrossSubsetting".
         * @param nameOrJson The JSON representation of the CrossSubsetting, or its declared name.
         */
        explicit CrossSubsetting(const std::string& nameOrJson);

        /**
         * Serializes the CrossSubsetting to JSON: all properties of the metaclass (stored and derived ones). References to other elements are
         * only written as identities ({"@id": "<uuid>"}), never recursively.
         * @return The JSON representation of the CrossSubsetting.
         */
        std::string serializeToJson() override;

        /**
         * Resolves the references that were read from JSON to the elements (see Element::resolveJsonReferences()), for the properties
         * of CrossSubsetting and of its base classes.
         * @param lookup Returns the element of an element id, or an empty pointer if it is not known.
         */
        void resolveJsonReferences(const std::function<std::shared_ptr<Element>(const boost::uuids::uuid&)>& lookup) override;

    protected:
        /**
         * Populates the CrossSubsetting from its JSON representation; the stored properties of CrossSubsetting and of its base classes are read,
         * computed derived properties are ignored, the derived references that the model keeps as collections are read like the stored ones,
         * and references are only stored as ids.
         * @param jsonString The JSON representation of the CrossSubsetting.
         */
        void deserializeAndPopulate(const std::string& jsonString) override;
    // END GENERATED JSON
	};
}