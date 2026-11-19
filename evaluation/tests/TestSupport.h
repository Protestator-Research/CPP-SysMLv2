#pragma once

#include <kerml/kernel/packages/LibraryPackage.h>
#include <set>

// Helpers of the tests: a harness that evaluates the arguments of a native function through a tiny hook (literals and registered
// stand-in expressions only, no parser).

#include <sysmlv2/evaluation/EvaluationContext.h>
#include <sysmlv2/evaluation/FunctionRegistry.h>
#include <sysmlv2/evaluation/Value.h>

#include <kerml/kernel/expressions/LiteralBoolean.h>
#include <kerml/kernel/expressions/LiteralInfinity.h>
#include <kerml/kernel/expressions/LiteralInteger.h>
#include <kerml/kernel/expressions/LiteralRational.h>
#include <kerml/kernel/expressions/LiteralString.h>
#include <kerml/kernel/expressions/NullExpression.h>
#include <kerml/core/classifiers/Subclassification.h>
#include <kerml/kernel/functions/Function.h>
#include <kerml/kernel/packages/Package.h>
#include <kerml/root/namespaces/Namespace.h>

#include <gtest/gtest.h>

#include <cstdint>
#include <initializer_list>
#include <limits>
#include <ostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace SysMLv2::Evaluation {
    // (for the messages of gtest)
    inline std::ostream& operator<<(std::ostream& out, const Value& value) { return out << value.toString(); }
}

namespace TestSupport {
    using namespace SysMLv2::Evaluation;
    using KerML::Entities::Expression;
    using ExpressionPtr = std::shared_ptr<Expression>;

    inline Value B(bool value) { return Value::boolean(value); }
    inline Value I(std::int64_t value) { return Value::integer(value); }
    inline Value R(double value) { return Value::real(value); }
    inline Value S(const std::string& value) { return Value::string(value); }
    inline Value N() { return Value::null(); }
    inline Value Inf() { return Value::infinity(); }
    inline Value Seq(std::initializer_list<std::int64_t> integers) {
        std::vector<Item> items;
        for (const std::int64_t integer : integers) items.emplace_back(std::in_place_type<std::int64_t>, integer);
        return Value(std::move(items));
    }

    constexpr std::int64_t Max = std::numeric_limits<std::int64_t>::max();
    constexpr std::int64_t Min = std::numeric_limits<std::int64_t>::min();

    /// Evaluates stand-in expressions (registered with stand()) to a given value and the literal classes to their value; logs every
    /// expression that was evaluated.
    class Harness {
    public:
        Harness() : Registry(FunctionRegistry::withStandardFunctions()) {
            Context.setExpressionEvaluator([this](const ExpressionPtr& expression, EvaluationContext&) {
                Evaluated.push_back(expression.get());
                return literal(expression);
            });
        }

        /// A stand-in expression that evaluates to @p value.
        ExpressionPtr stand(const Value& value) {
            auto expression = std::make_shared<Expression>();
            Stands[expression.get()] = value;
            Keep.push_back(expression);
            return expression;
        }

        bool wasEvaluated(const ExpressionPtr& expression) const {
            for (const Expression* evaluated : Evaluated) {
                if (evaluated == expression.get()) return true;
            }
            return false;
        }

        /// Calls the function registered under @p name with expressions standing for @p arguments.
        Value call(const std::string& name, const std::vector<Value>& arguments) {
            std::vector<ExpressionPtr> expressions;
            for (const Value& argument : arguments) expressions.push_back(stand(argument));
            return callExpressions(name, expressions);
        }

        Value callExpressions(const std::string& name, const std::vector<ExpressionPtr>& expressions) {
            const NativeFunction* function = Registry.find(name);
            if (function == nullptr) {
                ADD_FAILURE() << "no function registered: " << name;
                return Value();
            }
            return (*function)(Context, expressions);
        }

        FunctionRegistry Registry;
        EvaluationContext Context;
        std::vector<const Expression*> Evaluated;

    private:
        Value literal(const ExpressionPtr& expression) {
            if (const auto stand = Stands.find(expression.get()); stand != Stands.end()) return stand->second;
            if (const auto boolean = std::dynamic_pointer_cast<KerML::Entities::LiteralBoolean>(expression)) return Value::boolean(boolean->value());
            if (const auto integer = std::dynamic_pointer_cast<KerML::Entities::LiteralInteger>(expression)) return Value::integer(integer->value());
            if (const auto real = std::dynamic_pointer_cast<KerML::Entities::LiteralRational>(expression)) return Value::real(real->value());
            if (const auto text = std::dynamic_pointer_cast<KerML::Entities::LiteralString>(expression)) return Value::string(text->value());
            if (std::dynamic_pointer_cast<KerML::Entities::LiteralInfinity>(expression)) return Value::infinity();
            return Value();   // (NullExpression and everything else)
        }

        std::map<const Expression*, Value> Stands;
        std::vector<ExpressionPtr> Keep;
    };

    inline std::shared_ptr<KerML::Entities::LiteralBoolean> literalBoolean(bool value) {
        auto literal = std::make_shared<KerML::Entities::LiteralBoolean>();
        literal->setValue(value);
        return literal;
    }

