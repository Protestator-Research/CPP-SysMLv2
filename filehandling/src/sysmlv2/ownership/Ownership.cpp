#include <sysmlv2/ownership/Ownership.h>
#include <kerml/KerML.h>
#include <sysml/SysML.h>

#include <algorithm>
#include <cstddef>
#include <memory>
#include <unordered_map>
#include <unordered_set>

namespace SysMLv2::Files {
    namespace {
        namespace K = KerML::Entities;
        namespace S = SysMLv2::Entities;
        using ElementPtr = std::shared_ptr<K::Element>;

        template <class T, class U>
        bool contains(const std::vector<std::shared_ptr<T>>& list, const std::shared_ptr<U>& item) {
            for (const auto& existing : list) {
                if (existing.get() == item.get()) return true;
            }
            return false;
        }

        template <class T, class U>
        void appendUnique(std::vector<std::shared_ptr<T>>& list, const std::shared_ptr<U>& item) {
            if (item && !contains(list, item)) list.push_back(item);
        }

        // A relationship that is not, at the same time, a namespace (a connector is both a feature and a relationship).
        bool isPlainRelationship(const K::Element* element) {
            return dynamic_cast<const K::Relationship*>(element) != nullptr && dynamic_cast<const K::Namespace*>(element) == nullptr;
        }

        // Appends to the collections of the model once per element: the collections are read a single time per owner, then a hash set decides.
        class Once {
        public:
            template <class Getter>
            bool insert(const void* owner, int list, Getter&& existing, const void* item) {
                const auto key = std::make_pair(owner, list);
                auto it = sets.find(key);
                if (it == sets.end()) {
                    it = sets.emplace(key, std::unordered_set<const void*>()).first;
                    for (const auto& present : existing()) it->second.insert(present.get());
                }
                return it->second.insert(item).second;
            }

        private:
            struct KeyHash {
                size_t operator()(const std::pair<const void*, int>& key) const {
                    return std::hash<const void*>()(key.first) * 31u + static_cast<size_t>(key.second);
                }
            };
            std::unordered_map<std::pair<const void*, int>, std::unordered_set<const void*>, KeyHash> sets;
        };

        class Builder {
        public:
            explicit Builder(OwnershipInput& in) : input(in) {}

            ElementPtr run() {
                auto& elements = *input.elements;
                ElementPtr root = input.root;
                std::vector<ElementPtr> tops;
                if (root == nullptr) {
                    // The top level elements are those no other element lists as an owned element.
                    std::unordered_set<const K::Element*> owned;
                    for (const auto& element : elements) {
                        if (!element) continue;
                        for (const auto& child : element->ownedElements()) owned.insert(child.get());
                    }
                    root = std::make_shared<K::Namespace>();
                    // Members of the root namespace, and the relationships at the top level (imports, dependencies) too.
                    for (const auto& element : elements) {
                        if (element && owned.count(element.get()) == 0) tops.push_back(element);
                    }
                    processChildren(root, tops);
                    if (input.appendRoot) elements.insert(elements.begin(), root);
                } else {
                    process(root);
                }
                return root;
            }

        private:
            OwnershipInput& input;
            std::unordered_set<const K::Element*> visited;
            Once once;

            MembershipKind hintOf(const K::Element* member) const {
                auto it = input.kinds.find(member);
                return it == input.kinds.end() ? MembershipKind::Automatic : it->second;
            }

            void process(const ElementPtr& element) {
                if (!element || !visited.insert(element.get()).second) return;
                processChildren(element, element->ownedElements());
            }

            static ElementPtr memberOf(const std::shared_ptr<K::OwningMembership>& membership) {
                if (auto member = membership->ownedMemberElement()) return member;
                for (const auto& child : membership->ownedElements()) {
                    if (child && !isPlainRelationship(child.get())) return child;
                }
                return nullptr;
            }

