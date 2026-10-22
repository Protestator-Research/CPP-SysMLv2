//
// Writer of the XMI files of the OMG pilot implementation. See XmiWriter.h.
//
//---------------------------------------------------------
// Constants, Definitions, Pragmas
//---------------------------------------------------------
//---------------------------------------------------------
// External Classes
//---------------------------------------------------------
#include <algorithm>
#include <cstdint>
#include <filesystem>
#include <map>
#include <sstream>
#include <string_view>
#include <unordered_map>
#include <unordered_set>

#include <boost/uuid/name_generator_sha1.hpp>
#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/string_generator.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <pugixml.hpp>
//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include <kerml/KerML.h>
#include <sysmlv2/resolution/ResolutionData.h>
#include <sysmlv2/xmi/XmiWriter.h>

#include "XmiBindings.h"
#include "XmiText.h"
//---------------------------------------------------------

namespace SysMLv2::Files {

    namespace K = KerML::Entities;

    namespace {
        using Xmi::ElementPtr;
        using Xmi::PropertyBinding;
        using Xmi::PropertyKind;
        using Xmi::utf8Sequence;

        using Locate = std::function<std::optional<std::string>(const K::Element&)>;
        using Errors = std::vector<std::shared_ptr<ParserError>>;

        /// The namespace of the name based ids: the version 5 UUIDs of this project are derived from it.
        const char* const IdNamespace = "5f0c8a52-3b1e-4d6a-9c7e-2a4b6d8e0f13";

        /// The metaclass name of an element (the getter of the hand-written classes is not const).
        std::string metaclassOf(const K::Element& element) { return const_cast<K::Element&>(element).getType(); }

        /// The concrete metaclass that stands for an abstract class the parsers instantiate (the type reference of `x as T` and `x istype T` is an
        /// InstantiationExpression of the instantiated type); empty if there is none.
        std::string concreteSubstitute(const std::string& abstractType) {
            if (abstractType == "InstantiationExpression") return "InvocationExpression";
            return std::string();
        }

        /// A relationship that is not, at the same time, a namespace (a connector is both a feature and a relationship).
        bool isPlainRelationship(const K::Element& element) {
            return dynamic_cast<const K::Relationship*>(&element) != nullptr && dynamic_cast<const K::Namespace*>(&element) == nullptr;
        }

        /// Percent-encodes the characters of a path that must not occur in an href (the reader decodes "%XX"): the control characters,
        /// the space, every byte of a UTF-8 sequence (above 0x7F) and the characters with a meaning in a URI reference.
        std::string urlEncode(const std::string& text) {
            static const char* digits = "0123456789ABCDEF";
            std::string out;
            out.reserve(text.size());
            for (const char c : text) {
                const auto byte = static_cast<unsigned char>(c);
                if (byte <= 0x20 || byte >= 0x7F || c == '%' || c == '#' || c == '?' || c == '"' || c == '<' || c == '>') {
                    out.push_back('%');
                    out.push_back(digits[byte >> 4]);
                    out.push_back(digits[byte & 0x0F]);
                } else {
                    out.push_back(c);
                }
            }
            return out;
        }

        /// The path a UTF-8 string stands for (the paths between the writer and its callers are UTF-8).
        std::filesystem::path pathFromUtf8(const std::string& text) { return std::filesystem::path(std::u8string(text.begin(), text.end())); }

        /// The path as UTF-8 with "/" as separator.
        std::string genericUtf8(const std::filesystem::path& path) {
            const auto text = path.generic_u8string();
            return std::string(text.begin(), text.end());
        }

        /// True for the characters XML 1.0 can hold (the production Char).
        bool isXmlChar(std::uint32_t code) {
            return code == 0x9 || code == 0xA || code == 0xD || (code >= 0x20 && code <= 0xD7FF) || (code >= 0xE000 && code <= 0xFFFD) ||
                   (code >= 0x10000 && code <= 0x10FFFF);
        }

        /// @p text with every character that an XML 1.0 document cannot hold (control characters, NUL, U+FFFE, U+FFFF) and every byte that is
        /// no UTF-8 replaced by U+FFFD; @p replaced counts the replacements.
        std::string xmlSafe(const std::string& text, std::size_t& replaced) {
            replaced = 0;
            std::string out;
            out.reserve(text.size());
            for (std::size_t i = 0; i < text.size();) {
                std::uint32_t code = 0;
                const std::size_t length = utf8Sequence(text.data() + i, text.size() - i, code);
                if (length != 0 && isXmlChar(code)) {
                    out.append(text, i, length);
                    i += length;
                } else {
                    out += "\xEF\xBF\xBD";
                    ++replaced;
                    i += length == 0 ? 1 : length;
                }
            }
            return out;
        }