    inline std::shared_ptr<KerML::Entities::LiteralInteger> literalInteger(std::int64_t value) {
        auto literal = std::make_shared<KerML::Entities::LiteralInteger>();
        literal->setValue(value);
        return literal;
    }

    // Hand-built models -------------------------------------------------------------------------------------------------------

    /// The root namespace of a source: a Namespace without owner and name.
    inline std::shared_ptr<KerML::Entities::Namespace> makeRoot() { return std::make_shared<KerML::Entities::Namespace>(); }

    inline std::shared_ptr<KerML::Entities::Package> makePackage(const std::string& name, const std::shared_ptr<KerML::Entities::Element>& owner) {
        // (the packages of the Kernel Function Library are library packages, a package of the same name of a user is not)
        static const std::set<std::string> kernel = {"BaseFunctions",    "BooleanFunctions", "CollectionFunctions", "ComplexFunctions",   "ControlFunctions",
                                                     "DataFunctions",    "IntegerFunctions", "NaturalFunctions",    "NumericalFunctions", "OccurrenceFunctions",
                                                     "RationalFunctions", "RealFunctions",    "ScalarFunctions",     "SequenceFunctions",  "StringFunctions",
                                                     "TrigFunctions",    "VectorFunctions"};
        std::shared_ptr<KerML::Entities::Package> package = kernel.count(name) != 0 ? std::make_shared<KerML::Entities::LibraryPackage>() : std::make_shared<KerML::Entities::Package>();
        package->setDeclaredName(name);
        if (const auto library = std::dynamic_pointer_cast<KerML::Entities::LibraryPackage>(package)) library->setIsStandard(true);
        package->setOwner(owner);
        return package;
    }

    inline std::shared_ptr<KerML::Entities::Function> makeFunction(const std::string& name, const std::shared_ptr<KerML::Entities::Element>& owner) {
        auto function = std::make_shared<KerML::Entities::Function>();
        function->setDeclaredName(name);
        function->setOwner(owner);
        return function;
    }

    /// `specific :> general` as the parser builds it: a Subclassification in the owned specializations of the specific function.
    inline void specialize(const std::shared_ptr<KerML::Entities::Function>& specific, const std::shared_ptr<KerML::Entities::Function>& general) {
        auto subclassification = std::make_shared<KerML::Entities::Subclassification>(general, specific);
        specific->appendOwnedSubclassification(subclassification);
        specific->appendOwnedSpecialization(subclassification);
    }

    /// Breaks the reference cycles of hand-built functions (their specializations point back to them), so that the model is freed.
    inline void disposeAll(const std::vector<std::shared_ptr<KerML::Entities::Function>>& functions) {
        for (const auto& function : functions) {
            for (const auto& specialization : function->ownedSpecialization()) {
                if (specialization) KerML::Entities::disposeLinks(*specialization);
            }
            KerML::Entities::disposeLinks(*function);
        }
    }

    inline bool hasError(const std::vector<Diagnostic>& diagnostics, const std::string& fragment) {
        for (const Diagnostic& diagnostic : diagnostics) {
            if (diagnostic.severity == Severity::Error && diagnostic.message.find(fragment) != std::string::npos) return true;
        }
        return false;
    }

    /// One row of a table of function calls: the result and either no diagnostic (@c error empty) or an Error containing @c error.
    struct Case {
        std::string function;
        std::vector<Value> arguments;
        Value expected;
        std::string error;   // fragment of the expected Error message, empty if the call must not report anything
        std::size_t maxSequenceLength = 0;   // 0: the default
    };

    /// The qualified name of a library function in the registry: `D("+")` is `DataFunctions::'+'`.
    inline std::string qualified(const char* package, const std::string& name) { return std::string(package) + "::'" + name + "'"; }
    inline std::string D(const std::string& name) { return qualified("DataFunctions", name); }
    inline std::string BF(const std::string& name) { return qualified("BaseFunctions", name); }
    inline std::string CF(const std::string& name) { return qualified("ControlFunctions", name); }

    inline std::string describe(const Case& test) {
        std::string text = test.function + "(";
        for (std::size_t index = 0; index < test.arguments.size(); ++index) text += (index ? ", " : "") + test.arguments[index].toString();
        return text + ")";
    }

    /// Runs every row of the table on a fresh harness.
    inline void runCases(const std::vector<Case>& cases) {
        for (const Case& test : cases) {
            SCOPED_TRACE(describe(test));
            Harness harness;
            if (test.maxSequenceLength != 0) harness.Context.setMaxSequenceLength(test.maxSequenceLength);
            const Value actual = harness.call(test.function, test.arguments);
            EXPECT_EQ(actual, test.expected);
            const auto& diagnostics = harness.Context.diagnostics();
            if (test.error.empty()) {
                EXPECT_TRUE(diagnostics.empty()) << (diagnostics.empty() ? "" : diagnostics.front().message);
            } else {
                EXPECT_TRUE(hasError(diagnostics, test.error)) << "expected an Error containing '" << test.error << "', got "
                                                               << (diagnostics.empty() ? "nothing" : diagnostics.front().message);
                EXPECT_TRUE(harness.Context.hasErrors());
                if (test.expected != N()) ADD_FAILURE() << "an error case must expect null";
                EXPECT_TRUE(actual.isNull());
            }
        }
    }
}
