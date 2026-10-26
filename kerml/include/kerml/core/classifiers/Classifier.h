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
#include <kerml/core/types/Type.h>
#include <kerml/kerml_global.h>
//---------------------------------------------------------
// Forwarding
//---------------------------------------------------------
namespace KerML::Entities
{
	class Subclassification;
}
//---------------------------------------------------------
namespace KerML::Entities {
    /**
     * @class Classifier
     * @version 1.0 Beta 4
     * @author Moritz Herzog
     * @brief Representation of the Abstract Syntax of one Classifier.
     * @see Type
     */
    class KERML_EXPORT Classifier : public virtual Type
	{
        friend struct ::KerML::Entities::ElementDisposer;
    public:
	    /**
	     * Constructor, with default values to be initialized
	     * @param elementID The Id of the specific element. This is initialized by a random UUID.
	     * @param owner The owner of the element, given as a shared pointer. By default initialized by a nullptr.
	     * @see boost::uuids::random_generator
	     */
	    explicit Classifier(boost::uuids::uuid elementID = boost::uuids::random_generator()(), std::shared_ptr<Element> owner = nullptr);
	    /**
	     * Constructor, allowing to set a classifier name.
	     * @param classifierName The name of the Classifier, stemming from the Constructor of the Namespace class.
		 * @param elementID The Id of the specific element. This is initialized by a random UUID.
		 * @param owner The owner of the element, given as a shared pointer. By default initialized by a nullptr.
		 * @see KerML::Entities::Namespace
	     * If the string is a JSON object (it starts with '{') it is the JSON representation of the element, see serializeToJson(); otherwise it is the declared name.
	     */
	    explicit Classifier(std::string classifierName, boost::uuids::uuid elementID = boost::uuids::random_generator()(), std::shared_ptr<Element> owner = nullptr);

	    /**
	     * Destructor
	     */
	    ~Classifier() override = default;

        /**
	     * Sets the OwnedSubclassification variable. Be carefull, this might delete all already present OwnedSubclassifications.
	     * @param ownedSubclassification The owned Subclassifications.
	     */
	    void setOwnedSubsclassification(std::vector<std::shared_ptr<Subclassification>> ownedSubclassification);

	    /**
	     * Gives access to the stored OwnedSubclassifications.
	     * @return The OwnedSubclassifications.
	     */
	    std::vector<std::shared_ptr<Subclassification>> ownedSubclassification() const;

	    /**
	     * Appends the given vector the already present ownedSubsclassifications.
	     * @param ownedSubclassification 
	     */
	    void appendOwnedSubclassification(std::vector<std::shared_ptr<Subclassification>> ownedSubclassification);

	    /**
	     * Appends one shared pointer of a subclassification.
	     * @param ownedSubclassification The owned subsclassification
	     */
	    void appendOwnedSubclassification(std::shared_ptr<Subclassification> ownedSubclassification);

    private:
        std::vector<std::shared_ptr<Subclassification>> OwnedSubclassification;

    // BEGIN GENERATED JSON (kerml/tools/generate_json.py): do not edit, run the script instead.
    public:
        /**
         * Serializes the Classifier to JSON: all properties of the metaclass (stored and derived ones). References to other elements are
         * only written as identities ({"@id": "<uuid>"}), never recursively.
         * @return The JSON representation of the Classifier.
         */
        std::string serializeToJson() override;

        /**
         * Resolves the references that were read from JSON to the elements (see Element::resolveJsonReferences()), for the properties
         * of Classifier and of its base classes.
         * @param lookup Returns the element of an element id, or an empty pointer if it is not known.
         */
        void resolveJsonReferences(const std::function<std::shared_ptr<Element>(const boost::uuids::uuid&)>& lookup) override;

    protected:
        /**
         * Populates the Classifier from its JSON representation; the stored properties of Classifier and of its base classes are read,
         * computed derived properties are ignored, the derived references that the model keeps as collections are read like the stored ones,
         * and references are only stored as ids.
         * @param jsonString The JSON representation of the Classifier.
         */
        void deserializeAndPopulate(const std::string& jsonString) override;
    // END GENERATED JSON
    };
}
