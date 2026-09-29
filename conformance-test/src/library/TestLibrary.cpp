// AP2: one test per resources/sysml.library file. A file passes if it parses without crashing or
// throwing, with zero syntax errors, within a time budget. Ratcheted against expected_failures.txt
// (entries prefixed "library/") so that known-bad library files don't block the suite, while
// silently fixing them is caught ("remove from expected_failures.txt").
#include <gtest/gtest.h>

#include <chrono>
#include <cstdlib>
#include <string>
#include <vector>

#include "../support/TestHelpers.h"

#ifndef SYSML_LIBRARY_DIR
#error "SYSML_LIBRARY_DIR must be defined by CMake to the resources/sysml.library path"
#endif
#ifndef CONFORMANCE_EXPECTED_FAILURES_FILE
#error "CONFORMANCE_EXPECTED_FAILURES_FILE must be defined by CMake"
#endif

namespace {

long parseBudgetMs() {
    if (const char* env = std::getenv("SYSML_PARSE_BUDGET_MS")) {
        try {
            return std::stol(env);
        } catch (...) {
            // fall through to default
        }
    }
    return 5000;
}

struct LibraryCase {
    std::filesystem::path absolutePath;
    std::string relativeKey; // "library/<path relative to SYSML_LIBRARY_DIR>", '/'-separated
};

// Lets gtest failure output show the relative path instead of a raw byte dump of the struct.
void PrintTo(const LibraryCase& c, std::ostream* os) { *os << c.relativeKey; }

std::vector<LibraryCase> buildCases() {
    const std::filesystem::path root(SYSML_LIBRARY_DIR);
    std::vector<LibraryCase> cases;
    for (const auto& path : ConformanceTest::listFiles(root, {".sysml", ".kerml"})) {
        auto rel = std::filesystem::relative(path, root).generic_string();
        cases.push_back({path, "library/" + rel});
    }
    return cases;
}

class LibraryFileTest : public ::testing::TestWithParam<LibraryCase> {};

TEST_P(LibraryFileTest, ParsesCleanly) {
    const auto& testCase = GetParam();
    static const auto expectedFailures = ConformanceTest::loadExpectedFailures(CONFORMANCE_EXPECTED_FAILURES_FILE);
    const long budgetMs = parseBudgetMs();

    bool crashed = false;
    std::string crashMessage;
    size_t errorCount = 0;
    long elapsedMs = 0;

    const auto start = std::chrono::steady_clock::now();
    try {
        auto [elements, errors] = ConformanceTest::parseFile(testCase.absolutePath);
        (void)elements;
        errorCount = errors.size();
    } catch (const std::exception& ex) {
        crashed = true;
        crashMessage = ex.what();
    } catch (...) {
        crashed = true;
        crashMessage = "unknown exception";
    }
    elapsedMs = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count();

    const bool overBudget = elapsedMs > budgetMs;
    const bool failed = crashed || errorCount > 0 || overBudget;
    const bool listedAsExpectedFailure = expectedFailures.count(testCase.relativeKey) > 0;

    if (failed) {
        if (listedAsExpectedFailure) {
            std::string reason = crashed ? ("crash/exception: " + crashMessage)
                                : overBudget ? ("over budget: " + std::to_string(elapsedMs) + "ms > " + std::to_string(budgetMs) + "ms")
                                : (std::to_string(errorCount) + " syntax error(s)");
            GTEST_SKIP() << "expected failure (" << testCase.relativeKey << "): " << reason;
        } else {
            if (crashed) {
                ADD_FAILURE() << testCase.relativeKey << " crashed/threw: " << crashMessage;
            } else if (overBudget) {
                ADD_FAILURE() << testCase.relativeKey << " exceeded parse budget: " << elapsedMs << "ms > " << budgetMs << "ms";
            } else {
                ADD_FAILURE() << testCase.relativeKey << " has " << errorCount
                              << " syntax error(s) and is not listed in expected_failures.txt";
            }
        }
    } else if (listedAsExpectedFailure) {
        ADD_FAILURE() << testCase.relativeKey << " now parses cleanly; remove it from expected_failures.txt";
    }
    // else: clean pass, nothing to do.
}

INSTANTIATE_TEST_SUITE_P(
    SysmlLibrary, LibraryFileTest, ::testing::ValuesIn(buildCases()),
    [](const ::testing::TestParamInfo<LibraryCase>& info) {
        return ConformanceTest::sanitizeTestName(info.param.relativeKey);
    });

} // namespace
