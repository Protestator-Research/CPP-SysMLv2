#pragma once

#include <kerml/kerml_global.h>
#include <kerml/kernel/structures/Structure.h>
#include <kerml/kernel/assiciations/Association.h>

namespace KerML::Entities {
    class KERML_EXPORT AssociationStructure : public virtual Structure, public virtual Association {
    public:
        virtual ~AssociationStructure() = default;
    };
}
