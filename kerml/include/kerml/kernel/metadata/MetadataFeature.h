#pragma once

#include <kerml/kerml_global.h>
#include <kerml/root/annotations/AnnotatingElement.h>
#include <kerml/core/features/Feature.h>

namespace KerML::Entities {
    class KERML_EXPORT MetadataFeature : public virtual AnnotatingElement, public virtual Feature {
    public:
        virtual ~MetadataFeature() = default;
    };
}
