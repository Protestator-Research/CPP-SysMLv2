// Real numbers do not depend on the locale of the process.
//
// Qt applications run in the locale of the user (QCoreApplication calls setlocale(LC_ALL, "") on Unix). With a comma as decimal separator
// std::stod and std::strtod read "5.02921" as 5. The parsers of SysML, KerML and XMI read reals through SysMLv2::Files::parseDouble; these
// tests switch the process to a German locale (skipped if the system has none) and check the values, not only the absence of errors.
#include <gtest/gtest.h>

#include <clocale>
#include <cmath>
#include <cstring>
#include <filesystem>
#include <limits>
#include <memory>
#include <string>
#include <vector>

#ifdef _WIN32
#include <process.h>
#define getpid _getpid
#else
#include <unistd.h>
#endif

#include <kerml/KerML.h>
#include <sysml/SysML.h>
#include <sysmlv2/Workspace.h>

#include "../../../filehandling/src/sysmlv2/parser/RealLiteral.h"
#include "../../../filehandling/src/sysmlv2/xmi/XmiBindings.h"
#include "../support/TestHelpers.h"

#ifndef SYSML_LIBRARY_XMI_DIR
#error "SYSML_LIBRARY_XMI_DIR must be defined by CMake to the resources/sysml.library.xmi path"
#endif

