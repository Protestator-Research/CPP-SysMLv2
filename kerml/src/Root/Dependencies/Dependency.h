//
// Created by Moritz Herzog on 24.03.25.
//

#ifndef SYSMLV2_DEPENDENCY_H
#define SYSMLV2_DEPENDENCY_H

#include "../Elements/Relationship.h"

namespace KerML::Entities{
    class Dependency : public Relationship{
    public:

    private:
        std::shared_ptr<Element> Client;
        std::shared_ptr<Element> Supplier;
    };
} // KerML::Entities

#endif //SYSMLV2_DEPENDENCY_H
