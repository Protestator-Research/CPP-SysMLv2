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
    class Classifier : public Type
	{
    public:
	    /**
	     * Constructor, with default values to be initialied
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
	     */
	    explicit Classifier(std::string classifierName, boost::uuids::uuid elementID = boost::uuids::random_generator()(), std::shared_ptr<Element> owner = nullptr);

	    /**
	     * Destructor
	     */
	    ~Classifier() override = default;

    protected:
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
    };
}
