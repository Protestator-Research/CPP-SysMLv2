//
// ModelDiff (AP11): compares the abstract syntax that our parse listeners built for one library file with the XMI that the OMG
// pilot implementation exported for the same file (resources/sysml.library.xmi, explicit relationships only).
//
// Compared, per library file (all keys use the qualified names of the textual notation, "A::'b c'::d"):
//   element     every named element: qualified name and metaclass
//   owner       the owner of every named element (the owning namespace, reached through its membership)
//   membership  the metaclass (OwningMembership, FeatureMembership, ...) and the visibility of the membership of every named member
//   alias       alias memberships: owner, names, target, visibility
//   rel         explicit relationships FeatureTyping, Subclassification, Subsetting, Redefinition, ReferenceSubsetting,
//               CrossSubsetting, Conjugation / PortConjugation: metaclass, source and target
//   relOwner    the element that owns each of these relationships (their owningRelatedElement)
//
// Elements without a name, and everything below them, have no qualified name (KerML 8.3.2.2.1) and are not compared; relationships
// whose source has no qualified name (typings of anonymous parameters, ...) are counted as "skipped" and not compared.
//
// Categories that the XMI encodes and the model has no concept of (excluded on purpose, counted in the "excluded" output of a run):
//   1. Feature chains as relationship targets (`subsets a.b`, `crosses a.b`, `subset a.b subsets c.d;`): the XMI has an anonymous Feature
//      with FeatureChainings as the target; our model targets the last feature of the chain (and, in the KerML listener, additionally keeps
//      the chain as a Feature named after its text). See kChainReason; the exclusion is structural (matched pair by pair, the chain's last
//      feature must be the target that our model resolved), so a wrong resolution of a chain still shows up as a difference.
// Not modelled and therefore not compared at all (not exclusions of differences, but gaps of the comparison): implicit relationships
// (the .implied XMI is not used), anonymous elements and what is below them, control action nodes (merge, decide, join, fork).
//
#pragma once

#include "XmiReader.h"

#include <kerml/KerML.h>
#include <sysmlv2/resolution/ResolutionData.h>

#include <algorithm>
#include <functional>
#include <iterator>
#include <map>
#include <memory>
#include <optional>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

namespace ConformanceTest {

// A category of differences that is excluded on purpose: the XMI encodes something the model has no concept of (yet).
struct XmiExclusion {
    std::string category;   // "element", "membership", ...
    std::string reason;     // documented in the test output
    // Decides on the key: the part before " : " / " -> " etc. (the id) and the full text of the item.
    std::function<bool(const std::string& id, const std::string& detail)> matches;
};

// Documented exclusion: relationships whose target is a feature chain (`subsets a.b`, `crosses a.b`).
inline constexpr const char* kChainReason =
    "target is a feature chain: the XMI has an anonymous Feature with FeatureChainings, the model targets the last feature and keeps the chain as a Feature named after its text";

// The differences that are excluded on purpose (see the comment at each entry). Empty entries mean: nothing is excluded.
inline std::vector<XmiExclusion> documentedXmiExclusions();

struct ModelDiffResult {
    /// category -> messages (each one is one difference)
    std::map<std::string, std::vector<std::string>> differences;
    /// category -> number of differences that were excluded, by reason
    std::map<std::string, std::map<std::string, size_t>> excluded;
    size_t skippedRelationships = 0;
    size_t comparedElements = 0;
    size_t comparedRelationships = 0;

    size_t total() const {
        size_t sum = 0;
        for (const auto& [category, messages] : differences) sum += messages.size();
        return sum;
    }
};

class ModelDiff {
public:
    using ElementPtr = std::shared_ptr<KerML::Entities::Element>;
    using Item = std::pair<std::string, std::string>;  // id, detail

    explicit ModelDiff(Xmi::Corpus& corpus) : corpus_(corpus) {}

    void addExclusion(XmiExclusion exclusion) { exclusions_.push_back(std::move(exclusion)); }

    ModelDiffResult compare(const std::vector<ElementPtr>& ours, const Xmi::File& xmi) {
        ModelDiffResult result;
        std::map<std::string, std::vector<Item>> expected;
        std::map<std::string, std::vector<Item>> actual;
        chainTargets_.clear();
        collectXmi(xmi, expected, result);
        collectOurs(ours, actual, result);
        for (const char* category : {"element", "owner", "membership", "alias", "rel", "relOwner"}) {
            diffCategory(category, expected[category], actual[category], result);
        }
        return result;
    }

