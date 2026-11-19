#include "Callables.h"
#include "Arguments.h"
#include "Navigation.h"
#include <kerml/kernel/expressions/FeatureReferenceExpression.h>

#include <kerml/core/features/FeatureMembership.h>
#include <kerml/kernel/packages/LibraryPackage.h>
#include <kerml/core/features/FeatureTyping.h>
#include <kerml/core/features/Redefinition.h>
#include <kerml/core/features/Multiplicity.h>
#include <kerml/core/types/Specialization.h>
#include <kerml/kernel/featurevalues/FeatureValue.h>
#include <kerml/kernel/functions/ResultExpressionMembership.h>
#include <kerml/kernel/functions/ReturnParameterMembership.h>
#include <kerml/kernel/expressions/LiteralInfinity.h>
#include <kerml/kernel/expressions/LiteralInteger.h>
#include <kerml/root/namespaces/Membership.h>

#include <algorithm>
#include <deque>
#include <optional>
#include <set>
#include <typeinfo>

namespace SysMLv2::Evaluation {

    using KerML::Entities::Expression;
    using KerML::Entities::Feature;
    using KerML::Entities::Type;

    std::string nameOf(const FeaturePtr& feature) {
        if (!feature) return {};
        if (const auto effective = feature->effectiveName(); effective && !effective->empty()) return *effective;
        return feature->declaredName().value_or(std::string());
    }

