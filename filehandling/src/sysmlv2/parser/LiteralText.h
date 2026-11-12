//
// Conversion of the text of integer and string literals (private header of the sysmlv2parser library; the KerML and the SysML v2
// listener share it, so that both languages give the same value or the same error for the same literal).
//
//---------------------------------------------------------
// Constants, Definitions, Pragmas
//---------------------------------------------------------
#pragma once
//---------------------------------------------------------
// External Classes
//---------------------------------------------------------
#include <charconv>
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <system_error>
#include <vector>
#include <tree/ParseTree.h>
#include <tree/TerminalNode.h>
//---------------------------------------------------------

namespace SysMLv2::Files {

    /// The outcome of the conversion of the text of an integer literal.
    enum class IntegerStatus {
        Ok,
        /// The text is no sequence of decimal digits (a real literal, a name, an expression, ...).
        NotAnInteger,
        /// The text is a sequence of decimal digits, but its value does not fit the type.
        OutOfRange
    };

    /**
     * Converts the text of a DECIMAL_VALUE (decimal digits only) to @p value. Unlike std::stoll / std::stoul this never throws, never reads
     * a prefix of the text ("1.5" is not the integer 1) and never wraps around: a number that is too big is OutOfRange. @p value is
     * changed only if Ok is returned.
     * Note that a negative number is not a literal: `-9223372036854775808` is the unary minus applied to the literal 9223372036854775808,
     * which does not fit a std::int64_t; it is reported as OutOfRange as well.
     */
    template <class Integer>
    inline IntegerStatus parseInteger(const std::string& text, Integer& value) {
        if (text.empty() || text.find_first_not_of("0123456789") != std::string::npos) return IntegerStatus::NotAnInteger;
        Integer parsed{};
        const auto result = std::from_chars(text.data(), text.data() + text.size(), parsed);
        if (result.ec == std::errc::result_out_of_range) return IntegerStatus::OutOfRange;
        if (result.ec != std::errc() || result.ptr != text.data() + text.size()) return IntegerStatus::NotAnInteger;
        value = parsed;
        return IntegerStatus::Ok;
    }

    /// The message of the diagnostic for an integer literal whose value does not fit @p range; @p consequence says what the element built from
    /// the literal got instead. The diagnostic is reported where the literal is written.
    inline std::string integerOutOfRangeMessage(const std::string& literal, const char* range, const char* consequence) {
        return "integer literal out of range: '" + literal + "' does not fit " + range + "; " + consequence;
    }

    /// The characters of a quoted token and the first escape sequence that the notation does not have.
    struct DecodedString {
        std::string text;
        /// Offset of the backslash of the first invalid escape sequence within the text of the token; npos if there is none.
        std::size_t invalidEscape = std::string::npos;
    };

    /**
     * Decodes the text of a STRING_VALUE token (@p quote is '"') or of an unrestricted name (@p quote is '\''), including its quotes, to the
     * characters it stands for. The escape sequences of the textual notation (KerML 8.2.2.3) are \' \" \b \f \t \n \\ ; \r is accepted as
     * well, because KerML::Names::escapeName writes it (KerML::Names::unescapeName decodes names the same way).
     * The lexer accepts any character after a backslash (also a line end). An escape sequence that is none of the above is not an error here: the
     * backslash is dropped and the character is kept (what AnnotationText::stringValue always did), and DecodedString::invalidEscape tells
     * where the first one is. The listeners report it once per token, in their visitTerminal().
     * Text that is not enclosed in @p quote is returned as it is.
     */
    inline DecodedString decodeQuoted(std::string_view lexical, char quote) {
        DecodedString decoded;
        if (lexical.size() < 2 || lexical.front() != quote || lexical.back() != quote) {
            decoded.text = std::string(lexical);
            return decoded;
        }
        std::string& out = decoded.text;
        out.reserve(lexical.size());
        for (std::size_t i = 1; i + 1 < lexical.size(); ++i) {
            if (lexical[i] != '\\' || i + 2 >= lexical.size()) {
                // (a backslash in front of the closing quote cannot be: the lexer takes the quote as the escaped character)
                out.push_back(lexical[i]);
                continue;
            }
            ++i;
            switch (lexical[i]) {
                case 'b': out.push_back('\b'); break;
                case 'f': out.push_back('\f'); break;
                case 't': out.push_back('\t'); break;
                case 'n': out.push_back('\n'); break;
                case 'r': out.push_back('\r'); break;
                case '"': case '\'': case '\\': out.push_back(lexical[i]); break;
                default:
                    // (also a backslash in front of a line end: no escape sequence of the notation)
                    if (decoded.invalidEscape == std::string::npos) decoded.invalidEscape = i - 1;
                    out.push_back(lexical[i]);
                    break;
            }
        }
        return decoded;
    }

    inline DecodedString decodeStringLiteral(std::string_view lexical) { return decodeQuoted(lexical, '"'); }

    /// @p text for a message: the line ends and tabs in it are written as `\n`, `\r` and `\t`.
    inline std::string printable(std::string_view text) {
        std::string out;
        for (const char c : text) {
            switch (c) {
                case '\n': out += "\\n"; break;
                case '\r': out += "\\r"; break;
                case '\t': out += "\\t"; break;
                default: out.push_back(c); break;
            }
        }
        return out;
    }

    /// The line and the column of the character at the byte @p offset of a token that starts at (@p line, @p column) and may span several lines.
    /// The columns of ANTLR count code points, not bytes: the continuation bytes of UTF-8 do not count.
    inline void positionInToken(std::string_view token, std::size_t offset, int& line, int& column) {
        for (std::size_t i = 0; i < offset && i < token.size(); ++i) {
            if (token[i] == '\n') {
                ++line;
                column = 0;
            } else if ((static_cast<unsigned char>(token[i]) & 0xC0) != 0x80) {
                ++column;
            }
        }
    }

