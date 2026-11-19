// Evaluation (sysmlv2evaluation, step 4): the Evaluator on text that the real parsers produce, for KerML (`feature x = ...;`) and SysML
// (`attribute x = ...;`), with the standard library loaded from text, from XMI, and not loaded at all.
//
// The expected values follow the grammar of the parsers (KerML.g4 / SysMLv2.g4): the unary operators bind tighter than `**` (so
// `-2 ** 2` is `(-2) ** 2` = 4), `**` and `^` are right associative, all other binary operators group to the left, a parenthesised
// expression is the expression itself (no node of its own) and `(a, b, c)` is a right nested chain of `,` operators.

#include <sysmlv2/ParserError.h>
#include <sysmlv2/Workspace.h>
#include <sysmlv2/evaluation/Evaluator.h>
#include <sysmlv2/evaluation/ModelLevelEvaluable.h>
#include <sysmlv2/evaluation/QualifiedName.h>

#include <kerml/core/features/Feature.h>
#include <kerml/kernel/expressions/FeatureChainExpression.h>
#include <kerml/kernel/expressions/OperatorExpression.h>
#include <kerml/kernel/featurevalues/FeatureValue.h>
#include <kerml/kernel/expressions/LiteralExpression.h>
#include <kerml/kernel/functions/Expression.h>

#include <gtest/gtest.h>

#include <chrono>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <set>
#include <memory>
#include <string>
#include <utility>
#include <variant>
#include <vector>

#ifndef SYSML_LIBRARY_DIR
#error "SYSML_LIBRARY_DIR must be defined by CMake to the resources/sysml.library path"

#endif
#ifndef SYSML_LIBRARY_XMI_DIR
#error "SYSML_LIBRARY_XMI_DIR must be defined by CMake to the resources/sysml.library.xmi path"
#endif

namespace SysMLv2::Evaluation {
    // (for the messages of gtest)
    inline std::ostream& operator<<(std::ostream& out, const Value& value) { return out << value.toString(); }
}

namespace {

using SysMLv2::Evaluation::Diagnostic;
using SysMLv2::Evaluation::Evaluator;
using SysMLv2::Evaluation::Result;
using SysMLv2::Evaluation::Severity;
using SysMLv2::Evaluation::Value;
using SysMLv2::Files::SourceLanguage;
using SysMLv2::Files::Workspace;
using FeaturePtr = std::shared_ptr<KerML::Entities::Feature>;

Value B(bool value) { return Value::boolean(value); }
Value I(std::int64_t value) { return Value::integer(value); }
Value R(double value) { return Value::real(value); }
Value S(const std::string& value) { return Value::string(value); }
Value N() { return Value::null(); }
Value Seq(std::initializer_list<std::int64_t> integers) {
    std::vector<SysMLv2::Evaluation::Item> items;
    for (const std::int64_t integer : integers) items.emplace_back(std::in_place_type<std::int64_t>, integer);
    return Value(std::move(items));
}

/// A workspace with one user source (level 1, above a library at level 0) whose text is replaced for every case.
class Session {
public:
    /// @param library the directory of the library to load (text or XMI), nullptr for none.
    explicit Session(const char* library) {
        if (library != nullptr) Workspace_.loadLibrary(library);
        User = Workspace_.addText("", "user.kerml", SourceLanguage::KerML, 1);
        Workspace_.resolve();
    }

    /// Replaces the user source by `package P { <text> }` and resolves. The text uses `$` for the feature keyword of the language.
    /// Every text must be free of syntax and resolution errors (ANTLR's recovery still produces plausible models), unless the test
    /// expects some (@p expectErrors).
    void load(SourceLanguage language, std::string text, bool expectErrors = false) {
        const std::string keyword = language == SourceLanguage::KerML ? "feature" : "attribute";
        for (std::size_t position = text.find('$'); position != std::string::npos; position = text.find('$', position + keyword.size()))
            text.replace(position, 1, keyword);
        Workspace_.replaceSource(User, "package P { " + text + " }", language);
        Workspace_.resolve();
        if (!expectErrors) {
            const auto errors = Workspace_.errors(User);
            for (const auto& error : errors) ADD_FAILURE() << "the model text has an error: " << error->description() << " (column " << error->getColumn() << ")\n" << text;
        }
    }

    /// The number of syntax errors of the user source; each is printed.
    std::size_t syntaxErrors() const {
        const auto errors = Workspace_.errors(User);
        for (const auto& error : errors) std::cout << "[  ERROR ] " << error->description() << " (column " << error->getColumn() << ")" << std::endl;
        return errors.size();
    }
    /// The syntax errors of the user source (not printed).
    std::vector<std::shared_ptr<SysMLv2::Files::ParserError>> errors() const { return Workspace_.errors(User); }
    std::shared_ptr<KerML::Entities::Element> element(const std::string& name) const { return Workspace_.find("P::" + name); }
    FeaturePtr feature(const std::string& name) const { return std::dynamic_pointer_cast<KerML::Entities::Feature>(Workspace_.find("P::" + name)); }
    Workspace& workspace() { return Workspace_; }

private:
    Workspace Workspace_;
    std::size_t User = 0;
};

/// The expression of the feature's own feature value.
std::shared_ptr<KerML::Entities::Expression> valueOf(const FeaturePtr& feature) {
    for (const auto& owned : feature->ownedElements()) {
        if (const auto value = std::dynamic_pointer_cast<KerML::Entities::FeatureValue>(owned)) return value->value();
    }
    return nullptr;
}

const char* languageName(SourceLanguage language) { return language == SourceLanguage::KerML ? "KerML" : "SysML"; }

/// One expression with its expected outcome: a value and no diagnostic, or null and exactly one Error that contains @c error, located at
/// an operator expression @c errorOperator (if given) or an element of the metaclass @c errorMetaclass (if given).
struct Row {
    std::string expression;
    Value expected;
    std::string error = {};
    std::string errorOperator = {};
    std::string errorMetaclass = {};
};

/// Loads one feature per row (`x0`, `x1`, ...) and checks the outcome of the evaluation of each.
void runRows(Session& session, SourceLanguage language, const std::vector<Row>& rows) {
    SCOPED_TRACE(languageName(language));
    std::string text;
    for (std::size_t index = 0; index < rows.size(); ++index) text += "$ x" + std::to_string(index) + " = " + rows[index].expression + "; ";
    session.load(language, text);
    ASSERT_EQ(session.syntaxErrors(), 0u);
    const Evaluator evaluator;
    for (std::size_t index = 0; index < rows.size(); ++index) {
        const Row& row = rows[index];
        SCOPED_TRACE(row.expression);
        const FeaturePtr feature = session.feature("x" + std::to_string(index));
        ASSERT_NE(feature, nullptr);
        const Result result = evaluator.evaluateFeatureValue(feature);
        if (row.error.empty()) {
            EXPECT_EQ(result.value, row.expected);
            EXPECT_TRUE(result.diagnostics.empty()) << (result.diagnostics.empty() ? "" : result.diagnostics.front().message);
            EXPECT_TRUE(result.ok());
            continue;
        }
        EXPECT_TRUE(result.value.isNull());
        EXPECT_FALSE(result.ok());
        ASSERT_EQ(result.diagnostics.size(), 1u) << (result.diagnostics.empty() ? "no diagnostic" : result.diagnostics.front().message);
        const Diagnostic& diagnostic = result.diagnostics.front();
        EXPECT_EQ(diagnostic.severity, Severity::Error);
        EXPECT_NE(diagnostic.message.find(row.error), std::string::npos) << diagnostic.message;
        ASSERT_NE(diagnostic.element, nullptr);
        if (!row.errorOperator.empty()) {
            const auto op = std::dynamic_pointer_cast<KerML::Entities::OperatorExpression>(diagnostic.element);
            ASSERT_NE(op, nullptr) << diagnostic.element->getType();
            EXPECT_EQ(op->operatorName(), row.errorOperator);
        }
        if (!row.errorMetaclass.empty()) EXPECT_EQ(diagnostic.element->getType(), row.errorMetaclass);
    }
}

/// Expressions of the grammar that need nothing of the library.
const std::vector<Row>& valueRows() {
    static const std::vector<Row> rows = {
        // literals
        {"42", I(42)}, {"2.5", R(2.5)}, {"true", B(true)}, {"false", B(false)}, {"\"text\"", S("text")}, {"null", N()}, {"*", Value::infinity()},
        {"9223372036854775807", I(9223372036854775807LL)},
        // arithmetic: precedence and associativity
        {"2 * (3 + 4) ** 2", I(98)}, {"2 ** 3 ** 2", I(512)}, {"10 - 4 - 3", I(3)}, {"7 / 2", R(3.5)}, {"7 % 3", I(1)},
        {"1 + 2 * 3", I(7)}, {"(1 + 2) * 3", I(9)}, {"2 * 3 ** 2", I(18)}, {"1 + 2 + 3", I(6)}, {"8 / 2 / 2", R(2.0)}, {"2 ^ 10", I(1024)},
        {"-(-5)", I(5)}, {"+5", I(5)}, {"- -5", I(5)}, {"1 + 2.5", R(3.5)}, {"3.0 * 2", R(6.0)}, {"0.1 + 0.2", R(0.1 + 0.2)}, {"10 / 4", R(2.5)},
        // (the unary minus binds tighter than `**`: `(-2) ** 2`)
        {"-2 ** 2", I(4)}, {"2 ** -1", R(0.5)}, {"((1))", I(1)}, {"(1,)", I(1)},
        // strings, comparisons, equality
        {"\"a\" + \"b\"", S("ab")}, {"\"a\" == \"a\"", B(true)}, {"\"a\" < \"b\"", B(true)},
        // (the escape sequences of a string literal are decoded: `\"`, `\\`, `\n`, `\t`)
        {"\"a\\nb\"", S("a\nb")}, {"\"say \\\"hi\\\"\"", S("say \"hi\"")}, {"\"back\\\\slash\"", S("back\\slash")},
        {"\"tab\\there\" == \"tab\\there\"", B(true)}, {"\"a\\\"b\" + \"\\\\\"", S("a\"b\\")}, {"\"\\\\n\"", S("\\n")},
        {"1 < 2", B(true)}, {"2 <= 2", B(true)}, {"3 > 4", B(false)}, {"3 >= 3", B(true)}, {"1 == 1.0", B(true)}, {"1 != 2", B(true)},
        {"1 === 1", B(true)}, {"1 === 2", B(false)}, {"1 !== 1", B(false)}, {"(1, 2) == (1, 2)", B(true)},
        // Boolean logic
        {"not true", B(false)}, {"true and false", B(false)}, {"true or false", B(true)}, {"true xor true", B(false)},
        {"false implies false", B(true)}, {"true implies false", B(false)}, {"true & false", B(false)}, {"true | false", B(true)},
        // conditional, null coalescing, ranges and sequences
        {"if true ? 1 else 2", I(1)}, {"if false ? 1 else 2", I(2)}, {"null ?? 5", I(5)}, {"3 ?? 5", I(3)},
        {"1..4", Seq({1, 2, 3, 4})}, {"(1, 2, 3)", Seq({1, 2, 3})}, {"(1, 2, 3, 4)", Seq({1, 2, 3, 4})}, {"(1, (2, 3))", Seq({1, 2, 3})},
        {"1 + null", N()},
        // short circuit: the operand that is not needed is not evaluated, so its error never happens
        {"false and (1 / 0 == 1)", B(false)}, {"true or (1 / 0 == 1)", B(true)}, {"false implies (1 / 0 == 1)", B(true)},
        {"if false ? 1 / 0 else 2", I(2)}, {"if true ? 1 else 1 / 0", I(1)}, {"1 ?? 1 / 0", I(1)},
        // errors: one diagnostic at the expression where the problem occurred, and no value
        {"1 / 0", N(), "division by zero", "/"}, {"1 % 0", N(), "modulo by zero", "%"}, {"2 + 1 / 0", N(), "division by zero", "/"},
        {"1 + true", N(), "unsupported argument types", "+"}, {"not 1", N(), "unsupported argument types", "not"},
        {"9223372036854775807 + 1", N(), "Integer overflow", "+"}, {"true and 1", N(), "unsupported argument types", "and"},
        {"if 1 ? 2 else 3", N(), "unsupported argument types", "if"}, {"(1, 1 / 0)", N(), "division by zero", "/"},
        // references to other features (x0 is the literal 42)
        {"x0 + 1", I(43)}, {"x0", I(42)}, {"x0 * x0 - 1", I(1763)}, {"if x0 > 40 ? x0 else 0", I(42)},
        // an unresolved name is a clean Error at the reference
        {"nothere + 1", N(), "unresolved reference 'nothere'", "", "FeatureReferenceExpression"},
    };
    return rows;
}

/// Invocations of the library functions by their names.
const std::vector<Row>& invocationRows() {
    static const std::vector<Row> rows = {
        {"DataFunctions::'+'(1, 2)", I(3)}, {"DataFunctions::'-'(5)", I(-5)}, {"DataFunctions::'*'(6, 7)", I(42)},
        {"BaseFunctions::'=='(1, 1.0)", B(true)}, {"ControlFunctions::'and'(true, false)", B(false)},
        {"DataFunctions::'+'(DataFunctions::'*'(2, 3), 1)", I(7)},
        // the arrow form: the left operand is the first argument
        {"3->DataFunctions::'+'(4)", I(7)}, {"(10 - 3)->DataFunctions::'-'(2)", I(5)}, {"2->DataFunctions::'-'()", I(-2)},
        {"1->DataFunctions::'+'(2)->DataFunctions::'*'(10)", I(30)},
        // named arguments are put in the order of the parameters of the function (DataFunctions::'-' has the parameters x and y) ...
        {"DataFunctions::'-'(y = 1, x = 10)", I(9)}, {"DataFunctions::'-'(x = 10, y = 1)", I(9)}, {"DataFunctions::'-'(x = 5)", I(-5)},
        // ... an unknown or twice given name is an Error; a parameter that is not given is empty, and so is the result
        {"DataFunctions::'-'(z = 1, x = 2)", N(), "unknown parameter 'z'", "", "InvocationExpression"},
        {"DataFunctions::'-'(x = 1, x = 2)", N(), "parameter 'x' is given twice", "", "InvocationExpression"},
        {"DataFunctions::'-'(y = 1)", N()},
        {"DataFunctions::'-'(1, 2, 3)", N(), "too many arguments", "", "InvocationExpression"},
        // the arrow form: the left operand is the first argument, the others can be named
        {"3->DataFunctions::'+'(y = 4)", I(7)}, {"10->DataFunctions::'-'(y = 4)", I(6)}, {"10->DataFunctions::'-'(x = 4)", I(-6)},   // (x is named, so the left operand 10 is the next free parameter y: 4 - 10)
        // a function whose result is declared as a Real gives a Real when it is called by name (3.0), while the operator `1 + 2` is decided by
        // the types of its operands (the Integer 3)
        {"RealFunctions::'+'(1, 2)", R(3.0)}, {"RealFunctions::'-'(10, 4)", R(6.0)}, {"IntegerFunctions::'+'(1, 2)", I(3)}, {"RationalFunctions::'+'(1, 2)", R(3.0)},
        // functions with a native implementation, called by name and with the arrow
        {"NumericalFunctions::sum((1, 2, 3))", I(6)}, {"(1, 2, 3)->NumericalFunctions::sum()", I(6)},
        // not implemented (the unary `~` has no sensible definition for data values)
        {"~1", N(), "no native implementation for DataFunctions::'~'", "~"},
    };
    return rows;
}

// The three ways to have a library --------------------------------------------------------------------------------------

struct TextLibrary {
    static constexpr bool HasLibrary = true;
    static const char* directory() { return SYSML_LIBRARY_DIR; }
};
struct XmiLibrary {
    static constexpr bool HasLibrary = true;
    static const char* directory() { return SYSML_LIBRARY_XMI_DIR; }
};
struct NoLibrary {
    static constexpr bool HasLibrary = false;
    static const char* directory() { return nullptr; }
};

/// The workspace of a mode, loaded on first use and shared by all tests (loading the standard library takes seconds).
template <class Mode>
Session& sharedSession() {
    static const std::unique_ptr<Session> session = [] {
        const auto start = std::chrono::steady_clock::now();
        auto created = std::make_unique<Session>(Mode::directory());
        std::cout << "[  INFO  ] workspace ready in " << std::chrono::duration<double>(std::chrono::steady_clock::now() - start).count() << " s"
                  << std::endl;
        return created;
    }();
    return *session;
}

template <class Mode>
class EvaluationTest : public ::testing::Test {
protected:
    static Session& session() { return sharedSession<Mode>(); }
};

using Modes = ::testing::Types<TextLibrary, XmiLibrary, NoLibrary>;
TYPED_TEST_SUITE(EvaluationTest, Modes);

}   // namespace

TYPED_TEST(EvaluationTest, ExpressionsEvaluateInKerMLText) { runRows(this->session(), SourceLanguage::KerML, valueRows()); }
TYPED_TEST(EvaluationTest, ExpressionsEvaluateInSysMLText) { runRows(this->session(), SourceLanguage::SysML, valueRows()); }

TYPED_TEST(EvaluationTest, InvocationsEvaluateInKerMLText) {
    if constexpr (TypeParam::HasLibrary) runRows(this->session(), SourceLanguage::KerML, invocationRows());
}
TYPED_TEST(EvaluationTest, InvocationsEvaluateInSysMLText) {
    if constexpr (TypeParam::HasLibrary) runRows(this->session(), SourceLanguage::SysML, invocationRows());
}

TYPED_TEST(EvaluationTest, OperatorsAreBoundExactlyIfTheLibraryIsLoaded) {
    for (const SourceLanguage language : {SourceLanguage::KerML, SourceLanguage::SysML}) {
        SCOPED_TRACE(languageName(language));
        Session& session = this->session();
        session.load(language, "$ x = 1 + 2;");
        ASSERT_EQ(session.syntaxErrors(), 0u);
        const auto op = std::dynamic_pointer_cast<KerML::Entities::OperatorExpression>(valueOf(session.feature("x")));
        ASSERT_NE(op, nullptr);
        EXPECT_EQ(op->function() != nullptr, TypeParam::HasLibrary);
        // evaluated either way: through the function or through the name of the operator
        const Result result = Evaluator().evaluateFeatureValue(session.feature("x"));
        EXPECT_EQ(result.value, I(3));
        EXPECT_TRUE(result.diagnostics.empty());
    }
}

TYPED_TEST(EvaluationTest, AnInvocationOfAnUnresolvedFunctionIsAnErrorWithoutTheLibrary) {
    if constexpr (!TypeParam::HasLibrary) {
        Session& session = this->session();
        session.load(SourceLanguage::SysML, "$ x = DataFunctions::'+'(1, 2);");
        const Result result = Evaluator().evaluateFeatureValue(session.feature("x"));
        EXPECT_TRUE(result.value.isNull());
        ASSERT_EQ(result.diagnostics.size(), 1u);
        EXPECT_NE(result.diagnostics.front().message.find("not bound to a function"), std::string::npos) << result.diagnostics.front().message;
    }
}