        template <class T>
        std::size_t indexOf(const std::vector<std::shared_ptr<T>>& list, const K::Element* element) {
            for (std::size_t i = 0; i < list.size(); ++i) {
                if (list[i].get() == element) return i;
            }
            return list.size();
        }

        class Writer {
        public:
            Writer(ElementPtr root, std::string targetPath, const Locate& locate, Errors& errors, const XmiWriteOptions& options)
                : Root(std::move(root)), TargetPath(std::move(targetPath)), LocateFile(locate), Out(errors), Options(options) {}

            /// Step one only: the id of every element that is written.
            std::unordered_map<const K::Element*, std::string> assign() {
                prepare();
                std::unordered_map<const K::Element*, std::string> ids;
                for (const auto& [element, entry] : Info) ids.emplace(element, entry.id);
                return ids;
            }

            std::string run() {
                prepare();
                if (Info.empty()) return std::string();

                pugi::xml_document xml;
                pugi::xml_node declaration = xml.append_child(pugi::node_declaration);
                declaration.append_attribute("version") = "1.0";
                declaration.append_attribute("encoding") = "UTF-8";
                pugi::xml_node top = xml.append_child(("sysml:" + Info.at(Root.get()).type).c_str());
                top.append_attribute("xmi:version") = "2.0";
                top.append_attribute("xmlns:xmi") = "http://www.omg.org/XMI";
                top.append_attribute("xmlns:xsi") = "http://www.w3.org/2001/XMLSchema-instance";
                top.append_attribute("xmlns:sysml") = "https://www.omg.org/spec/SysML/20250201";
                emit(Root, top, true);

                std::ostringstream stream;
                const unsigned int flags = Options.indent.empty() ? pugi::format_raw : pugi::format_default;
                xml.save(stream, Options.indent.c_str(), flags, pugi::encoding_utf8);
                return stream.str();
            }

        private:
            /// What is known about one element of the tree.
            struct Entry {
                const Xmi::MetaclassBinding* meta = nullptr;
                std::string type;
                std::string id;
                /// The relationships the element owns (role ownedRelationship) and the elements it owns as a relationship (ownedRelatedElement).
                std::vector<ElementPtr> relationships;
                std::vector<ElementPtr> related;
            };

            /// A reference property with its targets.
            struct Reference {
                const PropertyBinding* binding = nullptr;
                std::vector<ElementPtr> targets;
                bool dropped = false;
            };

            /// An owned element that is not written because the source does not list it.
            struct Skipped {
                const K::Element* owner;
                ElementPtr element;
            };

            /// At most this many skipped elements are reported one by one; the rest is summarized.
            static constexpr std::size_t MaxSkippedReports = 10;

            ElementPtr Root;
            std::string TargetPath;
            const Locate& LocateFile;
            Errors& Out;
            const XmiWriteOptions& Options;

            std::unordered_map<const K::Element*, Entry> Info;
            std::unordered_map<const K::Element*, const K::Element*> ParentOf;
            /// The elements that a relationship owns as related element.
            std::unordered_set<const K::Element*> OwnedAsRelated;
            std::unordered_map<std::string, const K::Element*> UsedIds;
            std::unordered_map<const K::Element*, std::optional<std::string>> Located;
            std::unordered_map<const K::Element*, std::string> Keys;
            std::vector<Skipped> SkippedList;
            std::unordered_set<const K::Element*> SkippedSeen;
            /// The stand-ins and wrappers of the end feature memberships of an XMI file: structure of the reader, not reported.
            std::unordered_set<const K::Element*> KnownStructure;
            /// Wrappers of the reader that are written in the end feature membership (adoptedFrom() without XmiWriteOptions::listed): not collected.
            std::unordered_set<const K::Element*> Dropped;

            // ---------------------------------------------------------------------------------------------------------------
            // Errors
            // ---------------------------------------------------------------------------------------------------------------

            void report(ErrorType type, const std::string& message) {
                Out.push_back(std::make_shared<ParserError>(boost::uuids::random_generator()(), "", type, message, -1, -1, TargetPath));
            }