            void processChildren(const ElementPtr& owner, const std::vector<ElementPtr>& children) {
                if (!owner) return;
                auto ns = std::dynamic_pointer_cast<K::Namespace>(owner);
                visited.insert(owner.get());

                // Members that a listener already related to the owner through a membership of its own.
                std::unordered_set<const K::Element*> wrapped;
                for (const auto& child : children) {
                    if (auto membership = std::dynamic_pointer_cast<K::OwningMembership>(child)) {
                        if (auto member = memberOf(membership)) wrapped.insert(member.get());
                    }
                }

                std::vector<std::shared_ptr<K::Relationship>> ownedRelationships;
                for (const auto& child : children) {
                    if (!child) continue;
                    if (auto membership = std::dynamic_pointer_cast<K::OwningMembership>(child)) {
                        auto member = memberOf(membership);
                        completeMembership(owner, ns, membership, member);
                        appendUnique(ownedRelationships, membership);
                        process(member);
                        continue;
                    }
                    if (auto membership = std::dynamic_pointer_cast<K::Membership>(child)) {
                        if (isPlainRelationship(membership.get())) {
                            // A membership that does not own its member (an alias).
                            membership->setOwningRelatedElement(owner);
                            membership->setOwner(owner);
                            if (ns) {
                                membership->setMembershipOwningNamespace(ns);
                                if (once.insert(ns.get(), 0, [&] { return ns->ownedMembership(); }, membership.get())) ns->appendOwnedMembership(membership);
                                if (once.insert(ns.get(), 1, [&] { return ns->memberships(); }, membership.get())) ns->appendMembership(membership);
                            }
                            appendUnique(ownedRelationships, membership);
                            continue;
                        }
                    }
                    if (isPlainRelationship(child.get())) {
                        auto relationship = std::dynamic_pointer_cast<K::Relationship>(child);
                        if (!relationship->owningRelatedElement()) relationship->setOwningRelatedElement(owner);
                        if (!relationship->owner()) relationship->setOwner(owner);
                        if (auto import = std::dynamic_pointer_cast<K::Import>(child)) {
                            if (ns) {
                                import->setImportOwningNamespace(ns);
                                if (once.insert(ns.get(), 2, [&] { return ns->ownedImport(); }, import.get())) ns->appendOwnedImport(import);
                            }
                        }
                        appendUnique(ownedRelationships, relationship);
                        continue;
                    }
                    // An owned member.
                    if (wrapped.count(child.get()) != 0) continue;
                    if (child->owningRelationship()) {
                        // Already related to an owner (listed by more than one element): the first owner keeps it.
                        continue;
                    }
                    if (!ns) {
                        child->setOwner(owner);
                        process(child);
                        continue;
                    }
                    auto membership = createMembership(owner, ns, child);
                    completeMembership(owner, ns, membership, child);
                    input.elements->push_back(membership);
                    owner->appendOwnedElement(membership);
                    appendUnique(ownedRelationships, membership);
                    process(child);
                }
                if (!ownedRelationships.empty()) {
                    auto existing = owner->ownedRelationship();
                    std::unordered_set<const K::Relationship*> present;
                    for (const auto& relationship : existing) present.insert(relationship.get());
                    for (const auto& relationship : ownedRelationships) {
                        if (present.insert(relationship.get()).second) existing.push_back(relationship);
                    }
                    owner->setOwnedRelationship(existing);
                }
            }

