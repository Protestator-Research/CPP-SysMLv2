//
// Scoped, qualified name resolution over the union of all sources of a Workspace. See Resolver.h.
//
#include <limits>
#include <typeinfo>
#include "Resolver.h"
#include "ImplicitGenerals.h"

#include <kerml/root/elements/NameEscaping.h>
#include <kerml/root/elements/Relationship.h>
#include <kerml/root/namespaces/Namespace.h>
#include <kerml/kernel/functions/ReturnParameterMembership.h>
#include <kerml/kernel/functions/Function.h>
#include <kerml/kernel/expressions/ConstructorExpression.h>
#include <kerml/kernel/expressions/FeatureChainExpression.h>
#include <kerml/kernel/expressions/FeatureReferenceExpression.h>
#include <kerml/kernel/expressions/IndexExpression.h>
#include <kerml/kernel/expressions/InstantiationExpression.h>
#include <kerml/kernel/expressions/InvocationExpression.h>
#include <kerml/kernel/expressions/NullExpression.h>
#include <kerml/core/features/Redefinition.h>
#include <kerml/kernel/featurevalues/FeatureValue.h>
#include <kerml/kernel/functions/Expression.h>
#include <kerml/kernel/expressions/OperatorExpression.h>
#include <kerml/kernel/expressions/SelectExpression.h>

#include <algorithm>
#include <cstdint>
#include <functional>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>

namespace SysMLv2::Files::Detail {

    using KerML::Entities::Classifier;
    using KerML::Entities::Element;
    using KerML::Entities::Feature;
    using KerML::Entities::Namespace;
    using KerML::Entities::Relationship;
    using KerML::Entities::Type;
    using KerML::Entities::VisibilityKind;

    namespace {
        /// The name that the text of a name in a reference stands for (quotes and escapes removed). Declared names are stored without quotes
        /// (the parsers apply KerML::Names::unescapeName() once) and are not passed through this.
        std::string normalizeName(const std::string& raw) { return KerML::Names::unescapeName(raw); }

        /// Splits "A::'b c'::d.e" at "::" and "." outside of quotes. A leading "$::" sets @p global.
        std::vector<std::string> splitName(const std::string& text, bool& global) {
            global = false;
            std::vector<std::string> segments;
            std::string current;
            bool quoted = false;
            for (size_t i = 0; i < text.size(); ++i) {
                const char c = text[i];
                if (quoted) {
                    current.push_back(c);
                    if (c == '\\' && i + 1 < text.size()) {
                        current.push_back(text[++i]);
                    } else if (c == '\'') {
                        quoted = false;
                    }
                    continue;
                }
                if (c == '\'') {
                    quoted = true;
                    current.push_back(c);
                } else if (c == ':' && i + 1 < text.size() && text[i + 1] == ':') {
                    segments.push_back(current);
                    current.clear();
                    ++i;
                } else if (c == '.') {
                    segments.push_back(current);
                    current.clear();
                } else if (c == ' ' || c == '\t' || c == '\r' || c == '\n') {
                    // whitespace between tokens is not part of a name
                } else {
                    current.push_back(c);
                }
            }
            segments.push_back(current);
            if (segments.size() > 1 && segments.front() == "$") {
                global = true;
                segments.erase(segments.begin());
            }
            for (auto& segment : segments) segment = normalizeName(segment);
            return segments;
        }

        /// True for a feature chain `a.b.c` (a '.' outside of quotes).
        bool isChain(const std::string& name) {
            bool quoted = false;
            for (size_t i = 0; i < name.size(); ++i) {
                const char c = name[i];
                if (quoted) {
                    if (c == '\\' && i + 1 < name.size()) ++i;
                    else if (c == '\'') quoted = false;
                } else if (c == '\'') {
                    quoted = true;
                } else if (c == '.') {
                    return true;
                }
            }
            return false;
        }

        enum class Access : int {
            Local = 0,   // everything (a name used inside the namespace or one of its enclosed scopes)
            All = 1,     // everything (`import all`)
            Inherit = 2, // public and protected (members inherited by a specialization)
            Public = 3   // public only (qualified access from outside, plain imports)
        };

        bool visibleUnder(VisibilityKind visibility, Access access) {
            switch (access) {
                case Access::Local:
                case Access::All: return true;
                case Access::Inherit: return visibility != KerML::Entities::PRIVATE;
                case Access::Public: return visibility == KerML::Entities::PUBLIC;
            }
            return false;
        }
    }

    struct Resolver::Impl {
        struct Scope;
        struct Entry {
            std::shared_ptr<Element> element;
            VisibilityKind visibility = KerML::Entities::PUBLIC;
            const AliasRecord* alias = nullptr;
            /// Level of the source of an alias (an alias has no element of its own that could tell it).
            int level = 0;
        };
        struct Child {
            const Scope* scope = nullptr;
            VisibilityKind visibility = KerML::Entities::PUBLIC;
        };
        struct Scope {
            std::shared_ptr<Element> element;
            const Scope* parent = nullptr;
            size_t depth = 0;
            /// The source this scope was indexed for (a scope never links to a scope of another source: parent and children are
            /// those of the same source).
            size_t source = 0;
            std::unordered_map<std::string, std::vector<Entry>> members;
            std::vector<const ImportRecord*> imports;
            std::vector<Child> children;
            /// -1: not computed; otherwise whether the element declares end features of its own.
            mutable signed char declaresEnds = -1;
        };
        struct Query {
            ReferenceKind kind = ReferenceKind::Element;
            const Element* exclude = nullptr;
            /// The lookup goes through the general types of a type that declares end features: the inherited end features
            /// are redefined by the declared ones (by position) and are not visible under their own names.
            bool hideEnds = false;
            /// Elements of sources of a higher level are invisible (see SourceInput::level).
            int maxLevel = std::numeric_limits<int>::max();
            /// The owned members of this scope are not candidates (the redefinition of a feature does not find its owner's own members).
            const Scope* skipOwnedOf = nullptr;
            /// The scope of a feature whose value expression the reference is written in: the lookup of the first segment does not start there.
            const Scope* skipStart = nullptr;
        };
        using Visited = std::vector<std::pair<const Scope*, unsigned>>;

        /// What the indexing of one source put into the tables below. removeSources() takes it out again. The pointers are only
        /// used as keys (never dereferenced): the elements, aliases and imports of a replaced source may be freed already.
        struct SourceRecord {
            SourceRecord() = default;
            SourceRecord(SourceRecord&&) noexcept = default;
            SourceRecord& operator=(SourceRecord&&) noexcept = default;
            SourceRecord(const SourceRecord&) = delete;
            SourceRecord& operator=(const SourceRecord&) = delete;
            std::vector<std::unique_ptr<Scope>> scopes;
            /// Every element visited by the indexing (scopes and transparent relationships, the root).
            std::vector<const Element*> elements;
            std::vector<const Element*> visibilityKeys;
            std::vector<const ImportRecord*> imports;
            /// The placeholders whose redirect was set by a reference of this source.
            std::vector<const Element*> redirectKeys;
            /// The elements that got a general type (generals) from a reference of this source: they can belong to another source.
            std::vector<const Element*> generalKeys;
            /// The elements whose provisional or effective name was registered because of a reference of this source.
            std::vector<const Element*> registeredKeys;
            /// What the root of the source contributed to `global` when it was indexed (the order of `global` is the order of the sources).
            std::unordered_map<std::string, std::vector<Entry>> globalContribution;
        };
        std::vector<SourceRecord> records;
        size_t currentSource = 0;
        /// removeSources() met something that only a new index can repair (see there): canReplace() is false from then on.
        bool tainted = false;
        /// Level of every source (by index), of every indexed element, and the level that is currently indexed.
        std::vector<int> sourceLevels;
        std::unordered_map<const Element*, int> elementLevel;
        int currentLevel = 0;
        int lowestLevel = 0;
        int levelOfSource(size_t source) const { return source < sourceLevels.size() ? sourceLevels[source] : lowestLevel; }
        int levelOf(const Element* element) const {
            auto it = elementLevel.find(element);
            return it == elementLevel.end() ? lowestLevel : it->second;
        }
        std::vector<Scope*> sourceRoots;
        std::unordered_map<const Element*, Scope*> scopeOf;
        /// Relationships (memberships, imports, ...) are transparent: they map to the scope their owned elements belong to.
        /// An association or connector is a relationship and a namespace at the same time and is a scope like any other type.
        std::unordered_map<const Element*, Scope*> relationshipScope;
        std::unordered_map<std::string, std::vector<Entry>> global;
        std::unordered_map<const Element*, VisibilityKind> visibility;
        std::unordered_map<const ImportRecord*, std::string> importedName;
        std::unordered_map<const Element*, std::vector<std::shared_ptr<Element>>> generals;
        /// The position of the reference that made a general type known, parallel to the lists of generals: the lists are kept in the
        /// order of the declarations, however late (in which run, after which source was added) a reference is resolved.
        std::unordered_map<const Element*, std::vector<std::uint64_t>> generalOrdinals;
        /// The place of a reference in the order of the declarations: the source, then the position within the source
        /// (PendingReference::order). It does not depend on which other sources exist or how many references are resolved.
        static std::uint64_t ordinalOf(const PendingReference& reference) {
            return (static_cast<std::uint64_t>(reference.source) << 32) | (static_cast<std::uint64_t>(reference.order) & 0xFFFFFFFFull);
        }
        static size_t sourceOfOrdinal(std::uint64_t ordinal) { return static_cast<size_t>(ordinal >> 32); }

