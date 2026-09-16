#pragma once

#include <kerml/kerml_global.h>
#include <kerml/core/classifiers/Classifier.h>

namespace KerML::Entities {
    class KERML_EXPORT DataType : public virtual Classifier {
    public:
        virtual ~DataType() = default;
    };
}
