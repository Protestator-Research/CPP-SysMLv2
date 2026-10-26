//
// Created by Moritz Herzog on 23.10.26.
// Diagnoses syntax errors that are caused by a misused keyword.
//

#pragma once

#include <antlr4-runtime/antlr4-runtime.h>
#include <optional>
#include <string>
#include <vector>

#include <sysmlv2/sysmlv2file_global.h>

namespace SysMLv2::Files {
    /**
     * The diagnosis of a misused keyword: a readable message instead of ANTLR's "mismatched input ..." and the
     * position of the token that causes the error (not necessarily the token ANTLR reports).
     */
    struct SYSMLV2FILE_EXPORT KeywordMisuse {
        std::string message;
        /// 1-based line number.
        int line = -1;
        /// 0-based column (ANTLR's charPositionInLine).
        int column = -1;
    };

    /**
     * Recognises the typical misuses of keywords in a SysML v2 / KerML text that fails to parse:
     *  - a reserved keyword is used as a name (e.g. "action send", "flow a to send.cs"),
     *  - "inv not" instead of "inv false",
     *  - "perform" after "entry", "do" or "exit",
     *  - an invocation "T(x)" in a typing (":" or "typed by").
     * The diagnoser works on any ANTLR parser of the two grammars (SysMLv2Parser and KerMLParser). The reserved keywords are
     * derived from the grammar (all KEYWORD_ tokens that the name rule does not accept), so nothing has to be kept in sync by hand.
     * It only inspects the token stream around the offending token. It is meant to be called from syntaxError() of an
     * error listener, i.e. only after a parse failed, and never influences the parse of a valid text.
     */
    class SYSMLV2FILE_EXPORT KeywordMisuseDiagnoser {
    public:
        /**
         * Looks for a keyword misuse around the offending token of a syntax error.
         * @param recognizer The recognizer that reported the error. Anything but a parser (e.g. a lexer) gives no diagnosis.
         * @param offendingSymbol The token the parser reported the error at (may be null).
         * @return The diagnosis or nothing if the error is not a keyword misuse.
         */
        static std::optional<KeywordMisuse> diagnose(antlr4::Recognizer* recognizer, antlr4::Token* offendingSymbol);

        /**
         * The elements of the grammar the diagnoser depends on that the given parser does not have (empty if all are there): the
         * name rule and the tokens the rules look at (NAME, SYMBOL_DOT, ...). A renamed grammar element would otherwise silently
         * disable the diagnosis; the tests assert that this list is empty for both parsers.
         */
        static std::vector<std::string> missingGrammarElements(antlr4::Parser& parser);

        /**
         * Whether the keyword token with the given symbolic name (e.g. "KEYWORD_INV") is reserved for the parser, i.e. cannot be used as a name.
         */
        static bool isReservedKeyword(antlr4::Parser& parser, const std::string& symbolicName);

        /**
         * True, if a statement ends (a ";" or a "}" token) in the token range [fromTokenIndex, toTokenIndex).
         * Used by the error listeners to suppress the follow-up errors of a diagnosed statement.
         * @param recognizer The recognizer (a parser) the tokens belong to. If it is no parser (e.g. a lexer) there are no tokens to
         * look at and the statement is regarded as ended (true), i.e. nothing is suppressed.
         */
        static bool statementEndsBetween(antlr4::Recognizer* recognizer, size_t fromTokenIndex, size_t toTokenIndex);
    };

    /**
     * Decides for every syntax error of a parse what an error listener does with it: report the message of the parser, report a
     * keyword misuse instead, or drop it as a follow-up error. The state (which statement is suppressed, which plain errors were
     * reported) is kept per parse, so every error listener owns one.
     */
    class SYSMLV2FILE_EXPORT KeywordMisuseFilter {
    public:
        enum class Kind {
            /// Report the message of the parser (the listener must report exactly one error).
            Plain,
            /// Report the keyword misuse instead (exactly one error) after dropping the last DropPlain errors the listener reported.
            Misuse,
            /// A follow-up error of a diagnosed statement: report nothing.
            Suppressed
        };

        struct Decision {
            Kind What = Kind::Plain;
            KeywordMisuse Misuse;
            /// Number of plain errors at the end of the listener's list that belong to the diagnosed statement and are replaced by the misuse.
            size_t DropPlain = 0;
        };

        /**
         * Classifies a syntax error.
         * @param recognizer The recognizer that reported the error.
         * @param offendingSymbol The token the error was reported at (may be null).
         */
        Decision onSyntaxError(antlr4::Recognizer* recognizer, antlr4::Token* offendingSymbol);

    private:
        /// True after a keyword misuse: the follow-up errors of its statement (up to the next ';' or '}' or the end of the text) are suppressed.
        bool Suppressing = false;
        /// Token index of the diagnosed misuse.
        size_t SuppressedFrom = 0;
        /// Token indices of the plain errors reported so far (npos if unknown).
        std::vector<size_t> PlainTokenIndices;
    };
}
