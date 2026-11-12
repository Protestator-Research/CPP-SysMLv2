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
#include <chrono>
#include <cstdint>
#include <functional>
#include <filesystem>
#include <exception>
#include <random>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

#include <sysmlv2/Workspace.h>
#include <sysmlv2/detail/WorkspaceTesting.h>

#if defined(__GLIBC__)
#include <malloc.h>
#endif
#if defined(__unix__) || defined(__APPLE__)
#include <pthread.h>
#define SYSML_TEST_SMALL_STACK_THREADS 1
#endif

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


// ---------------------------------------------------------------------------------------------------------------------------------------
// Deeply nested and very long texts. A legitimate text of a large size (a sum of 10000 terms, a sequence of 10000 elements, a qualified name of 5000
// segments, ...) must be accepted: loaded, resolved, written as XMI, serialised to JSON, replaced and released. A text that is nested far deeper than
// the limits of the library (100000 and more) ends in one of two ways: it is handled (no error), or it is rejected with the one error "nesting too
// deep" -- never a crash (stack overflow of the parser, of the walk over the parse tree, of the resolver, of the writer, of the destruction of the
// model) and never a hang. Which texts are rejected does not depend on the speed of the machine (the limits count nesting and look-ahead, not time);
// the only time that these tests look at is a generous limit for the whole load, to find a hang.
// The workspace is loaded on a thread with a 1 MB stack (the stack of a Windows main thread); the parser itself runs on a thread of its own with a
// large stack, as does the name resolution.
// ---------------------------------------------------------------------------------------------------------------------------------------

constexpr size_t kSmallStackBytes = size_t(1) << 20;
constexpr double kTimeLimitSeconds = 300.0;

enum class Kind { Sum, Sequence, Parentheses, Packages, FeatureChain, QualifiedName, ArrowInvocations, Conditionals, Negations };

struct KindInfo {
    const char* name;
    size_t legitimate;     // a size that every text of the kind may have: it must be accepted
    size_t excessive;      // a size far over the limits
    bool mustReject;       // the text of the excessive size is rejected (else it may be accepted as well)
    const char* rejection; // what the message of the rejection starts with
};

KindInfo kindInfoOf(Kind kind) {
    constexpr const char* recursion = "nesting too deep";
    constexpr const char* tree = "text too large for the stack";
    switch (kind) {
        case Kind::Sum: return {"sum", 50000, 250000, true, tree};
        case Kind::Sequence: return {"sequence", 50000, 250000, true, tree};
        case Kind::Parentheses: return {"parentheses", 1000, 100000, true, recursion};
        case Kind::Packages: return {"packages", 1000, 100000, true, recursion};
        case Kind::FeatureChain: return {"feature_chain", 10000, 250000, true, tree};
        case Kind::QualifiedName: return {"qualified_name", 5000, 100000, false, tree};
        case Kind::ArrowInvocations: return {"arrow_invocations", 2000, 250000, true, tree};
        case Kind::Conditionals: return {"conditionals", 1000, 60000, true, recursion};
        case Kind::Negations: return {"negations", 5000, 60000, true, recursion};
    }
    return {"?", 0, 0, false, ""};
}

std::string repeat(const std::string& text, size_t count, const std::string& separator = "") {
    std::string result;
    result.reserve(count * (text.size() + separator.size()));
    for (size_t index = 0; index < count; ++index) {
        if (index != 0) result += separator;
        result += text;
    }
    return result;
}

std::string deepText(Kind kind, size_t count, bool kerml) {
    const std::string feature = kerml ? "feature" : "attribute";
    const std::string head = "package P { " + feature + " x = ";
    switch (kind) {
        case Kind::Sum: return head + repeat("1", count, " + ") + "; }";
        case Kind::Sequence: return head + "(" + repeat("1", count, ", ") + "); }";
        case Kind::Parentheses: return head + repeat("(", count) + "1" + repeat(")", count) + "; }";
        case Kind::Packages: return repeat("package a { import a::**; ", count) + repeat("}", count);
        case Kind::FeatureChain: return head + "a" + repeat(".b", count) + "; }";
        case Kind::QualifiedName: return "package P { " + feature + " x : a" + repeat("::a", count) + "; }";
        case Kind::ArrowInvocations: return head + "1" + repeat("->DataFunctions::'+'(1)", count) + "; }";
        case Kind::Conditionals: return head + repeat("if true ? ", count) + "1" + repeat(" else 2", count) + "; }";
        case Kind::Negations: return head + repeat("-", count) + "1; }";
    }
    return {};
}

