//
// Minimal reader for the XMI files of the OMG pilot implementation (resources/sysml.library.xmi/**, *.sysmlx / *.kermlx).
//
// The files are plain XML: every model element is an XML element (the root, or a child named "ownedRelationship" (a
// relationship owned by the enclosing element) or "ownedRelatedElement" (an element owned by the enclosing relationship));
// its metaclass is "xsi:type", its name "declaredName" / "declaredShortName". References to other elements are either XML
// attributes whose value is an element id (same file) or child tags with an "href" of the form "<file>#<id>". No external
// XML library is used (the parser below understands exactly the subset that occurs in these files).
//
// Used by ModelDiff.h (AP11): the oracle the abstract syntax built by our listeners is compared with.
//
#pragma once

#include <algorithm>
#include <cctype>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <functional>
#include <map>
#include <memory>
#include <optional>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

namespace ConformanceTest::Xmi {

// ---------------------------------------------------------------------------------------------------------------------
// Names in the textual notation
// ---------------------------------------------------------------------------------------------------------------------

// Removes the quotes of an unrestricted name ('a b' -> a b) and resolves its escape sequences; other names are returned as is.
inline std::string unquoteName(const std::string& raw) {
    if (raw.size() >= 2 && raw.front() == '\'' && raw.back() == '\'') {
        std::string out;
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

// A name segment in the form of a qualified name: basic names as they are, every other name quoted ('a b', 'it\'s').
inline std::string quoteName(const std::string& name) {
    bool basic = !name.empty() && !(name[0] >= '0' && name[0] <= '9');
    for (char c : name) {
        if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_')) {
            basic = false;
            break;
        }
    }
    if (basic) return name;
    std::string out = "'";
    for (char c : name) {
        switch (c) {
            case '\'': out += "\\'"; break;
            case '\\': out += "\\\\"; break;
            case '\n': out += "\\n"; break;
            case '\t': out += "\\t"; break;
            default: out.push_back(c); break;
        }
    }
    out += "'";
    return out;
}

inline std::string joinQualifiedName(const std::string& qualifier, const std::string& name) {
    return qualifier.empty() ? quoteName(name) : qualifier + "::" + quoteName(name);
}

// ---------------------------------------------------------------------------------------------------------------------
// The XML subset
// ---------------------------------------------------------------------------------------------------------------------

namespace detail {

inline void appendUtf8(std::string& out, unsigned long cp) {
    if (cp < 0x80) {
        out.push_back(static_cast<char>(cp));
    } else if (cp < 0x800) {
        out.push_back(static_cast<char>(0xC0 | (cp >> 6)));
        out.push_back(static_cast<char>(0x80 | (cp & 0x3F)));
    } else if (cp < 0x10000) {
        out.push_back(static_cast<char>(0xE0 | (cp >> 12)));
        out.push_back(static_cast<char>(0x80 | ((cp >> 6) & 0x3F)));
        out.push_back(static_cast<char>(0x80 | (cp & 0x3F)));
    } else {
        out.push_back(static_cast<char>(0xF0 | (cp >> 18)));
        out.push_back(static_cast<char>(0x80 | ((cp >> 12) & 0x3F)));
        out.push_back(static_cast<char>(0x80 | ((cp >> 6) & 0x3F)));
        out.push_back(static_cast<char>(0x80 | (cp & 0x3F)));
    }
}

inline std::string decodeEntities(const std::string& text) {
    if (text.find('&') == std::string::npos) return text;
    std::string out;
    out.reserve(text.size());
    for (size_t i = 0; i < text.size(); ++i) {
        if (text[i] != '&') {
            out.push_back(text[i]);
            continue;
        }
        const size_t end = text.find(';', i);
        if (end == std::string::npos) {
            out.push_back(text[i]);
            continue;
        }
        const std::string entity = text.substr(i + 1, end - i - 1);
        if (entity == "amp") out.push_back('&');
        else if (entity == "lt") out.push_back('<');
        else if (entity == "gt") out.push_back('>');
        else if (entity == "quot") out.push_back('"');
        else if (entity == "apos") out.push_back('\'');
        else if (!entity.empty() && entity[0] == '#') {
            try {
                const bool hex = entity.size() > 1 && (entity[1] == 'x' || entity[1] == 'X');
                appendUtf8(out, std::stoul(entity.substr(hex ? 2 : 1), nullptr, hex ? 16 : 10));
            } catch (...) {
            }
        } else {
            out.append(text, i, end - i + 1);
        }
        i = end;
    }
    return out;
}

struct XmlAttribute {
    std::string name;
    std::string value;
};

// Calls onStart(tag, attributes, selfClosing) and onEnd(tag) in document order; text, comments, processing instructions and the
// document type are skipped.
template <class OnStart, class OnEnd>
void parseXml(const std::string& text, OnStart onStart, OnEnd onEnd) {
    size_t i = 0;
    const size_t n = text.size();
    auto isSpace = [](char c) { return c == ' ' || c == '\t' || c == '\r' || c == '\n'; };
    while (i < n) {
        const size_t lt = text.find('<', i);
        if (lt == std::string::npos) break;
        i = lt + 1;
        if (i >= n) break;
        if (text.compare(i, 3, "!--") == 0) {
            const size_t end = text.find("-->", i);
            i = end == std::string::npos ? n : end + 3;
            continue;
        }
        if (text[i] == '?' || text[i] == '!') {
            const size_t end = text.find('>', i);
            i = end == std::string::npos ? n : end + 1;
            continue;
        }
        if (text[i] == '/') {
            ++i;
            const size_t start = i;
            while (i < n && text[i] != '>' && !isSpace(text[i])) ++i;
            const std::string tag = text.substr(start, i - start);
            while (i < n && text[i] != '>') ++i;
            ++i;
            onEnd(tag);
            continue;
        }
        const size_t start = i;
        while (i < n && text[i] != '>' && text[i] != '/' && !isSpace(text[i])) ++i;
        const std::string tag = text.substr(start, i - start);
        std::vector<XmlAttribute> attributes;
        bool selfClosing = false;
        while (i < n) {
            while (i < n && isSpace(text[i])) ++i;
            if (i >= n) break;
            if (text[i] == '>') {
                ++i;
                break;
            }
            if (text[i] == '/') {
                selfClosing = true;
                ++i;
                continue;
            }
            const size_t nameStart = i;
            while (i < n && text[i] != '=' && !isSpace(text[i]) && text[i] != '>' && text[i] != '/') ++i;
            XmlAttribute attribute;
            attribute.name = text.substr(nameStart, i - nameStart);
            while (i < n && isSpace(text[i])) ++i;
            if (i < n && text[i] == '=') {
                ++i;
                while (i < n && isSpace(text[i])) ++i;
                if (i < n && (text[i] == '"' || text[i] == '\'')) {
                    const char quote = text[i++];
                    const size_t valueStart = i;
                    while (i < n && text[i] != quote) ++i;
                    attribute.value = decodeEntities(text.substr(valueStart, i - valueStart));
                    ++i;
                }
            }
            attributes.push_back(std::move(attribute));
        }
        onStart(tag, attributes, selfClosing);
        if (selfClosing) onEnd(tag);
    }
}

inline std::string localName(const std::string& qualified) {
    const size_t colon = qualified.rfind(':');
    return colon == std::string::npos ? qualified : qualified.substr(colon + 1);
}

inline bool looksLikeId(const std::string& value) {
    if (value.size() != 36) return false;
    for (size_t i = 0; i < value.size(); ++i) {
        const char c = value[i];
        if (i == 8 || i == 13 || i == 18 || i == 23) {
            if (c != '-') return false;
        } else if (!std::isxdigit(static_cast<unsigned char>(c))) {
            return false;
        }
    }
    return true;
}

inline std::string urlDecode(const std::string& text) {
    std::string out;
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

}  // namespace detail

// ---------------------------------------------------------------------------------------------------------------------
// The model of one XMI file
// ---------------------------------------------------------------------------------------------------------------------

struct Reference {
    /// The name of the attribute / tag that holds the reference, for example "type" or "redefinedFeature".
    std::string role;
    /// The file that holds the target (absolute, normalized); empty for a target in the same file.
    std::string file;
    std::string id;
};

struct Element {
    std::string id;
    /// The metaclass, without the "sysml:" prefix.
    std::string type;
    std::string name;
    std::string shortName;
    std::string visibility;  // as written; empty means public
    std::string memberName;
    std::string memberShortName;
    std::string direction;
    bool isEnd = false;
    /// True if the element is a relationship that is owned by @c parent (an "ownedRelationship" of it).
    bool isOwnedRelationship = false;
    /// The element that owns this element: the enclosing element for an owned relationship, the owner of the enclosing relationship
    /// for an owned related element. -1 for the root.
    int parent = -1;
    /// For an owned related element: the relationship that owns it (-1 otherwise).
    int owningRelationship = -1;
    std::vector<Reference> references;

    const Reference* reference(const std::string& role) const {
        for (const auto& reference : references) {
            if (reference.role == role) return &reference;
        }
        return nullptr;
    }
};

struct File {
    std::string path;
    std::vector<Element> elements;
    std::unordered_map<std::string, int> byId;
    /// Memoized qualified names; see Corpus::qualifiedName.
    mutable std::vector<signed char> qualifiedNameState;  // 0 unknown, 1 known, 2 none
    mutable std::vector<std::string> qualifiedNames;
    /// For every element: the first Redefinition it owns (-1 if none); the source of the effective name of an unnamed feature.
    std::vector<int> firstRedefinition;
};

inline bool isMembershipType(const std::string& type) {
    return type == "FeatureValue" || (type.size() >= 10 && type.compare(type.size() - 10, 10, "Membership") == 0);
}

inline std::unique_ptr<File> parseFile(const std::filesystem::path& path) {
    std::ifstream in(path, std::ios::binary);
    if (!in) throw std::runtime_error("cannot read " + path.string());
    std::ostringstream buffer;
    buffer << in.rdbuf();
    const std::string text = buffer.str();

    auto file = std::make_unique<File>();
    file->path = path.lexically_normal().generic_string();
    const std::string directory = path.parent_path().generic_string();

    struct Frame {
        int element = -1;  // -1: a reference tag
        std::string tag;
    };
    std::vector<Frame> stack;

    auto sameFileOrPath = [&](const std::string& href, Reference& reference) {
        const size_t hash = href.find('#');
        std::string filePart = hash == std::string::npos ? href : href.substr(0, hash);
        reference.id = hash == std::string::npos ? std::string() : href.substr(hash + 1);
        if (filePart.empty()) {
            reference.file.clear();
        } else {
            reference.file = (std::filesystem::path(directory) / std::filesystem::path(detail::urlDecode(filePart))).lexically_normal().generic_string();
            if (reference.file == file->path) reference.file.clear();
        }
    };

    detail::parseXml(
        text,
        [&](const std::string& tag, const std::vector<detail::XmlAttribute>& attributes, bool) {
            const bool hasType = std::any_of(attributes.begin(), attributes.end(), [](const auto& a) { return a.name == "xsi:type"; });
            const std::string href = [&]() {
                for (const auto& a : attributes) {
                    if (a.name == "href") return a.value;
                }
                return std::string();
            }();
            const bool isInstance = stack.empty() || tag == "ownedRelationship" || tag == "ownedRelatedElement";
            if (!isInstance) {
                // A reference tag such as <redefinedFeature href="Items.sysmlx#..."/>.
                int owner = -1;
                for (auto it = stack.rbegin(); it != stack.rend(); ++it) {
                    if (it->element >= 0) {
                        owner = it->element;
                        break;
                    }
                }
                if (owner >= 0 && !href.empty()) {
                    Reference reference;
                    reference.role = tag;
                    sameFileOrPath(href, reference);
                    file->elements[static_cast<size_t>(owner)].references.push_back(std::move(reference));
                }
                stack.push_back({-1, tag});
                return;
            }
            Element element;
            element.type = "Namespace";
            for (const auto& a : attributes) {
                if (a.name == "xsi:type") element.type = detail::localName(a.value);
                else if (a.name == "xmi:id") element.id = a.value;
                else if (a.name == "declaredName") element.name = a.value;
                else if (a.name == "declaredShortName") element.shortName = a.value;
                else if (a.name == "visibility") element.visibility = a.value;
                else if (a.name == "memberName") element.memberName = a.value;
                else if (a.name == "memberShortName") element.memberShortName = a.value;
                else if (a.name == "direction") element.direction = a.value;
                else if (a.name == "isEnd") element.isEnd = a.value == "true";
                else if (detail::looksLikeId(a.value) && a.name != "elementId") {
                    Reference reference;
                    reference.role = a.name;
                    reference.id = a.value;
                    element.references.push_back(std::move(reference));
                }
            }
            (void)hasType;
            // The enclosing instance frame.
            int enclosing = -1;
            for (auto it = stack.rbegin(); it != stack.rend(); ++it) {
                if (it->element >= 0) {
                    enclosing = it->element;
                    break;
                }
            }
            if (tag == "ownedRelationship" && enclosing >= 0) {
                element.isOwnedRelationship = true;
                element.parent = enclosing;
            } else if (tag == "ownedRelatedElement" && enclosing >= 0) {
                element.owningRelationship = enclosing;
                element.parent = file->elements[static_cast<size_t>(enclosing)].parent;
            }
            const int index = static_cast<int>(file->elements.size());
            if (!element.id.empty()) file->byId[element.id] = index;
            file->elements.push_back(std::move(element));
            stack.push_back({index, tag});
        },
        [&](const std::string&) {
            if (!stack.empty()) stack.pop_back();
        });
    file->firstRedefinition.assign(file->elements.size(), -1);
    for (size_t i = 0; i < file->elements.size(); ++i) {
        const auto& element = file->elements[i];
        if (element.isOwnedRelationship && element.type == "Redefinition" && element.parent >= 0 &&
            file->firstRedefinition[static_cast<size_t>(element.parent)] < 0) {
            file->firstRedefinition[static_cast<size_t>(element.parent)] = static_cast<int>(i);
        }
    }
    file->qualifiedNameState.assign(file->elements.size(), 0);
    file->qualifiedNames.assign(file->elements.size(), std::string());
    return file;
}

// ---------------------------------------------------------------------------------------------------------------------
// The files of the oracle, loaded on demand
// ---------------------------------------------------------------------------------------------------------------------

class Corpus {
public:
    explicit Corpus(std::filesystem::path root) : root_(std::move(root)) {}

    /// The file at @p path (absolute; loaded on first use).
    const File& file(const std::filesystem::path& path) {
        const std::string key = path.lexically_normal().generic_string();
        auto it = files_.find(key);
        if (it == files_.end()) it = files_.emplace(key, parseFile(path)).first;
        return *it->second;
    }

    /// All *.sysmlx / *.kermlx files below the root, sorted by path.
    std::vector<std::filesystem::path> listFiles() const {
        std::vector<std::filesystem::path> result;
        if (!std::filesystem::exists(root_)) return result;
        for (const auto& entry : std::filesystem::recursive_directory_iterator(root_)) {
            if (!entry.is_regular_file()) continue;
            const auto ext = entry.path().extension().string();
            if (ext == ".sysmlx" || ext == ".kermlx") result.push_back(entry.path());
        }
        std::sort(result.begin(), result.end());
        return result;
    }

    /// The XMI file that belongs to a library source: the file with the same stem (KerML/Base.kerml -> "Base.kermlx").
    std::optional<std::filesystem::path> fileForSource(const std::filesystem::path& source) const {
        const std::string stem = source.stem().string();
        for (const auto& candidate : listFiles()) {
            if (candidate.stem().string() == stem) return candidate;
        }
        return std::nullopt;
    }

    /// Resolves a reference of an element of @p from to (file, index); null file if the target does not exist.
    std::pair<const File*, int> resolve(const File& from, const Reference& reference) {
        const File* target = &from;
        if (!reference.file.empty()) {
            try {
                target = &file(reference.file);
            } catch (...) {
                return {nullptr, -1};
            }
        }
        auto it = target->byId.find(reference.id);
        if (it == target->byId.end()) return {nullptr, -1};
        return {target, it->second};
    }

    /// The name of element @p index: its declared name; for a feature without one the effective name (KerML 8.3.3.3.x, Feature::effectiveName),
    /// which is the name of the feature it redefines first (`:>> quantity = ...` is the feature `quantity`).
    std::string effectiveName(const File& file, int index, int depth = 0) {
        const Element& element = file.elements[static_cast<size_t>(index)];
        if (!element.name.empty() || element.isOwnedRelationship || depth > 32) return element.name;
        const int redefinition = file.firstRedefinition[static_cast<size_t>(index)];
        if (redefinition < 0) return std::string();
        const auto* reference = file.elements[static_cast<size_t>(redefinition)].reference("redefinedFeature");
        if (reference == nullptr) return std::string();
        const auto [targetFile, targetIndex] = resolve(file, *reference);
        if (targetFile == nullptr) return std::string();
        return effectiveName(*targetFile, targetIndex, depth + 1);
    }

    /// The qualified name (in the form of the textual notation, "A::'b c'::d") of element @p index of @p file: the names of the
    /// element and of all its owning namespaces, connected by memberships. The empty string is the qualified name of the root
    /// namespace; nullopt if the element or one of its owners has no name (or is not owned through a membership).
    std::optional<std::string> qualifiedName(const File& file, int index) {
        const auto slot = static_cast<size_t>(index);
        if (file.qualifiedNameState[slot] == 1) return file.qualifiedNames[slot];
        if (file.qualifiedNameState[slot] == 2) return std::nullopt;
        std::optional<std::string> result;
        const Element& element = file.elements[slot];
        if (element.parent < 0) {
            if (element.type == "Namespace" && element.name.empty()) result = std::string();
        } else if (element.isOwnedRelationship) {
            result = std::nullopt;  // relationships have no qualified name
        } else if (element.owningRelationship >= 0 && isMembershipType(file.elements[static_cast<size_t>(element.owningRelationship)].type)) {
            const std::string name = effectiveName(file, index);
            if (!name.empty()) {
                const auto ownerName = qualifiedName(file, element.parent);
                if (ownerName) result = joinQualifiedName(*ownerName, name);
            }
        }
        if (result) {
            file.qualifiedNames[slot] = *result;
            file.qualifiedNameState[slot] = 1;
        } else {
            file.qualifiedNameState[slot] = 2;
        }
        return result;
    }

    const std::filesystem::path& root() const { return root_; }

private:
    std::filesystem::path root_;
    std::unordered_map<std::string, std::unique_ptr<File>> files_;
};

}  // namespace ConformanceTest::Xmi