    // The qualified name of one of our elements: nullopt if it (or one of its owners) has no name.
    std::optional<std::string> qualifiedName(KerML::Entities::Element* element) { return ourName(element, 0); }

private:
    using Element = KerML::Entities::Element;

    Xmi::Corpus& corpus_;
    std::vector<XmiExclusion> exclusions_;
    std::unordered_map<const Element*, std::pair<char, std::string>> memo_;  // 0 none, 1 name
    /// Documented exclusion "feature chains" (see documentedXmiExclusions): "<qualified name of the source>|<last feature of the chain>".
    std::set<std::string> chainTargets_;
    mutable std::unordered_map<const Xmi::File*, std::vector<char>> chainFeatures_;

    /// Our model names a feature chain `a.b.c` after its text and keeps it as an owned Feature next to the relationship, whose
    /// target is the last feature of the chain; the XMI has an anonymous Feature with FeatureChainings as the target.
    static bool isChainFeature(Element* element) {
        if (dynamic_cast<const KerML::Entities::Feature*>(element) == nullptr) return false;
        if (!element->declaredName() || element->declaredName()->find('.') == std::string::npos) return false;
        for (const auto& child : element->ownedElements()) {
            if (dynamic_cast<const KerML::Entities::FeatureChaining*>(child.get()) != nullptr) return true;
        }
        return false;
    }

    static bool canTargetChain(const std::string& type) { return type == "Subsetting" || type == "CrossSubsetting" || type == "ReferenceSubsetting"; }

    static std::string lastSegment(const std::string& qualifiedName) {
        const size_t position = qualifiedName.rfind("::");
        return Xmi::unquoteName(position == std::string::npos ? qualifiedName : qualifiedName.substr(position + 2));
    }

    bool isXmiChain(const Xmi::File& file, int index) const {
        if (index >= 0 && static_cast<size_t>(index) < file.elements.size()) {
            const auto& target = file.elements[static_cast<size_t>(index)];
            if (!target.name.empty() || !target.shortName.empty()) return false;
        }
        auto it = chainFeatures_.find(&file);
        if (it == chainFeatures_.end()) {
            std::vector<char> chained(file.elements.size(), 0);
            for (const auto& element : file.elements) {
                if (element.type == "FeatureChaining" && element.parent >= 0) chained[static_cast<size_t>(element.parent)] = 1;
            }
            it = chainFeatures_.emplace(&file, std::move(chained)).first;
        }
        return index >= 0 && static_cast<size_t>(index) < it->second.size() && it->second[static_cast<size_t>(index)] != 0;
    }

    static const char* visibilityName(KerML::Entities::VisibilityKind kind) {
        switch (kind) {
            case KerML::Entities::PRIVATE: return "private";
            case KerML::Entities::PROTECTED: return "protected";
            default: return "public";
        }
    }

    // ------------------------------------------------------------------------------------------------ our side

    static bool isRoot(Element* element) { return element->owner() == nullptr && element->getType() == "Namespace"; }

    static bool isPlainRelationship(const Element* element) {
        return dynamic_cast<const KerML::Entities::Relationship*>(element) != nullptr &&
               dynamic_cast<const KerML::Entities::Namespace*>(element) == nullptr;
    }

    // The owner of @p element, looking through memberships (which stand between an element and its owner).
    static Element* ownerOf(Element* element) {
        Element* owner = element->owner().get();
        for (int guard = 0; owner != nullptr && dynamic_cast<KerML::Entities::Membership*>(owner) != nullptr && guard < 8; ++guard) {
            owner = owner->owner().get();
        }
        return owner;
    }

    // The name of an element: its declared name; for a feature without one the effective name (KerML Feature::effectiveName), which is the
    // name of the feature it redefines first (`attribute :>> num : Real;` is the feature `num`).
    static std::string ownName(const Element* element, int depth = 0) {
        std::string name = Xmi::unquoteName(element->declaredName().value_or(""));
        if (!name.empty() || depth > 32) return name;
        if (const auto* feature = dynamic_cast<const KerML::Entities::Feature*>(element)) {
            const auto redefinitions = feature->ownedRedefinition();
            if (!redefinitions.empty() && redefinitions.front()) {
                const auto redefined = redefinitions.front()->redefinedFeature();
                if (redefined && dynamic_cast<const SysMLv2::Files::UnresolvedMarker*>(redefined.get()) == nullptr) {
                    return ownName(redefined.get(), depth + 1);
                }
            }
        }
        return std::string();
    }

