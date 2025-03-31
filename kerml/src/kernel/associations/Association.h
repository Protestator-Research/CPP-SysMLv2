//
// Created by Moritz Herzog on 25.03.25.
//

#ifndef SYSMLV2_ASSOCIATION_H
#define SYSMLV2_ASSOCIATION_H

#include <core/classifiers/Classifier.h>
#include <root/elements/Relationship.h>

namespace KerML::Entities {
    class Association : public Classifier, Relationship{

    };
}

#endif //SYSMLV2_ASSOCIATION_H
