//
// Created by Moritz Herzog on 15.05.25.
//

#ifndef SYSML_KERMLFLEXSCANNER_H
#define SYSML_KERMLFLEXSCANNER_H

#if !defined(yyFlexLexerOnce)
#undef YY_DECL
# define YY_DECL KerML::Parser::parser::symbol_type KerMLFlexScanner::yylex ()
#include <FlexLexer.h>
#endif

#include "KerMLBisonParser.h"

    
class KerMLFlexScanner : public yyFlexLexer {
public:
    KerMLFlexScanner(std::istream* in = nullptr, std::ostream* out = nullptr);

    KerML::Parser::parser::symbol_type yylex() override;

    KerML::Parser::parser::symbol_type make_BASIC_NAME(const std::string &s);
    KerML::Parser::parser::symbol_type make_NUMBER(const std::string &s);
    KerML::Parser::parser::symbol_type make_UNRESTRICTED_NAME(const std::string &s);
    KerML::Parser::parser::symbol_type make_DECIMAL_VALUE(const std::string &s);
    KerML::Parser::parser::symbol_type make_EXPONENTIAL_VALUE(const std::string &s);
    KerML::Parser::parser::symbol_type make_SINGLE_LINE_COMMENT(const std::string &s);
    KerML::Parser::parser::symbol_type make_BLOCK_COMMENT(const std::string &s);
    KerML::Parser::parser::symbol_type make_STRING(const std::string &s);
};

#endif //SYSML_KERMLFLEXSCANNER_H
