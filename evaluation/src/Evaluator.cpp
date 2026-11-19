#include <sysmlv2/evaluation/Evaluator.h>
#include <sysmlv2/evaluation/QualifiedName.h>

#include "Arguments.h"
#include "Callables.h"
#include "CompilerSupport.h"
#include "Navigation.h"
#include "StackRunner.h"

#include <kerml/core/features/FeatureChaining.h>
#include <kerml/core/features/FeatureTyping.h>
#include <kerml/core/features/Redefinition.h>
#include <kerml/core/types/Specialization.h>
#include <kerml/core/features/FeatureMembership.h>
#include <kerml/kernel/expressions/CollectExpression.h>
#include <kerml/kernel/expressions/FeatureReferenceExpression.h>
#include <kerml/kernel/expressions/FeatureChainExpression.h>
#include <kerml/kernel/expressions/IndexExpression.h>
#include <kerml/kernel/expressions/InvocationExpression.h>
#include <kerml/kernel/expressions/LiteralBoolean.h>
#include <kerml/kernel/expressions/LiteralInfinity.h>
#include <kerml/kernel/expressions/LiteralInteger.h>
#include <kerml/kernel/expressions/LiteralRational.h>
#include <kerml/kernel/expressions/LiteralString.h>
#include <kerml/kernel/expressions/NullExpression.h>
#include <kerml/kernel/expressions/OperatorExpression.h>
#include <kerml/kernel/expressions/OperatorFunctions.h>
#include <kerml/kernel/expressions/SelectExpression.h>
#include <kerml/kernel/featurevalues/FeatureValue.h>
#include <kerml/kernel/functions/ParameterMembership.h>
#include <kerml/kernel/functions/ResultExpressionMembership.h>
#include <kerml/kernel/functions/ReturnParameterMembership.h>
#include <kerml/root/elements/Relationship.h>
#include <kerml/root/namespaces/Membership.h>

#include <algorithm>
#include <cmath>
#include <deque>
#include <exception>
#include <set>
#include <typeinfo>
#include <unordered_map>
#include <utility>

namespace SysMLv2::Evaluation {

    namespace {
        using KerML::Entities::Element;
        using KerML::Entities::Expression;
        using KerML::Entities::Feature;
        using KerML::Entities::Function;
        using ExpressionPtr = std::shared_ptr<Expression>;
        using FeaturePtr = std::shared_ptr<Feature>;
        using Arguments = std::vector<ExpressionPtr>;

        /// The qualified name of a function for messages (a placeholder if the ownership chain gives nothing).
        std::string describeFunction(const std::shared_ptr<Function>& function) {
            const std::string name = qualifiedNameOf(function);
            return name.empty() ? std::string("<unnamed function>") : name;
        }

        // The shape of the arguments: see Arguments.cpp.

        std::shared_ptr<Function> invokedFunction(const KerML::Entities::InvocationExpression& invocation) { return invokedFunctionOf(invocation); }

        // Inherited native implementations -----------------------------------------------------------------------------------

        enum class IssueKind { None, Body, Reordered };

        /// True if an input parameter of the function redefines a parameter of its general at another position (`in a :>> y;` as the
        /// first parameter): a native implementation of the general would receive the arguments in the wrong order.
        bool reordersParameters(const std::shared_ptr<Function>& function) {
            const auto own = ownInputParameters(*function);
            for (std::size_t index = 0; index < own.size(); ++index) {
                for (const auto& redefinition : own[index]->ownedRedefinition()) {
                    const auto redefined = redefinition ? redefinition->redefinedFeature() : nullptr;
                    const auto general = redefined ? std::dynamic_pointer_cast<KerML::Entities::Type>(redefined->owner()) : nullptr;
                    if (!general) continue;
                    const auto parameters = ownInputParameters(*general);
                    for (std::size_t position = 0; position < parameters.size(); ++position) {
                        if (parameters[position] == redefined && position != index) return true;
                    }
                }
            }
            return false;
        }

        /// What differs between a function and the generals that hold its inherited native implementation (all paths; the holders
        /// themselves and what lies above them are not checked): Body if the function or one between has a result of its own (its body
        /// runs instead of the native implementation), else Reordered if parameters are redefined in another order (the native
        /// implementation gets the arguments reordered), else None.
        IssueKind inheritedImplementationIssue(const std::shared_ptr<Function>& function, const FunctionRegistry& registry) {
            std::deque<std::shared_ptr<KerML::Entities::Type>> queue{function};
            std::set<const KerML::Entities::Type*> visited{function.get()};
            IssueKind issue = IssueKind::None;
            while (!queue.empty()) {
                const std::shared_ptr<KerML::Entities::Type> current = std::move(queue.front());
                queue.pop_front();
                if (current != function && registry.find(qualifiedNameOf(*current)) != nullptr) continue;   // (a holder)
                if (const auto currentFunction = std::dynamic_pointer_cast<Function>(current)) {
                    if (const OwnResult own = ownResultOf(*currentFunction)) {
                        // a library function whose result only has a `default` value is what the native implementation mirrors; any
                        // other body (`= (col.elements as Anything)#(index)`) is not
                        const bool mirrored = own.Parameter && boundValueOf(own.Parameter).IsDefault && isKernelLibraryType(*currentFunction);
                        if (!mirrored) return IssueKind::Body;
                    }
                    if (reordersParameters(currentFunction)) issue = IssueKind::Reordered;
                }
                for (const auto& specialization : current->ownedSpecialization()) {
                    const auto general = specialization ? specialization->general() : nullptr;
                    if (general && visited.insert(general.get()).second) queue.push_back(general);
                }
            }
            return issue;
        }
    }

    namespace {
    /// A value as an expression: how the values of arguments reach the native functions and user functions that expect expressions.
    class ConstantExpression : public virtual KerML::Entities::Expression {
    public:
        explicit ConstantExpression(Value value) : Constant(std::move(value)) {}
        Value Constant;
    };
    }   // namespace

    namespace {
    struct Env;
    using EnvPtr = std::shared_ptr<Env>;

    /// A function value: a body expression `{ in x; x + 1 }` or a function reference, with the path and the frame (the lexical scope) of
    /// the place where it was written.
    struct Lambda {
        ExpressionPtr Body;
        PathPtr Where;
        EnvPtr Scope;
    };

    /// What a parameter is bound to in a frame: a value, or a function value (`in expr f`). Both empty: an optional parameter without
    /// argument, which still shadows whatever the frames outside have bound.
    struct Bound {
        Value Val;
        std::shared_ptr<Lambda> Fn;
    };

    /// A call frame: the parameters of a call of a function or of a body expression (`that` too), and the frame that encloses the body
    /// lexically (a body sees the frame where it was written, not the one that calls it).
    struct Env {
        std::vector<std::pair<const KerML::Entities::Feature*, Bound>> Entries;
        EnvPtr Outer;
        std::size_t Id = 0;
        std::optional<Value> That;
    };
    }   // namespace

    namespace {
    // The state of one evaluate call: the context, the options and the lookup cache. Nothing of it outlives the call, so a change of
    // the model between two calls (a library loaded, generals resolved in place) is always seen.
    class Run {
    public:
        Run(std::shared_ptr<const FunctionRegistry> registry, const EvaluationOptions& options, std::size_t maxDepth, std::size_t maxCallDepth) : Registry(std::move(registry)) {
            Context.setMaxDepth(maxDepth);
            Context.setMaxCallDepth(maxCallDepth);
            (void)options;
            Context.setMaxSequenceLength(options.maxSequenceLength);
            Context.setExpressionEvaluator([this](const ExpressionPtr& current, EvaluationContext& running) { return dispatch(current, running); });
            Context.setFunctionInvoker([this](const ExpressionPtr& function, std::vector<Value> arguments, EvaluationContext& running) {
                return callCallable(function, Current, std::move(arguments), running);
            });
        }

        bool limitReached() const { return Context.limitReached(); }
        bool depthLimitHit() const { return Context.depthLimitHit(); }
        bool callLimitHit() const { return Context.callLimitHit(); }

        /// Evaluates an expression in a target (null: none).
        Result execute(const ExpressionPtr& expression, const std::shared_ptr<Element>& target) {
            return finish([&] {
                // without a target the expression is evaluated in the type that features the feature it belongs to
                const std::shared_ptr<Element> context = target ? target : Nav.featuringContext(expression);
                Current = context ? std::make_shared<const Path>(Path{context, nullptr}) : nullptr;
                const auto scope = Context.enterTarget(context);
                return Context.evaluate(expression);
            });
        }

        /// Evaluates the value of a feature in a target: its effective binding there.
        Result executeFeature(const FeaturePtr& feature, const std::shared_ptr<Element>& target) {
            return finish([&] {
                const auto guard = Context.enterScope();
                if (!guard) return Value();
                // without a target the feature is evaluated in the context that features it: its owning type
                const std::shared_ptr<Element> context = target ? target : Nav.featuringContext(feature);
                if (target && !Nav.conforms(feature, target)) {
                    Context.report(Severity::Error, "the target '" + qualifiedNameOf(*target) + "' does not conform to the owner of '" + describeFeature(feature) + "'");
                    return Value();
                }
                return valueIn(feature, context ? std::make_shared<const Path>(Path{context, nullptr}) : nullptr, Context);
            });
        }

