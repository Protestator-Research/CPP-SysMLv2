#pragma once

#include <algorithm>
#include <iterator>
#include <string>

namespace KerML::Names {

    /**
     * Names in the textual notation (KerML 8.2.2.3, lexical structure): a basic name starts with a letter or '_' and continues with letters,
     * digits and '_'. Every other name is an unrestricted name: it is written between single quotes, and the characters \ ' " and the control
     * characters of the escape sequences (\b \f \t \n \r) are written as escape sequences.
     * The reserved words (the keywords of the notation) are not basic names either: a name that is a reserved word is quoted as well
     * (`'not'`, `'if'`, `'action'`).
     */

    /// The reserved words of KerML and SysML v2, sorted. Source: the literal tokens of the lexers of the two parsers (filehandling/src/kerml/parser/
    /// KerML.tokens, filehandling/src/sysmlv2/parser/SysMLv2.tokens, which come from the keyword rules of KerML.g4 and SysMLv2.g4): 174 words, the
    /// 104 words of KerML are among them. Regenerate the list when a keyword is added to a grammar.
    inline const char* const* reservedWordsBegin() {
        static const char* const words[] = {
        "about", "abstract", "accept", "action", "actor", "after", "alias", "all", "allocate", "allocation", "analysis", "and", "as",
        "assert", "assign", "assoc", "assume", "at", "attribute", "behavior", "bind", "binding", "bool", "by", "calc", "case", "chains",
        "class", "classifier", "comment", "composite", "concern", "conjugate", "conjugates", "conjugation", "connect", "connection",
        "connector", "const", "constant", "constraint", "crosses", "datatype", "decide", "def", "default", "defined", "dependency",
        "derived", "differences", "disjoining", "disjoint", "do", "doc", "else", "end", "entry", "enum", "event", "exhibit", "exit",
        "expose", "expr", "false", "feature", "featured", "featuring", "filter", "first", "flow", "for", "fork", "frame", "from",
        "function", "hastype", "if", "implies", "import", "in", "include", "individual", "inout", "interaction", "interface", "intersects",
        "inv", "inverse", "inverting", "istype", "item", "join", "language", "library", "locale", "loop", "member", "merge", "message",
        "meta", "metaclass", "metadata", "multiplicity", "namespace", "new", "nonunique", "not", "null", "objective", "occurrence", "of",
        "or", "ordered", "out", "package", "parallel", "part", "perform", "port", "portion", "predicate", "private", "protected", "public",
        "readonly", "redefines", "redefinition", "ref", "references", "render", "rendering", "rep", "require", "requirement", "return",
        "satisfy", "send", "snapshot", "specialization", "specializes", "stakeholder", "standard", "state", "step", "struct",
        "subclassifier", "subject", "subset", "subsets", "subtype", "succession", "terminate", "then", "timeslice", "to", "transition",
        "true", "type", "typed", "typing", "unions", "until", "use", "var", "variant", "variation", "verification", "verify", "via",
        "view", "viewpoint", "when", "while", "xor",
        };
        return words;
    }
    inline size_t reservedWordCount() { return 174; }

    /// Whether @p name is a reserved word of KerML or SysML v2.
    inline bool isReservedWord(const std::string& name) {
        const char* const* first = reservedWordsBegin();
        const char* const* last = first + reservedWordCount();
        const auto found = std::lower_bound(first, last, name, [](const char* word, const std::string& value) { return value.compare(word) > 0; });
        return found != last && name == *found;
    }

    /// The name of an element for the textual notation: unchanged if it is a basic name, else quoted with the escape sequences of the notation.
    inline std::string escapeName(const std::string& name) {
        bool basic = !name.empty() && !(name[0] >= '0' && name[0] <= '9');
        for (const char c : name) {
            if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_')) {
                basic = false;
                break;
            }
        }
        if (basic && !isReservedWord(name)) return name;
        std::string out = "'";
        for (const char c : name) {
            switch (c) {
                case '\'': out += "\\'"; break;
                case '\\': out += "\\\\"; break;
                case '\b': out += "\\b"; break;
                case '\f': out += "\\f"; break;
                case '\t': out += "\\t"; break;
                case '\n': out += "\\n"; break;
                case '\r': out += "\\r"; break;
                default: out.push_back(c); break;
            }
        }
        out.push_back('\'');
        return out;
    }

    /// The name that the text of a name token stands for: the quotes of an unrestricted name ('a b' -> a b) are removed and its escape
    /// sequences resolved; a basic name (or any text that is not quoted) is returned as is. Apply it once, to what the parser read: a
    /// declared name that is stored without quotes may itself start and end with a quote character.
    inline std::string unescapeName(const std::string& text) {
        if (text.size() < 2 || text.front() != '\'' || text.back() != '\'') return text;
        std::string out;
        out.reserve(text.size());
        for (size_t i = 1; i + 1 < text.size(); ++i) {
            if (text[i] == '\\' && i + 2 < text.size()) {
                ++i;
                switch (text[i]) {
                    case 'b': out.push_back('\b'); break;
                    case 'f': out.push_back('\f'); break;
                    case 't': out.push_back('\t'); break;
                    case 'n': out.push_back('\n'); break;
                    case 'r': out.push_back('\r'); break;
                    default: out.push_back(text[i]); break;   // \' \" \\ (and an escape that the notation does not know: the character)
                }
            } else {
                out.push_back(text[i]);
            }
        }
        return out;
    }

}
