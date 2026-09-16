#pragma once

#include <kerml/kerml_global.h>
#include <kerml/core/features/Feature.h>

namespace KerML::Entities {
    class KERML_EXPORT Step : public virtual Feature {
    public:
        virtual ~Step() = default;
    };
}