    private:
        template <class Evaluation>
        Result finish(Evaluation&& evaluation) {
            Result result;
            try {
                result.value = evaluation();
            } catch (const std::exception& error) {
                reportException(Context, error.what());
            } catch (...) {
                reportException(Context, "unknown exception");
            }
            result.failed = Context.failed();
            if (Context.hasErrors()) result.value = Value();
            result.diagnostics = Context.takeDiagnostics();
            return result;
        }

        struct CacheEntry {
            std::shared_ptr<Function> Owner;   // (keeps the key's address valid for the call)
            FunctionRegistry::Match Match;
            IssueKind Issue = IssueKind::None; // (what differs from the holder of an inherited implementation)
        };

        /// registry.lookup() through the per-call cache.
        const CacheEntry& lookup(const std::shared_ptr<Function>& function) {
            const auto found = Cache.find(function.get());
            if (found != Cache.end()) return found->second;
            CacheEntry entry{function, Registry->lookup(function), IssueKind::None};
            // a function of a user package that is named like a library package is no library function (its qualified name is the
            // name of a native implementation by chance)
            if (entry.Match.implementation != nullptr && !entry.Match.inherited && !isKernelLibraryType(*function)) {
                const std::string name = qualifiedNameOf(*function);
                if (isKernelPackageName(name.substr(0, name.find("::")))) entry.Match = FunctionRegistry::Match{};
            }
            if (entry.Match.implementation != nullptr && entry.Match.inherited) entry.Issue = inheritedImplementationIssue(function, *Registry);
            return Cache.emplace(function.get(), std::move(entry)).first->second;
        }

        /// The hook of EvaluationContext::evaluate(): one expression, already counted as a level of depth and as the current element.
        Value dispatch(const ExpressionPtr& expression, EvaluationContext& context) {
            Expression* const raw = expression.get();
            if (auto* operation = dynamic_cast<KerML::Entities::OperatorExpression*>(raw)) {
                // (the subclasses of the operator expression first)
                if (auto* chain = dynamic_cast<KerML::Entities::FeatureChainExpression*>(operation)) return evaluateChain(*chain, context);
                return evaluateOperator(*operation, context);
            }
            if (auto* invocation = dynamic_cast<KerML::Entities::InvocationExpression*>(raw)) {
                // Only a plain call: a subclass from outside kerml (a trigger invocation of sysml, ...) means something else.
                const Expression& object = *raw;
                if (typeid(object) != typeid(KerML::Entities::InvocationExpression)) return unsupported(context, *expression);
                return evaluateInvocation(*invocation, context);
            }
            if (const auto* literal = dynamic_cast<KerML::Entities::LiteralInteger*>(raw)) return Value::integer(literal->value());
            if (const auto* literal = dynamic_cast<KerML::Entities::LiteralRational*>(raw)) {
                if (!std::isfinite(literal->value())) return nonFiniteLiteral(context);
                return Value::real(literal->value());
            }
            if (const auto* literal = dynamic_cast<KerML::Entities::LiteralBoolean*>(raw)) return Value::boolean(literal->value());
            if (const auto* literal = dynamic_cast<KerML::Entities::LiteralString*>(raw)) return Value::string(literal->value());
            if (dynamic_cast<KerML::Entities::LiteralInfinity*>(raw)) return Value::infinity();
            if (dynamic_cast<KerML::Entities::NullExpression*>(raw)) return Value();
            if (const auto* constant = dynamic_cast<ConstantExpression*>(raw)) return constant->Constant;
            if (const auto* reference = dynamic_cast<KerML::Entities::FeatureReferenceExpression*>(raw)) return evaluateReference(*reference, context);
            return unsupported(context, *expression);   // (feature references, metadata access, constructors, usages, bodies, ...)
        }


        // Feature references and chains --------------------------------------------------------------------------------------
        //
        // A reference is evaluated at the current path (the instance, a usage or definition of the model, that the expression is evaluated
        // in, and the instances it was reached through, see Path): its value is the value of the effective binding of the referent
        // there, see Navigation::resolve(). A feature without a value is the element it denotes if it is structural (a part, an item),
        // else the empty sequence. A chain `a.b` evaluates `b` in every element that `a` stands for ("targets"): the elements that the
        // value of `a` has, or, for a feature without a value, the feature itself, entered at the path of `a`.

        /// The feature of a reference, or null after an Error (no referent recorded in the model, or an unresolved name).
        SYSMLV2_COLD_PATH static FeaturePtr referentOrReport(const KerML::Entities::FeatureReferenceExpression& reference, EvaluationContext& context) {
            const FeaturePtr referent = referentOf(reference);
            if (!referent) {
                context.report(Severity::Error, "the reference has no referent in the model");
                return nullptr;
            }
            return checkResolved(referent, "reference", context);
        }

        SYSMLV2_COLD_PATH static FeaturePtr checkResolved(const FeaturePtr& feature, const char* what, EvaluationContext& context) {
            if (isUnresolvedPlaceholder(*feature)) {
                context.report(Severity::Error, std::string("unresolved ") + what + " '" + feature->declaredName().value_or("<unnamed>") + "'");
                return nullptr;
            }
            return feature;
        }

        /// What a reference without a referent wraps (see wrappedExpressionOf()): a body `{ ... }` (a plain Expression) is not supported
        /// yet, like in parsed text; any other expression is a lazily evaluated operand and is evaluated in its place. Null if the
        /// reference is no wrapper or after an Error.
        ExpressionPtr unwrap(const KerML::Entities::FeatureReferenceExpression& reference, EvaluationContext& context, bool& reported) {
            if (referentOf(reference)) return nullptr;
            ExpressionPtr wrapped = wrappedExpressionOf(reference);
            if (!wrapped) return nullptr;
            const Expression& object = *wrapped;
            if (typeid(object) == typeid(Expression)) {
                context.report(Severity::Error, "not supported yet: a function value (a body expression) as a result; function values can be passed to functions, not returned");
                reported = true;
                return nullptr;
            }
            return wrapped;
        }

        Value evaluateReference(const KerML::Entities::FeatureReferenceExpression& reference, EvaluationContext& context) {
            bool reported = false;
            if (const ExpressionPtr wrapped = unwrap(reference, context, reported)) return context.evaluate(wrapped);
            if (reported) return Value();
            const FeaturePtr referent = referentOrReport(reference, context);
            if (!referent) return Value();
            return valueIn(referent, Nav.contextFor(referent, Current), context);
        }

        /// The value of a feature chain.
        Value evaluateChain(KerML::Entities::FeatureChainExpression& chain, EvaluationContext& context) {
            std::vector<PathPtr> unused;
            std::vector<Item> items;
            if (!walkChain(chain, context, true, unused, items)) return Value();
            return Value(std::move(items));
        }

        /// The links of a chain after the left operand: the target feature, or, if that is a chain of its own (XMI of the pilot
        /// implementation writes `a.b.c` as one expression whose target is the chain `b.c`), its chaining features. False after an Error.
        SYSMLV2_COLD_PATH static bool linksOf(const KerML::Entities::FeatureChainExpression& chain, EvaluationContext& context, std::vector<FeaturePtr>& links) {
            const FeaturePtr last = chainTargetOf(chain);
            if (!last) {
                context.report(Severity::Error, "the feature chain has no target feature in the model");
                return false;
            }
            if (last->ownedFeatureChaining().empty()) {
                links.push_back(last);
                return true;
            }
            for (const auto& chaining : last->ownedFeatureChaining()) {
                const FeaturePtr link = chaining ? chaining->chainingFeature() : nullptr;
                if (!link) {
                    context.report(Severity::Error, "the feature chain has a link that the model does not record");
                    return false;
                }
                links.push_back(link);
            }
            return true;
        }

        /// Follows the links of a chain element-wise from the targets of its left operand. With @p finalValue the value of the last link
        /// is appended to @p items, else the targets of the last link are appended to @p targets. False after an Error.
        bool walkChain(const KerML::Entities::FeatureChainExpression& chain, EvaluationContext& context, bool finalValue, std::vector<PathPtr>& targets,
                       std::vector<Item>& items) {
            const ArgumentList operands = argumentsOf(chain);
            if (operands.MissingValue || operands.Values.size() != 1) {
                context.report(Severity::Error, "the feature chain has no single left operand");
                return false;
            }
            std::vector<FeaturePtr> links;
            if (!linksOf(chain, context, links)) return false;
            std::vector<PathPtr> current;
            if (!targetsOfExpression(operands.Values.front(), context, current)) return false;
            for (std::size_t index = 0; index < links.size(); ++index) {
                const bool last = index + 1 == links.size();
                std::vector<PathPtr> next;
                for (const auto& target : current) {
                    const FeaturePtr link = chainLinkIn(links[index], target, context);
                    if (!link) return false;
                    if (last && finalValue) {
                        const Value value = valueIn(link, target, context);
                        if (context.hasErrors()) return false;
                        items.insert(items.end(), value.items().begin(), value.items().end());
                    } else if (!targetsIn(link, target, context, next)) {
                        return false;
                    }
                    if (items.size() > context.maxSequenceLength() || next.size() > context.maxSequenceLength()) {
                        context.report(Severity::Error, "the sequence is longer than the limit of " + std::to_string(context.maxSequenceLength()) + " items");
                        return false;
                    }
                }
                current = std::move(next);
            }
            if (!finalValue) targets.insert(targets.end(), current.begin(), current.end());
            return true;
        }

