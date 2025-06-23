//
// Created by Moritz Herzog on 25.03.25.
//

#ifndef SYSMLV2_SPECIALIZATION_H
#define SYSMLV2_SPECIALIZATION_H

#include <root/elements/Relationship.h>

namespace KerML::Entities {
    class Type;

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
        ~Specialization() override = default;

        std::shared_ptr<Type> general() const;
        void setGeneral(std::shared_ptr<Type> general);

        std::shared_ptr<Type> specific() const;
        void setSpecific(std::shared_ptr<Type> specific);

    private:
        std::shared_ptr<Type> General;
        std::shared_ptr<Type> Specific;
    };
}

#endif //SYSMLV2_SPECIALIZATION_H
