#pragma once

#include <kerml/kerml_global.h>
#include <kerml/core/features/Feature.h>
#include <kerml/root/elements/Relationship.h>

namespace KerML::Entities {
    class KERML_EXPORT Connector : public virtual Feature, public virtual Relationship {
    public:
        virtual ~Connector() = default;
    };
}
