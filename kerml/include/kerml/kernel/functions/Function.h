#pragma once

#include <kerml/kerml_global.h>
#include <kerml/kernel/behaviors/Behavior.h>

namespace KerML::Entities {
    class KERML_EXPORT Function : public virtual Behavior {
    public:
        virtual ~Function() = default;
    };
}
