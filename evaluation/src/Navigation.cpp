#include "Navigation.h"

#include <kerml/core/features/FeatureTyping.h>
#include <kerml/core/features/Redefinition.h>
#include <kerml/core/features/Subsetting.h>
#include <kerml/core/types/Specialization.h>
#include <kerml/kernel/classes/Class.h>
#include <kerml/kernel/datatypes/DataType.h>
#include <kerml/kernel/featurevalues/FeatureValue.h>
#include <kerml/root/elements/Relationship.h>
#include <kerml/core/features/FeatureMembership.h>
#include <kerml/root/namespaces/Membership.h>
#include <kerml/root/namespaces/OwningMembership.h>

#include <algorithm>
#include <deque>
#include <optional>
#include <set>
#include <typeinfo>

namespace SysMLv2::Evaluation {

    using KerML::Entities::Element;
    using KerML::Entities::Feature;
    using KerML::Entities::Type;
    using FeaturePtr = std::shared_ptr<Feature>;

    namespace {
        /// The member (a Feature) of the plain Membership (exactly a Membership) that a pilot XMI expression owns, nullptr if none.
        FeaturePtr plainMembershipFeature(const KerML::Entities::Expression& expression) {
            for (const auto& relationship : expression.ownedRelationship()) {
                if (!relationship) continue;
                const KerML::Entities::Relationship& object = *relationship;
                if (typeid(object) != typeid(KerML::Entities::Membership)) continue;
                if (auto feature = std::dynamic_pointer_cast<Feature>(dynamic_cast<KerML::Entities::Membership&>(*relationship).memberElement())) return feature;
            }
            return nullptr;
        }

    }

    FeaturePtr referentOf(const KerML::Entities::FeatureReferenceExpression& reference) {
        if (auto referent = reference.referent()) return referent;
        return plainMembershipFeature(reference);
    }

    FeaturePtr chainTargetOf(const KerML::Entities::FeatureChainExpression& chain) {
        if (auto target = chain.targetFeature()) return target;
        if (auto target = plainMembershipFeature(chain)) return target;
        // the pilot's XMI owns a target that is a chain of its own (`a.b.c`: the target is `b.c`) through an OwningMembership
        for (const auto& relationship : chain.ownedRelationship()) {
            if (!relationship) continue;
            const KerML::Entities::Relationship& object = *relationship;
            if (typeid(object) != typeid(KerML::Entities::OwningMembership)) continue;
            if (auto feature = std::dynamic_pointer_cast<Feature>(dynamic_cast<KerML::Entities::Membership&>(*relationship).memberElement())) return feature;
        }
        return nullptr;
    }

    std::shared_ptr<KerML::Entities::Expression> wrappedExpressionOf(const KerML::Entities::FeatureReferenceExpression& reference) {
        for (const auto& relationship : reference.ownedRelationship()) {
            if (!relationship) continue;
            const KerML::Entities::Relationship& object = *relationship;
            if (typeid(object) != typeid(KerML::Entities::FeatureMembership)) continue;
            if (auto expression = std::dynamic_pointer_cast<KerML::Entities::Expression>(dynamic_cast<KerML::Entities::Membership&>(*relationship).memberElement()))
                return expression;
        }
        return nullptr;
    }

    bool isUnresolvedPlaceholder(const Feature& feature) { return feature.owner() == nullptr; }

    BoundValue boundValueOf(const FeaturePtr& feature) {
        for (const auto& owned : feature->ownedElements()) {
            if (const auto value = std::dynamic_pointer_cast<KerML::Entities::FeatureValue>(owned)) {
                if (auto expression = value->value()) return BoundValue{std::move(expression), value->isDefault()};
            }
        }
        return {};
    }

    namespace {
        /// The direct generals of a type: its owned specializations and, for a feature, its typings, subsettings and redefinitions (the
        /// model keeps those apart from the owned specializations of a feature).
        std::vector<std::shared_ptr<Type>> generalsOf(Type& type) {
            std::vector<std::shared_ptr<Type>> generals;
            const auto add = [&generals](std::shared_ptr<Type> general) {
                if (general && std::find(generals.begin(), generals.end(), general) == generals.end()) generals.push_back(std::move(general));
            };
            for (const auto& specialization : type.ownedSpecialization()) add(specialization ? specialization->general() : nullptr);
            if (const auto feature = dynamic_cast<Feature*>(&type)) {
                for (const auto& typing : feature->ownedTyping()) add(typing ? typing->type() : nullptr);
                for (const auto& subsetting : feature->ownedSubsetting()) add(subsetting ? subsetting->subsettedFeature() : nullptr);
                for (const auto& redefinition : feature->ownedRedefinition()) add(redefinition ? redefinition->redefinedFeature() : nullptr);
            }
            return generals;
        }
    }

