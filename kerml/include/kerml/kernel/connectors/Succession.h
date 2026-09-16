#pragma once

#include <kerml/kerml_global.h>
#include <kerml/kernel/connectors/Connector.h>

namespace KerML::Entities {
    class KERML_EXPORT Succession : public virtual Connector {
    public:
        virtual ~Succession() = default;
    };
}
