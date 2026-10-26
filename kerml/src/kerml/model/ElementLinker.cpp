//
// Links elements that were created from JSON, see ElementLinker.h.
//
#include <kerml/model/ElementLinker.h>
#include <kerml/KerML.h>

#include <boost/uuid/uuid_io.hpp>
#include <nlohmann/json.hpp>
#include <map>
#include <string>
#include <unordered_map>

namespace KerML::Entities {
    namespace {
        template <class T, class U>
        bool sameObject(const std::shared_ptr<T>& a, const std::shared_ptr<U>& b) {
            return a && b && dynamic_cast<const void*>(a.get()) == dynamic_cast<const void*>(b.get());
        }

        template <class T, class U>
        bool contains(const std::vector<std::shared_ptr<T>>& list, const std::shared_ptr<U>& item) {
            for (const auto& existing : list) {
                if (sameObject(existing, item))
                    return true;
            }
            return false;
        }

        // A relationship that is not, at the same time, a namespace (a connector is both a feature and a relationship).
        bool isPlainRelationship(const Element* element) {
            return dynamic_cast<const Relationship*>(element) != nullptr && dynamic_cast<const Namespace*>(element) == nullptr;
        }

        /**
         * Writes the derived properties. With @p onlyMissing a property is only written if the JSON the element was created from does not
         * hold it: what the JSON delivered is already set (and must stay as it is), the rest is rebuilt. Without it every property is written
         * (the XMI reader, which creates the elements without JSON).
         */
        class Wiring {
        public:
            explicit Wiring(bool onlyMissing) : OnlyMissing(onlyMissing) {}

            /**
             * The JSON the element was created from (empty if there is none); parsed once.
             */
            const nlohmann::json& sourceOf(const Element& element) const {
                const auto found = Sources.find(&element);
                if (found != Sources.end())
                    return found->second;
                const std::string text = element.sourceJson();
                return Sources.emplace(&element, text.empty() ? nlohmann::json() : nlohmann::json::parse(text)).first->second;
            }

            /**
             * Tells if the property of the element is to be written: if the JSON of the element does not hold it, or if every entry is to be
             * checked (@p item) because the collection is not read from JSON (it has no setter): then the entries the JSON lists are rebuilt.
             */
            bool wants(const Element& element, const char* property, const Element* item = nullptr) const {
                if (!OnlyMissing)
                    return true;
                const auto& source = sourceOf(element);
                const auto entry = source.is_object() ? source.find(property) : source.end();
                if (!source.is_object() || entry == source.end())
                    return true;
                if (item == nullptr || !entry->is_array())
                    return false;
                // (a collection without a setter: reading JSON does not set it, so the entries the JSON lists are rebuilt)
                static const char* const notRead[] = {"membership", "featureMembership", "ownedSubclassification", "ownedSubsetting"};
                bool isNotRead = false;
                for (const char* name : notRead)
                    isNotRead = isNotRead || std::string(name) == property;
                if (!isNotRead)
                    return false;
                const std::string id = boost::uuids::to_string(item->elementIdAsUUID());
                for (const auto& listed : *entry) {
                    if (listed.is_object() && listed.value("@id", std::string()) == id)
                        return true;
                }
                return false;
            }

            /**
             * Adds @p item to the collection that @p current reads, unless it is there already, and only if the property is to be written.
             */
            template <class List, class Item, class Append>
            void appendOnce(const Element& owner, const char* property, const List& current, const std::shared_ptr<Item>& item, Append&& append) const {
                if (item && wants(owner, property, item.get()) && !contains(current, item))
                    append(item);
            }