    const std::vector<std::shared_ptr<Type>>& Navigation::closure(Type& type) {
        const auto found = Closures.find(&type);
        if (found != Closures.end()) return found->second;
        std::vector<std::shared_ptr<Type>> result;
        std::set<const Type*> visited{&type};
        std::deque<std::shared_ptr<Type>> queue;
        // (the starting type itself is not owned by a shared_ptr here: it is added by the caller through its own shared_ptr)
        for (auto& general : generalsOf(type)) {
            if (visited.insert(general.get()).second) queue.push_back(std::move(general));
        }
        while (!queue.empty()) {
            auto current = std::move(queue.front());
            queue.pop_front();
            result.push_back(current);
            for (auto& general : generalsOf(*current)) {
                if (visited.insert(general.get()).second) queue.push_back(std::move(general));
            }
        }
        return Closures.emplace(&type, std::move(result)).first->second;
    }

    const std::vector<FeaturePtr>& Navigation::ownedFeatures(const std::shared_ptr<Type>& type) {
        const auto found = Owned.find(type.get());
        if (found != Owned.end()) return found->second;
        std::vector<FeaturePtr> features;
        for (const auto& owned : type->ownedElements()) {
            if (auto feature = std::dynamic_pointer_cast<Feature>(owned)) features.push_back(std::move(feature));
        }
        return Owned.emplace(type.get(), std::move(features)).first->second;
    }

    const std::vector<FeaturePtr>& Navigation::redefinedBy(const FeaturePtr& feature) {
        const auto found = Redefined.find(feature.get());
        if (found != Redefined.end()) return found->second;
        std::vector<FeaturePtr> result;
        std::set<const Feature*> visited{feature.get()};
        std::deque<FeaturePtr> queue{feature};
        while (!queue.empty()) {
            const FeaturePtr current = std::move(queue.front());
            queue.pop_front();
            for (const auto& redefinition : current->ownedRedefinition()) {
                const auto redefined = redefinition ? redefinition->redefinedFeature() : nullptr;
                if (redefined && visited.insert(redefined.get()).second) {
                    result.push_back(redefined);
                    queue.push_back(redefined);
                }
            }
        }
        return Redefined.emplace(feature.get(), std::move(result)).first->second;
    }

    bool Navigation::moreSpecific(const FeaturePtr& a, const FeaturePtr& b) {
        if (a == b) return false;
        for (const auto& redefined : redefinedBy(a)) {
            if (redefined == b) return true;
        }
        const auto ownerA = std::dynamic_pointer_cast<Type>(a->owner());
        const auto ownerB = std::dynamic_pointer_cast<Type>(b->owner());
        if (!ownerA || !ownerB || ownerA == ownerB) return false;
        // b's owner is one of the generals of a's owner
        for (const auto& general : closure(*ownerA)) {
            if (general == ownerB) return true;
        }
        return false;
    }

    std::vector<FeaturePtr> Navigation::maximal(const std::vector<FeaturePtr>& candidates) {
        std::vector<FeaturePtr> result;
        for (const auto& candidate : candidates) {
            bool dominated = false;
            for (const auto& other : candidates) {
                if (moreSpecific(other, candidate)) {
                    dominated = true;
                    break;
                }
            }
            if (!dominated) result.push_back(candidate);
        }
        return result;
    }

    namespace {
        /// True if @p type owns @p feature through a private membership (not accessible to the specializations of the type).
        bool isPrivateMember(const std::shared_ptr<Type>& type, const FeaturePtr& feature) {
            for (const auto& relationship : type->ownedRelationship()) {
                const auto membership = std::dynamic_pointer_cast<KerML::Entities::Membership>(relationship);
                if (membership && membership->memberElement() == feature && membership->visibility() == KerML::Entities::PRIVATE) return true;
            }
            return false;
        }
    }

