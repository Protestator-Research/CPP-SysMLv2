#pragma once

#include <sysmlv2/evaluation/Diagnostic.h>
#include <sysmlv2/evaluation/EvaluationContext.h>
#include <sysmlv2/evaluation/FunctionRegistry.h>

#include <kerml/core/features/Feature.h>
#include <kerml/kernel/functions/Expression.h>

#include <cstddef>
#include <memory>

namespace SysMLv2::Evaluation {

    /// The limits of one evaluation.
    struct EvaluationOptions {
        /// The maximum nesting of expressions (every nested expression is one level), see EvaluationContext::setMaxDepth(). Mind the native
        /// stack that a level costs (EvaluationContext::DefaultMaxDepth).
        std::size_t maxDepth = EvaluationContext::DefaultMaxDepth;
        /// The longest sequence that a range `a..b` may generate, see EvaluationContext::setMaxSequenceLength().
        std::size_t maxSequenceLength = EvaluationContext::DefaultMaxSequenceLength;
    };

    /**
     * Evaluates expressions without model context: literals, `null`, operator expressions (`1 + 2`, `a and b`, `if c ? x else y`, ...)
     * and invocations of functions that have a native implementation in the FunctionRegistry (`DataFunctions::'+'(1, 2)`,
     * `x->F(y)`). All of them run the same way: the library function an expression invokes is looked up in the registry (the
     * function itself first, then its generals). The function is Expression::function() (set by Workspace::resolve()), else the
     * instantiated type if it is a Function, else the function that the expression names through a non-owning Membership (how the
     * XMI import stores it). An operator expression that has no function falls back to the function that
     * KerML::operatorFunctionName() names for its operator, so models of a workspace without the standard library, or loaded from
     * XMI or older JSON, evaluate as well.
     *
     * The arguments are `InstantiationExpression::argument()`; if that is empty (XMI import) they are the owned input parameters of
     * the pilot implementation's XMI (the value expressions of their FeatureValues; a parameter without a value is an Error) or, for
     * XMI written by XmiWriter, the expressions that are owned directly through plain FeatureMemberships, in ownership order.
     *
     * A function that specializes a library function with a native implementation uses it (`IntegerFunctions::'-'`), unless it has a
     * body of its own or redefines the parameters of its general in another order; such a function is refused with a "not supported
     * yet" Error (the body evaluation comes with step 6) instead of silently running the general's implementation.
     * Named arguments (`F(y = 1, x = 2)`) are put in the order of the parameters of the function if every argument is named,
     * the names are those of distinct parameters of the function and together they are its first parameters; otherwise (and for
     * the arrow form) the call is refused ("named arguments not supported yet").
     *
     * Feature references and chains (since step 5). The model has no instances; the "instance" that features are looked up in, the
     * target, is an element of the model, a usage or definition (`part p : P`). The value of a feature in a target is the value of its
     * effective binding there. The candidates are the feature, everything it redefines (a value-less redefinition has the value of
     * what it redefines) and every feature among the features of the target and of its generals (typings, subclassifications,
     * subsettings, redefinitions, nearest first) that redefines one of them. A candidate is more specific if it redefines the other or
     * is owned by a type that specializes the other's owner; the most specific one that binds a value wins, and two unrelated ones that
     * both bind a value are an Error ("ambiguous", the diamond; without values a diamond is no problem). A `default` value is used only
     * if no candidate binds a value that is not a default; a `:=` initial value is a bound value. KerML allows only default values to
     * be overridden, so a bound value that overrides another bound value is kept but reported as one Warning. A feature without a value
     * is the element it denotes if it is a part, action, enumeration literal ... (see evaluateFeatureValue()), else the empty
     * sequence (null) without a diagnostic; this refines the rule "no value is the empty sequence" so that `part alias = e1;` can be
     * navigated. A reference to a feature of an enclosing type is looked up in the nearest instance that has the feature.
     * Without a target the entry points use the type that features the feature (see evaluate()), which is then also `self`. The target is one element: nested instances (the usage `e` of the
     * definition of `c` in `c.e.x`) are only known when they are reached through a chain; then they carry the instance they were
     * reached through, and references in their values to features of an enclosing definition find the enclosing instance `c`, so
     * that redefinitions in `c` apply.
     *
     * A chain `a.b.c` evaluates the left operand to targets (the elements that its value has, or, for a feature without a value, the
     * feature that is effective in the target; a sequence `(p, q)` stands for both) and then every link in each target in turn,
     * element-wise, appending the values (flattened, within maxSequenceLength). A link that the parser could not resolve (the type of
     * the left operand was unknown, or the left operand is computed) is looked up by its name among the features of the target; that lookup is lost in a
     * round trip through XmiWriter's XMI, because the pilot's shape cannot carry a name without a feature (the chain has no target feature in the model then). `self` is the target (an element value); `that` and any feature that the caller binds with EvaluationContext::bind()
     * have their bound value. A feature that is being evaluated for the same target again is a cycle: one Error naming it.
     *
     * Models: parsed text records the referent and the chain target; the pilot implementation's XMI records them as plain Memberships
     * (a chain `a.b.c` there is one expression whose target is the chain `b.c`) and wraps lazily evaluated operands in references
     * that own the expression. XMI written by XmiWriter records both in the same way (a plain Membership whose member is the feature) for every
     * referent and target the parser resolved; only an unresolved one (see above) is not written and gives the Error "no referent / no target feature in the model".
     *
     * Not supported yet (an Error "not supported yet: <metaclass>" and a null value, never an exception): select / collect / index
     * expressions, metadata access, constructors, constraint and calculation usages, invocations of other metaclasses than
     * InvocationExpression (trigger invocations, ...), body expressions. Functions that only have a body give "no native
     * implementation".
     *
     * Contract of every evaluate call:
     *  - no exception leaves the call; an unexpected exception is turned into an Error diagnostic, and if even that cannot be
     *    recorded the Result has failed == true (not ok, null value);
     *  - a null expression or feature, and a moved-from Evaluator, give an Error;
     *  - the diagnostics name the expression where the problem occurred (Diagnostic::element);
     *  - the value is null whenever an Error was reported; a Warning keeps the value;
     *  - the depth limit is reported once per evaluation.
     *
     * Thread safety: evaluate calls are const and keep no state between calls (the lookup cache of the registry is local to one call),
     * so they may run from several threads at once as long as the model is not modified and setRegistry() is not running.
     * Re-entrancy: a call holds its own shared copy of the registry, so a native function may call setRegistry() or assign to the
     * Evaluator while it runs (the running call keeps the registry it started with).
     *
     * An Evaluator is movable, not copyable; use the moved-from object only to assign to it or to destroy it (its evaluate calls
     * report an Error).
     */
    class SYSMLV2EVALUATION_EXPORT Evaluator {
    public:
        explicit Evaluator(FunctionRegistry registry = FunctionRegistry::withStandardFunctions(), EvaluationOptions options = {});
        ~Evaluator();
        Evaluator(const Evaluator&) = delete;
        Evaluator& operator=(const Evaluator&) = delete;
        Evaluator(Evaluator&& other) noexcept;
        Evaluator& operator=(Evaluator&& other) noexcept;

