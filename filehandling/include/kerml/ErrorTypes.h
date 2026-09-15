#pragma once

#include <sysmlv2/sysmlv2file_global.h>

namespace KerML::Parser {
    enum SYSMLV2FILE_EXPORT ErrorTypes {
        SYNTAX_ERROR,
        AMBIGUITY_ERROR,
        CONTEXT_SENSITIVITY_ERROR,
        ATTEMPTING_FULL_CONTEXT_ERROR
    };
}