TYPED_TEST(EvaluationTest, AnIntegerLiteralOutOfRangeIsAParserErrorAndNeverTheValueZeroWithoutAnError) {
    for (const SourceLanguage language : {SourceLanguage::KerML, SourceLanguage::SysML}) {
        SCOPED_TRACE(languageName(language));
        Session& session = this->session();
        session.load(language, "$ x = 9223372036854775808; $ y = 9223372036854775807;", true);
        ASSERT_EQ(session.syntaxErrors(), 1u);
        const auto errors = session.errors();
        EXPECT_NE(errors[0]->description().find("integer literal out of range"), std::string::npos) << errors[0]->description();
        EXPECT_NE(errors[0]->description().find("9223372036854775808"), std::string::npos);
        EXPECT_EQ(errors[0]->getLine(), 1);
        // (the literal next to it is not affected)
        EXPECT_EQ(Evaluator().evaluateFeatureValue(session.feature("y")).value, I(9223372036854775807LL));
        // `-9223372036854775808` is the unary minus applied to the literal that does not fit: the same error
        session.load(language, "$ x = -9223372036854775808;", true);
        EXPECT_EQ(session.syntaxErrors(), 1u);
    }
}

TYPED_TEST(EvaluationTest, AStringWithAnInvalidEscapeIsAParserError) {
    for (const SourceLanguage language : {SourceLanguage::KerML, SourceLanguage::SysML}) {
        SCOPED_TRACE(languageName(language));
        Session& session = this->session();
        session.load(language, "$ x = \"a\\qb\";", true);
        ASSERT_EQ(session.syntaxErrors(), 1u);
        EXPECT_NE(session.errors()[0]->description().find("invalid escape sequence"), std::string::npos);
    }
}

TYPED_TEST(EvaluationTest, AFeatureWithoutAValueIsNullWithoutADiagnostic) {
    for (const SourceLanguage language : {SourceLanguage::KerML, SourceLanguage::SysML}) {
        Session& session = this->session();
        session.load(language, "$ x;");
        const Result result = Evaluator().evaluateFeatureValue(session.feature("x"));
        EXPECT_TRUE(result.value.isNull());
        EXPECT_TRUE(result.diagnostics.empty());
    }
}

TYPED_TEST(EvaluationTest, TheExpressionOverloadEvaluatesTheValueExpression) {
    Session& session = this->session();
    session.load(SourceLanguage::SysML, "$ x = 2 * 3;");
    const auto expression = valueOf(session.feature("x"));
    ASSERT_NE(expression, nullptr);
    const Result result = Evaluator().evaluate(expression);
    EXPECT_EQ(result.value, I(6));
    EXPECT_TRUE(result.diagnostics.empty());
}

TYPED_TEST(EvaluationTest, AFeatureThatReferencesAnotherOneIsEvaluated) {
    for (const SourceLanguage language : {SourceLanguage::KerML, SourceLanguage::SysML}) {
        Session& session = this->session();
        session.load(language, "$ x = 1; $ y = x + 1;");
        const Result result = Evaluator().evaluateFeatureValue(session.feature("y"));
        EXPECT_EQ(result.value, I(2));
        EXPECT_TRUE(result.diagnostics.empty());
    }
}

// The whole standard library ------------------------------------------------------------------------------------------------

namespace {

/// The kind of an Error message, without the names in it.
std::string categoryOf(const std::string& message) {
    if (message.find(" specializes a function with a native implementation but ") != std::string::npos)
        return "not supported yet: a specialization with a body of its own or reordered parameters";
    if (message.rfind("not supported yet", 0) == 0 || message.rfind("named arguments", 0) == 0) return message;
    if (message.rfind("no native implementation", 0) == 0) return "no native implementation";
    if (message.rfind("the invocation is not bound", 0) == 0) return "the invocation is not bound to a function";
    if (message.rfind("exception in a native function", 0) == 0) return "exception in a native function";
    if (message.rfind("cyclic definition", 0) == 0) return message;
    if (message.find(" is not an Integer") != std::string::npos && message.find("the value ") != std::string::npos) return "a Real does not fit into an Integer";   // (kept whole: the allowed ones are pinned by name)
    if (message.rfind("The maximum evaluation depth", 0) == 0 || message.rfind("The maximum call depth", 0) == 0) return "depth";
    if (message.find(" is not bound to a function") != std::string::npos) return "operator is not bound to a function";
    const std::size_t colon = message.find(": ");
    return colon == std::string::npos ? message : message.substr(colon + 2);   // ("DataFunctions::'+': Integer overflow")
}

/// What the evaluation of a feature gave: for the comparison of two workspaces.
struct Outcome {
    Value value;
    bool ok = true;
    std::string category;   // of the first Error
    bool literal = false;   // the value expression is a literal (nothing was computed)
};

/// The features whose value is an element that the text and the XMI model denote differently. Investigated: the evaluator derives the
/// effective feature from the referent that the model records, and for these the referents differ.
///  (`xUnit = mRefs#(1)` of ISQSpaceTime was one of them until the resolver looked names in a value expression up from the namespace that owns
///  the feature: the text bound `mRefs` through the type of xUnit, the pilot's XMI to the local redefinition `:>> mRefs: LengthUnit[3]`.)
///  - `AcceptAction::acceptedMessage = aState.aTransition.accepter.acceptedMessage`: parsed from text the transition has no step of its
///    own for `accept apayload ...`, so the link `accepter` is TransitionAction::accepter, which owns the redefinition `acceptedMessage
///    :>> acceptedTransfer`; the pilot's XMI has that step as an anonymous AcceptActionUsage and links the chain to it, but records no
///    general for it (ownedRedefinition / ownedSubsetting / ownedTyping are empty), so the value is the bare
///    AcceptMessageAction::acceptedMessage. The information is missing in the XMI.
bool isKnownDifference(const std::string& name) {
    static const std::set<std::string> names = {"Actions::AcceptAction::acceptedMessage"};
    return names.count(name) != 0;
}

/// Equality of two values from different workspaces: elements are the same if they have the same qualified name.
bool sameValue(const Value& left, const Value& right) {
    if (left.size() != right.size()) return false;
    for (std::size_t index = 0; index < left.size(); ++index) {
        const auto* a = std::get_if<std::shared_ptr<KerML::Entities::Element>>(&left.items()[index]);
        const auto* b = std::get_if<std::shared_ptr<KerML::Entities::Element>>(&right.items()[index]);
        if ((a == nullptr) != (b == nullptr)) return false;
        if (a != nullptr) {
            if (SysMLv2::Evaluation::qualifiedNameOf(*a) != SysMLv2::Evaluation::qualifiedNameOf(*b)) return false;
        } else if (left.items()[index] != right.items()[index]) {
            return false;
        }
    }
    return true;
}

/// A value for messages: elements by qualified name.
std::string describeValue(const Value& value) {
    std::string text = "(";
    for (const auto& item : value.items()) {
        if (text.size() > 1) text += ", ";
        if (const auto* element = std::get_if<std::shared_ptr<KerML::Entities::Element>>(&item)) text += "@" + SysMLv2::Evaluation::qualifiedNameOf(*element);
        else text += Value(std::vector<SysMLv2::Evaluation::Item>{item}).toString();
    }
    return text + ")";
}

/// Evaluates the value of every feature of the workspace that has a value expression, by qualified name. Features whose name is not
/// unique or contains an unnamed element are left out (`skipped`).
struct Sweep {
    std::map<std::string, Outcome> outcomes;
    std::size_t withValue = 0, ok = 0, skipped = 0, overriding = 0, emptyPrototypes = 0;
    std::map<std::string, std::size_t> emptyPatterns;   // overriding: features whose evaluation warns that a bound value is overridden
    std::map<std::string, std::size_t> errors;   // category -> number of features whose first Error it is
    double seconds = 0;
};

Sweep sweep(Workspace& workspace) {
    Sweep result;
    const Evaluator evaluator;
    std::set<std::string> seen, duplicates;
    const auto start = std::chrono::steady_clock::now();
    for (const auto& element : workspace.elements()) {
        const auto feature = std::dynamic_pointer_cast<KerML::Entities::Feature>(element);
        if (!feature || !valueOf(feature)) continue;
        ++result.withValue;
        const Result evaluated = evaluator.evaluateFeatureValue(feature);
        Outcome outcome;
        outcome.value = evaluated.value;
        outcome.ok = evaluated.ok();
        for (const Diagnostic& diagnostic : evaluated.diagnostics) {
            if (diagnostic.severity == Severity::Warning) {
                if (diagnostic.message.rfind("the values of '", 0) == 0) {
                    ++result.emptyPrototypes;
                    ++result.emptyPatterns[diagnostic.message.substr(0, diagnostic.message.find("' are not given") + 1)];
                } else {
                    ++result.overriding;
                }
                break;
            }
        }
        outcome.literal = std::dynamic_pointer_cast<KerML::Entities::LiteralExpression>(valueOf(feature)) != nullptr;
        if (!outcome.ok) {
            for (const Diagnostic& diagnostic : evaluated.diagnostics) {
                if (diagnostic.severity != Severity::Error) continue;
                outcome.category = categoryOf(diagnostic.message);
                break;
            }
            if (outcome.category.empty()) outcome.category = "failed without a diagnostic";
            // (allowed only for the features that are named in the list of the allowed errors)
            for (const char* pinned : {"a Real does not fit into an Integer", "Integer overflow", "the invocation is not bound to a function"}) {
                if (outcome.category == pinned) outcome.category += " in " + SysMLv2::Evaluation::qualifiedNameOf(feature);
            }
            ++result.errors[outcome.category];
        } else {
            ++result.ok;
        }
        const std::string name = SysMLv2::Evaluation::qualifiedNameOf(feature);
        if (name.find("<unnamed>") != std::string::npos) {
            ++result.skipped;
        } else if (!seen.insert(name).second) {
            duplicates.insert(name);
        } else {
            result.outcomes.emplace(name, std::move(outcome));
        }
    }
    for (const std::string& name : duplicates) {
        result.outcomes.erase(name);
        ++result.skipped;
    }
    result.seconds = std::chrono::duration<double>(std::chrono::steady_clock::now() - start).count();
    return result;
}

void print(const char* what, const Sweep& sweep) {
    std::cout << "[  INFO  ] " << what << ": features with a value expression: " << sweep.withValue << ", evaluated ok: " << sweep.ok
              << ", with errors: " << sweep.withValue - sweep.ok << ", compared by name: " << sweep.outcomes.size() << ", not unique or unnamed: "
              << sweep.skipped << ", warnings about an overridden bound value: " << sweep.overriding << " (" << sweep.seconds << " s)" << std::endl;
    std::cout << "[  INFO  ]   features whose value evaluates a not given feature of a larger multiplicity (Warning): " << sweep.emptyPrototypes << std::endl;
    std::size_t shown = 0;
    for (const auto& [pattern, count] : sweep.emptyPatterns) {
        if (++shown > 8) break;
        std::cout << "[  INFO  ]     " << count << " x " << pattern << std::endl;
    }
    for (const auto& [category, count] : sweep.errors) std::cout << "[  INFO  ]   " << count << " x " << category << std::endl;
}

}   // namespace

// Evaluates every feature value of the library that is an expression: nothing crashes or hangs, and no feature fails in a way that
// would point at a defect (arity errors, exceptions, named arguments, unbound operators); what is allowed are the things that later
// steps implement.
TYPED_TEST(EvaluationTest, EveryFeatureValueOfTheStandardLibraryEvaluatesWithoutAnUnexpectedError) {
    if constexpr (TypeParam::HasLibrary) {
        Session& session = this->session();
        session.load(SourceLanguage::KerML, "");   // (nothing of the tests in the user source)
        const Sweep result = sweep(session.workspace());
        print(TypeParam::HasLibrary && std::string(TypeParam::directory()) == SYSML_LIBRARY_DIR ? "text library" : "XMI library", result);
        EXPECT_GT(result.withValue, 0u);
        EXPECT_GT(result.ok, 0u);
        const std::set<std::string> allowed = {
            // (index, select and collect expressions, feature chains and references are evaluated now)
            "not supported yet: ConstructorExpression", "not supported yet: a function value (a body expression) as a result; function values can be passed to functions, not returned", "not supported yet: MetadataAccessExpression",
            // library functions that are not implemented: the classification operators, `[` (units) and the vector, complex and spatial
            // functions (steps 7 and later)
            "no native implementation",
            // Integers are 64 bit: SIPrefixes::zebi and yobi have the conversion factors 1000^7 and 1000^8 (and 1024^7, 1024^8), which
            // do not fit (pinned by name)
            "Integer overflow in SIPrefixes::yobi::conversionFactor", "Integer overflow in SIPrefixes::zebi::conversionFactor",
            // references to `self` in features that are evaluated without a target (there is no instance to be self)
            "'self' has no target in this evaluation",
            // `that` is bound by the invocation of a body expression (select, collect, ...), which comes with step 6
            "'that' is not bound here",
            // circular definitions of the library itself, pinned by name:
            //  - `item :>> rf : RightTriangle { attribute :>> width = rf.width; }` (ShapeItems.sysml);
            //  - `feature redefines isRunToCompletion default this.isRunToCompletion;` and the same for runToCompletionScope
            //    (StatePerformances.kerml): `this` is the performance itself, so the default value is the feature's own value;
            //  - in the XMI only, the anonymous parameter of `accept apayload: Anything via receiver` of AcceptAction: a feature that
            //    redefines a parameter and has the reference to that parameter as its value (a feature value that the pilot derived).
            "cyclic definition: ShapeItems::RightTriangularPrism::rf::width -> ShapeItems::RightTriangularPrism::rf::width",
            //  - `private feature observations[0..*] : ObserveChange = observations->select{...}` (Observation.kerml): the value of the
            //    feature is a selection from itself;
            "cyclic definition: Observation::ChangeMonitor::cancelObservation::observations -> Observation::ChangeMonitor::cancelObservation::observations",
            "cyclic definition: StatePerformances::StatePerformance::isRunToCompletion -> StatePerformances::StatePerformance::isRunToCompletion",
            "cyclic definition: StatePerformances::StatePerformance::runToCompletionScope -> StatePerformances::StatePerformance::runToCompletionScope",
            "cyclic definition: Actions::AcceptAction::aState::aTransition::<unnamed>::<unnamed> -> Actions::AcceptAction::aState::aTransition::<unnamed>::<unnamed>",
            // functions of the library that specialize a function with a native one but have a body of their own (VectorFunctions): step 6
            "not supported yet: a specialization with a body of its own or reordered parameters",
            // invocations of features that are no functions and have no result (abstract calculation usages such as `getElapsedUtcTime`)
            "it is no function and has no result",
            // the invariant `RealFunctions::round(pi * 1E20) == 314159265358979323846.0` of TrigFunctions::piPrecision (XMI only): the
            // library assumes an unbounded Integer, an Integer here is 64 bit, and the Real is beyond that (pinned by name)
            "a Real does not fit into an Integer in TrigFunctions::piPrecision::<unnamed>::<unnamed>",
            // an anonymous invocation of Observation::ObserveChange::wait::ifTest that the model leaves unbound (XMI only)
            "the invocation is not bound to a function in Observation::ObserveChange::wait::ifTest::<unnamed>::<unnamed>"};
        for (const auto& [category, count] : result.errors) EXPECT_TRUE(allowed.count(category) == 1) << count << " x unexpected: " << category;
    }
}

// The same library from text and from XMI must evaluate the same: the XMI import stores the arguments and the invoked function in
// another shape (see Evaluator.h), and nothing may get lost there.
TEST(EvaluationLibrary, TheTextAndTheXmiLibraryGiveTheSameResults) {
    Session& text = sharedSession<TextLibrary>();
    Session& xmi = sharedSession<XmiLibrary>();
    text.load(SourceLanguage::KerML, "");
    xmi.load(SourceLanguage::KerML, "");
    const Sweep fromText = sweep(text.workspace());
    const Sweep fromXmi = sweep(xmi.workspace());
    print("text", fromText);
    print("XMI", fromXmi);
    std::size_t compared = 0, onlyOne = 0, comparedOk = 0, comparedComputed = 0, knownResolverDifference = 0;
    std::map<std::string, std::size_t> mismatches;
    std::vector<std::string> examples;
    for (const auto& [name, left] : fromText.outcomes) {
        const auto right = fromXmi.outcomes.find(name);
        if (right == fromXmi.outcomes.end()) {
            ++onlyOne;
            continue;
        }
        ++compared;
        if (left.ok && right->second.ok) {
            ++comparedOk;
            if (!left.literal) ++comparedComputed;
        }
        std::string kind;
        if (left.ok != right->second.ok) kind = "ok differs: " + (left.ok ? "ok" : left.category) + " vs " + (right->second.ok ? "ok" : right->second.category);
        else if (!left.ok && left.category != right->second.category) {
            kind = "category differs: " + left.category + " vs " + right->second.category;
        }
        else if (left.ok && !sameValue(left.value, right->second.value)) {
            // The one known difference, caused by what the two models contain (investigated): the value is the chain
            // `aState.aTransition.accepter.acceptedMessage`. Parsed from text, the transition has no step of its own for `accept
            // apayload ...`, so the link `accepter` is TransitionAction::accepter, which owns the redefinition `acceptedMessage :>>
            // acceptedTransfer`, and the value is TransitionAction::acceptedMessage. The pilot's XMI has that step as an anonymous
            // AcceptActionUsage and links the chain to it, but records no general for it (the implied redefinition of `accepter` is
            // not stored, as ownedRedefinition / ownedSubsetting / ownedTyping of the step are empty), so its closure is empty and the
            // value is the bare AcceptMessageAction::acceptedMessage. The information is missing in the XMI, not in the evaluator.
            if (isKnownDifference(name)) {
                ++knownResolverDifference;
                continue;
            }
            kind = "value differs";
        }
        if (kind.empty()) continue;
        ++mismatches[kind];
        if (examples.size() < 20) examples.push_back(name + ": " + kind + " (" + describeValue(left.value) + " vs " + describeValue(right->second.value) + ")");
    }
    for (const auto& [name, right] : fromXmi.outcomes) {
        if (fromText.outcomes.find(name) == fromText.outcomes.end()) ++onlyOne;
    }
    std::cout << "[  INFO  ] compared by name: " << compared << " (" << comparedOk << " evaluated ok in both), present in only one of the two: " << onlyOne << ", mismatches: ";
    std::size_t total = 0;
    for (const auto& [kind, count] : mismatches) total += count;
    std::cout << total << std::endl;
    for (const auto& [kind, count] : mismatches) std::cout << "[  INFO  ]   " << count << " x " << kind << std::endl;
    for (const std::string& example : examples) std::cout << "[  INFO  ]   e.g. " << example << std::endl;
    std::cout << "[  INFO  ] evaluated ok in both and computed (not literals): " << comparedComputed << std::endl;
    std::cout << "[  INFO  ] known difference caused by the resolver (excluded by name): " << knownResolverDifference << std::endl;
    // (of the six names, only Actions::AcceptAction::acceptedMessage still differs: the five ShapeItems ones agree since the resolver binds the
    // unnamed redefinitions of a value expression's scope like the pilot; their names stay in the list until the evaluator side revisits it)
    EXPECT_EQ(knownResolverDifference, 1u);
    EXPECT_GT(compared, 1000u);
    EXPECT_GE(comparedComputed, 350u);   // (measured: 384, almost all of them unary minus; the pilot-shaped fixture below adds invocations)
    EXPECT_EQ(total, 0u);
}