        /**
         * Evaluates an expression.
         * @param target the instance, a usage or definition of the model, whose features the references of the expression are looked up in
         *        (see the class description; it is one element: nested instances are only known when they are reached through a chain, so
         *        an explicit target that is a nested usage, such as `C::e` for `C::e::x`, sees the definition's own features and not those
         *        of an instance of `C`). Without a target the context is the type that features the feature the expression belongs to
         *        (the owner of the nearest feature that is owned by a type, no Expression); it stands for any instance of the type, so
         *        `self` is that type. An expression of a feature of a package has no context and no `self`.
         */
        [[nodiscard]] Result evaluate(const std::shared_ptr<KerML::Entities::Expression>& expression,
                                      const std::shared_ptr<KerML::Entities::Element>& target = nullptr) const;

        /**
         * Evaluates the value of a feature in a target: the value of its effective binding there, which can be a redefinition in a
         * specialization or in the target itself, or the inherited value of a redefinition that has none (`attribute x = 1 + 2;`). Default
         * values (`default =`) and initial values (`:=`) follow the rules of the class description. A feature without a value is the
         * element it denotes if it is a part, action, enumeration literal ... (see below), else null and no diagnostic. A feature without
         * a FeatureValue that is itself an Expression (a `constraint x { ... }` or `calc x { ... }` usage) is evaluated as that expression.
         * An explicit target that is none of the feature's featuring types (nor of the lexical owners of the target) is an Error; the
         * same default context and the same one-element target as for evaluate() apply.
         *
         * Which value-less features are elements: an enumeration literal (metaclass EnumerationUsage), a usage of any other kind than an
         * attribute or reference usage (part, item, action, port, connection, state, ...; typed or untyped), and any feature typed by a
         * Class and by no DataType. The metaclass is read from Element::getType(), so the module needs no sysml. A plain attribute and an
         * untyped feature are null, so two unbound attributes are equal (null == null).
         * @param target as for evaluate().
         */
        [[nodiscard]] Result evaluateFeatureValue(const std::shared_ptr<KerML::Entities::Feature>& feature,
                                                  const std::shared_ptr<KerML::Entities::Element>& target = nullptr) const;

        /// The registry in use. The reference is valid until the next setRegistry().
        [[nodiscard]] const FunctionRegistry& registry() const;
        /// Replaces the registry (also the way to add functions: copy registry(), register, set).
        void setRegistry(FunctionRegistry registry);
        [[nodiscard]] const EvaluationOptions& options() const;

    private:
        struct Impl;
        std::unique_ptr<Impl> Data;
    };
}
