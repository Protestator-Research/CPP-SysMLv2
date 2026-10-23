//
// Reader of the XMI files of the OMG pilot implementation. See XmiReader.h.
//
//---------------------------------------------------------
// Constants, Definitions, Pragmas
//---------------------------------------------------------
//---------------------------------------------------------
// External Classes
//---------------------------------------------------------
#include <algorithm>
#include <cctype>
#include <filesystem>
#include <set>
#include <unordered_set>

#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/string_generator.hpp>
#include <pugixml.hpp>
//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include <kerml/KerML.h>
#include <sysmlv2/ownership/Ownership.h>
#include <sysmlv2/resolution/Retarget.h>
#include <sysmlv2/xmi/XmiReader.h>

#include "XmiBindings.h"
#include "XmiText.h"
//---------------------------------------------------------

namespace SysMLv2::Files {

    namespace K = KerML::Entities;

    namespace {
        using Xmi::ElementPtr;
        using Xmi::PropertyBinding;
        using Xmi::PropertyKind;

        /// "sysml:Feature" -> "Feature"
        std::string localName(const std::string& qualified) {
            const auto colon = qualified.rfind(':');
            return colon == std::string::npos ? qualified : qualified.substr(colon + 1);
        }

        std::string urlDecode(const std::string& text) {
            std::string out;
            out.reserve(text.size());
            for (size_t i = 0; i < text.size(); ++i) {
                if (text[i] == '%' && i + 2 < text.size() && std::isxdigit(static_cast<unsigned char>(text[i + 1])) &&
                    std::isxdigit(static_cast<unsigned char>(text[i + 2]))) {
                    out.push_back(static_cast<char>(std::stoi(text.substr(i + 1, 2), nullptr, 16)));
                    i += 2;
                } else {
                    out.push_back(text[i]);
                }
            }
            return out;
        }

        /// The file part of an href, for display (the target of a reference is found by its id, the file only names it in messages): relative to the
        /// directory of the file @p name that holds the href, normalised, with "/" as separator. The file part is UTF-8 as the writer makes it; an
        /// href from another producer can hold bytes that are no UTF-8 (a percent escape of Latin-1, a raw byte), which the filesystem library
        /// refuses to turn into a path (std::system_error). Such a part, and anything else the library refuses, is joined and normalised as plain
        /// text instead: this never throws.
        std::string displayPath(const std::string& name, const std::string& file) {
            if (Xmi::isValidUtf8(file)) {
                try {
                    const std::filesystem::path base = std::filesystem::path(name).parent_path();
                    const auto normalized = (base / std::filesystem::path(std::u8string(file.begin(), file.end()))).lexically_normal().generic_u8string();
                    return std::string(normalized.begin(), normalized.end());
                } catch (const std::exception&) {
                    // (plain text below)
                }
            }
            std::string joined = file;
            std::replace(joined.begin(), joined.end(), '\\', '/');
            const bool absolute = !joined.empty() && (joined[0] == '/' || (joined.size() >= 2 && joined[1] == ':'));
            if (!absolute) {
                const auto slash = name.find_last_of("/\\");
                if (slash != std::string::npos) {
                    std::string directory = name.substr(0, slash + 1);
                    std::replace(directory.begin(), directory.end(), '\\', '/');
                    joined.insert(0, directory);
                }
            }
            // ("." and ".." segments; the leading separators of an absolute path stay)
            const size_t lead = joined.find_first_not_of('/');
            const std::string prefix = joined.substr(0, lead == std::string::npos ? joined.size() : lead);
            const std::string rest = joined.substr(prefix.size());
            std::vector<std::string> segments;
            for (size_t position = 0; position <= rest.size();) {
                size_t end = rest.find('/', position);
                if (end == std::string::npos) end = rest.size();
                const std::string segment = rest.substr(position, end - position);
                position = end + 1;
                if (segment.empty() || segment == ".") continue;
                if (segment == ".." && !segments.empty() && segments.back() != "..") {
                    segments.pop_back();
                } else if (segment != ".." || prefix.empty()) {
                    segments.push_back(segment);
                }
            }
            std::string result = prefix;
            for (size_t i = 0; i < segments.size(); ++i) result += (i == 0 ? "" : "/") + segments[i];
            return result;
        }

        std::vector<std::string> splitWords(const std::string& text) {
            std::vector<std::string> words;
            std::string current;
            for (const char c : text) {
                if (std::isspace(static_cast<unsigned char>(c)) != 0) {
                    if (!current.empty()) words.push_back(std::move(current));
                    current.clear();
                } else {
                    current.push_back(c);
                }
            }
            if (!current.empty()) words.push_back(std::move(current));
            return words;
        }

