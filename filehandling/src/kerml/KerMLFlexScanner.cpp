#include "KerMLFlexScanner.h"

KerMLFlexScanner::KerMLFlexScanner(std::istream* in, std::ostream* out)
  : yyFlexLexer(in, out) {}

KerML::Parser::parser::symbol_type KerMLFlexScanner::yylex() {
  return KerML::Parser::parser::token::make_KEYWORD_AND();
}
