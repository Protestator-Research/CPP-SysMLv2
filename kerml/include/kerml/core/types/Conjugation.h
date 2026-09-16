//
// Created by Moritz Herzog on 25.03.25.
//

#pragma once


#include <kerml/root/elements/Relationship.h>

namespace KerML::Entities {
    class Type;

    /**
     * @class Conjugation
     * @brief Defines the conjungation relationship.
     * @version 1.0 Beta 4
     * @author Moritz Herzog <herzogm@rptu.de>
     */
    class KERML_EXPORT Conjugation : public Relationship{
    public:
	    /**
	     * Protected construction supports derived representations before their references are populated.
	     */
	    protected:
        // Allow derived representations to be populated before validation.
        Conjugation() = default;
    public:
	    /**
	     * Constructor for the Conjugation. This is required considering the Standard
	     * @param originalType The provided Type, that was original
	     * @param conjugatedType The conjugated type, that is resulting
	     */
	    Conjugation(std::shared_ptr<Type> originalType, std::shared_ptr<Type> conjugatedType);
        ~Conjugation() override = default;

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


namespace KerML::Entities { using Conjungation = Conjugation; }