    FeaturePtr Navigation::findByName(const std::string& name, const std::shared_ptr<Element>& context, bool& ambiguous) {
        ambiguous = false;
        const auto contextType = std::dynamic_pointer_cast<Type>(context);
        if (!contextType) return nullptr;
        std::vector<std::shared_ptr<Type>> types{contextType};
        const auto& generals = closure(*contextType);
        types.insert(types.end(), generals.begin(), generals.end());
        std::vector<FeaturePtr> found;
        for (std::size_t index = 0; index < types.size(); ++index) {
            for (const auto& owned : ownedFeatures(types[index])) {
                const auto effective = owned->effectiveName();
                if (!effective || *effective != name) continue;
                if (index > 0 && isPrivateMember(types[index], owned)) continue;   // (inherited private members are not accessible)
                found.push_back(owned);
            }
        }
        const auto best = maximal(found);
        if (best.size() > 1) ambiguous = true;
        return best.size() == 1 ? best.front() : nullptr;
    }

    bool samePath(const PathPtr& a, const PathPtr& b) {
        auto left = a;
        auto right = b;
        while (left && right) {
            if (left == right) return true;
            if (left->Element != right->Element) return false;
            left = left->Parent;
            right = right->Parent;
        }
        return !left && !right;
    }

    bool Navigation::denotesElement(const FeaturePtr& feature) {
        const auto cached = Denotes.find(feature.get());
        if (cached != Denotes.end()) return cached->second;
        bool result = false;
        const std::string metaclass = feature->getType();
        const bool usage = metaclass.size() > 5 && metaclass.compare(metaclass.size() - 5, 5, "Usage") == 0;
        if (metaclass == "EnumerationUsage") {
            result = true;   // an enumeration literal
        } else if (metaclass == "AttributeUsage") {
            result = false;  // data, whatever the recorded types are (the implicit generals differ between text and XMI)
        } else if (usage && metaclass != "ReferenceUsage") {
            result = true;   // a part, item, action, port, ...: an occurrence-like usage even if no type is recorded
        } else {
            bool classFound = false;
            bool dataType = false;
            std::vector<std::shared_ptr<Type>> types{feature};
            const auto& generals = closure(*feature);
            types.insert(types.end(), generals.begin(), generals.end());
            for (const auto& type : types) {
                if (dynamic_cast<KerML::Entities::DataType*>(type.get())) dataType = true;
                if (dynamic_cast<KerML::Entities::Class*>(type.get())) classFound = true;
            }
            result = classFound && !dataType;
        }
        Denotes.emplace(feature.get(), result);
        return result;
    }

    std::shared_ptr<Element> Navigation::featuringContext(const std::shared_ptr<Element>& element) {
        for (auto current = element; current; current = current->owner()) {
            const auto feature = std::dynamic_pointer_cast<Feature>(current);
            if (!feature || std::dynamic_pointer_cast<KerML::Entities::Expression>(current)) continue;
            const auto owner = std::dynamic_pointer_cast<Type>(feature->owner());
            if (owner && !std::dynamic_pointer_cast<KerML::Entities::Expression>(owner)) return owner;
        }
        return nullptr;
    }

    bool Navigation::conforms(const FeaturePtr& feature, const std::shared_ptr<Element>& target) {
        const auto featureOwner = std::dynamic_pointer_cast<Type>(feature->owner());
        if (!target || !featureOwner) return true;
        const auto has = [&](const std::shared_ptr<Element>& element) {
            const auto type = std::dynamic_pointer_cast<Type>(element);
            if (!type) return false;
            if (type == featureOwner) return true;
            for (const auto& general : closure(*type)) {
                if (general == featureOwner) return true;
            }
            return false;
        };
        for (auto current = target; current; current = current->owner()) {
            if (has(current)) return true;
        }
        return false;
    }

    PathPtr Navigation::contextFor(const FeaturePtr& feature, const PathPtr& path) {
        const auto featureOwner = std::dynamic_pointer_cast<Type>(feature->owner());
        if (!path || !featureOwner) return path;
        const auto has = [&](const std::shared_ptr<Element>& element) {
            const auto type = std::dynamic_pointer_cast<Type>(element);
            if (!type) return false;
            if (type == featureOwner) return true;
            for (const auto& general : closure(*type)) {
                if (general == featureOwner) return true;
            }
            return false;
        };
        // the instances of the path first, innermost to outermost (a nested usage that was entered through a chain is featured by the
        // instance it was reached through, not by its definition) ...
        for (auto node = path; node; node = node->Parent) {
            if (has(node->Element)) return node;
        }
        // ... then the lexical owners
        for (auto node = path; node; node = node->Parent) {
            for (auto current = node->Element->owner(); current; current = current->owner()) {
                if (has(current)) return std::make_shared<const Path>(Path{current, nullptr});
            }
        }
        return path;
    }