// A function that specializes a library function before the library is loaded, evaluated again after it was loaded and resolved:
// the generals of the function change in place, and the evaluator must see that (it keeps no cache between two calls).
TEST(EvaluationLibrary, ASpecializationIsEvaluatedAgainAfterTheLibraryWasLoaded) {
    Workspace workspace;
    workspace.addText("package P { function F specializes DataFunctions::'+'; feature x = F(1, 2); }", "user.kerml", SourceLanguage::KerML, 1);
    workspace.resolve();
    const auto feature = std::dynamic_pointer_cast<KerML::Entities::Feature>(workspace.find("P::x"));
    ASSERT_NE(feature, nullptr);
    const Evaluator evaluator;
    const Result before = evaluator.evaluateFeatureValue(feature);
    EXPECT_TRUE(before.value.isNull());
    ASSERT_EQ(before.diagnostics.size(), 1u);
    EXPECT_NE(before.diagnostics.front().message.find("no native implementation for P::F"), std::string::npos) << before.diagnostics.front().message;
    ASSERT_GT(workspace.loadLibrary(SYSML_LIBRARY_DIR), 0u);
    workspace.resolve();
    ASSERT_EQ(feature, std::dynamic_pointer_cast<KerML::Entities::Feature>(workspace.find("P::x")));   // (the same objects)
    const Result after = evaluator.evaluateFeatureValue(feature);
    EXPECT_EQ(after.value, I(3));
    EXPECT_TRUE(after.diagnostics.empty()) << (after.diagnostics.empty() ? "" : after.diagnostics.front().message);
}

// Constraint and calculation usages are expressions themselves: both entry points evaluate them as expressions, which is not supported
// yet, instead of a silent null.
TYPED_TEST(EvaluationTest, UsagesThatAreExpressionsAreNotSilentlyNull) {
    Session& session = this->session();
    session.load(SourceLanguage::SysML, "constraint x { 1 < 2 } calc y { 1 + 2 } attribute z default = 5; attribute w := 6;");
    ASSERT_EQ(session.syntaxErrors(), 0u);
    for (const char* name : {"x", "y"}) {
        SCOPED_TRACE(name);
        const FeaturePtr feature = session.feature(name);
        ASSERT_NE(feature, nullptr);
        const auto expression = std::dynamic_pointer_cast<KerML::Entities::Expression>(feature);
        ASSERT_NE(expression, nullptr) << feature->getType();
        for (const Result& result : {Evaluator().evaluateFeatureValue(feature), Evaluator().evaluate(expression)}) {
            EXPECT_TRUE(result.value.isNull());
            ASSERT_EQ(result.diagnostics.size(), 1u);
            EXPECT_EQ(result.diagnostics.front().message, "not supported yet: " + feature->getType());
            EXPECT_EQ(result.diagnostics.front().element, feature);
        }
    }
    // default and initial values are treated like bound values for now
    EXPECT_EQ(Evaluator().evaluateFeatureValue(session.feature("z")).value, I(5));
    EXPECT_EQ(Evaluator().evaluateFeatureValue(session.feature("w")).value, I(6));
}

// A function that specializes a library function must not silently run the native implementation of the general: not when it has a
// body of its own, and not when its parameters redefine those of the general in another order. A library specialization that has
// neither is fine.
TYPED_TEST(EvaluationTest, ASpecializationWithABodyRunsTheBodyAndReorderedParametersAreHandled) {
    if constexpr (TypeParam::HasLibrary) {
        Session& session = this->session();
        session.load(SourceLanguage::KerML,
                     "function H specializes DataFunctions::'+' { in a : ScalarValues::Integer; in b : ScalarValues::Integer; return : ScalarValues::Integer = a * b; } "
                     "function G specializes DataFunctions::'-' { in a :>> y; in b :>> x; } "
                     "feature h = H(2, 3); feature g = G(1, 10); feature hn = H(a = 2, b = 3); feature gn = G(a = 1, b = 10); "
                     "feature lib = IntegerFunctions::'-'(10, 4); feature libNamed = IntegerFunctions::'-'(y = 4, x = 10);");
        ASSERT_EQ(session.syntaxErrors(), 0u);
        const Evaluator evaluator;
        // the body of H runs (2 * 3), G redefines the parameters in the other order (10 - 1) and still uses the native `-`
        for (const auto& [name, expected] : std::vector<std::pair<const char*, Value>>{{"h", I(6)}, {"g", I(9)}, {"hn", I(6)}, {"gn", I(9)}}) {
            SCOPED_TRACE(name);
            const Result result = evaluator.evaluateFeatureValue(session.feature(name));
            EXPECT_EQ(result.value, expected);
            EXPECT_TRUE(result.diagnostics.empty()) << (result.diagnostics.empty() ? "" : result.diagnostics.front().message);
        }
        // a library specialization without a body keeps working, positional and named
        EXPECT_EQ(evaluator.evaluateFeatureValue(session.feature("lib")).value, I(6));
        EXPECT_TRUE(evaluator.evaluateFeatureValue(session.feature("lib")).ok());
        EXPECT_EQ(evaluator.evaluateFeatureValue(session.feature("libNamed")).value, I(6));
    }
}

