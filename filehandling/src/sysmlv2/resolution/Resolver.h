//
// Scoped, qualified name resolution over the union of all sources of a Workspace.
// (Private header of the sysmlv2parser library.)
//
#pragma once

#include <sysmlv2/resolution/ResolutionData.h>

#include <chrono>
#include <memory>
#include <optional>
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

        /// Resolves the given references (in dependency order, to a fixed point) and calls their patch callbacks.
        /// @return the number of references that were resolved.
        /// @param deadline throws ResolveDeadlineReached after this point in time (checked between references).
        size_t run(const std::vector<PendingReference*>& pending, std::optional<std::chrono::steady_clock::time_point> deadline = std::nullopt);

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

    private:
        struct Impl;
        std::unique_ptr<Impl> impl_;
    };
}
