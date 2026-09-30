// AP1 lexer suite: TEST_P over a table of (language, input text, expected first-token symbolic
// name), using the generated lexers' own vocabulary (getVocabulary().getSymbolicName). Only
// unambiguous tokens are asserted here (keywords, symbols, NAME, unrestricted names, numbers incl.
// unsigned exponent, strings, REGULAR_COMMENT vs. a single-line note).
// NOTE (AP5/G1 fix): TYPED_BY/SPECIALIZES/SUBSETS/REFERENCES/REDEFINES/CONJUGATES used to be
// *composite lexer tokens* (e.g. "SUBSETS: SYMBOL_SPECIALIZES | KEYWORD_SUBSETS;") that shadowed
// their own underlying symbol/keyword tokens (':>' always lexed as SPECIALIZES, so a real
// "subsets"/SUBSETS token was unreachable, and 'typed by' with whitespace never matched). They are
// now parser rules (typed_by_operator, specializes_operator, subsets_operator, references_operator,
// redefines_operator, conjugates_operator) built from the plain SYMBOL_*/KEYWORD_* lexer tokens, so
// the lexer now reports the real underlying token for ':>' , 'specializes', 'subsets', etc.
#include <gtest/gtest.h>

#include <antlr4-common.h>
#include <kerml/parser/KerMLLexer.h>
#include <sysmlv2/parser/SysMLv2Lexer.h>

#include <string>
#include <vector>

#include "../support/TestHelpers.h"

namespace {

enum class Lang { SysML, KerML };

struct LexerCase {
    std::string name;
    Lang lang;
    std::string text;
    std::string expectedTokenName;
};

// Values below were captured empirically by running each lexer over the given text and reading
// back its own vocabulary's symbolic name for the first emitted token, so the table matches actual
// generated-lexer behavior rather than a guess from the grammar source.
const std::vector<LexerCase>& cases() {
    static const std::vector<LexerCase> table = {
        // --- SysML v2 ---
        {"SysML_KeywordPart", Lang::SysML, "part", "KEYWORD_PART"},
        {"SysML_KeywordDef", Lang::SysML, "def", "KEYWORD_DEF"},
        {"SysML_KeywordAttribute", Lang::SysML, "attribute", "KEYWORD_ATTRIBUTE"},
        {"SysML_KeywordNamespace", Lang::SysML, "namespace", "KEYWORD_NAMESPACE"},
        {"SysML_KeywordPackage", Lang::SysML, "package", "KEYWORD_PACKAGE"},
        {"SysML_KeywordImport", Lang::SysML, "import", "KEYWORD_IMPORT"},
        {"SysML_SymbolSpecializes", Lang::SysML, ":>", "SYMBOL_SPECIALIZES"},
        {"SysML_SymbolRedefines", Lang::SysML, ":>>", "SYMBOL_REDEFINES"},
        {"SysML_SymbolGreater", Lang::SysML, ">", "SYMBOL_GREATER"},
        {"SysML_SymbolNamespaceSubset", Lang::SysML, "::", "SYMBOL_NAMESPACE_SUBSET"},
        {"SysML_WordSpecializes", Lang::SysML, "specializes", "KEYWORD_SPECIALIZES"},
        {"SysML_WordSubsets", Lang::SysML, "subsets", "KEYWORD_SUBSETS"},
        {"SysML_Name", Lang::SysML, "a", "NAME"},
        {"SysML_UnrestrictedName", Lang::SysML, "'a b'", "NAME"},
        {"SysML_DecimalValue", Lang::SysML, "12", "DECIMAL_VALUE"},
        {"SysML_ExponentialValueUnsigned", Lang::SysML, "1e11", "EXPONENTIAL_VALUE"},
        {"SysML_StringValue", Lang::SysML, "\"hi\"", "STRING_VALUE"},
        {"SysML_SingleLineNote", Lang::SysML, "// note", "SINGLE_LINE_NOTE"},
        {"SysML_RegularComment", Lang::SysML, "/* c */", "REGULAR_COMMENT"},

        // --- KerML ---
        {"KerML_KeywordClass", Lang::KerML, "class", "KEYWORD_CLASS"},
        {"KerML_KeywordFeature", Lang::KerML, "feature", "KEYWORD_FEATURE"},
        {"KerML_KeywordSpecialization", Lang::KerML, "specialization", "KEYWORD_SPECIALIZATION"},
        {"KerML_KeywordPackage", Lang::KerML, "package", "KEYWORD_PACKAGE"},
        {"KerML_KeywordImport", Lang::KerML, "import", "KEYWORD_IMPORT"},
        {"KerML_SymbolSpecializes", Lang::KerML, ":>", "SYMBOL_SPECIALIZES"},
        {"KerML_WordSubsets", Lang::KerML, "subsets", "KEYWORD_SUBSETS"},
        {"KerML_Name", Lang::KerML, "a", "NAME"},
        {"KerML_DecimalValue", Lang::KerML, "12", "DECIMAL_VALUE"},
        {"KerML_ExponentialValueUnsigned", Lang::KerML, "1e5", "EXPONENTIAL_VALUE"},
        {"KerML_StringValue", Lang::KerML, "\"str\"", "STRING_VALUE"},
        {"KerML_SingleLineNote", Lang::KerML, "// note", "SINGLE_LINE_NOTE"},
        {"KerML_RegularComment", Lang::KerML, "/* c */", "REGULAR_COMMENT"},
    };
    return table;
}

template <class LexerT>
std::string firstTokenSymbolicName(const std::string& text) {
    antlr4::ANTLRInputStream input(text);
    LexerT lexer(&input);
    auto vocabulary = lexer.getVocabulary();
    auto token = lexer.nextToken();
    return std::string(vocabulary.getSymbolicName(token->getType()));
}

class LexerTest : public ::testing::TestWithParam<LexerCase> {};

TEST_P(LexerTest, FirstTokenHasExpectedType) {
    const auto& testCase = GetParam();
    const std::string actual = testCase.lang == Lang::SysML ? firstTokenSymbolicName<SysMLv2Lexer>(testCase.text)
                                                             : firstTokenSymbolicName<KerMLLexer>(testCase.text);
    EXPECT_EQ(actual, testCase.expectedTokenName) << "input: " << testCase.text;
}

INSTANTIATE_TEST_SUITE_P(
    UnambiguousTokens, LexerTest, ::testing::ValuesIn(cases()),
    [](const ::testing::TestParamInfo<LexerCase>& info) { return ConformanceTest::sanitizeTestName(info.param.name); });

} // namespace
