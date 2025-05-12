//
// Created by Moritz Herzog on 24.03.25.
//

#ifndef SYSMLV2_DEPENDENCY_H
#define SYSMLV2_DEPENDENCY_H

#include <root/elements/Relationship.h>

namespace KerML::Entities{
    /**
     * @class Dependency
     * @author 
     */
    class Dependency : public Relationship{
    public:
        Dependency();
        virtual ~Dependency();
    private:
        std::shared_ptr<Element> Client;
        std::shared_ptr<Element> Supplier;
    };
} // KerML::Entities

#endif //SYSMLV2_DEPENDENCY_H
