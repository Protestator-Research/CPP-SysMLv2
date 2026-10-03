//
// Multi-file workspace: parses any number of KerML / SysML v2 sources and resolves the names that occur in them
// against the union of all of them (KerML 8.2.3.5 / 7.2.5 name resolution).
//
//---------------------------------------------------------
// Constants, Definitions, Pragmas
//---------------------------------------------------------
#pragma once
//---------------------------------------------------------
// External Classes
//---------------------------------------------------------
#include <chrono>
#include <cstddef>
#include <memory>
#include <optional>
#include <stdexcept>
#include <string>
#include <vector>
//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include <sysmlv2/ParserError.h>
#include <sysmlv2/resolution/ResolutionData.h>
#include <sysmlv2/sysmlv2file_global.h>
//---------------------------------------------------------
// Forwarding
//---------------------------------------------------------
namespace KerML::Entities {
    class Namespace;
}
//---------------------------------------------------------

namespace SysMLv2::Files {

    /// The language of a source. Auto picks KerML for names ending in ".kerml" and SysML v2 for everything else.
    enum class SourceLanguage {
        Auto,
        KerML,
        SysML
    };

    /// Thrown by addText(), addFile(), replaceSource() (the workspace is unchanged) and resolve() (what was resolved stays resolved) when the
    /// deadline (setParseDeadline()) has passed.
    class SYSMLV2FILE_EXPORT ParseTimeout : public std::runtime_error {
    public:
        ParseTimeout() : std::runtime_error("the parse deadline has passed") {}
    };

    /**
     * A reference that could not be resolved. The model keeps a placeholder element (see isUnresolved()) in place of the
     * target; the placeholder is not part of any element list.
     */
    struct SYSMLV2FILE_EXPORT UnresolvedReferenceInfo {
        /// The name as written in the source.
        std::string name;
        ReferenceKind kind = ReferenceKind::Element;
        ReferenceRole role = ReferenceRole::Plain;
        /// Source name (file path) and 1-based line / 0-based column of the reference; -1 if unknown.
        std::string sourceName;
        int line = -1;
        int column = -1;
        size_t source = 0;
        /// The element the reference is written in and the placeholder that stands in for the target.
        std::shared_ptr<KerML::Entities::Element> context;
        std::shared_ptr<KerML::Entities::Element> placeholder;
    };

    /**
     * @class Workspace
     * @brief Loads any number of sources and resolves all references over the union of their root namespaces.
     *
     * Parsing (addFile / addText / loadLibrary) only builds the model of each source and records every reference by name;
     * nothing is resolved while a parse tree is walked. resolve() then resolves the recorded references of all loaded
     * sources at once:
     *  - qualified names are resolved segment by segment through namespaces (`A::B::c`, feature chains `a.b`);
     *  - unqualified names are looked up in the local namespace (owned members, aliases, members imported by the namespace,
     *    inherited members), then in each enclosing namespace, then in the implicit global namespace that contains the root
     *    packages of every loaded source;
     *  - imports (`import A::*;`, `import A::**;`, `import A::x;`), their visibility (only public imports are re-exported,
     *    `import all` ignores member visibility), aliases and short names (`<kg>`) are honoured; quoted names are compared
     *    without their quotes.
     * References that cannot be resolved keep a placeholder element and are reported by unresolvedReferences().
     * The workspace can be extended and resolve() called again; already resolved references are kept.
     */
    class SYSMLV2FILE_EXPORT Workspace {
    public:
        Workspace();
        ~Workspace();
        Workspace(const Workspace&) = delete;
        Workspace& operator=(const Workspace&) = delete;

        /**
         * Parses the file at @p path (KerML for ".kerml", SysML v2 otherwise). A file that cannot be opened becomes a source
         * without elements and with one error.
         * @return the index of the new source.
         */
        size_t addFile(const std::string& path, int level = 0);

        /**
         * Parses @p text.
         * @param sourceName recorded on the errors and unresolved references of this source (usually a file path).
         * @param level the level of the source, see setSourceLevel().
         * @return the index of the new source.
         */
        size_t addText(std::string text, std::string sourceName, SourceLanguage language = SourceLanguage::Auto, int level = 0);

        /**
         * Sets the level of a source (the default is 0). A reference only resolves to elements of sources of the same or a lower
         * level: names written in a library (level 0) never find the elements of a model (level 1, 2, ...) that happens to define a
         * package with the same name, whereas the model sees the library. The level also applies to the implicit general types
         * (`Base::Anything`, ...), which are looked up on the lowest level. Set it before resolve(); sources whose references were
         * already resolved keep what they resolved to. replaceSource() keeps the level.
         * @throws std::out_of_range if @p source is not the index of a source.
         */
        void setSourceLevel(size_t source, int level);
        /// The level of a source (see setSourceLevel()).
        int sourceLevel(size_t source) const;

