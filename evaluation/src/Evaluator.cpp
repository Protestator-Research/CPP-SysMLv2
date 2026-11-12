#include <sysmlv2/evaluation/Evaluator.h>
#include <sysmlv2/evaluation/QualifiedName.h>

#include "Arguments.h"
#include "CompilerSupport.h"
#include "Navigation.h"

#include <kerml/core/features/FeatureChaining.h>
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

        // Named arguments -----------------------------------------------------------------------------------------------------

        /// The parameter feature that holds the value of an argument of a plain invocation: the owner, or the owner of its
        /// FeatureValue, if that is exactly a Feature (null otherwise).
        std::shared_ptr<Feature> parameterOf(const ExpressionPtr& argument) {
            std::shared_ptr<Element> holder = argument->owner();
            if (std::dynamic_pointer_cast<KerML::Entities::FeatureValue>(holder)) holder = holder->owner();
            if (!holder) return nullptr;
            const Element& element = *holder;
            if (typeid(element) != typeid(Feature)) return nullptr;
            return std::dynamic_pointer_cast<Feature>(holder);
        }

        std::string nameOf(const std::shared_ptr<Feature>& feature);

        /// The names of the parameters that the parameter feature redefines (`F(y = 1)` makes a parameter that redefines `y`). The
        /// listeners do not add implicit redefinitions to the parameters of positional arguments (the model has no isImplied flag to
        /// tell them apart), so any redefinition marks the argument as named.
        std::vector<std::string> redefinedNames(const std::shared_ptr<Feature>& parameter) {
            std::vector<std::string> names;
            for (const auto& redefinition : parameter->ownedRedefinition()) {
                const auto redefined = redefinition ? redefinition->redefinedFeature() : nullptr;
                names.push_back(nameOf(redefined));
            }
            return names;
        }

        /// An argument of the form `name = value`: of a plain invocation (see parameterOf) or, for the arrow form, a plain Expression
        /// that carries the name.
        bool isNamedArgument(const ExpressionPtr& argument) {
            if (!argument) return false;
            if (const auto parameter = parameterOf(argument)) return !parameter->ownedRedefinition().empty();
            const Expression& expression = *argument;
            return typeid(expression) == typeid(Expression) && argument->declaredName().has_value();
        }

        /// True if one of the arguments from @p first on is named. (The first argument of `x->F(...)` is the left operand.)
        bool hasNamedArguments(const Arguments& arguments, std::size_t first) {
            for (std::size_t index = first; index < arguments.size(); ++index) {
                if (isNamedArgument(arguments[index])) return true;
            }
            return false;
        }

        /// The name of a feature for matching: the effective name (a parameter `in :>> x` has none of its own and is known by the
        /// feature it redefines), else the declared name; empty if there is none.
        std::string nameOf(const std::shared_ptr<Feature>& feature) {
            if (!feature) return {};
            if (const auto effective = feature->effectiveName(); effective && !effective->empty()) return *effective;
            return feature->declaredName().value_or(std::string());
        }

        /// The input parameters that a type owns itself, in order. (The parameters of a library function are owned through a
        /// FeatureMembership in the text and in the XMI model; an input parameter has a direction that is not out.)
        std::vector<std::shared_ptr<Feature>> ownInputParameters(const KerML::Entities::Type& type) {
            std::vector<std::shared_ptr<Feature>> parameters;
            for (const auto& relationship : type.ownedRelationship()) {
                if (!relationship || !dynamic_cast<KerML::Entities::FeatureMembership*>(relationship.get()) ||
                    dynamic_cast<KerML::Entities::ReturnParameterMembership*>(relationship.get()))
                    continue;
                const auto* membership = dynamic_cast<KerML::Entities::Membership*>(relationship.get());
                const auto parameter = membership ? std::dynamic_pointer_cast<Feature>(membership->memberElement()) : nullptr;
                if (!parameter) continue;
                const auto direction = parameter->direction();
                if (!direction || *direction == KerML::Entities::OUT) continue;
                parameters.push_back(parameter);
            }
            return parameters;
        }

        /// The input parameters of a function in order: its own, else those of the nearest general that has some.
        std::vector<std::shared_ptr<Feature>> inputParameters(const std::shared_ptr<Function>& function) {
            std::deque<std::shared_ptr<KerML::Entities::Type>> queue{function};
            std::set<const KerML::Entities::Type*> visited{function.get()};
            while (!queue.empty()) {
                const std::shared_ptr<KerML::Entities::Type> current = std::move(queue.front());
                queue.pop_front();
                auto parameters = ownInputParameters(*current);
                if (!parameters.empty()) return parameters;
                for (const auto& specialization : current->ownedSpecialization()) {
                    const auto general = specialization ? specialization->general() : nullptr;
                    if (general && visited.insert(general.get()).second) queue.push_back(general);
                }
            }
            return {};
        }

        /// Why the native implementation of a general must not be used for a function that specializes it ("" if it may): the function
        /// has a body of its own (a result expression, or an owned feature that is not an input parameter and has a value, such as a
        /// result parameter `return = a * b;` or `out :>> result = a * b;`), or one of its input parameters redefines a parameter of
        /// its general at another position (`in a :>> y;` as the first parameter), so that the native function would receive the
        /// arguments in the wrong order. Library specializations without a body that redefine positionally are fine. Checks one level.
        std::string functionIssue(const std::shared_ptr<Function>& function) {
            for (const auto& relationship : function->ownedRelationship()) {
                if (!relationship) continue;
                if (dynamic_cast<KerML::Entities::ResultExpressionMembership*>(relationship.get())) return "has a body of its own";
                if (!dynamic_cast<KerML::Entities::FeatureMembership*>(relationship.get())) continue;
                const auto* membership = dynamic_cast<KerML::Entities::Membership*>(relationship.get());
                const auto owned = membership ? std::dynamic_pointer_cast<Feature>(membership->memberElement()) : nullptr;
                if (!owned) continue;
                const auto direction = owned->direction();
                if (direction && *direction != KerML::Entities::OUT) continue;   // (an input parameter)
                if (featureValueExpression(owned)) return "has a result expression of its own";
            }
            const auto own = ownInputParameters(*function);
            for (std::size_t index = 0; index < own.size(); ++index) {
                for (const auto& redefinition : own[index]->ownedRedefinition()) {
                    const auto redefined = redefinition ? redefinition->redefinedFeature() : nullptr;
                    const auto general = redefined ? std::dynamic_pointer_cast<KerML::Entities::Type>(redefined->owner()) : nullptr;
                    if (!general) continue;
                    const auto parameters = ownInputParameters(*general);
                    for (std::size_t position = 0; position < parameters.size(); ++position) {
                        if (parameters[position] == redefined && position != index) return "redefines the parameters of its general in another order";
                    }
                }
            }
            return {};
        }

        /// The issue (see functionIssue) of the function or of any function between it and the generals that hold the native
        /// implementation (all paths; the holders themselves and what lies above them are not checked). "" if there is none.
        std::string inheritedImplementationIssue(const std::shared_ptr<Function>& function, const FunctionRegistry& registry) {
            std::deque<std::shared_ptr<KerML::Entities::Type>> queue{function};
            std::set<const KerML::Entities::Type*> visited{function.get()};
            while (!queue.empty()) {
                const std::shared_ptr<KerML::Entities::Type> current = std::move(queue.front());
                queue.pop_front();
                if (current != function && registry.find(qualifiedNameOf(*current)) != nullptr) continue;   // (a holder)
                if (const auto currentFunction = std::dynamic_pointer_cast<Function>(current)) {
                    if (std::string issue = functionIssue(currentFunction); !issue.empty()) {
                        return current == function ? issue : issue + " (" + describeFunction(currentFunction) + ", between it and the native implementation)";
                    }
                }
                for (const auto& specialization : current->ownedSpecialization()) {
                    const auto general = specialization ? specialization->general() : nullptr;
                    if (general && visited.insert(general.get()).second) queue.push_back(general);
                }
            }
            return {};
        }

        /// Puts the named arguments of a plain invocation in the order of the parameters of the function. False if that is not
        /// unambiguous (not every argument is named, a name is not a parameter of the function or is used twice, or the named
        /// parameters are not the first ones).
        bool orderNamedArguments(const std::shared_ptr<Function>& function, Arguments& arguments) {
            const auto parameters = inputParameters(function);
            Arguments ordered(arguments.size());
            std::vector<bool> placed(arguments.size(), false);
            for (const ExpressionPtr& argument : arguments) {
                const auto holder = parameterOf(argument);
                if (!holder) return false;
                const auto names = redefinedNames(holder);
                if (names.size() != 1 || names.front().empty()) return false;
                std::size_t position = parameters.size();
                for (std::size_t index = 0; index < parameters.size(); ++index) {
                    if (nameOf(parameters[index]) == names.front()) position = index;
                }
                if (position >= arguments.size() || placed[position]) return false;
                placed[position] = true;
                ordered[position] = argument;
            }
            arguments = std::move(ordered);
            return true;
        }
    }

    namespace {
    // The state of one evaluate call: the context, the options and the lookup cache. Nothing of it outlives the call, so a change of
    // the model between two calls (a library loaded, generals resolved in place) is always seen.
    class Run {
    public:
        Run(std::shared_ptr<const FunctionRegistry> registry, const EvaluationOptions& options) : Registry(std::move(registry)) {
            Context.setMaxDepth(options.maxDepth);
            Context.setMaxSequenceLength(options.maxSequenceLength);
            Context.setExpressionEvaluator([this](const ExpressionPtr& current, EvaluationContext& running) { return dispatch(current, running); });
        }

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
            std::string Issue;                 // (why an inherited implementation must not be used, see inheritedImplementationIssue)
        };

        /// registry.lookup() through the per-call cache.
        const CacheEntry& lookup(const std::shared_ptr<Function>& function) {
            const auto found = Cache.find(function.get());
            if (found != Cache.end()) return found->second;
            CacheEntry entry{function, Registry->lookup(function), {}};
            if (entry.Match.implementation != nullptr && entry.Match.inherited) entry.Issue = inheritedImplementationIssue(function, *Registry);
            return Cache.emplace(function.get(), std::move(entry)).first->second;
        }

        /// The native implementation of a function; null if there is none, or if it is inherited and does not apply to the function
        /// (then an Error has been reported and @p reported is set).
        SYSMLV2_COLD_PATH const NativeFunction* implementationOf(const std::shared_ptr<Function>& function, EvaluationContext& context, bool& reported) {
            const CacheEntry& entry = lookup(function);
            if (entry.Match.implementation != nullptr && !entry.Issue.empty()) {
                context.report(Severity::Error, "not supported yet: " + describeFunction(function) + " specializes a function with a native implementation but " + entry.Issue);
                reported = true;
                return nullptr;
            }
            return entry.Match.implementation;
        }

        /// The hook of EvaluationContext::evaluate(): one expression, already counted as a level of depth and as the current element.
        Value dispatch(const ExpressionPtr& expression, EvaluationContext& context) {
            Expression* const raw = expression.get();
            if (auto* operation = dynamic_cast<KerML::Entities::OperatorExpression*>(raw)) {
                // (the subclasses of the operator expression first)
                if (auto* chain = dynamic_cast<KerML::Entities::FeatureChainExpression*>(operation)) return evaluateChain(*chain, context);
                if (dynamic_cast<KerML::Entities::IndexExpression*>(operation) || dynamic_cast<KerML::Entities::SelectExpression*>(operation) ||
                    dynamic_cast<KerML::Entities::CollectExpression*>(operation))
                    return unsupported(context, *expression);
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
                context.report(Severity::Error, "not supported yet: Expression");
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
        Value valueIn(const FeaturePtr& feature, const PathPtr& path, EvaluationContext& context) {
            if (const Value* bound = context.binding(feature.get())) return *bound;
            if (const int kind = specialKind(feature)) {
                if (kind == SelfKind && path) return Value::element(path->Element);
                context.report(Severity::Error, kind == SelfKind ? "'self' has no target in this evaluation" : "'that' is not bound here");
                return Value();
            }
            const Resolution resolution = Nav.resolve(feature, path ? path->Element : nullptr);
            if (!resolution.Ambiguity.empty()) {
                context.report(Severity::Error, resolution.Ambiguity);
                return Value();
            }
            if (!resolution.Value) {
                // no value: a part, an action, an enumeration literal, ... is the element it denotes, an attribute has the empty sequence
                const FeaturePtr effective = resolution.Effective ? resolution.Effective : feature;
                return Nav.denotesElement(effective) ? Value::element(effective) : Value();
            }
            warnIfOverriding(resolution, context);
            return evaluateBinding(resolution.Binding, resolution.Value, path, context);
        }

        /// The paths a feature stands for at a path, to navigate into: the elements of its value, or, if it has no value, the feature that
        /// is effective there, entered at the path (so that references in its value find the outer instance). False after an Error.
        bool targetsIn(const FeaturePtr& feature, const PathPtr& path, EvaluationContext& context, std::vector<PathPtr>& out) {
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
            if (resolution.Value) {
                warnIfOverriding(resolution, context);
                // the value expression is navigated, not evaluated: a reference to a part (`ref part driverSeat : Seat = seat;`) keeps the
                // instance it is found in, which a plain element value would lose
                return withBinding(resolution.Binding, path, context, [&] { return targetsOfExpression(resolution.Value, context, out); });
            }
            // (a feature of a type is entered through the instance that features it; a feature of a package starts a new path)
            const FeaturePtr effective = resolution.Effective ? resolution.Effective : feature;
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
                if (Active[index].first.get() == binding.get() && samePath(Active[index].second, path)) {
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
            Active.emplace_back(binding, path);
            Guard guard{*this, Current};
            Current = path;
            const auto scope = context.enterTarget(path ? path->Element : nullptr);
            return action();
        }

        SYSMLV2_COLD_PATH void reportCycle(std::size_t first, const FeaturePtr& again, EvaluationContext& context) {
            std::string path;
            for (std::size_t index = first; index < Active.size(); ++index) path += describeFeature(Active[index].first) + " -> ";
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
            context.report(Severity::Error, "not supported yet: " + expression.getType());
            return Value();
        }

        /// The implementation of an operator expression (nullptr if there is none). Not inlined: it is only the setup of a call and its
        /// locals must not add to the frame of evaluateOperator, which is on the recursion path.
        SYSMLV2_COLD_PATH const NativeFunction* resolveOperator(const KerML::Entities::OperatorExpression& operation, std::shared_ptr<Function>& function,
                                                                EvaluationContext& context, bool& reported) {
            function = invokedFunction(operation);
            if (function) return implementationOf(function, context, reported);
            // No function (no library loaded, XMI, older JSON, hand-built): the function that the operator stands for.
            if (const char* name = KerML::operatorFunctionName(operation.operatorName())) return Registry->find(name);
            return nullptr;
        }

        Value evaluateOperator(KerML::Entities::OperatorExpression& operation, EvaluationContext& context) {
            std::shared_ptr<Function> function;
            bool reported = false;
            const NativeFunction* const implementation = resolveOperator(operation, function, context, reported);
            if (implementation == nullptr) return reported ? Value() : noImplementation(operation, function, context);
            ArgumentList list = argumentsOf(operation);
            if (list.MissingValue) return missingArgumentValue(context);
            Arguments& arguments = list.Values;
            if (isArrow(operation) && !orderArrowArguments(arguments, context)) return Value();
            return call(*implementation, arguments, context);
        }

        SYSMLV2_COLD_PATH static Value missingArgumentValue(EvaluationContext& context) {
            context.report(Severity::Error, "an input parameter of the invocation has no value");
            return Value();
        }

        SYSMLV2_COLD_PATH static bool isArrow(const KerML::Entities::OperatorExpression& operation) { return operation.operatorName() == "->"; }

        /// `x->F(...)`: named arguments are refused (reports). The left operand is the first argument of F, the others start at index 1.
        SYSMLV2_COLD_PATH static bool orderArrowArguments(const Arguments& arguments, EvaluationContext& context) {
            if (!hasNamedArguments(arguments, 1)) return true;
            context.report(Severity::Error, "named arguments not supported yet");
            return false;
        }

        Value evaluateInvocation(KerML::Entities::InvocationExpression& invocation, EvaluationContext& context) {
            std::shared_ptr<Function> function;
            const NativeFunction* const implementation = resolveInvocation(invocation, function, context);
            if (implementation == nullptr) return Value();   // (reported)
            ArgumentList list = argumentsOf(invocation);
            if (list.MissingValue) return missingArgumentValue(context);
            Arguments& arguments = list.Values;
            if (!orderPlainArguments(function, arguments, context)) return Value();
            return call(*implementation, arguments, context);
        }

        SYSMLV2_COLD_PATH static bool orderPlainArguments(const std::shared_ptr<Function>& function, Arguments& arguments, EvaluationContext& context) {
            if (!hasNamedArguments(arguments, 0)) return true;
            if (orderNamedArguments(function, arguments)) return true;
            context.report(Severity::Error, "named arguments not supported yet");
            return false;
        }

        /// The implementation of a plain invocation or reports why there is none.
        SYSMLV2_COLD_PATH const NativeFunction* resolveInvocation(const KerML::Entities::InvocationExpression& invocation,
                                                                  std::shared_ptr<Function>& function, EvaluationContext& context) {
            function = invokedFunction(invocation);
            if (!function) {
                const auto type = invocation.instantiatedType();
                context.report(Severity::Error, "the invocation is not bound to a function" +
                                                    (type ? " (invoked: " + type->declaredName().value_or("<unnamed>") + ")" : std::string()));
                return nullptr;
            }
            // Step 6 hooks in here: a function with a body of its own (lookup().inherited == false and no implementation, or an
            // implementation that is inherited) is evaluated by binding the arguments to its parameters.
            bool reported = false;
            const NativeFunction* const implementation = implementationOf(function, context, reported);
            if (implementation == nullptr && !reported) context.report(Severity::Error, "no native implementation for " + describeFunction(function));
            return implementation;
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
        std::vector<std::pair<FeaturePtr, PathPtr>> Active;   // (binding, path) pairs being evaluated: cycle detection
        PathPtr Current;                                      // the path the expression that is evaluated belongs to
        std::unordered_map<const Feature*, int> Special;
        std::set<const Feature*> Warned;
        std::unordered_map<const Function*, CacheEntry> Cache;
    };

    }   // namespace

    struct Evaluator::Impl {
        Impl(FunctionRegistry registry, EvaluationOptions options)
            : Registry(std::make_shared<const FunctionRegistry>(std::move(registry))), Options(options) {}

        std::shared_ptr<const FunctionRegistry> Registry;
        EvaluationOptions Options;

        /// An Error result for a problem before or outside the evaluation. Never throws; if the message cannot be stored the result is
        /// marked failed.
        Result runFeature(const FeaturePtr& feature, const std::shared_ptr<Element>& target) const noexcept {
            try {
                Run run(Registry, Options);
                return run.executeFeature(feature, target);
            } catch (...) {
                return failure("Unexpected exception while evaluating.");
            }
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
            try {
                Run run(Registry, Options);
                return run.execute(expression, target);
            } catch (...) {
                return failure("Unexpected exception while evaluating.");
            }
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