        /// The feature of a chain link in a target. A link that the parser could not resolve (the type of the left operand was not known,
        /// or the chain is longer than the parser resolves) is looked up by its name among the features of the target; null after an Error.
        FeaturePtr chainLinkIn(const FeaturePtr& link, const PathPtr& target, EvaluationContext& context) {
            if (!isUnresolvedPlaceholder(*link)) return link;
            const std::string name = link->declaredName().value_or(std::string());
            bool ambiguous = false;
            if (!name.empty()) {
                if (FeaturePtr found = Nav.findByName(name, target->Element, ambiguous)) return found;
            }
            context.report(Severity::Error, ambiguous ? "the feature '" + name + "' is ambiguous in the target" : "unresolved feature '" + name + "'");
            return nullptr;
        }

        /// The value of a feature at a path.
        Value valueIn(const FeaturePtr& feature, const PathPtr& path, EvaluationContext& context, bool withSubsetters = true) {
            if (const Bound* bound = findBinding(feature.get())) return bound->Val;
            if (const Value* bound = context.binding(feature.get())) return *bound;
            if (const int kind = specialKind(feature)) {
                if (kind == SelfKind && path) return Value::element(path->Element);
                if (kind == ThatKind) { if (const Value* that = findThat()) return *that; }
                context.report(Severity::Error, kind == SelfKind ? "'self' has no target in this evaluation" : "'that' is not bound here");
                return Value();
            }
            // the constant of the library: TrigFunctions::pi is a feature without a value (it has an invariant that fixes its digits)
            if (feature->declaredName() == std::string("pi") && qualifiedNameOf(feature) == "TrigFunctions::pi") return Value::real(3.141592653589793);
            const Resolution resolution = Nav.resolve(feature, path ? path->Element : nullptr);
            if (!resolution.Ambiguity.empty()) {
                context.report(Severity::Error, resolution.Ambiguity);
                return Value();
            }
            const FeaturePtr effective = resolution.Effective ? resolution.Effective : feature;
            // the features of the instance that subset it are its values (`parts` is `a` and `b` of `part a :> parts`); a `default` value does
            // not stop them, a bound one does
            if (withSubsetters && (!resolution.Value || (resolution.Binding && boundValueOf(resolution.Binding).IsDefault))) {
                const auto subsetters = Nav.subsettersOf(effective, path ? path->Element : nullptr);
                if (!subsetters.empty()) return subsettersValue(effective, subsetters, path, context);
            }
            if (!resolution.Value) {
                // no value: a part, an action, an enumeration literal, ... is the element it denotes, an attribute has the empty sequence
                if (!Nav.denotesElement(effective)) return Value();
                if (withSubsetters && isEmptyPrototype(effective, path, context)) return Value();   // (see there)
                return Value::element(effective);
            }
            warnIfOverriding(resolution, context);
            return evaluateBinding(resolution.Binding, resolution.Value, path, context);
        }

        /// The values of the subsetters of a feature, in order. A subsetter whose value is being evaluated is left out of the nested
        /// evaluation (`frst :> ps = ps#(1)`); if it then adds an element that the others do not have, the definition is cyclic (Error).
        /// An element that several subsetters have counts once.
        Value subsettersValue(const FeaturePtr& effective, const std::vector<FeaturePtr>& subsetters, const PathPtr& path, EvaluationContext& context) {
            std::vector<Item> items;
            for (const FeaturePtr& subsetter : subsetters) {
                const PathPtr where = Nav.contextFor(subsetter, path);
                if (isBeingEvaluated(subsetter, where)) {
                    Skipped.insert(subsetter.get());
                    continue;
                }
                const Value one = valueIn(subsetter, where, context, false);
                if (context.hasErrors()) return Value();
                const bool wasSkipped = Skipped.erase(subsetter.get()) != 0;
                for (const Item& item : one.items()) {
                    if (std::holds_alternative<std::shared_ptr<KerML::Entities::Element>>(item) && std::find(items.begin(), items.end(), item) != items.end()) continue;
                    if (wasSkipped && !std::holds_alternative<std::shared_ptr<KerML::Entities::Element>>(item)) continue;
                    if (wasSkipped) {
                        context.report(Severity::Error, "cyclic definition: '" + describeFeature(subsetter) + "' subsets '" + describeFeature(effective) + "' and adds to its value");
                        return Value();
                    }
                    items.push_back(item);
                }
            }
            return Value(std::move(items));
        }

        /// True if the value of the feature at the path is being evaluated right now: a subsetter whose value depends on the feature
        /// that it subsets (`minuend subsets elements = head(elements)`) is no member of that feature's value.
        bool isBeingEvaluated(const FeaturePtr& feature, const PathPtr& path) {
            const Resolution resolution = Nav.resolve(feature, path ? path->Element : nullptr);
            if (!resolution.Binding) return false;
            for (const ActiveBinding& active : Active) {
                if (active.Binding.get() == resolution.Binding.get() && active.FrameId == Frame && samePath(active.Where, path)) return true;
            }
            return false;
        }

        /// A value-less structural feature that nothing subsets (see Evaluator.h): the prototypical element only if its effective
        /// multiplicity has the upper bound 1 (also if none is written) and the path that leads to it has not passed through it (or a
        /// feature that redefines it or that it redefines) as a prototype already; otherwise empty, with a Warning once per feature if
        /// the multiplicity requires instances.
        bool isEmptyPrototype(const FeaturePtr& feature, const PathPtr& path, EvaluationContext& context) {
            const WrittenBounds bounds = effectiveBoundsOf(feature);
            if (!bounds.upper || *bounds.upper > 1) {
                if (bounds.lower >= 1 && WarnedEmpty.insert(feature.get()).second)
                    context.report(Severity::Warning, "the values of '" + describeFeature(feature) + "' are not given; it is evaluated as empty although its multiplicity requires at least " + std::to_string(bounds.lower));
                return true;
            }
            if (!std::dynamic_pointer_cast<KerML::Entities::Type>(feature->owner())) return false;   // (a usage of a package is no prototype: a reference that leads back to it is a cycle)
            for (auto node = path; node; node = node->Parent) {
                if (node->Element == feature) return true;
                const auto element = std::dynamic_pointer_cast<Feature>(node->Element);
                if (!element) continue;
                for (const auto& redefinition : element->ownedRedefinition()) {
                    if (redefinition && redefinition->redefinedFeature() == feature) return true;
                }
                for (const auto& redefinition : feature->ownedRedefinition()) {
                    if (redefinition && redefinition->redefinedFeature() == element) return true;
                }
            }
            return false;
        }

        /// The paths a feature stands for at a path, to navigate into: the elements of its value, or, if it has no value, the feature that
        /// is effective there, entered at the path (so that references in its value find the outer instance). False after an Error.
        bool targetsIn(const FeaturePtr& feature, const PathPtr& path, EvaluationContext& context, std::vector<PathPtr>& out, bool withSubsetters = true) {
            if (const Bound* bound = findBinding(feature.get())) return collectElements(bound->Val, path, context, out);
            if (const Value* bound = context.binding(feature.get())) return collectElements(*bound, path, context, out);
            if (specialKind(feature) != 0) {
                const Value value = valueIn(feature, path, context);
                return !context.hasErrors() && collectElements(value, path, context, out);
            }
            const Resolution resolution = Nav.resolve(feature, path ? path->Element : nullptr);
            if (!resolution.Ambiguity.empty()) {
                context.report(Severity::Error, resolution.Ambiguity);
                return false;
            }
            const FeaturePtr effective = resolution.Effective ? resolution.Effective : feature;
            if (withSubsetters && (!resolution.Value || (resolution.Binding && boundValueOf(resolution.Binding).IsDefault))) {
                const auto subsetters = Nav.subsettersOf(effective, path ? path->Element : nullptr);
                if (!subsetters.empty()) {
                    for (const FeaturePtr& subsetter : subsetters) {
                        const PathPtr where = Nav.contextFor(subsetter, path);
                        if (isBeingEvaluated(subsetter, where)) continue;
                        const std::size_t before = out.size();
                        if (!targetsIn(subsetter, where, context, out, false)) return false;
                        // (an element that several subsetters have counts once)
                        for (std::size_t index = before; index < out.size();) {
                            bool duplicate = false;
                            for (std::size_t other = 0; other < before && !duplicate; ++other) duplicate = out[other]->Element == out[index]->Element && samePath(out[other]->Parent, out[index]->Parent);
                            if (duplicate) out.erase(out.begin() + static_cast<std::ptrdiff_t>(index));
                            else ++index;
                        }
                    }
                    return true;
                }
            }
            if (resolution.Value) {
                warnIfOverriding(resolution, context);
                // the value expression is navigated, not evaluated: a reference to a part (`ref part driverSeat : Seat = seat;`) keeps the
                // instance it is found in, which a plain element value would lose
                return withBinding(resolution.Binding, path, context, [&] { return targetsOfExpression(resolution.Value, context, out); });
            }
            // (a feature of a type is entered through the instance that features it; a feature of a package starts a new path)
            if (withSubsetters && Nav.denotesElement(effective) && isEmptyPrototype(effective, path, context)) return true;   // (see there)
            const bool featured = std::dynamic_pointer_cast<KerML::Entities::Type>(effective->owner()) != nullptr;
            out.push_back(std::make_shared<const Path>(Path{effective, featured ? path : nullptr}));
            return true;
        }

