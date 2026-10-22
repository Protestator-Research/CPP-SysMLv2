//
// Writer of the XMI files of the OMG pilot implementation (*.sysmlx, *.kermlx): serializes a model, the counterpart of XmiReader.
//
//---------------------------------------------------------
// Constants, Definitions, Pragmas
//---------------------------------------------------------
#pragma once
//---------------------------------------------------------
// External Classes
//---------------------------------------------------------
#include <functional>
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>
//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include <sysmlv2/ParserError.h>
#include <sysmlv2/sysmlv2file_global.h>
//---------------------------------------------------------
// Forwarding
//---------------------------------------------------------
namespace KerML::Entities {
    class Element;
}
//---------------------------------------------------------

namespace SysMLv2::Files {

    /// How XmiWriter::write() writes a model.
    struct SYSMLV2FILE_EXPORT XmiWriteOptions {
        /// One level of indentation of the XML; empty: no indentation and no line breaks.
        std::string indent = "  ";

        /// Where the ids (xmi:id and elementId) of the elements come from.
        enum class IdMode {
            /// The element id of the element: elements that were read from an XMI file keep the id of the file, all others write the id
            /// they were created with. Different runs of a parser give different ids to the elements of a text.
            ElementId,
            /// Opt-in: an id that depends on the model only, not on the run: a UUID (version 5, name based) of the qualified name of the
            /// element, or, for elements without a name (relationships, anonymous elements), of the name of the nearest named owner and
            /// the position in the ownership structure. The ids of the elements of a file start from the identity of the file
            /// (fileKey), not from what the file contains: two files that declare the same package get different ids, and adding a
            /// member to the top level of a file does not change the ids of the other members. The ids do depend on the fileKey, so on
            /// the path of the file (relative to the export root, see exportRoot), and on the names and the order of the
            /// model: renaming or moving a file changes all of its ids. Elements that came with an imported id (see keepsId) keep it.
            NameBased
        } ids = IdMode::ElementId;

        /// IdMode::NameBased: the identity of the file, from which the ids of its elements are derived (the path of the file relative to
        /// the export root, with "/" as separator, as Workspace sets it). Empty: the targetPath that is given to XmiWriter::write().
        /// A Workspace sets it itself (the value given here is replaced), from the name of the source and exportRoot only, never from the
        /// working directory or from the other sources (see exportRoot), so that the ids of a model are the same on every machine and do not
        /// change when another source is added or removed.
        std::string fileKey;

        /// Only for Workspace::writeXmi() and Workspace::exportXmi() (XmiWriter::write() and assignIds() ignore it; they take fileKey): the
        /// export root, a directory (in the narrow encoding of the system, like the names of the sources) that the NameBased file keys, and
        /// with them the layout of exportXmi(), are relative to. The key of a source is
        ///  1. its path relative to the export root, if the source (the name it was added with, with the extension of the XMI file) is a
        ///     file below the root: "/" as separator, UTF-8, for example "sub/m.sysmlx";
        ///  2. otherwise (no root given, or the source is not below it) its path relative to its load root, the directory that
        ///     Workspace::loadLibrary() read it from, if the workspace knows one and the source is below it;
        ///  3. otherwise the file name alone.
        /// A relative root and relative names are compared as they are (relative to the same working directory); if only one of them is
        /// relative, both are made absolute for the comparison (the working directory is not part of a key, but whether the source is below
        /// the root then depends on it: a WARNING says so, give both as absolute paths or both as relative ones). The components are
        /// compared without regard to the case on Windows. A key is never absolute and never contains "." or "..". Two sources that get
        /// the same key (the comparison ignores the case: on Windows by the upper case table of the system, as the file systems do;
        /// elsewhere by a fixed table of the common Latin, Greek and Cyrillic letters) get "_2", "_3", ... appended to the file name of
        /// the later ones (the XMI sources come first, then the others, each in the order they were added), and a WARNING says so. No
        /// other source is ever consulted: adding or removing a source does not change the key of another (but a collision of keys).
        /// Empty: rules 2 and 3 apply to every source.
        std::string exportRoot;

        /// IdMode::NameBased: true for the elements that came with an id of their own (read from an XMI file) and keep it. Null: none does.
        std::function<bool(const KerML::Entities::Element&)> keepsId;

        /// Null: the whole ownership tree is written. Otherwise the root itself (if this returns false for it, nothing is written) and an
        /// owned element (and what it owns) for which this returns false are not written. This is a deliberate choice of the caller; it is
        /// not reported.
        std::function<bool(const KerML::Entities::Element&)> include;

        /// Null: every owned element is an element of the model that is written. Otherwise it returns false for the elements that the
        /// classes of the model create on their own (the end features of a connector, ...), which the model owns like the elements of
        /// the source but which the source does not list; a Workspace writes the elements of the source only. Such an element, and what it
        /// owns, is not written. A WARNING names every one of them that is not one of the known kinds of such structure (the stand-ins
        /// of the end feature memberships that an XMI file describes, see XmiWriter), so that nothing disappears unnoticed.
        std::function<bool(const KerML::Entities::Element&)> listed;