            void registerMembership(const std::shared_ptr<Membership>& membership) const {
                const auto owner = membership->owningRelatedElement();
                const auto ns = std::dynamic_pointer_cast<Namespace>(owner);
                if (!ns)
                    return;
                if (wants(*membership, "membershipOwningNamespace"))
                    membership->setMembershipOwningNamespace(ns);
                if (wants(*membership, "owner"))
                    membership->setOwner(ns);
                appendOnce(*ns, "ownedMembership", ns->ownedMembership(), membership, [&](const std::shared_ptr<Membership>& m) { ns->appendOwnedMembership(m); });
                appendOnce(*ns, "membership", ns->memberships(), membership, [&](const std::shared_ptr<Membership>& m) { ns->appendMembership(m); });

                const auto owning = std::dynamic_pointer_cast<OwningMembership>(membership);
                if (!owning)
                    return;
                const auto member = owning->memberElement();
                if (!member)
                    return;
                if (owning->ownedRelatedElement().empty() && wants(*owning, "ownedRelatedElement"))
                    owning->setOwnedRelatedElements({member});
                if (!member->owningRelationship() && wants(*member, "owningRelationship"))
                    member->setOwningRelationship(owning);
                if (!member->owner() && wants(*member, "owner"))
                    member->setOwner(ns);
                appendOnce(*ns, "ownedMember", ns->ownedMember(), member, [&](const std::shared_ptr<Element>& m) { ns->appendOwnedMember(m); });
                appendOnce(*ns, "member", ns->member(), member, [&](const std::shared_ptr<Element>& m) { ns->appendMember(m); });

                if (const auto type = std::dynamic_pointer_cast<Type>(owner)) {
                    const auto featureMembership = std::dynamic_pointer_cast<FeatureMembership>(membership);
                    const auto feature = std::dynamic_pointer_cast<Feature>(member);
                    if (featureMembership && feature) {
                        if (wants(*featureMembership, "owningType"))
                            featureMembership->FeatureMembership::setOwningType(type);
                        if (wants(*featureMembership, "ownedMemberFeature"))
                            featureMembership->FeatureMembership::setOwnedMemberFeature(feature);
                        appendOnce(*type, "ownedFeatureMembership", type->ownedFeatureMembership(), featureMembership,
                                   [&](const std::shared_ptr<FeatureMembership>& m) { type->appendOwnedFeatureMembership(m); });
                        appendOnce(*type, "featureMembership", type->featureMemberships(), featureMembership,
                                   [&](const std::shared_ptr<FeatureMembership>& m) { type->appendFeatureMemberships(m); });
                        appendOnce(*type, "ownedFeature", type->ownedFeature(), feature, [&](const std::shared_ptr<Feature>& f) { type->appendOwnedFeature(f); });
                        if (wants(*feature, "owningFeatureMembership"))
                            feature->setOwningFeatureMembership(featureMembership);
                        if (wants(*feature, "owningType"))
                            feature->setOwningType(type);
                        if (feature->isEnd()) {
                            appendOnce(*type, "ownedEndFeature", type->ownedEndFeature(), feature,
                                       [&](const std::shared_ptr<Feature>& f) { type->appendOwnedEndFeature(f); });
                            if (wants(*feature, "endOwningType"))
                                feature->setEndOwningType(type);
                        }
                    }
                }
                if (const auto filter = std::dynamic_pointer_cast<ElementFilterMembership>(membership)) {
                    if (wants(*filter, "condition"))
                        filter->setCondition(std::dynamic_pointer_cast<Expression>(member));
                }
            }

            void registerImport(const std::shared_ptr<Import>& import) const {
                const auto ns = std::dynamic_pointer_cast<Namespace>(import->owningRelatedElement());
                if (!ns)
                    return;
                if (wants(*import, "importOwningNamespace"))
                    import->setImportOwningNamespace(ns);
                appendOnce(*ns, "ownedImport", ns->ownedImport(), import, [&](const std::shared_ptr<Import>& i) { ns->appendOwnedImport(i); });
            }