            /// "PartUsage 'engine' (id)" for messages.
            std::string describe(const K::Element& element) const {
                std::string text = metaclassOf(element);
                const auto name = element.declaredName();
                if (name && !name->empty()) text += " '" + *name + "'";
                const auto found = Info.find(&element);
                text += " (" + (found == Info.end() ? element.elementId() : found->second.id) + ")";
                // (a relationship has no name: say whose it is)
                if (isPlainRelationship(element) && !(name && !name->empty())) {
                    const auto owner = dynamic_cast<const K::Relationship&>(element).owningRelatedElement();
                    if (owner) {
                        text += " of " + metaclassOf(*owner);
                        if (owner->declaredName() && !owner->declaredName()->empty()) text += " '" + *owner->declaredName() + "'";
                    }
                }
                return text;
            }

            // ---------------------------------------------------------------------------------------------------------------
            // Step one: the ownership tree and the ids
            // ---------------------------------------------------------------------------------------------------------------

            void prepare() {
                if (!Root || !userIncluded(*Root)) return;
                collect(Root, nullptr);
                reportSkipped();
            }

            /// @param asRelated true if @p parent is a relationship that owns the element as one of its related elements, false if the element
            /// is a relationship of @p parent.
            void collect(const ElementPtr& element, const K::Element* parent, bool asRelated = false) {
                if (!element || Dropped.count(element.get()) != 0) return;
                if (Info.count(element.get()) != 0) {
                    // A relationship that a membership owns as its member is also listed in the relationships of the namespace the
                    // membership belongs to (the way the reader and the parsers wire the model): the membership is the owner in the file.
                    const K::Element* first = ParentOf[element.get()];
                    if (asRelated && OwnedAsRelated.count(element.get()) == 0 && first != nullptr) {
                        auto& siblings = Info.at(first).relationships;
                        siblings.erase(std::remove(siblings.begin(), siblings.end(), element), siblings.end());
                        ParentOf[element.get()] = parent;
                        OwnedAsRelated.insert(element.get());
                    } else if (!asRelated && OwnedAsRelated.count(element.get()) != 0 && parent != nullptr) {
                        // (already owned by the relationship: not written a second time)
                        auto& siblings = Info.at(parent).relationships;
                        siblings.erase(std::remove(siblings.begin(), siblings.end(), element), siblings.end());
                    } else {
                        report(ErrorType::LOGICAL_ERROR, describe(*element) + " is owned more than once (by " + (first != nullptr ? describe(*first) : std::string("-")) +
                                                             " and by " + (parent != nullptr ? describe(*parent) : std::string("-")) + "); it is written once");
                    }
                    return;
                }
                const std::string type = metaclassOf(*element);
                const Xmi::MetaclassBinding* meta = Xmi::findMetaclass(type);
                std::string written = type;
                if (meta != nullptr && meta->isAbstract) written = concreteSubstitute(type);
                if (meta == nullptr || written.empty()) {
                    report(ErrorType::LOGICAL_ERROR, "cannot write an element of the class '" + type + "': it is no concrete KerML or SysML metaclass; it and its owned elements are not written");
                    return;
                }
                Entry entry;
                entry.meta = meta;
                entry.type = written;
                for (const auto& relationship : element->ownedRelationship()) {
                    if (!relationship) continue;
                    if (included(*relationship)) {
                        entry.relationships.push_back(relationship);
                    } else {
                        noteSkipped(*element, relationship);
                    }
                }
                // A relationship the element owns but does not list among its ownedRelationship (the one owned by a membership that is no
                // member of the element, such as the annotation of an alias): the owned elements of the model know it.
                for (const auto& owned : element->ownedElements()) {
                    if (!owned || !isPlainRelationship(*owned)) continue;
                    if (!included(*owned)) {
                        noteSkipped(*element, owned);
                    } else if (std::find(entry.relationships.begin(), entry.relationships.end(), owned) == entry.relationships.end()) {
                        entry.relationships.push_back(owned);
                    }
                }
                if (const auto relationship = std::dynamic_pointer_cast<K::Relationship>(element); relationship && isPlainRelationship(*element)) {
                    const auto all = relationship->ownedRelatedElement();
                    for (const auto& related : all) {
                        if (!related) continue;
                        if (included(*related)) {
                            entry.related.push_back(related);
                        } else {
                            noteSkipped(*element, related);
                        }
                    }
                    // (without XmiWriteOptions::listed the stand-in is an element of the tree like any other: adoption replaces it)
                    if (!all.empty() && parent != nullptr && (entry.related.empty() || !Options.listed)) {
                        auto adopted = adoptedFrom(element, all, *parent);
                        if (!adopted.empty()) entry.related = std::move(adopted);
                    }
                }
                ParentOf[element.get()] = parent;
                if (asRelated) OwnedAsRelated.insert(element.get());
                entry.id = idOf(*element);
                const auto& stored = Info.emplace(element.get(), std::move(entry)).first->second;
                // (Info does not move its values: the vectors of the entry stay valid while the children are collected)
                // (collect() may take a relationship out of the lists: the loops run over copies)
                const std::vector<ElementPtr> relationships = stored.relationships;
                const std::vector<ElementPtr> related = stored.related;
                for (const auto& relationship : relationships) collect(relationship, element.get(), false);
                for (const auto& owned : related) collect(owned, element.get(), true);
            }

