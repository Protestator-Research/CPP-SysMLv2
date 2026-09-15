#pragma once

#include <kerml/kerml_global.h>
#include <kerml/kernel/behaviors/Step.h>

namespace KerML::Entities {
    class KERML_EXPORT Expression : public virtual Step {
    public:
        virtual ~Expression() = default;
    };
}
