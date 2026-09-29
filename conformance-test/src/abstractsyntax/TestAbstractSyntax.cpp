// AP11: abstract-syntax conformance. The whole standard library is loaded into one Workspace (parsed and resolved) and, per library
// file, the model that our listeners built is compared with the XMI that the OMG pilot implementation exported for the same file
// (resources/sysml.library.xmi; explicit relationships only, NOT sysml.library.xmi.implied): named elements and their metaclasses,
// their owners, the metaclass and visibility of their memberships, aliases and the explicit relationships (see support/ModelDiff.h).
//
// One test per library file. The number of remaining differences per file is ratcheted in conformance-test/expected_xmi_diffs.txt
// (format "library/<path relative to resources/sysml.library>: <count>"; files that are not listed must have 0 differences):
// more differences than listed fails, fewer fails as well ("update the list") so that fixes cannot get lost again.
//
// Environment variables for working on the differences:
//   XMI_DIFF_DUMP=1         print the differences of every file (not only of the failing ones)
//   XMI_DIFF_DUMP_MAX=<n>   at most n differences per category and file are printed (default 30; 0 = all)
//   XMI_DIFF_COUNTS_OUT=<f> append "library/<file>: <count>" for every file with differences to <f> (regenerates the ratchet file)
#include <gtest/gtest.h>

#include <algorithm>
#include <cctype>
#include <chrono>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include <sysmlv2/Workspace.h>

#include "../support/ModelDiff.h"
#include "../support/TestHelpers.h"
#include "../support/XmiReader.h"

#ifndef SYSML_LIBRARY_DIR
#error "SYSML_LIBRARY_DIR must be defined by CMake to the resources/sysml.library path"
#endif
#ifndef SYSML_LIBRARY_XMI_DIR
#error "SYSML_LIBRARY_XMI_DIR must be defined by CMake to the resources/sysml.library.xmi path"
#endif
#ifndef CONFORMANCE_EXPECTED_XMI_DIFFS_FILE
#error "CONFORMANCE_EXPECTED_XMI_DIFFS_FILE must be defined by CMake"
#endif

namespace {

using SysMLv2::Files::SourceLanguage;
using SysMLv2::Files::Workspace;

struct LibraryCase {
    std::filesystem::path absolutePath;
    std::string relativeKey;  // "library/<path relative to SYSML_LIBRARY_DIR>", '/'-separated
};

void PrintTo(const LibraryCase& c, std::ostream* os) { *os << c.relativeKey; }

std::vector<LibraryCase> buildCases() {
    const std::filesystem::path root(SYSML_LIBRARY_DIR);
    std::vector<LibraryCase> cases;
    for (const auto& path : ConformanceTest::listFiles(root, {".sysml", ".kerml"})) {
        cases.push_back({path, "library/" + std::filesystem::relative(path, root).generic_string()});
    }
    return cases;
}

// "library/<file>: <count>", '#' starts a comment
std::map<std::string, size_t> loadExpectedCounts(const std::filesystem::path& path) {
    std::map<std::string, size_t> result;
    std::ifstream in(path);
    std::string line;
    while (std::getline(in, line)) {
        const auto hash = line.find('#');
        if (hash != std::string::npos) line = line.substr(0, hash);
        while (!line.empty() && std::isspace(static_cast<unsigned char>(line.back()))) line.pop_back();
        size_t start = 0;
        while (start < line.size() && std::isspace(static_cast<unsigned char>(line[start]))) ++start;
        line = line.substr(start);
        std::replace(line.begin(), line.end(), '\\', '/');
        const auto colon = line.rfind(':');
        if (line.empty() || colon == std::string::npos) continue;
        std::string key = line.substr(0, colon);
        while (!key.empty() && std::isspace(static_cast<unsigned char>(key.back()))) key.pop_back();
        try {
            result[key] = static_cast<size_t>(std::stoul(line.substr(colon + 1)));
        } catch (...) {
        }
    }
    return result;
}

size_t envNumber(const char* name, size_t fallback) {
    if (const char* value = std::getenv(name)) {
        try {
            return static_cast<size_t>(std::stoul(value));
        } catch (...) {
        }
    }
    return fallback;
}

// The library as one workspace, the oracle and the diff engine; built once.
struct Model {
    Workspace workspace;
    ConformanceTest::Xmi::Corpus corpus{SYSML_LIBRARY_XMI_DIR};
    ConformanceTest::ModelDiff diff{corpus};
    std::map<std::string, size_t> sourceOf;
    double loadSeconds = 0;

