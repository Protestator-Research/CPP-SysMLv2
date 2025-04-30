//
// Created by Moritz Herzog on 30.04.25.
//

#ifndef SYSML_PARSER_H
#define SYSML_PARSER_H

#include "ParserError.h"
#include <vector>
#include <memory>
#include <utility>

namespace KerML::Entities {
    class Element;
}

namespace SysMLv2::Files {
    class Parser {
    public:
        static std::pair<std::vector<std::shared_ptr<KerML::Entities::Element>>,std::vector<std::shared_ptr<ParserError>>> parseKerML(std::string text);
    };
}


#endif //SYSML_PARSER_H
