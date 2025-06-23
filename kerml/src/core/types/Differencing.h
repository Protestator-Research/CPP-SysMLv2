//
// Created by Moritz Herzog on 25.03.25.
//

#ifndef SYSMLV2_DIFFERENCING_H
#define SYSMLV2_DIFFERENCING_H

#include <root/elements/Relationship.h>

namespace KerML::Entities {
    class Type;

    /**
     * @class Differencing
     * @version 1.0 Beta 4
     */
    class Differencing : public Relationship{
    public:
        Differencing() = delete;
        Differencing(std::shared_ptr<Type> typeDifferenced, std::shared_ptr<Type> differencingType);
        ~Differencing() override = default;

        std::shared_ptr<Type> differencingType();
        void setDifferencingType(std::shared_ptr<Type> differencingType);

    protected:
        std::shared_ptr<Type> typeDifferenced();
        void setTypeDifferenced(std::shared_ptr<Type> typeDifferenced);

    private:
        std::shared_ptr<Type> TypeDifferenced;
        std::shared_ptr<Type> DifferencingType;
    };
}


#endif //SYSMLV2_DIFFERENCING_H