            void registerRelationship(const std::shared_ptr<Relationship>& relationship) const {
                const auto owner = relationship->owningRelatedElement();
                if (!owner)
                    return;
                const auto feature = std::dynamic_pointer_cast<Feature>(owner);
                const auto type = std::dynamic_pointer_cast<Type>(owner);
                if (const auto redefinition = std::dynamic_pointer_cast<Redefinition>(relationship)) {
                    if (!feature)
                        return;
                    appendOnce(*feature, "ownedRedefinition", feature->ownedRedefinition(), redefinition,
                               [&](const std::shared_ptr<Redefinition>& r) { feature->appendOwnedRedefinition(r); });
                    appendOnce(*feature, "ownedSubsetting", feature->ownedSubsetting(), redefinition,
                               [&](const std::shared_ptr<Redefinition>& r) { feature->appendOwnedSubsetting(r); });
                    appendOnce(*feature, "ownedSpecialization", feature->ownedSpecialization(), redefinition,
                               [&](const std::shared_ptr<Redefinition>& r) { feature->appendOwnedSpecialization(r); });
                    if (wants(*redefinition, "owningFeature"))
                        redefinition->setOwningFeature(feature);
                } else if (const auto referenceSubsetting = std::dynamic_pointer_cast<ReferenceSubsetting>(relationship)) {
                    if (!feature)
                        return;
                    if (wants(*feature, "ownedReferenceSubsetting"))
                        feature->setOwnedReferenceSubsetting(referenceSubsetting);
                    if (wants(*referenceSubsetting, "owningFeature"))
                        referenceSubsetting->setOwningFeature(feature);
                } else if (const auto crossSubsetting = std::dynamic_pointer_cast<CrossSubsetting>(relationship)) {
                    if (!feature)
                        return;
                    if (wants(*feature, "ownedCrossSubsetting"))
                        feature->setOwnedCrossSubsetting(crossSubsetting);
                    if (wants(*crossSubsetting, "owningFeature"))
                        crossSubsetting->setOwningFeature(feature);
                } else if (const auto subsetting = std::dynamic_pointer_cast<Subsetting>(relationship)) {
                    if (!feature)
                        return;
                    appendOnce(*feature, "ownedSubsetting", feature->ownedSubsetting(), subsetting,
                               [&](const std::shared_ptr<Subsetting>& s) { feature->appendOwnedSubsetting(s); });
                    appendOnce(*feature, "ownedSpecialization", feature->ownedSpecialization(), subsetting,
                               [&](const std::shared_ptr<Subsetting>& s) { feature->appendOwnedSpecialization(s); });
                    if (wants(*subsetting, "owningFeature"))
                        subsetting->setOwningFeature(feature);
                } else if (const auto typing = std::dynamic_pointer_cast<FeatureTyping>(relationship)) {
                    if (!feature)
                        return;
                    appendOnce(*feature, "ownedTyping", feature->ownedTyping(), typing, [&](const std::shared_ptr<FeatureTyping>& t) { feature->appendOwnedTyping(t); });
                    if (wants(*typing, "owningFeature"))
                        typing->setOwningFeature(feature);
                } else if (const auto subclassification = std::dynamic_pointer_cast<Subclassification>(relationship)) {
                    const auto classifier = std::dynamic_pointer_cast<Classifier>(owner);
                    if (!classifier)
                        return;
                    appendOnce(*classifier, "ownedSubclassification", classifier->ownedSubclassification(), subclassification,
                               [&](const std::shared_ptr<Subclassification>& s) { classifier->appendOwnedSubclassification(s); });
                    appendOnce(*classifier, "ownedSpecialization", classifier->ownedSpecialization(), subclassification,
                               [&](const std::shared_ptr<Subclassification>& s) { classifier->appendOwnedSpecialization(s); });
                } else if (const auto specialization = std::dynamic_pointer_cast<Specialization>(relationship)) {
                    if (!type)
                        return;
                    appendOnce(*type, "ownedSpecialization", type->ownedSpecialization(), specialization,
                               [&](const std::shared_ptr<Specialization>& s) { type->appendOwnedSpecialization(s); });
                    if (wants(*specialization, "owningType"))
                        specialization->setOwningType(type);
                } else if (const auto conjugation = std::dynamic_pointer_cast<Conjugation>(relationship)) {
                    if (!type)
                        return;
                    if (wants(*type, "ownedConjugator"))
                        type->setConjugation(conjugation);
                    if (wants(*conjugation, "owningType"))
                        conjugation->setOwningType(type);
                } else if (const auto disjoining = std::dynamic_pointer_cast<Disjoining>(relationship)) {
                    if (!type)
                        return;
                    appendOnce(*type, "ownedDisjoining", type->ownedDisjoining(), disjoining, [&](const std::shared_ptr<Disjoining>& d) { type->appendOwnedDisjoining(d); });
                    if (wants(*disjoining, "owningType"))
                        disjoining->setOwningType(type);
                } else if (const auto unioning = std::dynamic_pointer_cast<Unioning>(relationship)) {
                    if (type)
                        appendOnce(*type, "ownedUnioning", type->ownedUnioning(), unioning, [&](const std::shared_ptr<Unioning>& u) { type->appendOwnedUnioning(u); });
                } else if (const auto intersecting = std::dynamic_pointer_cast<Intersecting>(relationship)) {
                    if (type)
                        appendOnce(*type, "ownedIntersecting", type->ownedIntersecting(), intersecting,
                                   [&](const std::shared_ptr<Intersecting>& i) { type->appendOwnedIntersecting(i); });
                } else if (const auto differencing = std::dynamic_pointer_cast<Differencing>(relationship)) {
                    if (type)
                        appendOnce(*type, "ownedDifferencing", type->ownedDifferencing(), differencing,
                                   [&](const std::shared_ptr<Differencing>& d) { type->appendOwnedDifferencing(d); });
                } else if (const auto inverting = std::dynamic_pointer_cast<FeatureInverting>(relationship)) {
                    if (!feature)
                        return;
                    appendOnce(*feature, "ownedFeatureInverting", feature->ownedFeatureInverting(), inverting,
                               [&](const std::shared_ptr<FeatureInverting>& i) { feature->appendOwnedFeatureInverting(i); });
                    if (wants(*inverting, "owningFeature"))
                        inverting->setOwningFeature(feature);
                } else if (const auto chaining = std::dynamic_pointer_cast<FeatureChaining>(relationship)) {
                    if (feature)
                        appendOnce(*feature, "ownedFeatureChaining", feature->ownedFeatureChaining(), chaining,
                                   [&](const std::shared_ptr<FeatureChaining>& c) { feature->appendOwnedFeatureChaining(c); });
                } else if (const auto featuring = std::dynamic_pointer_cast<TypeFeaturing>(relationship)) {
                    if (feature)
                        appendOnce(*feature, "ownedTypeFeaturing", feature->ownedTypeFeaturing(), featuring,
                                   [&](const std::shared_ptr<TypeFeaturing>& f) { feature->appendOwnedTypeFeaturing(f); });
                }
            }

