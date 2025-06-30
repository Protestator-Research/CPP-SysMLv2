//
// Created by Moritz Herzog on 25.03.25.
//

#pragma once

#include <root/elements/Relationship.h>

namespace KerML::Entities {
    class Type;

    /**
     * @class Unioning
     * @version 1.0 Beta 4
     * 
     */
    class Unioning  : public Relationship {
    public:
        Unioning() = delete;

        Unioning(std::shared_ptr<Type> typeUnioned, std::shared_ptr<Type> unioningType);
        ~Unioning() override = default;

        std::shared_ptr<Type> typeUnioned();
        void setTypeUnioned(std::shared_ptr<Type> typeUnioned);

        std::shared_ptr<Type> unioningType();
        void setUnioningType(std::shared_ptr<Type> unioningType);

    private:
        std::shared_ptr<Type> TypeUnionioned;
        std::shared_ptr<Type> UnioningType;
    };
}

