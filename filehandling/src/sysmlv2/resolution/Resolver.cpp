//
// Scoped, qualified name resolution over the union of all sources of a Workspace. See Resolver.h.
//
#include <limits>
#include "Resolver.h"
#include "ImplicitGenerals.h"

#include <kerml/root/elements/NameEscaping.h>
#include <kerml/root/elements/Relationship.h>
#include <kerml/root/namespaces/Namespace.h>
#include <kerml/kernel/functions/ReturnParameterMembership.h>

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

        void visit(const std::shared_ptr<Element>& element, Scope* memberScope) {
            if (!element || !visitedElements.insert(element.get()).second) return;
            records[currentSource].elements.push_back(element.get());
            elementLevel[element.get()] = currentLevel;
            if (dynamic_cast<const Relationship*>(element.get()) != nullptr && dynamic_cast<const Namespace*>(element.get()) == nullptr) {
                relationshipScope[element.get()] = memberScope;
                const bool returnParameter = dynamic_cast<const KerML::Entities::ReturnParameterMembership*>(element.get()) != nullptr;
                for (const auto& child : element->ownedElements()) {
                    visit(child, memberScope);
                    // A return parameter without a name is known as `result` (it redefines Evaluation::result).
                    if (returnParameter && child && !child->declaredName().has_value() && !child->declaredShortName().has_value() &&
                        dynamic_cast<const Feature*>(child.get()) != nullptr) {
                        memberScope->members["result"].push_back({child, visibilityOf(child.get()), nullptr});
                    }
                }
                return;
            }
            const VisibilityKind vis = visibilityOf(element.get());
            addNames(memberScope, element, nullptr, vis, element->declaredName().value_or(""), element->declaredShortName().value_or(""));
            Scope* scope = newScope(element, memberScope);
            scopeOf[element.get()] = scope;
            memberScope->children.push_back({scope, vis});
            for (const auto& child : element->ownedElements()) visit(child, scope);
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
            if (auto found = lookupIn(scope, name, access, q, visited)) return found;
            for (const auto& child : scope->children) {
                if (!visibleUnder(child.visibility, access)) continue;
                if (auto found = lookupRecursive(child.scope, name, access, q, visited)) return found;
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

        /// Candidates for the first segment of a name: the local namespace, then each enclosing namespace, then the global namespace.
        bool forEachStartCandidate(const Scope* start, bool globalOnly, const std::string& name, const Query& q,
                                   const std::function<bool(const std::shared_ptr<Element>&)>& callback) const {
            std::unordered_set<const Element*> seen;
            if (!globalOnly) {
                for (const Scope* scope = start; scope; scope = scope->parent) {
                    if (auto found = lookupIn(scope, name, Access::Local, q)) {
                        if (seen.insert(found.get()).second && callback(found)) return true;
                    }
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

        std::shared_ptr<Element> resolveReference(const PendingReference& pending) const {
            bool globalOnly = false;
            const auto segments = splitName(pending.name, globalOnly);
            const Scope* own = scopeFor(pending.context.get());
            const Scope* start = pending.relativeToOwner ? (own ? own->parent : nullptr) : own;
            Query finalQuery;
            finalQuery.kind = pending.kind;
            finalQuery.exclude = canonical(pending.specific);
            finalQuery.maxLevel = levelOfSource(pending.source);

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
                    reference->placeholder != reference->resolvedTarget && !isChain(reference->name)) {
                    setRedirect(*reference, reference->resolvedTarget);
                }
            }
            for (PendingReference* reference : pending) {
                if (!reference) continue;
                if (reference->role == ReferenceRole::NotAttempted) continue;
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
            return total;
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

    size_t Resolver::detachedContexts() const {
        return impl_->detached;
    }
}
