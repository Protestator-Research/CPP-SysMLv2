//
// Created by Moritz Herzog on 02.11.26.
// Adds a hint to the lexer errors that are caused by a name with a special character that is not quoted.
//

#pragma once

#include <antlr4-runtime/antlr4-runtime.h>
#include <string>

#include <sysmlv2/sysmlv2file_global.h>

namespace SysMLv2::Files {
    /**
     * A basic name only contains letters, digits and '_' (KerML 8.2.2.3); every other name has to be written as an unrestricted name
     * between single quotes. A text like `[°C]` therefore fails in the lexer with ANTLR's "token recognition error at: '°'".
     * This helper completes that message with the word that was meant and the quoted form of it.
     */
    class SYSMLV2FILE_EXPORT LexerErrorHint {
    public:
        /**
         * @param recognizer the recognizer that reported the error (the hint is only added for a lexer).
         * @param offendingSymbol null for lexer errors; a parser error is never changed.
         * @param message the message of ANTLR.
         * @return @p message, followed by the hint if the lexer failed at a character that can only appear in a quoted name; else @p message.
         */
        static std::string complete(antlr4::Recognizer* recognizer, antlr4::Token* offendingSymbol, const std::string& message);
    };
}
