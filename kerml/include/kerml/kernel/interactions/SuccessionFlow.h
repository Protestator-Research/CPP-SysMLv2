#pragma once

#include <kerml/kerml_global.h>
#include <kerml/kernel/connectors/Succession.h>
#include <kerml/kernel/interactions/Flow.h>

namespace KerML::Entities {
    class KERML_EXPORT SuccessionFlow : public virtual Succession, public virtual Flow {
    public:
        virtual ~SuccessionFlow() = default;
    };
}