        /**
         * Replaces the content of one source by the parse of @p text, keeping its index and name. The elements, the syntax
         * errors and the recorded references of the old source are discarded (so are its entries in unresolvedReferences()
         * and notAttemptedReferences()); the new text is parsed like addText() does. Nothing of the new source is resolved
         * until the next resolve(), which resolves its references over the union of all sources. The other sources are not
         * parsed again and their already resolved references stay resolved, which makes this the cheap way to re-check a
         * changing text against a fixed (library) context: load the library sources once, then call replaceSource() and
         * resolve() for every new version of the text.
         *
         * Assumption: the other sources do not refer to the elements of the replaced source (a standard library does not
         * refer to a user model). A reference of another source that was resolved to an element of the old source keeps
         * that (now detached) element, and an unresolved reference of another source may be resolved to an element of the
         * new source by the next resolve(). Replace such sources together, or build a new Workspace.
         * The elements of the old source are taken apart (KerML::Entities::disposeLinks: owners, owned elements, relationships,
         * types, ... are cleared), because the model refers to itself through std::shared_ptr in cycles and would never be freed
         * otherwise. A pointer to an old element that the caller still holds stays valid as an object, but the element is detached
         * from its model and must not be used any more.
         * @param source index of the source (see addText()).
         * @param language SourceLanguage::Auto keeps the language the source had.
         * @throws std::out_of_range if @p source is not the index of a source.
         */
        void replaceSource(size_t source, std::string text, SourceLanguage language = SourceLanguage::Auto);

        /**
         * Parses every ".kerml" and ".sysml" file below @p directory (recursively, in sorted path order).
         * @return the number of files added.
         */
        size_t loadLibrary(const std::string& directory);

        /**
         * Sets a point in time after which parsing a text is aborted with ParseTimeout (the parser is checked while it reads tokens, so
         * the abort comes soon after the deadline, but not at once if a single prediction step takes long). Applies to all following
         * addText(), addFile(), replaceSource() and resolve() calls until it is cleared (resolve() is checked between references). Without a deadline (the
         * default) parsing is never aborted. Meant to stop pathological input, which makes the ANTLR parser run for minutes.
         */
        void setParseDeadline(std::chrono::steady_clock::time_point deadline);
        /// Removes the parse deadline.
        void clearParseDeadline();

        /// Resolves all pending references of all sources. May be called again after more sources were added.
        void resolve();

        /// Number of loaded sources.
        size_t sourceCount() const;
        /// The name (usually the path) the source was added with.
        const std::string& sourceName(size_t source) const;
        /**
         * The index of the first source that was added under @p name.
         * @return the index, or sourceCount() if there is no such source.
         */
        size_t findSource(const std::string& name) const;
        /**
         * The root namespace of one source: the namespace that owns the top-level elements of the source (through their memberships)
         * and its top-level imports. Every source with at least one element has one; its members are the top-level packages
         * of the source. The root namespace is not part of elements().
         * @return the root namespace, or null if the source has no elements (empty text, unreadable file).
         */
        std::shared_ptr<KerML::Entities::Namespace> rootNamespace(size_t source) const;
        /// The elements of one source, without placeholders.
        const std::vector<std::shared_ptr<KerML::Entities::Element>>& elements(size_t source) const;
        /// The elements of all sources in the order the sources were added, without placeholders.
        std::vector<std::shared_ptr<KerML::Entities::Element>> elements() const;
        /// The top-level packages (Package / LibraryPackage) of all sources: the members of the implicit global namespace.
        std::vector<std::shared_ptr<KerML::Entities::Element>> rootPackages() const;
        /// Syntax errors of one source (references that could not be resolved are not errors).
        const std::vector<std::shared_ptr<ParserError>>& errors(size_t source) const;
        /// Syntax errors of all sources.
        std::vector<std::shared_ptr<ParserError>> errors() const;

        /// References that could not be resolved by the last resolve(), in source order.
        const std::vector<UnresolvedReferenceInfo>& unresolvedReferences() const;
        /// References that are recorded but for which no scoped resolution is attempted (currently: the parameter names of
        /// named invocation arguments). They keep their placeholder.
        const std::vector<UnresolvedReferenceInfo>& notAttemptedReferences() const;
        /// The unresolved references of one source as ParserErrors of type WARNING (with position).
        std::vector<std::shared_ptr<ParserError>> unresolvedAsWarnings(size_t source) const;
        /// The names (as written) of all references recorded in one source, resolved or not, without the ones that are not attempted.
        /// Available right after parsing; meant to find out which library packages a text needs before it is resolved.
        std::vector<std::string> referenceNames(size_t source) const;
        /// Number of references recorded in all sources (resolved, unresolved and not attempted).
        size_t referenceCount() const;
        /// Number of references resolved so far.
        size_t resolvedReferenceCount() const;

        /**
         * Resolves @p name like a reference written in @p scope would be resolved (after resolve()).
         * @param name a simple, qualified ("A::b") or chained ("a.b") name.
         * @param scope the element the name is written in; null: only the global namespace is searched.
         * @return the element, or null.
         */
        std::shared_ptr<KerML::Entities::Element> find(const std::string& name,
                                                       const std::shared_ptr<KerML::Entities::Element>& scope = nullptr,
                                                       ReferenceKind kind = ReferenceKind::Element) const;

    private:
        struct Impl;
        std::unique_ptr<Impl> impl_;
    };
}