        /// Remembers that the reference makes the placeholder stand for @p target.
        void setRedirect(const PendingReference& reference, const std::shared_ptr<Element>& target) {
            auto [it, inserted] = redirect.emplace(reference.placeholder.get(), target);
            if (inserted) {
                if (reference.source < records.size()) records[reference.source].redirectKeys.push_back(reference.placeholder.get());
            } else {
                it->second = target;
            }
        }
        // A reference may name the *specific* element of another reference through its placeholder (`subclassifier A specializes B`:
        // A is itself a reference). Once A is resolved, its placeholder stands for the resolved element.
        std::unordered_map<const Element*, std::shared_ptr<Element>> redirect;

        const Element* canonical(const std::shared_ptr<Element>& element) const {
            if (!element) return nullptr;
            auto found = redirect.find(element.get());
            return found != redirect.end() ? found->second.get() : element.get();
        }
        std::unordered_set<const Element*> visitedElements;
        size_t detached = 0;
        // Library elements named by implicitGenerals(), looked up once (null: not loaded), and the implicit generals of each element.
        mutable std::unordered_map<std::string, std::shared_ptr<Element>> libraryElements;
        mutable std::unordered_map<const Element*, std::vector<std::shared_ptr<Element>>> implicitOf;

        // Resolution order. A name may be found before the generalizations of a type it passes through are known (a redefinition
        // of `x` in a feature whose typing is still pending would find the `x` of an outer namespace or of an implicit general).
        // A result that was obtained while looking through the inherited members of a type with pending generalizations is
        // therefore deferred until they are resolved (`strictOrder`), unless nothing else can make progress.
        mutable std::unordered_map<const Element*, int> pendingGenerals;
        mutable bool incomplete = false;
        /// Set by resolveReference(): the result of a redefinition came from the enclosing namespaces while generals of its owner are pending.
        mutable bool redefinitionOwnerPending = false;
        mutable const Element* ignoreIncomplete = nullptr;
        void noteInheritance(const Element* element) const {
            if (element == nullptr || element == ignoreIncomplete || pendingGenerals.empty()) return;
            auto it = pendingGenerals.find(element);
            if (it != pendingGenerals.end() && it->second > 0) incomplete = true;
        }

        const std::vector<std::shared_ptr<Element>>& implicitGeneralsOf(const std::shared_ptr<Element>& element) const {
            // The entry is created first: looking up the library names below may ask for the implicit generals of this element again
            // (for example when the element is itself named like a package of the library); that inner request sees no generals.
            auto [entry, inserted] = implicitOf.emplace(element.get(), std::vector<std::shared_ptr<Element>>());
            std::vector<std::shared_ptr<Element>>& slot = entry->second;  // references stay valid when the map is rehashed
            if (!inserted) return slot;
            std::vector<std::shared_ptr<Element>> result;
            if (!isUnresolved(element)) {
                for (const char* name : implicitGenerals(element.get())) {
                    auto found = libraryElements.find(name);
                    if (found == libraryElements.end()) {
                        libraryElements.emplace(name, nullptr);
                        bool globalOnly = false;
                        const auto segments = splitName(name, globalOnly);
                        Query query;
                        query.maxLevel = lowestLevel;  // the implicit generals are library elements: a model must not shadow them
                        auto library = resolveSegments(segments, true, nullptr, query);
                        found = libraryElements.find(name);
                        found->second = library;
                    }
                    if (found->second && found->second != element) result.push_back(found->second);
                }
            }
            slot = std::move(result);
            return slot;
        }

        Scope* newScope(const std::shared_ptr<Element>& element, const Scope* parent) {
            records[currentSource].scopes.push_back(std::make_unique<Scope>());
            Scope* scope = records[currentSource].scopes.back().get();
            scope->source = currentSource;
            scope->element = element;
            scope->parent = parent;
            scope->depth = parent ? parent->depth + 1 : 0;
            return scope;
        }

        VisibilityKind visibilityOf(const Element* element) const {
            auto it = visibility.find(element);
            return it == visibility.end() ? KerML::Entities::PUBLIC : it->second;
        }

        void addNames(Scope* scope, const std::shared_ptr<Element>& element, const AliasRecord* alias, VisibilityKind vis,
                      const std::string& name, const std::string& shortName) {
            if (!name.empty()) scope->members[name].push_back({element, vis, alias, currentLevel});
            if (!shortName.empty() && shortName != name) scope->members[shortName].push_back({element, vis, alias, currentLevel});
        }

        /// One element of the walk of visit() whose owned elements are still being visited.
        struct VisitFrame {
            std::vector<std::shared_ptr<Element>> children;
            /// The index of the next child to visit; the children before it are visited or being visited.
            size_t next = 0;
            /// The number of children whose visit is complete (the checks that follow a visit were made).
            size_t done = 0;
            /// The scope that the children are members of.
            Scope* childScope = nullptr;
            /// The element is a return parameter membership: a child without a name is known as `result`.
            bool returnParameter = false;
        };

        /// Indexes @p element and everything it owns (depth first, in the order of ownedElements()). The walk keeps its own stack of frames instead
        /// of recursing: a model can be nested as deep as the text (an expression `1 + 1 + ... + 1` with 100000 terms is a tree 100000 levels deep).
        void visit(const std::shared_ptr<Element>& root, Scope* rootScope) {
            std::vector<VisitFrame> stack;
            // Indexes one element; if it has owned elements, a frame for them is pushed.
            const auto enter = [&](const std::shared_ptr<Element>& element, Scope* memberScope) {
                if (!element || !visitedElements.insert(element.get()).second) return;
                records[currentSource].elements.push_back(element.get());
                elementLevel[element.get()] = currentLevel;
                VisitFrame frame;
                if (dynamic_cast<const Relationship*>(element.get()) != nullptr && dynamic_cast<const Namespace*>(element.get()) == nullptr) {
                    relationshipScope[element.get()] = memberScope;
                    frame.returnParameter = dynamic_cast<const KerML::Entities::ReturnParameterMembership*>(element.get()) != nullptr;
                    frame.childScope = memberScope;
                } else {
                    const VisibilityKind vis = visibilityOf(element.get());
                    addNames(memberScope, element, nullptr, vis, element->declaredName().value_or(""), element->declaredShortName().value_or(""));
                    Scope* scope = newScope(element, memberScope);
                    scopeOf[element.get()] = scope;
                    memberScope->children.push_back({scope, vis});
                    frame.childScope = scope;
                }
                frame.children = element->ownedElements();
                if (!frame.children.empty()) stack.push_back(std::move(frame));
            };
            enter(root, rootScope);
            while (!stack.empty()) {
                VisitFrame& frame = stack.back();
                if (frame.done < frame.next) {
                    // The visit of the previous child is complete.
                    const auto& child = frame.children[frame.done++];
                    // A return parameter without a name is known as `result` (it redefines Evaluation::result).
                    if (frame.returnParameter && child && !child->declaredName().has_value() && !child->declaredShortName().has_value() &&
                        dynamic_cast<const Feature*>(child.get()) != nullptr) {
                        frame.childScope->members["result"].push_back({child, visibilityOf(child.get()), nullptr});
                    }
                }
                if (frame.next == frame.children.size()) {
                    stack.pop_back();
                    continue;
                }
                const std::shared_ptr<Element> child = frame.children[frame.next++];
                enter(child, frame.childScope);   // (may push: `frame` is not used again in this iteration)
            }
        }

        /// Indexes @p source as the source number @p index: a new one (index == number of the indexed sources), or one that
        /// removeSources() took out before (it keeps its level).
        void indexSource(const SourceInput& source, size_t index) {
            const bool fresh = index == sourceRoots.size();
            if (fresh) {
                records.emplace_back();
                sourceRoots.push_back(nullptr);
                sourceLevels.push_back(source.level);
                lowestLevel = sourceLevels.size() == 1 ? source.level : std::min(lowestLevel, source.level);
            } else {
                sourceLevels[index] = source.level;
            }
            currentSource = index;
            Scope* root = newScope(nullptr, nullptr);
            sourceRoots[index] = root;
            currentLevel = source.level;
            if (!source.elements || !source.data) return;
            for (const auto& [element, vis] : source.data->visibility) {
                visibility[element] = vis;
                records[index].visibilityKeys.push_back(element);
            }

            if (source.data->root) {
                root->element = source.data->root;
                scopeOf[source.data->root.get()] = root;
                if (visitedElements.insert(source.data->root.get()).second) records[index].elements.push_back(source.data->root.get());
                elementLevel[source.data->root.get()] = currentLevel;
                for (const auto& child : source.data->root->ownedElements()) visit(child, root);
            }
            std::unordered_set<const Element*> owned;
            for (const auto& element : *source.elements) {
                if (!element) continue;
                for (const auto& child : element->ownedElements()) owned.insert(child.get());
            }
            if (source.data->root) {
                for (const auto& child : source.data->root->ownedElements()) owned.insert(child.get());
            }
            for (const auto& element : *source.elements) {
                if (!element || owned.count(element.get()) != 0) continue;
                visit(element, root);
            }
            // Anything the walk above could not reach (owned by an element that is not itself reachable) is still visited
            // so that its own children get scopes.
            for (const auto& element : *source.elements) {
                if (element && visitedElements.count(element.get()) == 0) visit(element, root);
            }

            for (const auto& alias : source.data->aliases) {
                Scope* scope = root;
                if (alias->owner) {
                    if (const Scope* owner = scopeFor(alias->owner.get())) scope = const_cast<Scope*>(owner);
                }
                addNames(scope, nullptr, alias.get(), alias->visibility, alias->name, alias->shortName);
            }
            for (const auto& import : source.data->imports) {
                Scope* scope = root;
                if (import->owner) {
                    // The owner may be the (transparent) membership that contains the import.
                    if (const Scope* owner = scopeFor(import->owner.get())) scope = const_cast<Scope*>(owner);
                }
                scope->imports.push_back(import.get());
                records[index].imports.push_back(import.get());
                bool globalPrefix = false;
                auto segments = splitName(import->target, globalPrefix);
                importedName[import.get()] = segments.empty() ? std::string() : segments.back();
            }
        }

