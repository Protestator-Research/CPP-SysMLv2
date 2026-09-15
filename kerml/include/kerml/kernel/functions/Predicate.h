#pragma once

#include <kerml/kerml_global.h>
#include <kerml/kernel/functions/Function.h>

namespace KerML::Entities {
    class KERML_EXPORT Predicate : public virtual Function {
    public:
        virtual ~Predicate() = default;
    };
}