    /// One bound of a multiplicity that is not a valid non-negative integer literal.
    struct BoundProblem {
        IntegerStatus status = IntegerStatus::NotAnInteger;
        std::string text;
        std::size_t index = 0;
    };

    /// The bounds of a multiplicity, `[3]`, `[1..*]`, `[*]`, `[2..5]`, read from the texts of its multiplicity_expression_member children.
    struct MultiplicityBounds {
        /// Every bound that is no valid unsigned integer (the others are read all the same): NotAnInteger for a feature reference, a real
        /// literal, a negative number, ...; OutOfRange for digits that do not fit an unsigned int.
        std::vector<BoundProblem> problems;
        unsigned lower = 0;
        unsigned upper = 0;
        /// `*` is the upper bound (alone it stands for [0..*]).
        bool unbounded = false;
        /// Two bounds were written (or `*` alone, which has the bounds 0 and *), else the single number stands for the exact multiplicity.
        bool hasUpper = false;
    };

    /// Reads the bounds from the texts of the members of a multiplicity (one or two), every one of them. A value that is too big is not wrapped around.
    inline MultiplicityBounds readMultiplicityBounds(const std::vector<std::string>& members) {
        MultiplicityBounds bounds;
        const std::size_t count = members.size();
        for (std::size_t index = 0; index < count; ++index) {
            if (members[index] == "*" && index + 1 == count) {
                bounds.unbounded = bounds.hasUpper = true;
                continue;
            }
            unsigned value = 0;
            const IntegerStatus status = parseInteger(members[index], value);
            if (status != IntegerStatus::Ok) bounds.problems.push_back({status, members[index], index});
            if (index == 0) bounds.lower = value;
            else bounds.upper = value, bounds.hasUpper = true;
        }
        return bounds;
    }

    /// The multiplicity element for valid @p bounds (no problems); @p Multiplicity is KerML::Entities::Multiplicity.
    template <class Multiplicity>
    inline std::shared_ptr<Multiplicity> makeMultiplicity(const MultiplicityBounds& bounds) {
        if (bounds.unbounded) return std::make_shared<Multiplicity>(bounds.lower, true);
        if (bounds.hasUpper) return std::make_shared<Multiplicity>(bounds.lower, bounds.upper);
        return std::make_shared<Multiplicity>(bounds.lower);
    }

    /**
     * The multiplicity of the text `[members...]`, or null if there is none. Bounds that cannot be read are reported through
     * @p report(message, memberIndex, isWarning):
     *  - a number that does not fit an unsigned int: an error for each such bound; no multiplicity (no other number is invented);
     *  - a bound that looks like a number but is no non-negative integer literal (`2.5`, `-1`, `1e3`): a warning naming it; the
     *    multiplicity is then the one that @p unreadable gives (KerML: 1, SysML: none), as it was before, when the bound was read in part
     *    (`2.5` as 2) or wrapped around (`-1` as 4294967295);
     *  - any other bound (a reference to a feature, ...): nothing is reported, @p unreadable gives the multiplicity.
     */
    template <class Multiplicity, class Report, class Unreadable>
    inline std::shared_ptr<Multiplicity> multiplicityFromBounds(const std::vector<std::string>& members, Report&& report, Unreadable&& unreadable) {
        const MultiplicityBounds bounds = readMultiplicityBounds(members);
        if (bounds.problems.empty()) return makeMultiplicity<Multiplicity>(bounds);
        bool outOfRange = false;
        for (const BoundProblem& problem : bounds.problems) {
            if (problem.status == IntegerStatus::OutOfRange) {
                outOfRange = true;
                report(integerOutOfRangeMessage(problem.text, "an unsigned 32-bit integer", "the multiplicity is left out"), problem.index, false);
            }
        }
        if (outOfRange) return nullptr;
        for (const BoundProblem& problem : bounds.problems) {
            const char first = problem.text.empty() ? ' ' : problem.text.front();
            if ((first >= '0' && first <= '9') || first == '-' || first == '+' || first == '.')
                report("multiplicity bound '" + problem.text + "' is not a non-negative integer literal; the bounds of the multiplicity are not read", problem.index, true);
        }
        return unreadable();
    }

    /// A feature chain `a.b.c` whose left operand is a plain chain of names is resolved as a whole, by a reference that carries the text of the whole
    /// chain: one reference for every link, each with the text of the chain up to it, so that a chain of n links needs memory and time that grow with
    /// n squared (4000 links take 17 s in an unoptimized build, 10000 links 100 MB). A left operand of more than this many tokens (a name and a dot
    /// are two, i.e. about 500 links) is therefore treated as a computed value, like `f(x).b`: the reference of the target is not attempted, and one
    /// warning says so.
    constexpr std::size_t MaxPlainChainTokens = 1024;

    /// The number of tokens that are in the parse tree below @p node (the tokens of the default channel: not the white space and the comments),
    /// counted up to @p cap + 1: counting stops there, so that it costs time in the size of the limit, not of the tree.
    inline std::size_t cappedTokenCount(antlr4::tree::ParseTree* node, std::size_t cap) {
        std::size_t count = 0;
        std::vector<antlr4::tree::ParseTree*> stack{node};
        while (!stack.empty() && count <= cap) {
            antlr4::tree::ParseTree* current = stack.back();
            stack.pop_back();
            if (dynamic_cast<antlr4::tree::TerminalNode*>(current) != nullptr) {
                ++count;
                continue;
            }
            for (auto* child : current->children) stack.push_back(child);
        }
        return count;
    }
}
