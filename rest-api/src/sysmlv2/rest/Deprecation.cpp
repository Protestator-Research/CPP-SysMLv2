//---------------------------------------------------------
// External Classes
//---------------------------------------------------------
#include <iostream>
#include <mutex>
#include <set>
//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include <sysmlv2/rest/Deprecation.h>
//---------------------------------------------------------

namespace SysMLv2::REST {
    namespace {
        std::mutex& warningMutex() {
            static auto* mutex = new std::mutex();
            return *mutex;
        }

        std::set<std::string>& printedWarnings() {
            // Intentionally leaked, so that warnings during static destruction stay safe.
            static auto* printed = new std::set<std::string>();
            return *printed;
        }
    }

    void warnDeprecated(const std::string& what, const std::string& replacement) {
        const std::string message = "[SysMLv2 REST] Deprecated: " + what + " is from an older library version. Use " +
                                    replacement + " instead.";
        std::lock_guard<std::mutex> lock(warningMutex());
        if (printedWarnings().insert(message).second)
            std::cerr << message << std::endl;
    }

    void resetDeprecationWarningsForTesting() {
        std::lock_guard<std::mutex> lock(warningMutex());
        printedWarnings().clear();
    }
}
