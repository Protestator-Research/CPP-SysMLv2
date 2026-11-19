#pragma once

#include <sysmlv2/evaluation/Diagnostic.h>
#include <sysmlv2/evaluation/Value.h>

#include <kerml/kernel/functions/Expression.h>

#include <cstddef>
#include <functional>
#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace SysMLv2::Evaluation {

    /**
     * The state of one evaluation: the diagnostics, the recursion depth and the limits. The native functions receive it to evaluate their
     * arguments (evaluate()) and to report problems (report()). It is not thread safe; use one context per evaluation.
     *
     * It also carries the target (the featuring context of the expressions that are evaluated, enterTarget()) and the bindings of features
     * to values (bind()). The cycle guard of the feature values lives in the Evaluator.
     */
    class SYSMLV2EVALUATION_EXPORT EvaluationContext {
    public:
        /// Evaluates one expression in the given context. The Evaluator installs itself as the hook.
        using ExpressionEvaluator = std::function<Value(const std::shared_ptr<KerML::Entities::Expression>&, EvaluationContext&)>;

        /// Calls a function value (a body expression `{ in x; x + 1 }`, a function reference such as `min`, a parameter that holds one) with
        /// the given argument values. The Evaluator installs itself as the invoker.
        using FunctionInvoker = std::function<Value(const std::shared_ptr<KerML::Entities::Expression>& function, std::vector<Value> arguments, EvaluationContext&)>;

        /// Default limit of the recursion depth (see enterScope()). Every level costs native stack. Measured with the Evaluator: about
        /// 470 to 580 bytes per level in an optimized build (GCC and clang) and 1.4 to 1.9 KB in an unoptimized one (GCC -O0, clang
        /// -O0), so 256 levels need at most about 0.5 MB; a test runs the default depth on a 1 MB thread stack with GCC -O0 (about
        /// twice the stack that it needs). MSVC and Emscripten were not measured: MSVC Debug frames are expected to be larger, and the
        /// Emscripten default stack (64 KB) is much smaller, so such callers should lower the limit. Callers that know they have a large
        /// stack may raise it (EvaluationOptions::maxDepth, setMaxDepth()); the 1000 of earlier versions overflowed 1 MB when unoptimized.
        static constexpr std::size_t DefaultMaxDepth = 256;
        /// Default limit of the nesting of calls of user functions, calculations and function values (see enterCall()). Measured with a
        /// recursive user function (`if n == 0 ? 0 else f(n - 1) + 1`) in an unoptimized build (GCC -O0): about 5.2 KB of native stack
        /// per call (the call and the 4 levels of expression that it costs), so 100 calls need about 0.5 MB and the 256 calls that would
        /// match the default depth do not fit a 1 MB stack. An optimized build needs about a third of that.
        static constexpr std::size_t DefaultMaxCallDepth = 100;
        /// Levels of depth that a call is credited with: the limit of the depth is maxDepth() plus this for every call that is running, so
        /// that maxDepth() is the nesting of expressions inside the calls and a call (which costs a few levels itself) counts once.
        static constexpr std::size_t DepthPerCall = 3;
        /// Default limit of the length of a generated sequence (the range `..`).
        static constexpr std::size_t DefaultMaxSequenceLength = 1'000'000;

        EvaluationContext() = default;

        /// RAII guard of one level of recursion, see enterScope().
        class SYSMLV2EVALUATION_EXPORT DepthGuard {
        public:
            DepthGuard(const DepthGuard&) = delete;
            DepthGuard& operator=(const DepthGuard&) = delete;
            DepthGuard(DepthGuard&& other) noexcept;
            DepthGuard& operator=(DepthGuard&&) = delete;
            ~DepthGuard();

            /// False if the depth limit was exceeded (an Error has been reported and the level was not entered).
            [[nodiscard]] explicit operator bool() const { return Entered; }

        private:
            friend class EvaluationContext;
            DepthGuard(EvaluationContext* context, bool entered) : Context(context), Entered(entered) {}
            EvaluationContext* Context;
            bool Entered;
        };

        /// RAII guard of one nested call, see enterCall().
        class SYSMLV2EVALUATION_EXPORT CallGuard {
        public:
            CallGuard(const CallGuard&) = delete;
            CallGuard& operator=(const CallGuard&) = delete;
            CallGuard(CallGuard&& other) noexcept;
            CallGuard& operator=(CallGuard&&) = delete;
            ~CallGuard();

            /// False if the call depth limit was exceeded (an Error has been reported and the call was not entered).
            [[nodiscard]] explicit operator bool() const { return Entered; }

        private:
            friend class EvaluationContext;
            CallGuard(EvaluationContext* context, bool entered) : Context(context), Entered(entered) {}
            EvaluationContext* Context;
            bool Entered;
        };

        /// RAII scope of one "current element", see enterElement().
        class SYSMLV2EVALUATION_EXPORT ElementScope {
        public:
            ElementScope(const ElementScope&) = delete;
            ElementScope& operator=(const ElementScope&) = delete;
            ElementScope(ElementScope&& other) noexcept : Context(other.Context) { other.Context = nullptr; }
            ElementScope& operator=(ElementScope&&) = delete;
            ~ElementScope();

        private:
            friend class EvaluationContext;
            explicit ElementScope(EvaluationContext* context) : Context(context) {}
            EvaluationContext* Context;
        };

        /// RAII scope of one "target" (the featuring context), see enterTarget().
        class SYSMLV2EVALUATION_EXPORT TargetScope {
        public:
            TargetScope(const TargetScope&) = delete;
            TargetScope& operator=(const TargetScope&) = delete;
            TargetScope(TargetScope&& other) noexcept : Context(other.Context) { other.Context = nullptr; }
            TargetScope& operator=(TargetScope&&) = delete;
            ~TargetScope();

        private:
            friend class EvaluationContext;
            explicit TargetScope(EvaluationContext* context) : Context(context) {}
            EvaluationContext* Context;
        };

        /// RAII scope of one binding of a feature to a value, see bind().
        class SYSMLV2EVALUATION_EXPORT BindingScope {
        public:
            BindingScope(const BindingScope&) = delete;
            BindingScope& operator=(const BindingScope&) = delete;
            BindingScope(BindingScope&& other) noexcept : Context(other.Context) { other.Context = nullptr; }
            BindingScope& operator=(BindingScope&&) = delete;
            ~BindingScope();

        private:
            friend class EvaluationContext;
            explicit BindingScope(EvaluationContext* context) : Context(context) {}
            EvaluationContext* Context;
        };

        /**
         * Makes @p target the featuring context until the returned scope ends (scopes nest; the innermost wins; null is "no context"):
         * the instance (a usage or definition of the model) whose features the references of the expressions that are evaluated meanwhile
         * are looked up in. `self` is the target.
         */
        [[nodiscard]] TargetScope enterTarget(std::shared_ptr<KerML::Entities::Element> target);
        /// The current target, null if there is none.
        [[nodiscard]] const std::shared_ptr<KerML::Entities::Element>& target() const;

        /**
         * Binds @p feature to @p value until the returned scope ends (scopes nest; the innermost binding of a feature wins). A reference
         * to a bound feature has the bound value (the mechanism for `that` and, in later versions, for the parameters of an invoked
         * function). The feature is identified by its address; the context keeps it alive.
         */
        [[nodiscard]] BindingScope bind(std::shared_ptr<KerML::Entities::Feature> feature, Value value);
        /// The innermost binding of the feature, nullptr if it is not bound.
        [[nodiscard]] const Value* binding(const KerML::Entities::Feature* feature) const;

        /**
         * Adds a diagnostic. Without an explicit @p element the diagnostic is located at the innermost current element (see
         * enterElement(); evaluate() makes the expression it evaluates the current element), if there is one.
         */
        void report(Severity severity, std::string message, std::shared_ptr<KerML::Entities::Element> element = nullptr);

        /// Makes @p element the current element until the returned scope ends (scopes nest; the innermost wins).
        [[nodiscard]] ElementScope enterElement(std::shared_ptr<KerML::Entities::Element> element);
        [[nodiscard]] const std::vector<Diagnostic>& diagnostics() const;
        /// Moves the collected diagnostics out and clears them.
        [[nodiscard]] std::vector<Diagnostic> takeDiagnostics();
        /// True if an Error has been reported or the evaluation failed (see markFailed()).
        [[nodiscard]] bool hasErrors() const;
        /// Marks the evaluation as failed without recording a diagnostic (for the case that no diagnostic can be recorded, for example
        /// when memory is exhausted). Sticky; report() sets it itself if it cannot store a diagnostic.
        void markFailed() noexcept { Failed = true; }
        [[nodiscard]] bool failed() const noexcept { return Failed; }

        /// Installs the invoker that invokeFunctionValue() calls (an empty function removes it).
        void setFunctionInvoker(FunctionInvoker invoker);
        /**
         * Calls the function value that the expression @p function stands for (an argument of a native function such as the body of
         * `select`) with the given arguments, inside one level of recursion. Reports an Error and returns null if no invoker is installed,
         * the expression is null or is no function value, or the depth limit is exceeded.
         */
        [[nodiscard]] Value invokeFunctionValue(const std::shared_ptr<KerML::Entities::Expression>& function, std::vector<Value> arguments);

        /// Installs the hook that evaluate() calls (an empty function removes it). It is safe to replace the hook from inside a running
        /// hook or native function: the call in progress keeps the hook it started with.
        void setExpressionEvaluator(ExpressionEvaluator evaluator);
        /**
         * Evaluates an expression through the hook, inside one level of recursion. Reports an Error and returns null if no hook is
         * installed, the expression is null or the depth limit is exceeded.
         */
        [[nodiscard]] Value evaluate(const std::shared_ptr<KerML::Entities::Expression>& expression);

        /// Enters one level of recursion. If the limit is exceeded an Error is reported and the guard converts to false.
        [[nodiscard]] DepthGuard enterScope();
        [[nodiscard]] std::size_t depth() const;
        void setMaxDepth(std::size_t maxDepth);
        [[nodiscard]] std::size_t maxDepth() const;

        /// Enters one nested call of a user function, calculation or function value. Beyond maxCallDepth() an Error is reported (once)
        /// and the guard converts to false. Every running call also raises the limit of the depth of expressions by DepthPerCall.
        [[nodiscard]] CallGuard enterCall();
        void setMaxCallDepth(std::size_t maxCallDepth);
        [[nodiscard]] std::size_t maxCallDepth() const;
        /// True if the depth limit or the call depth limit was exceeded in this evaluation.
        [[nodiscard]] bool limitReached() const { return DepthReported; }
        /// Which limit was exceeded: the depth of the expressions, the depth of the calls.
        [[nodiscard]] bool depthLimitHit() const { return DepthHit; }
        [[nodiscard]] bool callLimitHit() const { return CallHit; }

        /// The longest sequence that generated sequences (the range `..`) may have; 0 rejects every generated sequence.
        void setMaxSequenceLength(std::size_t maxLength);
        [[nodiscard]] std::size_t maxSequenceLength() const;

    private:
        std::vector<Diagnostic> Diagnostics;
        std::shared_ptr<const ExpressionEvaluator> Evaluator;
        std::shared_ptr<const FunctionInvoker> Invoker;
        std::vector<std::shared_ptr<KerML::Entities::Element>> CurrentElements;
        std::vector<std::shared_ptr<KerML::Entities::Element>> Targets;
        std::vector<std::pair<std::shared_ptr<KerML::Entities::Feature>, Value>> Bindings;
        std::size_t Depth = 0;
        std::size_t CallDepth = 0;
        bool DepthHit = false;
        bool CallHit = false;
        std::size_t MaxCallDepth = DefaultMaxCallDepth;
        bool Failed = false;
        bool DepthReported = false;   // (the depth limit is reported once per evaluation, not once per operand)
        std::size_t MaxDepth = DefaultMaxDepth;
        std::size_t MaxSequenceLength = DefaultMaxSequenceLength;
    };
}