        /// Adds the members of the roots of the sources from @p first on to the implicit global namespace.
        void buildGlobal(size_t first) {
            for (size_t index = first; index < sourceRoots.size(); ++index) {
                const Scope* root = sourceRoots[index];
                if (root == nullptr) continue;
                records[index].globalContribution = root->members;
                for (const auto& [name, entries] : root->members) {
                    auto& target = global[name];
                    target.insert(target.end(), entries.begin(), entries.end());
                }
            }
        }

        /// Builds the entries of `global` for @p names again from what the sources contributed, in the order of the sources.
        void rebuildGlobal(const std::set<std::string>& names) {
            for (const auto& name : names) {
                std::vector<Entry> entries;
                for (const auto& record : records) {
                    auto found = record.globalContribution.find(name);
                    if (found != record.globalContribution.end()) entries.insert(entries.end(), found->second.begin(), found->second.end());
                }
                if (entries.empty()) global.erase(name);
                else global[name] = std::move(entries);
            }
        }

        const Scope* scopeFor(const Element* element) const {
            if (!element) return nullptr;
            auto it = scopeOf.find(element);
            if (it != scopeOf.end()) return it->second;
            auto rel = relationshipScope.find(element);
            if (rel != relationshipScope.end()) return rel->second;
            return nullptr;
        }

        bool accepts(const Query& q, const Element* element) const {
            if (!element || element == q.exclude) return false;
            if (q.maxLevel != std::numeric_limits<int>::max() && levelOf(element) > q.maxLevel) return false;
            switch (q.kind) {
                case ReferenceKind::Element: return true;
                case ReferenceKind::Namespace: return dynamic_cast<const Namespace*>(element) != nullptr;
                case ReferenceKind::Type: return dynamic_cast<const Type*>(element) != nullptr;
                case ReferenceKind::Classifier: return dynamic_cast<const Classifier*>(element) != nullptr;
                case ReferenceKind::Feature: return dynamic_cast<const Feature*>(element) != nullptr;
            }
            return false;
        }

        static bool markVisited(Visited& visited, const Scope* scope, Access access) {
            const unsigned bit = 1u << static_cast<int>(access);
            for (auto& entry : visited) {
                if (entry.first == scope) {
                    if ((entry.second & bit) != 0) return false;
                    entry.second |= bit;
                    return true;
                }
            }
            visited.emplace_back(scope, bit);
            return true;
        }

        std::shared_ptr<Element> lookupRecursive(const Scope* scope, const std::string& name, Access access, const Query& q,
                                                 Visited& visited) const {
            // (depth first with a stack of its own: the scopes are nested as deep as the packages of the text)
            if (auto found = lookupIn(scope, name, access, q, visited)) return found;
            std::vector<std::pair<const Scope*, size_t>> stack;
            stack.emplace_back(scope, 0);
            while (!stack.empty()) {
                const Scope* current = stack.back().first;
                if (stack.back().second == current->children.size()) {
                    stack.pop_back();
                    continue;
                }
                const auto& child = current->children[stack.back().second++];
                if (!visibleUnder(child.visibility, access)) continue;
                if (auto found = lookupIn(child.scope, name, access, q, visited)) return found;
                stack.emplace_back(child.scope, 0);
            }
            return nullptr;
        }

        static bool isEndFeature(const Element* element) {
            auto* feature = dynamic_cast<const Feature*>(element);
            return feature != nullptr && const_cast<Feature*>(feature)->isEnd();
        }

        bool declaresEnd(const Scope* scope) const {
            if (scope->declaresEnds < 0) {
                scope->declaresEnds = 0;
                for (const auto& child : scope->children) {
                    if (child.scope && isEndFeature(child.scope->element.get())) {
                        scope->declaresEnds = 1;
                        break;
                    }
                }
            }
            return scope->declaresEnds == 1;
        }

        /// Of several inherited features with the same name, the one that redefines the others: a feature that is redefined is not
        /// inherited (`Occurrence::self` redefines `Anything::self`, `suboccurrences::x` redefines `Occurrence::x`).
        std::shared_ptr<Element> mostSpecific(const std::vector<std::shared_ptr<Element>>& candidates) const {
            if (candidates.size() == 1) return candidates.front();
            // (a candidate whose own generalizations are not resolved yet may still turn out to redefine another candidate)
            for (const auto& candidate : candidates) noteInheritance(candidate.get());
            std::vector<char> redefined(candidates.size(), 0);
            for (size_t i = 0; i < candidates.size(); ++i) {
                std::vector<const Element*> stack{candidates[i].get()};
                std::unordered_set<const Element*> seen;
                while (!stack.empty()) {
                    const Element* current = stack.back();
                    stack.pop_back();
                    if (!seen.insert(current).second) continue;
                    auto gens = generals.find(current);
                    if (gens == generals.end()) continue;
                    for (const auto& general : gens->second) {
                        if (dynamic_cast<const Feature*>(general.get()) == nullptr) continue;
                        for (size_t j = 0; j < candidates.size(); ++j) {
                            if (j != i && candidates[j] == general) redefined[j] = 1;
                        }
                        stack.push_back(general.get());
                    }
                }
            }
            for (size_t i = 0; i < candidates.size(); ++i) {
                if (!redefined[i]) return candidates[i];
            }
            return candidates.front();
        }

        /// Members named @p name of @p scope: owned members and aliases, imported members, inherited members.
        std::shared_ptr<Element> lookupIn(const Scope* scope, const std::string& name, Access access, const Query& q,
                                          Visited& visited) const {
            if (!scope || !markVisited(visited, scope, access)) return nullptr;

            auto own = scope == q.skipOwnedOf ? scope->members.end() : scope->members.find(name);
            if (own != scope->members.end()) {
                for (const auto& entry : own->second) {
                    if (!visibleUnder(entry.visibility, access)) continue;
                    if (entry.alias && entry.level > q.maxLevel) continue;
                    const std::shared_ptr<Element>& target = entry.alias ? entry.alias->resolvedTarget : entry.element;
                    if (q.hideEnds && isEndFeature(target.get())) continue;
                    if (target && accepts(q, target.get())) return target;
                }
            }

            for (const ImportRecord* import : scope->imports) {
                if (!import->resolvedTarget) continue;
                if (!visibleUnder(import->visibility, access)) continue;
                if (import->isMembershipImport) {
                    auto it = importedName.find(import);
                    if (it != importedName.end() && it->second == name && accepts(q, import->resolvedTarget.get())) {
                        return import->resolvedTarget;
                    }
                    if (!import->isRecursive) continue;
                }
                const Scope* imported = scopeFor(import->resolvedTarget.get());
                if (!imported) continue;
                const Access importAccess = import->isImportAll ? Access::All : Access::Public;
                if (import->isRecursive) {
                    // `import N::**` is equivalent to `import N; import N::*;` plus the same for every visible owned namespace.
                    const Element* target = import->resolvedTarget.get();
                    if (!import->isMembershipImport) {
                        const std::string targetName = target->declaredName().value_or("");
                        const std::string targetShort = target->declaredShortName().value_or("");
                        if ((targetName == name || targetShort == name) && accepts(q, target)) return import->resolvedTarget;
                    }
                    if (auto found = lookupRecursive(imported, name, importAccess, q, visited)) return found;
                } else if (auto found = lookupIn(imported, name, importAccess, q, visited)) {
                    return found;
                }
            }

            if (scope->element) {
                noteInheritance(scope->element.get());
                Query inheritedQuery = q;
                if (declaresEnd(scope)) inheritedQuery.hideEnds = true;
                std::vector<std::shared_ptr<Element>> candidates;
                auto gens = generals.find(scope->element.get());
                if (gens != generals.end()) {
                    const Access inherited = (access == Access::Public) ? Access::Public : Access::Inherit;
                    // The features a feature subsets or redefines come before its types: they redefine the members of those types, and a
                    // redefined member is not inherited (KerML 8.3.3.1.9, Type::inheritedMemberships excludes redefined features).
                    for (int pass = 0; pass < 2; ++pass) {
                        for (const auto& general : gens->second) {
                            const bool isFeature = dynamic_cast<const Feature*>(general.get()) != nullptr;
                            if (isFeature != (pass == 0)) continue;
                            if (auto found = lookupIn(scopeFor(general.get()), name, inherited, inheritedQuery, visited)) {
                                if (dynamic_cast<const Feature*>(found.get()) == nullptr) return found;
                                candidates.push_back(std::move(found));
                            }
                        }
                    }
                }
                const Access implicitAccess = (access == Access::Public) ? Access::Public : Access::Inherit;
                for (const auto& general : implicitGeneralsOf(scope->element)) {
                    if (auto found = lookupIn(scopeFor(general.get()), name, implicitAccess, inheritedQuery, visited)) {
                        if (dynamic_cast<const Feature*>(found.get()) == nullptr) return found;
                        candidates.push_back(std::move(found));
                    }
                }
                if (!candidates.empty()) return mostSpecific(candidates);
            }
            return nullptr;
        }

