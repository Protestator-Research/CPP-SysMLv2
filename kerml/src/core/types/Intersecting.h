//
// Created by Moritz Herzog on 25.03.25.
//

#pragma once

#include <root/elements/Relationship.h>

namespace KerML::Entities {
    class Type;

    /**
     * @class Intersecting
     * @version 1.0 Beta 4
     */
    class Intersecting : public Relationship{
    public:
        Intersecting() = delete;
        Intersecting(std::shared_ptr<Type> typeIntersecting, std::shared_ptr<Type> intersectingType);
        ~Intersecting() override = default;


        std::shared_ptr<Type> intersectingType();
        void setIntersectingType(std::shared_ptr<Type> intersectingType);

    protected:
        std::shared_ptr<Type> typeIntersecting();
        void setTypeIntersecting(std::shared_ptr<Type> typeIntersecting);

    private:
        std::shared_ptr<Type> TypeIntersected;
        std::shared_ptr<Type> IntersectingType;
    };
}