        /// A name in the form of the textual notation, so that the name resolution can split and unquote it.
        std::string quoted(const std::string& name) {
            bool basic = !name.empty() && !(name[0] >= '0' && name[0] <= '9');
            for (const char c : name) {
                if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_')) {
                    basic = false;
                    break;
                }
            }
            if (basic) return name;
            std::string out = "'";
            for (const char c : name) {
                if (c == '\'' || c == '\\') out.push_back('\\');
                out.push_back(c);
            }
            out.push_back('\'');
            return out;
        }

        /// Line numbers of byte offsets.
        class LineTable {
        public:
            explicit LineTable(const std::string& text) {
                starts_.push_back(0);
                for (size_t i = 0; i < text.size(); ++i) {
                    if (text[i] == '\n') starts_.push_back(i + 1);
                }
            }
            /// 1-based line of @p offset; -1 if the offset is unknown.
            int lineOf(std::ptrdiff_t offset) const {
                if (offset < 0) return -1;
                const auto it = std::upper_bound(starts_.begin(), starts_.end(), static_cast<size_t>(offset));
                return static_cast<int>(it - starts_.begin());
            }

        private:
            std::vector<size_t> starts_;
        };
    }

    // -----------------------------------------------------------------------------------------------------------------
    // XmiDocument
    // -----------------------------------------------------------------------------------------------------------------

    struct XmiDocument::Impl {
        /// One element of a document that a property refers to: the id, and the file of an href.
        struct Token {
            std::string id;
            std::string file;      // normalized path of the file of an href, empty for an id of the same file
            std::string display;   // as shown in messages
            ElementPtr placeholder;
        };
        struct Pending {
            ElementPtr element;
            const PropertyBinding* binding = nullptr;
            std::vector<Token> tokens;
            int line = -1;
            bool done = false;
            std::vector<bool> resolved;
        };

        std::string name;
        std::vector<ElementPtr> elements;
        std::vector<int> lines;   // parallel to elements
        ElementPtr root;
        std::unordered_map<std::string, ElementPtr> byId;
        std::vector<std::shared_ptr<ParserError>> errors;
        ResolutionData data;
        std::vector<Pending> pending;
        /// The relationships that are owned by an element, in document order.
        std::vector<std::shared_ptr<K::Relationship>> relationships;
        std::unordered_map<const K::Element*, size_t> lineOfElement;
        std::vector<XmiUnresolvedReference> unresolvedList;
        std::vector<std::shared_ptr<ImportRecord>> imports;
        std::vector<std::shared_ptr<AliasRecord>> aliases;

        void report(ErrorType type, std::string message, int line) {
            errors.push_back(std::make_shared<ParserError>(boost::uuids::random_generator()(), "", type, std::move(message), line, -1, name));
        }
    };

    XmiDocument::XmiDocument() : impl_(std::make_unique<Impl>()) {}

    XmiDocument::~XmiDocument() = default;

    const std::string& XmiDocument::sourceName() const { return impl_->name; }

    const std::vector<ElementPtr>& XmiDocument::elements() const { return impl_->elements; }

    ElementPtr XmiDocument::root() const { return impl_->root; }

    const std::vector<std::shared_ptr<ParserError>>& XmiDocument::errors() const { return impl_->errors; }

    const ResolutionData& XmiDocument::resolutionData() const { return impl_->data; }

    std::vector<XmiUnresolvedReference> XmiDocument::unresolved() const { return impl_->unresolvedList; }

    std::vector<PendingReference> XmiDocument::generalizations() const {
        std::vector<PendingReference> result;
        for (const auto& relationship : impl_->relationships) {
            const auto specialization = std::dynamic_pointer_cast<K::Specialization>(relationship);
            if (!specialization) continue;
            const auto specific = specialization->specific();
            const auto general = specialization->general();
            if (!specific || !general || isUnresolved(specific) || isUnresolved(general)) continue;
            PendingReference reference;
            reference.kind = ReferenceKind::Type;
            reference.role = std::dynamic_pointer_cast<K::Redefinition>(relationship) ? ReferenceRole::Redefinition : ReferenceRole::Generalization;
            reference.context = specific;
            reference.specific = specific;
            reference.resolvedTarget = general;
            reference.resolved = true;
            result.push_back(std::move(reference));
        }
        return result;
    }

    // -----------------------------------------------------------------------------------------------------------------
    // XmiIndex
    // -----------------------------------------------------------------------------------------------------------------

    void XmiIndex::add(const XmiDocument& document) {
        for (const auto& [id, element] : document.impl_->byId) Elements[id] = element;
    }

    void XmiIndex::remove(const XmiDocument& document) {
        for (const auto& [id, element] : document.impl_->byId) {
            const auto it = Elements.find(id);
            if (it != Elements.end() && it->second == element) Elements.erase(it);
        }
    }

    ElementPtr XmiIndex::find(const std::string& id) const {
        const auto it = Elements.find(id);
        return it == Elements.end() ? nullptr : it->second;
    }

    std::size_t XmiIndex::size() const { return Elements.size(); }

    // -----------------------------------------------------------------------------------------------------------------
    // Step one: the elements of a file
    // -----------------------------------------------------------------------------------------------------------------

    namespace {

        class Reader {
        public:
            Reader(XmiDocument::Impl& impl, const std::string& text) : D(impl), Lines(text) {}

            void run(const std::string& text) {
                pugi::xml_document xml;
                const pugi::xml_parse_result parsed = xml.load_buffer(text.data(), text.size(), pugi::parse_default, pugi::encoding_utf8);
                if (!parsed) {
                    D.report(SYNTAX_ERROR, std::string("malformed XML: ") + parsed.description(), Lines.lineOf(parsed.offset));
                    return;
                }
                const pugi::xml_node top = xml.document_element();
                if (!top) {
                    D.report(SYNTAX_ERROR, "the XMI file has no root element", -1);
                    return;
                }
                D.root = readElement(top, Role::Root, nullptr);
                if (D.root) buildStructure();
            }

        private:
            enum class Role { Root, OwnedRelationship, OwnedRelatedElement };

            XmiDocument::Impl& D;
            LineTable Lines;
            /// The element that owns a relationship (the element whose "ownedRelationship" it is).
            std::unordered_map<const K::Element*, ElementPtr> OwnerOfRelationship;
            /// Elements owned by a relationship that is not an owning membership.
            std::vector<std::pair<std::shared_ptr<K::Relationship>, ElementPtr>> PlainOwned;

            static bool isInstanceTag(const std::string& tag) { return tag == "ownedRelationship" || tag == "ownedRelatedElement"; }

            void applyScalar(const ElementPtr& element, const PropertyBinding& binding, const std::string& text, const std::string& metaclass,
                             int line) {
                bool ok = false;
                try {
                    ok = binding.setValue(*element, text);
                } catch (const std::exception& ex) {
                    D.report(LOGICAL_ERROR, "cannot set property '" + std::string(binding.name) + "' of " + metaclass + ": " + ex.what(), line);
                    return;
                }
                if (ok) return;
                std::string expected;
                switch (binding.kind) {
                    case PropertyKind::Boolean: expected = "a boolean (true or false)"; break;
                    case PropertyKind::Integer: expected = "an integer"; break;
                    case PropertyKind::Real: expected = "a number"; break;
                    case PropertyKind::Enumeration: expected = "a literal of the enumeration " + std::string(binding.target); break;
                    default: expected = "a valid value"; break;
                }
                D.report(SYNTAX_ERROR, "invalid value '" + text + "' for property '" + std::string(binding.name) + "' of " + metaclass +
                                       ", expected " + expected, line);
            }

            XmiDocument::Impl::Token makeToken(const std::string& word) const {
                XmiDocument::Impl::Token token;
                const auto hash = word.find('#');
                if (hash == std::string::npos) {
                    token.id = word;
                    token.display = word;
                    return token;
                }
                token.id = word.substr(hash + 1);
                std::string file = urlDecode(word.substr(0, hash));
                if (!file.empty()) {
                    // (a file URI, the form the writer uses for a file it cannot reach by a relative path: "file:///D:/dir/f.sysmlx", "file://server/share/f.sysmlx"
                    // and "file:///dir/f.sysmlx")
                    if (file.compare(0, 7, "file://") == 0) {
                        file.erase(0, 7);
                        const bool drive = file.size() >= 3 && file[0] == '/' && std::isalpha(static_cast<unsigned char>(file[1])) != 0 && file[2] == ':';
                        if (drive) {
                            file.erase(0, 1);
                        } else if (file.empty() || file[0] != '/') {
                            file.insert(0, "//");
                        }
                    }
                    token.file = displayPath(D.name, file);
                }
                token.display = (token.file.empty() ? std::string() : token.file) + "#" + token.id;
                return token;
            }

            void addReference(const ElementPtr& element, const PropertyBinding& binding, const std::vector<std::string>& words,
                              std::unordered_map<const PropertyBinding*, size_t>& pendingOf, int line) {
                if (words.empty()) return;
                auto it = pendingOf.find(&binding);
                if (it == pendingOf.end()) {
                    XmiDocument::Impl::Pending pending;
                    pending.element = element;
                    pending.binding = &binding;
                    pending.line = line;
                    D.pending.push_back(std::move(pending));
                    it = pendingOf.emplace(&binding, D.pending.size() - 1).first;
                }
                auto& pending = D.pending[it->second];
                for (const auto& word : words) {
                    if (!binding.many && !pending.tokens.empty()) {
                        D.report(LOGICAL_ERROR, "property '" + std::string(binding.name) + "' of " + element->getType() + " holds one element, but has more", line);
                        break;
                    }
                    pending.tokens.push_back(makeToken(word));
                }
            }

            void readReferenceTag(const pugi::xml_node& child, const ElementPtr& element, const Xmi::MetaclassBinding& meta,
                                  std::unordered_map<const PropertyBinding*, size_t>& pendingOf, int line) {
                const std::string tag = localName(child.name());
                const PropertyBinding* binding = meta.find(tag);
                const int childLine = Lines.lineOf(child.offset_debug());
                if (binding == nullptr) {
                    if (!Xmi::isDerivedProperty(tag)) {
                        D.report(WARNING, "unknown element '" + tag + "' in " + std::string(meta.name) + "; ignored", childLine);
                    }
                    return;
                }
                if (binding->kind != PropertyKind::Reference) {
                    // (a primitive property written as an element with text)
                    applyScalar(element, *binding, child.child_value(), std::string(meta.name), childLine);
                    return;
                }
                std::string href = child.attribute("href").value();
                if (href.empty()) href = child.attribute("xmi:idref").value();
                if (href.empty()) {
                    D.report(LOGICAL_ERROR, "the reference '" + tag + "' of " + std::string(meta.name) + " has no href", childLine);
                    return;
                }
                addReference(element, *binding, {href}, pendingOf, line);
            }

            ElementPtr readElement(const pugi::xml_node& node, Role role, const ElementPtr& parent) {
                const int line = Lines.lineOf(node.offset_debug());
                std::string typeName = localName(node.attribute("xsi:type").value());
                if (typeName.empty()) {
                    if (role != Role::Root) {
                        D.report(LOGICAL_ERROR, std::string("the element '") + node.name() + "' has no xsi:type", line);
                        return nullptr;
                    }
                    typeName = localName(node.name());
                }
                const Xmi::MetaclassBinding* meta = Xmi::findMetaclass(typeName);
                if (meta == nullptr) {
                    D.report(LOGICAL_ERROR, "unknown metaclass '" + typeName + "' (xsi:type)", line);
                    return nullptr;
                }
                if (meta->isAbstract) {
                    D.report(LOGICAL_ERROR, "the metaclass '" + typeName + "' is abstract and cannot be instantiated (xsi:type)", line);
                    return nullptr;
                }
                ElementPtr element;
                try {
                    element = meta->create();
                } catch (const std::exception& ex) {
                    D.report(INTERNAL_ERROR, "cannot create an element of " + typeName + ": " + ex.what(), line);
                    return nullptr;
                }
                if (!element) {
                    D.report(INTERNAL_ERROR, "cannot create an element of " + typeName, line);
                    return nullptr;
                }

                // Where the element belongs to.
                std::shared_ptr<K::Relationship> owningRelationship;
                if (role == Role::OwnedRelationship) {
                    if (std::dynamic_pointer_cast<K::Relationship>(element) == nullptr) {
                        D.report(LOGICAL_ERROR, typeName + " is not a relationship, but it is an ownedRelationship of " + parent->getType(), line);
                        return nullptr;
                    }
                } else if (role == Role::OwnedRelatedElement) {
                    owningRelationship = std::dynamic_pointer_cast<K::Relationship>(parent);
                    if (!owningRelationship) {
                        D.report(LOGICAL_ERROR, "an ownedRelatedElement is only allowed in a relationship, not in " + parent->getType(), line);
                        return nullptr;
                    }
                }

                registerIds(node, element, typeName, line);
                D.elements.push_back(element);
                D.lines.push_back(line);
                D.lineOfElement[element.get()] = static_cast<size_t>(line < 0 ? 0 : line);

                if (role == Role::OwnedRelationship) {
                    parent->appendOwnedElement(element);
                    OwnerOfRelationship[element.get()] = parent;
                } else if (role == Role::OwnedRelatedElement) {
                    owningRelationship->appendElementToOwnedRelatedElement(element);
                    owningRelationship->appendOwnedElement(element);
                    const auto owner = OwnerOfRelationship.find(owningRelationship.get());
                    if (std::dynamic_pointer_cast<K::OwningMembership>(owningRelationship) && owner != OwnerOfRelationship.end()) {
                        owner->second->appendOwnedElement(element);
                    } else {
                        PlainOwned.emplace_back(owningRelationship, element);
                    }
                }

                // Properties.
                std::unordered_map<const PropertyBinding*, size_t> pendingOf;
                for (const pugi::xml_attribute attribute : node.attributes()) {
                    const std::string name = attribute.name();
                    if (name == "xmi:id" || name == "elementId" || name == "xsi:type" || name.rfind("xmlns", 0) == 0 || name.rfind("xmi:", 0) == 0 ||
                        name.rfind("xsi:", 0) == 0) {
                        continue;
                    }
                    const PropertyBinding* binding = meta->find(name);
                    if (binding == nullptr) {
                        if (!Xmi::isDerivedProperty(name)) {
                            D.report(WARNING, "unknown attribute '" + name + "' of " + typeName + "; ignored", line);
                        }
                        continue;
                    }
                    if (binding->kind == PropertyKind::Reference) {
                        addReference(element, *binding, splitWords(attribute.value()), pendingOf, line);
                    } else {
                        applyScalar(element, *binding, attribute.value(), typeName, line);
                    }
                }

                for (const pugi::xml_node child : node.children()) {
                    if (child.type() != pugi::node_element) continue;
                    const std::string tag = localName(child.name());
                    if (isInstanceTag(tag)) {
                        readElement(child, tag == "ownedRelationship" ? Role::OwnedRelationship : Role::OwnedRelatedElement, element);
                    } else {
                        readReferenceTag(child, element, *meta, pendingOf, line);
                    }
                }
                return element;
            }

            void registerIds(const pugi::xml_node& node, const ElementPtr& element, const std::string& typeName, int line) {
                const std::string xmiId = node.attribute("xmi:id").value();
                const std::string elementId = node.attribute("elementId").value();
                const std::string& id = elementId.empty() ? xmiId : elementId;
                if (!id.empty()) {
                    try {
                        element->assignElementId(boost::uuids::string_generator()(id));
                    } catch (const std::exception&) {
                        D.report(WARNING, "the id '" + id + "' of " + typeName + " is not a UUID; the element keeps a generated element id", line);
                    }
                }
                for (const std::string* key : {&xmiId, &elementId}) {
                    if (key->empty()) continue;
                    const auto inserted = D.byId.emplace(*key, element);
                    if (!inserted.second && inserted.first->second != element) {
                        D.report(LOGICAL_ERROR, "the id '" + *key + "' is used by more than one element", line);
                    }
                }
            }

            // The ownership structure the listeners of the textual notation produce: memberships, owners and the typed collections.
            void buildStructure() {
                std::vector<ElementPtr> created;
                OwnershipInput input;
                input.elements = &created;
                input.root = D.root;
                buildOwnership(input);
                // An element owned by a relationship that is not a membership (the anonymous feature of a feature chain).
                for (const auto& [relationship, member] : PlainOwned) {
                    const auto owner = relationship->owningRelatedElement();
                    member->setOwningRelationship(relationship);
                    member->setOwner(owner ? owner : relationship);
                    OwnershipInput nested;
                    nested.elements = &created;
                    nested.root = member;
                    buildOwnership(nested);
                }
                registerElements();
                collectResolutionData();
            }

            // The relationships register themselves at the element that owns them (the collections the listeners fill).
            void registerElements() {
                for (const auto& element : D.elements) {
                    if (const auto documentation = std::dynamic_pointer_cast<K::Documentation>(element)) {
                        documentation->setDocumentedElement(documentation->owner());
                        continue;
                    }
                    const auto relationship = std::dynamic_pointer_cast<K::Relationship>(element);
                    if (!relationship) continue;
                    const auto owner = relationship->owningRelatedElement();
                    if (!owner) continue;
                    D.relationships.push_back(relationship);
                    const auto feature = std::dynamic_pointer_cast<K::Feature>(owner);
                    const auto type = std::dynamic_pointer_cast<K::Type>(owner);
                    if (const auto redefinition = std::dynamic_pointer_cast<K::Redefinition>(relationship)) {
                        if (!feature) continue;
                        feature->appendOwnedRedefinition(redefinition);
                        feature->appendOwnedSubsetting(redefinition);
                        feature->appendOwnedSpecialization(redefinition);
                        redefinition->setOwningFeature(feature);
                    } else if (const auto referenceSubsetting = std::dynamic_pointer_cast<K::ReferenceSubsetting>(relationship)) {
                        if (!feature) continue;
                        feature->setOwnedReferenceSubsetting(referenceSubsetting);
                        referenceSubsetting->setOwningFeature(feature);
                    } else if (const auto crossSubsetting = std::dynamic_pointer_cast<K::CrossSubsetting>(relationship)) {
                        if (!feature) continue;
                        feature->setOwnedCrossSubsetting(crossSubsetting);
                        crossSubsetting->setOwningFeature(feature);
                    } else if (const auto subsetting = std::dynamic_pointer_cast<K::Subsetting>(relationship)) {
                        if (!feature) continue;
                        feature->appendOwnedSubsetting(subsetting);
                        feature->appendOwnedSpecialization(subsetting);
                        subsetting->setOwningFeature(feature);
                    } else if (const auto typing = std::dynamic_pointer_cast<K::FeatureTyping>(relationship)) {
                        if (!feature) continue;
                        feature->appendOwnedTyping(typing);
                        typing->setOwningFeature(feature);
                    } else if (const auto subclassification = std::dynamic_pointer_cast<K::Subclassification>(relationship)) {
                        const auto classifier = std::dynamic_pointer_cast<K::Classifier>(owner);
                        if (!classifier) continue;
                        classifier->appendOwnedSubclassification(subclassification);
                        classifier->appendOwnedSpecialization(subclassification);
                    } else if (const auto specialization = std::dynamic_pointer_cast<K::Specialization>(relationship)) {
                        if (!type) continue;
                        type->appendOwnedSpecialization(specialization);
                        specialization->setOwningType(type);
                    } else if (const auto conjugation = std::dynamic_pointer_cast<K::Conjugation>(relationship)) {
                        if (!type) continue;
                        type->setConjugation(conjugation);
                        conjugation->setOwningType(type);
                    } else if (const auto disjoining = std::dynamic_pointer_cast<K::Disjoining>(relationship)) {
                        if (!type) continue;
                        type->appendOwnedDisjoining(disjoining);
                        disjoining->setOwningType(type);
                    } else if (const auto unioning = std::dynamic_pointer_cast<K::Unioning>(relationship)) {
                        if (type) type->appendOwnedUnioning(unioning);
                    } else if (const auto intersecting = std::dynamic_pointer_cast<K::Intersecting>(relationship)) {
                        if (type) type->appendOwnedIntersecting(intersecting);
                    } else if (const auto differencing = std::dynamic_pointer_cast<K::Differencing>(relationship)) {
                        if (type) type->appendOwnedDifferencing(differencing);
                    } else if (const auto inverting = std::dynamic_pointer_cast<K::FeatureInverting>(relationship)) {
                        if (!feature) continue;
                        feature->appendOwnedFeatureInverting(inverting);
                        inverting->setOwningFeature(feature);
                    } else if (const auto chaining = std::dynamic_pointer_cast<K::FeatureChaining>(relationship)) {
                        if (feature) feature->appendOwnedFeatureChaining(chaining);
                    } else if (const auto featuring = std::dynamic_pointer_cast<K::TypeFeaturing>(relationship)) {
                        if (feature) feature->appendOwnedTypeFeaturing(featuring);
                    }
                }
            }

            // What the name resolution of a Workspace needs: the root, the declared visibilities, the imports and the aliases.
            void collectResolutionData() {
                D.data.root = D.root;
                for (const auto& element : D.elements) {
                    if (const auto membership = std::dynamic_pointer_cast<K::OwningMembership>(element)) {
                        const auto member = membership->ownedMemberElement();
                        if (member && membership->visibility() != K::PUBLIC) D.data.visibility[member.get()] = membership->visibility();
                        continue;
                    }
                    if (const auto membership = std::dynamic_pointer_cast<K::Membership>(element)) {
                        if (std::dynamic_pointer_cast<K::Namespace>(element)) continue;
                        // A membership that does not own its member: an alias.
                        auto alias = std::make_shared<AliasRecord>();
                        alias->owner = membership->owningRelatedElement();
                        alias->membership = membership;
                        alias->name = membership->memberName().value_or("");
                        alias->shortName = membership->memberShortName().value_or("");
                        alias->visibility = membership->visibility();
                        alias->line = static_cast<int>(D.lineOfElement[element.get()]);
                        D.aliases.push_back(alias);
                        D.data.aliases.push_back(alias);
                        continue;
                    }
                    if (const auto import = std::dynamic_pointer_cast<K::Import>(element)) {
                        auto record = std::make_shared<ImportRecord>();
                        record->owner = import->owningRelatedElement();
                        record->element = import;
                        record->isMembershipImport = std::dynamic_pointer_cast<K::MembershipImport>(import) != nullptr;
                        record->isRecursive = import->isRecursive();
                        record->isImportAll = import->isImportAll();
                        record->visibility = import->visibility();
                        record->line = static_cast<int>(D.lineOfElement[element.get()]);
                        D.imports.push_back(record);
                        D.data.imports.push_back(record);
                    }
                }
            }
        };
    }

    std::unique_ptr<XmiDocument> XmiReader::read(const std::string& text, const std::string& sourceName) {
        std::unique_ptr<XmiDocument> document(new XmiDocument());
        document->impl_->name = sourceName;
        Reader reader(*document->impl_, text);
        reader.run(text);
        return document;
    }

    // -----------------------------------------------------------------------------------------------------------------
    // Step two: the references
    // -----------------------------------------------------------------------------------------------------------------

    namespace {

        /// The end of a relationship the owner stands for, if the file does not say (and the end is still the stand-in of the factory).
        template <class T>
        std::shared_ptr<T> endOrOwner(std::shared_ptr<T> end, const ElementPtr& owner) {
            if ((!end || isUnresolved(end)) && owner) {
                if (auto typed = std::dynamic_pointer_cast<T>(owner)) return typed;
            }
            return end;
        }

        /// Makes the redundant ends of a relationship (general / specific, subsetted / subsetting, ...) consistent with the properties
        /// that were read from the file, like the Retarget helpers do for the relationships of the textual notation.
        void retarget(const std::shared_ptr<K::Relationship>& relationship, std::set<K::Feature*>& typed, std::set<K::Feature*>& chained) {
            const ElementPtr owner = relationship->owningRelatedElement();
            if (const auto redefinition = std::dynamic_pointer_cast<K::Redefinition>(relationship)) {
                if (const auto specific = endOrOwner(redefinition->redefiningFeature(), owner)) {
                    redefinition->setRedefiningFeature(specific);
                    redefinition->setSubsettingFeature(specific);
                    redefinition->setSpecific(specific);
                }
                if (const auto general = redefinition->redefinedFeature()) Retarget::redefinition(*redefinition, general);
            } else if (const auto referenceSubsetting = std::dynamic_pointer_cast<K::ReferenceSubsetting>(relationship)) {
                if (const auto specific = endOrOwner(referenceSubsetting->referencingFeature(), owner)) {
                    referenceSubsetting->setReferencingFeature(specific);
                    referenceSubsetting->setSubsettingFeature(specific);
                    referenceSubsetting->setSpecific(specific);
                }
                if (const auto general = referenceSubsetting->referencedFeature()) Retarget::referenceSubsetting(*referenceSubsetting, general);
            } else if (const auto crossSubsetting = std::dynamic_pointer_cast<K::CrossSubsetting>(relationship)) {
                if (const auto specific = endOrOwner(crossSubsetting->crossingFeature(), owner)) {
                    crossSubsetting->setCrossingFeature(specific);
                    crossSubsetting->setSubsettingFeature(specific);
                    crossSubsetting->setSpecific(specific);
                }
                if (const auto general = crossSubsetting->crossedFeature()) Retarget::crossSubsetting(*crossSubsetting, general);
            } else if (const auto subsetting = std::dynamic_pointer_cast<K::Subsetting>(relationship)) {
                if (const auto specific = endOrOwner(subsetting->subsettingFeature(), owner)) {
                    subsetting->setSubsettingFeature(specific);
                    subsetting->setSpecific(specific);
                }
                if (const auto general = subsetting->subsettedFeature()) Retarget::subsetting(*subsetting, general);
            } else if (const auto typing = std::dynamic_pointer_cast<K::FeatureTyping>(relationship)) {
                if (const auto specific = endOrOwner(typing->typedFeature(), owner)) {
                    typing->setTypedFeature(specific);
                    typed.insert(specific.get());
                }
                if (const auto general = typing->type()) Retarget::featureTyping(*typing, general);
            } else if (const auto subclassification = std::dynamic_pointer_cast<K::Subclassification>(relationship)) {
                if (const auto specific = endOrOwner(subclassification->subclassifier(), owner)) {
                    subclassification->setSubclassifier(specific);
                    subclassification->setSpecific(specific);
                }
                if (const auto general = subclassification->superclassifier()) Retarget::subclassification(*subclassification, general);
            } else if (const auto specialization = std::dynamic_pointer_cast<K::Specialization>(relationship)) {
                if (const auto specific = endOrOwner(specialization->specific(), owner)) specialization->setSpecific(specific);
            } else if (const auto conjugation = std::dynamic_pointer_cast<K::Conjugation>(relationship)) {
                if (const auto conjugated = endOrOwner(conjugation->conjugatedType(), owner)) conjugation->setConjungatedType(conjugated);
            } else if (const auto disjoining = std::dynamic_pointer_cast<K::Disjoining>(relationship)) {
                if (const auto disjoined = endOrOwner(disjoining->typeDisjoined(), owner)) disjoining->setTypeDisjoined(disjoined);
            } else if (const auto unioning = std::dynamic_pointer_cast<K::Unioning>(relationship)) {
                if (const auto unioned = endOrOwner(unioning->typeUnioned(), owner)) unioning->setTypeUnioned(unioned);
            } else if (const auto intersecting = std::dynamic_pointer_cast<K::Intersecting>(relationship)) {
                if (const auto intersected = endOrOwner(intersecting->typeIntersecting(), owner)) intersecting->setTypeIntersecting(intersected);
            } else if (const auto differencing = std::dynamic_pointer_cast<K::Differencing>(relationship)) {
                if (const auto differenced = endOrOwner(differencing->typeDifferenced(), owner)) differencing->setTypeDifferenced(differenced);
            } else if (const auto chaining = std::dynamic_pointer_cast<K::FeatureChaining>(relationship)) {
                if (const auto feature = endOrOwner(chaining->featureChained(), owner)) {
                    chaining->setFeatureChained(feature);
                    chained.insert(feature.get());
                }
            } else if (const auto featuring = std::dynamic_pointer_cast<K::TypeFeaturing>(relationship)) {
                if (const auto feature = endOrOwner(featuring->featureOfType(), owner)) featuring->setFeatureOfType(feature);
            }
        }
    }

    void XmiReader::link(XmiDocument& document, const XmiIndex& index) {
        auto& D = *document.impl_;
        D.unresolvedList.clear();

        for (auto& pending : D.pending) {
            if (pending.done) continue;
            const PropertyBinding& binding = *pending.binding;
            std::vector<ElementPtr> targets;
            pending.resolved.assign(pending.tokens.size(), false);
            bool complete = true;
            for (size_t i = 0; i < pending.tokens.size(); ++i) {
                auto& token = pending.tokens[i];
                ElementPtr target;
                const auto local = D.byId.find(token.id);
                if (local != D.byId.end()) target = local->second;
                if (!target) target = index.find(token.id);
                if (target) {
                    pending.resolved[i] = true;
                    targets.push_back(std::move(target));
                    continue;
                }
                complete = false;
                if (binding.canPlaceholder) {
                    if (!token.placeholder) token.placeholder = makePlaceholder(binding.placeholder, token.display);
                    targets.push_back(token.placeholder);
                }
            }
            if (!targets.empty() && (binding.many || targets.size() == 1)) {
                std::string error;
                bool ok = false;
                try {
                    ok = binding.setReferences(*pending.element, targets, error);
                } catch (const std::exception& ex) {
                    error = ex.what();
                }
                if (!ok) {
                    D.report(LOGICAL_ERROR, "cannot set property '" + std::string(binding.name) + "' of " + pending.element->getType() + ": " + error,
                             pending.line);
                    pending.done = true;
                    continue;
                }
            }
            pending.done = complete;
            for (size_t i = 0; i < pending.tokens.size(); ++i) {
                if (pending.resolved[i]) continue;
                XmiUnresolvedReference reference;
                reference.name = pending.tokens[i].display;
                reference.property = std::string(binding.name);
                reference.kind = binding.placeholder;
                reference.line = pending.line;
                reference.context = pending.element;
                reference.placeholder = pending.tokens[i].placeholder;
                D.unresolvedList.push_back(std::move(reference));
            }
        }

        // The redundant ends of the relationships and the collections derived from them.
        std::set<K::Feature*> typed;
        std::set<K::Feature*> chained;
        for (const auto& relationship : D.relationships) retarget(relationship, typed, chained);
        for (const auto& element : D.elements) {
            const auto feature = std::dynamic_pointer_cast<K::Feature>(element);
            if (!feature) continue;
            if (typed.count(feature.get()) != 0) {
                std::vector<std::shared_ptr<K::Type>> types;
                for (const auto& typing : feature->ownedTyping()) {
                    if (typing && typing->type()) types.push_back(typing->type());
                }
                feature->setType(types);
            }
            if (chained.count(feature.get()) != 0) {
                std::vector<std::shared_ptr<K::Feature>> chain;
                for (const auto& chaining : feature->ownedFeatureChaining()) {
                    if (chaining && chaining->chainingFeature()) chain.push_back(chaining->chainingFeature());
                }
                feature->setChainingFeature(chain);
            }
        }

        // The targets of the aliases and imports.
        for (const auto& alias : D.aliases) {
            const auto target = alias->membership->memberElement();
            alias->resolvedTarget = target && !isUnresolved(target) ? target : nullptr;
            const auto name = target ? target->declaredName().value_or("") : std::string();
            alias->target = name.empty() ? std::string() : quoted(name);
        }
        for (const auto& record : D.imports) {
            ElementPtr target;
            if (const auto membershipImport = std::dynamic_pointer_cast<K::MembershipImport>(record->element)) {
                if (const auto membership = membershipImport->importedMembership()) target = membership->memberElement();
            } else if (const auto namespaceImport = std::dynamic_pointer_cast<K::NamespaceImport>(record->element)) {
                target = namespaceImport->importedNamespace();
            }
            record->resolvedTarget = target && !isUnresolved(target) ? target : nullptr;
            const auto name = target ? target->declaredName().value_or("") : std::string();
            record->target = name.empty() ? std::string() : quoted(name);
        }
    }
}