            // ---------------------------------------------------------------------------------------------------------------
            // What the source does not list
            // ---------------------------------------------------------------------------------------------------------------

            bool userIncluded(const K::Element& element) const { return !Options.include || Options.include(element); }

            bool listed(const K::Element& element) const { return !Options.listed || Options.listed(element); }

            bool included(const K::Element& element) const { return listed(element) && userIncluded(element); }

            /// Remembers an owned element that is left out because the source does not list it (a choice of Options.include is not reported).
            void noteSkipped(const K::Element& owner, const ElementPtr& element) {
                if (!element || listed(*element)) return;
                if (SkippedSeen.insert(element.get()).second) SkippedList.push_back({&owner, element});
            }

            /// A WARNING for every element that is left out because the source does not list it, except for the structure of the reader
            /// (see adoptedFrom()); beyond MaxSkippedReports the rest is summarized.
            void reportSkipped() {
                std::size_t shown = 0;
                std::size_t hidden = 0;
                std::map<std::string, std::size_t> hiddenKinds;
                for (const auto& skipped : SkippedList) {
                    if (KnownStructure.count(skipped.element.get()) != 0 || Info.count(skipped.element.get()) != 0) continue;
                    if (shown < MaxSkippedReports) {
                        ++shown;
                        report(ErrorType::WARNING, describe(*skipped.owner) + " owns " + describe(*skipped.element) +
                                                       ", which the source does not list (the classes of the model created it); it and what it owns are not written");
                    } else {
                        ++hidden;
                        ++hiddenKinds[metaclassOf(*skipped.element)];
                    }
                }
                if (hidden == 0) return;
                std::string kinds;
                for (const auto& [kind, count] : hiddenKinds) kinds += (kinds.empty() ? "" : ", ") + kind + " x" + std::to_string(count);
                report(ErrorType::WARNING, std::to_string(hidden) + " more elements that the source does not list are not written (" + kinds + ")");
            }

            /// The reader gives an end feature membership a stand-in (made by the factory) for its member, and wraps the member the file means
            /// in a membership of its own that follows the end feature membership among the relationships of the owner. When the only
            /// related element of an EndFeatureMembership is such a stand-in, the end feature of that next relationship is the one the file
            /// means. Everything is checked: the relationship is an end feature membership whose only element is an unnamed feature of its own;
            /// the next relationship of the owner is a membership of its own that owns one end feature; and the source does not list the
            /// stand-in and the wrapper (XmiWriteOptions::listed), while it lists the end feature. Only the exclusion by the source is undone:
            /// what the caller excluded with Options.include (the wrapper or the end feature) stays excluded.
            /// Without XmiWriteOptions::listed nothing says what the reader made, so the structure decides: the stand-in is the plain feature the
            /// factory makes (not an end, no name, owns nothing) and the wrapper is exactly an OwningMembership or a FeatureMembership (an
            /// end feature membership of a text owns its end feature itself and is followed by the next end feature membership); the wrapper
            /// is then left out of the tree.
            std::vector<ElementPtr> adoptedFrom(const ElementPtr& relationship, const std::vector<ElementPtr>& all, const K::Element& owner) {
                std::vector<ElementPtr> adopted;
                if (!dynamic_cast<const K::EndFeatureMembership*>(relationship.get()) || all.size() != 1) return adopted;
                const bool structural = !Options.listed;
                const ElementPtr& standIn = all.front();
                const auto standInFeature = std::dynamic_pointer_cast<K::Feature>(standIn);
                if (!standInFeature || !standIn->declaredName().value_or(std::string()).empty() ||
                    !standIn->declaredShortName().value_or(std::string()).empty() || standIn->owningRelationship().get() != relationship.get()) {
                    return adopted;
                }
                if (structural ? (standInFeature->isEnd() || !standIn->ownedRelationship().empty()) : listed(*standIn)) return adopted;
                const auto siblings = owner.ownedRelationship();
                for (std::size_t i = 0; i + 1 < siblings.size(); ++i) {
                    if (siblings[i].get() != relationship.get()) continue;
                    const auto wrapper = std::dynamic_pointer_cast<K::OwningMembership>(siblings[i + 1]);
                    if (!wrapper || !userIncluded(*wrapper) || wrapper->owningRelatedElement().get() != &owner) break;
                    if (structural) {
                        const std::string type = metaclassOf(*wrapper);
                        if (type != "OwningMembership" && type != "FeatureMembership") break;
                    } else if (listed(*wrapper)) {
                        break;
                    }
                    const auto members = wrapper->ownedRelatedElement();
                    if (members.size() != 1) break;
                    const auto feature = std::dynamic_pointer_cast<K::Feature>(members.front());
                    if (!feature || !feature->isEnd() || !listed(*feature) || !userIncluded(*feature)) break;
                    KnownStructure.insert(standIn.get());
                    KnownStructure.insert(wrapper.get());
                    // (the wrapper is only a vehicle of the reader: relationships it owns besides the end feature would be lost silently)
                    if (const auto lost = wrapper->ownedRelationship().size(); lost != 0) {
                        report(ErrorType::WARNING, describe(*wrapper) + " is left out, because the end feature it owns is written in the end feature membership, but it owns " +
                                                       std::to_string(lost) + " further relationship" + (lost == 1 ? "" : "s") + ", which " + (lost == 1 ? "is" : "are") + " not written");
                    }
                    if (structural) {
                        // (the owner's entry holds the wrapper; it is collected after the end feature membership)
                        auto& relationships = Info.at(&owner).relationships;
                        relationships.erase(std::remove(relationships.begin(), relationships.end(), siblings[i + 1]), relationships.end());
                        Dropped.insert(wrapper.get());
                    }
                    adopted.push_back(feature);
                    break;
                }
                return adopted;
            }