    std::optional<std::string> ourName(Element* element, int depth) {
        if (element == nullptr || depth > 200) return std::nullopt;
        auto found = memo_.find(element);
        if (found != memo_.end()) {
            if (found->second.first == 1) return found->second.second;
            return std::nullopt;
        }
        std::optional<std::string> result;
        if (isRoot(element)) {
            result = std::string();
        } else {
            const std::string name = ownName(element);
            const bool namable = !isPlainRelationship(element) || element->getType() == "Dependency";
            if (!name.empty() && namable) {
                Element* owner = ownerOf(element);
                if (owner == nullptr) {
                    result = Xmi::quoteName(name);  // a top-level element (its owner, the root namespace, is not modelled)
                } else if (dynamic_cast<const KerML::Entities::Namespace*>(owner) != nullptr) {
                    const auto ownerName = ourName(owner, depth + 1);
                    if (ownerName) result = Xmi::joinQualifiedName(*ownerName, name);
                }
            }
        }
        memo_[element] = result ? std::make_pair(char(1), *result) : std::make_pair(char(0), std::string());
        return result;
    }

    static std::string shown(const std::string& qualifiedName) { return qualifiedName.empty() ? "(root)" : qualifiedName; }

    std::string targetName(const std::shared_ptr<Element>& target) {
        if (!target) return "(none)";
        if (const auto* marker = dynamic_cast<const SysMLv2::Files::UnresolvedMarker*>(target.get())) return "?unresolved " + marker->reference;
        const auto name = ourName(target.get(), 0);
        return name ? shown(*name) : "(unnamed " + target->getType() + ")";
    }

    static bool isTargetedRelationship(const std::string& type) {
        static const std::set<std::string> kinds = {"FeatureTyping",  "Subclassification", "Subsetting",       "Redefinition",
                                                     "ReferenceSubsetting", "CrossSubsetting", "Conjugation", "PortConjugation",
                                                     "Specialization"};
        return kinds.count(type) != 0;
    }

    void collectOurs(const std::vector<ElementPtr>& elements, std::map<std::string, std::vector<Item>>& out, ModelDiffResult& result) {
        for (const auto& element : elements) {
            if (!element || isRoot(element.get())) continue;
            const std::string type = element->getType();
            if (isChainFeature(element.get())) {
                ++result.excluded["element"][kChainReason];
                continue;
            }
            const auto qn = ourName(element.get(), 0);

            if (qn && !isPlainRelationship(element.get())) {
                ++result.comparedElements;
                out["element"].push_back({*qn, type});
                const auto owningRelationship = element->owningRelationship();
                const auto membership = std::dynamic_pointer_cast<KerML::Entities::Membership>(owningRelationship);
                out["membership"].push_back({*qn, (owningRelationship ? owningRelationship->getType() : std::string("(none)")) + " [" +
                                                      (membership ? visibilityName(membership->visibility()) : "public") + "]"});
                const auto owningNamespace = element->owningNamespace();
                std::string ownerText = "(none)";
                if (owningNamespace) {
                    const auto ownerName = ourName(owningNamespace.get(), 0);
                    ownerText = ownerName ? shown(*ownerName) : "(unnamed " + owningNamespace->getType() + ")";
                }
                out["owner"].push_back({*qn, ownerText});
            }

            // aliases: memberships that do not own their member
            if (type == "Membership") {
                const auto membership = std::dynamic_pointer_cast<KerML::Entities::Membership>(element);
                const std::string memberName = Xmi::unquoteName(membership->memberName().value_or(""));
                const std::string memberShortName = Xmi::unquoteName(membership->memberShortName().value_or(""));
                if (membership && (!memberName.empty() || !memberShortName.empty())) {
                    Element* owner = ownerOf(element.get());
                    const auto ownerName = owner ? ourName(owner, 0) : std::optional<std::string>(std::string());
                    const std::string key = (ownerName ? shown(*ownerName) : std::string("(unnamed owner)")) + " :: " + memberName + "|" +
                                            memberShortName;
                    out["alias"].push_back({key, targetName(membership->memberElement()) + " [" + visibilityName(membership->visibility()) + "]"});
                }
            }

            // explicit relationships
            std::shared_ptr<Element> source;
            std::shared_ptr<Element> target;
            bool relationship = false;
            if (const auto specialization = std::dynamic_pointer_cast<KerML::Entities::Specialization>(element)) {
                relationship = true;
                source = specialization->specific();
                target = specialization->general();
                // `subset a.b subsets c.d;` is owned by the enclosing type in our model; in the XMI the subsetting feature is an
                // anonymous chain Feature (see kChainReason), so the relationship is not comparable.
                const auto owningElement = specialization->owningRelatedElement();
                if (owningElement && source && (owningElement != source || source == target) && dynamic_cast<KerML::Entities::Membership*>(owningElement.get()) == nullptr) {
                    ++result.excluded["rel"][kChainReason];
                    continue;
                }
            } else if (const auto conjugation = std::dynamic_pointer_cast<KerML::Entities::Conjugation>(element)) {
                relationship = true;
                source = conjugation->conjungatedType();
                target = conjugation->originalType();
            }
            if (relationship) {
                if (!source) source = element->owner();
                const auto sourceName = ourName(source.get(), 0);
                if (!sourceName || sourceName->empty()) {
                    ++result.skippedRelationships;
                    continue;
                }
                if (canTargetChain(type) && chainTargets_.count(type + "|" + *sourceName + "|" + targetName(target)) != 0) {
                    ++result.excluded["rel"][kChainReason];
                    continue;
                }
                ++result.comparedRelationships;
                out["rel"].push_back({type + " : " + *sourceName, targetName(target)});
                const auto relationshipOwner = dynamic_cast<KerML::Entities::Relationship*>(element.get())->owningRelatedElement();
                std::string ownerText = "(none)";
                if (relationshipOwner) {
                    const auto ownerName = ourName(relationshipOwner.get(), 0);
                    ownerText = ownerName ? shown(*ownerName) : "(unnamed " + relationshipOwner->getType() + ")";
                }
                out["relOwner"].push_back({type + " : " + *sourceName + " -> " + targetName(target), ownerText});
            }
        }
    }