        std::shared_ptr<Element> lookupIn(const Scope* scope, const std::string& name, Access access, const Query& q) const {
            Visited visited;
            return lookupIn(scope, name, access, q, visited);
        }

        /// The members that the element of @p scope inherits from its implicit general types only (not its own members, imports or declared general types).
        std::shared_ptr<Element> lookupImplicitOnly(const Scope* scope, const std::string& name, const Query& q) const {
            if (!scope || !scope->element) return nullptr;
            Query inheritedQuery = q;
            inheritedQuery.skipStart = nullptr;
            std::vector<std::shared_ptr<Element>> candidates;
            for (const auto& general : implicitGeneralsOf(scope->element)) {
                Visited visited;
                if (auto found = lookupIn(scopeFor(general.get()), name, Access::Inherit, inheritedQuery, visited)) {
                    if (dynamic_cast<const Feature*>(found.get()) == nullptr) return found;
                    candidates.push_back(std::move(found));
                }
            }
            return candidates.empty() ? nullptr : mostSpecific(candidates);
        }

        /// Candidates for the first segment of a name: the local namespace, then each enclosing namespace, then the global namespace.
        bool forEachStartCandidate(const Scope* start, bool globalOnly, const std::string& name, const Query& q,
                                   const std::function<bool(const std::shared_ptr<Element>&)>& callback) const {
            std::unordered_set<const Element*> seen;
            if (!globalOnly) {
                for (const Scope* scope = start; scope; scope = scope->parent) {
                    if (scope == q.skipStart) continue;
                    if (auto found = lookupIn(scope, name, Access::Local, q)) {
                        if (seen.insert(found.get()).second && callback(found)) return true;
                    }
                }
            }
            // The members that every feature has through the implicit general types of the pilot's specializations (`self`, `that`) come after the
            // enclosing namespaces: `feature this default self` inside Occurrence is Occurrence::self, which Occurrence owns, not Anything::self.
            if (q.skipStart != nullptr) {
                if (auto found = lookupImplicitOnly(q.skipStart, name, q)) {
                    if (seen.insert(found.get()).second && callback(found)) return true;
                }
            }
            auto it = global.find(name);
            if (it != global.end()) {
                for (const auto& entry : it->second) {
                    if (entry.visibility == KerML::Entities::PRIVATE) continue;
                    if (entry.alias && entry.level > q.maxLevel) continue;
                    const std::shared_ptr<Element>& target = entry.alias ? entry.alias->resolvedTarget : entry.element;
                    if (target && accepts(q, target.get()) && seen.insert(target.get()).second && callback(target)) return true;
                }
            }
            return false;
        }

        static bool encloses(const Scope* ns, const Scope* start) {
            for (const Scope* scope = start; scope; scope = scope->parent) {
                if (scope == ns) return true;
            }
            return false;
        }

        std::shared_ptr<Element> resolveSegments(const std::vector<std::string>& segments, bool globalOnly, const Scope* start,
                                                 const Query& finalQuery) const {
            if (segments.empty() || segments.front().empty()) return nullptr;
            std::shared_ptr<Element> result;
            if (segments.size() == 1) {
                forEachStartCandidate(start, globalOnly, segments[0], finalQuery, [&](const std::shared_ptr<Element>& candidate) {
                    result = candidate;
                    return true;
                });
                return result;
            }
            Query middle;
            middle.kind = ReferenceKind::Namespace;
            middle.maxLevel = finalQuery.maxLevel;
            middle.skipStart = finalQuery.skipStart;
            forEachStartCandidate(start, globalOnly, segments[0], middle, [&](const std::shared_ptr<Element>& candidate) {
                std::shared_ptr<Element> current = candidate;
                for (size_t i = 1; i < segments.size(); ++i) {
                    const Scope* ns = scopeFor(current.get());
                    if (!ns) return false;
                    const Query& q = (i + 1 == segments.size()) ? finalQuery : middle;
                    // Names used inside a namespace may refer to its private members by qualified name.
                    const Access access = encloses(ns, start) ? Access::Local : Access::Public;
                    current = lookupIn(ns, segments[i], access, q);
                    if (!current) return false;
                }
                result = current;
                return true;
            });
            return result;
        }

        /// The scope of the feature whose value expression @p pending is written in (the expression is the value of its FeatureValue), else null.
        /// A name in the value expression of a feature is looked up from the namespace that owns the feature, not in the feature itself: the members
        /// that the feature has through its own types (`attribute xUnit : LengthUnit = mRefs#(1)` does not mean the `mRefs` of LengthUnit) are not
        /// visible there. (This is what the pilot implementation binds: for the 46 references of the standard library that it changes, the 42 new
        /// bindings are those of the pilot's XMI, and none of the 32 that go is.)
        const Scope* valueOwnerScope(const PendingReference& pending) const {
            const Element* current = pending.context.get();
            // (the link of the feature chain of an invoked type, or any other plain feature that an expression owns)
            if (current != nullptr && typeid(*current) == typeid(Feature)) {
                const auto owner = current->owner();
                if (owner && dynamic_cast<const KerML::Entities::Expression*>(owner.get()) != nullptr) current = owner.get();
            }
            // (the reference is written directly in the value: the parser records the feature value as its context)
            if (dynamic_cast<const KerML::Entities::FeatureValue*>(current) != nullptr) {
                const auto owner = current->owner();
                return owner && dynamic_cast<const Feature*>(owner.get()) != nullptr ? scopeFor(owner.get()) : nullptr;
            }
            while (current != nullptr && dynamic_cast<const KerML::Entities::Expression*>(current) != nullptr) {
                const auto next = current->owner();
                if (next && dynamic_cast<const KerML::Entities::Expression*>(next.get()) == nullptr) {
                    if (dynamic_cast<const Feature*>(next.get()) == nullptr) return nullptr;
                    for (const auto& relationship : next->ownedRelationship()) {
                        const auto value = std::dynamic_pointer_cast<KerML::Entities::FeatureValue>(relationship);
                        if (value && value->value().get() == current) return scopeFor(next.get());
                    }
                    return nullptr;
                }
                current = next.get();
            }
            return nullptr;
        }

        std::shared_ptr<Element> resolveReference(const PendingReference& pending) const {
            bool globalOnly = false;
            const auto segments = splitName(pending.name, globalOnly);
            const Scope* own = scopeFor(pending.context.get());
            const Scope* start = pending.relativeToOwner ? (own ? own->parent : nullptr) : own;
            Query finalQuery;
            finalQuery.kind = pending.kind;
            finalQuery.exclude = canonical(pending.specific);
            finalQuery.maxLevel = levelOfSource(pending.source);
            finalQuery.skipStart = valueOwnerScope(pending);

            if (pending.role == ReferenceRole::Redefinition && segments.size() == 1 && start && start->element) {
                noteInheritance(start->element.get());
                std::vector<std::shared_ptr<Element>> candidates;
                auto gens = generals.find(start->element.get());
                if (gens != generals.end()) {
                    // (features first, as in lookupIn: their members redefine those of their types)
                    for (int pass = 0; pass < 2; ++pass) {
                        for (const auto& general : gens->second) {
                            const bool isFeature = dynamic_cast<const Feature*>(general.get()) != nullptr;
                            if (isFeature != (pass == 0)) continue;
                            Visited visited;
                            if (auto found = lookupIn(scopeFor(general.get()), segments[0], Access::Inherit, finalQuery, visited)) {
                                if (dynamic_cast<const Feature*>(found.get()) == nullptr) return found;
                                candidates.push_back(std::move(found));
                            }
                        }
                    }
                }
                for (const auto& general : implicitGeneralsOf(start->element)) {
                    Visited visited;
                    if (auto found = lookupIn(scopeFor(general.get()), segments[0], Access::Inherit, finalQuery, visited)) {
                        if (dynamic_cast<const Feature*>(found.get()) == nullptr) return found;
                        candidates.push_back(std::move(found));
                    }
                }
                if (!candidates.empty()) return mostSpecific(candidates);
                // An end feature redefines the end of the general types of its owner that it corresponds to (KerML 8.3.4.5.5, matched
                // here by name): `end feature source { feature redefines sourceOutput; }` finds sourceOutput in the inherited source.
                if (auto* endFeature = dynamic_cast<const Feature*>(start->element.get());
                    endFeature != nullptr && const_cast<Feature*>(endFeature)->isEnd() && start->parent && start->parent->element &&
                    endFeature->declaredName().has_value()) {
                    const std::string endName = *endFeature->declaredName();
                    std::vector<std::shared_ptr<Element>> ownerGenerals;
                    auto ownerGens = generals.find(start->parent->element.get());
                    if (ownerGens != generals.end()) ownerGenerals = ownerGens->second;
                    for (const auto& general : implicitGeneralsOf(start->parent->element)) ownerGenerals.push_back(general);
                    Query endQuery;
                    endQuery.kind = ReferenceKind::Feature;
                    endQuery.maxLevel = finalQuery.maxLevel;
                    endQuery.exclude = start->element.get();
                    for (const auto& general : ownerGenerals) {
                        Visited visitedEnd;
                        auto redefinedEnd = lookupIn(scopeFor(general.get()), endName, Access::Inherit, endQuery, visitedEnd);
                        if (!redefinedEnd) continue;
                        Visited visited;
                        if (auto found = lookupIn(scopeFor(redefinedEnd.get()), segments[0], Access::Inherit, finalQuery, visited)) return found;
                    }
                }
            }
            if (pending.role == ReferenceRole::Redefinition && segments.size() == 1 && start && start->element) {
                // The redefined feature is looked up through the general types of the owning type (above), never among its owned members
                // (KerML 8.3.3.3.4: a redefinition is not inherited from, nor does it redefine, a feature of its own featuring type). What
                // remains is the enclosing namespaces (a feature of the enclosing package that the owner redefines, as in the geometry library).
                // While generals of the owner are pending, what is found here may be shadowed by an inherited feature: it is not accepted
                // permanently (see run()).
                const Element* owner = canonical(start->element);
                auto pendingIt = pendingGenerals.find(owner);
                if (pendingIt != pendingGenerals.end() && pendingIt->second > 0) redefinitionOwnerPending = true;
                finalQuery.skipOwnedOf = start;
            }
            return resolveSegments(segments, globalOnly, start, finalQuery);
        }

