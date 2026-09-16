#pragma once

#include <kerml/kerml_global.h>
#include <kerml/kernel/connectors/Connector.h>
#include <kerml/kernel/behaviors/Step.h>

namespace KerML::Entities {
    class KERML_EXPORT Flow : public virtual Connector, public virtual Step {
    public:
        virtual ~Flow() = default;
    };
}
