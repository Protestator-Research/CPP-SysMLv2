//
// Created by Moritz Herzog on 02.11.26.
// Adds a hint to the lexer errors that are caused by a name with a special character that is not quoted.
//

#include <sysmlv2/parser/LexerErrorHint.h>

#include <kerml/root/elements/NameEscaping.h>

#include <cctype>
#include <cstring>

namespace SysMLv2::Files {
    namespace {
        /// Characters that end a word: whitespace and the delimiters and operators of the grammars (the quotes included).
        bool endsWord(size_t code) {
            return code < 0x80 && (std::isspace(static_cast<int>(code)) != 0 || std::strchr(";,()[]{}:=<>+-*/^%.!|&?#@~'\"", static_cast<int>(code)) != nullptr);
        }

        /// Characters that the grammars never use outside of quotes and comments: they can only be part of a quoted name.
        bool onlyInQuotedName(size_t code) {
            return code >= 0x80 || code == '$' || code == '`' || code == '\\';
        }

        /// The longest word (in code points) in front of and behind the failed character that is looked at.
        constexpr size_t MaxWord = 64;

        void appendUtf8(std::string& out, size_t code) {
            if (code < 0x80) {
                out.push_back(static_cast<char>(code));
            } else if (code < 0x800) {
                out.push_back(static_cast<char>(0xC0 | (code >> 6)));
                out.push_back(static_cast<char>(0x80 | (code & 0x3F)));
            } else if (code < 0x10000) {
                out.push_back(static_cast<char>(0xE0 | (code >> 12)));
                out.push_back(static_cast<char>(0x80 | ((code >> 6) & 0x3F)));
                out.push_back(static_cast<char>(0x80 | (code & 0x3F)));
            } else {
                out.push_back(static_cast<char>(0xF0 | (code >> 18)));
                out.push_back(static_cast<char>(0x80 | ((code >> 12) & 0x3F)));
                out.push_back(static_cast<char>(0x80 | ((code >> 6) & 0x3F)));
                out.push_back(static_cast<char>(0x80 | (code & 0x3F)));
            }
        }

        bool basicNameCharacter(size_t code) {
            return code == '_' || (code >= '0' && code <= '9') || (code >= 'a' && code <= 'z') || (code >= 'A' && code <= 'Z');
        }
    }

    std::string LexerErrorHint::complete(antlr4::Recognizer* recognizer, antlr4::Token* offendingSymbol, const std::string& message) {
        auto* lexer = dynamic_cast<antlr4::Lexer*>(recognizer);
        if (offendingSymbol != nullptr || lexer == nullptr) return message;
        antlr4::CharStream* input = lexer->getInputStream();
        if (input == nullptr) return message;
        const size_t start = lexer->tokenStartCharIndex;
        const size_t size = input->size();
        if (start >= size) return message;

        // The code point at an index (the stream is addressed by code points), 0 outside of the stream.
        const auto codeAt = [&](size_t index) -> size_t {
            if (index >= size) return 0;
            const std::string text = input->getText(antlr4::misc::Interval(index, index));
            if (text.empty()) return 0;
            const unsigned char lead = static_cast<unsigned char>(text[0]);
            if (lead < 0x80) return lead;
            size_t code = lead >= 0xF0 ? lead & 0x07 : lead >= 0xE0 ? lead & 0x0F : lead & 0x1F;
            for (size_t k = 1; k < text.size(); ++k) code = (code << 6) | (static_cast<unsigned char>(text[k]) & 0x3F);
            return code;
        };
        if (!onlyInQuotedName(codeAt(start))) return message;

        // The word: backward over everything that can be part of it, forward up to the next whitespace or delimiter. Both scans are bounded.
        size_t first = start;
        bool tooLong = false;
        while (first > 0) {
            const size_t previous = codeAt(first - 1);
            if (!basicNameCharacter(previous) && !onlyInQuotedName(previous)) break;
            // A further special character in front: the first one of the word has the hint.
            if (onlyInQuotedName(previous)) return message;
            if (start - first >= MaxWord) { tooLong = true; break; }
            --first;
        }
        size_t last = start;
        while (last + 1 < size) {
            const size_t next = codeAt(last + 1);
            if (next == 0 || endsWord(next)) break;
            if (last - start >= MaxWord) { tooLong = true; break; }
            ++last;
        }
        const std::string explanation = ": names may only contain letters, digits and '_' unless they are quoted";
        if (tooLong) return message + explanation;

        // (digits in front of the character are a number of their own, not a part of the name; typographic quotes are no part of it)
        std::string word;
        bool typographic = false;
        bool digitsOnly = true;
        for (size_t index = first; index <= last; ++index) {
            const size_t code = codeAt(index);
            if (code >= 0x2018 && code <= 0x201D && (code <= 0x2019 || code >= 0x201C)) { typographic = true; continue; }
            digitsOnly = digitsOnly && code >= '0' && code <= '9';
            if (digitsOnly) continue;
            appendUtf8(word, code);
        }
        if (typographic) {
            const std::string quotes = ": quoted names are written between the ASCII apostrophe ', not between typographic quotes";
            return message + quotes + (word.empty() ? std::string() : "; write " + KerML::Names::escapeName(word));
        }
        if (word.empty()) return message + explanation;
        return message + explanation + "; write " + KerML::Names::escapeName(word);
    }
}
