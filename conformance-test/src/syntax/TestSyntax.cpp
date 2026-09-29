// AP1 syntax suite: data-driven TEST_P over testdata/syntax/**. Each file's first line is a
// directive comment:
//   // expect: valid
//   // expect: error
//   // expect: error <line>:<col>   (line:col currently informational only; see NOTE below)
//
// "expect: valid" constructs that the current grammar/parser does not yet accept correctly are
// still marked "valid" (that is the target, per the language spec) but are additionally listed in
// expected_failures.txt with a "syntax/" prefix; the ratchet mechanism mirrors the library suite's
// (AP2): listed + still failing -> skipped as a known/expected failure; listed + now passing ->
// hard failure telling the author to remove the ratchet entry; unlisted + failing -> hard failure.
// "expect: error" files are a permanent hard requirement (never ratcheted): the parser must report
// at least one syntax error for them, today and going forward.
//
// NOTE: exact line:col checking is not implemented in this pass; only the valid/error distinction
// is enforced. The optional "<line>:<col>" suffix is parsed (so files may carry it for documentation
// / future use) but not currently asserted against ParserError::getLine()/getColumn().
#include <gtest/gtest.h>

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "../support/TestHelpers.h"

#ifndef CONFORMANCE_TESTDATA_DIR
#error "CONFORMANCE_TESTDATA_DIR must be defined by CMake"
#endif
#ifndef CONFORMANCE_EXPECTED_FAILURES_FILE
#error "CONFORMANCE_EXPECTED_FAILURES_FILE must be defined by CMake"
#endif

namespace {

enum class Expectation { Valid, Error, Unknown };

struct Directive {
    Expectation expectation = Expectation::Unknown;
    int line = -1;
    int column = -1;
};

// Parses the "// expect: valid|error [<line>:<col>]" directive from a file's first line.
Directive parseDirective(const std::string& firstLine) {
    Directive directive;
    std::istringstream iss(firstLine);
    std::string slashes, expectWord, verdict;
    iss >> slashes >> expectWord;
    if (slashes != "//" || expectWord != "expect:") return directive;
    iss >> verdict;
    if (verdict == "valid") {
        directive.expectation = Expectation::Valid;
    } else if (verdict == "error") {
        directive.expectation = Expectation::Error;
        std::string pos;
        if (iss >> pos) {
            const auto colon = pos.find(':');
            if (colon != std::string::npos) {
                try {
                    directive.line = std::stoi(pos.substr(0, colon));
                    directive.column = std::stoi(pos.substr(colon + 1));
                } catch (...) {
                    // ignore malformed position, expectation itself is still valid
                }
            }
        }
    }
    return directive;
}

struct SyntaxCase {
    std::filesystem::path absolutePath;
    std::string relativeKey; // "syntax/<path relative to testdata/syntax>", '/'-separated
    bool isKerML = false;
};

// Lets gtest failure output show the relative path instead of a raw byte dump of the struct.
void PrintTo(const SyntaxCase& c, std::ostream* os) { *os << c.relativeKey; }

std::vector<SyntaxCase> buildCases() {
    const std::filesystem::path root(CONFORMANCE_TESTDATA_DIR);
    std::vector<SyntaxCase> cases;
    for (const auto& path : ConformanceTest::listFiles(root, {".sysml", ".kerml"})) {
        auto rel = std::filesystem::relative(path, root).generic_string();
        cases.push_back({path, "syntax/" + rel, path.extension() == ".kerml"});
    }
    return cases;
}

class SyntaxFileTest : public ::testing::TestWithParam<SyntaxCase> {};

TEST_P(SyntaxFileTest, MatchesExpectation) {
    const auto& testCase = GetParam();
    static const auto expectedFailures = ConformanceTest::loadExpectedFailures(CONFORMANCE_EXPECTED_FAILURES_FILE);

    const std::string content = ConformanceTest::readFile(testCase.absolutePath);
    std::istringstream contentStream(content);
    std::string firstLine;
    std::getline(contentStream, firstLine);
    const Directive directive = parseDirective(firstLine);
    ASSERT_NE(directive.expectation, Expectation::Unknown)
        << testCase.absolutePath << " is missing a '// expect: valid|error' first line";

    std::vector<std::shared_ptr<SysMLv2::Files::ParserError>> errors;
    bool crashed = false;
    std::string crashMessage;
    try {
        auto result = testCase.isKerML ? SysMLv2::Files::Parser::parseKerML(content, testCase.relativeKey)
                                        : SysMLv2::Files::Parser::parseSysMLv2(content, testCase.relativeKey);
        errors = result.second;
    } catch (const std::exception& ex) {
        crashed = true;
        crashMessage = ex.what();
    } catch (...) {
        crashed = true;
        crashMessage = "unknown exception";
    }

    if (directive.expectation == Expectation::Error) {
        // Hard requirement, never ratcheted: these are deliberately-broken snippets.
        ASSERT_FALSE(crashed) << testCase.relativeKey << " crashed/threw instead of reporting a syntax error: " << crashMessage;
        EXPECT_FALSE(errors.empty()) << testCase.relativeKey << " was expected to report a syntax error but parsed cleanly";
        return;
    }

    // Expectation::Valid, possibly ratcheted via expected_failures.txt.
    const bool actuallyFailed = crashed || !errors.empty();
    const bool listedAsExpectedFailure = expectedFailures.count(testCase.relativeKey) > 0;

    if (actuallyFailed) {
        if (listedAsExpectedFailure) {
            GTEST_SKIP() << "expected failure (" << testCase.relativeKey << "): "
                         << (crashed ? crashMessage : (std::to_string(errors.size()) + " syntax error(s)"));
        } else {
            if (crashed) {
                ADD_FAILURE() << testCase.relativeKey << " crashed/threw: " << crashMessage;
            } else {
                ADD_FAILURE() << testCase.relativeKey << " expected valid but got " << errors.size()
                              << " syntax error(s) and is not listed in expected_failures.txt";
            }
        }
    } else if (listedAsExpectedFailure) {
        ADD_FAILURE() << testCase.relativeKey << " now parses cleanly; remove it from expected_failures.txt";
    }
}

INSTANTIATE_TEST_SUITE_P(
    Syntax, SyntaxFileTest, ::testing::ValuesIn(buildCases()),
    [](const ::testing::TestParamInfo<SyntaxCase>& info) {
        return ConformanceTest::sanitizeTestName(info.param.relativeKey);
    });

} // namespace
