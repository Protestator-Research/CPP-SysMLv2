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
#include <kerml/core/types/Specialization.h>
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
	class KERML_EXPORT Subclassification : public Specialization
	{
        friend struct ::KerML::Entities::ElementDisposer;
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

	public:
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



    // BEGIN GENERATED JSON (kerml/tools/generate_json.py): do not edit, run the script instead.
    public:
        /**
         * Creates a Subclassification either from its JSON representation (if the string starts with '{') or with the given declared name.
         * Reading JSON only stores the ids of the referenced elements, see Element::resolveJsonReferences(). The type of the object stays "Subclassification".
         * @param nameOrJson The JSON representation of the Subclassification, or its declared name.
         */
        explicit Subclassification(const std::string& nameOrJson);

        /**
         * Serializes the Subclassification to JSON: all properties of the metaclass (stored and derived ones). References to other elements are
         * only written as identities ({"@id": "<uuid>"}), never recursively.
         * @return The JSON representation of the Subclassification.
         */
        std::string serializeToJson() override;

        /**
         * Resolves the references that were read from JSON to the elements (see Element::resolveJsonReferences()), for the properties
         * of Subclassification and of its base classes.
         * @param lookup Returns the element of an element id, or an empty pointer if it is not known.
         */
        void resolveJsonReferences(const std::function<std::shared_ptr<Element>(const boost::uuids::uuid&)>& lookup) override;

    protected:
        /**
         * Populates the Subclassification from its JSON representation; the stored properties of Subclassification and of its base classes are read,
         * computed derived properties are ignored, the derived references that the model keeps as collections are read like the stored ones,
         * and references are only stored as ids.
         * @param jsonString The JSON representation of the Subclassification.
         */
        void deserializeAndPopulate(const std::string& jsonString) override;
    // END GENERATED JSON
    };
}