    bool Navigation::isA(const std::shared_ptr<Type>& type, const std::shared_ptr<Type>& general) {
        if (!type || !general) return false;
        if (type == general) return true;
        for (const auto& candidate : closure(*type)) {
            if (candidate == general) return true;
        }
        return false;
    }

    namespace {
        /// Does the feature reach one of the targets through at least one subsetting (redefinitions alone make it the effective feature)?
        bool subsetsAny(const FeaturePtr& candidate, const std::set<const Feature*>& targets) {
            std::set<std::pair<const Feature*, bool>> visited;
            std::vector<std::pair<FeaturePtr, bool>> pending{{candidate, false}};
            while (!pending.empty()) {
                const auto [current, viaSubsetting] = pending.back();
                pending.pop_back();
                if (!visited.insert({current.get(), viaSubsetting}).second) continue;
                if (viaSubsetting && targets.count(current.get())) return true;
                // (a subsetting of what the feature also redefines is implied by the redefinition - XMI writes both - and no subsetting)
                std::set<const Feature*> redefined;
                for (const auto& redefinition : current->ownedRedefinition()) {
                    if (const auto general = redefinition ? redefinition->redefinedFeature() : nullptr) redefined.insert(general.get());
                }
                for (const auto& subsetting : current->ownedSubsetting()) {
                    const auto general = subsetting ? subsetting->subsettedFeature() : nullptr;
                    if (general && redefined.count(general.get()) == 0) pending.emplace_back(general, true);
                }
                for (const auto& redefinition : current->ownedRedefinition()) {
                    if (const auto general = redefinition ? redefinition->redefinedFeature() : nullptr) pending.emplace_back(general, viaSubsetting);
                }
            }
            return false;
        }
    }

    namespace {
        /// Everything that the feature reaches through at least one subsetting (and any redefinitions around it).
        std::set<const Feature*> subsettedBy(const FeaturePtr& candidate) {
            std::set<const Feature*> reached;
            std::set<std::pair<const Feature*, bool>> visited;
            std::vector<std::pair<FeaturePtr, bool>> pending{{candidate, false}};
            while (!pending.empty()) {
                const auto [current, viaSubsetting] = pending.back();
                pending.pop_back();
                if (!visited.insert({current.get(), viaSubsetting}).second) continue;
                if (viaSubsetting) reached.insert(current.get());
                std::set<const Feature*> redefined;
                for (const auto& redefinition : current->ownedRedefinition()) {
                    if (const auto general = redefinition ? redefinition->redefinedFeature() : nullptr) redefined.insert(general.get());
                }
                for (const auto& subsetting : current->ownedSubsetting()) {
                    const auto general = subsetting ? subsetting->subsettedFeature() : nullptr;
                    if (general && redefined.count(general.get()) == 0) pending.emplace_back(general, true);
                }
                for (const auto& redefinition : current->ownedRedefinition()) {
                    if (const auto general = redefinition ? redefinition->redefinedFeature() : nullptr) pending.emplace_back(general, viaSubsetting);
                }
            }
            return reached;
        }
    }

    std::vector<FeaturePtr> Navigation::subsettersOf(const FeaturePtr& feature, const std::shared_ptr<Element>& context) {
        const auto key = std::make_pair(feature.get(), context.get());
        if (const auto found = Subsetters.find(key); found != Subsetters.end()) return found->second;
        std::vector<FeaturePtr> candidates;
        std::set<const Feature*> targets{feature.get()};
        for (const auto& redefined : redefinedBy(feature)) targets.insert(redefined.get());
        std::set<const Feature*> seen;
        const auto consider = [&](const FeaturePtr& candidate) {
            if (targets.count(candidate.get()) || !seen.insert(candidate.get()).second) return;
            if (subsetsAny(candidate, targets)) candidates.push_back(candidate);
        };
        if (!std::dynamic_pointer_cast<Type>(feature->owner())) {
            // a feature of a package: the features of that package that subset it
            if (const auto owner = feature->owner()) {
                for (const auto& owned : owner->ownedElements()) {
                    if (const auto candidate = std::dynamic_pointer_cast<Feature>(owned)) consider(candidate);
                }
            }
        } else if (const auto contextType = std::dynamic_pointer_cast<Type>(context)) {
            std::vector<std::shared_ptr<Type>> types{contextType};
            for (const auto& general : closure(*contextType)) types.push_back(general);
            for (const auto& type : types) {
                for (const auto& candidate : ownedFeatures(type)) consider(candidate);
            }
        }
        // features are unique: a candidate that another candidate subsets stands for the same values (`x :> a2`, `a2 :> parts`: x counts).
        // Linear: what every candidate reaches through subsetting marks the candidates (and their redefinitions) among it as covered.
        std::unordered_map<const Feature*, std::vector<std::size_t>> byFeature;
        for (std::size_t index = 0; index < candidates.size(); ++index) {
            byFeature[candidates[index].get()].push_back(index);
            for (const auto& redefined : redefinedBy(candidates[index])) byFeature[redefined.get()].push_back(index);
        }
        std::vector<bool> covered(candidates.size(), false);
        for (std::size_t index = 0; index < candidates.size(); ++index) {
            for (const Feature* reached : subsettedBy(candidates[index])) {
                const auto found = byFeature.find(reached);
                if (found == byFeature.end()) continue;
                for (const std::size_t other : found->second) {
                    if (other != index) covered[other] = true;
                }
            }
        }
        std::vector<FeaturePtr> result;
        for (std::size_t index = 0; index < candidates.size(); ++index) {
            if (!covered[index]) result.push_back(candidates[index]);
        }
        return Subsetters.emplace(key, std::move(result)).first->second;
    }

