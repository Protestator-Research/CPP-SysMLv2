//
// Created by Moritz Herzog on 25.03.25.
//
//---------------------------------------------------------
// Constants, Definitions, Pragmas
//---------------------------------------------------------
#ifndef SYSMLV2_VISIBILITYKIND_H
#define SYSMLV2_VISIBILITYKIND_H
//---------------------------------------------------------
// External Classes
//---------------------------------------------------------

//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include "../../kerml_global.h"
//---------------------------------------------------------
// Forwarding
//---------------------------------------------------------

namespace KerML::Entities {
    /**
     * @class VisibilityKind
     * @author Moritz Herzog
     * @version 1.0 Beta 2
     *
     *
     */
    enum KERML_EXPORT VisibilityKind {
        PRIVATE,
        PROTECTED,
        PUBLIC
    };
} // KerML::Enitties

#endif //SYSMLV2_VISIBILITYKIND_H
