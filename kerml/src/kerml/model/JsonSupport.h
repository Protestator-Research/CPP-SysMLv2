//
// Helpers of the JSON serialization of the KerML metaclasses (private to the kerml library).
//
// The JSON format is the one of the SysML v2 API (PSM): "@id" and "@type" identify an element, the properties are named like the
// properties of the metamodel, a reference to another element is {"@id": "<uuid>"}, a many-valued property is an array and an empty
// single-valued reference is null. Enumerations are written as their literal text.
//
// The readers are tolerant: a missing key, null or a value of a wrong JSON type leaves the target untouched.
//---------------------------------------------------------
// Constants, Definitions, Pragmas
//---------------------------------------------------------
#pragma once
//---------------------------------------------------------
// External Classes
//---------------------------------------------------------
#include <cstdint>
#include <functional>
#include <memory>
#include <optional>
#include <string>
#include <type_traits>
#include <vector>
#include <boost/uuid/nil_generator.hpp>
#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/string_generator.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <nlohmann/json.hpp>
//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include <kerml/root/elements/Element.h>
#include <kerml/core/features/FeatureDirectionKind.h>
#include <kerml/root/namespaces/VisibilityKind.h>
//---------------------------------------------------------

namespace KerML::Entities::Json {
    /**
     * Resolves the id of an element to the element (empty if the id is unknown). Used by Element::resolveJsonReferences().
     */
    using Lookup = std::function<std::shared_ptr<Element>(const boost::uuids::uuid&)>;

    /**
     * The ids of the elements a property refers to as long as they are not resolved to objects. Empty if there are none.
     */
    using References = std::optional<std::vector<boost::uuids::uuid>>;

    /**
     * Decides if a text is a JSON object (its first character that is no whitespace is '{').
     * Used by the constructors that take either a name or a JSON representation.
     */
    inline bool looksLikeJson(const std::string& text) {
        for (const char c : text) {
            if (c == ' ' || c == '\t' || c == '\r' || c == '\n')
                continue;
            return c == '{';
        }
        return false;
    }

    /**
     * The element id of the constructors that take an element id or a JSON representation: the UUID that is written in the text, or
     * a random UUID if the text is JSON (the id is read from the JSON afterwards).
     * @throws std::runtime_error If the text is no JSON and no valid UUID (boost::uuids::string_generator).
     */
    inline boost::uuids::uuid elementIdOf(const std::string& text) {
        if (looksLikeJson(text))
            return boost::uuids::random_generator()();
        return boost::uuids::string_generator()(text);
    }

    //-----------------------------------------------------
    // Writing
    //-----------------------------------------------------

    /**
     * The JSON identity of an element: {"@id": "<uuid>"}.
     */
    inline nlohmann::json identityOf(const boost::uuids::uuid& id) {
        nlohmann::json json = nlohmann::json::object();
        json["@id"] = boost::uuids::to_string(id);
        return json;
    }

    /**
     * The JSON identity of an element, or null for an empty pointer.
     */
    template<class T>
    nlohmann::json identity(const std::shared_ptr<T>& element) {
        if (!element)
            return nullptr;
        return identityOf(element->getId());
    }

    /**
     * An array of the identities of the elements (empty pointers are skipped).
     */
    template<class T>
    nlohmann::json identities(const std::vector<std::shared_ptr<T>>& elements) {
        nlohmann::json json = nlohmann::json::array();
        for (const auto& element : elements) {
            if (element)
                json.push_back(identityOf(element->getId()));
        }
        return json;
    }

    /**
     * A single-valued reference: the identity of the element. If there is no element, the stored id of the reference that is not
     * resolved yet is written (null if there is none).
     */
    template<class T>
    nlohmann::json reference(const References& unresolved, const std::shared_ptr<T>& element) {
        if (element)
            return identity(element);
        if (unresolved && !unresolved->empty())
            return identityOf(unresolved->front());
        return nullptr;
    }

    template<class T>
    nlohmann::json reference(const References& unresolved, const std::optional<std::shared_ptr<T>>& element) {
        return reference(unresolved, element.value_or(nullptr));
    }

    /**
     * A many-valued reference: an array of identities. If there are no elements, the stored ids of the references that are not
     * resolved yet are written.
     */
    template<class T>
    nlohmann::json reference(const References& unresolved, const std::vector<std::shared_ptr<T>>& elements) {
        if (!elements.empty() || !unresolved)
            return identities(elements);
        nlohmann::json json = nlohmann::json::array();
        for (const auto& id : *unresolved)
            json.push_back(identityOf(id));
        return json;
    }

    /**
     * The id of an element as text that is derived from a reference (for example memberElementId): the text of the element, or, if the
     * reference is not resolved yet, the id that was read from JSON.
     */
    inline nlohmann::json idText(const std::string& id, const References& unresolved) {
        if ((id.empty() || id == boost::uuids::to_string(boost::uuids::nil_uuid())) && unresolved && !unresolved->empty())
            return boost::uuids::to_string(unresolved->front());
        return id;
    }