struct DeepOutcome {
    bool finished = false;
    std::string exception;
    std::vector<std::string> errors;
    std::vector<std::string> xmiErrors;
    bool json = false;
    double seconds = 0;
};

// Loads `text` into a workspace, resolves it, writes it as XMI, serialises the feature P::x to JSON, replaces the source (which releases the model),
// resolves again and destroys the workspace.
void loadResolveAndRelease(const std::string& text, bool kerml, bool alsoSingleText, DeepOutcome& outcome) {
    const auto begin = std::chrono::steady_clock::now();
    try {
        const auto language = kerml ? SysMLv2::Files::SourceLanguage::KerML : SysMLv2::Files::SourceLanguage::SysML;
        SysMLv2::Files::Workspace workspace;
        const size_t source = workspace.addText(text, "deep", language);
        workspace.resolve();
        for (const auto& error : workspace.errors(source)) {
            if (error->errorType() != SysMLv2::Files::ErrorType::WARNING) outcome.errors.push_back(error->description());
        }
        if (outcome.errors.empty()) {
            const auto directory = std::filesystem::temp_directory_path() / ("deep_" + std::to_string(reinterpret_cast<std::uintptr_t>(&outcome)));
            std::filesystem::create_directories(directory);
            // (without indentation: the indentation of the default format is one step per level of nesting for every line, which for a model that is
            // 50000 levels deep is a file of gigabytes)
            SysMLv2::Files::XmiWriteOptions options;
            options.indent.clear();
            for (const auto& error : workspace.writeXmi(source, (directory / "deep.sysmlx").string(), options)) {
                if (error->errorType() == SysMLv2::Files::ErrorType::INTERNAL_ERROR) outcome.xmiErrors.push_back(error->description());
            }
            std::filesystem::remove_all(directory);
            if (const auto feature = workspace.find("P::x")) outcome.json = !feature->serializeToJson().empty();
        }
        workspace.replaceSource(source, "package Q;", language);
        workspace.resolve();
        if (alsoSingleText) {
            // the same text through the single-text API (only for the small result of a rejected text: the models of accepted texts are cyclic and not
            // freed when a workspace ends, which is costly for a text of this size)
            const auto result = kerml ? SysMLv2::Files::Parser::parseKerML(text) : SysMLv2::Files::Parser::parseSysMLv2(text);
            std::vector<std::string> again;
            for (const auto& error : result.second) {
                if (error->errorType() != SysMLv2::Files::ErrorType::WARNING) again.push_back(error->description());
            }
            if (again.size() != outcome.errors.size()) outcome.errors.push_back("Parser::parse* reports " + std::to_string(again.size()) + " errors");
        }
        outcome.finished = true;
    } catch (const std::exception& ex) {
        outcome.exception = ex.what();
    } catch (...) {
        outcome.exception = "unknown exception";
    }
    outcome.seconds = std::chrono::duration<double>(std::chrono::steady_clock::now() - begin).count();
}

// Runs loadResolveAndRelease() on a thread with a 1 MB stack (where the platform lets us choose it, else on the calling thread).
DeepOutcome loadOnSmallStack(const std::string& text, bool kerml, bool alsoSingleText, size_t stackBytes = kSmallStackBytes) {
    DeepOutcome outcome;
#ifdef SYSML_TEST_SMALL_STACK_THREADS
    struct Job {
        const std::string* text;
        bool kerml;
        bool alsoSingleText;
        DeepOutcome* outcome;
    } job{&text, kerml, alsoSingleText, &outcome};
    pthread_attr_t attributes;
    pthread_attr_init(&attributes);
    pthread_attr_setstacksize(&attributes, stackBytes);
    pthread_t thread;
    const int created = pthread_create(&thread, &attributes, [](void* argument) -> void* {
        auto* work = static_cast<Job*>(argument);
        loadResolveAndRelease(*work->text, work->kerml, work->alsoSingleText, *work->outcome);
        return nullptr;
    }, &job);
    pthread_attr_destroy(&attributes);
    if (created == 0) {
        pthread_join(thread, nullptr);
        return outcome;
    }
#endif
    loadResolveAndRelease(text, kerml, alsoSingleText, outcome);
    return outcome;
}

class DeepNestingTest : public ::testing::TestWithParam<std::tuple<Kind, bool>> {};