            std::shared_ptr<K::OwningMembership> createMembership(const ElementPtr& owner, const std::shared_ptr<K::Namespace>& ns,
                                                                  const ElementPtr& member) {
                (void)ns;
                MembershipKind kind = hintOf(member.get());
                const bool ownerIsType = std::dynamic_pointer_cast<K::Type>(owner) != nullptr;
                const bool memberIsFeature = std::dynamic_pointer_cast<K::Feature>(member) != nullptr;
                const bool memberIsMultiplicity = std::dynamic_pointer_cast<K::Multiplicity>(member) != nullptr;
                if (kind == MembershipKind::Automatic) {
                    kind = (ownerIsType && memberIsFeature && !memberIsMultiplicity) ? MembershipKind::Feature : MembershipKind::Owning;
                }
                // The kinds that are feature memberships need a type that owns a feature.
                const bool needsType = kind != MembershipKind::Owning && kind != MembershipKind::Variant && kind != MembershipKind::ElementFilter;
                if (needsType && !(ownerIsType && memberIsFeature)) kind = MembershipKind::Owning;
                switch (kind) {
                    case MembershipKind::Feature: return std::make_shared<K::FeatureMembership>();
                    case MembershipKind::EndFeature:
                        return std::make_shared<K::EndFeatureMembership>(std::dynamic_pointer_cast<K::Feature>(member),
                                                                         std::dynamic_pointer_cast<K::Type>(owner), std::vector<std::shared_ptr<K::Type>>{});
                    case MembershipKind::Parameter: return std::make_shared<K::ParameterMembership>();
                    case MembershipKind::ReturnParameter: return std::make_shared<K::ReturnParameterMembership>();
                    case MembershipKind::ResultExpression:
                        if (std::dynamic_pointer_cast<K::Expression>(member)) return std::make_shared<K::ResultExpressionMembership>();
                        return std::make_shared<K::FeatureMembership>();
                    case MembershipKind::Variant: return std::make_shared<S::VariantMembership>();
                    case MembershipKind::Subject: return std::make_shared<S::SubjectMembership>();
                    case MembershipKind::Actor: return std::make_shared<S::ActorMembership>();
                    case MembershipKind::Stakeholder: return std::make_shared<S::StakeholderMembership>();
                    case MembershipKind::Objective: return std::make_shared<S::ObjectiveMembership>();
                    case MembershipKind::AssumedConstraint: {
                        auto membership = std::make_shared<S::RequirementConstraintMembership>();
                        membership->setKind(S::RequirementConstraintKind::assumption);
                        return membership;
                    }
                    case MembershipKind::RequiredConstraint: {
                        auto membership = std::make_shared<S::RequirementConstraintMembership>();
                        membership->setKind(S::RequirementConstraintKind::requirement);
                        return membership;
                    }
                    case MembershipKind::FramedConcern: return std::make_shared<S::FramedConcernMembership>();
                    case MembershipKind::VerifiedRequirement: return std::make_shared<S::RequirementVerificationMembership>();
                    case MembershipKind::EntryAction: {
                        auto membership = std::make_shared<S::StateSubactionMembership>();
                        membership->setKind(S::StateSubactionKind::entry);
                        return membership;
                    }
                    case MembershipKind::DoAction: {
                        auto membership = std::make_shared<S::StateSubactionMembership>();
                        membership->setKind(S::StateSubactionKind::do_);
                        return membership;
                    }
                    case MembershipKind::ExitAction: {
                        auto membership = std::make_shared<S::StateSubactionMembership>();
                        membership->setKind(S::StateSubactionKind::exit);
                        return membership;
                    }
                    case MembershipKind::TriggerAction: {
                        auto membership = std::make_shared<S::TransitionFeatureMembership>();
                        membership->setKind(S::TransitionFeatureKind::trigger);
                        return membership;
                    }
                    case MembershipKind::GuardExpression: {
                        auto membership = std::make_shared<S::TransitionFeatureMembership>();
                        membership->setKind(S::TransitionFeatureKind::guard);
                        return membership;
                    }
                    case MembershipKind::EffectBehavior: {
                        auto membership = std::make_shared<S::TransitionFeatureMembership>();
                        membership->setKind(S::TransitionFeatureKind::effect);
                        return membership;
                    }
                    case MembershipKind::ViewRendering: return std::make_shared<S::ViewRenderingMembership>();
                    case MembershipKind::ElementFilter: return std::make_shared<K::ElementFilterMembership>();
                    case MembershipKind::Owning:
                    case MembershipKind::Automatic:
                    default: return std::make_shared<K::OwningMembership>();
                }
            }

            // Relates @p member to @p owner through @p membership and records the membership in the collections of the owner.
            void completeMembership(const ElementPtr& owner, const std::shared_ptr<K::Namespace>& ns,
                                    const std::shared_ptr<K::OwningMembership>& membership, const ElementPtr& member) {
                membership->setOwningRelatedElement(owner);
                membership->setOwner(owner);
                if (ns) membership->setMembershipOwningNamespace(ns);
                if (!member) return;
                membership->setOwnedMemberElement(member);
                membership->setMemberElement(member);
                if (member->declaredName() && !membership->memberName()) membership->setMemberName(*member->declaredName());
                if (member->declaredShortName() && !membership->memberShortName()) membership->setMemberShortName(*member->declaredShortName());
                if (input.visibility) {
                    auto it = input.visibility->find(member.get());
                    if (it != input.visibility->end()) membership->setVisibility(it->second);
                }
                member->setOwningRelationship(membership);
                member->setOwner(owner);
                typedMembership(owner, membership, member);
                if (!ns) return;
                if (once.insert(ns.get(), 0, [&] { return ns->ownedMembership(); }, membership.get())) ns->appendOwnedMembership(membership);
                if (once.insert(ns.get(), 1, [&] { return ns->memberships(); }, membership.get())) ns->appendMembership(membership);
                if (once.insert(ns.get(), 3, [&] { return ns->ownedMember(); }, member.get())) ns->appendOwnedMember(member);
                if (once.insert(ns.get(), 4, [&] { return ns->member(); }, member.get())) ns->appendMember(member);
                if (auto type = std::dynamic_pointer_cast<K::Type>(owner)) {
                    auto featureMembership = std::dynamic_pointer_cast<K::FeatureMembership>(membership);
                    auto feature = std::dynamic_pointer_cast<K::Feature>(member);
                    if (featureMembership && feature) {
                        featureMembership->FeatureMembership::setOwningType(type);
                        featureMembership->FeatureMembership::setOwnedMemberFeature(feature);
                        if (once.insert(type.get(), 5, [&] { return type->ownedFeatureMembership(); }, featureMembership.get()))
                            type->appendOwnedFeatureMembership(featureMembership);
                        if (once.insert(type.get(), 6, [&] { return type->featureMemberships(); }, featureMembership.get()))
                            type->appendFeatureMemberships(featureMembership);
                        if (once.insert(type.get(), 7, [&] { return type->ownedFeature(); }, feature.get())) type->appendOwnedFeature(feature);
                        feature->setOwningFeatureMembership(featureMembership);
                        feature->setOwningType(type);
                        if (feature->isEnd()) {
                            if (once.insert(type.get(), 8, [&] { return type->ownedEndFeature(); }, feature.get())) type->appendOwnedEndFeature(feature);
                            feature->setEndOwningType(type);
                        }
                    }
                }
            }

