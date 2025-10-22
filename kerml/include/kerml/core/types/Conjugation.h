//
// Created by Moritz Herzog on 25.03.25.
//

#pragma once


#include <kerml/root/elements/Relationship.h>

namespace KerML::Entities {
    class Type;

    /**
     * @class Conjungation
     * @brief Defines the conjungation relationship.
     * @version 1.0 Beta 4
     * @author Moritz Herzog <herzogm@rptu.de>
     */
    class Conjungation : public Relationship{
    public:
	    /**
	     * Default Constructor is deleted, because this would allow for a configuration, that is not allowed by the standard.
	     */
	    Conjungation() = delete;
	    /**
	     * Constructor for the Conjungation. This is required considering the Standard
	     * @param originalType The provided Type, that was original
	     * @param conjugatedType The conjugated type, that is resulting
	     */
	    Conjungation(std::shared_ptr<Type> originalType, std::shared_ptr<Type> conjugatedType);
        ~Conjungation() override = default;

        std::shared_ptr<Type> originalType();
        void setOrginalType(std::shared_ptr<Type> originalType);

        std::shared_ptr<Type> conjungatedType();
        void setConjungatedType(std::shared_ptr<Type> conjungatedType);

    protected:
        std::shared_ptr<Type> owningType();
        void setOwningType(std::shared_ptr<Type> owningType);

    private:
        std::shared_ptr<Type> OriginalType;
        std::shared_ptr<Type> ConjugatedType;

        std::shared_ptr<Type> OwningType;

    };
}
