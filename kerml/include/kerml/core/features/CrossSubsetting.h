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
	class CrossSubsetting : public Subsetting
	{
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

	protected:
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

	private:
		std::shared_ptr<Feature> CrossedFeature;
		std::shared_ptr<Feature> CrossingFeature;
	};
}