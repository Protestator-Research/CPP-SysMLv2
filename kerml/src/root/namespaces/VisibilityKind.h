//
// Created by Moritz Herzog on 25.03.25.
//
//---------------------------------------------------------
// Constants, Definitions, Pragmas
//---------------------------------------------------------
#pragma once
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