TEST_P(DeepNestingTest, ALegitimateLargeTextIsAcceptedWrittenAndReleased) {
    const auto [kind, kerml] = GetParam();
    const KindInfo kindInfo = kindInfoOf(kind);
    const DeepOutcome outcome = loadOnSmallStack(deepText(kind, kindInfo.legitimate, kerml), kerml, false);
    EXPECT_TRUE(outcome.finished) << outcome.exception;
    EXPECT_TRUE(outcome.errors.empty()) << kindInfo.name << ": " << (outcome.errors.empty() ? "" : outcome.errors.front());
    EXPECT_TRUE(outcome.xmiErrors.empty()) << kindInfo.name << ": " << (outcome.xmiErrors.empty() ? "" : outcome.xmiErrors.front());
    if (kind != Kind::Packages) EXPECT_TRUE(outcome.json) << kindInfo.name << ": no JSON";
    EXPECT_LT(outcome.seconds, kTimeLimitSeconds) << kindInfo.name << " took " << outcome.seconds << " s";
}

TEST_P(DeepNestingTest, ATextFarOverTheLimitsIsRejectedWithOneCleanError) {
    const auto [kind, kerml] = GetParam();
    const KindInfo kindInfo = kindInfoOf(kind);
    const DeepOutcome outcome = loadOnSmallStack(deepText(kind, kindInfo.excessive, kerml), kerml, true);
    EXPECT_TRUE(outcome.finished) << outcome.exception;
    EXPECT_LT(outcome.seconds, kTimeLimitSeconds) << kindInfo.name << " took " << outcome.seconds << " s";
    if (kindInfo.mustReject) EXPECT_EQ(outcome.errors.size(), 1u) << kindInfo.name << " was not rejected";
    if (!outcome.errors.empty()) {
        ASSERT_EQ(outcome.errors.size(), 1u) << kindInfo.name << ": " << outcome.errors.front();
        EXPECT_EQ(outcome.errors.front().rfind(kindInfo.rejection, 0), 0u) << kindInfo.name << ": " << outcome.errors.front();
    }
}

INSTANTIATE_TEST_SUITE_P(
    Kinds, DeepNestingTest,
    ::testing::Combine(::testing::Values(Kind::Sum, Kind::Sequence, Kind::Parentheses, Kind::Packages, Kind::FeatureChain, Kind::QualifiedName,
                                         Kind::ArrowInvocations, Kind::Conditionals, Kind::Negations),
                       ::testing::Bool()),
    [](const ::testing::TestParamInfo<std::tuple<Kind, bool>>& info_) {
        return std::string(kindInfoOf(std::get<0>(info_.param)).name) + (std::get<1>(info_.param) ? "_KerML" : "_SysML");
    });


// ---------------------------------------------------------------------------------------------------------------------------------------
// Flat texts of any size are accepted: the limits are for the nesting and the look-ahead, not for the size of a file.
// ---------------------------------------------------------------------------------------------------------------------------------------

struct FlatShape {
    const char* name;
    bool kerml;
    std::function<std::string()> text;
};

std::string many(const std::string& pattern, size_t count) {
    // every '#' of the pattern is the number of the repetition
    std::string result;
    for (size_t index = 0; index < count; ++index) {
        for (const char c : pattern) {
            if (c == '#') result += std::to_string(index);
            else result.push_back(c);
        }
    }
    return result;
}

TEST(FlatTexts, LargeFlatTextsAreAccepted) {
    const std::vector<FlatShape> shapes = {
        {"sysml part def with 2500 attributes", false, [] { return "package P { part def Big { " + many("attribute a# : ScalarValues::Real = #.0; ", 2500) + "} }"; }},
        {"sysml package with 3000 attributes", false, [] { return "package P { " + many("attribute a# : ScalarValues::Real = #.0; ", 3000) + "}"; }},
        {"sysml 2000 requirement defs", false, [] { return "package P { " + many("requirement def R# { doc /* text # */ } ", 2000) + "}"; }},
        {"kerml package with 5000 features", true, [] { return "package P { " + many("feature a# : ScalarValues::Real = 1.5; ", 5000) + "}"; }},
        {"kerml library package with 5000 features", true, [] { return "library package P { " + many("feature a# : ScalarValues::Real = 1.5; ", 5000) + "}"; }},
        {"sysml sequence of 20000 values", false, [] { return "package P { attribute x = (" + many("#.5, ", 19999) + "1.5); }"; }},
        {"kerml sequence of 20000 values", true, [] { return "package P { feature x = (" + many("#.5, ", 19999) + "1.5); }"; }},
        {"sysml sum of 15000 terms", false, [] { return "package P { attribute x = " + many("# + ", 14999) + "1; }"; }},
        {"kerml sum of 15000 terms", true, [] { return "package P { feature x = " + many("# + ", 14999) + "1; }"; }},
    };
    for (const auto& shape : shapes) {
        SCOPED_TRACE(shape.name);
        const std::string text = shape.text();
        const DeepOutcome outcome = loadOnSmallStack(text, shape.kerml, false);
        EXPECT_TRUE(outcome.finished) << outcome.exception;
        EXPECT_TRUE(outcome.errors.empty()) << (outcome.errors.empty() ? "" : outcome.errors.front());
        EXPECT_LT(outcome.seconds, kTimeLimitSeconds);
    }
}

