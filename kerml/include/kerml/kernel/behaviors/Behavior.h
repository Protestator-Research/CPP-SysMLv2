#pragma once

#include <kerml/kerml_global.h>
#include <kerml/kernel/classes/Class.h>

namespace KerML::Entities {
    class KERML_EXPORT Behavior : public virtual Class {
    public:
        virtual ~Behavior() = default;
    };
}
