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
#include "Subsetting.h"
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
	 * 
	 */
	class CrossSubsetting : public Subsetting
	{
	public:
		/**
		 * 
		 */
		CrossSubsetting() = delete;

		/**
		 *
		 * @param crossedFeature 
		 * @param crossingFeature 
		 */
		CrossSubsetting(std::shared_ptr<Feature> crossedFeature, std::shared_ptr<Feature> crossingFeature);

		/**
		 * 
		 * @param crossedFeature 
		 */
		void setCrossedFeature(std::shared_ptr<Feature> crossedFeature);
		/**
		 * 
		 * @return 
		 */
		std::shared_ptr<Feature> crossedFeature();

	protected:
		void setCrossingFeature(std::shared_ptr<Feature> crossingFeautre);
		std::shared_ptr<Feature> crossingFeatures();

	private:
		std::shared_ptr<Feature> CrossedFeature;
		std::shared_ptr<Feature> CrossingFeature;
	};
}