#pragma once

#include <kerml/kerml_global.h>
#include <kerml/core/classifiers/Classifier.h>

namespace KerML::Entities {
    class KERML_EXPORT Class : public virtual Classifier {
    public:
        virtual ~Class() = default;
    };
}
