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
		Multiplicity() = delete;
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
    };
}

