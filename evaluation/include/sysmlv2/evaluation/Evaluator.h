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
        /// The maximum nesting of calls of user functions, calculations and function values, see EvaluationContext::enterCall(). 0 (the
        /// default): what the stack that the evaluation runs on allows, with a safety factor of 2 on the measured 5.2 KB per call
        /// (unoptimized): about 6400 calls on the default stack of 64 MB, about 85 on a 1 MB stack. A value above that is lowered to it.
        std::size_t maxCallDepth = 0;
        /// The stack of the thread that an evaluation runs on when the stack of the caller is not enough, in bytes (if the system refuses
        /// it, half of it, down to 4 MB). An evaluation starts on the thread of the caller, with limits that follow what is left of
        /// its stack, and only if it reaches the depth limit or the call depth limit it is repeated on such a thread (evaluations have
        /// no side effects, and the results of the first run are dropped). That costs nothing for the evaluation that fits. 0: never
        /// switch; the limits stay those of the stack of the caller. No thread is made in WebAssembly, which has one stack.
        std::size_t stackSize = std::size_t(64) << 20;
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
     * body of its own (it runs that, see the user-defined functions below) or redefines the parameters of its general in another order
     * (the native implementation gets the arguments in the order of the general's parameters).
     * Named arguments (`F(y = 1, x = 2)`) bind to the parameters of the function by name; see the user-defined functions below.
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
     * User-defined functions and calculations (since step 6). An invocation (`F(a, b)`, `x->F(a)`, a calculation usage `g(a)` through the
     * function that types it) binds its arguments to the input parameters of the callee: the parameters it owns, else those of the nearest
     * general (so `in a :>> y` parameters of a specialization and the inherited ones of a function without own parameters work).
     * Arguments are positional or named (`F(y = 1, x = 2)`; the arrow form can name them too, the left operand is the first positional
     * argument); positional ones fill the parameters that are not named, in order. An unknown or twice given name and too many arguments
     * are Errors; a parameter without an argument has its default value (a FeatureValue of the parameter or of a parameter it
     * redefines, evaluated in the callee's frame, after the parameters before it are bound), else it is empty if its multiplicity is
     * written with a lower bound of 0, and an Error ("missing argument for parameter 'y'") otherwise: the default multiplicity of a
     * parameter is 1..1. Every parameter of a frame is bound (an absent one to the empty sequence), so what an outer frame bound
     * for the same parameter (a recursive call that omits an optional argument) is never seen. A parameter of a specialization that
     * has no explicit redefinition stands for the parameter of its general at the same position (`function G2 specializes G1 { in z; }`
     * binds G1's `a` to z); the ones beyond the general's are additional. The positional parameter list of a function is its OWNED input parameters in declaration order, followed by the
     * inherited ones that no owned parameter redefines, in each general's list order (generals in declaration order, a parameter
     * that comes through two generals counts once). An owned parameter redefines what it names (`in :>> b, c`, through chains) or,
     * if it names nothing, the parameter at its index among the owned input parameters (all of them counted) in every general that
     * has one; if an owned parameter that names it redefines that already, it redefines nothing and is an additional parameter. So
     * `H2 specializes H1 { in :>> b; }` is called H2(b, a), `F5 specializes F { in :>> c; in z; }` is F5(c, z, a) (z redefines b).
     * Named arguments use the effective names of the list. This is the reading of the KerML specification (the library has no case that
     * would discriminate: its specializations redefine all parameters in the same order, `IntegerFunctions::max`); it is not confirmed
     * by data of the pilot implementation.
     * A call through a feature chain (`c.twice(5)`, when the model records the chain as the invoked type) runs the last feature at
     * every instance that the prefix leads to; parsed text does not record the prefix of such a call yet. The result is the result expression of the function (`{ in x; x + 1 }`, `calc def
     * { ... a * 2 }`) or the value of its result parameter (`return : T = expr;`, `out :>> result = expr;`), evaluated in a frame where the
     * parameters are bound; features that the function owns (`attribute tmp = a * 2;`) can be used in the result. The arguments are
     * evaluated where the call is written, so a recursive call with other arguments is no cycle of definitions; recursion is bounded
     * by the call depth limit (EvaluationOptions::maxCallDepth, one Error); the depth limit of the expressions (maxDepth) is for the nesting of expressions inside the calls. A function that specializes a function with a native implementation runs its own body, or the
     * body of the nearest general between it and the native one, if it has one, unless that body is a `default` value of a library
     * function that the native implementation mirrors (ComplexFunctions::sum, ...): a library function that binds another body
     * (`CollectionFunctions::'#'`, `VectorFunctions::'cartesian+'`, ...) runs it; the native implementation of a function is used only
     * for the function of the Kernel Function Library (a user package named like a library package gets none); without a body the inherited native implementation gets the arguments in the order of the
     * parameters of the general. The result of a function, native or user, is coerced by its declared result type (also an inherited one): Real or
     * Rational promotes Integers to Reals (`RealFunctions::'+'(1, 2)` is 3.0, the operator `1 + 2` is decided by its operands), Integer
     * or Natural takes an integral Real as an Integer and refuses another one (Error), Boolean and String refuse another kind (Error);
     * untyped results and other types stay as they are. A calculation usage runs its own result (`return :>> r = x * 3`) before the
     * result of the calculation that types it, and a calculation or function that is owned by a type (a `calc` of a `part def`)
     * runs at the instance that calls it: its frame continues the path of the caller, so `m` in its body is the `m` of that instance.
     * A frame does not see the target of its caller.
     *
     * Value-less features that are subsetted. The value of a value-less feature in an instance is the sequence of the features of the
     * instance that subset it (directly or through subsetting and redefinition chains; a feature that only redefines it is the
     * effective feature, not a subsetter; a subsetter whose own value is being evaluated is left out), in declaration order, the
     * instance's own first: `part parts : Comp[0..*]` with `part a :> parts` and `part b :> parts` is `(a, b)`, also as the target of a
     * chain (`parts.mass`). A value-less structural feature that nothing subsets is the prototypical element (itself) ONLY if its effective
     * multiplicity has the upper bound 1 (`[1]`, `[0..1]`, or none written anywhere along its redefinitions: the nearest written one
     * wins); a larger upper bound (`[4]`, `[0..*]`, `[1..*]`) makes it EMPTY, with one Warning per feature and evaluation if the
     * lower bound is at least 1 ("the values of 'X' are not given; it is evaluated as empty although its multiplicity requires at
     * least N"; the result stays ok). Recursion of prototypes (`part child : Node[0..1]`, `part inner : Self`) is cut by one
     * guard: the first prototype level exists, the path that leads to a feature that it has already passed through as a prototype
     * (or a feature that redefines it or that it redefines) makes it empty; a feature of a package is never a prototype in this sense
     * (a reference that leads back to it is a cycle). An attribute without a value is null. A `default` value does not stop the subsetters,
     * a bound one does. The subsetters of a feature of a package are the features of that package. A subsetter that another
     * subsetter subsets is left out (the leaves of the subsetting forest count), an element that several subsetters have counts
     * once, and a subsetter whose value depends on the collection and adds an element to it is a cyclic definition (Error). A feature that is subsetted several
     * times (multiplicity above 1) counts once.
     *
     * Function values (body expressions `{ in x; x > 1 }`, function references such as `min` in `reduce min`, parameters that are
     * declared `in expr f`) are evaluated lazily: the body is called with the values of its arguments by the functions that take it
     * (`select`, `collect`, `reject`, `forAll`, `exists`, `reduce`, `selectOne`, `minimize`, `maximize`, the operators `.?` and `.{ }`,
     * and user functions that call their parameter `f(x)`); `that` is the first argument. A body sees the features and the context
     * instance of the place where it is written, and the parameters of the call frame where it is written (lexical capture): a body
     * that is passed down (`Ap(n - 1, {in x; x + n})`) still sees the `n` of the call that created it, and a function value that a
     * function passes on unchanged (`Ap2(n - 1, f)`) is the one it was given.
     *
     * Native functions (everything else is evaluated through the body of the library function if it has one): BaseFunctions `== != === !==
     * , # ToString`; DataFunctions `+ - * / % ** ^ < > <= >= not xor | & .. min max`; ControlFunctions `if and or implies ?? collect select
     * selectOne reject forAll exists reduce allTrue anyTrue minimize maximize`; SequenceFunctions `# size isEmpty notEmpty equals same
     * includes includesOnly excludes union intersection including includingAt excluding excludingAt subsequence head tail last`
     * (native because the library bodies recurse over `size` and `tail`, which is quadratic and exceeds the depth limit for a few hundred
     * items; they have the semantics of the bodies, null is the empty sequence); NumericalFunctions `sum product abs isZero isUnit`
     * (and IntegerFunctions / RationalFunctions / RealFunctions `sum product`); RealFunctions `sqrt floor round ToInteger ToReal
     * ToRational`; IntegerFunctions `ToInteger ToNatural`; NaturalFunctions `ToNatural`; RationalFunctions `gcd rat ToInteger
     * ToRational`; BooleanFunctions `ToBoolean`; TrigFunctions `sin cos arcsin arccos arctan` and the constant `pi` (`tan cot deg rad`
     * and `NumericalFunctions::sum0 product1` run through their library bodies); StringFunctions `Length Substring`. Not implemented:
     * the classification operators (`istype hastype @ @@ as meta all`), `[` and units (step 7), `~`, `numer`/`denom` (a Rational is a
     * double), and the functions of OccurrenceFunctions, CollectionFunctions, VectorFunctions and ComplexFunctions that have no body.
     *
     * Known limits: the typings of features are not checked (`attribute n : Natural = 0 - 5;` is -5; only the declared result type
     * of a function is applied).
     *
     * Not supported yet (an Error "not supported yet: <metaclass>" and a null value, never an exception): metadata access, constructors,
     * constraint and calculation usages evaluated as values, invocations of other metaclasses than InvocationExpression (trigger
     * invocations, ...), body expressions that are not used as function values.
     *
     * Contract of every evaluate call:
     *  - no exception leaves the call; an unexpected exception is turned into an Error diagnostic, and if even that cannot be
     *    recorded the Result has failed == true (not ok, null value);
     *  - a null expression or feature, and a moved-from Evaluator, give an Error;
     *  - the diagnostics name the expression where the problem occurred (Diagnostic::element);
     *  - the value is null whenever an Error was reported; a Warning keeps the value;
     *  - the depth limit and the call depth limit are reported once per evaluation.
     *
     * Stack. With a stackSize the limits are those of that stack whatever the caller has (the outcome and the Error text do not depend on
     * the caller's stack); with stackSize 0 they follow what is left of the caller's stack (caller-dependent). An evaluation runs on the thread of the caller with limits that follow what is left of its stack (about 1.3 KB per level
     * of expression and 5.2 KB per call unoptimized, safety factor 2; EvaluationOptions::maxDepth / maxCallDepth only lower them). If it
     * reaches a limit and a larger stack allows more, it runs again (no side effects) on a thread with EvaluationOptions::stackSize
     * (64 MB; about 6400 calls). Evaluations that fit pay nothing (about 13 us for a trivial expression, with or without this).
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