    // ------------------------------------------------------------------------------------------------ the oracle

    std::string xmiTargetName(const Xmi::File& file, const Xmi::Element& element) {
        static const char* roles[] = {"type",           "superclassifier",   "subsettedFeature", "redefinedFeature", "referencedFeature",
                                      "crossedFeature", "general",           "originalType",     "originalPortDefinition"};
        for (const char* role : roles) {
            if (const auto* reference = element.reference(role)) {
                const auto [targetFile, index] = corpus_.resolve(file, *reference);
                if (!targetFile) return "(missing target " + reference->id + ")";
                const auto name = corpus_.qualifiedName(*targetFile, index);
                return name ? shown(*name) : "(unnamed " + targetFile->elements[static_cast<size_t>(index)].type + ")";
            }
        }
        return "(none)";
    }

    void collectXmi(const Xmi::File& file, std::map<std::string, std::vector<Item>>& out, ModelDiffResult& result) {
        for (size_t i = 0; i < file.elements.size(); ++i) {
            const auto& element = file.elements[i];
            const int index = static_cast<int>(i);
            if (element.parent < 0) continue;
            if (!element.isOwnedRelationship) {
                const auto qn = corpus_.qualifiedName(file, index);
                if (!qn) continue;
                ++result.comparedElements;
                out["element"].push_back({*qn, element.type});
                const auto& membership = file.elements[static_cast<size_t>(element.owningRelationship)];
                out["membership"].push_back({*qn, membership.type + " [" + (membership.visibility.empty() ? "public" : membership.visibility) + "]"});
                const auto ownerName = corpus_.qualifiedName(file, element.parent);
                out["owner"].push_back({*qn, ownerName ? shown(*ownerName) : "(unnamed " + file.elements[static_cast<size_t>(element.parent)].type + ")"});
                continue;
            }
            const auto& parent = file.elements[static_cast<size_t>(element.parent)];
            (void)parent;
            if (element.type == "Membership" && (!element.memberName.empty() || !element.memberShortName.empty())) {
                const auto ownerName = corpus_.qualifiedName(file, element.parent);
                const std::string key = (ownerName ? shown(*ownerName) : std::string("(unnamed owner)")) + " :: " + element.memberName + "|" + element.memberShortName;
                std::string target = "(none)";
                if (const auto* reference = element.reference("memberElement")) {
                    const auto [targetFile, targetIndex] = corpus_.resolve(file, *reference);
                    if (!targetFile) {
                        target = "(missing target " + reference->id + ")";
                    } else {
                        const auto name = corpus_.qualifiedName(*targetFile, targetIndex);
                        target = name ? shown(*name) : "(unnamed " + targetFile->elements[static_cast<size_t>(targetIndex)].type + ")";
                    }
                }
                out["alias"].push_back({key, target + " [" + (element.visibility.empty() ? "public" : element.visibility) + "]"});
                continue;
            }
            if (isTargetedRelationship(element.type)) {
                const auto sourceName = corpus_.qualifiedName(file, element.parent);
                if (!sourceName || sourceName->empty()) {
                    ++result.skippedRelationships;
                    continue;
                }
                bool chain = false;
                for (const char* role : {"type", "superclassifier", "subsettedFeature", "redefinedFeature", "referencedFeature", "crossedFeature", "general"}) {
                    if (const auto* reference = element.reference(role)) {
                        const auto [targetFile, targetIndex] = corpus_.resolve(file, *reference);
                        if (canTargetChain(element.type) && targetFile != nullptr && isXmiChain(*targetFile, targetIndex)) {
                            chain = true;
                            // our model targets the last feature of the chain
                            std::string last = "(none)";
                            for (const auto& candidate : targetFile->elements) {
                                if (candidate.type != "FeatureChaining" || candidate.parent != targetIndex) continue;
                                if (const auto* chaining = candidate.reference("chainingFeature")) {
                                    const auto [chainFile, chainIndex] = corpus_.resolve(*targetFile, *chaining);
                                    const auto name = chainFile ? corpus_.qualifiedName(*chainFile, chainIndex) : std::nullopt;
                                    last = name ? shown(*name) : "(unnamed)";
                                }
                            }
                            chainTargets_.insert(element.type + "|" + *sourceName + "|" + last);
                        }
                        break;
                    }
                }
                if (chain) {
                    ++result.excluded["rel"][kChainReason];
                    continue;
                }
                ++result.comparedRelationships;
                const std::string target = xmiTargetName(file, element);
                out["rel"].push_back({element.type + " : " + *sourceName, target});
                out["relOwner"].push_back({element.type + " : " + *sourceName + " -> " + target, shown(*sourceName)});
            }
        }
    }