            void rebuild(const std::vector<std::shared_ptr<Element>>& elements) const {
                // The owners.
                for (const auto& element : elements) {
                    if (!element)
                        continue;
                    if (const auto owning = element->owningRelationship()) {
                        const auto owner = owning->owningRelatedElement();
                        if (!element->owner() && wants(*element, "owner"))
                            element->setOwner(owner ? owner : std::shared_ptr<Element>(owning));
                    }
                }
                for (const auto& element : elements) {
                    const auto relationship = std::dynamic_pointer_cast<Relationship>(element);
                    if (!relationship || !relationship->owningRelatedElement())
                        continue;
                    const auto owner = relationship->owningRelatedElement();
                    if (!relationship->owner() && wants(*relationship, "owner"))
                        relationship->setOwner(owner);
                    auto owned = owner->ownedRelationship();
                    if (!contains(owned, relationship) && wants(*owner, "ownedRelationship")) {
                        owned.push_back(relationship);
                        owner->setOwnedRelationship(owned);
                    }
                }
                // The owned elements: the owned relationships and the elements that these own.
                for (const auto& element : elements) {
                    if (!element || !wants(*element, "ownedElement"))
                        continue;
                    const auto add = [&element](const std::shared_ptr<Element>& item) {
                        if (item && !contains(element->ownedElements(), item))
                            element->appendOwnedElement(item);
                    };
                    for (const auto& relationship : element->ownedRelationship()) {
                        add(relationship);
                        if (relationship) {
                            for (const auto& owned : relationship->ownedRelatedElement())
                                add(owned);
                        }
                    }
                    if (const auto relationship = std::dynamic_pointer_cast<Relationship>(element)) {
                        for (const auto& owned : relationship->ownedRelatedElement())
                            add(owned);
                    }
                }
                // The collections of the owners.
                for (const auto& element : elements) {
                    if (const auto membership = std::dynamic_pointer_cast<Membership>(element)) {
                        if (isPlainRelationship(membership.get()))
                            registerMembership(membership);
                        continue;
                    }
                    if (const auto import = std::dynamic_pointer_cast<Import>(element)) {
                        registerImport(import);
                        continue;
                    }
                    if (const auto documentation = std::dynamic_pointer_cast<Documentation>(element)) {
                        if (wants(*documentation, "documentedElement"))
                            documentation->setDocumentedElement(documentation->owner());
                        continue;
                    }
                    if (const auto relationship = std::dynamic_pointer_cast<Relationship>(element))
                        registerRelationship(relationship);
                }
                // The types and the chaining features that the typings and chainings of a feature define.
                for (const auto& element : elements) {
                    const auto feature = std::dynamic_pointer_cast<Feature>(element);
                    if (!feature)
                        continue;
                    if (wants(*feature, "type") && !feature->ownedTyping().empty()) {
                        std::vector<std::shared_ptr<Type>> types;
                        for (const auto& typing : feature->ownedTyping()) {
                            if (typing && typing->type())
                                types.push_back(typing->type());
                        }
                        feature->setType(types);
                    }
                    if (wants(*feature, "chainingFeature") && !feature->ownedFeatureChaining().empty()) {
                        std::vector<std::shared_ptr<Feature>> chain;
                        for (const auto& chaining : feature->ownedFeatureChaining()) {
                            if (chaining && chaining->chainingFeature())
                                chain.push_back(chaining->chainingFeature());
                        }
                        feature->setChainingFeature(chain);
                    }
                }
            }

        private:
            bool OnlyMissing;
            mutable std::unordered_map<const Element*, nlohmann::json> Sources;
        };
    }

    void registerOwnedRelationship(const std::shared_ptr<Relationship>& relationship) {
        Wiring(false).registerRelationship(relationship);
    }

    void linkElements(const std::vector<std::shared_ptr<Element>>& elements) {
        std::map<boost::uuids::uuid, std::shared_ptr<Element>> byId;
        for (const auto& element : elements) {
            if (!element)
                continue;
            byId.emplace(element->getId(), element);
            byId.emplace(element->elementIdAsUUID(), element);
        }
        const auto lookup = [&byId](const boost::uuids::uuid& id) -> std::shared_ptr<Element> {
            const auto it = byId.find(id);
            return it == byId.end() ? nullptr : it->second;
        };
        for (const auto& element : elements) {
            if (element)
                element->resolveJsonReferences(lookup);
        }
        rebuildDerivedProperties(elements);
    }

    void rebuildDerivedProperties(const std::vector<std::shared_ptr<Element>>& elements) {
        Wiring(true).rebuild(elements);
    }
}
