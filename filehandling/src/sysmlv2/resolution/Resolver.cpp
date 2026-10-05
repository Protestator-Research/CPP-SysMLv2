//
// Scoped, qualified name resolution over the union of all sources of a Workspace. See Resolver.h.
//
#include <limits>
#include "Resolver.h"
#include "ImplicitGenerals.h"

#include <kerml/root/elements/Relationship.h>
#include <kerml/root/namespaces/Namespace.h>
#include <kerml/kernel/functions/ReturnParameterMembership.h>

#include <algorithm>
#include <cstdint>
#include <functional>
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
        /// Removes the quotes of an unrestricted name ('a b' -> a b) and resolves its escape sequences.
        std::string normalizeName(const std::string& raw) {
            if (raw.size() >= 2 && raw.front() == '\'' && raw.back() == '\'') {
                std::string out;
                out.reserve(raw.size());
                for (size_t i = 1; i + 1 < raw.size(); ++i) {
                    if (raw[i] == '\\' && i + 2 < raw.size()) {
                        ++i;
                        switch (raw[i]) {
                            case 'n': out.push_back('\n'); break;
                            case 't': out.push_back('\t'); break;
                            case 'b': out.push_back('\b'); break;
                            case 'f': out.push_back('\f'); break;
                            default: out.push_back(raw[i]); break;
                        }
                    } else {
                        out.push_back(raw[i]);
                    }
                }
                return out;
            }
            return raw;
        }

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
        };
        using Visited = std::vector<std::pair<const Scope*, unsigned>>;

        std::vector<std::unique_ptr<Scope>> pool;
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
            pool.push_back(std::make_unique<Scope>());
            Scope* scope = pool.back().get();
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
            if (!name.empty()) scope->members[normalizeName(name)].push_back({element, vis, alias, currentLevel});
            if (!shortName.empty() && shortName != name) scope->members[normalizeName(shortName)].push_back({element, vis, alias, currentLevel});
        }

        void visit(const std::shared_ptr<Element>& element, Scope* memberScope) {
            if (!element || !visitedElements.insert(element.get()).second) return;
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

        void indexSource(const SourceInput& source) {
            Scope* root = newScope(nullptr, nullptr);
            sourceRoots.push_back(root);
            currentLevel = source.level;
            sourceLevels.push_back(source.level);
            lowestLevel = sourceLevels.size() == 1 ? source.level : std::min(lowestLevel, source.level);
            if (!source.elements || !source.data) return;
            for (const auto& [element, vis] : source.data->visibility) visibility[element] = vis;

            if (source.data->root) {
                root->element = source.data->root;
                scopeOf[source.data->root.get()] = root;
                visitedElements.insert(source.data->root.get());
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
                bool globalPrefix = false;
                auto segments = splitName(import->target, globalPrefix);
                importedName[import.get()] = segments.empty() ? std::string() : segments.back();
            }
        }

        void buildGlobal() {
            for (const Scope* root : sourceRoots) {
                for (const auto& [name, entries] : root->members) {
                    auto& target = global[name];
                    target.insert(target.end(), entries.begin(), entries.end());
                }
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

            auto own = scope->members.find(name);
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
                        const std::string targetName = normalizeName(target->declaredName().value_or(""));
                        const std::string targetShort = normalizeName(target->declaredShortName().value_or(""));
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
                    const std::string endName = normalizeName(*endFeature->declaredName());
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
            return resolveSegments(segments, globalOnly, start, finalQuery);
        }

        size_t run(const std::vector<PendingReference*>& pending, std::optional<std::chrono::steady_clock::time_point> deadline) {
            std::vector<PendingReference*> todo;
            for (const PendingReference* reference : pending) {
                if (reference && reference->resolved && reference->placeholder && reference->resolvedTarget &&
                    reference->placeholder != reference->resolvedTarget && !isChain(reference->name)) {
                    redirect[reference->placeholder.get()] = reference->resolvedTarget;
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
                    if (deadline && (++visited & 0xF) == 0 && std::chrono::steady_clock::now() > *deadline) throw ResolveDeadlineReached();
                    if (lenientAccepted) {
                        next.push_back(reference);
                        continue;
                    }
                    std::shared_ptr<Element> target;
                    incomplete = false;
                    ignoreIncomplete = canonical(reference->specific);
                    try {
                        target = resolveReference(*reference);
                    } catch (...) {
                        target = nullptr;
                    }
                    ignoreIncomplete = nullptr;
                    if (target && incomplete && strictOrder) {
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
                        redirect[reference->placeholder.get()] = target;
                        auto moved = generals.find(reference->placeholder.get());
                        if (moved != generals.end()) {
                            const auto movedGenerals = moved->second;
                            generals.erase(moved);
                            auto& list = generals[target.get()];
                            for (const auto& general : movedGenerals) {
                                if (std::find(list.begin(), list.end(), general) == list.end()) list.push_back(general);
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
                    if (reference->role == ReferenceRole::Redefinition) registerEffectiveName(reference->specific, target);
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

        /// The name a feature that is declared without a name gets from its first redefinition is known before the redefinition is
        /// resolved: it is the last segment of the text (`feature redefines elements` is `elements`), which is what a lookup of the
        /// name inside the owner needs. The name is corrected when the redefined feature turns out to have another name.
        void registerProvisionalNames(const std::vector<PendingReference*>& pending) {
            provisionalNames.clear();
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
                const std::string name = normalizeName(segments.back());
                if (name.empty()) continue;
                provisionalNames[key] = name;
                owner->members[name].push_back({scopeIt->second->element, visibilityOf(element), nullptr});
            }
        }

        std::unordered_set<const Element*> effectivelyNamed;
        std::unordered_map<const Element*, std::pair<std::string, std::string>> effectiveNames;

        /// A feature that is declared without a name and redefines another feature is known by the name of the redefined feature
        /// (KerML 8.3.3.3.4 effectiveName): `feature redefines elements { ... }` can be referred to as `elements`.
        void registerEffectiveName(const std::shared_ptr<Element>& specific, const std::shared_ptr<Element>& redefined) {
            if (!specific || !redefined || specific == redefined) return;
            const Element* key = canonical(specific);
            if (key == nullptr || effectivelyNamed.count(key) != 0) return;
            auto scopeIt = scopeOf.find(key);
            if (scopeIt == scopeOf.end()) return;
            auto provisional = provisionalNames.find(key);
            if (provisional != provisionalNames.end()) {
                // The name that was registered from the text of the redefinition stands if it is the name of the redefined feature.
                std::string actual = normalizeName(redefined->declaredName().value_or(""));
                std::string actualShort = normalizeName(redefined->declaredShortName().value_or(""));
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
            std::string name = normalizeName(redefined->declaredName().value_or(""));
            std::string shortName = normalizeName(redefined->declaredShortName().value_or(""));
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
            Scope* mutableOwner = const_cast<Scope*>(owner);
            if (!name.empty()) mutableOwner->members[name].push_back({scopeIt->second->element, visibilityOf(element), nullptr});
            if (!shortName.empty() && shortName != name) {
                mutableOwner->members[shortName].push_back({scopeIt->second->element, visibilityOf(element), nullptr});
            }
        }

        void seedGenerals(const PendingReference& reference) {
            if ((reference.role == ReferenceRole::Generalization || reference.role == ReferenceRole::Redefinition) &&
                reference.specific && reference.resolvedTarget) {
                auto& list = generals[canonical(reference.specific)];
                if (std::find(list.begin(), list.end(), reference.resolvedTarget) == list.end()) list.push_back(reference.resolvedTarget);
            }
        }
    };

    Resolver::Resolver(std::vector<SourceInput> sources) : impl_(std::make_unique<Impl>()) {
        for (const auto& source : sources) impl_->indexSource(source);
        impl_->buildGlobal();
    }

    Resolver::~Resolver() = default;

    size_t Resolver::run(const std::vector<PendingReference*>& pending, std::optional<std::chrono::steady_clock::time_point> deadline) {
        return impl_->run(pending, deadline);
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