    // ------------------------------------------------------------------------------------------------ the difference

    bool excluded(const std::string& category, const Item& item, ModelDiffResult& result) const {
        for (const auto& exclusion : exclusions_) {
            if (exclusion.category == category && exclusion.matches(item.first, item.second)) {
                ++result.excluded[category][exclusion.reason];
                return true;
            }
        }
        return false;
    }

    void diffCategory(const std::string& category, std::vector<Item> expected, std::vector<Item> actual, ModelDiffResult& result) const {
        std::sort(expected.begin(), expected.end());
        std::sort(actual.begin(), actual.end());
        std::vector<Item> missing;
        std::vector<Item> extra;
        std::set_difference(expected.begin(), expected.end(), actual.begin(), actual.end(), std::back_inserter(missing));
        std::set_difference(actual.begin(), actual.end(), expected.begin(), expected.end(), std::back_inserter(extra));
        auto& messages = result.differences[category];
        // A missing and an extra item with the same id are one difference ("differs").
        std::multimap<std::string, Item> extraById;
        for (const auto& item : extra) extraById.emplace(item.first, item);
        for (const auto& item : missing) {
            auto match = extraById.find(item.first);
            if (match != extraById.end()) {
                if (!excluded(category, item, result)) {
                    messages.push_back("differs   " + item.first + "\n            expected: " + item.second + "\n            actual:   " + match->second.second);
                }
                extraById.erase(match);
            } else if (!excluded(category, item, result)) {
                messages.push_back("missing   " + item.first + (item.second.empty() ? "" : "  =>  " + item.second));
            }
        }
        for (const auto& [id, item] : extraById) {
            if (!excluded(category, item, result)) messages.push_back("extra     " + id + (item.second.empty() ? "" : "  =>  " + item.second));
        }
    }
};

inline std::vector<XmiExclusion> documentedXmiExclusions() {
    // Nothing is excluded by pattern: the one excluded category (feature chains, kChainReason) is recognized structurally by ModelDiff.
    std::vector<XmiExclusion> exclusions;
    return exclusions;
}

}  // namespace ConformanceTest