            // ---------------------------------------------------------------------------------------------------------------
            // Ids
            // ---------------------------------------------------------------------------------------------------------------

            /// The id of an element of the tree; makes sure that no two elements of the tree share an id.
            std::string idOf(const K::Element& element) {
                std::string id = idOfTree(element);
                const auto used = UsedIds.find(id);
                if (used != UsedIds.end() && used->second != &element) {
                    if (Options.ids == XmiWriteOptions::IdMode::NameBased && !keepsId(element)) {
                        // Two elements with the same key (for example equal anonymous elements): the later one gets a numbered key.
                        for (int n = 2;; ++n) {
                            id = nameBasedId(key(element) + "~" + std::to_string(n));
                            if (UsedIds.count(id) == 0) break;
                        }
                    } else {
                        report(ErrorType::LOGICAL_ERROR, "the id '" + id + "' is used by more than one element (" + describe(element) + ")");
                    }
                }
                UsedIds[id] = &element;
                return id;
            }

            bool keepsId(const K::Element& element) const { return Options.keepsId && Options.keepsId(element); }

            /// The id an element of the tree starts from (before the check for duplicates).
            std::string idOfTree(const K::Element& element) {
                if (Options.ids == XmiWriteOptions::IdMode::ElementId || keepsId(element)) return element.elementId();
                return nameBasedId(key(element));
            }

            /// The id of an element in another file (for an href), as that file defines it; nullopt if it is not known. Nothing is derived
            /// here: the element is not part of this tree, so only the table of its file (XmiWriteOptions::foreignId) knows what it is called.
            std::optional<std::string> foreignIdOf(const K::Element& element) const {
                if (Options.foreignId) return Options.foreignId(element);
                if (Options.ids == XmiWriteOptions::IdMode::ElementId || keepsId(element)) return element.elementId();
                return std::nullopt;
            }

            static std::string nameBasedId(const std::string& key) {
                static const boost::uuids::uuid space = boost::uuids::string_generator()(IdNamespace);
                return boost::uuids::to_string(boost::uuids::name_generator_sha1(space)(key));
            }

            /// The owner in the ownership tree (as the tree is written): for a relationship the element that owns it, for any other element the
            /// relationship that owns it. Null for the root.
            const K::Element* parentOf(const K::Element& element) const {
                const auto recorded = ParentOf.find(&element);
                return recorded == ParentOf.end() ? nullptr : recorded->second;
            }

