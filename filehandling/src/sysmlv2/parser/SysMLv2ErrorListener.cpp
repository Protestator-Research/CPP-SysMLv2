//
// Created by Moritz Herzog on 08.04.25.
//

#include <sysmlv2/parser/SysMLv2ErrorListener.h>
#include <kerml/ErrorTypes.h>

SysMLErrorListenener::SysMLErrorListenener() {

}

void SysMLErrorListenener::syntaxError(antlr4::Recognizer *, antlr4::Token *, size_t line,
                                     size_t charPositionInLine, const std::string &msg, std::exception_ptr ) {
    SyntaxErrors.push_back(std::make_shared<SysMLError>(KerML::Parser::SYNTAX_ERROR,line,charPositionInLine,msg));
}

void SysMLErrorListenener::reportAttemptingFullContext(antlr4::Parser *, const antlr4::dfa::DFA &,
                                                     size_t , size_t ,
                                                     const antlrcpp::BitSet &,
                                                     antlr4::atn::ATNConfigSet *) {
}

void SysMLErrorListenener::reportAmbiguity(antlr4::Parser *, const antlr4::dfa::DFA &, size_t ,
                                         size_t , bool , const antlrcpp::BitSet &,
                                         antlr4::atn::ATNConfigSet *) {
}

void
SysMLErrorListenener::reportContextSensitivity(antlr4::Parser *, const antlr4::dfa::DFA &, size_t ,
                                             size_t , size_t , antlr4::atn::ATNConfigSet *) {
}

std::vector<std::shared_ptr<SysMLError>> SysMLErrorListenener::getSyntaxErrors() const {
    return SyntaxErrors;
}
