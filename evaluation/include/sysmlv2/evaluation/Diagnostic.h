#pragma once

#include <sysmlv2/evaluation/Value.h>

#include <memory>
#include <string>
#include <vector>

namespace SysMLv2::Evaluation {

    enum class Severity { Warning, Error };

    /// A message of the evaluation; @c element is the model element that caused it (may be null).
    struct Diagnostic {
        Severity severity = Severity::Error;
        std::string message;
        std::shared_ptr<KerML::Entities::Element> element;
    };

    /// The outcome of an evaluation: the value and the diagnostics that were reported while computing it.
    struct Result {
        Value value;
        std::vector<Diagnostic> diagnostics;
        /// Set if the evaluation failed without a recorded diagnostic (a diagnostic could not be stored). Such a result is not ok.
        bool failed = false;

        /// True if no diagnostic is an Error (warnings do not count) and the evaluation did not fail.
        [[nodiscard]] bool ok() const {
            if (failed) return false;
            for (const Diagnostic& diagnostic : diagnostics) {
                if (diagnostic.severity == Severity::Error) return false;
            }
            return true;
        }
    };
}