        /// KerML allows only a default value to be overridden: a Warning (once per binding and evaluation), the value is kept.
        void warnIfOverriding(const Resolution& resolution, EvaluationContext& context) {
            if (resolution.Binding && (!resolution.Overridden.empty() || !resolution.IgnoredDefaults.empty()) && Warned.insert(resolution.Binding.get()).second) {
                if (!resolution.Overridden.empty())
                    context.report(Severity::Warning, "'" + describeFeature(resolution.Binding) + "' overrides the bound value of '" + describeFeature(resolution.Overridden.front()) +
                                                          "'; only default values may be overridden");
                if (!resolution.IgnoredDefaults.empty())
                    context.report(Severity::Warning, "the default value of '" + describeFeature(resolution.IgnoredDefaults.front()) + "' is ignored: '" + describeFeature(resolution.Binding) +
                                                          "' binds a value");
            }
        }

        /// The targets an operand of a chain stands for. False after an Error.
        bool targetsOfExpression(const ExpressionPtr& expression, EvaluationContext& context, std::vector<PathPtr>& out) {
            const auto guard = context.enterScope();
            if (!guard) return false;
            const auto scope = context.enterElement(expression);
            if (const auto reference = std::dynamic_pointer_cast<KerML::Entities::FeatureReferenceExpression>(expression)) {
                bool reported = false;
                if (const ExpressionPtr wrapped = unwrap(*reference, context, reported)) return targetsOfExpression(wrapped, context, out);
                if (reported) return false;
                const FeaturePtr referent = referentOrReport(*reference, context);
                return referent && targetsIn(referent, Nav.contextFor(referent, Current), context, out);
            }
            if (const auto chain = std::dynamic_pointer_cast<KerML::Entities::FeatureChainExpression>(expression)) {
                std::vector<Item> unused;
                return walkChain(*chain, context, false, out, unused);
            }
            // a sequence `(a, b, c)`: the targets of every element, in order (walked iteratively, like the concatenation)
            if (const auto sequence = std::dynamic_pointer_cast<KerML::Entities::OperatorExpression>(expression); sequence && sequence->operatorName() == ",") {
                std::vector<ExpressionPtr> pending{expression};
                while (!pending.empty()) {
                    const ExpressionPtr next = std::move(pending.back());
                    pending.pop_back();
                    const auto nested = std::dynamic_pointer_cast<KerML::Entities::OperatorExpression>(next);
                    if (nested && nested->operatorName() == ",") {
                        ArgumentList list = argumentsOf(*nested);
                        if (list.MissingValue || list.Values.size() != 2) {
                            context.report(Severity::Error, "the sequence is incomplete in the model");
                            return false;
                        }
                        pending.push_back(std::move(list.Values[1]));
                        pending.push_back(std::move(list.Values[0]));
                        continue;
                    }
                    if (!targetsOfLeaf(next, context, out)) return false;
                    if (out.size() > context.maxSequenceLength()) {
                        context.report(Severity::Error, "the sequence is longer than the limit of " + std::to_string(context.maxSequenceLength()) + " items");
                        return false;
                    }
                }
                return true;
            }
            return targetsOfLeaf(expression, context, out);
        }

        /// The targets of an operand that is not a chain or sequence: a reference (or any expression, by its value).
        bool targetsOfLeaf(const ExpressionPtr& expression, EvaluationContext& context, std::vector<PathPtr>& out) {
            if (std::dynamic_pointer_cast<KerML::Entities::FeatureReferenceExpression>(expression) ||
                std::dynamic_pointer_cast<KerML::Entities::FeatureChainExpression>(expression))
                return targetsOfExpression(expression, context, out);
            const Value value = context.evaluate(expression);
            return !context.hasErrors() && collectElements(value, Current, context, out);
        }

        /// The elements of a value as paths (the element of the current path keeps its path, the others stand alone).
        SYSMLV2_COLD_PATH static bool collectElements(const Value& value, const PathPtr& current, EvaluationContext& context, std::vector<PathPtr>& out) {
            for (const Item& item : value.items()) {
                if (const auto* element = std::get_if<std::shared_ptr<Element>>(&item)) {
                    out.push_back(current && current->Element == *element ? current : std::make_shared<const Path>(Path{*element, nullptr}));
                } else {
                    context.report(Severity::Error, "cannot navigate into a value that is not an element of the model");
                    return false;
                }
            }
            return true;
        }

        static constexpr int SelfKind = 1;
        static constexpr int ThatKind = 2;

        /// SelfKind / ThatKind for Base::Anything::self / Base::things::that and every feature that redefines them (a part definition finds
        /// `Performance::self` first, a class may declare `feature me redefines self`), else 0. Cached for the evaluation.
        int specialKind(const FeaturePtr& feature) {
            const auto cached = Special.find(feature.get());
            if (cached != Special.end()) return cached->second;
            int kind = 0;
            std::vector<FeaturePtr> pending{feature};
            std::set<const Feature*> visited{feature.get()};
            while (!pending.empty() && kind == 0) {
                const FeaturePtr current = std::move(pending.back());
                pending.pop_back();
                const auto& name = current->declaredName();
                if (name && *name == "self" && qualifiedNameOf(current) == "Base::Anything::self") kind = SelfKind;
                if (name && *name == "that") {
                    const std::string qualified = qualifiedNameOf(current);
                    if (qualified == "Base::things::that" || qualified == "Base::Anything::that") kind = ThatKind;
                }
                for (const auto& redefinition : current->ownedRedefinition()) {
                    const auto redefined = redefinition ? redefinition->redefinedFeature() : nullptr;
                    if (redefined && visited.insert(redefined.get()).second) pending.push_back(redefined);
                }
            }
            Special.emplace(feature.get(), kind);
            return kind;
        }

        /// Evaluates the value expression of a binding at a path; a binding that is already being evaluated for that path is a cycle.
        Value evaluateBinding(const FeaturePtr& binding, const ExpressionPtr& expression, const PathPtr& path, EvaluationContext& context) {
            Value result;
            withBinding(binding, path, context, [&] {
                result = context.evaluate(expression);
                return true;
            });
            return result;
        }

        /// Runs @p action with the binding active at the path: the expressions it evaluates belong to that path. False (after reporting
        /// the cycle) if the binding is already being evaluated for the same path, else what the action returns.
        template <class Action>
        bool withBinding(const FeaturePtr& binding, const PathPtr& path, EvaluationContext& context, Action&& action) {
            for (std::size_t index = 0; index < Active.size(); ++index) {
                if (Active[index].Binding.get() == binding.get() && Active[index].FrameId == Frame && samePath(Active[index].Where, path)) {
                    reportCycle(index, binding, context);
                    return false;
                }
            }
            struct Guard {
                Run& Owner;
                PathPtr Saved;
                ~Guard() {
                    Owner.Active.pop_back();
                    Owner.Current = std::move(Saved);
                }
            };
            Active.push_back(ActiveBinding{binding, path, Frame});
            Guard guard{*this, Current};
            Current = path;
            const auto scope = context.enterTarget(path ? path->Element : nullptr);
            return action();
        }

        SYSMLV2_COLD_PATH void reportCycle(std::size_t first, const FeaturePtr& again, EvaluationContext& context) {
            std::string path;
            for (std::size_t index = first; index < Active.size(); ++index) path += describeFeature(Active[index].Binding) + " -> ";
            context.report(Severity::Error, "cyclic definition: " + path + describeFeature(again));
        }

        static std::string describeFeature(const FeaturePtr& feature) {
            const std::string name = qualifiedNameOf(feature);
            return name.empty() ? feature->declaredName().value_or("<unnamed>") : name;
        }

        SYSMLV2_COLD_PATH static Value nonFiniteLiteral(EvaluationContext& context) {
            context.report(Severity::Error, "the Real literal is not a finite number");
            return Value();
        }

        SYSMLV2_COLD_PATH static Value unsupported(EvaluationContext& context, Expression& expression) {
            if (expression.getType() == "Expression")
                context.report(Severity::Error, "not supported yet: a function value (a body expression) as a result; function values can be passed to functions, not returned");
            else
                context.report(Severity::Error, "not supported yet: " + expression.getType());
            return Value();
        }

        /// The implementation of an operator expression (nullptr if there is none). Not inlined: it is only the setup of a call and its
        /// locals must not add to the frame of evaluateOperator, which is on the recursion path.
        SYSMLV2_COLD_PATH const NativeFunction* resolveOperator(const KerML::Entities::OperatorExpression& operation, std::shared_ptr<Function>& function) {
            function = invokedFunction(operation);
            if (function) {
                const CacheEntry& entry = lookup(function);
                if (entry.Match.implementation != nullptr && entry.Match.inherited && entry.Issue == IssueKind::Body) return nullptr;
                return entry.Match.implementation;
            }
            // No function (no library loaded, XMI, older JSON, hand-built): the function that the operator stands for.
            if (const char* name = KerML::operatorFunctionName(operation.operatorName())) return Registry->find(name);
            return nullptr;
        }

        Value evaluateOperator(KerML::Entities::OperatorExpression& operation, EvaluationContext& context) {
            if (isArrow(operation)) return evaluateCall(operation, true, context);
            std::shared_ptr<Function> function;
            const NativeFunction* const implementation = resolveOperator(operation, function);
            if (implementation == nullptr) {
                // a user function that an operator is bound to, with a body of its own: the call machinery runs it
                if (function) return evaluateCall(operation, false, context);
                return noImplementation(operation, function, context);
            }
            ArgumentList list = argumentsOf(operation);
            if (list.MissingValue) return missingArgumentValue(context);
            return call(*implementation, list.Values, context);
        }

