#pragma once

#include <kerml/kerml_global.h>
#include <kerml/kernel/functions/BooleanExpression.h>

namespace KerML::Entities {
    class KERML_EXPORT Invariant : public virtual BooleanExpression {
    public:
        virtual ~Invariant() = default;
    };
}
