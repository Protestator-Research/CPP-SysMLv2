#pragma once

#include <kerml/kerml_global.h>
#include <kerml/kernel/assiciations/Association.h>
#include <kerml/kernel/behaviors/Behavior.h>

namespace KerML::Entities {
    class KERML_EXPORT Interaction : public virtual Association, public virtual Behavior {
    public:
        virtual ~Interaction() = default;
    };
}
