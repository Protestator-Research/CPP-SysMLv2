#pragma once

#include <cstdint>
#include <memory>
#include <optional>
#include <string>
#include <string_view>
#include <span>
#include <utility>
#include <vector>
#include <sysml/sysml_global.h>

namespace SysMLv2::Entities {
struct RepresentationIssue {
    std::string property;
    std::string message;
};

/// Common interface of the SysML abstract representation.
/// This checks stored data, not the OCL semantic constraints of SysML.
class SYSML_EXPORT Representation {
public:
    virtual ~Representation() = default;
    virtual std::string_view metaclassName() const noexcept = 0;
    virtual std::vector<RepresentationIssue> validateRepresentation(bool includeDerived = false) const = 0;
};
struct MetaclassDescriptor {
    std::string_view name;
    std::string_view package;
    bool isAbstract;
    std::size_t declaredPropertyCount;
};

/// Stable inventory of all SysML classes; no RTTI name parsing is required.
SYSML_EXPORT std::span<const MetaclassDescriptor> metaclasses() noexcept;
/// Rejects unknown names and abstract metaclasses with std::invalid_argument.
SYSML_EXPORT std::shared_ptr<Representation> createRepresentation(std::string_view name);
}
