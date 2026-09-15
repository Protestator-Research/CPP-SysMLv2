#pragma once

#include <kerml/kerml_global.h>
#include <kerml/core/classifiers/Classifier.h>
#include <kerml/root/elements/Relationship.h>

namespace KerML::Entities {
    class KERML_EXPORT Association : public virtual Classifier, public virtual Relationship {
    public:
        virtual ~Association() = default;
    };
}