// Text -> XmiWriter -> read back: the operands of the operators are then owned through plain FeatureMemberships and argument() is
// empty; the evaluation must give what the text gives.
TEST(EvaluationXmiRoundTrip, TheValuesOfWrittenAndReadBackModelsEqualThoseOfTheText) {
    std::string longList = "(1";
    for (int element = 2; element <= 300; ++element) longList += ", " + std::to_string(element);
    longList += ")";
    const std::vector<std::pair<std::string, Value>> cases = {
        {"10 - 4", I(6)}, {"2 ** 3 ** 2", I(512)}, {"if false ? 1 else 2", I(2)}, {"-(3 + 4) * 2", I(-14)}, {"true and (1 < 2)", B(true)},
        {longList, Value()},   // (compared with the text only)
    };
    const std::filesystem::path directory = std::filesystem::temp_directory_path() / ("sysmlv2-evaluation-roundtrip-" + std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    std::filesystem::create_directories(directory);
    for (std::size_t index = 0; index < cases.size(); ++index) {
        SCOPED_TRACE(index == 5 ? "300 elements" : cases[index].first);
        Workspace text;
        text.addText("package P { feature d = " + cases[index].first + "; }", "m.kerml", SourceLanguage::KerML, 1);
        text.resolve();
        ASSERT_TRUE(text.errors().empty());
        const Result fromText = Evaluator().evaluateFeatureValue(std::dynamic_pointer_cast<KerML::Entities::Feature>(text.find("P::d")));
        ASSERT_TRUE(fromText.ok()) << (fromText.diagnostics.empty() ? "" : fromText.diagnostics.front().message);
        if (index != 5) EXPECT_EQ(fromText.value, cases[index].second);
        else EXPECT_EQ(fromText.value.size(), 300u);

        const std::string file = (directory / ("m" + std::to_string(index) + ".kermlx")).string();
        ASSERT_TRUE(text.writeXmi(0, file).empty());
        Workspace read;
        read.addFile(file, 1);
        read.resolve();
        ASSERT_TRUE(read.errors().empty());
        const auto feature = std::dynamic_pointer_cast<KerML::Entities::Feature>(read.find("P::d"));
        ASSERT_NE(feature, nullptr);
        const auto expression = valueOf(feature);
        ASSERT_NE(expression, nullptr);
        const Result fromXmi = Evaluator().evaluateFeatureValue(feature);
        EXPECT_TRUE(fromXmi.ok()) << (fromXmi.diagnostics.empty() ? "" : fromXmi.diagnostics.front().message);
        EXPECT_EQ(fromXmi.value, fromText.value);
        EXPECT_TRUE(fromXmi.diagnostics.empty());
    }
    std::filesystem::remove_all(directory);
}

namespace {

/// A user model in the shape of the pilot implementation's XMI: `DataFunctions::'-'` invoked positionally and with named arguments.
class PilotFixture {
public:
    PilotFixture(Workspace& library) {
        const auto minus = std::dynamic_pointer_cast<KerML::Entities::Function>(library.find("DataFunctions::'-'"));
        EXPECT_NE(minus, nullptr);
        std::vector<std::string> parameters;
        for (const auto& relationship : minus->ownedRelationship()) {
            const auto membership = std::dynamic_pointer_cast<KerML::Entities::Membership>(relationship);
            const auto parameter = membership ? std::dynamic_pointer_cast<KerML::Entities::Feature>(membership->memberElement()) : nullptr;
            if (parameter && parameter->direction() && *parameter->direction() != KerML::Entities::OUT) parameters.push_back(parameter->elementId());
        }
        EXPECT_EQ(parameters.size(), 2u);   // (x, y)
        const std::filesystem::path library_file = std::filesystem::path(SYSML_LIBRARY_XMI_DIR) / "Kernel Libraries" / "Kernel Function Library" / "DataFunctions.kermlx";
        Directory = std::filesystem::temp_directory_path() / ("sysmlv2-evaluation-pilot-" + std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
        std::filesystem::create_directories(Directory);
        std::string href = std::filesystem::relative(library_file, Directory).generic_string();
        for (std::size_t position = href.find(' '); position != std::string::npos; position = href.find(' ', position)) href.replace(position, 1, "%20");
        const std::string functionHref = href + "#" + minus->elementId();
        const auto parameterHref = [&](std::size_t index) { return href + "#" + parameters.at(index); };

        std::ostringstream xml;
        xml << "<?xml version=\"1.0\" encoding=\"ASCII\"?>\n"
            << "<sysml:Namespace xmi:version=\"2.0\" xmlns:xmi=\"http://www.omg.org/XMI\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" "
            << "xmlns:sysml=\"https://www.omg.org/spec/SysML/20250201\" " << ids("xmi:id", "elementId") << ">\n"
            << "<ownedRelationship xsi:type=\"sysml:OwningMembership\" " << ids("xmi:id", "elementId") << ">\n"
            << "<ownedRelatedElement xsi:type=\"sysml:Package\" declaredName=\"XmiFixture\" " << ids("xmi:id", "elementId") << ">\n";
        invocation(xml, "positional", functionHref, {{"10", ""}, {"4", ""}}, parameterHref);
        invocation(xml, "named", functionHref, {{"1", "y"}, {"10", "x"}}, parameterHref);
        xml << "</ownedRelatedElement>\n</ownedRelationship>\n</sysml:Namespace>\n";
        File = (Directory / "fixture.kermlx").string();
        std::ofstream(File) << xml.str();
    }
    ~PilotFixture() { std::filesystem::remove_all(Directory); }
    const std::string& file() const { return File; }

private:
    std::string ids(const char* first, const char* second) {
        char buffer[40];
        std::snprintf(buffer, sizeof buffer, "00000000-0000-4000-8000-%012x", ++Counter);
        return std::string(first) + "=\"" + buffer + "\" " + second + "=\"" + buffer + "\"";
    }
    std::string lastId() const {
        char buffer[40];
        std::snprintf(buffer, sizeof buffer, "00000000-0000-4000-8000-%012x", Counter);
        return buffer;
    }

    /// One feature whose value is the invocation of the function with the given (value, redefined parameter name or "") arguments.
    template <class ParameterHref>
    void invocation(std::ostringstream& xml, const std::string& name, const std::string& functionHref,
                    const std::vector<std::pair<std::string, std::string>>& arguments, const ParameterHref& parameterHref) {
        xml << "<ownedRelationship xsi:type=\"sysml:OwningMembership\" " << ids("xmi:id", "elementId") << ">\n"
            << "<ownedRelatedElement xsi:type=\"sysml:Feature\" declaredName=\"" << name << "\" " << ids("xmi:id", "elementId") << ">\n"
            << "<ownedRelationship xsi:type=\"sysml:FeatureValue\" " << ids("xmi:id", "elementId") << ">\n"
            << "<ownedRelatedElement xsi:type=\"sysml:InvocationExpression\" " << ids("xmi:id", "elementId") << ">\n"
            << "<ownedRelationship xsi:type=\"sysml:Membership\" " << ids("xmi:id", "elementId") << ">\n"
            << "<memberElement xsi:type=\"sysml:Function\" href=\"" << functionHref << "\"/>\n</ownedRelationship>\n";
        for (const auto& [value, redefined] : arguments) {
            xml << "<ownedRelationship xsi:type=\"sysml:ParameterMembership\" " << ids("xmi:id", "elementId") << ">\n"
                << "<ownedRelatedElement xsi:type=\"sysml:Feature\" direction=\"in\" " << ids("xmi:id", "elementId") << ">\n";
            const std::string parameterId = lastId();
            if (!redefined.empty()) {
                xml << "<ownedRelationship xsi:type=\"sysml:Redefinition\" " << ids("xmi:id", "elementId") << " redefiningFeature=\"" << parameterId << "\">\n"
                    << "<redefinedFeature href=\"" << parameterHref(redefined == "x" ? 0 : 1) << "\"/>\n</ownedRelationship>\n";
            }
            xml << "<ownedRelationship xsi:type=\"sysml:FeatureValue\" " << ids("xmi:id", "elementId") << ">\n"
                << "<ownedRelatedElement xsi:type=\"sysml:LiteralInteger\" " << ids("xmi:id", "elementId") << " value=\"" << value << "\"/>\n"
                << "</ownedRelationship>\n</ownedRelatedElement>\n</ownedRelationship>\n";
        }
        xml << "<ownedRelationship xsi:type=\"sysml:ReturnParameterMembership\" " << ids("xmi:id", "elementId") << ">\n"
            << "<ownedRelatedElement xsi:type=\"sysml:Feature\" direction=\"out\" " << ids("xmi:id", "elementId") << "/>\n</ownedRelationship>\n"
            << "</ownedRelatedElement>\n</ownedRelationship>\n</ownedRelatedElement>\n</ownedRelationship>\n";
    }

    unsigned Counter = 0;
    std::filesystem::path Directory;
    std::string File;
};

}   // namespace

// The sweep of the library has few computed values; this fixture is a user model in the shape of the pilot implementation's XMI whose
// invocations of a library function (positional and named) must evaluate against the XMI library.
TEST(EvaluationXmiRoundTrip, PilotShapedInvocationsEvaluateAgainstTheXmiLibrary) {
    Session& session = sharedSession<XmiLibrary>();
    session.load(SourceLanguage::KerML, "");
    const PilotFixture fixture(session.workspace());
    const std::size_t source = session.workspace().addFile(fixture.file(), 1);
    session.workspace().resolve();
    ASSERT_TRUE(session.workspace().errors(source).empty()) << session.workspace().errors(source).front()->description();
    const auto positional = std::dynamic_pointer_cast<KerML::Entities::Feature>(session.workspace().find("XmiFixture::positional"));
    const auto named = std::dynamic_pointer_cast<KerML::Entities::Feature>(session.workspace().find("XmiFixture::named"));
    ASSERT_NE(positional, nullptr);
    ASSERT_NE(named, nullptr);
    const auto call = std::dynamic_pointer_cast<KerML::Entities::InvocationExpression>(valueOf(positional));
    ASSERT_NE(call, nullptr);
    EXPECT_TRUE(call->argument().empty());   // (the pilot shape: the arguments are only parameters)
    const Result first = Evaluator().evaluateFeatureValue(positional);
    EXPECT_EQ(first.value, I(6));
    EXPECT_TRUE(first.diagnostics.empty()) << (first.diagnostics.empty() ? "" : first.diagnostics.front().message);
    const Result second = Evaluator().evaluateFeatureValue(named);
    EXPECT_EQ(second.value, I(9));
    EXPECT_TRUE(second.diagnostics.empty()) << (second.diagnostics.empty() ? "" : second.diagnostics.front().message);
    session.workspace().replaceSource(source, "", SourceLanguage::KerML);
    session.workspace().resolve();
}

// The check for an inherited native implementation covers every function between the invoked one and the one that holds the
// implementation, and all kinds of bodies.
TYPED_TEST(EvaluationTest, ASpecializationOfASpecializationRunsTheInheritedBody) {
    if constexpr (TypeParam::HasLibrary) {
        Session& session = this->session();
        session.load(SourceLanguage::KerML,
                     "function G :> DataFunctions::'+' { in a : ScalarValues::Integer; in b : ScalarValues::Integer; return : ScalarValues::Integer = a * b; } "
                     "function F :> G; "
                     "function G2 :> DataFunctions::'-' { in a :>> y; in b :>> x; } function F2 :> G2; "
                     "function K :> DataFunctions::'+' { in a : ScalarValues::Integer; in b : ScalarValues::Integer; out :>> result = a * b; } "
                     "function L1 :> DataFunctions::'+' { in a : ScalarValues::Integer; in b : ScalarValues::Integer; return : ScalarValues::Integer = a * b; } "
                     "function L2 :> L1; function L3 :> L2; "
                     "function N :> DataFunctions::'-' { in :>> x; in :>> y; } "
                     "feature f = F(2, 3); feature fn = F(a = 2, b = 3); feature f2 = F2(1, 10); feature f2n = F2(a = 1, b = 10); "
                     "feature k = K(2, 3); feature kn = K(a = 2, b = 3); feature l3 = L3(2, 3); "
                     "feature natural = NaturalFunctions::'+'(1, 2); feature integer = IntegerFunctions::'+'(1, 2); feature realMinus = RealFunctions::'-'(10, 4); "
                     "feature unnamed = N(10, 1); feature unnamedNamed = N(y = 1, x = 10);");
        ASSERT_EQ(session.syntaxErrors(), 0u);
        const Evaluator evaluator;
        // F inherits the body of G (2 * 3), F2 the reordered parameters of G2, K has its body as `out :>> result = a * b`, L3 inherits from L1
        for (const auto& [name, expected] : std::vector<std::pair<const char*, Value>>{{"f", I(6)}, {"fn", I(6)}, {"f2", I(9)}, {"f2n", I(9)}, {"k", I(6)}, {"kn", I(6)}, {"l3", I(6)}}) {
            SCOPED_TRACE(name);
            const Result result = evaluator.evaluateFeatureValue(session.feature(name));
            EXPECT_EQ(result.value, expected);
            EXPECT_TRUE(result.diagnostics.empty()) << (result.diagnostics.empty() ? "" : result.diagnostics.front().message);
        }
        // library specializations, six levels deep for NaturalFunctions, still evaluate
        for (const auto& [name, expected] : std::vector<std::pair<const char*, Value>>{{"natural", I(3)}, {"integer", I(3)}, {"realMinus", R(6.0)}, {"unnamed", I(9)}, {"unnamedNamed", I(9)}}) {
            SCOPED_TRACE(name);
            const Result result = evaluator.evaluateFeatureValue(session.feature(name));
            EXPECT_EQ(result.value, expected);
            EXPECT_TRUE(result.diagnostics.empty()) << (result.diagnostics.empty() ? "" : result.diagnostics.front().message);
        }
    }
}

// Feature references in a context ---------------------------------------------------------------------------------------------

namespace {

/// A feature of a model text and what its evaluation must give: a value without a diagnostic, or null and exactly one Error that
/// contains @c error.
struct ModelCase {
    std::string name;
    Value expected;
    std::string error = {};
};

/// The Errors of a result (Warnings, such as the one for overriding a bound value, do not matter to most cases).
std::vector<Diagnostic> errorsOf(const Result& result) {
    std::vector<Diagnostic> errors;
    for (const Diagnostic& diagnostic : result.diagnostics) {
        if (diagnostic.severity == Severity::Error) errors.push_back(diagnostic);
    }
    return errors;
}

/// Loads the model text and checks the cases (evaluateFeatureValue without a target; only the Errors are compared).
void checkModel(Session& session, SourceLanguage language, const std::string& text, const std::vector<ModelCase>& cases) {
    SCOPED_TRACE(languageName(language));
    session.load(language, text);
    ASSERT_EQ(session.syntaxErrors(), 0u) << text;
    for (const ModelCase& item : cases) {
        SCOPED_TRACE(item.name);
        const FeaturePtr feature = session.feature(item.name);
        ASSERT_NE(feature, nullptr);
        const Result result = Evaluator().evaluateFeatureValue(feature);
        const auto errors = errorsOf(result);
        if (item.error.empty()) {
            EXPECT_EQ(result.value, item.expected) << (result.diagnostics.empty() ? "(no diagnostic)" : result.diagnostics.front().message);
            EXPECT_TRUE(errors.empty()) << (errors.empty() ? "" : errors.front().message);
            EXPECT_TRUE(result.ok());
        } else {
            EXPECT_TRUE(result.value.isNull());
            ASSERT_EQ(errors.size(), 1u) << (errors.empty() ? "no diagnostic" : errors.front().message);
            EXPECT_NE(errors.front().message.find(item.error), std::string::npos) << errors.front().message;
        }
    }
}

}   // namespace

// A chain over a sequence: with features that redefine a common feature the resolver gives the chain that target; with features that only subset a
// common one, or are unrelated, it leaves the target open and the evaluator finds the feature in each member by its name.
TYPED_TEST(EvaluationTest, ChainsOverSequencesEvaluateInEveryMember) {
    Session& session = this->session();
    const std::string model =
        "part def Q { attribute base = 0; attribute r0 = 0; } part q1 : Q { attribute r :> base = 5; attribute :>> r0 = 7; } part q2 : Q { attribute r :> base = 6; attribute :>> r0 = 8; } "
        "part def X { attribute r = 1; } part def Y { attribute r :> X::r = 2; } part x : X; part y : Y; part def A { attribute f = 10; } part def B { attribute f = 20; } part a : A; part b : B; "
        "attribute subsetted = (q1, q2).r; attribute viaIf = (if true ? q1 else q2).r; attribute redefined = (q1, q2).r0; attribute otherOwner = (x, y).r; attribute unrelated = (a, b).f;";
    checkModel(session, SourceLanguage::SysML, model,
               {{"subsetted", Seq({5, 6})}, {"viaIf", I(5)}, {"redefined", Seq({7, 8})}, {"otherOwner", Seq({1, 2})}, {"unrelated", Seq({10, 20})}});
}

// A call whose invoked type is a feature chain (`c.twice(5)`): the model owns a chain feature [c, Car::twice] as the instantiated type and the
// evaluator runs the last feature at the instance that the prefix leads to.
TYPED_TEST(EvaluationTest, ACallThroughAFeatureChainRunsAtTheInstanceOfThePrefix) {
    Session& session = this->session();
    const std::string model =
        "part def Car { attribute m : Integer = 3; constraint ok { m > 2 } calc twice { in k : Integer; k * m } attribute inside = twice(5); } "
        "part c : Car { attribute :>> m = 1; } part c2 : Car { attribute :>> m = 10; } "
        "part def G { part car : Car { attribute :>> m = 2; } } part g : G; "
        "attribute r = c.twice(5); attribute b = c.ok(); attribute r3 = g.car.twice(2); attribute r0 = Car::twice(5); attribute inst = c.inside;";
    // (a prefix that is not a name chain, `(c, c2).twice(1)`, is not grammatical: the invoked type is a qualified name or a feature chain of names)
    checkModel(session, SourceLanguage::SysML, model,
               {{"r", I(5)}, {"b", B(false)}, {"r3", I(4)}, {"r0", I(15)}, {"inst", I(5)}});
}

TYPED_TEST(EvaluationTest, ReferencesAndOperatorsOverReferences) {
    Session& session = this->session();
    for (const SourceLanguage language : {SourceLanguage::KerML, SourceLanguage::SysML}) {
        checkModel(session, language, "$ x = 2; $ y = 3; $ z = x + y * 2; $ same = z; $ none; $ ofNone = none; $ sum = x + none;",
                   {{"z", I(8)}, {"same", I(8)}, {"ofNone", N()}, {"sum", N()}});
    }
    // a reference to a feature of an outer scope
    checkModel(session, SourceLanguage::SysML, "package Q { attribute k = 10; part def D { attribute v = k + 1; } } attribute w = Q::D::v;",
               {{"Q::D::v", I(11)}, {"w", I(11)}});
}

TYPED_TEST(EvaluationTest, TheValueOfAFeatureIsEvaluatedInTheContextOfItsTarget) {
    Session& session = this->session();
    const std::string model =
        "part def Base { attribute mass = 5; attribute double = mass * 2; } "
        "part def Derived :> Base { attribute :>> mass = 7; } "
        "part b : Base; part d : Derived; part p : Base { attribute :>> mass = 9; } "
        "attribute vb = b.double; attribute vd = d.double; attribute vp = p.double; attribute mb = b.mass; attribute md = d.mass; "
        "attribute own = Base::double;";
    checkModel(session, SourceLanguage::SysML, model, {{"vb", I(10)}, {"vd", I(14)}, {"vp", I(18)}, {"mb", I(5)}, {"md", I(7)}, {"own", I(10)}});
    // the feature in a target, through the API
    const Evaluator evaluator;
    const auto doubleFeature = session.feature("Base::double");
    ASSERT_NE(doubleFeature, nullptr);
    EXPECT_EQ(evaluator.evaluateFeatureValue(doubleFeature, session.feature("d")).value, I(14));
    EXPECT_EQ(evaluator.evaluateFeatureValue(doubleFeature, session.feature("p")).value, I(18));
    EXPECT_EQ(evaluator.evaluateFeatureValue(doubleFeature, session.feature("b")).value, I(10));
    EXPECT_EQ(evaluator.evaluateFeatureValue(doubleFeature).value, I(10));
}

TYPED_TEST(EvaluationTest, DefaultValuesApplyOnlyIfNoRedefinitionBindsAValue) {
    Session& session = this->session();
    const std::string model =
        "part def DP { attribute w default 3; attribute w2 = w + 1; } part dp : DP; part dq : DP { attribute :>> w = 10; } "
        "part dr : DP { attribute :>> w default 20; } "
        "attribute a = dp.w2; attribute b = dq.w2; attribute c = dr.w2; attribute d = dp.w; attribute e = dq.w; attribute f = dr.w;";
    checkModel(session, SourceLanguage::SysML, model, {{"a", I(4)}, {"b", I(11)}, {"c", I(21)}, {"d", I(3)}, {"e", I(10)}, {"f", I(20)}});
}

TYPED_TEST(EvaluationTest, TheMostSpecificRedefinitionWinsAndAnAmbiguousOneIsAnError) {
    Session& session = this->session();
    const std::string model =
        "part def A { attribute v = 1; attribute w = v; } part def B :> A { attribute :>> v = 2; } part def C :> B { attribute :>> v = 3; } "
        "part a1 : A; part b1 : B; part c1 : C; "
        "attribute va = a1.v; attribute vb = b1.v; attribute vc = c1.v; "
        "part def L :> A { attribute :>> v = 2; } part def R :> A { attribute :>> v = 3; } part def D :> L, R; part def D2 :> L, R { attribute :>> v = 4; } "
        "part d : D; part d2 : D2; part dl : L; "
        "attribute diamond = d.w; attribute decided = d2.w; attribute oneSide = dl.w;";
    checkModel(session, SourceLanguage::SysML, model,
               {{"va", I(1)}, {"vb", I(2)}, {"vc", I(3)}, {"diamond", N(), "ambiguous"}, {"decided", I(4)}, {"oneSide", I(2)}});
}

TYPED_TEST(EvaluationTest, ChainsNavigateThroughPartsAndSequences) {
    Session& session = this->session();
    const std::string model =
        "part def Engine { attribute power = 100; attribute twice = power * 2; } part def Car { part engine : Engine; } "
        "part car : Car; part car2 : Car { part :>> engine { attribute :>> power = 150; } } "
        "attribute pw = car.engine.power; attribute pw2 = car2.engine.power; attribute tw = car2.engine.twice; "
        "part def Wheel { attribute r = 5; } part q1 : Wheel; part q2 : Wheel { attribute :>> r = 6; } "
        "attribute rs = (q1, q2).r; attribute one = (q2).r; attribute missing = car.engine.nothere;";
    checkModel(session, SourceLanguage::SysML, model,
               {{"pw", I(100)}, {"pw2", I(150)}, {"tw", I(300)}, {"rs", Seq({5, 6})}, {"one", I(6)}, {"missing", N(), "unresolved feature 'nothere'"}});
}

TYPED_TEST(EvaluationTest, KerMLChainsAndRedefinitions) {
    Session& session = this->session();
    const std::string model =
        "class C { feature mass = 5; feature double = mass * 2; } class C2 specializes C { feature redefines mass = 7; } "
        "feature c : C; feature c2 : C2; feature r1 = c.double; feature r2 = c2.double; feature r3 = c2.mass;";
    checkModel(session, SourceLanguage::KerML, model, {{"r1", I(10)}, {"r2", I(14)}, {"r3", I(7)}});
}

TYPED_TEST(EvaluationTest, CyclesAreOneErrorAndNeverALoop) {
    Session& session = this->session();
    for (const SourceLanguage language : {SourceLanguage::KerML, SourceLanguage::SysML}) {
        checkModel(session, language, "$ a = b; $ b = a; $ s = s + 1; $ t = u; $ u = t + 1; $ ok = 1;",
                   {{"a", N(), "cyclic definition"}, {"b", N(), "cyclic definition"}, {"s", N(), "cyclic definition"}, {"t", N(), "cyclic definition"},
                    {"u", N(), "cyclic definition"}, {"ok", I(1)}});
    }
    // through a chain: the value of Cy::v is c2.v, which is Cy::v in c2 again
    checkModel(session, SourceLanguage::SysML, "part def Cy { attribute v = c2.v; } part c2 : Cy; attribute w = c2.v;", {{"w", N(), "cyclic definition"}});
}

TYPED_TEST(EvaluationTest, SelfIsTheTarget) {
    if constexpr (TypeParam::HasLibrary) {
        Session& session = this->session();
        checkModel(session, SourceLanguage::SysML, "part def S { attribute mass = 5; attribute m2 = self.mass * 2; } part s : S; attribute r = s.m2;",
                   {{"r", I(10)}});
        // without a target the feature is evaluated in its owning type: that is self; a feature of a package has no self
        checkModel(session, SourceLanguage::SysML, "part def S { attribute mass = 5; attribute m2 = self.mass; } attribute top = self;",
                   {{"S::m2", I(5)}, {"top", N(), "'self' has no target"}});
    }
}

// Text -> XmiWriter -> read back: the writer writes the referent of a FeatureReferenceExpression and the target feature of a
// FeatureChainExpression as the pilot's XMI does (a plain Membership whose memberElement is the feature), so the model that is read
// back evaluates to the same values as the text model.
namespace {

/// Writes the first source of @p text to a temporary file and reads it back into @p read; returns the directory (to be removed).
std::filesystem::path writeAndReadBack(Workspace& text, Workspace& read, const char* extension) {
    const std::filesystem::path directory = std::filesystem::temp_directory_path() / ("sysmlv2-evaluation-references-" + std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    std::filesystem::create_directories(directory);
    const std::string file = (directory / (std::string("m") + extension)).string();
    const auto writeErrors = text.writeXmi(0, file);
    EXPECT_TRUE(writeErrors.empty()) << (writeErrors.empty() ? "" : writeErrors.front()->description());
    read.addFile(file, 1);
    read.resolve();
    return directory;
}

/// The model text is evaluated as text and as XMI that was written from it and read back; the values must be the expected ones in both.
void checkRoundTrip(SourceLanguage language, const std::string& model, const std::vector<ModelCase>& cases) {
    SCOPED_TRACE(languageName(language));
    Workspace text;
    text.addText(model, language == SourceLanguage::KerML ? "m.kerml" : "m.sysml", language, 1);
    text.resolve();
    ASSERT_TRUE(text.errors().empty()) << model;
    Workspace read;
    const auto directory = writeAndReadBack(text, read, language == SourceLanguage::KerML ? ".kermlx" : ".sysmlx");
    ASSERT_TRUE(read.errors().empty());
    const auto feature = [](Workspace& workspace, const std::string& name) { return std::dynamic_pointer_cast<KerML::Entities::Feature>(workspace.find("P::" + name)); };
    for (const ModelCase& item : cases) {
        SCOPED_TRACE(item.name);
        const FeaturePtr fromText = feature(text, item.name);
        const FeaturePtr fromXmi = feature(read, item.name);
        ASSERT_NE(fromText, nullptr);
        ASSERT_NE(fromXmi, nullptr);
        const Result expected = Evaluator().evaluateFeatureValue(fromText);
        const Result actual = Evaluator().evaluateFeatureValue(fromXmi);
        EXPECT_EQ(expected.value, item.expected) << (expected.diagnostics.empty() ? "" : expected.diagnostics.front().message);
        EXPECT_EQ(actual.value, expected.value) << (actual.diagnostics.empty() ? "" : actual.diagnostics.front().message);
        EXPECT_EQ(actual.diagnostics.size(), expected.diagnostics.size());
        EXPECT_TRUE(actual.ok());
    }
    std::filesystem::remove_all(directory);
}

}   // namespace

TEST(EvaluationXmiRoundTrip, ReferencesAndChainsOfASysMLModelEvaluateLikeTheText) {
    checkRoundTrip(SourceLanguage::SysML,
                   "package P { part def Engine { attribute power = 100; attribute twice = power * 2; } part def Big :> Engine { attribute :>> power = 300; } "
                   "part e : Engine; part b : Big; attribute a = 3; attribute r1 = a + 1; attribute r2 = e.power; attribute r3 = b.twice; "
                   "part def V { part motor { attribute k = 2; part inner { attribute z = 7; } } } part v : V; attribute r4 = v.motor.inner.z; attribute r4b = v.motor.k * 2; "
                   "ref part x : Engine = e; attribute r5 = x.power; "
                   "enum def Col { enum red; enum green; } attribute c1 : Col = Col::red; attribute c2 : Col = Col::green; attribute r6 = c1 == c2; "
                   "attribute r7 = c1 == Col::red; attribute r8 = if c1 == Col::green ? 1 else 2; }",
                   {{"r1", I(4)}, {"r2", I(100)}, {"r3", I(600)}, {"r4", I(7)}, {"r4b", I(4)}, {"r5", I(100)}, {"r6", B(false)}, {"r7", B(true)}, {"r8", I(2)}});
}

TEST(EvaluationXmiRoundTrip, ReferencesAndChainsOfAKerMLModelEvaluateLikeTheText) {
    checkRoundTrip(SourceLanguage::KerML,
                   "package P { feature x = 2; feature y = 3; feature z = x + y * 2; class C { feature k = 1; feature kk = k + 1; } class C2 :> C { feature :>> k = 7; } "
                   "feature c : C2; feature r = c.kk; class Outer { feature mid { feature leaf = 5; } } feature o : Outer; feature deep = o.mid.leaf; }",
                   {{"z", I(8)}, {"r", I(8)}, {"deep", I(5)}});
}

// The resolver resolves the target of a chain whose left operand is computed (`(q1, q2).r`, `(w.m).i.z`, `(x).f`, `f(x).y`, `v#(1).z`,
// `(x as T).f`) in the static result type of the operand, so the writer writes it and the model that is read back evaluates like the text.
TEST(EvaluationXmiRoundTrip, ChainsWithAComputedLeftOperandEvaluateLikeTheTextAfterTheRoundTrip) {
    checkRoundTrip(SourceLanguage::SysML,
                   "package P { part def Engine { attribute power = 100; } part e : Engine; "
                   "part def Q { attribute r; } part q1 : Q { attribute :>> r = 5; } part q2 : Q { attribute :>> r = 6; } attribute s = (q1, q2).r; "
                   "part def Inner { attribute z = 9; } part def M { part i : Inner; } part def W { part m : M; } part w : W; attribute t = (w.m).i.z; "
                   "attribute paren = (e).power; attribute plain = w.m.i.z; }",
                   {{"s", Seq({5, 6})}, {"t", I(9)}, {"paren", I(100)}, {"plain", I(9)}});
}

TEST(EvaluationXmiRoundTrip, CallsThroughAFeatureChainEvaluateLikeTheTextAfterTheRoundTrip) {
    checkRoundTrip(SourceLanguage::SysML,
                   "package P { part def Car { attribute m = 3; constraint ok { m > 2 } calc twice { in k; k * m } } part c : Car { attribute :>> m = 1; } "
                   "part def G { part car : Car { attribute :>> m = 2; } } part g : G; "
                   "attribute r = c.twice(5); attribute b = c.ok(); attribute r3 = g.car.twice(2); attribute r0 = Car::twice(5); }",
                   {{"r", I(5)}, {"b", B(false)}, {"r3", I(4)}, {"r0", I(15)}});
}

TEST(EvaluationXmiRoundTrip, ChainsOverSequencesAndConditionalsEvaluateLikeTheTextAfterTheRoundTrip) {
    checkRoundTrip(SourceLanguage::KerML,
                   "package P { class Engine { feature power = 100; } feature e : Engine; "
                   "feature viaSeq = (e, e).power; feature viaIf = (if true ? e else e).power; }",
                   {{"viaSeq", Seq({100, 100})}, {"viaIf", I(100)}});
}

// Known gap: a chain through a feature without a declared type. The type of `x` in `ref part x = e` is only suggested by its value, so
// the resolver does not resolve the target of `x.power` (a plain chain: reported as unresolved) or of `(x).power` (reported as not
// attempted). The evaluator finds such a link by its name among the features of the target, so the text model evaluates. The writer writes
// nothing for a placeholder (a reference to it would dangle) and the pilot's shape has no place for a name without a feature, so after the
// round trip the evaluator reports the clean Error "the feature chain has no target feature in the model". (If the resolver ever resolves
// them, the text model and the XMI model agree and this test has to change.)
TEST(EvaluationXmiRoundTrip, ATargetThroughAnUntypedFeatureIsACleanErrorAfterTheRoundTrip) {
    const std::string model =
        "package P { part def Engine { attribute power = 100; } part e : Engine; ref part x = e; attribute r5 = x.power; attribute r6 = (x).power; }";
    Workspace text;
    text.addText(model, "m.sysml", SourceLanguage::SysML, 1);
    text.resolve();
    Workspace read;
    const auto directory = writeAndReadBack(text, read, ".sysmlx");
    const auto feature = [](Workspace& workspace, const char* name) { return std::dynamic_pointer_cast<KerML::Entities::Feature>(workspace.find(std::string("P::") + name)); };
    for (const char* name : {"r5", "r6"}) {
        SCOPED_TRACE(name);
        const auto value = std::dynamic_pointer_cast<KerML::Entities::FeatureChainExpression>(valueOf(feature(text, name)));
        ASSERT_NE(value, nullptr);
        EXPECT_EQ(value->targetFeature()->owner(), nullptr);   // (a placeholder)
        EXPECT_EQ(Evaluator().evaluateFeatureValue(feature(text, name)).value, I(100));
        const Result result = Evaluator().evaluateFeatureValue(feature(read, name));
        EXPECT_TRUE(result.value.isNull());
        ASSERT_EQ(result.diagnostics.size(), 1u);
        EXPECT_NE(result.diagnostics.front().message.find("the feature chain has no target feature in the model"), std::string::npos) << result.diagnostics.front().message;
    }
    std::filesystem::remove_all(directory);
}

TEST(EvaluationXmiRoundTrip, AReferenceThatCannotBeResolvedStaysACleanErrorAfterTheRoundTrip) {
    Workspace text;
    text.addText("package P { attribute a = 3; attribute bad = nothere + 1; attribute good = a; }", "m.sysml", SourceLanguage::SysML, 1);
    text.resolve();
    Workspace read;
    const auto directory = writeAndReadBack(text, read, ".sysmlx");
    const auto feature = [&](const char* name) { return std::dynamic_pointer_cast<KerML::Entities::Feature>(read.find(std::string("P::") + name)); };
    EXPECT_EQ(Evaluator().evaluateFeatureValue(feature("good")).value, I(3));
    const Result result = Evaluator().evaluateFeatureValue(feature("bad"));
    EXPECT_TRUE(result.value.isNull());
    ASSERT_EQ(result.diagnostics.size(), 1u);
    EXPECT_NE(result.diagnostics.front().message.find("in the model"), std::string::npos) << result.diagnostics.front().message;
    std::filesystem::remove_all(directory);
}

// isModelLevelEvaluable against the evaluator on the library: the pilot's XMI of the library carries no value of Expression::
// isModelLevelEvaluable (the attribute is only declared in KerML.kermlx), so there is no reference to compare with; this reports how
// the helper and the evaluator agree.
TYPED_TEST(EvaluationTest, TheModelLevelEvaluableHelperAgreesWithTheEvaluatorOnTheLibrary) {
    if constexpr (TypeParam::HasLibrary) {
        Session& session = this->session();
        session.load(SourceLanguage::KerML, "");
        std::size_t flagged = 0, evaluableOk = 0, evaluableError = 0, otherOk = 0, otherError = 0;
        std::map<std::string, std::size_t> evaluableErrors;
        const Evaluator evaluator;
        for (const auto& element : session.workspace().elements()) {
            if (const auto expression = std::dynamic_pointer_cast<KerML::Entities::Expression>(element)) flagged += expression->isModelLevelEvaluable() ? 1 : 0;
            const auto feature = std::dynamic_pointer_cast<KerML::Entities::Feature>(element);
            const auto expression = feature ? valueOf(feature) : nullptr;
            if (!expression) continue;
            const Result result = evaluator.evaluateFeatureValue(feature);
            const bool helper = SysMLv2::Evaluation::isModelLevelEvaluable(expression);
            if (helper && result.ok()) ++evaluableOk;
            else if (helper) {
                ++evaluableError;
                for (const Diagnostic& diagnostic : result.diagnostics) {
                    if (diagnostic.severity == Severity::Error) {
                        ++evaluableErrors[categoryOf(diagnostic.message)];
                        break;
                    }
                }
            } else if (result.ok()) ++otherOk;
            else ++otherError;
        }
        std::cout << "[  INFO  ] isModelLevelEvaluable(): expressions with the flag set in the model: " << flagged << "; helper true and evaluates ok: " << evaluableOk
                  << ", helper true but evaluation fails: " << evaluableError << ", helper false and evaluates ok: " << otherOk << ", helper false and fails: " << otherError
                  << std::endl;
        for (const auto& [category, count] : evaluableErrors) std::cout << "[  INFO  ]   helper true, fails: " << count << " x " << category << std::endl;
        EXPECT_GT(evaluableOk, 100u);
        // "model-level evaluable" (the specification) is not "this module can evaluate it": what the helper calls evaluable may still fail
        // for what the module does not implement yet (library functions without a native implementation, select / index, metadata
        // access), for overflow, for `self` and for circular definitions of the library; nothing else.
        for (const auto& [category, count] : evaluableErrors) {
            EXPECT_TRUE(category == "Integer overflow" || category == "no native implementation" || category.rfind("not supported yet", 0) == 0 ||
                        category == "a Real does not fit into an Integer" || category == "it is no function and has no result" ||
                        category.rfind("'self'", 0) == 0 || category.rfind("'that'", 0) == 0 || category.rfind("cyclic definition", 0) == 0)
                << count << " x " << category;
        }
    }
}

// Nested usages keep their outer instance ------------------------------------------------------------------------------------

TYPED_TEST(EvaluationTest, ANestedUsageEnteredThroughAChainStillSeesTheOuterInstance) {
    Session& session = this->session();
    const std::string model =
        "part def C { attribute k = 1; part e { attribute x = k; } } part def C2 :> C { attribute :>> k = 7; } part c : C2; attribute r1 = c.e.x; "
        "part def Vehicle { part engine { attribute power = 100; } part transmission { attribute input = engine.power; } } "
        "part myCar : Vehicle { part :>> engine { attribute :>> power = 200; } } attribute r2 = myCar.transmission.input; "
        "part def S { attribute mass = 5; part inner { attribute n = mass; } } part s : S { attribute :>> mass = 6; } attribute r3 = s.inner.n; "
        "part plain : S; attribute r4 = plain.inner.n;";
    checkModel(session, SourceLanguage::SysML, model, {{"r1", I(7)}, {"r2", I(200)}, {"r3", I(6)}, {"r4", I(5)}});
}

TYPED_TEST(EvaluationTest, ALibraryDefinitionInstantiatedByAUsageWithRedefinedAttributes) {
    if constexpr (TypeParam::HasLibrary) {
        Session& session = this->session();
        const std::string model =
            "item prism : ShapeItems::RightTriangularPrism { attribute :>> length = 3; attribute :>> width = 4; attribute :>> height = 5; } "
            "attribute ffLength = prism.ff.length; attribute ufleLength = prism.ufle.length; attribute bfeLength = prism.bfe.length; "
            "attribute tsleLength = prism.tsle.length; "
            "item rect : ShapeItems::Rectangle { attribute :>> length = 6; attribute :>> width = 2; } attribute e1 = rect.e1.length; attribute e2 = rect.e2.length; "
            "attribute e3 = rect.e3.length;";
        // (ufle, bfe and tsle are `[2]` edges that no usage gives: empty, with a Warning, not a prototype for two)
        checkModel(session, SourceLanguage::SysML, model,
                   {{"ffLength", I(3)}, {"ufleLength", N()}, {"bfeLength", N()}, {"tsleLength", N()}, {"e1", I(6)}, {"e2", I(2)}, {"e3", I(6)}});
    }
}

TYPED_TEST(EvaluationTest, AValueLessRedefinitionKeepsTheValueOfWhatItRedefines) {
    Session& session = this->session();
    const std::string model =
        "part def A2 { attribute v = 1; attribute d default 4; } part def B2 :> A2 { attribute :>> v; attribute :>> d; } part b2 : B2; "
        "attribute v2 = b2.v; attribute d2 = b2.d; "
        "part def Sh { attribute len; attribute area = len * 2; } part def Sq :> Sh { attribute :>> len = 3; } part def Sq2 :> Sq { attribute :>> len [1]; } part s2 : Sq2; "
        "attribute len2 = s2.len; attribute area2 = s2.area; "
        "part def A3 { attribute v = 1; attribute w = v; } part def B3 :> A3 { attribute :>> v default 2; } part b3 : B3; attribute v3 = b3.v; attribute w3 = b3.w;";
    checkModel(session, SourceLanguage::SysML, model, {{"v2", I(1)}, {"d2", I(4)}, {"len2", I(3)}, {"area2", I(6)}, {"v3", I(1)}, {"w3", I(1)}});
}

TYPED_TEST(EvaluationTest, ADiamondWithoutValuesFallsThroughToTheInheritedValue) {
    Session& session = this->session();
    const std::string model =
        "part def A { attribute v = 1; part q { attribute z = 9; } } part def L :> A { attribute :>> v; part :>> q; } part def R :> A { attribute :>> v; part :>> q; } "
        "part def D :> L, R; part d : D; attribute v = d.v; attribute z = d.q.z;";
    checkModel(session, SourceLanguage::SysML, model, {{"v", I(1)}, {"z", I(9)}});
}

TYPED_TEST(EvaluationTest, OverridingABoundValueIsAWarningAndKeepsTheValue) {
    Session& session = this->session();
    session.load(SourceLanguage::SysML,
                 "part def A4 { attribute v = 1; attribute w default 3; } part a4 : A4 { attribute :>> v = 2; attribute :>> w = 4; } "
                 "attribute twice = a4.v + a4.v; attribute defaulted = a4.w;");
    ASSERT_EQ(session.syntaxErrors(), 0u);
    const Result twice = Evaluator().evaluateFeatureValue(session.feature("twice"));
    EXPECT_EQ(twice.value, I(4));
    EXPECT_TRUE(twice.ok());
    EXPECT_FALSE(twice.failed);
    ASSERT_EQ(twice.diagnostics.size(), 1u);   // (once, although the value is used twice)
    EXPECT_EQ(twice.diagnostics.front().severity, Severity::Warning);
    EXPECT_NE(twice.diagnostics.front().message.find("only default values may be overridden"), std::string::npos) << twice.diagnostics.front().message;
    // a default value may be overridden
    const Result defaulted = Evaluator().evaluateFeatureValue(session.feature("defaulted"));
    EXPECT_EQ(defaulted.value, I(4));
    EXPECT_TRUE(defaulted.diagnostics.empty());
}

TYPED_TEST(EvaluationTest, AStructuralFeatureWithoutAValueIsTheElementItDenotes) {
    Session& session = this->session();
    session.load(SourceLanguage::SysML,
                 "part def Engine { attribute power = 100; } part e1 : Engine; part al = e1; attribute viaAlias = al.power; attribute direct = e1.power; "
                 "attribute plainAttribute; attribute ofAttribute = plainAttribute; attribute the = e1;");
    ASSERT_EQ(session.syntaxErrors(), 0u);
    const Evaluator evaluator;
    EXPECT_EQ(evaluator.evaluateFeatureValue(session.feature("viaAlias")).value, I(100));
    EXPECT_EQ(evaluator.evaluateFeatureValue(session.feature("direct")).value, I(100));
    EXPECT_TRUE(evaluator.evaluateFeatureValue(session.feature("ofAttribute")).value.isNull());   // (an attribute without a value: empty)
    const Result element = evaluator.evaluateFeatureValue(session.feature("the"));
    ASSERT_EQ(element.value.size(), 1u);
    const auto* item = std::get_if<std::shared_ptr<KerML::Entities::Element>>(&element.value.items().front());
    ASSERT_NE(item, nullptr);
    EXPECT_EQ(*item, session.feature("e1"));
    EXPECT_FALSE(element.value.toString().empty());
    EXPECT_FALSE(element.value.toJson().is_null());
}

TYPED_TEST(EvaluationTest, ByNameLookupOfAnUnresolvedLinkSkipsInheritedPrivateMembers) {
    Session& session = this->session();
    checkModel(session, SourceLanguage::SysML,
               "part def Pv { private attribute secret = 1; attribute shown = 2; } part def Pw :> Pv; part pw : Pw; "
               "attribute ok = (pw).shown; attribute hidden = (pw).secret;",
               {{"ok", I(2)}, {"hidden", N(), "unresolved feature 'secret'"}});
}

TYPED_TEST(EvaluationTest, SelfAliasesAndThat) {
    if constexpr (TypeParam::HasLibrary) {
        Session& session = this->session();
        session.load(SourceLanguage::KerML, "class Cc { feature me : Cc redefines self; feature y = me; } class Tt { feature v = that; } feature c : Cc; feature r = c.y; feature t : Tt; feature rt = t.v;");
        ASSERT_EQ(session.syntaxErrors(), 0u);
        const Result alias = Evaluator().evaluateFeatureValue(session.feature("r"));
        ASSERT_EQ(alias.value.size(), 1u) << (alias.diagnostics.empty() ? "" : alias.diagnostics.front().message);
        const auto* item = std::get_if<std::shared_ptr<KerML::Entities::Element>>(&alias.value.items().front());
        ASSERT_NE(item, nullptr);
        EXPECT_EQ(*item, session.feature("c"));
        // `that` is an Error unless it is bound
        const Result that = Evaluator().evaluateFeatureValue(session.feature("rt"));
        EXPECT_TRUE(that.value.isNull());
        ASSERT_EQ(that.diagnostics.size(), 1u);
        EXPECT_NE(that.diagnostics.front().message.find("'that' is not bound"), std::string::npos) << that.diagnostics.front().message;
    }
}

// Round 3: references that hold parts, untyped parts, enumerations, entry points ------------------------------------------------

TYPED_TEST(EvaluationTest, AReferenceThatHoldsAPartKeepsTheInstanceItIsFoundIn) {
    Session& session = this->session();
    const std::string model =
        "part def Seat { attribute load = 0; } "
        "part def Car { attribute mass = 1000; part seat : Seat { attribute :>> load = mass / 10; } ref part driverSeat : Seat = seat; ref part second : Seat = driverSeat; "
        "part seat2 : Seat { attribute :>> load = mass / 5; } ref part seats : Seat [2] = (seat, seat2); } "
        "part car : Car { attribute :>> mass = 2000; } "
        "attribute direct = car.seat.load; attribute viaAlias = car.driverSeat.load; attribute aliasOfAlias = car.second.load; attribute both = car.seats.load; "
        "part def E { attribute x = 1; } part def C { part e : E { attribute :>> x = 7; } ref part e2 : E = e; } part c : C; attribute viaE2 = c.e2.x; "
        "part def Garage { part inner : Car { attribute :>> mass = 3000; } ref part parked : Car = inner; } part g : Garage; "
        "attribute nested = g.parked.mass; attribute nestedSeat = g.parked.driverSeat.load; "
        "part def Car4 { attribute mass = 1000; part s1 : Seat { attribute :>> load = mass / 10; } ref part chosen : Seat; } "
        "part car4 : Car4 { attribute :>> mass = 500; ref part :>> chosen = s1; } attribute bound = car4.chosen.load;";
    checkModel(session, SourceLanguage::SysML, model,
               {{"direct", R(200.0)}, {"viaAlias", R(200.0)}, {"aliasOfAlias", R(200.0)}, {"both", Value(std::vector<SysMLv2::Evaluation::Item>{SysMLv2::Evaluation::Item(200.0), SysMLv2::Evaluation::Item(400.0)})},
                {"viaE2", I(7)}, {"nested", I(3000)}, {"nestedSeat", R(300.0)}, {"bound", R(50.0)}});
}

TYPED_TEST(EvaluationTest, UntypedPartsAndActionsAreDistinctElements) {
    Session& session = this->session();
    const std::string model =
        "part def Vehicle { part engine { } part transmission { } attribute same = engine == transmission; attribute itself = engine == engine; } part myCar : Vehicle; "
        "attribute r1 = myCar.same; attribute r2 = myCar.itself; attribute r3 = myCar.engine == myCar.transmission; "
        "part p2; part p4; attribute r4 = p2 == p4; attribute r5 = p2 == p2; action ac1; action ac2; attribute r6 = ac1 == ac2; attribute r7 = ac1 == ac1; "
        "attribute r8 = p2 != p4;";
    checkModel(session, SourceLanguage::SysML, model, {{"r1", B(false)}, {"r2", B(true)}, {"r3", B(false)}, {"r4", B(false)}, {"r5", B(true)}, {"r6", B(false)}, {"r7", B(true)}, {"r8", B(true)}});
}

TYPED_TEST(EvaluationTest, EnumerationLiteralsAreDistinctElements) {
    Session& session = this->session();
    const std::string model =
        "enum def Col { enum red; enum green; } attribute c1 : Col = Col::red; attribute c2 : Col = Col::green; "
        "attribute same = c1 == c2; attribute different = c1 != c2; attribute viaIf = if c1 == Col::green ? 1 else 2; attribute literals = Col::red == Col::green; "
        "attribute sameLiteral = Col::red == Col::red; attribute again = c1 == Col::red;";
    checkModel(session, SourceLanguage::SysML, model,
               {{"same", B(false)}, {"different", B(true)}, {"viaIf", I(2)}, {"literals", B(false)}, {"sameLiteral", B(true)}, {"again", B(true)}});
}

TYPED_TEST(EvaluationTest, AFeatureValueWithoutAValueOfItsOwnIsEvaluatedThroughItsEffectiveBinding) {
    Session& session = this->session();
    session.load(SourceLanguage::SysML, "part def A2 { attribute v = 1; } part def B2 :> A2 { attribute :>> v; } part def PD; part p1 : PD; part untyped; attribute plain;");
    ASSERT_EQ(session.syntaxErrors(), 0u);
    const Evaluator evaluator;
    // no target: the feature is evaluated in its owning type, and a redefinition without a value has the inherited value
    const Result inherited = evaluator.evaluateFeatureValue(session.feature("B2::v"));
    EXPECT_EQ(inherited.value, I(1));
    EXPECT_TRUE(inherited.diagnostics.empty());
    for (const char* name : {"p1", "untyped"}) {
        SCOPED_TRACE(name);
        const Result element = evaluator.evaluateFeatureValue(session.feature(name));
        ASSERT_EQ(element.value.size(), 1u);
        const auto* item = std::get_if<std::shared_ptr<KerML::Entities::Element>>(&element.value.items().front());
        ASSERT_NE(item, nullptr);
        EXPECT_EQ(*item, session.feature(name));
    }
    EXPECT_TRUE(evaluator.evaluateFeatureValue(session.feature("plain")).value.isNull());
}

TYPED_TEST(EvaluationTest, BothEntryPointsAgreeOnSelfWithoutATarget) {
    if constexpr (TypeParam::HasLibrary) {
        Session& session = this->session();
        session.load(SourceLanguage::SysML, "part def A { attribute s = self; } attribute top = self;");
        ASSERT_EQ(session.syntaxErrors(), 0u);
        const Evaluator evaluator;
        const auto feature = session.feature("A::s");
        ASSERT_NE(feature, nullptr);
        const auto expression = valueOf(feature);
        ASSERT_NE(expression, nullptr);
        for (const Result& result : {evaluator.evaluateFeatureValue(feature), evaluator.evaluate(expression)}) {
            ASSERT_EQ(result.value.size(), 1u) << (result.diagnostics.empty() ? "" : result.diagnostics.front().message);
            const auto* item = std::get_if<std::shared_ptr<KerML::Entities::Element>>(&result.value.items().front());
            ASSERT_NE(item, nullptr);
            EXPECT_EQ(*item, session.element("A"));   // (self is the type that stands for any instance of it)
        }
        // a feature of a package has no featuring type
        const auto top = session.feature("top");
        for (const Result& result : {evaluator.evaluateFeatureValue(top), evaluator.evaluate(valueOf(top))}) {
            EXPECT_TRUE(result.value.isNull());
            ASSERT_EQ(result.diagnostics.size(), 1u);
            EXPECT_NE(result.diagnostics.front().message.find("'self' has no target"), std::string::npos);
        }
    }
}

TYPED_TEST(EvaluationTest, ATargetThatDoesNotConformIsAnError) {
    Session& session = this->session();
    session.load(SourceLanguage::SysML, "part def A { attribute v = 1; } part def B { attribute v = 5; } part aa : A; part bb : B; attribute outer = 3;");
    ASSERT_EQ(session.syntaxErrors(), 0u);
    const Evaluator evaluator;
    const auto bv = session.feature("B::v");
    const Result wrong = evaluator.evaluateFeatureValue(bv, session.feature("aa"));
    EXPECT_TRUE(wrong.value.isNull());
    ASSERT_EQ(wrong.diagnostics.size(), 1u);
    EXPECT_NE(wrong.diagnostics.front().message.find("does not conform"), std::string::npos) << wrong.diagnostics.front().message;
    EXPECT_EQ(evaluator.evaluateFeatureValue(bv, session.feature("bb")).value, I(5));
    EXPECT_EQ(evaluator.evaluateFeatureValue(session.feature("outer"), session.feature("aa")).value, I(3));   // (a feature of a package conforms)
}

TYPED_TEST(EvaluationTest, ADefaultThatIsMoreSpecificThanABoundValueIsIgnoredWithAWarning) {
    Session& session = this->session();
    session.load(SourceLanguage::SysML, "part def A { attribute v = 1; } part def B :> A { attribute :>> v default 2; } part b : B; attribute r = b.v;");
    ASSERT_EQ(session.syntaxErrors(), 0u);
    const Result result = Evaluator().evaluateFeatureValue(session.feature("r"));
    EXPECT_EQ(result.value, I(1));
    EXPECT_TRUE(result.ok());
    ASSERT_EQ(result.diagnostics.size(), 1u);
    EXPECT_EQ(result.diagnostics.front().severity, Severity::Warning);
    EXPECT_NE(result.diagnostics.front().message.find("default value"), std::string::npos) << result.diagnostics.front().message;
}

TYPED_TEST(EvaluationTest, TheAmbiguityMessageNamesTheFeatures) {
    Session& session = this->session();
    session.load(SourceLanguage::SysML,
                 "part def A { attribute v = 1; attribute w = v; } part def L :> A { attribute :>> v = 2; } part def R :> A { attribute :>> v = 3; } part def D :> L, R; "
                 "part d : D; attribute r = d.w;");
    const Result result = Evaluator().evaluateFeatureValue(session.feature("r"));
    ASSERT_EQ(result.diagnostics.size(), 1u);
    EXPECT_NE(result.diagnostics.front().message.find("L::v and R::v"), std::string::npos) << result.diagnostics.front().message;
}

TYPED_TEST(EvaluationTest, OnlyFunctionsOfTheKernelFunctionLibraryAreModelLevelEvaluable) {
    if constexpr (TypeParam::HasLibrary) {
        Session& session = this->session();
        // a user package that is named like a library package is no library package
        session.load(SourceLanguage::KerML,
                     "package MyFunctions { function f { in x : ScalarValues::Integer; return : ScalarValues::Integer = x; } } "
                     "feature user = MyFunctions::f(1); feature lib = DataFunctions::'+'(1, 2); feature viaOperator = 1 + 2; feature arrow = 3->DataFunctions::'-'(1);");
        ASSERT_EQ(session.syntaxErrors(), 0u);
        const auto evaluable = [&](const char* name) { return SysMLv2::Evaluation::isModelLevelEvaluable(valueOf(session.feature(name))); };
        EXPECT_FALSE(evaluable("user"));
        EXPECT_TRUE(evaluable("lib"));
        EXPECT_TRUE(evaluable("viaOperator"));
        EXPECT_TRUE(evaluable("arrow"));
    }
}

// Step 6: user-defined functions, body expressions, sequences ------------------------------------------------------------------

TYPED_TEST(EvaluationTest, RecursiveFunctionsAndTheDepthLimit) {
    Session& session = this->session();
    const std::string kerml =
        "function fact { in n : ScalarValues::Integer; return : ScalarValues::Integer = if n <= 1 ? 1 else n * fact(n - 1); } "
        "function fib { in n : ScalarValues::Integer; return : ScalarValues::Integer = if n < 2 ? n else fib(n - 1) + fib(n - 2); } "
        "function count { in n : ScalarValues::Integer; return : ScalarValues::Integer = if n == 0 ? 0 else count(n - 1) + 1; } "
        "$ f0 = fact(1); $ f5 = fact(5); $ f10 = fact(10); $ b10 = fib(10); $ c3 = count(3); $ c40 = count(40); $ deep = count(100000);";
    if constexpr (!TypeParam::HasLibrary) {
        // (the type ScalarValues::Integer is unresolved without the library, which does not matter for the evaluation)
    }
    checkModel(session, SourceLanguage::KerML, kerml,
               {{"f0", I(1)}, {"f5", I(120)}, {"f10", I(3628800)}, {"b10", I(55)}, {"c3", I(3)}, {"c40", I(40)}, {"deep", N(), "maximum call depth"}});
    // the same as calculations
    const std::string sysml =
        "calc def Fact { in n : Integer; return : Integer = if n <= 1 ? 1 else n * Fact(n - 1); } attribute f6 = Fact(6); attribute f20 = Fact(20);";
    checkModel(session, SourceLanguage::SysML, sysml, {{"f6", I(720)}, {"f20", I(2432902008176640000LL)}});
    // legitimate recursion is no cycle of definitions: the same local feature in several frames
    checkModel(session, SourceLanguage::SysML,
               "calc def Sum { in n : Integer; attribute rest = if n == 0 ? 0 else Sum(n - 1); return : Integer = n + rest; } attribute s10 = Sum(10);", {{"s10", I(55)}});
    // a real cycle of definitions still is one
    checkModel(session, SourceLanguage::SysML, "attribute a = b; attribute b = a;", {{"a", N(), "cyclic definition"}});
}

TYPED_TEST(EvaluationTest, CalculationsBindArgumentsToParameters) {
    Session& session = this->session();
    const std::string model =
        "calc def G { in a : Integer; in b : Integer = 2; attribute tmp = a * 2; return c : Integer = tmp + b; } "
        "attribute r1 = G(5); attribute r2 = G(5, 1); attribute r3 = G(b = 3, a = 1); attribute r4 = G(a = 4); "
        "calc def H { in x; x + 1 } attribute h = H(4); calc def Two { in x : Integer[1]; in y : Integer[1]; x - y } attribute t = Two(y = 1, x = 10); "
        "calc g : G; attribute viaUsage = g(7); attribute usageNamed = g(a = 7, b = 0); "
        "attribute tooMany = G(1, 2, 3); attribute unknown = G(z = 1); attribute twice = G(a = 1, a = 2); attribute missing = Two(1);";
    checkModel(session, SourceLanguage::SysML, model,
               {{"r1", I(12)}, {"r2", I(11)}, {"r3", I(5)}, {"r4", I(10)}, {"h", I(5)}, {"t", I(9)}, {"viaUsage", I(16)}, {"usageNamed", I(14)},
                {"tooMany", N(), "too many arguments"}, {"unknown", N(), "unknown parameter 'z'"}, {"twice", N(), "given twice"}, {"missing", N(), "missing argument"}});
}

TYPED_TEST(EvaluationTest, ResultsInAllTheirShapes) {
    Session& session = this->session();
    const std::string model =
        "function R1 { in x : ScalarValues::Integer; return : ScalarValues::Integer = x * 2; } "
        "function R2 { in x : ScalarValues::Integer; x * 3 } "
        "function R3 { in x : ScalarValues::Integer; return r : ScalarValues::Integer = x * 4; } "
        "function R4 :> R1 { in x : ScalarValues::Integer; out :>> result = x * 5; } "
        "$ a = R1(1); $ b = R2(1); $ c = R3(1); $ d = R4(1); $ nested = R1(R2(R3(1)));";
    // (R4 specializes R1 and gives its own result)
    checkModel(session, SourceLanguage::KerML, model, {{"a", I(2)}, {"b", I(3)}, {"c", I(4)}, {"d", I(5)}, {"nested", I(24)}});
}

TYPED_TEST(EvaluationTest, SequencesAndBodyExpressions) {
    if constexpr (TypeParam::HasLibrary) {
        Session& session = this->session();
        const std::string model =
            "attribute select1 = (1, 2, 3, 4)->ControlFunctions::select {in x; x > 2}; attribute reject1 = (1, 2, 3, 4)->ControlFunctions::reject {in x; x > 2}; "
            "attribute collect1 = (1, 2, 3)->ControlFunctions::collect {in x; x * 2}; attribute forAll1 = (1, 2, 3)->ControlFunctions::forAll {in x; x > 0}; "
            "attribute forAll2 = (1, 2, 3)->ControlFunctions::forAll {in x; x > 1}; attribute exists1 = (1, 2, 3)->ControlFunctions::exists {in x; x > 2}; "
            "attribute exists2 = (1, 2, 3)->ControlFunctions::exists {in x; x > 3}; attribute reduce1 = (1, 2, 3, 4)->ControlFunctions::reduce {in a; in b; a + b}; "
            "attribute reduce2 = (3, 9, 2)->ControlFunctions::reduce ScalarFunctions::max; attribute reduceEmpty = (1, 2, 3)->ControlFunctions::select {in x; x > 5}->ControlFunctions::reduce ScalarFunctions::max; "
            "attribute selectOne1 = (1, 2, 3, 4)->ControlFunctions::selectOne {in x; x > 2}; "
            "attribute selectExpr = (1, 2, 3, 4).?{ that > 2 }; attribute collectExpr = (1, 2, 3).{ that * 2 }; "
            "attribute allT = ControlFunctions::allTrue((true, true)); attribute allF = ControlFunctions::allTrue((true, false)); attribute anyT = ControlFunctions::anyTrue((false, true)); "
            "attribute anyF = ControlFunctions::anyTrue(null); attribute minimized = (3, 1, 2)->ControlFunctions::minimize {in x; x * 10}; attribute maximized = (3, 1, 2)->ControlFunctions::maximize {in x; x * 10}; "
            "attribute asString = BaseFunctions::ToString(1.5); attribute manyIndexes = (10, 20, 30)#((1, 3)); attribute nonBoolean = (1, 2)->ControlFunctions::select {in x; x}; "
            "attribute index1 = (10, 20, 30)#(2); attribute index2 = (10, 20, 30)#(5); attribute index3 = (10, 20, 30)#(0); attribute index4 = (10, 20, 30)#(1);";
        checkModel(session, SourceLanguage::SysML, model,
                   {{"select1", Seq({3, 4})}, {"reject1", Seq({1, 2})}, {"collect1", Seq({2, 4, 6})}, {"forAll1", B(true)}, {"forAll2", B(false)}, {"exists1", B(true)},
                    {"exists2", B(false)}, {"reduce1", I(10)}, {"reduce2", I(9)}, {"reduceEmpty", N()}, {"selectOne1", Seq({3})}, {"selectExpr", Seq({3, 4})},
                    {"collectExpr", Seq({2, 4, 6})}, {"index1", I(20)}, {"index2", N()}, {"index3", N()}, {"index4", I(10)}, {"allT", B(true)}, {"allF", B(false)}, {"anyT", B(true)}, {"anyF", B(false)}, {"minimized", I(10)}, {"maximized", I(30)},
                    {"asString", S("1.5")}, {"manyIndexes", Seq({10, 30})}, {"nonBoolean", N(), "unsupported argument types"}});
    }
}

TYPED_TEST(EvaluationTest, BodyExpressionsSeeOuterFeaturesAndTheContextInstance) {
    if constexpr (TypeParam::HasLibrary) {
        Session& session = this->session();
        const std::string model =
            "part def Item { attribute limit = 2; attribute big = (1, 2, 3, 4)->ControlFunctions::select {in x; x > limit}; attribute scaled = (1, 2)->ControlFunctions::collect {in x; x * limit}; } "
            "part plain : Item; part tight : Item { attribute :>> limit = 3; } "
            "attribute r1 = plain.big; attribute r2 = tight.big; attribute r3 = tight.scaled; "
            "calc def Count { in values; in threshold : Integer; return : Integer = SequenceFunctions::size(values->ControlFunctions::select {in v; v > threshold}); } "
            "attribute r4 = Count((1, 5, 7, 9), 4);";
        checkModel(session, SourceLanguage::SysML, model, {{"r1", Seq({3, 4})}, {"r2", Seq({4})}, {"r3", Seq({3, 6})}, {"r4", I(3)}});
    }
}

TYPED_TEST(EvaluationTest, RollupsOverPartsWithRedefinedMasses) {
    if constexpr (TypeParam::HasLibrary) {
        Session& session = this->session();
        const std::string model =
            "part def Component { attribute mass = 0; } "
            "part def Vehicle { part engine : Component { attribute :>> mass = 100; } part body : Component { attribute :>> mass = 300; } "
            "  attribute total = (engine, body).mass->NumericalFunctions::sum(); attribute heaviest = (engine.mass, body.mass)->ControlFunctions::maximize {in m; m}; } "
            "part car : Vehicle { part :>> engine { attribute :>> mass = 150; } } part plain : Vehicle; "
            "calc def TotalMass { in v : Vehicle; return : Integer = (v.engine.mass, v.body.mass)->NumericalFunctions::sum(); } "
            "calc def MassOf { in v : Vehicle; return : Integer = (v.engine, v.body)->ControlFunctions::collect {in p; p.mass}->NumericalFunctions::sum(); } "
            "attribute carTotal = car.total; attribute plainTotal = plain.total; attribute viaCalc = TotalMass(car); attribute viaCollect = MassOf(car); attribute heavy = car.heaviest;";
        checkModel(session, SourceLanguage::SysML, model, {{"carTotal", I(450)}, {"plainTotal", I(400)}, {"viaCalc", I(450)}, {"viaCollect", I(450)}, {"heavy", I(300)}});
    }
}

TYPED_TEST(EvaluationTest, NativeSequenceFunctions) {
    if constexpr (TypeParam::HasLibrary) {
        Session& session = this->session();
        const std::string model =
            "attribute size1 = SequenceFunctions::size((1, 2, 3)); attribute size0 = SequenceFunctions::size(null); attribute empty1 = SequenceFunctions::isEmpty(null); "
            "attribute empty2 = SequenceFunctions::isEmpty((1, 2)); attribute notEmpty1 = SequenceFunctions::notEmpty((1)); "
            "attribute inc1 = SequenceFunctions::includes((1, 2, 3), (2, 3)); attribute inc2 = SequenceFunctions::includes((1, 2), (2, 3)); attribute inc3 = SequenceFunctions::includes((1, 2), null); "
            "attribute only1 = SequenceFunctions::includesOnly((1, 2), (2, 1)); attribute exc1 = SequenceFunctions::excludes((1, 2), (3, 4)); attribute exc2 = SequenceFunctions::excludes((1, 2), (2, 4)); "
            "attribute uni = SequenceFunctions::union((1, 2), (3)); attribute inter = SequenceFunctions::intersection((1, 2, 3, 2), (2, 3)); attribute incl = SequenceFunctions::including((1, 2), (9)); "
            "attribute inclAt = SequenceFunctions::includingAt((1, 2, 3), (9, 8), 2); attribute excl = SequenceFunctions::excluding((1, 2, 3, 2), (2)); attribute exclAt = SequenceFunctions::excludingAt((1, 2, 3, 4), 2, 3); "
            "attribute exclAt1 = SequenceFunctions::excludingAt((1, 2, 3), 2); attribute sub = SequenceFunctions::subsequence((1, 2, 3, 4), 2, 3); attribute sub1 = SequenceFunctions::subsequence((1, 2, 3, 4), 3); "
            "attribute subOut = SequenceFunctions::subsequence((1, 2, 3), 2, 9); attribute head1 = SequenceFunctions::head((7, 8)); attribute head0 = SequenceFunctions::head(null); "
            "attribute tail1 = SequenceFunctions::tail((7, 8, 9)); attribute tail0 = SequenceFunctions::tail((7)); attribute last1 = SequenceFunctions::last((7, 8, 9)); "
            "attribute eq1 = SequenceFunctions::equals((1, 2), (1, 2)); attribute eq2 = SequenceFunctions::equals((1, 2), (1, 3)); attribute same1 = SequenceFunctions::same((1, 2), (1, 2)); "
            "attribute arrowSize = (1, 2, 3, 4)->SequenceFunctions::size(); attribute arrowHead = (5, 6)->SequenceFunctions::head();";
        checkModel(session, SourceLanguage::SysML, model,
                   {{"size1", I(3)}, {"size0", I(0)}, {"empty1", B(true)}, {"empty2", B(false)}, {"notEmpty1", B(true)}, {"inc1", B(true)}, {"inc2", B(false)}, {"inc3", B(true)},
                    {"only1", B(true)}, {"exc1", B(true)}, {"exc2", B(false)}, {"uni", Seq({1, 2, 3})}, {"inter", Seq({2, 3, 2})}, {"incl", Seq({1, 2, 9})},
                    {"inclAt", Seq({1, 9, 8, 3})}, {"excl", Seq({1, 3})}, {"exclAt", Seq({1, 4})}, {"exclAt1", Seq({1, 3})}, {"sub", Seq({2, 3})}, {"sub1", Seq({3, 4})},
                    {"subOut", Seq({2, 3})}, {"head1", I(7)}, {"head0", N()}, {"tail1", Seq({8, 9})}, {"tail0", N()}, {"last1", I(9)}, {"eq1", B(true)}, {"eq2", B(false)},
                    {"same1", B(true)}, {"arrowSize", I(4)}, {"arrowHead", I(5)}});
    }
}

TYPED_TEST(EvaluationTest, NativeScalarFunctions) {
    if constexpr (TypeParam::HasLibrary) {
        Session& session = this->session();
        const std::string model =
            "attribute sum1 = NumericalFunctions::sum((1, 2, 3)); attribute sum0 = NumericalFunctions::sum(null); attribute sumReal = NumericalFunctions::sum((1, 2.5)); "
            "attribute sumRealEmpty = RealFunctions::sum(null); attribute prod = NumericalFunctions::product((2, 3, 4)); attribute prod0 = NumericalFunctions::product(null); "
            "attribute sumOver = NumericalFunctions::sum((9223372036854775807, 1)); "
            "attribute abs1 = NumericalFunctions::abs(-3); attribute abs2 = NumericalFunctions::abs(-2.5); attribute zero = NumericalFunctions::isZero(0); attribute unit = NumericalFunctions::isUnit(1); "
            "attribute max1 = ScalarFunctions::max(3, 7); attribute min1 = ScalarFunctions::min(3, 7); attribute max2 = DataFunctions::max(2.5, 1); attribute maxS = DataFunctions::max(\"a\", \"b\"); "
            "attribute sqrt1 = RealFunctions::sqrt(16); attribute sqrtNeg = RealFunctions::sqrt(-1); attribute floor1 = RealFunctions::floor(2.7); attribute floorNeg = RealFunctions::floor(-2.1); "
            "attribute round1 = RealFunctions::round(2.5); attribute round2 = RealFunctions::round(-2.5); attribute round3 = RealFunctions::round(2.4); "
            "attribute toInt = RealFunctions::ToInteger(-2.9); attribute toIntS = IntegerFunctions::ToInteger(\"42\"); attribute toIntBad = IntegerFunctions::ToInteger(\"x\"); "
            "attribute toNat = IntegerFunctions::ToNatural(5); attribute toNatNeg = IntegerFunctions::ToNatural(-5); attribute toReal = RealFunctions::ToReal(\"2.5\"); "
            "attribute toBool = BooleanFunctions::ToBoolean(\"true\"); attribute toStr = IntegerFunctions::ToString(42); attribute toStrS = StringFunctions::ToString(\"x\"); "
            "attribute gcd1 = RationalFunctions::gcd(12, 18); attribute rat1 = RationalFunctions::rat(1, 4); "
            "attribute sin0 = TrigFunctions::sin(0.0); attribute cos0 = TrigFunctions::cos(0.0); attribute atan1 = TrigFunctions::arctan(0.0); attribute asinBad = TrigFunctions::arcsin(2.0); "
            "attribute len = StringFunctions::Length(\"abc\"); attribute len0 = StringFunctions::Length(\"\"); attribute sub = StringFunctions::Substring(\"abcdef\", 2, 4); "
            "attribute subEmpty = StringFunctions::Substring(\"abc\", 3, 2); attribute subOut = StringFunctions::Substring(\"abc\", 1, 9); attribute cat = StringFunctions::'+'(\"a\", \"b\"); "
            "attribute degrees = TrigFunctions::deg(TrigFunctions::pi); attribute radians = TrigFunctions::rad(180.0);";
        checkModel(session, SourceLanguage::SysML, model,
                   {{"sum1", I(6)}, {"sum0", I(0)}, {"sumReal", R(3.5)}, {"sumRealEmpty", R(0.0)}, {"prod", I(24)}, {"prod0", I(1)}, {"sumOver", N(), "Integer overflow"},
                    {"abs1", I(3)}, {"abs2", R(2.5)}, {"zero", B(true)}, {"unit", B(true)}, {"max1", I(7)}, {"min1", I(3)}, {"max2", R(2.5)}, {"maxS", S("b")},
                    {"sqrt1", R(4.0)}, {"sqrtNeg", N(), "square root of a negative"}, {"floor1", I(2)}, {"floorNeg", I(-3)}, {"round1", I(3)}, {"round2", I(-3)}, {"round3", I(2)},
                    {"toInt", I(-2)}, {"toIntS", I(42)}, {"toIntBad", N(), "is not an Integer"}, {"toNat", I(5)}, {"toNatNeg", N(), "not a Natural"}, {"toReal", R(2.5)},
                    {"toBool", B(true)}, {"toStr", S("42")}, {"toStrS", S("x")}, {"gcd1", I(6)}, {"rat1", R(0.25)}, {"sin0", R(0.0)}, {"cos0", R(1.0)}, {"atan1", R(0.0)},
                    {"asinBad", N(), "outside of [-1, 1]"}, {"len", I(3)}, {"len0", I(0)}, {"sub", S("bcd")}, {"subEmpty", S("")}, {"subOut", N(), "outside of a string"},
                    {"cat", S("ab")}, {"degrees", R(180.0)}, {"radians", R(3.141592653589793)}});
    }
}

TYPED_TEST(EvaluationTest, UserFunctionsCanTakeFunctionValues) {
    Session& session = this->session();
    const std::string model =
        "function apply { in x : ScalarValues::Integer; in expr f { in v : ScalarValues::Integer; return : ScalarValues::Integer; } return : ScalarValues::Integer = f(x); } "
        "function twice { in x : ScalarValues::Integer; in expr f { in v : ScalarValues::Integer; return : ScalarValues::Integer; } return : ScalarValues::Integer = f(f(x)); } "
        "$ a = apply(3, { in v; v * 10 }); $ b = twice(2, { in v; v + 5 }); $ outer = 7; $ c = apply(1, { in v; v + outer });";
    checkModel(session, SourceLanguage::KerML, model, {{"a", I(30)}, {"b", I(12)}, {"c", I(8)}});
}

// Rework of step 6 (the review): function values are lexical closures, every parameter of a frame is bound, a usage's own result wins,
// a nested calculation keeps the calling instance, inherited parameters are redefined by position, a missing argument is an Error.
TYPED_TEST(EvaluationTest, FunctionValuesPassedDownAreLexicalAndEveryParameterIsBound) {
    Session& session = this->session();
    const std::string model =
        "function Ap2 { in n : ScalarValues::Integer; in expr f { in x; return : ScalarValues::Integer; } return : ScalarValues::Integer = if n == 0 ? f(1) else Ap2(n - 1, f); } "
        "feature r = Ap2(1, {in x; x * 5}); "
        "function Pass { in n : ScalarValues::Integer; in expr g { in x; return : ScalarValues::Integer; } return : ScalarValues::Integer = if n == 0 ? g(0) else Pass(n - 1, {in v; g(v) + 1}); } "
        "feature p = Pass(2, {in x; x + 10}); "
        "function Ap { in n : ScalarValues::Integer; in expr f { in x; return : ScalarValues::Integer; } return : ScalarValues::Integer = if n == 0 ? f(100) else Ap(n - 1, {in x; x + n}); } "
        "feature lexical = Ap(2, {in x; x}); "
        "function A4 { in n : ScalarValues::Integer; in acc : ScalarValues::Integer[0..1]; return : ScalarValues::Integer = if n == 0 ? (acc ?? -1) else A4(n - 1); } "
        "feature a4 = A4(1, 42); feature a4b = A4(0, 42); "
        "function A5 { in n : ScalarValues::Integer; in expr f [0..1] { in x; return : ScalarValues::Integer; } return : ScalarValues::Integer = if n == 0 ? 7 else A5(n - 1); } "
        "feature a5 = A5(1, {in x; x});";
    checkModel(session, SourceLanguage::KerML, model, {{"r", I(5)}, {"p", I(12)}, {"lexical", I(101)}, {"a4", I(-1)}, {"a4b", I(42)}, {"a5", I(7)}});
}

TYPED_TEST(EvaluationTest, ACalculationUsageKeepsItsOwnResultAndTheCallingInstance) {
    Session& session = this->session();
    const std::string model =
        "calc def C2 { in x : Integer; return r : Integer = x * 2; } calc c2 : C2 { in :>> x; return :>> r = x * 3; } attribute t2 = c2(2); "
        "part def Car { attribute m : Integer = 3; calc twice { in k : Integer; k * m } attribute r = twice(2); "
        "calc withDefault { in b : Integer = m; b + 1 } attribute d = withDefault(); } "
        "part c : Car { attribute :>> m = 7; } attribute viaChain = c.r; attribute viaDefault = c.d; "
        "calc def M { in p : Car; p.m * 2 } attribute mm = M(c);";
    checkModel(session, SourceLanguage::SysML, model, {{"t2", I(6)}, {"viaChain", I(14)}, {"viaDefault", I(8)}, {"mm", I(14)}});
}

TYPED_TEST(EvaluationTest, ParametersAreRedefinedByPositionAndAMissingArgumentIsAnError) {
    Session& session = this->session();
    const std::string model =
        "function G1 { in a : ScalarValues::Integer; return : ScalarValues::Integer = a * 10; } function G2 specializes G1 { in z : ScalarValues::Integer; } "
        "function G3 specializes G1 { in b : ScalarValues::Integer; return : ScalarValues::Integer = a + b; } "
        "feature g2 = G2(4); feature g3 = G3(1); "
        "function A1 { in x : ScalarValues::Integer; in y : ScalarValues::Integer; return : ScalarValues::Integer = x; } "
        "function A1o { in x : ScalarValues::Integer; in y : ScalarValues::Integer[0..1]; return : ScalarValues::Integer = x; } "
        "function A1d { in x : ScalarValues::Integer; in y : ScalarValues::Integer = 3; return : ScalarValues::Integer = x + y; } "
        "feature miss = A1(10); feature opt = A1o(10); feature dflt = A1d(10);";
    checkModel(session, SourceLanguage::KerML, model,
               {{"g2", I(40)}, {"g3", I(2)}, {"miss", N(), "missing argument for parameter 'y'"}, {"opt", I(10)}, {"dflt", I(13)}});
}

// One rule for the result of every function: the declared result type decides (Real promotes Integers, Integer takes integral Reals).
TYPED_TEST(EvaluationTest, TheDeclaredResultTypeCoercesTheResultOfAFunction) {
    if constexpr (TypeParam::HasLibrary) {
        Session& session = this->session();
        const std::string model =
            "function R1 { in x : ScalarValues::Integer; return : ScalarValues::Real = x + 1; } feature real1 = R1(1); "
            "function I1 { return : ScalarValues::Integer = 1.5; } feature int1 = I1(); function I2 { return : ScalarValues::Integer = 2.0; } feature int2 = I2(); "
            "function B1 { return : ScalarValues::Boolean = 1; } feature bool1 = B1(); function S1 { return : ScalarValues::String = 1; } feature str1 = S1(); "
            "function U1 { return r = 1.5; } feature untyped = U1(); function U2 { return r = 2; } feature untyped2 = U2(); "
            "function MyPlus specializes RealFunctions::'+' { } feature inherited = MyPlus(1, 2); "
            "feature big = IntegerFunctions::ToInteger(1E20);";
        checkModel(session, SourceLanguage::KerML, model,
                   {{"real1", R(2.0)}, {"int1", N(), "is no Integer"}, {"int2", I(2)}, {"bool1", N(), "is no Boolean"}, {"str1", N(), "is no String"}, {"untyped", R(1.5)},
                    {"untyped2", I(2)}, {"inherited", R(3.0)}, {"big", N(), "the value 100000000000000000000.0 is not an Integer"}});
    }
}

// minimize and maximize follow the body in the library: `collection->collect {in x; fn(x)}->reduce min`, so a function that gives several values
// contributes all of them.
TYPED_TEST(EvaluationTest, MinimizeAndMaximizeFlattenTheValuesOfTheFunction) {
    if constexpr (TypeParam::HasLibrary) {
        Session& session = this->session();
        checkModel(session, SourceLanguage::SysML,
                   "attribute lo = (1, 2, 3)->ControlFunctions::minimize {in x; (x * 10, 5 - x)}; attribute hi = (1, 2, 3)->ControlFunctions::maximize {in x; (x * 10, 5 - x)};",
                   {{"lo", I(2)}, {"hi", I(30)}});
    }
}

// A function of a user package that is named like a library package is no library function: its body runs, not the native one.
TYPED_TEST(EvaluationTest, AUserPackageNamedLikeALibraryPackageGetsNoNativeFunctions) {
    Session& session = this->session();
    checkModel(session, SourceLanguage::KerML,
               "package SequenceFunctions { function size { in c; return r = 42; } feature r = size((1, 2)); } feature q = SequenceFunctions::r;",
               {{"q", I(42)}});
}

// A library function that binds a body of its own runs that body: `CollectionFunctions::'#'` is `(col.elements as Anything)#(index)` (`as`
// is not supported yet), it must not get the native result of the `#` of BaseFunctions.
TYPED_TEST(EvaluationTest, ALibraryFunctionWithAnotherBodyRunsTheBodyAndNotTheNativeOfItsGeneral) {
    if constexpr (TypeParam::HasLibrary) {
        Session& session = this->session();
        checkModel(session, SourceLanguage::SysML, "attribute viaBase = BaseFunctions::'#'((10, 20, 30), 2); attribute viaCollection = CollectionFunctions::'#'((10, 20, 30), 2);",
                   {{"viaBase", I(20)}, {"viaCollection", N(), "no native implementation for BaseFunctions::'as'"}});
    }
}

// The parameter list of a specialization is its general's, each parameter replaced by the own one that redefines it.
TYPED_TEST(EvaluationTest, ASpecializationKeepsTheInheritedParametersThatItDoesNotRedefine) {
    Session& session = this->session();
    const std::string model =
        "function H1 { in a; in b; return r = a - b; } function H2 specializes H1 { in :>> b; } function H3 specializes H2 { in :>> a; } "
        "function H4 specializes H1 { in x; in y; feature local :>> a = 1; } "
        "feature h2a = H2(10); feature h2b = H2(10, 3); feature h2c = H2(b = 3, a = 10); feature h3a = H3(10, 3); feature h3b = H3(a = 10, b = 3); feature h4 = H4(5, 2); "
        "function G1 { in a; in b[0..1]; return r = a + (b ?? 0); } function G2 specializes G1 { in z; } feature g2a = G2(4, 5); feature g2b = G2(z = 4); feature g2c = G2(4); "
        "feature g2d = G2(a = 4);";
    checkModel(session, SourceLanguage::KerML, model,
               {{"h2a", N(), "missing argument for parameter 'a'"}, {"h2b", I(-7)}, {"h2c", I(7)}, {"h3a", I(7)}, {"h3b", I(7)}, {"h4", I(3)}, {"g2a", I(9)}, {"g2b", I(4)}, {"g2c", I(4)},
                {"g2d", N(), "unknown parameter 'a'"}});
}

// The positional list is the owned parameters in declaration order, then the inherited ones that no owned parameter redefines.
TYPED_TEST(EvaluationTest, ThePositionalParameterListIsTheOwnedOnesFollowedByTheInheritedOnes) {
    Session& session = this->session();
    const std::string model =
        "function F { in a; in b; in c; return r = a * 100 + b * 10 + c; } "
        "function F3 specializes F { in :>> c; in :>> a; } function F3b specializes F { in :>> c; in :>> a; in q; } function F5 specializes F { in :>> c; in z; } "
        "function R2 specializes F { in p :>> a, b; } "
        "feature f3 = F3(1, 2, 3); feature f3n = F3(a = 1, b = 2, c = 3); feature f3b = F3b(1, 2, 3, 4); feature f5 = F5(1, 2, 3); feature r2 = R2(1, 2); "
        "function GA { in x; return r = x; } function GB { in y; in w; } function GN specializes GA, GB; feature gn = GN(1, 2, 3); feature gnn = GN(w = 3, y = 2, x = 1); "
        "function G specializes DataFunctions::'-' { in a :>> y; in b :>> x; } feature g = G(1, 10);";
    if constexpr (TypeParam::HasLibrary) {
        checkModel(session, SourceLanguage::KerML, model,
                   {{"f3", I(231)}, {"f3n", I(123)}, {"f3b", I(241)}, {"f5", I(321)}, {"r2", I(112)}, {"gn", I(1)}, {"gnn", I(1)}, {"g", I(9)}});
    }
}

TYPED_TEST(EvaluationTest, AUserSpecializationOfANativeWithARedefinedParameterKeepsTheOthers) {
    if constexpr (TypeParam::HasLibrary) {
        Session& session = this->session();
        checkModel(session, SourceLanguage::KerML, "function MyMinus specializes DataFunctions::'-' { in :>> y; } feature m = MyMinus(10, 3);", {{"m", I(-7)}});
    }
}

TYPED_TEST(EvaluationTest, AFunctionValueParameterCanBePassedOnByName) {
    if constexpr (TypeParam::HasLibrary) {
        Session& session = this->session();
        const std::string model =
            "function PassThrough { in expr f { in x : ScalarValues::Integer; return : ScalarValues::Integer; } in xs : ScalarValues::Integer[*]; return : ScalarValues::Integer[*] = xs->ControlFunctions::collect f; } "
            "feature r = PassThrough({in x; x * 2}, (1, 2, 3));";
        checkModel(session, SourceLanguage::KerML, model, {{"r", Seq({2, 4, 6})}});
    }
}

// The prototype stands for a feature of upper bound 1 only; a larger multiplicity without subsetters is empty (with a Warning if instances are required).
TYPED_TEST(EvaluationTest, AFeatureOfALargerMultiplicityWithoutValuesIsEmpty) {
    if constexpr (TypeParam::HasLibrary) {
        Session& session = this->session();
        const std::string model =
            "part def Comp { attribute mass : Real = 1.0; part subs : Comp[0..*]; attribute total : Real = mass + subs.total->NumericalFunctions::sum(); } "
            "part rl : Comp { part :>> subs; } part rl2 : Comp { part :>> subs : Comp; } attribute t1 = rl.total; attribute t2 = rl2.total; "
            "part def Wheel { attribute mass : Real = 10.0; } part def Car { part wheels : Wheel[4]; attribute tm = wheels.mass->NumericalFunctions::sum(); attribute n = wheels->SequenceFunctions::size(); } "
            "part car : Car; part car4 : Car { part w1 :> wheels; part w2 :> wheels; part w3 :> wheels; part w4 :> wheels; } "
            "attribute n0 = car.n; attribute tm0 = car.tm; attribute n4 = car4.n; attribute tm4 = car4.tm; "
            "part def Node { attribute v = 1; part child : Node[0..1]; } part nd : Node; attribute c1 = nd.child.v; attribute c2 = nd.child.child;";
        checkModel(session, SourceLanguage::SysML, model, {{"t1", R(1.0)}, {"t2", R(1.0)}, {"n0", I(0)}, {"tm0", I(0)}, {"n4", I(4)}, {"tm4", R(40.0)}, {"c1", I(1)}, {"c2", N()}});
        const Result warned = Evaluator().evaluateFeatureValue(session.feature("n0"));
        ASSERT_EQ(warned.diagnostics.size(), 1u);
        EXPECT_EQ(warned.diagnostics.front().severity, Severity::Warning);
        EXPECT_NE(warned.diagnostics.front().message.find("requires at least 4"), std::string::npos);
        EXPECT_TRUE(warned.ok());
        EXPECT_TRUE(Evaluator().evaluateFeatureValue(session.feature("n4")).diagnostics.empty());
    }
}

// More than 256 subsetters: the intermediate ones are still not counted twice.
TYPED_TEST(EvaluationTest, TheLeavesOfManySubsettersCountOnce) {
    if constexpr (TypeParam::HasLibrary) {
        Session& session = this->session();
        std::string model = "part def Comp; part def Many { part ps : Comp[0..*]; part mid :> ps; part x :> mid; ";
        for (int index = 0; index < 300; ++index) model += "part s" + std::to_string(index) + " :> ps; ";
        model += "attribute n = ps->SequenceFunctions::size(); } part many : Many; attribute total = many.n;";
        checkModel(session, SourceLanguage::SysML, model, {{"total", I(301)}});
    }
}

// A function value is passed on to a parameter that is not declared as a function, and on again.
TYPED_TEST(EvaluationTest, AFunctionValueIsForwardedThroughAnUntypedParameter) {
    if constexpr (TypeParam::HasLibrary) {
        Session& session = this->session();
        checkModel(session, SourceLanguage::SysML,
                   "calc def A1 { in xs[0..*]; in f[0..*]; ControlFunctions::collect(xs, f) } calc def A2 { in ys[0..*]; in g[0..*]; A1(ys, g) } "
                   "attribute r = A1((1, 2, 3), {in x; x * 2}); attribute r2 = A2((1, 2), {in x; x + 10});",
                   {{"r", Seq({2, 4, 6})}, {"r2", Seq({11, 12})}});
    }
}

// The values of the subsetters count once: transitively, by element, at package level; a default value does not stop them, a bound one does.
TYPED_TEST(EvaluationTest, SubsettersCountOnceAndAreFoundInPackagesAndDefaultsDoNotStopThem) {
    if constexpr (TypeParam::HasLibrary) {
        Session& session = this->session();
        const std::string model =
            "part def Comp { attribute mass : Real = 1.0; } "
            "part def Veh { part parts : Comp[0..*]; attribute total = parts.mass->NumericalFunctions::sum(); part d1 :> parts { :>> mass = 10.0; } } "
            "part v2 : Veh { part x :> a2; part a2 :> parts { :>> mass = 5.0; } } attribute vt = v2.total; "
            "part def PS { part ps : Comp[0..*]; part e1 :> ps; part e2 :> ps; part frst :> ps = ps#(1); attribute n = ps->SequenceFunctions::size(); } part p : PS; attribute pn = p.n; "
            "attribute masses : Real[*]; attribute m1 :> masses = 2.0; attribute m2 :> masses = 3.0; attribute msum = masses->NumericalFunctions::sum(); "
            "part def DD { part cx : Comp { :>> mass = 7.0; } part ps : Comp[0..*] default cx; part e :> ps; part ps2 : Comp[0..*] = cx; part e2 :> ps2; "
            "attribute dm = ps.mass->NumericalFunctions::sum(); attribute bm = ps2.mass->NumericalFunctions::sum(); } part dd : DD; attribute dmr = dd.dm; attribute bmr = dd.bm;";
        checkModel(session, SourceLanguage::SysML, model, {{"vt", R(15.0)}, {"pn", I(2)}, {"msum", R(5.0)}, {"dmr", R(1.0)}, {"bmr", R(7.0)}});
    }
}

// A value-less structural feature that nothing subsets is the prototypical element, whatever its multiplicity, except where that recurses.
TYPED_TEST(EvaluationTest, APrototypeIsAnElementExceptWhereItRecurses) {
    Session& session = this->session();
    const std::string model =
        "part def Wheel { attribute mass = 10.0; } part def Car2 { part spare : Wheel[0..1]; part eng : Wheel; part any : Wheel[1..*]; part plain : Wheel; } part car2 : Car2; "
        "attribute spareMass = car2.spare.mass; attribute engOk = car2.eng != null; attribute anyMass = car2.any.mass; attribute plainMass = car2.plain.mass; "
        "part def Comp { attribute mass; part subs : Comp[0..*]; attribute total = mass + subs.total->NumericalFunctions::sum(); } "
        "part leaf : Comp { :>> mass = 4.0; } part tree : Comp { :>> mass = 1.0; part l :> subs { :>> mass = 2.0; part ll :> subs { :>> mass = 4.0; } } part r :> subs { :>> mass = 8.0; } } "
        "attribute leafTotal = leaf.total; attribute treeTotal = tree.total; "
        "part def Self { part inner : Self; attribute depth = 1.0 + inner.depth; } part sf : Self; attribute selfDepth = sf.depth; "
        "part def MA { part b : MB; attribute n = 1; attribute depth = n + b.depth; } part def MB { part a : MA; attribute depth = a.depth; } part ma : MA; attribute mutual = ma.depth;";
    if constexpr (TypeParam::HasLibrary) {
        checkModel(session, SourceLanguage::SysML, model,
                   {{"spareMass", R(10.0)}, {"engOk", B(true)}, {"anyMass", N()}, {"plainMass", R(10.0)}, {"leafTotal", R(4.0)}, {"treeTotal", R(15.0)}, {"selfDepth", N()}, {"mutual", N()}});
    }
}

// A value-less feature of an instance is the sequence of the features of the instance that subset it.
TYPED_TEST(EvaluationTest, AValueLessFeatureIsTheSequenceOfTheFeaturesThatSubsetIt) {
    if constexpr (TypeParam::HasLibrary) {
        Session& session = this->session();
        const std::string model =
            "part def Comp { attribute mass : Real = 1.0; } "
            "part def Veh { part parts : Comp[0..*]; attribute total = parts.mass->NumericalFunctions::sum(); attribute n = parts->SequenceFunctions::size(); attribute viaCollect = parts->ControlFunctions::collect{in p; p.mass}->NumericalFunctions::sum(); } "
            "part v : Veh { part a :> parts { :>> mass = 2.0; } part b :> parts { :>> mass = 3.0; } } part empty : Veh; "
            "part def Node { attribute mass : Real = 0.0; part subs : Node[0..*]; attribute total : Real = mass + subs.total->NumericalFunctions::sum(); } "
            "part tree : Node { :>> mass = 1.0; part l :> subs { :>> mass = 2.0; part ll :> subs { :>> mass = 4.0; } } part r :> subs { :>> mass = 8.0; } } "
            "attribute vt = v.total; attribute vn = v.n; attribute vc = v.viaCollect; attribute et = empty.total; attribute tt = tree.total; "
            "part def Loop { part inner : Loop[0..*]; attribute depth : Real = 1.0 + inner.depth->NumericalFunctions::sum(); } part lp : Loop { part me :> inner; } attribute lt = lp.depth; "
            "part def Self { part inner : Self; attribute depth : Real = 1.0 + inner.depth; } part sf : Self; attribute st = sf.depth;";
        checkModel(session, SourceLanguage::SysML, model, {{"vt", R(5.0)}, {"vn", I(2)}, {"vc", R(5.0)}, {"et", I(0)}, {"tt", R(15.0)}, {"lt", R(2.0)}, {"st", N()}});
    }
}

TEST(EvaluationXmiRoundTrip, TheFeaturesThatSubsetAValueLessFeatureEvaluateLikeTheTextAfterTheRoundTrip) {
    checkRoundTrip(SourceLanguage::SysML,
                   "package P { part def Comp { attribute mass = 1.0; } "
                   "part def Veh { part parts : Comp[0..*]; attribute total = (parts.mass)#(1) + (parts.mass)#(2); } "
                   "part v : Veh { part a :> parts { :>> mass = 2.0; } part b :> parts { :>> mass = 3.0; } } "
                   "part def Node { attribute mass = 0.0; part subs : Node[0..*]; "
                   "attribute total = mass + ((subs.total)#(1) ?? 0.0) + ((subs.total)#(2) ?? 0.0); } "
                   "part tree : Node { :>> mass = 1.0; part l :> subs { :>> mass = 2.0; part ll :> subs { :>> mass = 4.0; } } part r :> subs { :>> mass = 8.0; } } "
                   "attribute vt = v.total; attribute tt = tree.total; }",
                   {{"vt", R(5.0)}, {"tt", R(15.0)}});
}

// Text -> XmiWriter -> read back: the functions, calls and body expressions must evaluate to what the text gives.
TEST(EvaluationXmiRoundTrip, FunctionsAndBodyExpressionsOfAWrittenModelEvaluateLikeTheText) {
    const std::string model =
        "package P { function fact { in n; return r = if n <= 1 ? 1 else n * fact(n - 1); } "
        "function apply { in x; in expr f { in v; return r; } return r = f(x); } "
        "function scaled { in x; in k default 3; x * k } "
        "feature a = fact(6); feature b = apply(4, { in v; v * v }); feature c = scaled(5); feature e = fact(3) + scaled(1); }";
    const std::filesystem::path directory = std::filesystem::temp_directory_path() / ("sysmlv2-evaluation-functions-" + std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    std::filesystem::create_directories(directory);
    Workspace text;
    text.addText(model, "m.kerml", SourceLanguage::KerML, 1);
    text.resolve();
    ASSERT_TRUE(text.errors().empty());
    const std::string file = (directory / "m.kermlx").string();
    const auto writeErrors = text.writeXmi(0, file);
    ASSERT_TRUE(writeErrors.empty()) << writeErrors.front()->description();
    Workspace read;
    read.addFile(file, 1);
    read.resolve();
    const std::vector<std::pair<const char*, Value>> expected = {{"a", I(720)}, {"b", I(16)}, {"c", I(15)}, {"e", I(9)}};
    for (const auto& [name, value] : expected) {
        SCOPED_TRACE(name);
        const auto fromText = Evaluator().evaluateFeatureValue(std::dynamic_pointer_cast<KerML::Entities::Feature>(text.find(std::string("P::") + name)));
        const auto fromXmi = Evaluator().evaluateFeatureValue(std::dynamic_pointer_cast<KerML::Entities::Feature>(read.find(std::string("P::") + name)));
        EXPECT_EQ(fromText.value, value);
        EXPECT_EQ(fromXmi.value, value) << (fromXmi.diagnostics.empty() ? "" : fromXmi.diagnostics.front().message);
        EXPECT_TRUE(fromXmi.diagnostics.empty());
    }
    std::filesystem::remove_all(directory);
}

#if defined(__unix__) || defined(__APPLE__)
#include <pthread.h>
namespace {
    struct RecursionJob {
        Session* session = nullptr;
        const char* name = "deep";
        SysMLv2::Evaluation::EvaluationOptions options;
        Result result;
    };

    void* recurseOnSmallStack(void* argument) {
        auto* job = static_cast<RecursionJob*>(argument);
        job->result = Evaluator(SysMLv2::Evaluation::FunctionRegistry::withStandardFunctions(), job->options).evaluateFeatureValue(job->session->feature(job->name));
        return nullptr;
    }
}

// Recursion of a user function at the default depth limit must not overflow a 1 MB stack (a Windows main thread): the limit is reported once.
TEST(EvaluationFunctions, TheDefaultDepthLimitOfARecursiveFunctionFitsAOneMegabyteThreadStack) {
    Session session(nullptr);
    session.load(SourceLanguage::KerML, "function count { in n : ScalarValues::Integer; return : ScalarValues::Integer = if n == 0 ? 0 else count(n - 1) + 1; } $ deep = count(100000);");
    ASSERT_EQ(session.syntaxErrors(), 0u);
    RecursionJob job;
    job.session = &session;
    pthread_attr_t attributes;
    ASSERT_EQ(pthread_attr_init(&attributes), 0);
    ASSERT_EQ(pthread_attr_setstacksize(&attributes, 1024 * 1024), 0);
    pthread_t thread;
    ASSERT_EQ(pthread_create(&thread, &attributes, recurseOnSmallStack, &job), 0);
    ASSERT_EQ(pthread_join(thread, nullptr), 0);
    pthread_attr_destroy(&attributes);
    EXPECT_TRUE(job.result.value.isNull());
    ASSERT_EQ(job.result.diagnostics.size(), 1u);
    EXPECT_NE(job.result.diagnostics.front().message.find("maximum call depth"), std::string::npos);
}
namespace {
    Result runOnOneMegabyte(Session& session, const char* name, const SysMLv2::Evaluation::EvaluationOptions& options, std::size_t stack = 1024 * 1024) {
        RecursionJob job;
        job.session = &session;
        job.name = name;
        job.options = options;
        pthread_attr_t attributes;
        EXPECT_EQ(pthread_attr_init(&attributes), 0);
        EXPECT_EQ(pthread_attr_setstacksize(&attributes, stack), 0);
        pthread_t thread;
        EXPECT_EQ(pthread_create(&thread, &attributes, recurseOnSmallStack, &job), 0);
        EXPECT_EQ(pthread_join(thread, nullptr), 0);
        pthread_attr_destroy(&attributes);
        return job.result;
    }
}

// The outcome does not depend on the stack of the caller (with the default stackSize): the same values and the same Error text.
TEST(EvaluationFunctions, TheResultOfADeepEvaluationDoesNotDependOnTheStackOfTheCaller) {
    Session session(nullptr);
    session.load(SourceLanguage::KerML,
                 "function count { in n : ScalarValues::Integer; return : ScalarValues::Integer = if n == 0 ? 0 else count(n - 1) + 1; } $ ok = count(3000); $ tooDeep = count(100000);");
    SysMLv2::Evaluation::EvaluationOptions options;
    std::string message;
    for (const std::size_t stack : {std::size_t(256) << 10, std::size_t(1) << 20, std::size_t(8) << 20, std::size_t(64) << 20}) {
        SCOPED_TRACE(stack);
        const Result ok = runOnOneMegabyte(session, "ok", options, stack);
        EXPECT_EQ(ok.value, I(3000));
        EXPECT_TRUE(ok.diagnostics.empty());
        const Result tooDeep = runOnOneMegabyte(session, "tooDeep", options, stack);
        ASSERT_EQ(tooDeep.diagnostics.size(), 1u);
        EXPECT_TRUE(tooDeep.value.isNull());
        if (message.empty()) message = tooDeep.diagnostics.front().message;
        EXPECT_EQ(tooDeep.diagnostics.front().message, message);
    }
    EXPECT_NE(message.find("maximum call depth of "), std::string::npos);
}

// The call depth: an evaluation starts on the stack of the caller (here 1 MB) with limits that follow what is left of it; if it reaches
// one, it runs again on a thread with a large stack (EvaluationOptions::stackSize, 64 MB), where about 6400 calls fit. With stackSize 0
// the limit of the small stack stays: a clean Error.
TEST(EvaluationFunctions, ADeepRecursionRunsOnALargeStackAndWithoutOneItFailsCleanlyOnASmallOne) {
    Session session(nullptr);
    session.load(SourceLanguage::KerML,
                 "function count { in n : ScalarValues::Integer; return : ScalarValues::Integer = if n == 0 ? 0 else count(n - 1) + 1; } "
                 "function sum { in n : ScalarValues::Integer; in xs : ScalarValues::Integer[*]; return : ScalarValues::Integer = if n == 0 ? 0 else xs#(n) + sum(n - 1, xs); } "
                 "$ small = count(50); $ deep = count(2000); $ tooDeep = count(100000); $ total = sum(2000, 1..2000); $ nested = count(1500) + (1 + (1 + (1 + (1 + (1 + (1 + (1 + (1 + 1))))))));");
    ASSERT_EQ(session.syntaxErrors(), 0u);
    SysMLv2::Evaluation::EvaluationOptions options;
    EXPECT_EQ(runOnOneMegabyte(session, "small", options).value, I(50));
    const Result deep = runOnOneMegabyte(session, "deep", options);
    EXPECT_EQ(deep.value, I(2000));
    EXPECT_TRUE(deep.diagnostics.empty());
    EXPECT_EQ(runOnOneMegabyte(session, "nested", options).value, I(1509));
    EXPECT_EQ(runOnOneMegabyte(session, "total", options).value, I(2001000));
    const Result tooDeep = runOnOneMegabyte(session, "tooDeep", options);
    EXPECT_TRUE(tooDeep.value.isNull());
    ASSERT_EQ(tooDeep.diagnostics.size(), 1u);
    EXPECT_NE(tooDeep.diagnostics.front().message.find("maximum call depth"), std::string::npos);
    // without a large stack: the limit of the 1 MB of the caller (about 85 calls), reported once
    options.stackSize = 0;
    EXPECT_EQ(runOnOneMegabyte(session, "small", options).value, I(50));
    const Result inlineDeep = runOnOneMegabyte(session, "deep", options);
    EXPECT_TRUE(inlineDeep.value.isNull());
    ASSERT_EQ(inlineDeep.diagnostics.size(), 1u);
    EXPECT_NE(inlineDeep.diagnostics.front().message.find("maximum call depth"), std::string::npos);
    // an explicit limit lowers the one of the stack
    options = {};
    options.maxCallDepth = 10;
    const Result limited = runOnOneMegabyte(session, "small", options);
    ASSERT_EQ(limited.diagnostics.size(), 1u);
    EXPECT_NE(limited.diagnostics.front().message.find("maximum call depth of 10"), std::string::npos);
}
#endif