        SYSMLV2_COLD_PATH static Value missingArgumentValue(EvaluationContext& context) {
            context.report(Severity::Error, "an input parameter of the invocation has no value");
            return Value();
        }

        SYSMLV2_COLD_PATH static bool isArrow(const KerML::Entities::OperatorExpression& operation) { return operation.operatorName() == "->"; }

        Value evaluateInvocation(KerML::Entities::InvocationExpression& invocation, EvaluationContext& context) { return evaluateCall(invocation, false, context); }

        // Calls -------------------------------------------------------------------------------------------------------------------
        //
        // A call (`F(a, b)`, `x->F(a)`, a calculation usage `g(a)`) binds its arguments to the input parameters of the callee (positional
        // and named, see bindArguments()) and then either calls the native implementation, or, for a user function (or a library function
        // without a native implementation), evaluates its body in a frame where the parameters are bound. A function that specializes a
        // function with a native implementation runs its own body if it has one (except for the functions of the Kernel Function
        // Library, which keep the native implementation), else the native implementation of the general, with the arguments in the order
        // of the general's parameters.

        /// The binding of a feature in the frames that are visible (the running frame, then those that enclose it lexically).
        const Bound* findBinding(const Feature* feature) const {
            for (const Env* env = CurrentEnv.get(); env != nullptr; env = env->Outer.get()) {
                for (auto it = env->Entries.rbegin(); it != env->Entries.rend(); ++it) {
                    if (it->first == feature) return &it->second;
                }
            }
            return nullptr;
        }

        const Value* findThat() const {
            for (const Env* env = CurrentEnv.get(); env != nullptr; env = env->Outer.get()) {
                if (env->That) return &*env->That;
            }
            return nullptr;
        }

        /// The function value that an argument expression stands for, resolved where it is written (in @p env, at @p path): a body, a
        /// function reference, or a parameter that holds a function value, whose function value is taken over. Null if it is none.
        std::shared_ptr<Lambda> lambdaOf(const ExpressionPtr& argument, const EnvPtr& env, const PathPtr& path) const {
            if (!argument) return nullptr;
            if (bodyExpressionOf(argument)) return std::make_shared<Lambda>(Lambda{argument, path, env});
            if (const auto reference = std::dynamic_pointer_cast<KerML::Entities::FeatureReferenceExpression>(argument)) {
                if (const FeaturePtr referent = referentOf(*reference)) {
                    for (const Env* frame = env.get(); frame != nullptr; frame = frame->Outer.get()) {
                        for (auto it = frame->Entries.rbegin(); it != frame->Entries.rend(); ++it) {
                            if (it->first == referent.get()) return it->second.Fn;
                        }
                    }
                }
                return nullptr;
            }
            const Expression& object = *argument;
            if (typeid(object) == typeid(KerML::Entities::InstantiationExpression)) {
                // a function reference that names a parameter holding a function value (`xs->collect f`): that function value
                if (const auto reference = std::dynamic_pointer_cast<KerML::Entities::InstantiationExpression>(argument)) {
                    if (const auto named = std::dynamic_pointer_cast<Feature>(invokedTypeOf(*reference))) {
                        for (const Env* frame = env.get(); frame != nullptr; frame = frame->Outer.get()) {
                            for (auto it = frame->Entries.rbegin(); it != frame->Entries.rend(); ++it) {
                                if (it->first == named.get() && it->second.Fn) return it->second.Fn;
                            }
                        }
                    }
                }
                return std::make_shared<Lambda>(Lambda{argument, path, env});
            }
            return nullptr;
        }

        Value evaluateCall(const KerML::Entities::InvocationExpression& invocation, bool arrow, EvaluationContext& context) {
            ArgumentList list = argumentsOf(invocation);
            if (list.MissingValue) return missingArgumentValue(context);
            const TypePtr type = invokedTypeOf(invocation);
            if (!type || type->owner() == nullptr) return notBound(invocation, context);   // (an unresolved name keeps an ownerless placeholder)
            const std::vector<ArgumentRef> refs = argumentRefs(list.Values, arrow);
            // a parameter that holds a function value is called with the values of the arguments
            if (const auto feature = std::dynamic_pointer_cast<Feature>(type)) {
                if (const Bound* found = findBinding(feature.get()); found != nullptr && (found->Fn || isFunctionParameter(feature))) {
                    const std::shared_ptr<Lambda> lambda = found->Fn;   // (copied: the frames may change while the arguments are evaluated)
                    std::vector<Value> values;
                    for (const ArgumentRef& ref : refs) {
                        if (!ref.Name.empty()) return failCall(context, "a function value has no named parameters");
                        values.push_back(context.evaluate(ref.Value));
                        if (context.hasErrors()) return Value();
                    }
                    if (!lambda) return failCall(context, "the parameter '" + nameOf(feature) + "' holds no function value");
                    return callLambda(*lambda, std::move(values), context);
                }
            }
            // a call through a feature chain (`c.twice(5)`): the last feature runs at every instance that the prefix leads to
            if (const auto feature = std::dynamic_pointer_cast<Feature>(type); feature && feature->chainingFeature().size() > 1) return callThroughChain(feature->chainingFeature(), refs, context);
            return callType(type, refs, context);
        }

        Value callThroughChain(const std::vector<FeaturePtr>& chain, const std::vector<ArgumentRef>& refs, EvaluationContext& context) {
            std::vector<PathPtr> paths{Nav.contextFor(chain.front(), Current)};
            for (std::size_t index = 0; index + 1 < chain.size(); ++index) {
                std::vector<PathPtr> next;
                for (const PathPtr& path : paths) {
                    if (!targetsIn(chain[index], index == 0 ? path : Nav.contextFor(chain[index], path), context, next)) return Value();
                }
                paths = std::move(next);
            }
            std::vector<Item> items;
            for (const PathPtr& path : paths) {
                CalleeContext = path;
                const Value one = callType(chain.back(), refs, context);
                CalleeContext = nullptr;
                if (context.hasErrors()) return Value();
                items.insert(items.end(), one.items().begin(), one.items().end());
            }
            return Value(std::move(items));
        }

        SYSMLV2_COLD_PATH static Value notBound(const KerML::Entities::InvocationExpression& invocation, EvaluationContext& context) {
            if (const auto* operation = dynamic_cast<const KerML::Entities::OperatorExpression*>(&invocation))
                context.report(Severity::Error, "operator '" + operation->operatorName() + "' is not bound to a function");
            else
                context.report(Severity::Error, "the invocation is not bound to a function");
            return Value();
        }

        SYSMLV2_COLD_PATH static Value failCall(EvaluationContext& context, const std::string& message) {
            context.report(Severity::Error, message);
            return Value();
        }

        /// The first function among the types of a feature (typings and their generals).
        static std::shared_ptr<Function> typingFunctionOf(const TypePtr& type) {
            std::deque<TypePtr> queue{type};
            std::set<const KerML::Entities::Type*> visited{type.get()};
            while (!queue.empty()) {
                const TypePtr current = std::move(queue.front());
                queue.pop_front();
                if (current != type) {
                    if (auto function = std::dynamic_pointer_cast<Function>(current)) return function;
                }
                if (const auto feature = std::dynamic_pointer_cast<Feature>(current)) {
                    for (const auto& typing : feature->ownedTyping()) {
                        const auto general = typing ? typing->type() : nullptr;
                        if (general && visited.insert(general.get()).second) queue.push_back(general);
                    }
                }
            }
            return nullptr;
        }

        /// Calls a function, calculation or function-typed feature with the given arguments.
        Value callType(const TypePtr& type, const std::vector<ArgumentRef>& refs, EvaluationContext& context) {
            std::shared_ptr<Function> function = std::dynamic_pointer_cast<Function>(type);
            if (!function) function = typingFunctionOf(type);   // (a calculation usage is called through the function that types it)
            const NativeFunction* native = nullptr;
            IssueKind issue = IssueKind::None;
            if (function) {
                const CacheEntry& entry = lookup(function);
                native = entry.Match.implementation;
                if (native != nullptr && entry.Match.inherited) {
                    issue = entry.Issue;
                    if (issue == IssueKind::Body) native = nullptr;   // (a body of its own wins over the native implementation of the general)
                }
            }
            if (native != nullptr) return callNative(function, *native, issue, refs, context);
            // (a calculation usage first: it has its own result or redefines one, and walks to the calculation that types it)
            BodyOwner body = findBodyOwner(type);
            if (!body.Owner && function) body = findBodyOwner(function);
            if (!body.Owner) {
                if (function) return failCall(context, "no native implementation for " + describeFunction(function));
                if (const auto feature = std::dynamic_pointer_cast<Feature>(type); feature && isUnresolvedPlaceholder(*feature))
                    return failCall(context, "the invoked feature '" + type->declaredName().value_or("<unnamed>") + "' is unresolved (not found or not visible)");
                return failCall(context, "the invocation of '" + type->declaredName().value_or("<unnamed>") + "' is not supported: it is no function and has no result");
            }
            return runUser(type, body, refs, context);
        }

