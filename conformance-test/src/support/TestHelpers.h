//
// Shared helpers for the conformance-test suites (AP1/AP2/AP4(e) of the test plan).
//
#pragma once

#include <algorithm>
#include <cctype>
#include <cstdlib>
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
#include <kerml/root/elements/Relationship.h>
#include <kerml/core/types/Type.h>
#include <kerml/core/types/Specialization.h>
#include <sysmlv2/resolution/ResolutionData.h>

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

// The name of an element made of the names of the namespaces that own it (an unnamed element is written as <Metaclass>); the root
// namespace of a source contributes nothing. Works for the elements of every source, whether or not qualifiedName() was set.
inline std::string qualifiedNameOf(const std::shared_ptr<KerML::Entities::Element>& element) {
    std::string result;
    for (auto current = element; current; current = current->owner()) {
        // (the root namespace of a source has no owner: it is named "Root Namespace" in the text and has no name in the XMI)
        if (std::dynamic_pointer_cast<KerML::Entities::Relationship>(current) || current->owner() == nullptr) continue;
        std::string part;
        // (a feature without a declared name, `:>> p`, is known by the name of the feature it redefines)
        if (const auto effective = current->effectiveName(); effective.has_value() && !effective->empty()) part = effective.value();
        else if (current->declaredShortName().has_value()) part = current->declaredShortName().value();
        else part = "<" + current->getType() + ">";
        result = result.empty() ? part : part + "::" + result;
    }
    return result;
}

// What the references of `elements` resolved to: one line "<type> :> <general 1>, <general 2>, ..." for every type with specializations
// (typings, subsettings, redefinitions, ... in the order of the type's specializations), sorted. A target that is still a placeholder is
// written as ?<name>. Two runs that resolved every reference to the same element give the same lines.
inline std::vector<std::string> resolvedGenerals(const std::vector<std::shared_ptr<KerML::Entities::Element>>& elements) {
    std::vector<std::string> lines;
    for (const auto& element : elements) {
        const auto type = std::dynamic_pointer_cast<KerML::Entities::Type>(element);
        if (!type) continue;
        const auto specializations = type->ownedSpecialization();
        if (specializations.empty()) continue;
        std::string line = qualifiedNameOf(type) + " :>";
        for (const auto& specialization : specializations) {
            const auto general = specialization ? specialization->general() : nullptr;
            line += (general && SysMLv2::Files::isUnresolved(general)) ? " ?" + general->declaredName().value_or("") + ","
                                                                         : " " + (general ? qualifiedNameOf(general) : std::string("-")) + ",";
        }
        lines.push_back(std::move(line));
    }
    std::sort(lines.begin(), lines.end());
    return lines;
}


// Expects the two sets of lines of resolvedGenerals() to be equal and reports (the first) lines that only one of them has.
inline void expectSameLines(const std::vector<std::string>& actual, const std::vector<std::string>& expected, const std::string& what) {
    std::vector<std::string> onlyActual, onlyExpected;
    std::set_difference(actual.begin(), actual.end(), expected.begin(), expected.end(), std::back_inserter(onlyActual));
    std::set_difference(expected.begin(), expected.end(), actual.begin(), actual.end(), std::back_inserter(onlyExpected));
    EXPECT_EQ(actual.size(), expected.size()) << what;
    for (size_t index = 0; index < onlyActual.size() && index < 10; ++index) ADD_FAILURE() << what << ": only in the first: " << onlyActual[index];
    for (size_t index = 0; index < onlyExpected.size() && index < 10; ++index) ADD_FAILURE() << what << ": only in the second: " << onlyExpected[index];
}


// Timing / performance assertions only run when SYSML_ENABLE_PERFORMANCE_TESTS is set to a non-empty value other than "0"; they depend
// on the machine and must not fail CI.
inline bool performanceTestsEnabled() {
    const char* env = std::getenv("SYSML_ENABLE_PERFORMANCE_TESTS");
    return env != nullptr && env[0] != '\0' && std::string(env) != "0";
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