        size_t run(const std::vector<PendingReference*>& pending, const std::function<bool()>& shouldStop) {
            detached = 0;   // (run() may be called again after sources were added)
            std::vector<PendingReference*> todo;
            for (const PendingReference* reference : pending) {
                if (reference && reference->resolved && reference->placeholder && reference->resolvedTarget &&
                    reference->placeholder != reference->resolvedTarget && !isChain(reference->name) && reference->role != ReferenceRole::ChainTarget) {
                    setRedirect(*reference, reference->resolvedTarget);
                }
            }
            for (PendingReference* reference : pending) {
                if (!reference) continue;
                if (reference->role == ReferenceRole::NotAttempted || reference->role == ReferenceRole::ChainTarget) continue;   // (chain targets: resolveChainTargets())
                if (reference->resolved) {
                    seedGenerals(*reference);
                } else {
                    todo.push_back(reference);
                }
            }
            for (const PendingReference* reference : todo) {
                if (!scopeFor(reference->context.get())) ++detached;
            }

            struct Key {
                int phase;
                size_t depth;
                int kindPriority;
                size_t sequence;
            };
            std::vector<std::pair<Key, PendingReference*>> keyed;
            keyed.reserve(todo.size());
            size_t sequence = 0;
            for (PendingReference* reference : todo) {
                const Scope* own = scopeFor(reference->context.get());
                const Scope* start = reference->relativeToOwner ? (own ? own->parent : nullptr) : own;
                Key key;
                key.phase = reference->role == ReferenceRole::Import ? 0 : (reference->role == ReferenceRole::Alias ? 1 : 2);
                key.depth = start ? start->depth : 0;
                key.kindPriority = (reference->kind == ReferenceKind::Feature) ? 1 : 0;
                key.sequence = sequence++;
                keyed.emplace_back(key, reference);
            }
            std::stable_sort(keyed.begin(), keyed.end(), [](const auto& a, const auto& b) {
                if (a.first.phase != b.first.phase) return a.first.phase < b.first.phase;
                if (a.first.depth != b.first.depth) return a.first.depth < b.first.depth;
                if (a.first.kindPriority != b.first.kindPriority) return a.first.kindPriority < b.first.kindPriority;
                return a.first.sequence < b.first.sequence;
            });
            todo.clear();
            for (const auto& item : keyed) todo.push_back(item.second);

            registerResolvedEffectiveNames(pending);
            registerProvisionalNames(pending);
            pendingGenerals.clear();
            for (const PendingReference* reference : todo) {
                if (reference->role == ReferenceRole::Generalization || reference->role == ReferenceRole::Redefinition) {
                    ++pendingGenerals[canonical(reference->specific)];
                }
            }

            size_t total = 0;
            bool progress = true;
            bool strictOrder = true;
            size_t lenientRounds = 0;
            while (!todo.empty()) {
                progress = false;
                std::vector<PendingReference*> next;
                bool lenientAccepted = false;
                size_t visited = 0;
                for (PendingReference* reference : todo) {
                    if (shouldStop && (++visited & 0xF) == 0 && shouldStop()) throw ResolveDeadlineReached();
                    if (lenientAccepted) {
                        next.push_back(reference);
                        continue;
                    }
                    std::shared_ptr<Element> target;
                    incomplete = false;
                    redefinitionOwnerPending = false;
                    ignoreIncomplete = canonical(reference->specific);
                    try {
                        target = resolveReference(*reference);
                    } catch (...) {
                        target = nullptr;
                    }
                    ignoreIncomplete = nullptr;
                    if (target && incomplete && (strictOrder || redefinitionOwnerPending)) {
                        // (a redefinition whose owner still lacks generals stays open for the next resolve(): the redefined feature may be inherited)
                        target = nullptr;
                    }
                    if (!target) {
                        next.push_back(reference);
                        continue;
                    }
                    if (incomplete) lenientAccepted = (lenientRounds < 16);
                    if (reference->role == ReferenceRole::Generalization || reference->role == ReferenceRole::Redefinition) {
                        auto pendingIt = pendingGenerals.find(canonical(reference->specific));
                        if (pendingIt != pendingGenerals.end() && pendingIt->second > 0) --pendingIt->second;
                    }
                    reference->resolved = true;
                    reference->resolvedTarget = target;
                    // (`a.b` names a feature chain, a new feature: its placeholder does not stand for the last feature of the chain)
                    if (reference->placeholder && reference->placeholder != target && !isChain(reference->name)) {
                        setRedirect(*reference, target);
                        auto moved = generals.find(reference->placeholder.get());
                        if (moved != generals.end()) {
                            const auto movedGenerals = moved->second;
                            const auto movedOrdinals = generalOrdinals[reference->placeholder.get()];   // (copy: the entry is erased below)
                            generals.erase(moved);
                            generalOrdinals.erase(reference->placeholder.get());
                            for (size_t index = 0; index < movedGenerals.size(); ++index) {
                                addGeneral(target.get(), movedGenerals[index], movedOrdinals[index]);
                            }
                        }
                    }
                    seedGenerals(*reference);
                    if (reference->apply) {
                        try {
                            reference->apply(target);
                        } catch (...) {
                            // A patch that cannot be applied leaves the model as recorded; the reference still counts as resolved.
                        }
                    }
                    if (reference->role == ReferenceRole::Redefinition) registerEffectiveName(reference->specific, target, reference->source);
                    progress = true;
                    ++total;
                }
                todo.swap(next);
                if (progress) {
                    strictOrder = true;
                } else if (strictOrder && !todo.empty()) {
                    // Nothing can be resolved with complete information: accept the first result that is still incomplete.
                    strictOrder = false;
                    ++lenientRounds;
                } else {
                    break;
                }
            }
            total += resolveChainTargets(pending, shouldStop);
            return total;
        }

        // ---------------------------------------------------------------------------------------------------------------
        // The targets of feature chains whose left operand is not a plain name chain
        // ---------------------------------------------------------------------------------------------------------------

        /// The static result type of an expression: the namespaces (features and types) in which a name that follows the expression with a `.` is
        /// looked up. The expression has several when its value is one of several (the members of a sequence, the branches of a conditional): the
        /// name must be found in each of them.
        struct StaticType {
            /// The type is known (every part of the expression has a result type that is resolved); false: nothing is attempted.
            bool known = false;
            /// No namespace of it is open: each has a general type that is declared, and none of the generalizations it (or one of its general
            /// types) is waiting for is unresolved. Only a complete type can lack a feature for good.
            bool complete = true;
            std::vector<std::shared_ptr<Element>> namespaces;
        };

        /// The result parameter of a function (the feature of its return parameter membership), looked up in the function and its general types.
        std::shared_ptr<Feature> resultParameterOf(const std::shared_ptr<Element>& function) const {
            std::vector<std::shared_ptr<Element>> stack{function};
            std::unordered_set<const Element*> seen;
            while (!stack.empty()) {
                const auto current = stack.back();
                stack.pop_back();
                if (!current || !seen.insert(current.get()).second) continue;
                for (const auto& relationship : current->ownedRelationship()) {
                    if (!dynamic_cast<const KerML::Entities::ReturnParameterMembership*>(relationship.get())) continue;
                    for (const auto& related : relationship->ownedRelatedElement()) {
                        if (auto feature = std::dynamic_pointer_cast<Feature>(related)) return feature;
                    }
                }
                auto gens = generals.find(canonical(current));
                if (gens == generals.end()) continue;
                for (auto it = gens->second.rbegin(); it != gens->second.rend(); ++it) stack.push_back(*it);
            }
            return nullptr;
        }

        /// The expressions that stand for the operands of an expression (the arguments of an invocation or operator).
        static std::vector<std::shared_ptr<KerML::Entities::Expression>> operandsOf(const std::shared_ptr<Element>& expression) {
            if (const auto instantiation = std::dynamic_pointer_cast<KerML::Entities::InstantiationExpression>(expression)) return instantiation->argument();
            return {};
        }

