//
// Scoped, qualified name resolution over the union of all sources of a Workspace.
// (Private header of the sysmlv2parser library.)
//
#pragma once

#include <sysmlv2/resolution/ResolutionData.h>

#include <chrono>
#include <functional>
#include <map>
#include <memory>
#include <optional>
#include <set>
#include <string>
#include <vector>

namespace SysMLv2::Files::Detail {

    /// Thrown by Resolver::run() when the deadline has passed; what was resolved until then stays resolved.
    struct ResolveDeadlineReached {};

    /// The elements and the recorded resolution data of one source.
    struct SourceInput {
        const std::vector<std::shared_ptr<KerML::Entities::Element>>* elements = nullptr;
        ResolutionData* data = nullptr;
        /// Level of the source: a reference only resolves to elements of sources of the same or a lower level.
        int level = 0;
    };

    /**
     * Resolves names following KerML 8.2.3.5 / 7.2.5:
     *  - a qualified name is resolved segment by segment; the first segment like an unqualified name, every further
     *    segment among the visible members of the namespace found for the previous segment;
     *  - an unqualified name is looked up in the local namespace (owned members, aliases, imported members, inherited
     *    members), then in each enclosing namespace, then in the implicit global namespace that contains the root
     *    packages of all sources;
     *  - imports (`::*`, `::**`, membership imports), their visibility (only public imports are re-exported, `import all`
     *    ignores member visibility), aliases and short names are honoured.
     */
    class Resolver {
    public:
        explicit Resolver(std::vector<SourceInput> sources);
        ~Resolver();
        Resolver(const Resolver&) = delete;
        Resolver& operator=(const Resolver&) = delete;

        /// Indexes further sources; the result is the same as that of a resolver built over all sources at once.
        /// Only possible if canAdd() is true for the level of every new source.
        void addSources(std::vector<SourceInput> sources);

        /// Whether a source of @p level can be added by addSources(): the implicit generals are looked up at the lowest level,
        /// so a source below every indexed level changes that lookup and needs a new Resolver.
        bool canAdd(int level) const;

        /// The number of the sources that are indexed (the index of the next source that addSources() adds).
        size_t sourceCount() const;

        /**
         * Whether the sources in @p replaced (index -> level of the new version) can be exchanged by replaceSources(): the resolver knows
         * every one of them with the same level, and every other indexed source has a lower level than all of them (a reference only
         * resolves to elements of its own or a lower level, so nothing that remains can be bound to what is removed). If not, a new
         * Resolver over all sources is needed.
         */
        bool canReplace(const std::map<size_t, int>& replaced) const;

        /// Takes the old versions of the sources out (if removeSources() did not yet; see canReplace()) and indexes the new ones under the same indices. The references
        /// of the new sources have to be passed to run() as pending; the result is that of a resolver built over all sources at once.
        void replaceSources(const std::map<size_t, SourceInput>& sources);

        /// Resolves the given references (in dependency order, to a fixed point) and calls their patch callbacks.
        /// @return the number of references that were resolved.
        /// @param shouldStop asked between references (every few of them); throws ResolveDeadlineReached if it returns true (the deadline
        ///        has passed or the work was cancelled). Empty: never stops.
        size_t run(const std::vector<PendingReference*>& pending, const std::function<bool()>& shouldStop = {});

        /**
         * Looks up @p name (qualified names and feature chains allowed).
         * @param scope the element the name is written in; null: only the global namespace is searched.
         * @param fromScopeItself true: search starts in @p scope (its members are visible); false: in the namespace that
         *        owns @p scope.
         */
        std::shared_ptr<KerML::Entities::Element> find(const std::string& name, const std::shared_ptr<KerML::Entities::Element>& scope,
                                                       ReferenceKind kind = ReferenceKind::Element, bool fromScopeItself = true) const;

        /// Number of references whose context element is not reachable from any root (resolved against the global namespace only).
        size_t detachedContexts() const;

        /// Takes the sources out of the index now (so that the elements the index holds are released) and leaves their slots empty until
        /// replaceSources() indexes the new versions. The index is only right afterwards if canReplace() accepts all the sources that are
        /// out of it; ask before using it again. Removing a source that is out already does nothing.
        void removeSources(const std::set<size_t>& removed);

    private:
        struct Impl;
        std::unique_ptr<Impl> impl_;
    };
}
