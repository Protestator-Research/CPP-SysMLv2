//
// Created by Moritz Herzog on 25.03.25.
//

#ifndef SYSMLV2_DISJOINING_H
#define SYSMLV2_DISJOINING_H

#include <root/elements/Relationship.h>

namespace KerML::Entities {
    class Type;

    /**
     * @class Disjoining
     * @version 1.0 Beta 4
     * @brief 
     * @author Moritz Herzog <herzogm@rptu.de>
     */
    class Disjoining  : public Relationship{
    public:
	    Disjoining() = delete;
	    /**
	     * Constructor of the Element
	     * @param typeDisjoined 
	     * @param disjoiningType 
	     */
	    Disjoining(std::shared_ptr<Type> typeDisjoined, std::shared_ptr<Type> disjoiningType);
    	~Disjoining() override = default;


        std::shared_ptr<Type> typeDisjoined();
        void setTypeDisjoined(std::shared_ptr<Type> typeDisjoined);

        std::shared_ptr<Type> disjoiningType();
        void setDisjoiningType(std::shared_ptr<Type> disjoiningType);

    protected:
        std::shared_ptr<Type> owningType();
        void setOwningType(std::shared_ptr<Type> owningType);

    private:
        std::shared_ptr<Type> TypeDisjoined;
        std::shared_ptr<Type> DisjoiningType;

        std::shared_ptr<Type> OwningType;
    };
}

#endif //SYSMLV2_DISJOINING_H
