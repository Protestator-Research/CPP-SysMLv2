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
#include <root/elements/Relationship.h>
//---------------------------------------------------------
// Forwarding
//---------------------------------------------------------
namespace KerML::Entities
{
    class Type;
}
//---------------------------------------------------------
namespace KerML::Entities {
    /**
     * @class Specialization
     * @brief Displays a Specialization Relation between two types.
     * @version 1.0 Beta 4
     * 
     */
    class Specialization  : public Relationship {
    public:
	    /**
	     * Constructor is deleted, because the standard does not allow for empty.
	     */
	    Specialization() = delete;
	    /**
	     * Constructor for the specialization class. Since the standard does not allow for empty general and specific type.
	     * @param general The type that is specialized by the specific type.
	     * @param specific The type that specializes the general type.
	     */
	    Specialization(std::shared_ptr<Type> general, std::shared_ptr<Type> specific);
	    /**
	     * Destructor
	     */
	    ~Specialization() override = default;

	    /**
	     * Gives access to the general type of the Specialization Relationship. 
	     * @return General Type as shared Pointer.
	     */
	    std::shared_ptr<Type> general() const;
	    /**
	     * This method allows to set the general type for a object.
	     * @param general The general Type given by the KerML Model
	     */
	    void setGeneral(std::shared_ptr<Type> general);

	    /**
	     * Gives access to the specific type.
	     * @return The specific type of the KerML Model as a shared pointer.
	     */
	    std::shared_ptr<Type> specific() const;
	    /**
	     * This method allows to set the specific type of a KerML model.
	     * @param specific The Specifigc Type as a shared_pointer
	     */
	    void setSpecific(std::shared_ptr<Type> specific);

    private:
        std::shared_ptr<Type> General;
        std::shared_ptr<Type> Specific;
    };
}