        /// The id of an element that is not in the tree, for an href to the file that @p locate gives for it: the id the element has in
        /// the file it is written to. Null: the element id (IdMode::ElementId; with IdMode::NameBased the reference is not written and an
        /// error of type LOGICAL_ERROR reports it, since the id cannot be derived without the file of the element). Returns nullopt if
        /// the element is not written to its file (the reference is not written, LOGICAL_ERROR). A Workspace delivers the ids that
        /// XmiWriter::assignIds() gives to the elements of the other sources, so that a reference never has to guess.
        std::function<std::optional<std::string>(const KerML::Entities::Element&)> foreignId;
    };

    /**
     * @class XmiWriter
     * @brief Writes a model in the explicit variant of the XMI serialization that XmiReader reads.
     *
     * The ownership tree below the root is written: an "ownedRelationship" is a relationship owned by the enclosing element, an
     * "ownedRelatedElement" an element owned by the enclosing relationship. Every element has an "xsi:type" with its metaclass and
     * the ids "xmi:id" and "elementId" (the same value). The properties of a metaclass are written in the order of the metamodel
     * (the properties of the supertypes first), primitive and enumeration properties as attributes, and only if they differ from the
     * default of the metamodel. A reference is an attribute with the (space separated) ids of the targets if all of them are in the
     * written tree; if one of them is in another file, all targets of the property are child tags with an "href" of the form
     * "relative/path%20of%20the%20file#id", in the order of the targets. The path is relative to the directory of the file that is
     * written, uses "/" as separator and is percent-encoded as UTF-8 (every byte above 0x7F, every space, '#', '%', ...). A file that
     * cannot be reached by a relative path (on another drive of Windows) is written as a file URI ("file:///D:/dir/file.sysmlx#id",
     * "file://server/share/file.sysmlx#id"), which the reader accepts as well.
     *
     * Not written: derived properties, which the reader recomputes; implicit relationships (the model does not own them); the
     * redundant ends of a relationship (when the specific end "typedFeature" is written, the end "specific" it redefines is not);
     * the member and the (short) name of an owning membership, which are those of the element it owns; and references that cannot be
     * written: a reference that was not resolved (an error of type WARNING names the element and the property; of a property with
     * several targets only the unresolved targets are left out), a target that is neither in the tree nor in a file that @p locate
     * knows (an error of type LOGICAL_ERROR) and a target that its file does not contain (XmiWriteOptions::foreignId, LOGICAL_ERROR).
     *
     * Texts: XML 1.0 cannot hold the control characters (except tab, line feed and carriage return), the characters U+FFFE and
     * U+FFFF and bytes that are no UTF-8. They are replaced by U+FFFD (a NUL byte inside a value as well); a WARNING names the element
     * and the property.
     *
     * The end features of a connector are owned by an EndFeatureMembership. When an XMI file is read, the membership gets a stand-in
     * (made by the factory) for its member and the element that the file means follows in a membership of its own; the writer
     * writes that element in the end feature membership again (and neither the stand-in nor the wrapper). With
     * XmiWriteOptions::listed the stand-in and the wrapper are the elements the source does not list; without it (a direct call) the
     * structure decides: an unnamed plain feature (not an end, owning nothing) in an EndFeatureMembership that is followed by an
     * OwningMembership or FeatureMembership (exactly these metaclasses) owning one end feature. The end feature memberships of a text,
     * which own their end feature themselves, are never touched.
     *
     * Deviations from the model: an instance of the abstract class InstantiationExpression (the type reference of `x as T`, which the
     * parsers create) is written as an InvocationExpression; a relationship that is listed among the relationships of a namespace and
     * is owned by a membership is written once, in the membership.
     */
    class SYSMLV2FILE_EXPORT XmiWriter {
    public:
        /**
         * Serializes the tree below @p root.
         * @param root the element to write as the root of the file, usually the root namespace of a source.
         * @param targetPath the path of the file the text is meant for (UTF-8); hrefs to other files are relative to its directory.
         * @param locate maps an element that is not in the tree of @p root to the path (UTF-8) of the file it is written to (so that it
         * can be referenced by an href); nullopt if it is in no file. May be empty if no reference leaves the tree.
         * @param errors receives the warnings and errors of writing.
         * @return the XML text (UTF-8); empty if nothing was written (@p root is null, has no concrete metaclass, or is excluded by
         * XmiWriteOptions::include); the errors say why, except for a null @p root. The caller must not create or truncate a file for
         * an empty text. Exceptions are not caught here (Workspace::writeXmi() does that).
         */
        static std::string write(const std::shared_ptr<KerML::Entities::Element>& root, const std::string& targetPath,
                                 const std::function<std::optional<std::string>(const KerML::Entities::Element&)>& locate,
                                 std::vector<std::shared_ptr<ParserError>>& errors, const XmiWriteOptions& options = {});

        /**
         * The ids that write() gives to the elements of the tree below @p root with the same arguments, without writing anything.
         * (Used to look up the ids of the elements another file refers to: XmiWriteOptions::foreignId.)
         * @param errors receives the errors of the id assignment (an id that is used twice); the same ones write() reports.
         * @return the id of every element that is written; empty if @p root is null or not written.
         */
        static std::unordered_map<const KerML::Entities::Element*, std::string> assignIds(
            const std::shared_ptr<KerML::Entities::Element>& root, const std::string& targetPath,
            std::vector<std::shared_ptr<ParserError>>& errors, const XmiWriteOptions& options = {});
    };
}