            /// The name of what a relationship relates the owner to: the name of the element it owns, or its member name (an alias).
            static std::string labelOf(const K::Element& element) {
                const auto& relationship = dynamic_cast<const K::Relationship&>(element);
                for (const auto& related : relationship.ownedRelatedElement()) {
                    if (related && related->declaredName() && !related->declaredName()->empty()) return *related->declaredName();
                }
                if (const auto membership = dynamic_cast<const K::Membership*>(&element)) {
                    if (const auto name = const_cast<K::Membership*>(membership)->memberName()) return *name;
                }
                return std::string();
            }

            /// The text the name based id of an element is made of: the identity of the file, the metaclasses and names on the path from the root
            /// of the file, and the position in the ownership structure for what has no name. (Only the file and the names and the order of the
            /// model go into it, nothing else that the file contains.) Only for elements of the tree.
            const std::string& key(const K::Element& element) {
                const auto found = Keys.find(&element);
                if (found != Keys.end()) return found->second;
                std::string text;
                const K::Element* parent = parentOf(element);
                if (parent == nullptr) {
                    // The root of a file: the file is what tells it from the roots of other files.
                    text = "root|" + (Options.fileKey.empty() ? TargetPath : Options.fileKey);
                } else if (isPlainRelationship(element)) {
                    const std::string label = labelOf(element);
                    text = key(*parent) + "/" + metaclassOf(element);
                    text += label.empty() ? "#" + std::to_string(indexOf(parent->ownedRelationship(), &element)) : "(" + label + ")";
                } else {
                    const auto* relationship = dynamic_cast<const K::Relationship*>(parent);
                    const K::Element* owner = relationship != nullptr ? parentOf(*parent) : nullptr;
                    const auto name = element.declaredName();
                    if (relationship != nullptr && owner != nullptr && dynamic_cast<const K::OwningMembership*>(parent) != nullptr) {
                        // A member of a namespace: qualified by the names of its owners.
                        text = key(*owner) + "::" + metaclassOf(element);
                        text += name && !name->empty() ? ":" + *name : "#" + std::to_string(indexOf(owner->ownedRelationship(), parent));
                    } else {
                        const std::size_t position = relationship != nullptr ? indexOf(relationship->ownedRelatedElement(), &element) : 0;
                        text = key(*parent) + "/" + metaclassOf(element) + "#" + std::to_string(position);
                        if (name && !name->empty()) text += ":" + *name;
                    }
                }
                return Keys.emplace(&element, std::move(text)).first->second;
            }

            // ---------------------------------------------------------------------------------------------------------------
            // Step two: the XML
            // ---------------------------------------------------------------------------------------------------------------

            void emit(const ElementPtr& element, pugi::xml_node node, bool isRoot) {
                const Entry& entry = Info.at(element.get());
                if (!isRoot) node.append_attribute("xsi:type") = ("sysml:" + entry.type).c_str();
                node.append_attribute("xmi:id") = entry.id.c_str();
                node.append_attribute("elementId") = entry.id.c_str();
                writeProperties(*element, entry, node);
                for (const auto& relationship : entry.relationships) {
                    if (Info.count(relationship.get()) != 0) emit(relationship, node.append_child("ownedRelationship"), false);
                }
                for (const auto& related : entry.related) {
                    if (Info.count(related.get()) != 0) emit(related, node.append_child("ownedRelatedElement"), false);
                }
            }

            void writeProperties(const K::Element& element, const Entry& entry, pugi::xml_node node) {
                const Xmi::MetaclassBinding& meta = *entry.meta;
                std::vector<Reference> references;
                // The table lists the properties of the metaclass first and those of its supertypes after them; the file has the
                // supertypes first, the way the metamodel declares them.
                std::vector<std::pair<const PropertyBinding*, std::string>> values;
                for (std::size_t i = 0; i < meta.propertyCount; ++i) {
                    const PropertyBinding* binding = meta.properties[i];
                    if (binding->kind == PropertyKind::Reference) {
                        if (binding->getReferences == nullptr) continue;
                        Reference reference;
                        reference.binding = binding;
                        reference.targets = binding->getReferences(element);
                        if (!reference.targets.empty()) references.push_back(std::move(reference));
                    } else if (binding->getValue != nullptr) {
                        if (auto value = binding->getValue(element)) {
                            if (!isNameOfOwnedMember(element, binding->name, *value)) values.emplace_back(binding, std::move(*value));
                        }
                    }
                }
                for (auto it = values.rbegin(); it != values.rend(); ++it) {
                    // (a text that XML cannot hold is written with U+FFFD in place of those bytes; the attribute takes a C string, so a NUL byte
                    // must not reach it)
                    std::size_t replaced = 0;
                    const std::string safe = xmlSafe(it->second, replaced);
                    if (replaced != 0) {
                        report(ErrorType::WARNING, "the value of the property '" + std::string(it->first->name) + "' of " + describe(element) + " has " + std::to_string(replaced) +
                                                       " byte(s) or character(s) that XML cannot hold (control characters, NUL, bytes that are no UTF-8); they are written as U+FFFD");
                    }
                    node.append_attribute(std::string(it->first->name).c_str()) = safe.c_str();
                }
                dropRedundant(element, references);
                for (auto it = references.rbegin(); it != references.rend(); ++it) {
                    if (!it->dropped) writeReference(element, *it, node);
                }
            }

