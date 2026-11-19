#pragma once

// Private: the parameters, bodies and arguments of functions, calculations and body expressions, independent of how an evaluation
// runs them. Works on the model shapes of parsed text, of the pilot's XMI and of XmiWriter (see Arguments.cpp).

#include <kerml/core/features/Feature.h>
#include <kerml/core/types/Type.h>
#include <kerml/kernel/functions/Expression.h>

#include <functional>
#include <memory>
#include <optional>
#include <string>
#include <vector>

namespace SysMLv2::Evaluation {

    using TypePtr = std::shared_ptr<KerML::Entities::Type>;
    using FeaturePtr = std::shared_ptr<KerML::Entities::Feature>;
    using ExpressionPtr = std::shared_ptr<KerML::Entities::Expression>;

    /// The name of a feature for matching: the effective name (a parameter `in :>> x` is known by the feature it redefines), else the
    /// declared name; empty if there is none.
    std::string nameOf(const FeaturePtr& feature);

    /// The input parameters that a type owns itself, in order (owned through a FeatureMembership; direction in or inout).
    std::vector<FeaturePtr> ownInputParameters(const KerML::Entities::Type& type);

    /// The positional parameter list of a type: its OWNED input parameters in declaration order, followed by the inherited ones that no
    /// owned parameter redefines, in each general's list order, the generals in declaration order (a parameter that comes through two
    /// generals counts once). An owned parameter redefines what it names (`in :>> b`, several targets allowed, through redefinition
    /// chains) or, if it names nothing, the parameter at its INDEX among the owned input parameters (counting all of them) in each
    /// general that has one; if that parameter is named by another owned parameter's redefinition, it redefines nothing and is an
    /// additional parameter. So `H2 specializes H1 { in :>> b; }` is called H2(b, a), and `G2 specializes G1 { in z; }` is
    /// G2(z, <G1's second>). Named arguments use the effective names of this list.
    std::vector<FeaturePtr> inputParameters(const TypePtr& type);
    std::vector<FeaturePtr> parametersOf(const TypePtr& type, int level);

    /// The lower bound of the multiplicity of a feature if it is written down as literal bounds (`[1]`, `[1..*]`, `[0..1]`), else 0.
    std::size_t lowerBoundOf(const FeaturePtr& feature);

    /// The bounds of a written multiplicity (literals): `[n]` is n..n, `[*]` is 0..*, `[a..b]`; no upper bound is infinite.
    struct WrittenBounds {
        std::size_t lower = 0;
        std::optional<std::size_t> upper;
    };
    std::optional<WrittenBounds> writtenBoundsOf(const FeaturePtr& feature);

    /// The multiplicity of a feature as the nearest one written along its redefinitions says, 1..1 if none is.
    WrittenBounds effectiveBoundsOf(const FeaturePtr& feature);

    /// The lower bound that is written down for a feature, if any.
    std::optional<std::size_t> writtenLowerBoundOf(const FeaturePtr& feature);

    /// True if a call must give an argument for the parameter: the lower bound of its multiplicity (written on it or on a parameter it
    /// redefines) is at least 1, and the default multiplicity of a parameter without a written one is 1..1. Whether the parameter has
    /// a default value is for the caller to decide.
    bool isRequiredParameter(const FeaturePtr& parameter);

    /// The result of a type that has one of its own: a result expression (`{ in x; x + 1 }`, `calc def { ... a * 2 }`) or a result
    /// parameter / output feature with a value (`return : T = a * 2;`, `out :>> result = a * 2;`). Both null: no result of its own.
    struct OwnResult {
        ExpressionPtr Expression;     // ResultExpressionMembership
        FeaturePtr Parameter;         // result parameter with a value
        ExpressionPtr ParameterValue; // its value expression
        explicit operator bool() const { return Expression != nullptr || ParameterValue != nullptr; }
        ExpressionPtr value() const { return Expression ? Expression : ParameterValue; }
    };
    OwnResult ownResultOf(const KerML::Entities::Type& type);

    /// A function with a body: the nearest of the type and its generals (breadth first) that has a result of its own. @p stopAt is
    /// called for the generals (not for the type itself) and ends the search along a branch (a holder of a native implementation).
    struct BodyOwner {
        TypePtr Owner;
        OwnResult Result;
    };
    BodyOwner findBodyOwner(const TypePtr& type, const std::function<bool(const KerML::Entities::Type&)>& stopAt = {});

    /// True if the type belongs to the Kernel Function Library: it is owned by one of the packages below
    /// resources/sysml.library/KerML/Function (BaseFunctions ... VectorFunctions) and that package is a library package (metaclass
    /// LibraryPackage), which a user package of the same name is not.
    /// True for the name of one of the packages of the Kernel Function Library (BaseFunctions ... VectorFunctions).
    bool isKernelPackageName(const std::string& name);

    bool isKernelLibraryType(const KerML::Entities::Type& type);

    /// One argument of a call: its value expression, and the parameter it is named after (empty: positional).
    struct ArgumentRef {
        ExpressionPtr Value;
        std::string Name;
    };

    /// Classifies the arguments of an invocation: positional, or named (a parameter feature that redefines the named parameter; for
    /// the arrow form a plain Expression that carries the name). @p arrow: the first argument is the left operand and positional.
    std::vector<ArgumentRef> argumentRefs(const std::vector<ExpressionPtr>& arguments, bool arrow);

    /// The arguments by parameter: named ones at their parameter, the others in order into the free parameters. @c Error is set for an
    /// unknown or twice given name and for too many arguments; missing arguments stay null.
    struct BoundArguments {
        std::vector<ExpressionPtr> ByParameter;
        std::string Error;
    };
    BoundArguments bindArguments(const std::vector<FeaturePtr>& parameters, const std::vector<ArgumentRef>& arguments);

    /// The features that a parameter stands for in bodies: itself and everything it redefines (a general's body refers to its own
    /// parameter, which the parameter of a specialization redefines).
    std::vector<FeaturePtr> parameterAliases(const FeaturePtr& parameter);

    /// The body expression (plain Expression with parameters and a result) that an argument expression stands for: the expression
    /// itself, or the one that the pilot's XMI wraps in a reference. Null if the argument is no body expression.
    ExpressionPtr bodyExpressionOf(const ExpressionPtr& argument);
}