        /// Calls a native implementation: the arguments by parameter, in the order of the parameters of the function that holds it.
        Value callNative(const std::shared_ptr<Function>& function, const NativeFunction& implementation, IssueKind issue, const std::vector<ArgumentRef>& refs,
                         EvaluationContext& context) {
            std::vector<FeaturePtr> parameters = inputParameters(function);
            Arguments arguments;
            if (parameters.empty()) {
                // no parameters are declared (a hand-built model): the arguments are taken as they are
                for (const ArgumentRef& ref : refs) {
                    if (!ref.Name.empty()) return failCall(context, describeFunction(function) + ": named arguments need the declared parameters of the function");
                    arguments.push_back(ref.Value);
                }
                return call(implementation, arguments, context);
            }
            BoundArguments bound = bindArguments(parameters, refs);
            if (!bound.Error.empty()) return failCall(context, describeFunction(function) + ": " + bound.Error);
            if (issue == IssueKind::Reordered) {
                // the parameters of the function redefine those of the general in another order: the general's order is what the native
                // implementation expects
                if (const auto holder = nativeHolderOf(function)) {
                    const auto holderParameters = ownInputParameters(*holder);
                    std::vector<ExpressionPtr> reordered(holderParameters.size());
                    for (std::size_t index = 0; index < parameters.size() && index < bound.ByParameter.size(); ++index) {
                        for (const auto& alias : parameterAliases(parameters[index])) {
                            const auto found = std::find(holderParameters.begin(), holderParameters.end(), alias);
                            if (found != holderParameters.end()) reordered[static_cast<std::size_t>(found - holderParameters.begin())] = bound.ByParameter[index];
                        }
                    }
                    bound.ByParameter = std::move(reordered);
                }
            }
            while (!bound.ByParameter.empty() && !bound.ByParameter.back()) bound.ByParameter.pop_back();
            for (ExpressionPtr& argument : bound.ByParameter) {
                if (!argument) argument = emptyArgument();   // (an optional parameter in the middle that was not given)
            }
            Value result = call(implementation, bound.ByParameter, context);
            return coerceResult(std::move(result), resultKindOf(function), function, context);
        }

        /// What the declared result type of a function demands of its result (see coerceResult()).
        enum class ResultKind { Any, Real, Integer, Natural, Boolean, String };

        /// The kind of the result type of the function: the typing of its own result parameter, else that of the nearest general that
        /// has a typed one (a result type is inherited). Cached for the evaluation.
        ResultKind resultKindOf(const std::shared_ptr<Function>& function) {
            const auto cached = ResultKinds.find(function.get());
            if (cached != ResultKinds.end()) return cached->second;
            ResultKind kind = ResultKind::Any;
            std::deque<std::shared_ptr<KerML::Entities::Type>> queue{function};
            std::set<const KerML::Entities::Type*> visited{function.get()};
            bool decided = false;
            while (!queue.empty() && !decided) {
                const auto current = std::move(queue.front());
                queue.pop_front();
                for (const auto& relationship : current->ownedRelationship()) {
                    if (!dynamic_cast<KerML::Entities::ReturnParameterMembership*>(relationship.get())) continue;
                    const auto* membership = dynamic_cast<KerML::Entities::Membership*>(relationship.get());
                    const auto result = membership ? std::dynamic_pointer_cast<Feature>(membership->memberElement()) : nullptr;
                    if (!result) continue;
                    for (const auto& typing : result->ownedTyping()) {
                        const auto type = typing ? typing->type() : nullptr;
                        if (!type) continue;
                        const std::string name = qualifiedNameOf(type);
                        decided = true;
                        if (name == "ScalarValues::Real" || name == "ScalarValues::Rational") kind = ResultKind::Real;
                        else if (name == "ScalarValues::Integer") kind = ResultKind::Integer;
                        else if (name == "ScalarValues::Natural") kind = ResultKind::Natural;
                        else if (name == "ScalarValues::Boolean") kind = ResultKind::Boolean;
                        else if (name == "ScalarValues::String") kind = ResultKind::String;
                        else kind = ResultKind::Any;
                        break;
                    }
                }
                for (const auto& specialization : current->ownedSpecialization()) {
                    const auto general = specialization ? specialization->general() : nullptr;
                    if (general && visited.insert(general.get()).second) queue.push_back(general);
                }
            }
            ResultKinds.emplace(function.get(), kind);
            return kind;
        }

        /// The one rule for the result of a function, native or user: a declared Real or Rational promotes Integers to Reals (`RealFunctions::'+'`
        /// gives 3.0 for 1 and 2); a declared Integer or Natural takes an integral Real as an Integer and refuses any other number; a
        /// declared Boolean or String refuses another kind. Untyped results and other types stay as they are.
        Value coerceResult(Value value, ResultKind kind, const std::shared_ptr<Function>& function, EvaluationContext& context) {
            if (kind == ResultKind::Any || value.isNull() || context.hasErrors()) return value;
            switch (kind) {
                case ResultKind::Real: {
                    bool any = false;
                    for (const Item& item : value.items()) any = any || std::holds_alternative<std::int64_t>(item);
                    if (!any) return value;
                    std::vector<Item> items;
                    items.reserve(value.size());
                    for (const Item& item : value.items()) {
                        if (const auto* integer = std::get_if<std::int64_t>(&item)) items.emplace_back(std::in_place_type<double>, static_cast<double>(*integer));
                        else items.push_back(item);
                    }
                    return Value(std::move(items));
                }
                case ResultKind::Natural:
                    for (const Item& item : value.items()) {
                        const auto* integer = std::get_if<std::int64_t>(&item);
                        const auto* real = std::get_if<double>(&item);
                        if ((integer && *integer < 0) || (real && *real < 0.0)) return failCall(context, describeFunction(function) + ": the result " + Value(Item(item)).toString() + " is no Natural");
                    }
                    [[fallthrough]];
                case ResultKind::Integer: {
                    std::vector<Item> items;
                    items.reserve(value.size());
                    for (const Item& item : value.items()) {
                        if (const auto* real = std::get_if<double>(&item)) {
                            if (std::isfinite(*real) && *real >= -9223372036854775808.0 && *real < 9223372036854775808.0 && std::trunc(*real) == *real) {
                                items.emplace_back(std::in_place_type<std::int64_t>, static_cast<std::int64_t>(*real));
                                continue;
                            }
                            return failCall(context, describeFunction(function) + ": the result " + Value::real(*real).toString() + " is no Integer");
                        }
                        items.push_back(item);
                    }
                    return Value(std::move(items));
                }
                case ResultKind::Boolean:
                    for (const Item& item : value.items()) {
                        if (!std::holds_alternative<bool>(item)) return failCall(context, describeFunction(function) + ": the result is no Boolean");
                    }
                    return value;
                case ResultKind::String:
                    for (const Item& item : value.items()) {
                        if (!std::holds_alternative<std::string>(item)) return failCall(context, describeFunction(function) + ": the result is no String");
                    }
                    return value;
                case ResultKind::Any:
                    break;
            }
            return value;
        }

        /// The nearest general of a function that holds a native implementation.
        std::shared_ptr<KerML::Entities::Type> nativeHolderOf(const std::shared_ptr<Function>& function) {
            std::deque<std::shared_ptr<KerML::Entities::Type>> queue{function};
            std::set<const KerML::Entities::Type*> visited{function.get()};
            while (!queue.empty()) {
                const auto current = std::move(queue.front());
                queue.pop_front();
                if (current != function && Registry->find(qualifiedNameOf(*current)) != nullptr) return current;
                for (const auto& specialization : current->ownedSpecialization()) {
                    const auto general = specialization ? specialization->general() : nullptr;
                    if (general && visited.insert(general.get()).second) queue.push_back(general);
                }
            }
            return nullptr;
        }

        static ExpressionPtr emptyArgument() {
            static const ExpressionPtr empty = std::make_shared<KerML::Entities::NullExpression>();
            return empty;
        }

        /// The value expression of a parameter that is used if no argument is given (its own, or that of a parameter it redefines).
        static ExpressionPtr defaultOf(const FeaturePtr& parameter) {
            for (const auto& alias : parameterAliases(parameter)) {
                if (ExpressionPtr value = featureValueExpression(alias)) return value;
            }
            return nullptr;
        }

        static bool isFunctionParameter(const FeaturePtr& parameter) { return dynamic_cast<Expression*>(parameter.get()) != nullptr; }

        static Bound* findOwn(Env& env, const Feature* feature) {
            for (auto it = env.Entries.rbegin(); it != env.Entries.rend(); ++it) {
                if (it->first == feature) return &it->second;
            }
            return nullptr;
        }

        /// Makes @p env the running frame and @p path the current path, for the lifetime of the guard.
        struct FrameGuard {
            Run& Owner;
            PathPtr SavedPath;
            EnvPtr SavedEnv;
            std::size_t SavedFrame;
            FrameGuard(Run& owner, EnvPtr env, PathPtr path) : Owner(owner), SavedPath(owner.Current), SavedEnv(owner.CurrentEnv), SavedFrame(owner.Frame) {
                owner.Frame = env ? env->Id : 0;
                owner.CurrentEnv = std::move(env);
                owner.Current = std::move(path);
            }
            ~FrameGuard() {
                Owner.Current = std::move(SavedPath);
                Owner.CurrentEnv = std::move(SavedEnv);
                Owner.Frame = SavedFrame;
            }
            FrameGuard(const FrameGuard&) = delete;
            FrameGuard& operator=(const FrameGuard&) = delete;
        };

