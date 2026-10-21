//
// Reader of the XMI files of the OMG pilot implementation (*.sysmlx, *.kermlx, *.xmi): builds the same abstract syntax as the parse
// listeners of the textual notation, but with ids, memberships and references taken from the file instead of resolved by name.
//
//---------------------------------------------------------
// Constants, Definitions, Pragmas
//---------------------------------------------------------
#pragma once
//---------------------------------------------------------
// External Classes
//---------------------------------------------------------
#include <memory>
#include <string>
#include <unordered_map>
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
    class Element;
}
//---------------------------------------------------------

namespace SysMLv2::Files {

    /// A reference of an XMI document (an id or a "file#id" href) that no loaded document defines.
    struct SYSMLV2FILE_EXPORT XmiUnresolvedReference {
        /// The reference as it is written: the id, or "<normalized path of the file>#<id>" for an href.
        std::string name;
        /// The property that holds the reference, for example "redefinedFeature".
        std::string property;
        ReferenceKind kind = ReferenceKind::Element;
        /// 1-based line of the element in the XMI file.
        int line = -1;
        /// The element the reference is written in and the placeholder that stands in for the target (null if the property cannot
        /// hold a placeholder; the property is then not set).
        std::shared_ptr<KerML::Entities::Element> context;
        std::shared_ptr<KerML::Entities::Element> placeholder;
    };

    class XmiReader;
    class XmiIndex;

    /**
     * @class XmiDocument
     * @brief The model of one XMI file, as far as it can be built from the file alone (see XmiReader::read()).
     */
    class SYSMLV2FILE_EXPORT XmiDocument {
    public:
        ~XmiDocument();
        XmiDocument(const XmiDocument&) = delete;
        XmiDocument& operator=(const XmiDocument&) = delete;

        /// The name the document was read with (usually the path of the file); relative hrefs are resolved against its directory.
        const std::string& sourceName() const;
        /// All elements of the document in document order (the root namespace first), memberships included.
        const std::vector<std::shared_ptr<KerML::Entities::Element>>& elements() const;
        /// The root element of the file (a Namespace); null if the file could not be read.
        std::shared_ptr<KerML::Entities::Element> root() const;
        /// Errors of reading the file (malformed XML, unknown metaclasses, invalid values, ...). References that cannot be resolved are
        /// not errors, see unresolved().
        const std::vector<std::shared_ptr<ParserError>>& errors() const;
        /// The root, the visibility of the members, the imports and the aliases of the document in the form the name resolution of a
        /// Workspace needs them. The targets of imports and aliases are filled in by XmiReader::link().
        const ResolutionData& resolutionData() const;
        /// The specializations of the document whose general type is known, as resolved references: they make the members of the
        /// general type visible to the name resolution of the specific type.
        std::vector<PendingReference> generalizations() const;
        /// The references of the last XmiReader::link() that no loaded document could resolve.
        std::vector<XmiUnresolvedReference> unresolved() const;

        /// (implementation detail)
        struct Impl;

    private:
        friend class XmiReader;
        friend class XmiIndex;
        XmiDocument();
        std::unique_ptr<Impl> impl_;
    };

    /**
     * @class XmiIndex
     * @brief The ids of the elements of all loaded XMI documents. References between files ("../Kernel Libraries/Base.kermlx#id") are
     * resolved by the (globally unique) id.
     */
    class SYSMLV2FILE_EXPORT XmiIndex {
    public:
        /// Adds the ids (xmi:id and elementId) of the elements of @p document.
        void add(const XmiDocument& document);
        /// Removes the ids of @p document (before it is replaced by a new version).
        void remove(const XmiDocument& document);
        /// The element with that id, or null.
        std::shared_ptr<KerML::Entities::Element> find(const std::string& id) const;
        /// Number of ids.
        std::size_t size() const;

    private:
        std::unordered_map<std::string, std::shared_ptr<KerML::Entities::Element>> Elements;
    };

    /**
     * @class XmiReader
     * @brief Reads the XMI serialization of KerML / SysML models in two steps.
     *
     * read() parses one file: it creates an element of the metaclass given by "xsi:type" for every XML element, takes the element
     * id, the primitive and enumeration properties from the attributes, builds the ownership structure (an "ownedRelationship" is
     * a relationship owned by the enclosing element, an "ownedRelatedElement" an element owned by the enclosing relationship) the
     * way the listeners of the textual notation do, and remembers the references (attributes holding ids of the same file,
     * child tags with an href) for link(). Properties that are derived in the metamodel are ignored; unknown attributes are
     * reported as warnings. Only the explicit variant of the files (resources/sysml.library.xmi, without the .implied files) is
     * supported.
     *
     * link() resolves the remembered references of a document by id: in the same document, or, for an href to another file, in the
     * index of all documents. A reference no document defines keeps a placeholder (see isUnresolved()) and is listed by
     * XmiDocument::unresolved(). link() can be called again after more documents were added to the index.
     */
    class SYSMLV2FILE_EXPORT XmiReader {
    public:
        /**
         * Reads the XMI text of one file.
         * @param text the content of the file.
         * @param sourceName recorded on the errors (usually the path of the file); relative hrefs are resolved against its directory.
         * @return the document; its errors() tell what could not be read. Never null.
         */
        static std::unique_ptr<XmiDocument> read(const std::string& text, const std::string& sourceName);

        /**
         * Resolves the references of @p document by id, sets the properties they stand for and completes the model (the generalization
         * relationships register their general types, imports and aliases their targets).
         * @param index the ids of all loaded documents, @p document included.
         */
        static void link(XmiDocument& document, const XmiIndex& index);
    };
}