            /// The (short) name of an owning membership is that of the element it owns: the reader gets it from there.
            static bool isNameOfOwnedMember(const K::Element& element, std::string_view property, const std::string& value) {
                if (property != "memberName" && property != "memberShortName") return false;
                const auto* membership = dynamic_cast<const K::OwningMembership*>(&element);
                if (membership == nullptr) return false;
                for (const auto& owned : membership->ownedRelatedElement()) {
                    if (!owned) continue;
                    const auto name = property == "memberName" ? owned->declaredName() : owned->declaredShortName();
                    return name && *name == value;
                }
                return false;
            }

            /// A property that the reader sets from another property of the same element (retarget() of the reader and the setters of the classes).
            struct Derivation {
                std::string_view derived;
                std::string_view from;
            };

            /// The properties the reader derives: when both have the same targets, the first one need not be written. Properties that are not in
            /// the table are always written, even if another property has the same targets (the original type of a port conjugation and its
            /// original port definition, the type of a conjugated port typing and its conjugated port definition): the reader does not derive them.
            static constexpr Derivation Derivations[] = {
                // the specific end of a relationship (the owner of the relationship if the file does not say)
                {"subsettingFeature", "redefiningFeature"},
                {"specific", "redefiningFeature"},
                {"subsettingFeature", "referencingFeature"},
                {"specific", "referencingFeature"},
                {"subsettingFeature", "crossingFeature"},
                {"specific", "crossingFeature"},
                {"specific", "subsettingFeature"},
                {"specific", "typedFeature"},
                {"specific", "subclassifier"},
                // the general end
                {"subsettedFeature", "redefinedFeature"},
                {"subsettedFeature", "referencedFeature"},
                {"subsettedFeature", "crossedFeature"},
                {"general", "redefinedFeature"},
                {"general", "referencedFeature"},
                {"general", "crossedFeature"},
                {"general", "subsettedFeature"},
                {"general", "type"},
                {"general", "superclassifier"},
            };

            /// Drops what the reader derives (the pairs of Derivations whose targets are equal), and the member of a membership that owns it.
            static void dropRedundant(const K::Element& element, std::vector<Reference>& references) {
                // (only the member of an owning membership is implied by the ownership; the crossed feature of a cross subsetting that owns it is not)
                const auto* membership = dynamic_cast<const K::OwningMembership*>(&element);
                std::vector<ElementPtr> owned;
                if (membership != nullptr) owned = membership->ownedRelatedElement();
                for (auto& reference : references) {
                    if (!owned.empty() && reference.binding->name == "memberElement" && std::all_of(reference.targets.begin(), reference.targets.end(), [&](const ElementPtr& target) {
                            return std::find(owned.begin(), owned.end(), target) != owned.end();
                        })) {
                        reference.dropped = true;
                    }
                }
                const auto find = [&](std::string_view name) -> Reference* {
                    for (auto& reference : references) {
                        if (reference.binding->name == name) return &reference;
                    }
                    return nullptr;
                };
                for (const auto& derivation : Derivations) {
                    Reference* derived = find(derivation.derived);
                    Reference* from = find(derivation.from);
                    if (derived == nullptr || from == nullptr || derived->dropped || from->dropped) continue;
                    if (derived->targets == from->targets) derived->dropped = true;
                }
            }

            /// The path of the file an element outside the tree is written to; nullopt if there is none.
            const std::optional<std::string>& fileOf(const K::Element& element) {
                auto found = Located.find(&element);
                if (found == Located.end()) {
                    std::optional<std::string> path;
                    if (LocateFile) path = LocateFile(element);
                    found = Located.emplace(&element, std::move(path)).first;
                }
                return found->second;
            }