        /// The path of the frame of a callee: a callee that is owned by a type (a calculation of a part) continues the path of the caller
        /// at the instance that features it, so that its body sees the features of that instance; any other callee starts a path.
        PathPtr calleePath(const TypePtr& callee, const PathPtr& callerPath) {
            PathPtr parent;
            if (callerPath && std::dynamic_pointer_cast<KerML::Entities::Type>(callee->owner()) && !std::dynamic_pointer_cast<Expression>(callee->owner())) {
                const auto feature = std::dynamic_pointer_cast<Feature>(callee);
                parent = feature ? Nav.contextFor(feature, callerPath) : callerPath;
            }
            return std::make_shared<const Path>(Path{callee, parent});
        }

        /// Runs the body of a function or calculation: the arguments are evaluated where the call is written, then bound to the
        /// parameters (and to the parameters they redefine) in a new frame (all of them: a parameter without an argument is bound to
        /// the empty sequence and hides what the frames outside have bound), then the result is evaluated in the frame.
        Value runUser(const TypePtr& callee, const BodyOwner& body, const std::vector<ArgumentRef>& refs, EvaluationContext& context) {
            const PathPtr instance = std::move(CalleeContext);   // (set by a call through a chain, for this call only)
            CalleeContext = nullptr;
            const auto depth = context.enterCall();
            if (!depth) return Value();
            const std::vector<FeaturePtr> parameters = inputParameters(callee);
            const BoundArguments bound = bindArguments(parameters, refs);
            const std::string name = describeType(callee);
            if (!bound.Error.empty()) return failCall(context, name + ": " + bound.Error);
            std::vector<ExpressionPtr> defaults(parameters.size());
            for (std::size_t index = 0; index < parameters.size(); ++index) {
                if (bound.ByParameter[index]) continue;
                defaults[index] = defaultOf(parameters[index]);
                if (!defaults[index] && isRequiredParameter(parameters[index])) return failCall(context, name + ": missing argument for parameter '" + nameOf(parameters[index]) + "'");
            }
            // the arguments are evaluated at the call, in the caller's frame (a parameter that holds a function value gets the lambda)
            const EnvPtr callerEnv = CurrentEnv;
            const PathPtr callerPath = Current;
            auto env = std::make_shared<Env>();
            env->Id = ++FrameCounter;
            std::vector<Bound> bounds(parameters.size());
            for (std::size_t index = 0; index < parameters.size(); ++index) {
                if (!bound.ByParameter[index]) continue;
                // a body expression, a function reference or a function value of the caller is passed on as one, also to a parameter that is not
                // declared as a function (`in f[0..*]`)
                if (isFunctionParameter(parameters[index])) {
                    bounds[index].Fn = lambdaOf(bound.ByParameter[index], callerEnv, callerPath);
                    if (!bounds[index].Fn) return failCall(context, name + ": the argument for '" + nameOf(parameters[index]) + "' is no function value");
                } else if (auto function = lambdaOf(bound.ByParameter[index], callerEnv, callerPath)) {
                    bounds[index].Fn = std::move(function);
                } else {
                    bounds[index].Val = context.evaluate(bound.ByParameter[index]);
                    if (context.hasErrors()) return Value();
                }
            }
            for (std::size_t index = 0; index < parameters.size(); ++index) {
                for (const auto& alias : parameterAliases(parameters[index])) env->Entries.emplace_back(alias.get(), bounds[index]);
            }
            FrameGuard guard(*this, env, calleePath(callee, instance ? instance : callerPath));
            const auto target = context.enterTarget(callee);
            // the defaults may refer to the parameters before them
            for (std::size_t index = 0; index < parameters.size(); ++index) {
                if (!defaults[index]) continue;
                Value value = context.evaluate(defaults[index]);
                if (context.hasErrors()) return Value();
                for (const auto& alias : parameterAliases(parameters[index])) {
                    if (Bound* entry = findOwn(*env, alias.get())) entry->Val = value;
                }
            }
            Value result = context.evaluate(body.Result.value());
            auto function = std::dynamic_pointer_cast<Function>(callee);
            if (!function) function = typingFunctionOf(callee);
            return function ? coerceResult(std::move(result), resultKindOf(function), function, context) : result;
        }

        static std::string describeType(const TypePtr& type) {
            const std::string name = qualifiedNameOf(type);
            return name.empty() ? type->declaredName().value_or("<unnamed>") : name;
        }

        /// Calls the function value that an expression stands for (see EvaluationContext::invokeFunctionValue()), written at the
        /// current frame.
        Value callCallable(const ExpressionPtr& callable, const PathPtr& definedAt, std::vector<Value> arguments, EvaluationContext& context) {
            const std::shared_ptr<Lambda> lambda = lambdaOf(callable, CurrentEnv, definedAt);
            if (!lambda) return failCall(context, "the expression is not a function value");
            return callLambda(*lambda, std::move(arguments), context);
        }

        /// Calls a function value: a body expression runs in a frame that encloses the one where it was written; a function reference
        /// calls the function.
        Value callLambda(const Lambda& lambda, std::vector<Value> arguments, EvaluationContext& context) {
            if (const ExpressionPtr body = bodyExpressionOf(lambda.Body)) {
                const auto depth = context.enterCall();
                if (!depth) return Value();
                return callBody(body, lambda, std::move(arguments), context);
            }
            // a function reference (`reduce min`): an InstantiationExpression that names the function
            const Expression& object = *lambda.Body;
            if (const auto* instantiation = dynamic_cast<const KerML::Entities::InstantiationExpression*>(lambda.Body.get());
                instantiation != nullptr && typeid(object) == typeid(KerML::Entities::InstantiationExpression)) {
                if (const Direct* direct = directCallOf(*instantiation)) {
                    // a native function that takes values: called with the values, without an expression for each of them
                    Value result = callStrict(*direct->Strict, std::move(arguments), context);
                    return coerceResult(std::move(result), direct->Kind, direct->Callee, context);
                }
                if (const TypePtr type = invokedTypeOf(*instantiation)) {
                    std::vector<ArgumentRef> refs;
                    for (Value& value : arguments) refs.push_back(ArgumentRef{std::make_shared<ConstantExpression>(std::move(value)), {}});
                    FrameGuard guard(*this, CurrentEnv, lambda.Where ? lambda.Where : Current);
                    return callType(type, refs, context);
                }
            }
            return failCall(context, "the expression is not a function value");
        }

        /// A function reference whose function is a native one that takes values (`reduce '+'`): what a call needs, found once per
        /// evaluation.
        struct Direct {
            const StrictFunction* Strict = nullptr;
            std::shared_ptr<Function> Callee;
            ResultKind Kind = ResultKind::Any;
        };

        const Direct* directCallOf(const KerML::Entities::InstantiationExpression& reference) {
            const auto found = Directs.find(&reference);
            if (found != Directs.end()) return found->second.Strict ? &found->second : nullptr;
            Direct direct;
            if (const TypePtr type = invokedTypeOf(reference)) {
                if (const auto function = std::dynamic_pointer_cast<Function>(type)) {
                    const CacheEntry& entry = lookup(function);
                    // (no issue: the function runs the native implementation as it is, with the arguments in order)
                    if (entry.Match.strict != nullptr && entry.Issue == IssueKind::None) {
                        direct.Strict = entry.Match.strict;
                        direct.Callee = function;
                        direct.Kind = resultKindOf(function);
                    }
                }
            }
            return Directs.emplace(&reference, std::move(direct)).first->second.Strict ? &Directs.find(&reference)->second : nullptr;
        }

        /// Calls a native function with the values of its arguments; an exception becomes an Error.
        static Value callStrict(const StrictFunction& implementation, std::vector<Value> arguments, EvaluationContext& context) {
            try {
                return implementation(context, std::move(arguments));
            } catch (const std::exception& error) {
                reportException(context, error.what());
            } catch (...) {
                reportException(context, "unknown exception");
            }
            return Value();
        }

        /// Calls a body expression `{ in x; x + 1 }`: the parameters are bound to the arguments (all of them), `that` is the first argument.
        Value callBody(const ExpressionPtr& body, const Lambda& lambda, std::vector<Value> arguments, EvaluationContext& context) {
            const std::vector<FeaturePtr> parameters = ownInputParameters(*body);
            const OwnResult result = ownResultOf(*body);
            if (!result) return failCall(context, "the body expression has no result");
            if (!parameters.empty() && arguments.size() > parameters.size()) return failCall(context, "too many arguments for the body expression");
            auto env = std::make_shared<Env>();
            env->Id = ++FrameCounter;
            env->Outer = lambda.Scope;
            env->That = arguments.empty() ? Value() : arguments.front();
            for (std::size_t index = 0; index < parameters.size(); ++index) {
                Bound entry;
                if (index < arguments.size()) entry.Val = arguments[index];
                for (const auto& alias : parameterAliases(parameters[index])) env->Entries.emplace_back(alias.get(), entry);
            }
            FrameGuard guard(*this, env, lambda.Where ? lambda.Where : Current);
            const auto target = context.enterTarget(Current ? Current->Element : nullptr);
            return context.evaluate(result.value());
        }

