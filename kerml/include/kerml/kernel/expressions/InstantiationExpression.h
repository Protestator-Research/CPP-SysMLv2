#pragma once

#include <kerml/kerml_global.h>
#include <kerml/kernel/functions/Expression.h>

namespace KerML::Entities {
    class KERML_EXPORT InstantiationExpression : public virtual Expression {
    public:
        virtual ~InstantiationExpression() = default;
    };
}
