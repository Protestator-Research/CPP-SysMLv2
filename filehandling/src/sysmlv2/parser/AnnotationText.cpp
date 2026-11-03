//
// Text processing for the lexical tokens of annotating elements.
//

#include <sysmlv2/parser/AnnotationText.h>

#include <vector>

namespace SysMLv2::Files {
    namespace {
        bool isBlank(const char c) { return c == ' ' || c == '\t' || c == '\f' || c == '\v'; }
    }

    std::string AnnotationText::processCommentBody(std::string_view lexical) {
        if (lexical.size() >= 2 && lexical.substr(0, 2) == "/*") lexical.remove_prefix(2);
        if (lexical.size() >= 2 && lexical.substr(lexical.size() - 2) == "*/") lexical.remove_suffix(2);

        // Split into lines; \r\n, \n and a single \r all terminate a line, the terminators themselves are dropped.
        std::vector<std::string_view> lines;
        size_t start = 0;
        for (size_t i = 0; i < lexical.size(); ++i) {
            if (lexical[i] == '\n' || lexical[i] == '\r') {
                lines.push_back(lexical.substr(start, i - start));
                if (lexical[i] == '\r' && i + 1 < lexical.size() && lexical[i + 1] == '\n') ++i;
                start = i + 1;
            }
        }
        lines.push_back(lexical.substr(start));

        // Rule 2: white space after `commet singage` up to and including the first line terminator. If the first line has only white space and
        // there is a terminator, the whole first line goes; otherwise the first line keeps its text (its white space is stripped
        // as on the other lines, so that "commet singage x commet singage" becomes "x"; only white space is stripped, a leading `*` is text there).
        size_t first = 0;
        std::string_view head = lines[0];
        size_t h = 0;
        while (h < head.size() && isBlank(head[h])) ++h;
        if (h == head.size() && lines.size() > 1) first = 1;

        std::string result;
        for (size_t n = first; n < lines.size(); ++n) {
            std::string_view line = lines[n];
            // Initial white space is stripped on every line.
            size_t p = 0;
            while (p < line.size() && isBlank(line[p])) ++p;
            line.remove_prefix(p);
            // Rule 3 (8.2.3.3.2) applies to the lines after the first one only: a `*`, then a single space.
            if (n != 0) {
                if (!line.empty() && line.front() == '*') line.remove_prefix(1);
                if (!line.empty() && line.front() == ' ') line.remove_prefix(1);
            }
            if (n != first) result.push_back('\n');
            result.append(line);
        }
        // The standard's rules alone would leave white space in front of the closing `commet singage` ("commet singage a > 0 commet singage" -> "a > 0 "); like the reference
        // (Pilot) implementation the trailing white space of the body is removed.
        while (!result.empty() && (isBlank(result.back()) || result.back() == '\n')) result.pop_back();
        return result;
    }

    std::string AnnotationText::stringValue(std::string_view lexical) {
        if (lexical.size() < 2 || lexical.front() != '"' || lexical.back() != '"') return std::string(lexical);
        std::string out;
        out.reserve(lexical.size());
        for (size_t i = 1; i + 1 < lexical.size(); ++i) {
            if (lexical[i] == '\\' && i + 2 < lexical.size()) {
                ++i;
                switch (lexical[i]) {
                    case 'b': out.push_back('\b'); break;
                    case 'f': out.push_back('\f'); break;
                    case 't': out.push_back('\t'); break;
                    case 'n': out.push_back('\n'); break;
                    case 'r': out.push_back('\r'); break;
                    default: out.push_back(lexical[i]); break;   // \" \\ \' (and an unknown escape: the character itself)
                }
            } else {
                out.push_back(lexical[i]);
            }
        }
        return out;
    }
}
