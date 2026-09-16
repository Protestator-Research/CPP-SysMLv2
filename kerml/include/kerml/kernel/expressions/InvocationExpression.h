#pragma once

#include <kerml/kerml_global.h>
#include <kerml/kernel/expressions/InstantiationExpression.h>

namespace KerML::Entities {
    class KERML_EXPORT InvocationExpression : public virtual InstantiationExpression {
    public:
        virtual ~InvocationExpression() = default;
    };
}
