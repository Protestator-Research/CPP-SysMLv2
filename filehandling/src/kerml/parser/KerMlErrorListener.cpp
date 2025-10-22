//
// Created by Moritz Herzog on 08.04.25.
//

#include <kerml/parser/KerMlErrorListener.h>

KerMLErrorListener::KerMLErrorListener() {

}

void KerMLErrorListener::syntaxError(antlr4::Recognizer *, antlr4::Token *, size_t line,
                                     size_t charPositionInLine, const std::string &msg, std::exception_ptr ) {
    SyntaxErrors.push_back(std::make_shared<KerMLError>(SYNTAX_ERROR,line,charPositionInLine,msg));
}

void KerMLErrorListener::reportAttemptingFullContext(antlr4::Parser *, const antlr4::dfa::DFA &,
                                                     size_t , size_t ,
                                                     const antlrcpp::BitSet &,
                                                     antlr4::atn::ATNConfigSet *) {
}

void KerMLErrorListener::reportAmbiguity(antlr4::Parser *, const antlr4::dfa::DFA &, size_t ,
                                         size_t , bool , const antlrcpp::BitSet &,
                                         antlr4::atn::ATNConfigSet *) {
}

void
KerMLErrorListener::reportContextSensitivity(antlr4::Parser *, const antlr4::dfa::DFA &, size_t ,
                                             size_t , size_t , antlr4::atn::ATNConfigSet *) {
}

std::vector<std::shared_ptr<KerMLError>> KerMLErrorListener::getSyntaxErrors() const {
    return SyntaxErrors;
}
