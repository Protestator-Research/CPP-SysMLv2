//
// Shared helpers for the conformance-test suites (AP1/AP2/AP4(e) of the test plan).
//
#pragma once

#include <algorithm>
#include <cctype>
#include <filesystem>
#include <fstream>
#include <memory>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

#include <sysmlv2/Parser.h>
#include <sysmlv2/ParserError.h>
#include <kerml/root/elements/Element.h>

namespace ConformanceTest {

// Finds the first element of type T with the given declared name. Behaviorally identical to the
// `named<T>` helper each of TestSysMLParser.cpp / TestKerMLParser.cpp currently defines for itself
// (those files are left untouched so they keep compiling as-is); new suites should include this
// header instead of redefining their own copy.
template <class T>
std::shared_ptr<T> named(const std::vector<std::shared_ptr<KerML::Entities::Element>>& elements, const std::string& name) {
    for (const auto& element : elements) {
        if (element && element->declaredName() == name) {
            if (auto result = std::dynamic_pointer_cast<T>(element)) return result;
        }
    }
    return nullptr;
}

// Reads a whole file into a string (binary mode, so CRLF files come back byte-for-byte).
inline std::string readFile(const std::filesystem::path& path) {
    std::ifstream in(path, std::ios::binary);
    std::ostringstream buffer;
    buffer << in.rdbuf();
    return buffer.str();
}

// Parses the file at `path` picking parseKerML/parseSysMLv2 by extension (".kerml" vs. everything
// else), the same rule SysMLv2::Files::Parser::parseFile uses.
inline std::pair<std::vector<std::shared_ptr<KerML::Entities::Element>>, std::vector<std::shared_ptr<SysMLv2::Files::ParserError>>>
parseFile(const std::filesystem::path& path) {
    return SysMLv2::Files::Parser::parseFile(path.string());
}

// Lists regular files under `dir` (recursively) whose extension (with leading '.') is one of
// `extensions`, sorted lexicographically by path for deterministic test enumeration/ordering.
inline std::vector<std::filesystem::path> listFiles(const std::filesystem::path& dir, const std::vector<std::string>& extensions) {
    std::vector<std::filesystem::path> result;
    if (!std::filesystem::exists(dir)) return result;
    for (const auto& entry : std::filesystem::recursive_directory_iterator(dir)) {
        if (!entry.is_regular_file()) continue;
        const auto ext = entry.path().extension().string();
        if (std::find(extensions.begin(), extensions.end(), ext) != extensions.end()) {
            result.push_back(entry.path());
        }
    }
    std::sort(result.begin(), result.end());
    return result;
}

// Loads conformance-test/expected_failures.txt: one relative path (ratchet key) per line; '#'
// starts a line comment (also allowed at the end of a line); blank lines are ignored.
inline std::unordered_set<std::string> loadExpectedFailures(const std::filesystem::path& path) {
    std::unordered_set<std::string> result;
    std::ifstream in(path);
    if (!in) return result;
    std::string line;
    while (std::getline(in, line)) {
        const auto hash = line.find('#');
        if (hash != std::string::npos) line = line.substr(0, hash);
        const auto isSpace = [](unsigned char c) { return std::isspace(c) != 0; };
        while (!line.empty() && isSpace(static_cast<unsigned char>(line.back()))) line.pop_back();
        size_t start = 0;
        while (start < line.size() && isSpace(static_cast<unsigned char>(line[start]))) ++start;
        line = line.substr(start);
        // Normalize accidental backslashes (Windows-style paths pasted into the file) to '/'.
        std::replace(line.begin(), line.end(), '\\', '/');
        if (line.empty()) continue;
        result.insert(line);
    }
    return result;
}

// Turns a path (or any string) into a valid GoogleTest test-name component: alnum runs survive,
// everything else becomes '_'.
inline std::string sanitizeTestName(const std::string& raw) {
    std::string out;
    out.reserve(raw.size());
    for (char c : raw) {
        out.push_back((std::isalnum(static_cast<unsigned char>(c)) != 0) ? c : '_');
    }
    if (out.empty() || std::isdigit(static_cast<unsigned char>(out.front()))) out = "_" + out;
    return out;
}

} // namespace ConformanceTest