        /// Whether @p element is a general type that is not resolved yet (or a placeholder).
        bool isOpen(const std::shared_ptr<Element>& element) const {
            if (!element || isUnresolved(element)) return true;
            std::vector<const Element*> stack{canonical(element)};
            std::unordered_set<const Element*> seen;
            while (!stack.empty()) {
                const Element* current = stack.back();
                stack.pop_back();
                if (!seen.insert(current).second) continue;
                // (an element that is not indexed any more: the source it was in was replaced, and a reference of a source that was not replaced
                // may still point to it)
                if (scopeFor(current) == nullptr) return true;
                const auto pendingIt = pendingGenerals.find(current);
                if (pendingIt != pendingGenerals.end() && pendingIt->second > 0) return true;
                auto gens = generals.find(current);
                if (gens == generals.end()) continue;
                for (const auto& general : gens->second) stack.push_back(canonical(general));
            }
            return false;
        }

        StaticType staticTypeOf(const std::shared_ptr<Element>& root) const {
            StaticType result;
            // (a worklist instead of recursion: a sequence of 100000 elements is nested as deep, and so is a row of indexings)
            std::vector<std::shared_ptr<Element>> work{root};
            size_t steps = 0;
            const auto add = [&](const std::shared_ptr<Element>& ns, bool needsDeclaredGeneral) {
                if (!ns || isUnresolved(ns)) return false;
                result.namespaces.push_back(ns);
                if (isOpen(ns)) result.complete = false;
                if (needsDeclaredGeneral) {
                    // (a feature without a declared type has the type its value suggests, which is not looked at: not for good)
                    const auto gens = generals.find(canonical(ns));
                    if (gens == generals.end() || gens->second.empty()) result.complete = false;
                }
                return true;
            };
            while (!work.empty()) {
                if (++steps > 4000000) return StaticType();
                const auto expression = work.back();
                work.pop_back();
                if (!expression) return StaticType();
                // (`null` is the empty sequence: it has no value that could lack the feature)
                if (std::dynamic_pointer_cast<KerML::Entities::NullExpression>(expression)) continue;
                if (const auto reference = std::dynamic_pointer_cast<KerML::Entities::FeatureReferenceExpression>(expression)) {
                    if (!add(reference->referent(), true)) return StaticType();
                } else if (const auto chain = std::dynamic_pointer_cast<KerML::Entities::FeatureChainExpression>(expression)) {
                    if (!add(chain->targetFeature(), true)) return StaticType();
                } else if (const auto index = std::dynamic_pointer_cast<KerML::Entities::IndexExpression>(expression)) {
                    // `v#(1)`: an element of the value of `v`, which has its type
                    const auto operands = operandsOf(index);
                    if (operands.empty()) return StaticType();
                    work.push_back(operands.front());
                } else if (const auto select = std::dynamic_pointer_cast<KerML::Entities::SelectExpression>(expression)) {
                    // `v.?{...}`: some of the elements of the value of `v`
                    const auto operands = operandsOf(select);
                    if (operands.empty()) return StaticType();
                    work.push_back(operands.front());
                } else if (const auto op = std::dynamic_pointer_cast<KerML::Entities::OperatorExpression>(expression)) {
                    const auto operands = operandsOf(op);
                    const std::string& name = op->operatorName();
                    if (name == "," && operands.size() == 2) {
                        work.push_back(operands[1]);
                        work.push_back(operands[0]);
                    } else if (name == "if" && operands.size() == 3) {
                        work.push_back(operands[2]);
                        work.push_back(operands[1]);
                    } else if (name == "as" && operands.size() == 2) {
                        const auto cast = std::dynamic_pointer_cast<KerML::Entities::InstantiationExpression>(operands[1]);
                        if (!cast || !add(cast->instantiatedType(), false)) return StaticType();
                    } else {
                        // (the function of an operator is bound after the resolution: its result type is not known here)
                        return StaticType();
                    }
                } else if (const auto constructor = std::dynamic_pointer_cast<KerML::Entities::ConstructorExpression>(expression)) {
                    if (!add(constructor->instantiatedType(), false)) return StaticType();
                } else if (const auto invocation = std::dynamic_pointer_cast<KerML::Entities::InvocationExpression>(expression)) {
                    auto type = invocation->instantiatedType();
                    // (an invoked type that is a feature chain, `c.twice(5)`: the result of its last feature)
                    const auto chainFeature = std::dynamic_pointer_cast<Feature>(type);
                    const auto chainFeatureRef = *chainFeature;
                    if (chainFeature && !chainFeature->chainingFeature().empty() && typeid(chainFeatureRef) == typeid(Feature)) {
                        type = chainFeature->chainingFeature().back();
                        if (!type || isUnresolved(type)) return StaticType();
                    } else if (!type || isUnresolved(type) || !std::dynamic_pointer_cast<KerML::Entities::Function>(type)) {
                        return StaticType();
                    }
                    const auto parameter = resultParameterOf(type);
                    if (!parameter) return StaticType();
                    if (!add(parameter, true)) return StaticType();
                    if (isOpen(type)) result.complete = false;
                } else {
                    return StaticType();
                }
            }
            result.known = !result.namespaces.empty();
            return result;
        }

        /// The feature itself and the features it redefines, directly or not (only redefinitions: a feature that is merely subsetted is another
        /// feature, which the members of a sequence do not share).
        static std::vector<std::shared_ptr<Element>> redefinitionAncestors(const std::shared_ptr<Element>& start) {
            std::vector<std::shared_ptr<Element>> result;
            std::vector<std::shared_ptr<Element>> stack{start};
            while (!stack.empty()) {
                const auto current = stack.back();
                stack.pop_back();
                if (!current || isUnresolved(current) || std::find(result.begin(), result.end(), current) != result.end()) continue;
                result.push_back(current);
                if (const auto feature = std::dynamic_pointer_cast<Feature>(current)) {
                    for (const auto& redefinition : feature->ownedRedefinition()) {
                        if (redefinition) stack.push_back(redefinition->redefinedFeature());
                    }
                }
            }
            return result;
        }

        /// The feature that the name stands for in every namespace of the type: the same one in all of them, or, where they differ, the nearest
        /// feature that all of them redefine (`(q1, q2).r` with `q1::r` and `q2::r` that redefine `Q::r` is `Q::r`; features that only subset a common
        /// one are not the same feature). Null if the name is not found in one of them, or if the features have no single nearest common redefined
        /// feature; @p unrelated tells the second case (every namespace has the name, but there is no feature to stand for it).
        std::shared_ptr<Element> chainMember(const StaticType& type, const std::vector<std::string>& segments, const Scope* start, int maxLevel,
                                             bool& unrelated) const {
            unrelated = false;
            std::vector<std::shared_ptr<Element>> found;
            for (const auto& ns : type.namespaces) {
                std::shared_ptr<Element> current = ns;
                for (size_t i = 0; i < segments.size(); ++i) {
                    const Scope* scope = scopeFor(current.get());
                    if (!scope) return nullptr;
                    Query query;
                    query.kind = i + 1 == segments.size() ? ReferenceKind::Feature : ReferenceKind::Namespace;
                    query.maxLevel = maxLevel;
                    current = lookupIn(scope, segments[i], encloses(scope, start) ? Access::Local : Access::Public, query);
                    if (!current) return nullptr;
                }
                found.push_back(std::move(current));
            }
            if (found.empty()) return nullptr;
            bool same = true;
            for (const auto& feature : found) same = same && feature == found.front();
            if (same) return found.front();
            // the common ancestors, and of those the ones that no other common ancestor is a redefinition of
            std::vector<std::shared_ptr<Element>> common = redefinitionAncestors(found.front());
            for (size_t i = 1; i < found.size() && !common.empty(); ++i) {
                const auto ancestors = redefinitionAncestors(found[i]);
                common.erase(std::remove_if(common.begin(), common.end(),
                                            [&](const std::shared_ptr<Element>& candidate) { return std::find(ancestors.begin(), ancestors.end(), candidate) == ancestors.end(); }),
                             common.end());
            }
            std::vector<std::shared_ptr<Element>> nearest;
            for (const auto& candidate : common) {
                bool general = false;
                for (const auto& other : common) {
                    if (other == candidate) continue;
                    const auto ancestors = redefinitionAncestors(other);
                    general = std::find(ancestors.begin(), ancestors.end(), candidate) != ancestors.end();
                    if (general) break;
                }
                if (!general) nearest.push_back(candidate);
            }
            if (nearest.size() != 1) {
                unrelated = true;
                return nullptr;
            }
            return nearest.front();
        }

        /// The names of the types of a static type, for a message: a type is named by itself, a feature by its declared types (or its own name).
        std::string typeNamesOf(const StaticType& type) const {
            std::string names;
            for (const auto& ns : type.namespaces) {
                std::string name;
                if (dynamic_cast<const Feature*>(ns.get()) != nullptr) {
                    const auto gens = generals.find(canonical(ns));
                    if (gens != generals.end()) {
                        for (const auto& general : gens->second) {
                            if (dynamic_cast<const Feature*>(general.get()) == nullptr && !isUnresolved(general) && general->declaredName()) {
                                name = *general->declaredName();
                                break;
                            }
                        }
                    }
                }
                if (name.empty()) name = ns->declaredName().value_or("<unnamed>");
                const std::string quoted = "'" + name + "'";
                if (names.find(quoted) != std::string::npos) continue;
                names += (names.empty() ? "" : ", ") + quoted;
            }
            return names;
        }

