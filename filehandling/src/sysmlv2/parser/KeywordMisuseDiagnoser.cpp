//
// Created by Moritz Herzog on 23.10.26.
// Diagnoses syntax errors that are caused by a misused keyword.
//

#include <sysmlv2/parser/KeywordMisuseDiagnoser.h>

#include <array>
#include <limits>
#include <mutex>
#include <typeindex>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace SysMLv2::Files {
    namespace {
        /// How many tokens in front of the offending one are looked at (a qualified name in front of a "(" needs some).
        constexpr size_t WindowSize = 12;
        /// The rules that only look at the tokens directly around the offending one use this many in front of it.
        constexpr size_t NearTokens = 3;
        /// How many tokens behind the offending one are looked at.
        constexpr size_t AheadTokens = 2;

        /// What is known about the token types of one parser (SysML v2 or KerML); built once per parser type.
        struct TokenInfo {
            std::unordered_map<std::string, size_t> TypeBySymbolicName;
            /// The KEYWORD_ tokens the name rule does not accept: these cannot be used as a name.
            std::unordered_set<size_t> Reserved;
            /// The KEYWORD_ tokens the name rule accepts (SysML: e.g. the KerML-only keywords); these are part of a qualified name.
            std::unordered_set<size_t> UsableAsName;
            /// Whether the name rule was found in the grammar.
            bool HasNameRule = false;

            size_t type(const std::string& symbolicName) const {
                const auto found = TypeBySymbolicName.find(symbolicName);
                return found == TypeBySymbolicName.end() ? antlr4::Token::INVALID_TYPE : found->second;
            }
        };

        bool startsWith(const std::string& text, const std::string& prefix) {
            return text.compare(0, prefix.size(), prefix) == 0;
        }

        const TokenInfo& tokenInfo(antlr4::Parser& parser) {
            static std::mutex mutex;
            static std::unordered_map<std::type_index, TokenInfo> cache;
            std::lock_guard<std::mutex> lock(mutex);
            const std::type_index key(typeid(parser));
            const auto cached = cache.find(key);
            if (cached != cache.end()) return cached->second;

            TokenInfo info;
            const antlr4::dfa::Vocabulary& vocabulary = parser.getVocabulary();
            for (size_t type = 1; type <= vocabulary.getMaxTokenType(); ++type) {
                const std::string name = std::string(vocabulary.getSymbolicName(type));
                if (!name.empty()) info.TypeBySymbolicName[name] = type;
            }

            // The tokens that can start the name rule can be used as a name: sysml_name in SysML v2 (it lists the
            // KerML-only keywords besides NAME), identification in KerML (NAME only).
            const auto ruleIndices = parser.getRuleIndexMap();
            auto rule = ruleIndices.find("sysml_name");
            if (rule == ruleIndices.end()) rule = ruleIndices.find("identification");
            antlr4::misc::IntervalSet allowed;
            if (rule != ruleIndices.end()) {
                info.HasNameRule = true;
                const antlr4::atn::ATN& atn = parser.getATN();
                allowed = atn.nextTokens(atn.ruleToStartState[rule->second]);
            }
            for (const auto& entry : info.TypeBySymbolicName) {
                if (!startsWith(entry.first, "KEYWORD_")) continue;
                (allowed.contains(entry.second) ? info.UsableAsName : info.Reserved).insert(entry.second);
            }
            return cache.emplace(key, std::move(info)).first->second;
        }

        /// The tokens that can directly follow a token in the grammar.
        struct Follow {
            std::unordered_set<size_t> Tokens;
            /// True if the token can end a rule: what follows then depends on the caller, so the set is incomplete.
            bool Open = false;
        };

        /**
         * The tokens that can directly follow @p type, derived from the ATN: the first tokens after every place the token is matched
         * (also through invoked rules). Cached per parser type.
         */
        const Follow& followOf(antlr4::Parser& parser, size_t type) {
            static std::mutex mutex;
            static std::unordered_map<std::type_index, std::unordered_map<size_t, Follow>> cache;
            std::lock_guard<std::mutex> lock(mutex);
            auto& perType = cache[std::type_index(typeid(parser))];
            const auto cached = perType.find(type);
            if (cached != perType.end()) return cached->second;

            Follow follow;
            const antlr4::atn::ATN& atn = parser.getATN();
            for (const antlr4::atn::ATNState* state : atn.states) {
                if (!state) continue;
                for (const auto& transition : state->transitions) {
                    const auto kind = transition->getTransitionType();
                    if (kind != antlr4::atn::TransitionType::ATOM && kind != antlr4::atn::TransitionType::SET &&
                        kind != antlr4::atn::TransitionType::RANGE) continue;
                    if (!transition->label().contains(type)) continue;
                    for (const size_t next : atn.nextTokens(transition->target).toList()) {
                        if (next == antlr4::Token::EPSILON) follow.Open = true;
                        else follow.Tokens.insert(next);
                    }
                }
            }
            return perType.emplace(type, std::move(follow)).first->second;
        }

        /// The tokens around the offending one (default channel only), oldest first.
        struct Window {
            antlr4::Parser& Parser;
            const TokenInfo& Info;
            std::vector<antlr4::Token*> Tokens;
            /// Position of the offending token in Tokens; the tokens behind it were read ahead.
            size_t Offending = 0;
            /// The tokens the parser expected instead of the offending one.
            antlr4::misc::IntervalSet Expected;

            /// The token @p back positions before the offending one (0 = the offending token itself), or null.
            antlr4::Token* at(size_t back) const { return back <= Offending ? Tokens[Offending - back] : nullptr; }
            /// The token @p count positions behind the offending one (count >= 1), or null.
            antlr4::Token* ahead(size_t count) const { return Offending + count < Tokens.size() ? Tokens[Offending + count] : nullptr; }
            /// The token after the one @p back positions before the offending one.
            antlr4::Token* after(size_t back) const { return back == 0 ? ahead(1) : at(back - 1); }

            static bool isType(const TokenInfo& info, const antlr4::Token* token, const char* symbolicName) {
                return token && token->getType() == info.type(symbolicName);
            }
            bool is(size_t back, const char* symbolicName) const { return isType(Info, at(back), symbolicName); }
            bool isReserved(const antlr4::Token* token) const { return token && Info.Reserved.count(token->getType()) != 0; }
            bool isReserved(size_t back) const { return isReserved(at(back)); }
            /// A token that can be part of a (qualified) name: a name, "::" or a keyword the name rule accepts.
            bool isNamePart(size_t back) const {
                const auto* token = at(back);
                return token && (is(back, "NAME") || is(back, "SYMBOL_NAMESPACE_SUBSET") || Info.UsableAsName.count(token->getType()) != 0);
            }
            bool isAnyOf(const antlr4::Token* token, std::initializer_list<const char*> symbolicNames) const {
                for (const char* name : symbolicNames) {
                    if (isType(Info, token, name)) return true;
                }
                return false;
            }
        };

        KeywordMisuse hit(const antlr4::Token* culprit, std::string message) {
            return {std::move(message), static_cast<int>(culprit->getLine()), static_cast<int>(culprit->getCharPositionInLine())};
        }

        // The rules: each looks at the window and returns a diagnosis or nothing. They are tried in the order of Rules, the
        // specific ones first (the general one would explain the same error wrongly).

        /// "inv not": an invariant is negated with "inv false". Only where "inv" is a keyword (KerML); in SysML v2 it is an ordinary name.
        std::optional<KeywordMisuse> invNot(const Window& window) {
            if (window.Info.Reserved.count(window.Info.type("KEYWORD_INV")) == 0) return std::nullopt;
            for (size_t back = 0; back < NearTokens; ++back) {
                if (window.is(back, "KEYWORD_NOT") && window.is(back + 1, "KEYWORD_INV"))
                    return hit(window.at(back + 1), "an invariant is negated with 'inv false', not 'inv not'");
            }
            return std::nullopt;
        }

        /// "entry perform", "do perform", "exit perform": no "perform" after the keyword of a state action.
        std::optional<KeywordMisuse> performAfterStateAction(const Window& window) {
            for (size_t back = 0; back < NearTokens; ++back) {
                if (!window.is(back, "KEYWORD_PERFORM")) continue;
                for (const char* keyword : {"KEYWORD_ENTRY", "KEYWORD_DO", "KEYWORD_EXIT"}) {
                    if (window.is(back + 1, keyword)) {
                        const std::string word = window.at(back + 1)->getText();
                        return hit(window.at(back), "'perform' is not written after '" + word + "'; write e.g. '" + word +
                                   " action x : T;' or '" + word + " x;'");
                    }
                }
            }
            return std::nullopt;
        }

        /// A typing (":" or "typed by" / "defined by") followed by "(": an invocation is not allowed in a typing.
        std::optional<KeywordMisuse> invocationInTyping(const Window& window) {
            for (size_t back = 0; back < NearTokens; ++back) {
                if (!window.is(back, "SYMBOL_ROUND_BRACKET_OPEN")) continue;
                size_t before = back + 1;
                while (window.isNamePart(before)) ++before;           // the qualified name of the type
                if (before == back + 1) continue;                      // there is no type in front of the "("
                if (window.is(before, "SYMBOL_TYPED_BY") ||
                    (window.is(before, "KEYWORD_BY") && (window.is(before + 1, "KEYWORD_TYPED") || window.is(before + 1, "KEYWORD_DEFINED"))))
                    return hit(window.at(back), "an invocation is not allowed in a typing; bind parameters in a body or use a value '= T(...)'");
            }
            return std::nullopt;
        }

        /// Whether the token is one after which a name is expected: "." and "::" of qualified names and chains, "<" of a short name,
        /// the symbols of typing and specialization, or a keyword (a definition or usage keyword).
        bool introducesName(const Window& window, const antlr4::Token* token) {
            return window.isReserved(token) ||
                   window.isAnyOf(token, {"SYMBOL_DOT", "SYMBOL_NAMESPACE_SUBSET", "SYMBOL_SMALLER", "SYMBOL_TYPED_BY", "SYMBOL_SPECIALIZES",
                                          "SYMBOL_REFERENCES", "SYMBOL_REDEFINES", "SYMBOL_CROSSES"});
        }

        /// Whether the token can follow the name in a declaration or a chain (the end of the statement, a body, a typing, a
        /// specialization, a value, a multiplicity, the next segment of a chain, ...).
        bool continuesDeclaration(const Window& window, const antlr4::Token* token) {
            if (token && token->getType() == antlr4::Token::EOF) return true;   // a name at the end of the text: the rest is missing
            return window.isAnyOf(token, {"SYMBOL_STATEMENT_DELIMITER", "SYMBOL_CURLY_BRACKET_OPEN", "SYMBOL_TYPED_BY", "SYMBOL_SPECIALIZES",
                                          "SYMBOL_REFERENCES", "SYMBOL_REDEFINES", "SYMBOL_CROSSES", "SYMBOL_DOT", "SYMBOL_NAMESPACE_SUBSET",
                                          "SYMBOL_ASSIGN", "SYMBOL_DEF_ASSIGN", "SYMBOL_SQUARE_BRACKET_OPEN", "SYMBOL_GREATER", "SYMBOL_COMMA",
                                          "KEYWORD_TYPED", "KEYWORD_SUBSETS", "KEYWORD_REDEFINES", "KEYWORD_SPECIALIZES", "KEYWORD_REFERENCES",
                                          "KEYWORD_DEFINED"});
        }

        /**
         * Whether the reserved keyword @p back positions before the offending token stands where a name belongs. That is the case if
         *  - the token in front of it introduces a name,
         *  - the token behind it continues a declaration (so the keyword is not the start of a new statement after a missing ";"
         *    or a missing name, as in "entry state a;", "attribute def part def X;", "part x :> part y;"), and
         *  - if the parser accepted the keyword (it is not the offending token), it is no keyword sequence of the grammar like
         *    "attribute def", "then action" or "action loop", or the parser has run into a dead end behind it, i.e. does not expect a
         *    name there (it does for "attribute def ;", where the name is just missing).
         */
        bool reservedWordInsteadOfName(const Window& window, size_t back) {
            const antlr4::Token* culprit = window.at(back);
            const antlr4::Token* before = window.at(back + 1);
            if (!window.isReserved(culprit) || !before || !introducesName(window, before)) return false;
            if (!continuesDeclaration(window, window.after(back))) return false;
            if (back == 0) return true;
            const Follow& follow = followOf(window.Parser, before->getType());
            const bool keywordSequence = follow.Open || follow.Tokens.count(culprit->getType()) != 0;
            return !keywordSequence || !window.Expected.contains(window.Info.type("NAME"));
        }

        /// A reserved keyword where a name is expected.
        std::optional<KeywordMisuse> reservedWordAsName(const Window& window) {
            for (size_t back = 0; back < NearTokens; ++back) {
                if (!reservedWordInsteadOfName(window, back)) continue;
                const std::string word = window.at(back)->getText();
                return hit(window.at(back), "'" + word + "' is a reserved keyword and cannot be used as a name; rename it or write it as an unrestricted name ('" + word + "')");
            }
            return std::nullopt;
        }

        using Rule = std::optional<KeywordMisuse> (*)(const Window&);
        /// The rule table: add a rule function above and list it here (specific rules first).
        constexpr std::array<Rule, 4> Rules = {&invNot, &performAfterStateAction, &invocationInTyping, &reservedWordAsName};

        /// The token types the rules look at (SysML only ones are listed separately).
        constexpr std::array<const char*, 22> RequiredTokens = {
            "NAME", "SYMBOL_DOT", "SYMBOL_NAMESPACE_SUBSET", "SYMBOL_STATEMENT_DELIMITER", "SYMBOL_CURLY_BRACKET_OPEN",
            "SYMBOL_CURLY_BRACKET_CLOSE", "SYMBOL_ROUND_BRACKET_OPEN", "SYMBOL_TYPED_BY", "SYMBOL_SPECIALIZES", "SYMBOL_REFERENCES",
            "SYMBOL_REDEFINES", "SYMBOL_CROSSES", "SYMBOL_ASSIGN", "SYMBOL_DEF_ASSIGN", "SYMBOL_SQUARE_BRACKET_OPEN", "SYMBOL_GREATER",
            "SYMBOL_SMALLER", "SYMBOL_COMMA", "KEYWORD_BY", "KEYWORD_TYPED", "KEYWORD_INV", "KEYWORD_NOT"};
        /// Needed in SysML v2 only (state actions, "defined by"); KerML has no such tokens.
        constexpr std::array<const char*, 5> SysMLOnlyTokens = {"KEYWORD_PERFORM", "KEYWORD_ENTRY", "KEYWORD_DO", "KEYWORD_EXIT", "KEYWORD_DEFINED"};
    }

    std::optional<KeywordMisuse> KeywordMisuseDiagnoser::diagnose(antlr4::Recognizer* recognizer, antlr4::Token* offendingSymbol) {
        auto* parser = dynamic_cast<antlr4::Parser*>(recognizer);
        if (!parser || !offendingSymbol) return std::nullopt;
        antlr4::TokenStream* stream = parser->getTokenStream();
        if (!stream) return std::nullopt;
        try {
            // The tokens behind the offending one may not be read yet; reading them does not change the parse.
            if (auto* buffered = dynamic_cast<antlr4::BufferedTokenStream*>(stream)) buffered->fill();
            Window window{*parser, tokenInfo(*parser), {}, 0, {}};
            // The offending token and the default channel tokens in front of it, then the ones behind it.
            std::vector<antlr4::Token*> newestFirst;
            for (ssize_t index = static_cast<ssize_t>(offendingSymbol->getTokenIndex()); index >= 0 && newestFirst.size() < WindowSize; --index) {
                antlr4::Token* token = stream->get(static_cast<size_t>(index));
                if (token && token->getChannel() == antlr4::Token::DEFAULT_CHANNEL) newestFirst.push_back(token);
            }
            window.Tokens.assign(newestFirst.rbegin(), newestFirst.rend());
            if (window.Tokens.empty() || window.Tokens.back() != offendingSymbol) return std::nullopt;
            window.Offending = window.Tokens.size() - 1;
            size_t ahead = 0;
            for (size_t index = offendingSymbol->getTokenIndex() + 1; index < stream->size() && ahead < AheadTokens; ++index) {
                antlr4::Token* token = stream->get(index);
                if (token && token->getChannel() == antlr4::Token::DEFAULT_CHANNEL) {
                    window.Tokens.push_back(token);
                    ++ahead;
                }
            }
            window.Expected = parser->getExpectedTokens();
            for (const Rule rule : Rules) {
                if (auto found = rule(window)) return found;
            }
        } catch (const std::exception&) {
            // a diagnosis must never make things worse: the message of the parser is used then
        }
        return std::nullopt;
    }

    std::vector<std::string> KeywordMisuseDiagnoser::missingGrammarElements(antlr4::Parser& parser) {
        const TokenInfo& info = tokenInfo(parser);
        std::vector<std::string> missing;
        if (!info.HasNameRule) missing.push_back("rule sysml_name / identification");
        if (info.Reserved.empty()) missing.push_back("reserved KEYWORD_ tokens");
        for (const char* token : RequiredTokens) {
            if (info.type(token) == antlr4::Token::INVALID_TYPE) missing.push_back(token);
        }
        const bool sysml = parser.getRuleIndexMap().count("sysml_name") != 0;
        if (sysml) {
            for (const char* token : SysMLOnlyTokens) {
                if (info.type(token) == antlr4::Token::INVALID_TYPE) missing.push_back(token);
            }
        }
        return missing;
    }

    bool KeywordMisuseDiagnoser::isReservedKeyword(antlr4::Parser& parser, const std::string& symbolicName) {
        const TokenInfo& info = tokenInfo(parser);
        return info.Reserved.count(info.type(symbolicName)) != 0;
    }

    bool KeywordMisuseDiagnoser::statementEndsBetween(antlr4::Recognizer* recognizer, size_t fromTokenIndex, size_t toTokenIndex) {
        auto* parser = dynamic_cast<antlr4::Parser*>(recognizer);
        if (!parser || !parser->getTokenStream()) return true;
        antlr4::TokenStream* stream = parser->getTokenStream();
        const TokenInfo& info = tokenInfo(*parser);
        const size_t semicolon = info.type("SYMBOL_STATEMENT_DELIMITER");
        const size_t closing = info.type("SYMBOL_CURLY_BRACKET_CLOSE");
        try {
            for (size_t index = fromTokenIndex; index < toTokenIndex; ++index) {
                const size_t type = stream->get(index)->getType();
                if (type == semicolon || type == closing) return true;
            }
        } catch (const std::exception&) {
            return true;
        }
        return false;
    }

    KeywordMisuseFilter::Decision KeywordMisuseFilter::onSyntaxError(antlr4::Recognizer* recognizer, antlr4::Token* offendingSymbol) {
        constexpr size_t Unknown = std::numeric_limits<size_t>::max();
        const size_t tokenIndex = offendingSymbol ? offendingSymbol->getTokenIndex() : Unknown;
        if (Suppressing && offendingSymbol) {
            // The statement ends at the next ';' or '}' and at the end of the text (a missing '}' there is a new error).
            if (offendingSymbol->getType() != antlr4::Token::EOF && !KeywordMisuseDiagnoser::statementEndsBetween(recognizer, SuppressedFrom, tokenIndex))
                return {Kind::Suppressed, {}, 0};
            Suppressing = false;
        }
        if (auto misuse = KeywordMisuseDiagnoser::diagnose(recognizer, offendingSymbol)) {
            // The parser reported the same problem before (e.g. at the ":" in front of the keyword): the diagnosis replaces it.
            size_t drop = 0;
            while (drop < PlainTokenIndices.size()) {
                const size_t earlier = PlainTokenIndices[PlainTokenIndices.size() - 1 - drop];
                if (earlier == Unknown || tokenIndex == Unknown || earlier > tokenIndex ||
                    KeywordMisuseDiagnoser::statementEndsBetween(recognizer, earlier, tokenIndex)) break;
                ++drop;
            }
            PlainTokenIndices.resize(PlainTokenIndices.size() - drop);
            Suppressing = true;
            SuppressedFrom = tokenIndex;
            return {Kind::Misuse, std::move(*misuse), drop};
        }
        PlainTokenIndices.push_back(tokenIndex);
        return {Kind::Plain, {}, 0};
    }
}
