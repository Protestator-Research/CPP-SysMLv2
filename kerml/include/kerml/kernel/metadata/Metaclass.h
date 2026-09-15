#pragma once

#include <kerml/kerml_global.h>
#include <kerml/kernel/structures/Structure.h>

namespace KerML::Entities {
    class KERML_EXPORT Metaclass : public virtual Structure {
    public:
        virtual ~Metaclass() = default;
    };
}