            // The typed properties of the SysML memberships.
            static void typedMembership(const ElementPtr&, const std::shared_ptr<K::OwningMembership>& membership, const ElementPtr& member) {
                if (auto m = std::dynamic_pointer_cast<S::SubjectMembership>(membership)) m->setOwnedSubjectParameter(std::dynamic_pointer_cast<S::Usage>(member));
                else if (auto m2 = std::dynamic_pointer_cast<S::ActorMembership>(membership)) m2->setOwnedActorParameter(std::dynamic_pointer_cast<S::PartUsage>(member));
                else if (auto m3 = std::dynamic_pointer_cast<S::StakeholderMembership>(membership)) m3->setOwnedStakeholderParameter(std::dynamic_pointer_cast<S::PartUsage>(member));
                else if (auto m4 = std::dynamic_pointer_cast<S::ObjectiveMembership>(membership)) m4->setOwnedObjectiveRequirement(std::dynamic_pointer_cast<S::RequirementUsage>(member));
                else if (auto m5 = std::dynamic_pointer_cast<S::VariantMembership>(membership)) m5->setOwnedVariantUsage(std::dynamic_pointer_cast<S::Usage>(member));
                else if (auto m6 = std::dynamic_pointer_cast<S::ViewRenderingMembership>(membership)) m6->setOwnedRendering(std::dynamic_pointer_cast<S::RenderingUsage>(member));
                else if (auto m7 = std::dynamic_pointer_cast<S::StateSubactionMembership>(membership)) m7->setAction(std::dynamic_pointer_cast<S::ActionUsage>(member));
                else if (auto m8 = std::dynamic_pointer_cast<S::TransitionFeatureMembership>(membership)) m8->setTransitionFeature(std::dynamic_pointer_cast<K::Step>(member));
                else if (auto m9 = std::dynamic_pointer_cast<K::ElementFilterMembership>(membership)) m9->setCondition(std::dynamic_pointer_cast<K::Expression>(member));
                else if (auto m10 = std::dynamic_pointer_cast<S::RequirementConstraintMembership>(membership)) m10->setOwnedConstraint(std::dynamic_pointer_cast<S::ConstraintUsage>(member));
            }
        };
    }

    void beginMember(std::vector<MemberMark>& marks, const void* context, MembershipKind kind, const ElementPtr& owner) {
        if (!owner || kind == MembershipKind::Automatic) return;
        marks.push_back({context, owner.get(), owner->ownedElements().size(), kind, false, KerML::Entities::PUBLIC});
    }

    void beginMemberWithVisibility(std::vector<MemberMark>& marks, const void* context, KerML::Entities::VisibilityKind visibility,
                                   const ElementPtr& owner) {
        if (!owner) return;
        marks.push_back({context, owner.get(), owner->ownedElements().size(), MembershipKind::Automatic, true, visibility});
    }

    void endMember(std::vector<MemberMark>& marks, const void* context, const ElementPtr& owner, MembershipKinds& kinds,
                   std::unordered_map<const KerML::Entities::Element*, KerML::Entities::VisibilityKind>* visibilities) {
        while (!marks.empty() && marks.back().context == context) {
            const MemberMark mark = marks.back();
            marks.pop_back();
            if (!owner || owner.get() != mark.owner) continue;
            const auto children = owner->ownedElements();
            for (std::size_t i = mark.ownedCount; i < children.size(); ++i) {
                const auto& child = children[i];
                if (!child || isPlainRelationship(child.get()) || dynamic_cast<const K::Membership*>(child.get()) != nullptr) continue;
                if (dynamic_cast<const K::Multiplicity*>(child.get()) != nullptr) continue;
                // (the innermost member rule is the most specific one: `accept` in a transition is a trigger, its payload a parameter)
                if (mark.kind != MembershipKind::Automatic) kinds.emplace(child.get(), mark.kind);
                if (mark.hasVisibility && visibilities != nullptr && mark.visibility != KerML::Entities::PUBLIC) {
                    (*visibilities)[child.get()] = mark.visibility;
                }
                break;
            }
        }
    }

    std::shared_ptr<KerML::Entities::Element> buildOwnership(OwnershipInput& input) {
        if (input.elements == nullptr) return nullptr;
        Builder builder(input);
        return builder.run();
    }
}
