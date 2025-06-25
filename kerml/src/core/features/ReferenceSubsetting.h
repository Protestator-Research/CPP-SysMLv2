//
// Created by Moritz Herzog on 25.03.25.
//

#ifndef SYSMLV2_REFERENCESUBSETTING_H
#define SYSMLV2_REFERENCESUBSETTING_H

#include "Subsetting.h"

namespace KerML::Entities {
	class Feature;
	/**
	 * @class ReferenceSubsetting
	 * @author Moritz Herzog <herzogm@rptu.de>
	 * @version 1.0 Beta 4
	 * 
	 */
	class ReferenceSubsetting : public Subsetting {
	public:
		ReferenceSubsetting() = delete;
		ReferenceSubsetting(std::shared_ptr<Feature> referencedFeature, std::shared_ptr<Feature> referencingFeature);
		~ReferenceSubsetting() override = default;

		std::shared_ptr<Feature> referencedFeature() const;
		void setReferencedFeature(std::shared_ptr<Feature> referencedFeature);

	protected:
		std::shared_ptr<Feature> referencingFeature() const;
		void setReferencingFeature(std::shared_ptr<Feature> referencingFeautre);

	private:
		std::shared_ptr<Feature> ReferencedFeature;
		std::shared_ptr<Feature> ReferencingFeature;

    };
}

#endif //SYSMLV2_REFERENCESUBSETTING_H
