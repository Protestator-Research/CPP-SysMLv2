// AP1 syntax suite: data-driven TEST_P over testdata/syntax/**. Each file's first line is a
// directive comment:
//   // expect: valid
//   // expect: error
//   // expect: error <line>:<col>   (line:col currently informational only; see NOTE below)
//   // expect: error no-keyword-misuse
//   // expect: keyword-misuse <word>
//
// "expect: keyword-misuse <word>" is an error expectation that is stricter than "expect: error": at least one reported error
// must be of type KEYWORD_MISUSE (a misused keyword diagnosed instead of the parser's "mismatched input ..." message) and its
// message must contain <word> (the rest of the line, e.g. "inv false"; it must not be empty, and should be specific to the rule). Like
// "expect: error" it is a permanent hard requirement.
// "expect: error no-keyword-misuse" is "expect: error" and additionally requires that NO error is of type KEYWORD_MISUSE (a control
// for texts that are broken in another way and must not be mistaken for a keyword misuse).
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

#include <cctype>
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

enum class Expectation { Valid, Error, KeywordMisuse, Unknown };

struct Directive {
    Expectation expectation = Expectation::Unknown;
    int line = -1;
    int column = -1;
    std::string word; // the text a KEYWORD_MISUSE message must contain
    bool forbidKeywordMisuse = false; // "error no-keyword-misuse"
};

// Parses the "// expect: valid|error [<line>:<col>] [no-keyword-misuse]|keyword-misuse <word>" directive from a file's first line.
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
        while (iss >> pos) {
            if (pos == "no-keyword-misuse") {
                directive.forbidKeywordMisuse = true;
                continue;
            }
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
    } else if (verdict == "keyword-misuse") {
        directive.expectation = Expectation::KeywordMisuse;
        std::getline(iss >> std::ws, directive.word);
        while (!directive.word.empty() && std::isspace(static_cast<unsigned char>(directive.word.back()))) directive.word.pop_back();
        if (directive.word.empty()) directive.expectation = Expectation::Unknown; // a keyword-misuse expectation needs the text to look for
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
        << testCase.absolutePath << " is missing a '// expect: valid|error|keyword-misuse <word>' first line";

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

    if (directive.expectation == Expectation::KeywordMisuse) {
        ASSERT_FALSE(crashed) << testCase.relativeKey << " crashed/threw instead of reporting a keyword misuse: " << crashMessage;
        bool found = false;
        std::string reported;
        for (const auto& error : errors) {
            reported += "\n  [" +std::to_string(static_cast<int>(error->errorType())) + "] " + std::to_string(error->getLine()) + ":" +
                        std::to_string(error->getColumn()) + " " + error->description();
            if (error->errorType() == SysMLv2::Files::ErrorType::KEYWORD_MISUSE && error->description().find(directive.word) != std::string::npos) found = true;
        }
        EXPECT_TRUE(found) << testCase.relativeKey << " was expected to report a KEYWORD_MISUSE error mentioning '" << directive.word
                           << "'; reported:" << reported;
        return;
    }

    if (directive.expectation == Expectation::Error) {
        // Hard requirement, never ratcheted: these are deliberately-broken snippets.
        ASSERT_FALSE(crashed) << testCase.relativeKey << " crashed/threw instead of reporting a syntax error: " << crashMessage;
        EXPECT_FALSE(errors.empty()) << testCase.relativeKey << " was expected to report a syntax error but parsed cleanly";
        if (directive.forbidKeywordMisuse) {
            for (const auto& error : errors) {
                EXPECT_NE(error->errorType(), SysMLv2::Files::ErrorType::KEYWORD_MISUSE)
                    << testCase.relativeKey << " must not report a keyword misuse, but did: " << error->description();
            }
        }
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
