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
#include <sysmlv2/xmi/XmiWriter.h>
//---------------------------------------------------------
// Forwarding
//---------------------------------------------------------
namespace KerML::Entities {
    class Namespace;
}
//---------------------------------------------------------

namespace SysMLv2::Files {

    /// The language of a source. Auto picks KerML for names ending in ".kerml", the XMI serialization for names ending in ".kermlx",
    /// ".sysmlx" or ".xmi", and SysML v2 for everything else.
    enum class SourceLanguage {
        Auto,
        KerML,
        SysML,
        /// The XMI serialization of the pilot implementation (see XmiReader). The ids of its elements are indexed by the workspace, so
        /// that references between XMI sources (hrefs such as "Base.kermlx#<id>") are resolved by resolve(); references that are
        /// resolved in the file are not resolved again by name.
        Xmi
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
         * Parses the file at @p path (KerML for ".kerml", XMI for ".kermlx", ".sysmlx" and ".xmi", SysML v2 otherwise). A file that
         * cannot be opened becomes a source without elements and with one error.
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
         * already resolved keep what they resolved to. replaceSource() keeps the level and the load root (loadLibrary()).
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
         * Parses every ".kerml" and ".sysml" file and every ".kermlx", ".sysmlx" and ".xmi" file below @p directory (recursively, in
         * sorted path order). The workspace remembers @p directory as the load root of these sources: writeXmi() and exportXmi() name them
         * relative to it when they are not below the export root (XmiWriteOptions::exportRoot).
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

        /// Resolves all pending references of all sources: the names of the textual sources, the ids and hrefs of the XMI sources.
        /// May be called again after more sources were added.
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

        /**
         * Writes one source as an XMI file (see XmiWriter): the tree below its root namespace. Elements of other sources that the
         * source refers to are referenced by an href to the file of that source; the file of an XMI source is the one it was read
         * from, the file of a text source is its name with the extension ".sysmlx" / ".kermlx" (exportXmi() writes the sources there).
         * Only what the other source writes to that file can be referenced: a target that the other source does not list (structure
         * the classes of the model created) is reported as an error (LOGICAL_ERROR) and the reference is not written. The ids of the
         * elements in the other files are the ones those files get from the same options (XmiWriteOptions::foreignId), also for
         * IdMode::NameBased. Elements that were read from an XMI file keep their ids. Parent directories of @p path are created.
         * The include of @p options is meant for the file that is written: the other files, whose ids the references need, are
         * listed completely (everything the source lists), so that an include that leaves out a library element does not make the
         * references to it fail. The keepsId counts for all files: write the other files with the same options and their ids are the
         * ones the references use.
         * The file keys of the NameBased ids are those of exportXmi() (XmiWriteOptions::exportRoot, the rules are documented there),
         * so that writeXmi() and exportXmi() give the same ids to the same elements. A source whose file key collides with that of
         * another source is renamed there (a number is appended); here the references point to the file the source lives in
         * (its own name; for a text source its name with the extension of the XMI file), which is renamed (a number is appended) only if
         * another source lives in the same file, so same-named sources in different directories are referenced at their real files even
         * though their keys differ. A WARNING names every source whose key was changed that is written or referenced. If the ids of a source that is
         * referenced cannot be assigned (a callback of the options throws), a LOGICAL_ERROR says why, once for this file, and the
         * references into it are not written; the errors that assigning its ids reported are returned as well.
         * The file is replaced as a whole or not at all (written to a temporary file next to it first); if nothing could be written, or
         * writing fails, the file is neither created nor changed.
         * Elements of the source that its text does not list (the classes of the model create some, such as the end features of a
         * connector) are not written; each one that is not a known kind of such structure is reported as a WARNING.
         * The paths are in the narrow encoding of the system (as for addFile()); in the XMI files they are UTF-8.
         * @param source index of the source.
         * @param path the file to write.
         * @return the warnings and errors of writing (references that cannot be written, a file that cannot be written, an exception
         * as INTERNAL_ERROR), see XmiWriter; empty if the file was written completely. The errors are not added to errors().
         * Nothing but the documented exception is thrown.
         * @throws std::out_of_range if @p source is not the index of a source.
         */
        std::vector<std::shared_ptr<ParserError>> writeXmi(size_t source, const std::string& path, const XmiWriteOptions& options = {}) const;

