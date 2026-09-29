//
// Implicit generalizations (KerML 9.2 / SysML v2 8.x "default generalization"): the library elements a model element
// specializes when its declaration names no general type. (Private header of the sysmlv2parser library.)
//
#pragma once

#include <kerml/root/elements/Element.h>

#include <vector>

namespace SysMLv2::Files::Detail {

    /**
     * The qualified names of the standard library elements that @p element implicitly specializes, most specific first
     * (for example a PartUsage: Parts::parts, Items::items, Occurrences::occurrences, Base::things). Every type
     * specializes Base::Anything and every feature Base::things at least.
     * The names are only names: whether the library that defines them is loaded is decided by the resolver.
     */
    std::vector<const char*> implicitGenerals(const KerML::Entities::Element* element);
}