        /// Resolves the references with the role ChainTarget (after all other references: they need the types that those resolved). Chains
        /// that depend on another (`(a.b).c.d`) are repeated until nothing changes. A reference that resolved in an earlier run is checked again:
        /// the types may be those of a source that was replaced meanwhile; if it no longer resolves, the model gets its placeholder back.
        size_t resolveChainTargets(const std::vector<PendingReference*>& pending, const std::function<bool()>& shouldStop) {
            std::vector<PendingReference*> chains;
            for (PendingReference* reference : pending) {
                if (reference && reference->role == ReferenceRole::ChainTarget) chains.push_back(reference);
            }
            if (chains.empty()) return 0;
            size_t resolvedNow = 0;
            for (size_t round = 0; round <= chains.size(); ++round) {
                bool changed = false;
                size_t visited = 0;
                for (PendingReference* reference : chains) {
                    if (shouldStop && (++visited & 0xF) == 0 && shouldStop()) throw ResolveDeadlineReached();
                    std::shared_ptr<Element> target;
                    bool absent = false;
                    bool unrelated = false;
                    const StaticType type = reference->operand ? staticTypeOf(reference->operand) : StaticType();
                    if (type.known) {
                        bool globalOnly = false;
                        const auto segments = splitName(reference->name, globalOnly);
                        const Scope* start = scopeFor(reference->context.get());
                        try {
                            if (!segments.empty() && !segments.front().empty()) {
                                target = chainMember(type, segments, start, levelOfSource(reference->source), unrelated);
                            }
                        } catch (...) {
                            target = nullptr;
                        }
                        absent = !target && type.complete && !unrelated;   // (features that no feature stands for: the evaluator finds them by name per member)
                    }
                    reference->absent = absent;
                    reference->absentIn = absent ? typeNamesOf(type) : std::string();
                    if (target == reference->resolvedTarget && reference->resolved == (target != nullptr)) continue;
                    changed = true;
                    if (target) {
                        if (!reference->resolved) ++resolvedNow;
                        reference->resolved = true;
                        reference->resolvedTarget = target;
                    } else {
                        reference->resolved = false;
                        reference->resolvedTarget = nullptr;
                    }
                    if (reference->apply) {
                        try {
                            reference->apply(target ? target : reference->placeholder);
                        } catch (...) {
                        }
                    }
                }
                if (!changed) break;
            }
            return resolvedNow;
        }

        std::unordered_map<const Element*, std::string> provisionalNames;

        /// The effective names of the redefinitions that are resolved already (XMI specializations, or the references of an earlier run of a
        /// resolver that was built anew since): resolving registers the name of a redefining feature without a name of its own, so it has
        /// to be done for these as well. A redefined feature can itself be only known by an effective name: repeat until nothing changes.
        void registerResolvedEffectiveNames(const std::vector<PendingReference*>& pending) {
            std::vector<const PendingReference*> redefinitions;
            for (const PendingReference* reference : pending) {
                if (reference && reference->resolved && reference->role == ReferenceRole::Redefinition && reference->specific &&
                    reference->resolvedTarget) {
                    redefinitions.push_back(reference);
                }
            }
            for (bool changed = !redefinitions.empty(); changed;) {
                changed = false;
                for (const PendingReference* reference : redefinitions) {
                    const Element* key = canonical(reference->specific);
                    if (key == nullptr || effectivelyNamed.count(key) != 0) continue;
                    registerEffectiveName(reference->specific, reference->resolvedTarget, reference->source);
                    if (effectivelyNamed.count(key) != 0) changed = true;
                }
            }
        }

        /// The name a feature that is declared without a name gets from its first redefinition is known before the redefinition is
        /// resolved: it is the last segment of the text (`feature redefines elements` is `elements`), which is what a lookup of the
        /// name inside the owner needs. The name is corrected when the redefined feature turns out to have another name.
        void registerProvisionalNames(const std::vector<PendingReference*>& pending) {
            // (the names of an earlier run() stay: their entries are already among the members of the owners)
            for (const PendingReference* reference : pending) {
                if (!reference || reference->resolved || reference->role != ReferenceRole::Redefinition || !reference->specific) continue;
                if (isChain(reference->name)) continue;
                const Element* key = canonical(reference->specific);
                if (key == nullptr || effectivelyNamed.count(key) != 0 || provisionalNames.count(key) != 0) continue;
                auto scopeIt = scopeOf.find(key);
                if (scopeIt == scopeOf.end()) continue;
                const Element* element = scopeIt->second->element.get();
                if (element == nullptr || element->declaredName().has_value() || element->declaredShortName().has_value()) continue;
                Scope* owner = const_cast<Scope*>(scopeIt->second->parent);
                if (owner == nullptr) continue;
                bool globalOnly = false;
                const auto segments = splitName(reference->name, globalOnly);
                if (segments.empty()) continue;
                const std::string name = segments.back();   // (splitName() removed the quotes)
                if (name.empty()) continue;
                provisionalNames[key] = name;
                noteRegistered(reference->source, key);
                owner->members[name].push_back({scopeIt->second->element, visibilityOf(element), nullptr});
            }
        }

        std::unordered_set<const Element*> effectivelyNamed;
        std::unordered_map<const Element*, std::pair<std::string, std::string>> effectiveNames;

        /// A feature that is declared without a name and redefines another feature is known by the name of the redefined feature
        /// (KerML 8.3.3.3.4 effectiveName): `feature redefines elements { ... }` can be referred to as `elements`.
        void noteRegistered(size_t source, const Element* key) {
            if (source < records.size()) records[source].registeredKeys.push_back(key);
        }

        void registerEffectiveName(const std::shared_ptr<Element>& specific, const std::shared_ptr<Element>& redefined, size_t source) {
            if (!specific || !redefined || specific == redefined) return;
            const Element* key = canonical(specific);
            if (key == nullptr || effectivelyNamed.count(key) != 0) return;
            auto scopeIt = scopeOf.find(key);
            if (scopeIt == scopeOf.end()) return;
            auto provisional = provisionalNames.find(key);
            if (provisional != provisionalNames.end()) {
                // The name that was registered from the text of the redefinition stands if it is the name of the redefined feature.
                std::string actual = redefined->declaredName().value_or("");
                std::string actualShort = redefined->declaredShortName().value_or("");
                if (actual.empty() && actualShort.empty()) {
                    // (the redefined feature is itself only known by the name it redefines)
                    auto known = effectiveNames.find(redefined.get());
                    if (known != effectiveNames.end()) {
                        actual = known->second.first;
                        actualShort = known->second.second;
                    }
                }
                // (a redefined feature whose own name is not known yet is assumed to have the name of the text)
                const bool same = (actual.empty() && actualShort.empty()) || provisional->second == actual || provisional->second == actualShort;
                if (same) {
                    effectivelyNamed.insert(key);
                    effectiveNames[key] = {actual.empty() && actualShort.empty() ? provisional->second : actual, actualShort};
                    noteRegistered(source, key);
                    return;
                }
                if (Scope* owner = const_cast<Scope*>(scopeIt->second->parent)) {
                    auto entries = owner->members.find(provisional->second);
                    if (entries != owner->members.end()) {
                        auto& list = entries->second;
                        list.erase(std::remove_if(list.begin(), list.end(),
                                                  [&](const auto& entry) { return entry.element == scopeIt->second->element; }),
                                   list.end());
                    }
                }
                provisionalNames.erase(provisional);
            }
            const Element* element = scopeIt->second->element.get();
            if (element == nullptr || element->declaredName().has_value() || element->declaredShortName().has_value()) return;
            const Scope* owner = scopeIt->second->parent;
            if (owner == nullptr) return;
            std::string name = redefined->declaredName().value_or("");
            std::string shortName = redefined->declaredShortName().value_or("");
            if (name.empty() && shortName.empty()) {
                // The redefined feature is itself only known by the name it redefines.
                auto known = effectiveNames.find(redefined.get());
                if (known != effectiveNames.end()) {
                    name = known->second.first;
                    shortName = known->second.second;
                }
            }
            if (name.empty() && shortName.empty()) return;
            effectiveNames[key] = {name, shortName};
            effectivelyNamed.insert(key);
            noteRegistered(source, key);
            Scope* mutableOwner = const_cast<Scope*>(owner);
            if (!name.empty()) mutableOwner->members[name].push_back({scopeIt->second->element, visibilityOf(element), nullptr});
            if (!shortName.empty() && shortName != name) {
                mutableOwner->members[shortName].push_back({scopeIt->second->element, visibilityOf(element), nullptr});
            }
        }

        /// Adds a general type of @p key at the place its ordinal gives (after the ones with an ordinal that is not greater).
        void addGeneral(const Element* key, const std::shared_ptr<Element>& general, std::uint64_t ordinal) {
            auto& list = generals[key];
            if (std::find(list.begin(), list.end(), general) != list.end()) return;
            auto& ordinals = generalOrdinals[key];
            const size_t position = static_cast<size_t>(std::upper_bound(ordinals.begin(), ordinals.end(), ordinal) - ordinals.begin());
            if (sourceOfOrdinal(ordinal) < records.size()) records[sourceOfOrdinal(ordinal)].generalKeys.push_back(key);
            list.insert(list.begin() + static_cast<std::ptrdiff_t>(position), general);
            ordinals.insert(ordinals.begin() + static_cast<std::ptrdiff_t>(position), ordinal);
        }