        /**
         * Writes all sources as XMI files below @p directory (see writeXmi()): ".sysml" becomes ".sysmlx", ".kerml" becomes ".kermlx",
         * XMI sources keep their name. References between the sources are hrefs between the written files, so that the
         * directory can be loaded as a library. Sources without a root namespace (unreadable files) are not written and reported.
         *
         * The place of a file below @p directory is its file key, and IdMode::NameBased derives the ids of a file from the same key, so
         * the ids depend on it (a file that moves to another place in the tree gets other ids), and they are unique across all files of the
         * export; an id that two files share (imported ids) is reported as an error (LOGICAL_ERROR). The key of a source is made from its
         * own name and the export root (XmiWriteOptions::exportRoot) only, never from the other sources, the working directory or the
         * directories above the root, so that adding or removing a source does not change the key of another, and a user name or
         * another machine specific directory cannot get into a key unless it is below the root:
         *  1. a source that is a file below the export root (the name it was added with, with the extension of the XMI file) gets its path
         *     relative to the root: "sub/m.sysmlx" for "<root>/sub/m.sysml";
         *  2. any other source (no root given, or the source is not below it) gets its path relative to its load root, the directory that
         *     loadLibrary() read it from, if it was loaded from one;
         *  3. any other source gets its file name alone.
         * A key is never absolute and never starts with "..": the files are always written below @p directory. The export root is
         * not @p directory (that is where the files go); give the directory the model was loaded from. If only one of the root and the
         * name is relative, both are made absolute to compare them, which depends on the working directory: avoid it (give both as
         * absolute paths, or both relative to the same directory); one WARNING per root (and kind: export root or load root) says so, with the number of
         * the sources it happened for and a few of their names (writeXmi(): for the written and the referenced sources only). The
         * components are compared without regard to the case on Windows. A name that has no file name (".") gets the key "source_<n>.sysmlx"
         * (n: the position of the source, from 1), and a WARNING says so; these names are given after all real names, so a real file
         * called "source_<n>.sysmlx" keeps its key.
         * Two sources whose keys are the same (the comparison ignores the case: on Windows the way the file system does it, by the
         * upper case table of the system, independent of the locale; elsewhere by a fixed table of the common Latin, Greek and Cyrillic
         * letters, which may warn where a case sensitive file system would not mind; "A.sysml" and "a.sysml" are two files here as well,
         * and so are "B.sysml" and "B.sysmlx") get a number appended to the file name of the later one, and a WARNING names the source and
         * the cause (a difference in case, the same file name for want of a root, the same path relative to the root, the same path, a key
         * that an earlier collision gave to another source). The later one: the sources that are XMI files come first (their name is the
         * file they live in, so an XMI file keeps its key, and the references into it find it, when a text source has the same one), each
         * group in the order the sources were added.
         * All options are applied to every file; if a callback of the options throws for a source, its table of ids stays empty (it is
         * built once), the failure is reported with that source, the files that refer to it get one LOGICAL_ERROR with the reason
         * ("the ids of the file ... could not be assigned: ..."), and the references into it are reported one by one (LOGICAL_ERROR)
         * and not written. A failure
         * of one file (an exception as INTERNAL_ERROR, a file that cannot be written) does not stop the export: the other files are
         * written, and the failed file is not touched.
         * @return the warnings and errors of writing all sources, each with the path of its file as source.
         */
        std::vector<std::shared_ptr<ParserError>> exportXmi(const std::string& directory, const XmiWriteOptions& options = {}) const;

    private:
        struct Impl;
        std::unique_ptr<Impl> impl_;
    };
}
