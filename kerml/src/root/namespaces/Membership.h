//
// Created by Moritz Herzog on 25.03.25.
//

#ifndef SYSMLV2_MEMBERSHIP_H
#define SYSMLV2_MEMBERSHIP_H

#include "../elements/Relationship.h"
#include "VisibilityKind.h"

namespace KerML::Entities {
    class Membership : public Relationship {
    public:
        Membership();
        ~Membership();

        VisibilityKind visibility();

    };
} // KerML::Entities

#endif //SYSMLV2_MEMBERSHIP_H