// ---------------------------------------------------------------------------------------------------------------------------------------
// The limits follow the stack that the parse runs on. The inline path (no thread with a large stack can be made) is forced by a hook of the workspace.
// ---------------------------------------------------------------------------------------------------------------------------------------

class ParseStackGuard {
public:
    ParseStackGuard(bool inlineParsing, size_t stackBytes) { SysMLv2::Files::detail::setParseStackForTesting(inlineParsing, stackBytes); }
    ~ParseStackGuard() { SysMLv2::Files::detail::setParseStackForTesting(false, 0); }
};

// Where no thread with a large stack can be made, the text is parsed on the calling thread, and the limits follow what is left of its stack (the
// text of a few levels works on 128 KB, a text that is deeper than the stack takes is rejected, nothing crashes).
TEST(ParseStack, TheInlinePathFollowsTheStackThatIsLeft) {
    ParseStackGuard guard(true, 0);
    const auto limitMessage = [](const std::string& message) {
        return message.rfind("nesting too deep", 0) == 0 || message.rfind("text too large for the stack", 0) == 0;
    };
    for (const size_t stackBytes : {size_t(128) << 10, size_t(256) << 10, size_t(1) << 20}) {
        for (const bool kerml : {true, false}) {
            SCOPED_TRACE(std::string(kerml ? "KerML " : "SysML ") + std::to_string(stackBytes >> 10) + " KB");
            const DeepOutcome tiny = loadOnSmallStack(kerml ? "feature x;" : "part x;", kerml, false, stackBytes);
            EXPECT_TRUE(tiny.finished) << tiny.exception;
            EXPECT_TRUE(tiny.errors.empty()) << (tiny.errors.empty() ? "" : tiny.errors.front());
            if (stackBytes > (size_t(128) << 10)) {
                EXPECT_TRUE(loadOnSmallStack(deepText(Kind::Sum, 10, kerml), kerml, false, stackBytes).errors.empty());
            }
            for (const Kind kind : {Kind::Sum, Kind::Parentheses}) {
                const DeepOutcome deep = loadOnSmallStack(deepText(kind, kind == Kind::Sum ? 2000 : 300, kerml), kerml, false, stackBytes);
                EXPECT_TRUE(deep.finished) << deep.exception;
                ASSERT_EQ(deep.errors.size(), 1u) << kindInfoOf(kind).name;
                EXPECT_TRUE(limitMessage(deep.errors[0])) << deep.errors[0];
                EXPECT_NE(deep.errors[0].find(" KB)"), std::string::npos) << deep.errors[0];   // (the stack is named in KB below 1 MB)
            }
        }
    }
}

TEST(ParseStack, ASmallerThreadStackScalesTheLimits) {
    ParseStackGuard guard(false, size_t(32) << 20);   // what the workspace falls back to when 512 and 128 MB are not available
    for (const bool kerml : {true, false}) {
        SCOPED_TRACE(kerml ? "KerML" : "SysML");
        EXPECT_TRUE(loadOnSmallStack(deepText(Kind::Sum, 10000, kerml), kerml, false).errors.empty());   // limit of the tree: 14600
        const DeepOutcome sum = loadOnSmallStack(deepText(Kind::Sum, 20000, kerml), kerml, false);
        ASSERT_EQ(sum.errors.size(), 1u);
        EXPECT_NE(sum.errors[0].find("a stack of 32 MB"), std::string::npos) << sum.errors[0];
    }
}

