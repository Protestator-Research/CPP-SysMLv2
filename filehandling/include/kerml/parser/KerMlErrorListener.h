//
// Created by Moritz Herzog on 08.04.25.
//

#pragma once


#include <antlr4-runtime/BaseErrorListener.h>
#include <vector>
#include <memory>

#include <kerml/parser/KerMlError.h>
#include <sysmlv2/sysmlv2file_global.h>

class SYSMLV2FILE_EXPORT KerMLErrorListener : public antlr4::BaseErrorListener {
public:
    KerMLErrorListener();
    virtual ~KerMLErrorListener() = default;

    void syntaxError(antlr4::Recognizer *recognizer, antlr4::Token * offendingSymbol, size_t line, size_t charPositionInLine, const std::string &msg, std::exception_ptr e) override;

    std::vector<std::shared_ptr<KerMLError>> getSyntaxErrors() const;

    void reportAmbiguity(antlr4::Parser *recognizer, const antlr4::dfa::DFA &dfa, size_t startIndex, size_t stopIndex, bool exact, const antlrcpp::BitSet &ambigAlts, antlr4::atn::ATNConfigSet *configs) override;

    void reportAttemptingFullContext(antlr4::Parser *recognizer, const antlr4::dfa::DFA &dfa, size_t startIndex, size_t stopIndex, const antlrcpp::BitSet &conflictingAlts, antlr4::atn::ATNConfigSet *configs) override;

    void reportContextSensitivity(antlr4::Parser *recognizer, const antlr4::dfa::DFA &dfa, size_t startIndex, size_t stopIndex,
                                          size_t prediction, antlr4::atn::ATNConfigSet *configs) override;
private:
    std::vector<std::shared_ptr<KerMLError>> SyntaxErrors;
};
