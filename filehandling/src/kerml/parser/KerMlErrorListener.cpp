//
// Created by Moritz Herzog on 08.04.25.
//

#include <kerml/parser/KerMlErrorListener.h>
#include <kerml/ErrorTypes.h>

#include <sysmlv2/parser/KeywordMisuseDiagnoser.h>

KerMLErrorListener::KerMLErrorListener() {

}

void KerMLErrorListener::syntaxError(antlr4::Recognizer *recognizer, antlr4::Token *offendingSymbol, size_t line,
                                     size_t charPositionInLine, const std::string &msg, std::exception_ptr ) {
    // A keyword misuse is reported instead of the message of the parser; the follow-up errors of its statement are dropped.
    auto decision = Filter.onSyntaxError(recognizer, offendingSymbol);
    if (decision.What == SysMLv2::Files::KeywordMisuseFilter::Kind::Suppressed) return;
    if (decision.What == SysMLv2::Files::KeywordMisuseFilter::Kind::Misuse) {
        SyntaxErrors.resize(SyntaxErrors.size() - decision.DropPlain);
        SyntaxErrors.push_back(std::make_shared<KerMLError>(KerML::Parser::KEYWORD_MISUSE, decision.Misuse.line, decision.Misuse.column, decision.Misuse.message));
        return;
    }
    SyntaxErrors.push_back(std::make_shared<KerMLError>(KerML::Parser::SYNTAX_ERROR,line,charPositionInLine,msg));
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