#if defined(__GLIBC__)
// ---------------------------------------------------------------------------------------------------------------------------------------
// A regression guard: the memory of a text that was rejected is given back. (Since the grammars no longer read to the end of a package for every level
// of the nesting, a rejected text leaves next to nothing behind with or without the cleanup of the prediction caches; the tests of the Lookahead
// suite above are the ones that run the cleanup.)
// ---------------------------------------------------------------------------------------------------------------------------------------

size_t heapInUseBytes() {
    malloc_trim(0);
#if defined(__GLIBC_PREREQ) && __GLIBC_PREREQ(2, 33)
    const struct mallinfo2 info = mallinfo2();
#else
    const struct mallinfo info = mallinfo();
#endif
    return static_cast<size_t>(info.uordblks) + static_cast<size_t>(info.hblkhd);
}

TEST(Memory, TheMemoryOfARejectedTextIsGivenBack) {
    for (const bool kerml : {true, false}) {
        SCOPED_TRACE(kerml ? "KerML" : "SysML");
        // (a small text first: the caches of the parser, the lexer and the library start at their size for a small text)
        loadOnSmallStack(deepText(Kind::Sum, 10, kerml), kerml, false);
        const size_t before = heapInUseBytes();
        for (const Kind kind : {Kind::Packages, Kind::Parentheses, Kind::Conditionals, Kind::Negations}) {
            const DeepOutcome outcome = loadOnSmallStack(deepText(kind, 20000, kerml), kerml, false);
            EXPECT_EQ(outcome.errors.size(), 1u) << kindInfoOf(kind).name;
        }
        const size_t after = heapInUseBytes();
        EXPECT_LT(after, before + (size_t(64) << 20)) << "before " << (before >> 20) << " MB, after " << (after >> 20) << " MB";
    }
}
#endif


// ---------------------------------------------------------------------------------------------------------------------------------------
// The look-ahead budget and the cleanup of the prediction caches, end to end.
// ---------------------------------------------------------------------------------------------------------------------------------------

std::string longName(size_t segments, bool kerml) {
    return std::string("package P { ") + (kerml ? "feature" : "attribute") + " x : a" + repeat("::a", segments) + "; }";
}

// The decision that has to see whether a `.` follows a name reads the whole name: 2000 segments are 4000 tokens, more than the 2000 units after which
// the workspace empties the caches of the language. The parse is correct every time, the caches are emptied every time (and built up again).
TEST(Lookahead, ALongNameEmptiesThePredictionCachesAndTheResultStaysCorrect) {
    for (const bool kerml : {true, false}) {
        SCOPED_TRACE(kerml ? "KerML" : "SysML");
        for (int round = 0; round < 3; ++round) {
            const size_t before = SysMLv2::Files::detail::predictionCacheCleanups();
            const auto result = kerml ? SysMLv2::Files::Parser::parseKerML(longName(2000, true)) : SysMLv2::Files::Parser::parseSysMLv2(longName(2000, false));
            size_t errors = 0;
            for (const auto& error : result.second) errors += error->errorType() != SysMLv2::Files::ErrorType::WARNING ? 1 : 0;
            EXPECT_EQ(errors, 0u) << "round " << round;
            bool found = false;
            for (const auto& element : result.first) found = found || (element && element->declaredName() == "x");
            EXPECT_TRUE(found) << "round " << round;
            EXPECT_GE(SysMLv2::Files::detail::predictionCacheCleanups(), before + 1) << "round " << round;
        }
    }
}

// A name of about 520000 segments (1.04 million tokens) needs more than the 1 million units of one decision.
TEST(Lookahead, ANameOfHalfAMillionSegmentsExceedsTheBudgetOfOneDecision) {
    for (const bool kerml : {true, false}) {
        SCOPED_TRACE(kerml ? "KerML" : "SysML");
        const size_t before = SysMLv2::Files::detail::predictionCacheCleanups();
        const auto result = kerml ? SysMLv2::Files::Parser::parseKerML(longName(520000, true)) : SysMLv2::Files::Parser::parseSysMLv2(longName(520000, false));
        ASSERT_EQ(result.second.size(), 1u);
        EXPECT_EQ(result.second[0]->description().rfind("look-ahead budget exceeded: one decision of the parser needs more than 1000000 units", 0), 0u)
            << result.second[0]->description();
        EXPECT_TRUE(result.first.empty());
        EXPECT_GE(SysMLv2::Files::detail::predictionCacheCleanups(), before + 1);
    }
}

} // namespace
