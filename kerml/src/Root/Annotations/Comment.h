//
// Created by Moritz Herzog on 24.03.25.
//

#ifndef SYSMLV2_COMMENT_H
#define SYSMLV2_COMMENT_H

#include "AnnotatingElement.h"

#include <string>

namespace KerML::Entities {
    class Comment  : public AnnotatingElement{
    public:

    private:
        std::string Locale;
        std::string Body;
    };
} // KerML::Entities

#endif //SYSMLV2_COMMENT_H
