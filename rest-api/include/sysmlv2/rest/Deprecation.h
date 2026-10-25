//---------------------------------------------------------
// Constants, Definitions, Pragmas
//---------------------------------------------------------
#pragma once
//---------------------------------------------------------
// External Classes
//---------------------------------------------------------
#include <string>
//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include <sysmlv2/rest/sysmlv2rest_global.h>
//---------------------------------------------------------

namespace SysMLv2::REST {
    /**
     * Tells the user on std::cerr that an API or a JSON format of an older version of the library is used:
     * "[SysMLv2 REST] Deprecated: <what> is from an older library version. Use <replacement> instead."
     * Every distinct message is printed only once per process. The function is thread safe.
     * @param what The deprecated API or JSON field.
     * @param replacement The API or JSON field that replaces it.
     */
    SYSMLV2REST_EXPORT void warnDeprecated(const std::string& what, const std::string& replacement);

    /**
     * Forgets which messages were already printed, so that they are printed again. Intended for tests.
     */
    SYSMLV2REST_EXPORT void resetDeprecationWarningsForTesting();
}
