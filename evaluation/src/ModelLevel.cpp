#include <sysmlv2/evaluation/ModelLevelEvaluable.h>
#include <sysmlv2/evaluation/QualifiedName.h>

#include "Arguments.h"
#include "Callables.h"
#include "Navigation.h"

#include <kerml/core/features/Redefinition.h>
#include <kerml/kernel/expressions/FeatureChainExpression.h>
#include <kerml/kernel/expressions/FeatureReferenceExpression.h>
#include <kerml/kernel/expressions/InstantiationExpression.h>
#include <kerml/kernel/expressions/InvocationExpression.h>
#include <kerml/kernel/expressions/LiteralExpression.h>
#include <kerml/kernel/expressions/MetadataAccessExpression.h>
#include <kerml/kernel/expressions/NullExpression.h>
#include <kerml/kernel/expressions/OperatorExpression.h>
#include <kerml/kernel/expressions/OperatorFunctions.h>
#include <kerml/kernel/functions/Function.h>
#include <kerml/kernel/metadata/Metaclass.h>
#include <kerml/kernel/metadata/MetadataFeature.h>

#include <set>
#include <string>
#include <typeinfo>

namespace SysMLv2::Evaluation {

    namespace {
        using KerML::Entities::Expression;
        using KerML::Entities::Feature;
        using ExpressionPtr = std::shared_ptr<Expression>;

        constexpr std::size_t MaxDepth = 256;

        /// True if the function belongs to the Kernel Function Library: it is an operator function, or it lives in a library package of
        /// it (see isKernelLibraryType). The library does not carry the flag Expression::isModelLevelEvaluable for its functions, so this
        /// is the approximation of "the invoked function is model-level evaluable".
        bool isLibraryFunction(const std::shared_ptr<KerML::Entities::Function>& function, const std::string& qualifiedName) {
            for (const KerML::OperatorFunction& entry : KerML::operatorFunctions) {
                if (qualifiedName == entry.functionName) return function == nullptr || isKernelLibraryType(*function);
            }
            return function != nullptr && isKernelLibraryType(*function);
        }

        /// True if @p feature is Base::Anything::self or redefines it.
        bool conformsToSelf(const std::shared_ptr<Feature>& feature) {
            std::vector<std::shared_ptr<Feature>> pending{feature};
            std::set<const Feature*> visited{feature.get()};
            while (!pending.empty()) {
                const auto current = std::move(pending.back());
                pending.pop_back();
                if (current->declaredName() == std::string("self") && qualifiedNameOf(current) == "Base::Anything::self") return true;
                for (const auto& redefinition : current->ownedRedefinition()) {
                    const auto redefined = redefinition ? redefinition->redefinedFeature() : nullptr;
                    if (redefined && visited.insert(redefined.get()).second) pending.push_back(redefined);
                }
            }
            return false;
        }

        struct Checker {
            std::set<const Feature*> Visiting;

            bool expression(const ExpressionPtr& expression, std::size_t depth) {
                if (!expression || depth > MaxDepth) return false;
                const Expression& object = *expression;
                if (dynamic_cast<KerML::Entities::LiteralExpression*>(expression.get()) || dynamic_cast<KerML::Entities::NullExpression*>(expression.get()) ||
                    dynamic_cast<KerML::Entities::MetadataAccessExpression*>(expression.get()))
                    return true;
                if (const auto reference = std::dynamic_pointer_cast<KerML::Entities::FeatureReferenceExpression>(expression)) return referenceIsEvaluable(*reference, depth);
                if (const auto chain = std::dynamic_pointer_cast<KerML::Entities::FeatureChainExpression>(expression)) return chainIsEvaluable(*chain, depth);
                if (const auto invocation = std::dynamic_pointer_cast<KerML::Entities::InvocationExpression>(expression)) {
                    // (a subclass from outside kerml, such as a trigger invocation, is no plain call)
                    if (typeid(object) != typeid(KerML::Entities::InvocationExpression) && !std::dynamic_pointer_cast<KerML::Entities::OperatorExpression>(expression)) return false;
                    return invocationIsEvaluable(*invocation, depth);
                }
                // the type operand of `istype`, `as`, `@`, ... is an InstantiationExpression that only names a type
                return typeid(object) == typeid(KerML::Entities::InstantiationExpression);
            }

            bool argumentsAreEvaluable(const KerML::Entities::InvocationExpression& invocation, std::size_t depth) {
                const ArgumentList arguments = argumentsOf(invocation);
                if (arguments.MissingValue) return false;
                for (const ExpressionPtr& argument : arguments.Values) {
                    if (!expression(argument, depth + 1)) return false;
                }
                return true;
            }

            bool invocationIsEvaluable(const KerML::Entities::InvocationExpression& invocation, std::size_t depth) {
                std::string function;
                const auto invoked = invokedFunctionOf(invocation);
                if (invoked) {
                    function = qualifiedNameOf(invoked);
                } else if (const auto* operation = dynamic_cast<const KerML::Entities::OperatorExpression*>(&invocation)) {
                    if (const char* name = KerML::operatorFunctionName(operation->operatorName())) function = name;
                }
                return !function.empty() && isLibraryFunction(invoked, function) && argumentsAreEvaluable(invocation, depth);
            }

            bool referenceIsEvaluable(const KerML::Entities::FeatureReferenceExpression& reference, std::size_t depth) {
                const auto referent = referentOf(reference);
                if (!referent) {
                    // (the pilot's XMI wraps lazily evaluated operands, but not bodies, in a reference without a referent)
                    const ExpressionPtr wrapped = wrappedExpressionOf(reference);
                    const Expression* object = wrapped.get();
                    return object != nullptr && typeid(*object) != typeid(Expression) && expression(wrapped, depth + 1);
                }
                return featureIsEvaluable(referent, depth);
            }

            /// The rule for a reference to @p feature.
            bool featureIsEvaluable(const std::shared_ptr<Feature>& feature, std::size_t depth) {
                if (isUnresolvedPlaceholder(*feature)) return false;
                if (conformsToSelf(feature)) return true;
                if (!Visiting.insert(feature.get()).second) return false;   // (already being checked: a cyclic definition)
                const bool result = featureRule(feature, depth);
                Visiting.erase(feature.get());
                return result;
            }

            bool featureRule(const std::shared_ptr<Feature>& feature, std::size_t depth) {
                // the referent is itself a model-level evaluable Expression
                if (const auto referentExpression = std::dynamic_pointer_cast<Expression>(feature)) {
                    if (expression(referentExpression, depth + 1)) return true;
                }
                // its owning type is a metaclass (or it is a metadata feature)
                const auto owner = feature->owner();
                if (dynamic_cast<KerML::Entities::Metaclass*>(owner.get()) || dynamic_cast<KerML::Entities::MetadataFeature*>(feature.get())) return true;
                // it has no featuring type and either no value or a model-level evaluable value
                if (std::dynamic_pointer_cast<KerML::Entities::Type>(owner)) return false;
                const BoundValue bound = boundValueOf(feature);
                return !bound.Expression || expression(bound.Expression, depth + 1);
            }

            bool chainIsEvaluable(const KerML::Entities::FeatureChainExpression& chain, std::size_t depth) {
                const auto last = chainTargetOf(chain);
                if (!last || !argumentsAreEvaluable(chain, depth)) return false;
                return featureIsEvaluable(last, depth);
            }
        };
    }

    bool isModelLevelEvaluable(const std::shared_ptr<KerML::Entities::Expression>& expression) {
        try {
            Checker checker;
            return checker.expression(expression, 0);
        } catch (...) {
            return false;
        }
    }
}