    static std::string keyOf(const std::filesystem::path& path) { return path.lexically_normal().generic_string(); }

    Model() {
        const auto start = std::chrono::steady_clock::now();
        workspace.loadLibrary(SYSML_LIBRARY_DIR);
        workspace.resolve();
        loadSeconds = std::chrono::duration<double>(std::chrono::steady_clock::now() - start).count();
        for (size_t i = 0; i < workspace.sourceCount(); ++i) sourceOf[keyOf(workspace.sourceName(i))] = i;
        for (const auto& exclusion : ConformanceTest::documentedXmiExclusions()) diff.addExclusion(exclusion);
    }
};

Model& model() {
    static Model instance;
    return instance;
}

void printDifferences(const ConformanceTest::ModelDiffResult& result, size_t limit) {
    for (const auto& [category, messages] : result.differences) {
        if (messages.empty()) continue;
        std::cout << "  [" << category << "] " << messages.size() << " difference(s)\n";
        size_t shown = 0;
        for (const auto& message : messages) {
            if (limit != 0 && shown++ >= limit) {
                std::cout << "    ... " << (messages.size() - limit) << " more\n";
                break;
            }
            std::cout << "    " << message << "\n";
        }
    }
    for (const auto& [category, reasons] : result.excluded) {
        for (const auto& [reason, count] : reasons) std::cout << "  (excluded " << count << " x " << category << ": " << reason << ")\n";
    }
}

class AbstractSyntaxFile : public ::testing::TestWithParam<LibraryCase> {};

TEST_P(AbstractSyntaxFile, MatchesTheXmiOracle) {
    const auto& testCase = GetParam();
    static const auto expectedCounts = loadExpectedCounts(CONFORMANCE_EXPECTED_XMI_DIFFS_FILE);
    Model& m = model();

    const auto source = m.sourceOf.find(Model::keyOf(testCase.absolutePath));
    ASSERT_NE(source, m.sourceOf.end()) << testCase.relativeKey << " is not part of the workspace";
    const auto xmiPath = m.corpus.fileForSource(testCase.absolutePath);
    ASSERT_TRUE(xmiPath.has_value()) << "no XMI file for " << testCase.relativeKey << " below " << SYSML_LIBRARY_XMI_DIR;

    const auto result = m.diff.compare(m.workspace.elements(source->second), m.corpus.file(*xmiPath));
    EXPECT_GT(result.comparedElements, 0u) << testCase.relativeKey;

    const size_t actual = result.total();
    const auto listed = expectedCounts.find(testCase.relativeKey);
    const size_t expected = listed == expectedCounts.end() ? 0 : listed->second;
    RecordProperty("xmi_differences", std::to_string(actual));

    if (const char* out = std::getenv("XMI_DIFF_COUNTS_OUT")) {
        if (actual > 0) std::ofstream(out, std::ios::app) << testCase.relativeKey << ": " << actual << "\n";
    }
    const bool dump = std::getenv("XMI_DIFF_DUMP") != nullptr;
    if (actual != expected || dump) {
        std::cout << "[  XMI   ] " << testCase.relativeKey << ": " << actual << " difference(s) (listed: " << expected << "; "
                  << result.comparedElements << " elements, " << result.comparedRelationships << " relationships compared, "
                  << result.skippedRelationships << " relationships of anonymous elements skipped)\n";
        printDifferences(result, envNumber("XMI_DIFF_DUMP_MAX", 30));
    }
    if (actual > expected) {
        ADD_FAILURE() << testCase.relativeKey << ": " << actual << " differences from the XMI oracle, but only " << expected
                      << " are listed in expected_xmi_diffs.txt";
    } else if (actual < expected) {
        ADD_FAILURE() << testCase.relativeKey << ": only " << actual << " differences left (listed: " << expected
                      << "); update expected_xmi_diffs.txt";
    }
}

INSTANTIATE_TEST_SUITE_P(SysmlLibrary, AbstractSyntaxFile, ::testing::ValuesIn(buildCases()),
                         [](const ::testing::TestParamInfo<LibraryCase>& info) {
                             return ConformanceTest::sanitizeTestName(info.param.relativeKey);
                         });

// Every library source has exactly one XMI file and vice versa.
TEST(XmiOracle, EveryLibrarySourceHasAnXmiFileAndViceVersa) {
    ConformanceTest::Xmi::Corpus corpus(SYSML_LIBRARY_XMI_DIR);
    const auto xmiFiles = corpus.listFiles();
    const auto sources = ConformanceTest::listFiles(SYSML_LIBRARY_DIR, {".sysml", ".kerml"});
    EXPECT_EQ(xmiFiles.size(), sources.size());
    std::map<std::string, int> stems;
    for (const auto& source : sources) ++stems[source.stem().string()];
    for (const auto& xmi : xmiFiles) --stems[xmi.stem().string()];
    for (const auto& [stem, balance] : stems) EXPECT_EQ(balance, 0) << stem;
}

// The reader understands the format: root namespace, ownership through relationships, references by id and by href.
TEST(XmiOracle, ReaderHandlesTheStructureOfAnXmiFile) {
    ConformanceTest::Xmi::Corpus corpus(SYSML_LIBRARY_XMI_DIR);
    const auto path = corpus.fileForSource("Base.kerml");
    ASSERT_TRUE(path.has_value());
    const auto& file = corpus.file(*path);
    ASSERT_FALSE(file.elements.empty());
    EXPECT_EQ(file.elements[0].type, "Namespace");
    EXPECT_EQ(file.elements[0].parent, -1);
    int anything = -1;
    for (size_t i = 0; i < file.elements.size(); ++i) {
        if (file.elements[i].name == "Anything") anything = static_cast<int>(i);
    }
    ASSERT_GE(anything, 0);
    EXPECT_EQ(file.elements[static_cast<size_t>(anything)].type, "Classifier");
    EXPECT_EQ(corpus.qualifiedName(file, anything).value_or("?"), "Base::Anything");
    const auto owning = file.elements[static_cast<size_t>(file.elements[static_cast<size_t>(anything)].owningRelationship)];
    EXPECT_EQ(owning.type, "OwningMembership");
    // a reference by id: Anything::self is typed by Anything
    bool found = false;
    for (size_t i = 0; i < file.elements.size(); ++i) {
        const auto& element = file.elements[i];
        if (element.type == "FeatureTyping" && element.parent >= 0 && file.elements[static_cast<size_t>(element.parent)].name == "self") {
            const auto* reference = element.reference("type");
            ASSERT_NE(reference, nullptr);
            const auto [target, index] = corpus.resolve(file, *reference);
            ASSERT_NE(target, nullptr);
            EXPECT_EQ(corpus.qualifiedName(*target, index).value_or("?"), "Base::Anything");
            found = true;
            break;
        }
    }
    EXPECT_TRUE(found);
    // names in qualified names are quoted like in the textual notation
    EXPECT_EQ(ConformanceTest::Xmi::joinQualifiedName("ISQ", "mass of body"), "ISQ::'mass of body'");
    EXPECT_EQ(ConformanceTest::Xmi::unquoteName("'a\\'b'"), "a'b");
}

}  // namespace
