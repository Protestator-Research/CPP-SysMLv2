#pragma once

#include <sysmlv2/evaluation/sysmlv2evaluation_global.h>

#include <kerml/root/elements/Element.h>

#include <memory>
#include <string>

namespace SysMLv2::Evaluation {

    /**
     * The qualified name of an element in the textual notation, for example `DataFunctions::'+'`: the escaped names (see
     * KerML::Names::escapeName) of the namespaces that own the element and of the element itself, joined with `::`.
     *
     * Element::qualifiedName() is only set for some models (it is not for models parsed from text), so the name is computed from the
     * ownership chain (Element::owner()); relationships on the chain (memberships) are skipped, and so is the root namespace of a
     * source (an owner-less element that is exactly a Namespace). An element without a name contributes `<unnamed>`; if that
     * happens and Element::qualifiedName() is set, that name is returned unchanged instead.
     */
    [[nodiscard]] SYSMLV2EVALUATION_EXPORT std::string qualifiedNameOf(const KerML::Entities::Element& element);

    /// Same as above for a pointer; the empty string for nullptr.
    [[nodiscard]] SYSMLV2EVALUATION_EXPORT std::string qualifiedNameOf(const std::shared_ptr<KerML::Entities::Element>& element);
}
