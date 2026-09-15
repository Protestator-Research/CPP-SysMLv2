#pragma once

#include <kerml/kerml_global.h>
#include <kerml/core/features/FeatureMembership.h>

namespace KerML::Entities {
    class KERML_EXPORT ParameterMembership : public virtual FeatureMembership {
    public:
        virtual ~ParameterMembership() = default;
    };
}
