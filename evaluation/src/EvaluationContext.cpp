#include <sysmlv2/evaluation/EvaluationContext.h>

#include "CompilerSupport.h"

#include <utility>

namespace SysMLv2::Evaluation {

    namespace {
        // (kept out of EvaluationContext::evaluate / enterScope, whose frames are on the recursion path)
        SYSMLV2_COLD_PATH Value reportUnusable(EvaluationContext& context, const std::shared_ptr<KerML::Entities::Expression>& expression, bool noHook) {
            if (!expression) {
                context.report(Severity::Error, "Cannot evaluate a missing expression.");
            } else if (noHook) {
                context.report(Severity::Error, "No expression evaluator is installed in the evaluation context.", expression);
            }
            return Value();
        }

        SYSMLV2_COLD_PATH void reportDepthExceeded(EvaluationContext& context, std::size_t maxDepth) {
            context.report(Severity::Error, "The maximum evaluation depth of " + std::to_string(maxDepth) + " is exceeded.");
        }

        SYSMLV2_COLD_PATH void reportCallDepthExceeded(EvaluationContext& context, std::size_t maxCallDepth) {
            context.report(Severity::Error, "The maximum call depth of " + std::to_string(maxCallDepth) + " is exceeded.");
        }
    }

    EvaluationContext::DepthGuard::DepthGuard(DepthGuard&& other) noexcept : Context(other.Context), Entered(other.Entered) {
        other.Entered = false;
    }

    EvaluationContext::DepthGuard::~DepthGuard() {
        if (Entered && Context != nullptr) --Context->Depth;
    }

    EvaluationContext::CallGuard::CallGuard(CallGuard&& other) noexcept : Context(other.Context), Entered(other.Entered) {
        other.Entered = false;
    }

    EvaluationContext::CallGuard::~CallGuard() {
        if (Entered && Context != nullptr) --Context->CallDepth;
    }

    EvaluationContext::ElementScope::~ElementScope() {
        if (Context != nullptr) Context->CurrentElements.pop_back();
    }

    EvaluationContext::TargetScope::~TargetScope() {
        if (Context != nullptr) Context->Targets.pop_back();
    }

    EvaluationContext::BindingScope::~BindingScope() {
        if (Context != nullptr) Context->Bindings.pop_back();
    }

    EvaluationContext::TargetScope EvaluationContext::enterTarget(std::shared_ptr<KerML::Entities::Element> target) {
        Targets.push_back(std::move(target));
        return TargetScope(this);
    }

    const std::shared_ptr<KerML::Entities::Element>& EvaluationContext::target() const {
        static const std::shared_ptr<KerML::Entities::Element> none;
        return Targets.empty() ? none : Targets.back();
    }

    EvaluationContext::BindingScope EvaluationContext::bind(std::shared_ptr<KerML::Entities::Feature> feature, Value value) {
        Bindings.emplace_back(std::move(feature), std::move(value));
        return BindingScope(this);
    }

    const Value* EvaluationContext::binding(const KerML::Entities::Feature* feature) const {
        for (auto it = Bindings.rbegin(); it != Bindings.rend(); ++it) {
            if (it->first.get() == feature) return &it->second;
        }
        return nullptr;
    }

    EvaluationContext::ElementScope EvaluationContext::enterElement(std::shared_ptr<KerML::Entities::Element> element) {
        CurrentElements.push_back(std::move(element));
        return ElementScope(this);
    }

    void EvaluationContext::report(Severity severity, std::string message, std::shared_ptr<KerML::Entities::Element> element) {
        if (!element && !CurrentElements.empty()) element = CurrentElements.back();
        try {
            Diagnostics.push_back(Diagnostic{severity, std::move(message), std::move(element)});
        } catch (...) {
            Failed = true;   // (out of memory: the diagnostic is lost, but the evaluation must not look successful)
        }
    }

    const std::vector<Diagnostic>& EvaluationContext::diagnostics() const { return Diagnostics; }

    std::vector<Diagnostic> EvaluationContext::takeDiagnostics() {
        std::vector<Diagnostic> result = std::move(Diagnostics);
        Diagnostics.clear();
        return result;
    }

    bool EvaluationContext::hasErrors() const {
        if (Failed) return true;
        for (const Diagnostic& diagnostic : Diagnostics) {
            if (diagnostic.severity == Severity::Error) return true;
        }
        return false;
    }

    void EvaluationContext::setExpressionEvaluator(ExpressionEvaluator evaluator) {
        Evaluator = evaluator ? std::make_shared<const ExpressionEvaluator>(std::move(evaluator)) : nullptr;
    }

    void EvaluationContext::setFunctionInvoker(FunctionInvoker invoker) {
        Invoker = invoker ? std::make_shared<const FunctionInvoker>(std::move(invoker)) : nullptr;
    }

    Value EvaluationContext::invokeFunctionValue(const std::shared_ptr<KerML::Entities::Expression>& function, std::vector<Value> arguments) {
        if (!function || !Invoker) return reportUnusable(*this, function, !Invoker);
        const DepthGuard guard = enterScope();
        if (!guard) return Value();
        const ElementScope scope = enterElement(function);
        const std::shared_ptr<const FunctionInvoker> running = Invoker;
        return (*running)(function, std::move(arguments), *this);
    }

    Value EvaluationContext::evaluate(const std::shared_ptr<KerML::Entities::Expression>& expression) {
        if (!expression || !Evaluator) return reportUnusable(*this, expression, !Evaluator);
        const DepthGuard guard = enterScope();
        if (!guard) return Value();
        const ElementScope scope = enterElement(expression);
        // (a local copy: the hook may replace the installed one while it runs)
        const std::shared_ptr<const ExpressionEvaluator> running = Evaluator;
        return (*running)(expression, *this);
    }

    EvaluationContext::DepthGuard EvaluationContext::enterScope() {
        if (Depth >= MaxDepth + DepthPerCall * CallDepth) {
            DepthHit = true;
            if (!DepthReported) {
                DepthReported = true;
                reportDepthExceeded(*this, MaxDepth + DepthPerCall * CallDepth);
            }
            return DepthGuard(this, false);
        }
        ++Depth;
        return DepthGuard(this, true);
    }

    EvaluationContext::CallGuard EvaluationContext::enterCall() {
        if (CallDepth >= MaxCallDepth) {
            CallHit = true;
            if (!DepthReported) {
                DepthReported = true;
                reportCallDepthExceeded(*this, MaxCallDepth);
            }
            return CallGuard(this, false);
        }
        ++CallDepth;
        return CallGuard(this, true);
    }

    void EvaluationContext::setMaxCallDepth(std::size_t maxCallDepth) { MaxCallDepth = maxCallDepth; }
    std::size_t EvaluationContext::maxCallDepth() const { return MaxCallDepth; }

    std::size_t EvaluationContext::depth() const { return Depth; }
    void EvaluationContext::setMaxDepth(std::size_t maxDepth) { MaxDepth = maxDepth; }
    std::size_t EvaluationContext::maxDepth() const { return MaxDepth; }
    void EvaluationContext::setMaxSequenceLength(std::size_t maxLength) { MaxSequenceLength = maxLength; }
    std::size_t EvaluationContext::maxSequenceLength() const { return MaxSequenceLength; }
}