            /// "../Kernel%20Libraries/Base.kermlx": the path of another file as seen from the directory of the file that is written, as
            /// percent-encoded UTF-8. A file that no relative path leads to (another drive) is a file URI: "file:///D:/dir/Base.kermlx".
            std::string hrefPathOf(const std::string& path) const {
                namespace fs = std::filesystem;
                std::error_code ec;
                const fs::path from = fs::absolute(pathFromUtf8(TargetPath), ec).lexically_normal().parent_path();
                const fs::path to = fs::absolute(pathFromUtf8(path), ec).lexically_normal();
                const fs::path relative = to.lexically_relative(from);
                if (!relative.empty()) return urlEncode(genericUtf8(relative));
                const std::string absolute = genericUtf8(to);
                if (absolute.compare(0, 2, "//") == 0) return "file:" + urlEncode(absolute);   // \\server\share\file -> file://server/share/file
                if (!absolute.empty() && absolute[0] == '/') return "file://" + urlEncode(absolute);
                return "file:///" + urlEncode(absolute);                                         // D:\dir\file -> file:///D:/dir/file
            }

            void writeReference(const K::Element& element, const Reference& reference, pugi::xml_node node) {
                const std::string property(reference.binding->name);
                struct Resolved {
                    const K::Element* element;
                    std::string href;   // empty: in the tree
                    std::string id;
                };
                std::vector<Resolved> targets;
                bool foreign = false;
                for (const auto& target : reference.targets) {
                    if (isUnresolved(target)) {
                        const auto* marker = dynamic_cast<const UnresolvedMarker*>(target.get());
                        report(ErrorType::WARNING, "unresolved reference '" + (marker != nullptr ? marker->reference : std::string()) + "' in the property '" + property +
                                                       "' of " + describe(element) + "; the reference is not written");
                        continue;
                    }
                    if (const auto inTree = Info.find(target.get()); inTree != Info.end()) {
                        targets.push_back({target.get(), std::string(), inTree->second.id});
                        continue;
                    }
                    const auto& file = fileOf(*target);
                    if (!file && !target->owner() && !target->owningRelationship()) {
                        // (an element no model owns: what the parser keeps for a name it could not resolve, such as the namespace of an import)
                        report(ErrorType::WARNING, "unresolved reference '" + target->declaredName().value_or(std::string()) + "' in the property '" + property + "' of " +
                                                       describe(element) + "; the reference is not written");
                        continue;
                    }
                    if (!file || *file == TargetPath) {
                        report(ErrorType::LOGICAL_ERROR, "the target " + describe(*target) + " of the property '" + property + "' of " + describe(element) +
                                                             (file ? " is not part of the written tree" : " is in no file") + "; the reference is not written");
                        continue;
                    }
                    const auto id = foreignIdOf(*target);
                    if (!id) {
                        report(ErrorType::LOGICAL_ERROR, "the target " + describe(*target) + " of the property '" + property + "' of " + describe(element) +
                                                             " is not written to its file '" + *file + "' (or its id there is not known: XmiWriteOptions::foreignId); the reference is not written");
                        continue;
                    }
                    targets.push_back({target.get(), hrefPathOf(*file), *id});
                    foreign = true;
                }
                if (targets.empty()) return;
                if (!foreign) {
                    std::string ids;
                    for (const auto& target : targets) {
                        if (!ids.empty()) ids += ' ';
                        ids += target.id;
                    }
                    node.append_attribute(property.c_str()) = ids.c_str();
                    return;
                }
                for (const auto& target : targets) {
                    pugi::xml_node tag = node.append_child(property.c_str());
                    const std::string href = target.href + "#" + target.id;
                    tag.append_attribute("href") = href.c_str();
                }
            }
        };
    }

    std::string XmiWriter::write(const std::shared_ptr<KerML::Entities::Element>& root, const std::string& targetPath,
                                 const std::function<std::optional<std::string>(const KerML::Entities::Element&)>& locate,
                                 std::vector<std::shared_ptr<ParserError>>& errors, const XmiWriteOptions& options) {
        if (!root) return std::string();
        Writer writer(root, targetPath, locate, errors, options);
        return writer.run();
    }

    std::unordered_map<const KerML::Entities::Element*, std::string> XmiWriter::assignIds(const std::shared_ptr<KerML::Entities::Element>& root,
                                                                                             const std::string& targetPath,
                                                                                             std::vector<std::shared_ptr<ParserError>>& errors,
                                                                                             const XmiWriteOptions& options) {
        if (!root) return {};
        const Locate none;
        Writer writer(root, targetPath, none, errors, options);
        return writer.assign();
    }
}