        SYSMLV2_COLD_PATH static Value noImplementation(const KerML::Entities::OperatorExpression& operation, const std::shared_ptr<Function>& function,
                                                        EvaluationContext& context) {
            const std::string name = "operator '" + operation.operatorName() + "'";
            if (function) {
                context.report(Severity::Error, "no native implementation for " + describeFunction(function) + " (" + name + ")");
            } else if (const char* functionName = KerML::operatorFunctionName(operation.operatorName())) {
                context.report(Severity::Error, std::string("no native implementation for ") + functionName + " (" + name + ")");
            } else {
                context.report(Severity::Error, name + " is not bound to a function");
            }
            return Value();
        }

        /// Calls a native function; an exception becomes an Error at the current expression.
        static Value call(const NativeFunction& implementation, const Arguments& arguments, EvaluationContext& context) {
            try {
                return implementation(context, arguments);
            } catch (const std::exception& error) {
                reportException(context, error.what());
            } catch (...) {
                reportException(context, "unknown exception");
            }
            return Value();
        }

        SYSMLV2_COLD_PATH static void reportException(EvaluationContext& context, const char* what) noexcept {
            try {
                context.report(Severity::Error, std::string("exception in a native function: ") + what);
            } catch (...) {
                context.markFailed();   // (out of memory: no diagnostic, but the result must not look successful)
            }
        }

        // (a shared copy: a native function may replace the registry of the evaluator while it runs)
        const std::shared_ptr<const FunctionRegistry> Registry;
        EvaluationContext Context;
        Navigation Nav;
        struct ActiveBinding {
            FeaturePtr Binding;
            PathPtr Where;
            std::size_t FrameId;
        };
        std::vector<ActiveBinding> Active;                    // (binding, path, call frame) being evaluated: cycle detection (not recursion)
        PathPtr Current;                                      // the path the expression that is evaluated belongs to
        std::unordered_map<const Feature*, int> Special;
        PathPtr CalleeContext;                                    // the instance of the next user call (see callThroughChain)
        EnvPtr CurrentEnv;                                        // the call frame that is running (null: the top)
        std::size_t FrameCounter = 0;
        std::size_t Frame = 0;                                    // the call frame that is running (0: the top)
        std::set<const Feature*> Warned;
        std::set<const Feature*> WarnedEmpty;
        std::set<const Feature*> Skipped;                         // subsetters left out of a nested evaluation of their feature
        std::unordered_map<const Function*, CacheEntry> Cache;
        std::unordered_map<const Function*, ResultKind> ResultKinds;
        std::unordered_map<const KerML::Entities::InstantiationExpression*, Direct> Directs;
    };

    }   // namespace

    struct Evaluator::Impl {
        Impl(FunctionRegistry registry, EvaluationOptions options)
            : Registry(std::make_shared<const FunctionRegistry>(std::move(registry))), Options(options) {}

        std::shared_ptr<const FunctionRegistry> Registry;
        EvaluationOptions Options;

        /// The limits that a stack of the given size allows: the depth of the nesting of expressions (about 1.3 KB per level
        /// unoptimized) and of calls (about 5.2 KB per call), both with a safety factor of 2, and at most what the options say.
        struct Limits {
            std::size_t Depth, Calls;
        };

        // The measured cost (GCC -O0, 1.3 KB per level of expression and 5.2 KB per call) times a safety factor of 2; where frames are
        // larger and that was not measured (MSVC Debug, AddressSanitizer) 4.
#if defined(__SANITIZE_ADDRESS__)
        static constexpr std::size_t SafetyFactor = 4;
#elif defined(__has_feature)
#if __has_feature(address_sanitizer)
        static constexpr std::size_t SafetyFactor = 4;
#elif defined(_MSC_VER) && defined(_DEBUG)
        static constexpr std::size_t SafetyFactor = 4;
#else
        static constexpr std::size_t SafetyFactor = 2;
#endif
#elif defined(_MSC_VER) && defined(_DEBUG)
        static constexpr std::size_t SafetyFactor = 4;
#else
        static constexpr std::size_t SafetyFactor = 2;
#endif

        Limits limitsFor(std::size_t stackBytes) const {
            const std::size_t depth = std::max<std::size_t>(stackBytes / (SafetyFactor * 1300), 8);
            const std::size_t calls = std::max<std::size_t>(stackBytes / (SafetyFactor * 5200), 1);
            return Limits{std::min(Options.maxDepth, depth), Options.maxCallDepth != 0 ? std::min(Options.maxCallDepth, calls) : calls};
        }

        /// Runs @p evaluation (a function of a Run that gives the Result) on the stack of the caller, and again on a large stack if it
        /// reached a limit that a larger stack would raise.
        template <class Evaluation>
        Result perform(Evaluation&& evaluation) const noexcept {
            try {
                // (with a large stack to switch to, the limits are those of that stack whatever the caller has, so that the outcome does
                // not depend on the stack of the caller; the run is repeated there if the caller's stack is too small)
                Limits inlineLimits = limitsFor(inlineStackBytes());
                const Limits large = Options.stackSize != 0 ? limitsFor(Options.stackSize) : inlineLimits;
                inlineLimits.Depth = std::min(inlineLimits.Depth, large.Depth);
                inlineLimits.Calls = std::min(inlineLimits.Calls, large.Calls);
                {
                    Run run(Registry, Options, inlineLimits.Depth, inlineLimits.Calls);
                    Result result = evaluation(run);
                    if (!run.limitReached() || Options.stackSize == 0) return result;
                    // (only a limit that the large stack raises: not one that the options set)
                    if (!((run.depthLimitHit() && inlineLimits.Depth < large.Depth) || (run.callLimitHit() && inlineLimits.Calls < large.Calls))) return result;
                    Result again;
                    bool done = false;
                    const std::size_t obtained = runOnStack(Options.stackSize, [&] {
                        try {
                            // (the stack that was asked for, or, if the system gave less, what it gave)
                            const std::size_t measured = remainingStackBytes();
                            const Limits limits = (measured == 0 || measured + (std::size_t(256) << 10) >= Options.stackSize) ? large : limitsFor(inlineStackBytes());
                            Run second(Registry, Options, limits.Depth, limits.Calls);
                            again = evaluation(second);
                            done = true;
                        } catch (...) {
                            again = failure("Unexpected exception while evaluating.");
                            done = true;
                        }
                    });
                    return obtained != 0 && done ? again : result;
                }
            } catch (...) {
                return failure("Unexpected exception while evaluating.");
            }
        }

        /// An Error result for a problem before or outside the evaluation. Never throws; if the message cannot be stored the result is
        /// marked failed.
        Result runFeature(const FeaturePtr& feature, const std::shared_ptr<Element>& target) const noexcept {
            return perform([&](Run& run) { return run.executeFeature(feature, target); });
        }

        static Result failure(const char* message) noexcept {
            Result result;
            result.failed = true;
            try {
                result.diagnostics.push_back(Diagnostic{Severity::Error, message, nullptr});
            } catch (...) {
            }
            return result;
        }

        Result run(const ExpressionPtr& expression, const std::shared_ptr<Element>& target) const noexcept {
            return perform([&](Run& run) { return run.execute(expression, target); });
        }
    };

    Evaluator::Evaluator(FunctionRegistry registry, EvaluationOptions options)
        : Data(std::make_unique<Impl>(std::move(registry), options)) {}

    Evaluator::~Evaluator() = default;
    Evaluator::Evaluator(Evaluator&& other) noexcept = default;
    Evaluator& Evaluator::operator=(Evaluator&& other) noexcept = default;

    Result Evaluator::evaluate(const std::shared_ptr<KerML::Entities::Expression>& expression, const std::shared_ptr<KerML::Entities::Element>& target) const {
        try {
            if (!Data) return Impl::failure("Cannot evaluate with a moved-from evaluator.");
            if (!expression) {
                Result result;
                result.diagnostics.push_back(Diagnostic{Severity::Error, "Cannot evaluate a missing expression.", nullptr});
                return result;
            }
            return Data->run(expression, target);
        } catch (...) {
            return Impl::failure("Unexpected exception while evaluating.");
        }
    }

    Result Evaluator::evaluateFeatureValue(const std::shared_ptr<KerML::Entities::Feature>& feature, const std::shared_ptr<KerML::Entities::Element>& target) const {
        try {
            if (!Data) return Impl::failure("Cannot evaluate with a moved-from evaluator.");
            if (!feature) {
                Result result;
                result.diagnostics.push_back(Diagnostic{Severity::Error, "Cannot evaluate a missing feature.", nullptr});
                return result;
            }
            // (through the effective binding, so that cycles of values are noticed; without a target that is the feature's own value)
            // A feature that is an expression itself (`constraint x { ... }`, `calc x { ... }`) and has no feature value is evaluated as such.
            if (!featureValueExpression(feature)) {
                if (const auto self = std::dynamic_pointer_cast<Expression>(feature)) return evaluate(self, target);
            }
            return Data->runFeature(feature, target);   // (through the effective binding: a redefinition without a value has the inherited one)
        } catch (...) {
            return Impl::failure("Unexpected exception while evaluating.");
        }
    }

    const FunctionRegistry& Evaluator::registry() const {
        static const FunctionRegistry empty;
        return Data ? *Data->Registry : empty;
    }

    void Evaluator::setRegistry(FunctionRegistry registry) {
        if (!Data) Data = std::make_unique<Impl>(std::move(registry), EvaluationOptions());
        else Data->Registry = std::make_shared<const FunctionRegistry>(std::move(registry));
    }

    const EvaluationOptions& Evaluator::options() const {
        static const EvaluationOptions defaults;
        return Data ? Data->Options : defaults;
    }
}