    Resolution Navigation::resolve(const FeaturePtr& feature, const std::shared_ptr<Element>& context) {
        const auto key = std::make_pair(feature.get(), context.get());
        const auto cached = Resolved.find(key);
        if (cached != Resolved.end()) return cached->second;

        // the feature, everything it redefines (a value-less redefinition has the value of what it redefines), and every feature of the
        // context and its generals that redefines one of those
        std::vector<FeaturePtr> candidates{feature};
        for (const auto& redefined : redefinedBy(feature)) candidates.push_back(redefined);
        std::set<const Feature*> base;
        for (const auto& candidate : candidates) base.insert(candidate.get());
        if (const auto contextType = std::dynamic_pointer_cast<Type>(context)) {
            std::vector<std::shared_ptr<Type>> types{contextType};
            const auto& generals = closure(*contextType);
            types.insert(types.end(), generals.begin(), generals.end());
            for (const auto& type : types) {
                for (const auto& owned : ownedFeatures(type)) {
                    if (base.count(owned.get()) != 0 || std::find(candidates.begin(), candidates.end(), owned) != candidates.end()) continue;
                    bool redefinesBase = false;
                    for (const auto& redefined : redefinedBy(owned)) {
                        if (base.count(redefined.get()) != 0) {
                            redefinesBase = true;
                            break;
                        }
                    }
                    if (redefinesBase) candidates.push_back(owned);
                }
            }
        }
        const auto describe = [](const std::vector<FeaturePtr>& features) {
            std::string text;
            for (const auto& item : features) {
                if (!text.empty()) text += " and ";
                const auto owner = item->owner();
                const auto ownerName = owner ? owner->effectiveName() : std::nullopt;
                text += (ownerName ? *ownerName + "::" : std::string()) + item->effectiveName().value_or("<unnamed>");
            }
            return text;
        };
        Resolution resolution;
        // the structural effective feature: the most specific one; unrelated ones (a diamond without values) fall back to the feature
        const auto structural = maximal(candidates);
        resolution.Effective = structural.size() == 1 ? structural.front() : feature;
        // the values: bound values first, `default` values only if no feature binds one; unrelated features that bind values are ambiguous
        for (const bool wantDefault : {false, true}) {
            std::vector<FeaturePtr> valued;
            for (const auto& candidate : candidates) {
                const BoundValue bound = boundValueOf(candidate);
                if (bound.Expression && bound.IsDefault == wantDefault) valued.push_back(candidate);
            }
            if (valued.empty()) continue;
            const auto best = maximal(valued);
            if (best.size() == 1) {
                resolution.Binding = best.front();
                resolution.Value = boundValueOf(best.front()).Expression;
                if (!wantDefault) {
                    // KerML allows only default values to be overridden
                    for (const auto& other : valued) {
                        if (moreSpecific(best.front(), other)) resolution.Overridden.push_back(other);
                    }
                    // a more specific `default` value does not override a bound value
                    for (const auto& candidate : candidates) {
                        const BoundValue bound = boundValueOf(candidate);
                        if (bound.Expression && bound.IsDefault && moreSpecific(candidate, best.front())) resolution.IgnoredDefaults.push_back(candidate);
                    }
                }
            } else {
                resolution.Ambiguity = "the value of '" + feature->effectiveName().value_or("<unnamed>") + "' is ambiguous: " + describe(best);
            }
            break;
        }
        Resolved.emplace(key, resolution);
        return resolution;
    }
}