namespace {

using SysMLv2::Files::ErrorType;
using SysMLv2::Files::ParserError;
using SysMLv2::Files::SourceLanguage;
using SysMLv2::Files::Workspace;
namespace K = KerML::Entities;
using Errors = std::vector<std::shared_ptr<ParserError>>;

// Switches LC_ALL to a locale with a comma as decimal separator and restores the previous one.
class GermanLocale {
public:
    GermanLocale() {
        const char* previous = std::setlocale(LC_ALL, nullptr);
        Saved = previous != nullptr ? previous : "C";
        for (const char* name : {"de_DE.UTF-8", "de_DE.utf8", "de_DE", "German_Germany.1252"}) {
            if (std::setlocale(LC_ALL, name) != nullptr) {
                const std::lconv* conv = std::localeconv();
                if (conv != nullptr && conv->decimal_point != nullptr && std::strcmp(conv->decimal_point, ",") == 0) {
                    Active = true;
                    return;
                }
                std::setlocale(LC_ALL, Saved.c_str());
            }
        }
    }
    ~GermanLocale() { std::setlocale(LC_ALL, Saved.c_str()); }
    GermanLocale(const GermanLocale&) = delete;
    GermanLocale& operator=(const GermanLocale&) = delete;
    bool active() const { return Active; }

private:
    std::string Saved;
    bool Active = false;
};

// A temporary directory that is removed with the object.
class TempDir {
public:
    TempDir() {
        static int counter = 0;
        Path = std::filesystem::temp_directory_path() / ("real_locale_" + std::to_string(getpid()) + "_" + std::to_string(counter++));
        std::filesystem::create_directories(Path);
    }
    ~TempDir() {
        std::error_code ec;
        std::filesystem::remove_all(Path, ec);
    }
    TempDir(const TempDir&) = delete;
    TempDir& operator=(const TempDir&) = delete;
    const std::filesystem::path& path() const { return Path; }

private:
    std::filesystem::path Path;
};

#define REQUIRE_GERMAN_LOCALE(guard) \
    if (!(guard).active()) GTEST_SKIP() << "no locale with a comma as decimal separator (de_DE) is installed"

std::string allErrors(const Errors& errors) {
    std::string out;
    for (const auto& error : errors) {
        out += "\n  [" + std::to_string(static_cast<int>(error->errorType())) + "] " + std::to_string(error->getLine()) + ":" +
               std::to_string(error->getColumn()) + " " + error->description();
    }
    return out;
}

std::vector<std::shared_ptr<K::LiteralRational>> rationals(const Workspace& workspace, size_t source) {
    std::vector<std::shared_ptr<K::LiteralRational>> result;
    for (const auto& element : workspace.elements(source)) {
        if (auto found = std::dynamic_pointer_cast<K::LiteralRational>(element)) result.push_back(found);
    }
    return result;
}

bool hasElementNamed(const Workspace& workspace, size_t source, const std::string& name) {
    for (const auto& element : workspace.elements(source)) {
        if (element && element->declaredName().value_or("") == name) return true;
    }
    return false;
}

// ---------------------------------------------------------------------------------------------------------------------
// The helper
// ---------------------------------------------------------------------------------------------------------------------

void checkHelper() {
    using SysMLv2::Files::parseDouble;
    const std::vector<std::pair<std::string, double>> good = {{"5.02921", 5.02921}, {"32.0", 32.0}, {"1.5e3", 1500.0}, {".5", 0.5},    {"+1.5", 1.5},
                                                              {"-2.25", -2.25},     {"0", 0.0},      {"1E2", 100.0},   {"5.", 5.0},     {"1e-3", 0.001}};
    for (const auto& [text, expected] : good) {
        double value = -1.0;
        EXPECT_TRUE(parseDouble(text, value)) << text;
        EXPECT_EQ(value, expected) << text;
    }
    const std::vector<std::string> bad = {"",    " ",   "1,5", "1.5x", "x1.5", "0x10", "inf", "nan",  "INF", "NaN",
                                          " 1.5", "1.5 ", "1.5\n", "e3",  "1e",   ".",    "-",   "1e999", "-1e999", "1.5.2"};
    for (const auto& text : bad) {
        double value = 42.0;
        EXPECT_FALSE(parseDouble(text, value)) << "'" << text << "'";
        EXPECT_EQ(value, 42.0) << "a failed parse must not change the value: '" << text << "'";
    }
    // Underflow depends on the standard library: either rejected (value untouched) or a positive subnormal.
    double subnormal = 42.0;
    if (parseDouble("1e-320", subnormal)) {
        EXPECT_GT(subnormal, 0.0);
        EXPECT_LT(subnormal, std::numeric_limits<double>::min());
    } else {
        EXPECT_EQ(subnormal, 42.0);
    }
    // No crash; either rejected (value untouched) or read as 0.
    double tiny = 42.0;
    if (parseDouble("1e-999", tiny)) {
        EXPECT_EQ(tiny, 0.0);
    } else {
        EXPECT_EQ(tiny, 42.0);
    }
}

TEST(RealLocaleHelper, ParsesInTheClassicLocale) { checkHelper(); }

TEST(RealLocaleHelper, ParsesUnderAGermanLocale) {
    GermanLocale german;
    REQUIRE_GERMAN_LOCALE(german);
    checkHelper();
}

TEST(RealLocaleXmiReal, ParseRealAcceptsXsdDoubleAndNothingElse) {
    using SysMLv2::Files::Xmi::parseReal;
    const auto check = [] {
        const std::vector<std::pair<std::string, double>> good = {{"5.02921", 5.02921}, {"32.0", 32.0}, {"  1.5\n", 1.5}, {"\t+1.5\r\n", 1.5},
                                                                  {"-2.5", -2.5},       {"1.5e3", 1500.0}, {"INF", std::numeric_limits<double>::infinity()},
                                                                  {"+INF", std::numeric_limits<double>::infinity()},
                                                                  {" -INF ", -std::numeric_limits<double>::infinity()}};
        for (const auto& [text, expected] : good) {
            double value = 0.0;
            EXPECT_TRUE(parseReal(text, value)) << "'" << text << "'";
            EXPECT_EQ(value, expected) << "'" << text << "'";
        }
        double nan = 0.0;
        EXPECT_TRUE(parseReal(" NaN ", nan));
        EXPECT_TRUE(std::isnan(nan));
        for (const char* text : {"", "  ", "1,5", "1.5x", "0x10", "inf", "-inf", "nan", "infinity", "1e999"}) {
            double value = 42.0;
            EXPECT_FALSE(parseReal(text, value)) << "'" << text << "'";
            EXPECT_EQ(value, 42.0) << "'" << text << "'";
        }
    };
    check();
    GermanLocale german;
    if (german.active()) check();
}

// ---------------------------------------------------------------------------------------------------------------------
// SysML and KerML text
// ---------------------------------------------------------------------------------------------------------------------

struct RealCase {
    const char* text;
    double expected;
};
const RealCase kRealCases[] = {{"5.02921", 5.02921}, {"32.0", 32.0}, {"1.5e3", 1500.0}, {".5", 0.5}};

void checkSysMLReals() {
    for (const auto& real : kRealCases) {
        Workspace workspace;
        const size_t source = workspace.addText(std::string("package P { attribute a = ") + real.text + "; attribute follow = 1; }", "p.sysml", SourceLanguage::SysML, 1);
        workspace.resolve();
        EXPECT_TRUE(workspace.errors(source).empty()) << real.text << allErrors(workspace.errors(source));
        const auto literals = rationals(workspace, source);
        ASSERT_EQ(literals.size(), 1u) << real.text;
        EXPECT_EQ(literals.front()->value(), real.expected) << real.text;
        EXPECT_TRUE(hasElementNamed(workspace, source, "a")) << real.text;
        EXPECT_TRUE(hasElementNamed(workspace, source, "follow")) << real.text;
    }
}

void checkKerMLReals() {
    for (const auto& real : kRealCases) {
        Workspace workspace;
        const size_t source = workspace.addText(std::string("package P { feature a = ") + real.text + "; feature follow = 1; }", "p.kerml", SourceLanguage::KerML, 1);
        workspace.resolve();
        EXPECT_TRUE(workspace.errors(source).empty()) << real.text << allErrors(workspace.errors(source));
        const auto literals = rationals(workspace, source);
        ASSERT_EQ(literals.size(), 1u) << real.text;
        EXPECT_EQ(literals.front()->value(), real.expected) << real.text;
        EXPECT_TRUE(hasElementNamed(workspace, source, "a")) << real.text;
        EXPECT_TRUE(hasElementNamed(workspace, source, "follow")) << real.text;
    }
}

TEST(RealLocaleText, SysMLRealsInTheClassicLocale) { checkSysMLReals(); }
TEST(RealLocaleText, KerMLRealsInTheClassicLocale) { checkKerMLReals(); }

TEST(RealLocaleText, SysMLRealsUnderAGermanLocale) {
    GermanLocale german;
    REQUIRE_GERMAN_LOCALE(german);
    checkSysMLReals();
}

TEST(RealLocaleText, KerMLRealsUnderAGermanLocale) {
    GermanLocale german;
    REQUIRE_GERMAN_LOCALE(german);
    checkKerMLReals();
}

// A real that does not fit a double is an error at the literal; the other elements of the file survive.
void checkOverflow(SourceLanguage language, const std::string& text, const std::string& name, int column) {
    Workspace workspace;
    const size_t source = workspace.addText(text, name, language, 1);
    workspace.resolve();
    const Errors errors = workspace.errors(source);
    std::shared_ptr<ParserError> found;
    for (const auto& error : errors) {
        if (error->description().find("1e999") != std::string::npos) found = error;
    }
    ASSERT_NE(found, nullptr) << allErrors(errors);
    EXPECT_EQ(found->errorType(), ErrorType::LOGICAL_ERROR);
    EXPECT_EQ(found->getLine(), 2);
    EXPECT_EQ(found->getColumn(), column);
    EXPECT_EQ(errors.size(), 1u) << allErrors(errors);
    EXPECT_TRUE(hasElementNamed(workspace, source, "big"));
    EXPECT_TRUE(hasElementNamed(workspace, source, "follow"));
    const auto literals = rationals(workspace, source);
    ASSERT_EQ(literals.size(), 1u);
    EXPECT_EQ(literals.front()->value(), 0.0);
}

const char* const kSysMLOverflow = "package P {\n    attribute big = 1e999;\n    attribute follow = 1;\n}\n";
const char* const kKerMLOverflow = "package P {\n    feature big = 1e999;\n    feature follow = 1;\n}\n";

TEST(RealLocaleText, SysMLOverflowIsAnErrorInTheClassicLocale) { checkOverflow(SourceLanguage::SysML, kSysMLOverflow, "o.sysml", 20); }
TEST(RealLocaleText, KerMLOverflowIsAnErrorInTheClassicLocale) { checkOverflow(SourceLanguage::KerML, kKerMLOverflow, "o.kerml", 18); }

TEST(RealLocaleText, SysMLOverflowIsAnErrorUnderAGermanLocale) {
    GermanLocale german;
    REQUIRE_GERMAN_LOCALE(german);
    checkOverflow(SourceLanguage::SysML, kSysMLOverflow, "o.sysml", 20);
}

TEST(RealLocaleText, KerMLOverflowIsAnErrorUnderAGermanLocale) {
    GermanLocale german;
    REQUIRE_GERMAN_LOCALE(german);
    checkOverflow(SourceLanguage::KerML, kKerMLOverflow, "o.kerml", 18);
}

// ---------------------------------------------------------------------------------------------------------------------
// XMI
// ---------------------------------------------------------------------------------------------------------------------

// The XMI of "attribute a = 1.5" with the value attribute of the literal replaced by @p valueText.
std::string xmiWithValue(const std::string& valueText) {
    Workspace workspace;
    const size_t source = workspace.addText("package P { attribute a = 1.5; }", "p.sysml", SourceLanguage::SysML, 1);
    workspace.resolve();
    TempDir out;
    const Errors errors = workspace.writeXmi(source, (out.path() / "p.sysmlx").string());
    EXPECT_TRUE(errors.empty()) << allErrors(errors);
    std::string xml = ConformanceTest::readFile((out.path() / "p.sysmlx"));
    const std::string marker = " value=\"1.5\"";
    const size_t at = xml.find(marker);
    EXPECT_NE(at, std::string::npos) << xml;
    if (at != std::string::npos) xml.replace(at, marker.size(), " value=\"" + valueText + "\"");
    return xml;
}

void checkXmiReals() {
    struct Case {
        std::string text;
        double expected;
    };
    const std::vector<Case> cases = {{"5.02921", 5.02921}, {"32.0", 32.0}, {"  2.5  ", 2.5}, {"+1.5", 1.5}, {"1.5e3", 1500.0}, {".5", 0.5},
                                     {"INF", std::numeric_limits<double>::infinity()}, {"-INF", -std::numeric_limits<double>::infinity()}};
    for (const auto& c : cases) {
        Workspace workspace;
        const size_t source = workspace.addText(xmiWithValue(c.text), "p.sysmlx", SourceLanguage::Xmi, 1);
        EXPECT_TRUE(workspace.errors(source).empty()) << c.text << allErrors(workspace.errors(source));
        const auto literals = rationals(workspace, source);
        ASSERT_EQ(literals.size(), 1u) << c.text;
        EXPECT_EQ(literals.front()->value(), c.expected) << c.text;
        EXPECT_TRUE(hasElementNamed(workspace, source, "a")) << c.text;
    }
    {
        Workspace workspace;
        const size_t source = workspace.addText(xmiWithValue("NaN"), "p.sysmlx", SourceLanguage::Xmi, 1);
        EXPECT_TRUE(workspace.errors(source).empty()) << allErrors(workspace.errors(source));
        const auto literals = rationals(workspace, source);
        ASSERT_EQ(literals.size(), 1u);
        EXPECT_TRUE(std::isnan(literals.front()->value()));
    }
    for (const char* text : {"1,5", "1.5x", "0x10", "inf"}) {
        Workspace workspace;
        const size_t source = workspace.addText(xmiWithValue(text), "p.sysmlx", SourceLanguage::Xmi, 1);
        bool reported = false;
        for (const auto& error : workspace.errors(source)) {
            if (error->description().find("invalid value") != std::string::npos) reported = true;
        }
        EXPECT_TRUE(reported) << text;
    }
}

// Export and import again: the values survive.
void checkXmiRoundTrip() {
    for (const auto& real : kRealCases) {
        Workspace workspace;
        const size_t source = workspace.addText(std::string("package P { attribute a = ") + real.text + "; }", "p.sysml", SourceLanguage::SysML, 1);
        workspace.resolve();
        TempDir out;
        const Errors errors = workspace.writeXmi(source, (out.path() / "p.sysmlx").string());
        EXPECT_TRUE(errors.empty()) << real.text << allErrors(errors);
        const std::string xml = ConformanceTest::readFile((out.path() / "p.sysmlx"));
        Workspace again;
        const size_t read = again.addText(xml, "p.sysmlx", SourceLanguage::Xmi, 1);
        EXPECT_TRUE(again.errors(read).empty()) << real.text << allErrors(again.errors(read));
        const auto literals = rationals(again, read);
        ASSERT_EQ(literals.size(), 1u) << real.text;
        EXPECT_EQ(literals.front()->value(), real.expected) << real.text;
    }
}

TEST(RealLocaleXmi, RealsInTheClassicLocale) {
    checkXmiReals();
    checkXmiRoundTrip();
}

TEST(RealLocaleXmi, RealsUnderAGermanLocale) {
    GermanLocale german;
    REQUIRE_GERMAN_LOCALE(german);
    checkXmiReals();
}

TEST(RealLocaleXmi, ExportAndReimportRoundTripUnderAGermanLocale) {
    GermanLocale german;
    REQUIRE_GERMAN_LOCALE(german);
    checkXmiRoundTrip();
}

// 129 literals of the library have a decimal point; they all failed with "invalid value" under a German locale.
TEST(RealLocaleXmi, LibraryLoadsWithoutInvalidValuesUnderAGermanLocale) {
    GermanLocale german;
    REQUIRE_GERMAN_LOCALE(german);
    Workspace workspace;
    for (const auto& file : ConformanceTest::listFiles(SYSML_LIBRARY_XMI_DIR, {".sysmlx", ".kermlx"})) workspace.addFile(file.string());
    workspace.resolve();
    size_t invalid = 0;
    std::string first;
    for (size_t i = 0; i < workspace.sourceCount(); ++i) {
        for (const auto& error : workspace.errors(i)) {
            if (error->description().find("invalid value") != std::string::npos) {
                if (invalid++ == 0) first = error->getSource() + ": " + error->description();
            }
        }
    }
    EXPECT_EQ(invalid, 0u) << first;
}

}  // namespace
