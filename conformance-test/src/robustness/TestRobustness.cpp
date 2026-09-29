// AP4(e): deterministic fuzz suite. For every resources/sysml.library file of at most 20 KB (larger
// files, e.g. SI.sysml at ~18s/parse, are excluded to keep runtime reasonable), this generates:
//   - truncations of the source text at 6 fixed fractions of its length, and
//   - 8 random single-"token" (whitespace-delimited word) deletions, using a std::mt19937 seeded
//     deterministically from the file's relative path so results are stable across runs/machines,
// for >= 1000 mutated inputs total across both languages (see the SetUpTestSuite check below), and
// asserts SysMLv2::Files::Parser::parseKerML/parseSysMLv2 always returns normally -- no crash
// (checked by the process still being alive to report the result) and no exception escapes.
// Syntax errors on a mutated/truncated input are expected and are not a failure.
#include <gtest/gtest.h>

#include <atomic>
#include <cctype>
#include <random>
#include <sstream>
#include <string>
#include <vector>

#include "../support/TestHelpers.h"

#ifndef SYSML_LIBRARY_DIR
#error "SYSML_LIBRARY_DIR must be defined by CMake to the resources/sysml.library path"
#endif

namespace {

constexpr size_t kMaxFuzzFileBytes = 20 * 1024;
constexpr int kTruncationPoints = 6;
constexpr int kWordDeletions = 8;

std::atomic<long> gGeneratedInputCount{0};

struct FuzzCase {
    std::filesystem::path absolutePath;
    std::string relativeKey;
    bool isKerML = false;
};

// Lets gtest failure output show the relative path instead of a raw byte dump of the struct.
void PrintTo(const FuzzCase& c, std::ostream* os) { *os << c.relativeKey; }

std::vector<FuzzCase> buildCases() {
    const std::filesystem::path root(SYSML_LIBRARY_DIR);
    std::vector<FuzzCase> cases;
    for (const auto& path : ConformanceTest::listFiles(root, {".sysml", ".kerml"})) {
        if (std::filesystem::file_size(path) > kMaxFuzzFileBytes) continue;
        auto rel = std::filesystem::relative(path, root).generic_string();
        cases.push_back({path, rel, path.extension() == ".kerml"});
    }
    return cases;
}

// A whitespace-delimited word's [start, end) byte range within the original text.
struct WordSpan {
    size_t start;
    size_t end;
};

// Records word ranges instead of copying words out, so dropWord() below can delete a word from
// the ORIGINAL text in place, preserving every other byte (including newlines) exactly. Rejoining
// words with a single space (the previous approach) collapsed all whitespace, which could turn a
// "//" line comment into a comment that swallows the rest of the file.
std::vector<WordSpan> splitWordSpans(const std::string& text) {
    std::vector<WordSpan> spans;
    size_t i = 0;
    const size_t n = text.size();
    while (i < n) {
        while (i < n && std::isspace(static_cast<unsigned char>(text[i]))) ++i;
        if (i >= n) break;
        const size_t start = i;
        while (i < n && !std::isspace(static_cast<unsigned char>(text[i]))) ++i;
        spans.push_back({start, i});
    }
    return spans;
}

std::string dropWord(const std::string& text, const std::vector<WordSpan>& spans, size_t indexToDrop) {
    std::string result = text;
    const auto& span = spans[indexToDrop];
    result.erase(span.start, span.end - span.start);
    return result;
}

// Deterministic per-file seed: FNV-1a hash of the relative path.
uint32_t seedFor(const std::string& relativeKey) {
    uint32_t hash = 2166136261u;
    for (unsigned char c : relativeKey) {
        hash ^= c;
        hash *= 16777619u;
    }
    return hash;
}

void assertParsesWithoutCrash(bool isKerML, const std::string& text, const std::string& description) {
    ++gGeneratedInputCount;
    try {
        if (isKerML) {
            auto result = SysMLv2::Files::Parser::parseKerML(text);
            (void)result;
        } else {
            auto result = SysMLv2::Files::Parser::parseSysMLv2(text);
            (void)result;
        }
    } catch (const std::exception& ex) {
        ADD_FAILURE() << description << " threw: " << ex.what();
    } catch (...) {
        ADD_FAILURE() << description << " threw an unknown exception";
    }
}

class RobustnessFuzzTest : public ::testing::TestWithParam<FuzzCase> {
public:
    static void TearDownTestSuite() {
        EXPECT_GE(gGeneratedInputCount.load(), 1000)
            << "AP4(e) requires >= 1000 fuzzed inputs total across both languages; only generated "
            << gGeneratedInputCount.load();
    }
};

TEST_P(RobustnessFuzzTest, TruncationsAndWordDeletionsDoNotCrash) {
    const auto& testCase = GetParam();
    const std::string content = ConformanceTest::readFile(testCase.absolutePath);
    if (content.empty()) GTEST_SKIP() << "empty file";

    for (int i = 1; i <= kTruncationPoints; ++i) {
        const double fraction = static_cast<double>(i) / (kTruncationPoints + 1); // 1/7 .. 6/7
        const size_t cut = static_cast<size_t>(content.size() * fraction);
        assertParsesWithoutCrash(testCase.isKerML, content.substr(0, cut),
                                  testCase.relativeKey + " truncated at " + std::to_string(cut) + " bytes");
    }

    const auto wordSpans = splitWordSpans(content);
    if (!wordSpans.empty()) {
        std::mt19937 rng(seedFor(testCase.relativeKey));
        std::uniform_int_distribution<size_t> dist(0, wordSpans.size() - 1);
        for (int i = 0; i < kWordDeletions; ++i) {
            const size_t dropIndex = dist(rng);
            assertParsesWithoutCrash(testCase.isKerML, dropWord(content, wordSpans, dropIndex),
                                      testCase.relativeKey + " with word #" + std::to_string(dropIndex) + " deleted");
        }
    }
}

INSTANTIATE_TEST_SUITE_P(
    LibraryFuzz, RobustnessFuzzTest, ::testing::ValuesIn(buildCases()),
    [](const ::testing::TestParamInfo<FuzzCase>& info) { return ConformanceTest::sanitizeTestName(info.param.relativeKey); });

} // namespace
