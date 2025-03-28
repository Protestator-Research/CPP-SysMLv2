//
// Created by Moritz Herzog on 24.03.25.
//

#ifndef SYSMLV2_TEXTUALREPRESENTATION_H
#define SYSMLV2_TEXTUALREPRESENTATION_H

#include "AnnotatingElement.h"
#include <string>


namespace KerML::Entities {
    class TextualRepresentation : public AnnotatingElement{
    public:

    private:
        std::string Language;
        std::string Body;
    };
} // KerML::Entities

#endif //SYSMLV2_TEXTUALREPRESENTATION_H