    inline nlohmann::json value(bool v) {
        return v;
    }

    template<class T, std::enable_if_t<std::is_arithmetic_v<T>, int> = 0>
    nlohmann::json value(T v) {
        return v;
    }

    inline nlohmann::json value(const std::string& v) {
        return v;
    }

    inline nlohmann::json value(const std::optional<std::string>& v) {
        if (!v.has_value())
            return nullptr;
        return *v;
    }

    inline std::string literal(FeatureDirectionKind direction) {
        switch (direction) {
            case IN: return "in";
            case IN_OUT: return "inout";
            case OUT: return "out";
        }
        return "in";
    }

    inline std::string literal(VisibilityKind visibility) {
        switch (visibility) {
            case PRIVATE: return "private";
            case PROTECTED: return "protected";
            case PUBLIC: return "public";
        }
        return "public";
    }

    inline nlohmann::json value(FeatureDirectionKind v) {
        return literal(v);
    }

    inline nlohmann::json value(VisibilityKind v) {
        return literal(v);
    }

    inline nlohmann::json value(const std::optional<FeatureDirectionKind>& v) {
        if (!v.has_value())
            return nullptr;
        return literal(*v);
    }

    //-----------------------------------------------------
    // Reading
    //-----------------------------------------------------

    inline bool readString(const nlohmann::json& json, const char* key, std::string& out) {
        const auto it = json.find(key);
        if (it == json.end() || !it->is_string())
            return false;
        out = it->get<std::string>();
        return true;
    }

    inline bool readBool(const nlohmann::json& json, const char* key, bool& out) {
        const auto it = json.find(key);
        if (it == json.end() || !it->is_boolean())
            return false;
        out = it->get<bool>();
        return true;
    }

    template<class T, std::enable_if_t<std::is_integral_v<T> && !std::is_same_v<T, bool>, int> = 0>
    bool readInt(const nlohmann::json& json, const char* key, T& out) {
        const auto it = json.find(key);
        if (it == json.end() || !(it->is_number_integer() || it->is_number_unsigned()))
            return false;
        out = it->get<T>();
        return true;
    }

    inline bool readDouble(const nlohmann::json& json, const char* key, double& out) {
        const auto it = json.find(key);
        if (it == json.end() || !it->is_number())
            return false;
        out = it->get<double>();
        return true;
    }

    inline bool readStringArray(const nlohmann::json& json, const char* key, std::vector<std::string>& out) {
        const auto it = json.find(key);
        if (it == json.end() || !it->is_array())
            return false;
        out.clear();
        for (const auto& item : *it) {
            if (item.is_string())
                out.push_back(item.get<std::string>());
        }
        return true;
    }

    inline bool readEnum(const nlohmann::json& json, const char* key, FeatureDirectionKind& out) {
        std::string text;
        if (!readString(json, key, text))
            return false;
        if (text == "in") { out = IN; return true; }
        if (text == "inout") { out = IN_OUT; return true; }
        if (text == "out") { out = OUT; return true; }
        return false;
    }

    inline bool readEnum(const nlohmann::json& json, const char* key, VisibilityKind& out) {
        std::string text;
        if (!readString(json, key, text))
            return false;
        if (text == "private") { out = PRIVATE; return true; }
        if (text == "protected") { out = PROTECTED; return true; }
        if (text == "public") { out = PUBLIC; return true; }
        return false;
    }

    /**
     * The id of a reference {"@id": "<uuid>"} (or of a plain UUID text).
     */
    inline std::optional<boost::uuids::uuid> parseIdentity(const nlohmann::json& json) {
        const nlohmann::json* text = &json;
        if (json.is_object()) {
            const auto it = json.find("@id");
            if (it == json.end())
                return std::nullopt;
            text = &*it;
        }
        if (!text->is_string())
            return std::nullopt;
        try {
            return boost::uuids::string_generator()(text->get<std::string>());
        } catch (const std::exception&) {
            return std::nullopt;
        }
    }

    /**
     * Reads a single- or many-valued reference. Returns true if the key holds null, an identity or an array of identities; the ids
     * that are valid are put into @p out (empty for null). Values of another JSON type (for example the empty string that older
     * versions wrote for an empty reference) are ignored and return false.
     */
    inline bool readReferences(const nlohmann::json& json, const char* key, std::vector<boost::uuids::uuid>& out) {
        const auto it = json.find(key);
        if (it == json.end())
            return false;
        out.clear();
        if (it->is_null())
            return true;
        if (it->is_object()) {
            if (const auto id = parseIdentity(*it))
                out.push_back(*id);
            return true;
        }
        if (it->is_array()) {
            for (const auto& item : *it) {
                if (!item.is_object())
                    continue;
                if (const auto id = parseIdentity(item))
                    out.push_back(*id);
            }
            return true;
        }
        return false;
    }
}
