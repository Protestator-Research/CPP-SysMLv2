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
#include <../types/Specialization.h>
//---------------------------------------------------------
// Forwarding
//---------------------------------------------------------
namespace KerML::Entities
{
	class Classifier;
}
//---------------------------------------------------------
namespace KerML::Entities {
	/**
     * @class Classifier
     * @version 1.0 Beta 4
     * @author Moritz Herzog
     * @brief Representation of the Abstract Syntax of the Subclassification.
	 */
	class Subclassification : public Specialization
	{
	public:
		/**
		 * Constuctor is deleted, bacause considering the standard the Elements are required by eaech Subclassification.
		 */
		Subclassification() = delete;
		/**
		 * Constructor that requries the superclassifier and subclassifier.
		 * @param superclassifier Sets the superclassifier of the given object.
		 * @param subclassifier Sets the subclassifier of the given object.
		 */
		Subclassification(std::shared_ptr<Classifier> superclassifier, std::shared_ptr<Classifier> subclassifier);

		/**
		 * Gives access to the superclassifier.
		 * @return A shared pointer to the Superclassifier object.
		 */
		std::shared_ptr<Classifier> superclassifier() const;
		/**
		 * Sets the superclassifier. In this method the given superclassifier is checked if it is a nullpointer. If it is to be found as a nullpointer, the object is not set.
		 * @param superclassifier A shared pointer of the Superclassifier.
		 */
		void setSuperclassifier(std::shared_ptr<Classifier> superclassifier);

		/**
		 * Gives Access to the subclassifier object.
		 * @return A shared pointer to the subclassifier object.
		 */
		std::shared_ptr<Classifier> subclassifier() const;
		/**
		 * Sets the subclassifier of the given object.
		 * @param subclassifier A shared pointer of the subclassifier.
		 */
		void setSubclassifier(std::shared_ptr<Classifier> subclassifier);

	protected:
		/**
		 * 
		 * @return 
		 */
		std::optional<std::shared_ptr<Classifier>> owningClassifier() const;
		/**
		 * 
		 * @param owningClassifier 
		 */
		void setOwningClassifier(std::optional<std::shared_ptr<Classifier>> owningClassifier);
	private:
		std::shared_ptr<Classifier> Superclassifier;
		std::shared_ptr<Classifier> Subclassifier;
		std::shared_ptr<Classifier> OwningClassifier;


    };
}
