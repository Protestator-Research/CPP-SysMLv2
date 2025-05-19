#include "KerMLFlexScanner.h"

KerMLFlexScanner::KerMLFlexScanner(std::istream* in, std::ostream* out)
  : yyFlexLexer(in, out) {}

KerML::Parser::parser::symbol_type KerMLFlexScanner::make_BASIC_NAME(const std::string &s){

}

KerML::Parser::parser::symbol_type KerMLFlexScanner::make_NUMBER(const std::string &s){

}

KerML::Parser::parser::symbol_type KerMLFlexScanner::make_UNRESTRICTED_NAME(const std::string &s){

}

KerML::Parser::parser::symbol_type KerMLFlexScanner::make_DECIMAL_VALUE(const std::string &s){

}

KerML::Parser::parser::symbol_type KerMLFlexScanner::make_EXPONENTIAL_VALUE(const std::string &s){

}

KerML::Parser::parser::symbol_type KerMLFlexScanner::make_SINGLE_LINE_COMMENT(const std::string &s){

}

KerML::Parser::parser::symbol_type KerMLFlexScanner::make_BLOCK_COMMENT(const std::string &s){

}

KerML::Parser::parser::symbol_type KerMLFlexScanner::make_STRING(const std::string &s){

}