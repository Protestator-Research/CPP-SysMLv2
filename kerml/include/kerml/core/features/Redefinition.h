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
	class Redefinition : public Subsetting{
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
    };
}