        void seedGenerals(const PendingReference& reference) {
            if ((reference.role == ReferenceRole::Generalization || reference.role == ReferenceRole::Redefinition) &&
                reference.specific && reference.resolvedTarget) {
                addGeneral(canonical(reference.specific), reference.resolvedTarget, ordinalOf(reference));
            }
        }
    };

    Resolver::Resolver(std::vector<SourceInput> sources) : impl_(std::make_unique<Impl>()) {
        for (const auto& source : sources) impl_->indexSource(source, impl_->sourceRoots.size());
        impl_->buildGlobal(0);
    }

    bool Resolver::canAdd(int level) const {
        return level >= impl_->lowestLevel;
    }

    void Resolver::addSources(std::vector<SourceInput> sources) {
        const size_t first = impl_->sourceRoots.size();
        for (const auto& source : sources) impl_->indexSource(source, impl_->sourceRoots.size());
        impl_->buildGlobal(first);
        // What was cached from the library elements so far (also the "not loaded" entries) may change with the new sources.
        impl_->libraryElements.clear();
        impl_->implicitOf.clear();
    }

    size_t Resolver::sourceCount() const {
        return impl_->sourceRoots.size();
    }

    bool Resolver::canReplace(const std::map<size_t, int>& replaced) const {
        if (replaced.empty()) return true;
        if (impl_->tainted) return false;
        int lowestReplaced = std::numeric_limits<int>::max();
        for (const auto& [index, level] : replaced) {
            // (a source the resolver does not know, or one that changes its level: a new Resolver is needed)
            if (index >= impl_->sourceLevels.size() || impl_->sourceLevels[index] != level) return false;
            lowestReplaced = std::min(lowestReplaced, level);
        }
        // Every other source is below all replaced ones: a reference only resolves to sources of the same or a lower level, so no
        // remaining reference, import or alias can have been bound to an element that is removed now.
        for (size_t index = 0; index < impl_->sourceLevels.size(); ++index) {
            if (replaced.count(index) == 0 && impl_->sourceLevels[index] >= lowestReplaced) return false;
        }
        // (A name that a reference of a replaced source registered for an element of another source would stay behind in that source. That
        // case is covered by `tainted`, which removeSources() sets before it clears the record of the source; Workspace removes a source
        // when it is replaced, so the record is gone when this is asked.)
        return true;
    }

    /*
     * removeSources: what each member of Impl can hold that belongs to a removed source, and what is done about it.
     * (S = the removed sources; a "key" is an Element* that is only used as a key and is never dereferenced.)
     *   records[s]               the scopes of s are freed with it (after every table below lost its pointers to them).
     *   sourceRoots, sourceLevels  stay by index: the slot is filled again by indexSource() with the same level.
     *   scopeOf, relationshipScope, elementLevel, visitedElements   keys = elements of s (records[s].elements): erased.
     *   visibility               keys = records[s].visibilityKeys: erased.
     *   importedName             keys = imports of s: erased.
     *   global                   entries of s (its elements and aliases) leave with records[s].globalContribution; the names it touched
     *                            are rebuilt from the contributions of all sources, in the order of the sources.
     *   generals, generalOrdinals  keys that are elements (or placeholders) of s are erased. The list of another key can hold a general
     *                            that a reference of s made known (the placeholder of s stands for an element elsewhere): those entries
     *                            carry an ordinal of s and are removed (records[s].generalKeys). No remaining key can hold an element
     *                            of s as a general otherwise (level rule, see canReplace()).
     *   redirect                 keys = placeholders of s (records[s].redirectKeys) and elements of s: erased. The targets of remaining
     *                            keys are never in s (level rule).
     *   provisionalNames, effectiveNames, effectivelyNamed   keys that are elements of s, and the keys that references of s registered
     *                            (records[s].registeredKeys): erased. Their entries in `members` sit in the scope of the owner of the
     *                            key, which is of the source of the key (a scope never has a parent of another source). If that source is
     *                            not s, the resolver is marked as tainted and canReplace() refuses from then on.
     *   The removal itself is valid for every source; whether the index that remains is right (nothing that remains was bound to what
     *   is gone) is decided by canReplace(), which has to be asked before the index is used again.
     *   ordinalOf (a function now) has no state. pendingGenerals, incomplete, ignoreIncomplete, detached: reset at the start of every
     *                            run(). currentLevel, currentSource: set by indexSource(). lowestLevel: unchanged (levels stay).
     *   libraryElements, implicitOf   caches over all sources: cleared.
     *   Scope::declaresEnds      a cache over the children of the scope, which are of the same source: other sources are not affected.
     *   Imports and aliases of the remaining scopes cannot have resolved into scopes of s (level rule), and Scope::parent / children
     *   never leave the source, so no remaining Scope points to a freed one.
     */
    void Resolver::removeSources(const std::set<size_t>& removed) {
        Impl& d = *impl_;
        // A name that a reference of a removed source registered for an element of a source that stays (the placeholder of the reference
        // stands for an element there) would stay behind in that source: only a new index repairs that.
        for (const size_t index : removed) {
            for (const Element* key : d.records[index].registeredKeys) {
                auto scope = d.scopeOf.find(key);
                if (scope != d.scopeOf.end() && removed.count(scope->second->source) == 0) d.tainted = true;
            }
        }
        std::set<std::string> touchedNames;
        const auto forget = [&d](const Element* key) {
            d.scopeOf.erase(key);
            d.relationshipScope.erase(key);
            d.elementLevel.erase(key);
            d.visitedElements.erase(key);
            d.generals.erase(key);
            d.generalOrdinals.erase(key);
            d.redirect.erase(key);
            d.provisionalNames.erase(key);
            d.effectiveNames.erase(key);
            d.effectivelyNamed.erase(key);
        };
        for (const size_t index : removed) {
            auto& record = d.records[index];
            for (const Element* key : record.elements) forget(key);
            for (const Element* key : record.redirectKeys) forget(key);
            for (const Element* key : record.registeredKeys) {
                d.provisionalNames.erase(key);
                d.effectiveNames.erase(key);
                d.effectivelyNamed.erase(key);
            }
            for (const Element* key : record.visibilityKeys) d.visibility.erase(key);
            for (const ImportRecord* import : record.imports) d.importedName.erase(import);
            for (const auto& entry : record.globalContribution) touchedNames.insert(entry.first);
        }
        // Entries that a reference of a removed source added to the lists of general types of elements of other sources.
        for (const size_t index : removed) {
            std::set<const Element*> done;
            for (const Element* key : d.records[index].generalKeys) {
                if (!done.insert(key).second) continue;
                auto list = d.generals.find(key);
                auto ordinals = d.generalOrdinals.find(key);
                if (list == d.generals.end() || ordinals == d.generalOrdinals.end()) continue;
                for (size_t position = list->second.size(); position-- > 0;) {
                    if (removed.count(Impl::sourceOfOrdinal(ordinals->second[position])) == 0) continue;
                    list->second.erase(list->second.begin() + static_cast<std::ptrdiff_t>(position));
                    ordinals->second.erase(ordinals->second.begin() + static_cast<std::ptrdiff_t>(position));
                }
                if (list->second.empty()) {
                    d.generals.erase(list);
                    d.generalOrdinals.erase(ordinals);
                }
            }
        }
        for (const size_t index : removed) {
            d.records[index] = Impl::SourceRecord();   // frees the scopes
            d.sourceRoots[index] = nullptr;
        }
        d.rebuildGlobal(touchedNames);
        d.libraryElements.clear();
        d.implicitOf.clear();
    }

    void Resolver::replaceSources(const std::map<size_t, SourceInput>& sources) {
        std::set<size_t> removed;
        for (const auto& entry : sources) removed.insert(entry.first);
        removeSources(removed);
        for (const auto& entry : sources) impl_->indexSource(entry.second, entry.first);
        // The entries of `global` are rebuilt in the order of the sources (as buildGlobal() would have appended them to a new resolver).
        std::set<std::string> names;
        for (const auto& entry : sources) {
            auto& record = impl_->records[entry.first];
            record.globalContribution = impl_->sourceRoots[entry.first]->members;
            for (const auto& member : record.globalContribution) names.insert(member.first);
        }
        impl_->rebuildGlobal(names);
        impl_->libraryElements.clear();
        impl_->implicitOf.clear();
    }

    Resolver::~Resolver() = default;

    size_t Resolver::run(const std::vector<PendingReference*>& pending, const std::function<bool()>& shouldStop) {
        return impl_->run(pending, shouldStop);
    }

    std::shared_ptr<Element> Resolver::find(const std::string& name, const std::shared_ptr<Element>& scope, ReferenceKind kind,
                                            bool fromScopeItself) const {
        bool globalOnly = false;
        const auto segments = splitName(name, globalOnly);
        const Impl::Scope* own = impl_->scopeFor(scope.get());
        const Impl::Scope* start = fromScopeItself ? own : (own ? own->parent : nullptr);
        Impl::Query query;
        query.kind = kind;
        return impl_->resolveSegments(segments, globalOnly, start, query);
    }

    std::shared_ptr<Element> Resolver::findLibraryElement(const std::string& name) const {
        bool globalOnly = false;
        const auto segments = splitName(name, globalOnly);
        Impl::Query query;
        query.maxLevel = impl_->lowestLevel;
        return impl_->resolveSegments(segments, true, nullptr, query);
    }

    size_t Resolver::detachedContexts() const {
        return impl_->detached;
    }
}
