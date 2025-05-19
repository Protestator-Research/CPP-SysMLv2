//
// Created by Moritz Herzog on 15.05.25.
//

#ifndef SYSML_KERMLFLEXSCANNER_H
#define SYSML_KERMLFLEXSCANNER_H


#include "KerMLBisonParser.h"

#ifndef FLEX_LEXER_H
#define FLEX_LEXER_H
#include <FlexLexer.h>
#endif


    
class KerMLFlexScanner : public yyFlexLexer {
public:
    KerMLFlexScanner(std::istream* in = nullptr, std::ostream* out = nullptr);

    KerML::Parser::parser::symbol_type yylex();
};

#endif //SYSML_KERMLFLEXSCANNER_H