    std::vector<FeaturePtr> ownInputParameters(const Type& type) {
        std::vector<FeaturePtr> parameters;
        for (const auto& relationship : type.ownedRelationship()) {
            if (!relationship || !dynamic_cast<KerML::Entities::FeatureMembership*>(relationship.get()) ||
                dynamic_cast<KerML::Entities::ReturnParameterMembership*>(relationship.get()) ||
                dynamic_cast<KerML::Entities::ResultExpressionMembership*>(relationship.get()))
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

    namespace {
        constexpr int MaxLevels = 16;

        std::vector<TypePtr> generalsOfType(const Type& type) {
            std::vector<TypePtr> generals;
            for (const auto& specialization : type.ownedSpecialization()) {
                if (const auto general = specialization ? specialization->general() : nullptr) generals.push_back(general);
            }
            if (const auto feature = dynamic_cast<const Feature*>(&type)) {
                for (const auto& typing : feature->ownedTyping()) {
                    if (const auto general = typing ? typing->type() : nullptr) generals.push_back(general);
                }
            }
            return generals;
        }

        std::vector<FeaturePtr> directTargets(const FeaturePtr& parameter, int level);

        /// The parameter and everything it redefines, explicitly or by position, transitively.
        std::vector<FeaturePtr> aliasSet(const FeaturePtr& parameter, int level) {
            std::vector<FeaturePtr> aliases{parameter};
            std::set<const Feature*> visited{parameter.get()};
            for (std::size_t index = 0; index < aliases.size(); ++index) {
                for (const auto& target : directTargets(aliases[index], level)) {
                    if (visited.insert(target.get()).second) aliases.push_back(target);
                }
            }
            return aliases;
        }

        bool overlap(const std::vector<FeaturePtr>& a, const std::vector<FeaturePtr>& b) {
            for (const auto& x : a) {
                if (std::find(b.begin(), b.end(), x) != b.end()) return true;
            }
            return false;
        }

        /// What a parameter redefines directly: the features it names (`in :>> b, c`), else, if it names none, the parameter at its
        /// index among the owned input parameters of its owner, in every general of the owner that has one - unless an owned
        /// parameter that names it redefines that already (then this one redefines nothing).
        std::vector<FeaturePtr> directTargets(const FeaturePtr& parameter, int level) {
            std::vector<FeaturePtr> targets;
            for (const auto& redefinition : parameter->ownedRedefinition()) {
                if (const auto redefined = redefinition ? redefinition->redefinedFeature() : nullptr) targets.push_back(redefined);
            }
            if (!targets.empty() || level <= 0) return targets;
            const auto owner = std::dynamic_pointer_cast<Type>(parameter->owner());
            if (!owner) return targets;
            const auto own = ownInputParameters(*owner);
            const auto found = std::find(own.begin(), own.end(), parameter);
            if (found == own.end()) return targets;
            const auto index = static_cast<std::size_t>(found - own.begin());
            for (const auto& general : generalsOfType(*owner)) {
                const auto list = parametersOf(general, level - 1);
                if (index >= list.size()) continue;
                const FeaturePtr& candidate = list[index];
                const auto candidateAliases = aliasSet(candidate, level - 1);
                bool taken = false;
                for (const auto& other : own) {
                    if (other == parameter || other->ownedRedefinition().empty()) continue;
                    if (overlap(aliasSet(other, level - 1), candidateAliases)) taken = true;
                }
                if (!taken) targets.push_back(candidate);
            }
            return targets;
        }
    }

    std::vector<FeaturePtr> parametersOf(const TypePtr& type, int level) {
        std::vector<FeaturePtr> result = ownInputParameters(*type);
        if (level <= 0) return result;
        std::vector<std::vector<FeaturePtr>> ownAliases;
        for (const auto& parameter : result) ownAliases.push_back(aliasSet(parameter, level - 1));
        const std::size_t ownCount = result.size();
        for (const auto& general : generalsOfType(*type)) {
            for (const auto& inherited : parametersOf(general, level - 1)) {
                if (std::find(result.begin(), result.end(), inherited) != result.end()) continue;
                const auto inheritedAliases = aliasSet(inherited, level - 1);
                bool redefined = false;
                for (std::size_t index = 0; index < ownCount && !redefined; ++index) redefined = overlap(ownAliases[index], inheritedAliases);
                if (!redefined) result.push_back(inherited);
            }
        }
        return result;
    }

    std::vector<FeaturePtr> inputParameters(const TypePtr& type) { return parametersOf(type, MaxLevels); }

    std::optional<WrittenBounds> writtenBoundsOf(const FeaturePtr& feature) {
        // The bounds are literals: owned by a multiplicity (`Multiplicity` or, in the pilot's XMI, a MultiplicityRange owned through an
        // OwningMembership) or, in parsed text, members of the feature itself.
        std::vector<std::shared_ptr<KerML::Entities::Element>> bounds;
        const auto collect = [&bounds](const std::shared_ptr<KerML::Entities::Element>& owner, auto&& self, int depth) -> void {
            for (const auto& owned : owner->ownedElements()) {
                if (std::dynamic_pointer_cast<KerML::Entities::LiteralInteger>(owned) || std::dynamic_pointer_cast<KerML::Entities::LiteralInfinity>(owned)) bounds.push_back(owned);
                else if (depth > 0 && std::dynamic_pointer_cast<KerML::Entities::Multiplicity>(owned)) self(owned, self, depth - 1);
            }
        };
        if (const auto multiplicity = feature->multiplicity(); multiplicity && *multiplicity) collect(*multiplicity, collect, 1);
        if (bounds.empty()) {
            for (const auto& owned : feature->ownedElements()) {
                if (std::dynamic_pointer_cast<KerML::Entities::LiteralInteger>(owned) || std::dynamic_pointer_cast<KerML::Entities::LiteralInfinity>(owned)) bounds.push_back(owned);
                else if (std::dynamic_pointer_cast<KerML::Entities::Multiplicity>(owned)) collect(owned, collect, 1);
            }
        }
        if (bounds.empty()) return std::nullopt;
        const auto number = [](const std::shared_ptr<KerML::Entities::Element>& bound) -> std::optional<std::size_t> {
            if (const auto literal = std::dynamic_pointer_cast<KerML::Entities::LiteralInteger>(bound)) return literal->value() > 0 ? static_cast<std::size_t>(literal->value()) : 0;
            return std::nullopt;   // (infinity)
        };
        WrittenBounds result;
        if (bounds.size() == 1) {
            const auto only = number(bounds.front());
            result.lower = only.value_or(0);
            result.upper = only;
        } else {
            result.lower = number(bounds.front()).value_or(0);
            result.upper = number(bounds[1]);
        }
        return result;
    }

    std::optional<std::size_t> writtenLowerBoundOf(const FeaturePtr& feature) {
        const auto bounds = writtenBoundsOf(feature);
        return bounds ? std::optional<std::size_t>(bounds->lower) : std::nullopt;
    }

    WrittenBounds effectiveBoundsOf(const FeaturePtr& feature) {
        // the nearest multiplicity that is written along the redefinitions wins; none written: 1..1 (the default of a usage)
        std::vector<FeaturePtr> pending{feature};
        std::set<const Feature*> visited{feature.get()};
        for (std::size_t index = 0; index < pending.size(); ++index) {
            if (const auto written = writtenBoundsOf(pending[index])) return *written;
            for (const auto& redefinition : pending[index]->ownedRedefinition()) {
                const auto redefined = redefinition ? redefinition->redefinedFeature() : nullptr;
                if (redefined && visited.insert(redefined.get()).second) pending.push_back(redefined);
            }
        }
        return WrittenBounds{1, std::size_t(1)};
    }

    std::size_t lowerBoundOf(const FeaturePtr& feature) { return writtenLowerBoundOf(feature).value_or(0); }

    bool isRequiredParameter(const FeaturePtr& parameter) {
        // the multiplicity that is written down (on the parameter or on one it redefines) decides, else the default 1..1 applies
        for (const auto& alias : parameterAliases(parameter)) {
            if (const auto lower = writtenLowerBoundOf(alias)) return *lower >= 1;
        }
        return true;
    }

    OwnResult ownResultOf(const Type& type) {
        OwnResult result;
        for (const auto& relationship : type.ownedRelationship()) {
            if (!relationship) continue;
            const auto* membership = dynamic_cast<KerML::Entities::Membership*>(relationship.get());
            if (!membership) continue;
            if (dynamic_cast<KerML::Entities::ResultExpressionMembership*>(relationship.get())) {
                if (auto expression = std::dynamic_pointer_cast<Expression>(membership->memberElement())) {
                    result.Expression = std::move(expression);
                    return result;
                }
                continue;
            }
            if (!dynamic_cast<KerML::Entities::FeatureMembership*>(relationship.get())) continue;
            const auto owned = std::dynamic_pointer_cast<Feature>(membership->memberElement());
            if (!owned) continue;
            const auto direction = owned->direction();
            const bool isResult = dynamic_cast<KerML::Entities::ReturnParameterMembership*>(relationship.get()) != nullptr || (direction && *direction == KerML::Entities::OUT);
            if (!isResult || result.ParameterValue) continue;
            if (auto value = featureValueExpression(owned)) {
                result.Parameter = owned;
                result.ParameterValue = std::move(value);
            }
        }
        return result;
    }

    BodyOwner findBodyOwner(const TypePtr& type, const std::function<bool(const Type&)>& stopAt) {
        std::deque<TypePtr> queue{type};
        std::set<const Type*> visited{type.get()};
        while (!queue.empty()) {
            const TypePtr current = std::move(queue.front());
            queue.pop_front();
            if (stopAt && current != type && stopAt(*current)) continue;
            if (auto result = ownResultOf(*current)) return BodyOwner{current, std::move(result)};
            for (const auto& specialization : current->ownedSpecialization()) {
                const auto general = specialization ? specialization->general() : nullptr;
                if (general && visited.insert(general.get()).second) queue.push_back(general);
            }
            if (const auto feature = std::dynamic_pointer_cast<Feature>(current)) {
                for (const auto& typing : feature->ownedTyping()) {
                    const auto general = typing ? typing->type() : nullptr;
                    if (general && visited.insert(general.get()).second) queue.push_back(general);
                }
            }
        }
        return {};
    }
    bool isKernelPackageName(const std::string& name) {
        static const std::set<std::string> packages = {"BaseFunctions",    "BooleanFunctions", "CollectionFunctions", "ComplexFunctions",   "ControlFunctions",
                                                       "DataFunctions",    "IntegerFunctions", "NaturalFunctions",    "NumericalFunctions", "OccurrenceFunctions",
                                                       "RationalFunctions", "RealFunctions",    "ScalarFunctions",     "SequenceFunctions",  "StringFunctions",
                                                       "TrigFunctions",    "VectorFunctions"};
        return packages.count(name) != 0;
    }

    bool isKernelLibraryType(const Type& type) {
        for (auto owner = type.owner(); owner; owner = owner->owner()) {
            const auto name = owner->declaredName();
            if (name && isKernelPackageName(*name) && owner->getType() == "LibraryPackage") {
                // only the standard library: `standard library package BaseFunctions` (a user `library package` of that name is none)
                const auto library = std::dynamic_pointer_cast<KerML::Entities::LibraryPackage>(owner);
                return library && library->isStandard();
            }
        }
        return false;
    }

    std::vector<ArgumentRef> argumentRefs(const std::vector<ExpressionPtr>& arguments, bool arrow) {
        std::vector<ArgumentRef> refs;
        for (std::size_t index = 0; index < arguments.size(); ++index) {
            const ExpressionPtr& argument = arguments[index];
            ArgumentRef ref{argument, {}};
            if (argument && !(arrow && index == 0)) {
                // a parameter (exactly a Feature) that redefines the named parameter owns the value of a named argument
                std::shared_ptr<KerML::Entities::Element> holder = argument->owner();
                if (std::dynamic_pointer_cast<KerML::Entities::FeatureValue>(holder)) holder = holder->owner();
                if (holder) {
                    const KerML::Entities::Element& element = *holder;
                    if (typeid(element) == typeid(Feature)) {
                        const auto parameter = std::dynamic_pointer_cast<Feature>(holder);
                        for (const auto& redefinition : parameter->ownedRedefinition()) {
                            const auto redefined = redefinition ? redefinition->redefinedFeature() : nullptr;
                            if (redefined && ref.Name.empty()) ref.Name = nameOf(redefined);
                        }
                        if (ref.Name.empty() && !parameter->ownedRedefinition().empty()) ref.Name = "?";   // (a redefinition without a name)
                    }
                }
                // the arrow form wraps `name = value` in a plain Expression that carries the name
                const Expression& object = *argument;
                if (ref.Name.empty() && typeid(object) == typeid(Expression) && argument->declaredName().has_value()) {
                    ref.Name = *argument->declaredName();
                    for (const auto& owned : argument->ownedElements()) {
                        if (auto value = std::dynamic_pointer_cast<Expression>(owned)) {
                            ref.Value = std::move(value);
                            break;
                        }
                    }
                }
            }
            refs.push_back(std::move(ref));
        }
        return refs;
    }

    BoundArguments bindArguments(const std::vector<FeaturePtr>& parameters, const std::vector<ArgumentRef>& arguments) {
        BoundArguments bound;
        bound.ByParameter.assign(parameters.size(), nullptr);
        for (const ArgumentRef& argument : arguments) {
            if (argument.Name.empty()) continue;
            std::size_t position = parameters.size();
            for (std::size_t index = 0; index < parameters.size(); ++index) {
                if (nameOf(parameters[index]) == argument.Name) position = index;
            }
            if (position == parameters.size()) {
                bound.Error = "unknown parameter '" + argument.Name + "'";
                return bound;
            }
            if (bound.ByParameter[position]) {
                bound.Error = "parameter '" + argument.Name + "' is given twice";
                return bound;
            }
            bound.ByParameter[position] = argument.Value;
        }
        std::size_t next = 0;
        for (const ArgumentRef& argument : arguments) {
            if (!argument.Name.empty()) continue;
            while (next < parameters.size() && bound.ByParameter[next]) ++next;
            if (next >= parameters.size()) {
                bound.Error = "too many arguments: " + std::to_string(arguments.size()) + " given, " + std::to_string(parameters.size()) + " expected";
                return bound;
            }
            bound.ByParameter[next++] = argument.Value;
        }
        return bound;
    }

    std::vector<FeaturePtr> parameterAliases(const FeaturePtr& parameter) { return aliasSet(parameter, MaxLevels); }

    ExpressionPtr bodyExpressionOf(const ExpressionPtr& argument) {
        if (!argument) return nullptr;
        const Expression& object = *argument;
        if (typeid(object) == typeid(Expression)) return argument;
        if (const auto reference = std::dynamic_pointer_cast<KerML::Entities::FeatureReferenceExpression>(argument)) {
            if (referentOf(*reference)) return nullptr;
            const ExpressionPtr wrapped = wrappedExpressionOf(*reference);
            if (wrapped) {
                const Expression& inner = *wrapped;
                if (typeid(inner) == typeid(Expression)) return wrapped;
            }
        }
        return nullptr;
    }
}
