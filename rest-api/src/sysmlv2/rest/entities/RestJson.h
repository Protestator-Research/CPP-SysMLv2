//
// Helpers of the JSON serialization of the REST entities (private to the rest-api library, not installed).
//
// The JSON format is the one of the SysML v2 API (PSM): a reference to another object is {"@id": "<uuid>"}, a many-valued property
// is an array and an empty single-valued reference is null. The readers throw std::invalid_argument for values of a wrong JSON type.
//---------------------------------------------------------
// Constants, Definitions, Pragmas
//---------------------------------------------------------
#pragma once
//---------------------------------------------------------
// External Classes
//---------------------------------------------------------
#include <chrono>
#include <optional>
#include <stdexcept>
#include <algorithm>
#include <cctype>
#include <string>
#include <vector>
#include <boost/uuid/nil_generator.hpp>
#include <boost/uuid/string_generator.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <nlohmann/json.hpp>
//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include <sysmlv2/rest/Deprecation.h>
#include <sysmlv2/rest/entities/JSONEntities.h>
#include <sysmlv2/rest/serialization/Utilities.h>
//---------------------------------------------------------

namespace SysMLv2::REST::Internal {
    /**
     * Decides if a text is a JSON object (its first character that is no whitespace is '{').
     * Used by the constructors that take either a name or a JSON representation.
     */
    /** Compares two ASCII names ignoring the case ("@type" values are case-insensitive). */
    inline bool equalsIgnoreCase(const std::string& left, const std::string& right) {
        return left.size() == right.size() &&
               std::equal(left.begin(), left.end(), right.begin(),
                          [](unsigned char a, unsigned char b) { return std::tolower(a) == std::tolower(b); });
    }

    inline bool looksLikeJson(const std::string& text) {
        for (const char c : text) {
            if (c == ' ' || c == '\t' || c == '\r' || c == '\n')
                continue;
            return c == '{';
        }
        return false;
    }

    /**
     * Parses a text that must be a JSON object.
     * @param context Name of the class for the message, e.g. "Record".
     * @throws std::invalid_argument If the text is not valid JSON or no JSON object.
     */
    inline nlohmann::json parseObject(const std::string& text, const std::string& context) {
        nlohmann::json parsed;
        try {
            parsed = nlohmann::json::parse(text);
        } catch (const nlohmann::json::exception& ex) {
            throw std::invalid_argument(context + ": invalid JSON: " + ex.what());
        }
        if (!parsed.is_object())
            throw std::invalid_argument(context + ": JSON object expected");
        return parsed;
    }

    /**
     * Finds the value under the current key; if it is missing, falls back to the key of an older library version and warns
     * once (warnDeprecated). Returns nullptr if neither key is present. An empty oldKey means there is no older key.
     * @param json The JSON object.
     * @param key The key of the SysML v2 API.
     * @param oldKey The key that earlier library versions used.
     */
    inline const nlohmann::json* findWithFallback(const nlohmann::json& json, const std::string& key, const std::string& oldKey = "") {
        const auto found = json.find(key);
        if (found != json.end())
            return &*found;
        if (oldKey.empty())
            return nullptr;
        const auto old = json.find(oldKey);
        if (old != json.end()) {
            warnDeprecated("JSON field \"" + oldKey + "\"", "\"" + key + "\"");
            return &*old;
        }
        return nullptr;
    }

    /**
     * The value of a string property. A missing key or null gives an empty string.
     * @param oldKey Optional key of an older library version that is read if key is missing (warns once).
     * @throws std::invalid_argument If the value is neither a string nor null.
     */
    inline std::string readOptionalString(const nlohmann::json& json, const std::string& key, const std::string& oldKey = "") {
        const auto* found = findWithFallback(json, key, oldKey);
        if (found == nullptr || found->is_null())
            return std::string();
        if (!found->is_string())
            throw std::invalid_argument("'" + key + "' must be a string or null");
        return found->get<std::string>();
    }

    /**
     * A string list. A missing key or null gives an empty list, a single string gives one element.
     * @throws std::invalid_argument If the value contains something else than strings.
     */
    inline std::vector<std::string> readStringList(const nlohmann::json& json, const std::string& key, const std::string& oldKey = "") {
        std::vector<std::string> result;
        const auto* found = findWithFallback(json, key, oldKey);
        if (found == nullptr || found->is_null())
            return result;
        if (found->is_string()) {
            result.push_back(found->get<std::string>());
            return result;
        }
        if (!found->is_array())
            throw std::invalid_argument("'" + key + "' must be a string, an array of strings or null");
        for (const auto& entry : *found) {
            if (!entry.is_string())
                throw std::invalid_argument("'" + key + "' must contain only strings");
            result.push_back(entry.get<std::string>());
        }
        return result;
    }

    /**
     * An optional boolean. A missing key or null gives nullopt.
     * @throws std::invalid_argument If the value is neither a boolean nor null.
     */
    inline std::optional<bool> readOptionalBool(const nlohmann::json& json, const std::string& key, const std::string& oldKey = "") {
        const auto* found = findWithFallback(json, key, oldKey);
        if (found == nullptr || found->is_null())
            return std::nullopt;
        if (!found->is_boolean())
            throw std::invalid_argument("'" + key + "' must be a boolean or null");
        return found->get<bool>();
    }

    /**
     * The id of a reference object {"@id": "<uuid>"}; nullopt for null.
     * @throws std::invalid_argument If the value is no reference object or the id is no valid UUID.
     */
    inline std::optional<boost::uuids::uuid> referenceId(const nlohmann::json& value, const std::string& key) {
        if (value.is_null())
            return std::nullopt;
        if (!value.is_object() || !value.contains(JSON_ID_ENTITY) || !value[JSON_ID_ENTITY].is_string())
            throw std::invalid_argument("'" + key + "' must be a reference {\"@id\": ...} or null");
        try {
            return boost::uuids::string_generator()(value[JSON_ID_ENTITY].get<std::string>());
        } catch (const std::exception&) {
            throw std::invalid_argument("'" + key + "' contains an invalid UUID");
        }
    }

    /**
     * The "@id" of an object. A missing "@id" or null gives nullopt (requests have no id).
     * @throws std::invalid_argument If "@id" is not a valid UUID string.
     */
    inline std::optional<boost::uuids::uuid> readOptionalId(const nlohmann::json& json) {
        const auto found = json.find(JSON_ID_ENTITY);
        if (found == json.end() || found->is_null())
            return std::nullopt;
        if (!found->is_string())
            throw std::invalid_argument("'@id' must be a string");
        try {
            return boost::uuids::string_generator()(found->get<std::string>());
        } catch (const std::exception&) {
            throw std::invalid_argument("'@id' is no valid UUID");
        }
    }

    /**
     * The required "@id" of an object.
     * @throws std::invalid_argument If "@id" is missing, null or no valid UUID.
     */
    inline boost::uuids::uuid readId(const nlohmann::json& json) {
        const auto id = readOptionalId(json);
        if (!id.has_value())
            throw std::invalid_argument("'@id' is missing");
        return *id;
    }

    /**
     * A single-valued reference. A missing key or null gives nullopt.
     * @param oldKey Optional key of an older library version that is read if key is missing (warns once).
     */
    inline std::optional<boost::uuids::uuid> readReference(const nlohmann::json& json, const std::string& key, const std::string& oldKey = "") {
        const auto* found = findWithFallback(json, key, oldKey);
        if (found == nullptr)
            return std::nullopt;
        return referenceId(*found, key);
    }

    /**
     * A many-valued reference. Accepts an array, a single reference object or null (and a missing key) under the key or the
     * optional old key. Null entries inside an array are skipped.
     */
    inline std::vector<boost::uuids::uuid> readReferences(const nlohmann::json& json, const std::string& key, const std::string& oldKey = "") {
        std::vector<boost::uuids::uuid> ids;
        const auto* found = findWithFallback(json, key, oldKey);
        if (found == nullptr || found->is_null())
            return ids;
        if (found->is_array()) {
            for (const auto& entry : *found) {
                if (auto id = referenceId(entry, key))
                    ids.push_back(*id);
            }
        } else if (auto id = referenceId(*found, key)) {
            ids.push_back(*id);
        }
        return ids;
    }

    /**
     * The JSON of a reference: {"@id": "<uuid>"}, or null for nullopt and the nil UUID.
     */
    inline nlohmann::json referenceToJson(const std::optional<boost::uuids::uuid>& id) {
        if (!id.has_value() || id->is_nil())
            return nullptr;
        nlohmann::json json = nlohmann::json::object();
        json[JSON_ID_ENTITY] = boost::uuids::to_string(*id);
        return json;
    }

    /**
     * The JSON text of a reference object {"@id": "<uuid>"} (also for the nil UUID). Used to create an entity that only
     * knows its id from a read reference.
     */
    inline std::string referenceObjectText(const boost::uuids::uuid& id) {
        nlohmann::json json = nlohmann::json::object();
        json[JSON_ID_ENTITY] = boost::uuids::to_string(id);
        return json.dump();
    }

    /**
     * Writes a single-valued reference (null if there is none).
     */
    inline void writeReference(nlohmann::json& target, const std::string& key, const std::optional<boost::uuids::uuid>& id) {
        target[key] = referenceToJson(id);
    }

    /**
     * Writes a many-valued reference as an array of {"@id": ...}.
     */
    inline void writeReferences(nlohmann::json& target, const std::string& key, const std::vector<boost::uuids::uuid>& ids) {
        nlohmann::json array = nlohmann::json::array();
        for (const auto& id : ids)
            array.push_back(referenceToJson(id));
        target[key] = array;
    }

    /**
     * A required timestamp (ISO 8601, with or without zone designator).
     * @param oldKey Optional key of an older library version that is read if key is missing (warns once).
     * @throws std::invalid_argument If the key is missing, null or no valid timestamp.
     */
    inline std::chrono::system_clock::time_point readTimestamp(const nlohmann::json& json, const std::string& key, const std::string& oldKey = "") {
        const auto* found = findWithFallback(json, key, oldKey);
        if (found == nullptr || !found->is_string())
            throw std::invalid_argument("'" + key + "' must be a timestamp string");
        try {
            return Utilities::fromIso8601(found->get<std::string>());
        } catch (const std::exception&) {
            throw std::invalid_argument("'" + key + "' is no valid timestamp");
        }
    }

    /**
     * An optional timestamp. A missing key or null gives nullopt.
     */
    inline std::optional<std::chrono::system_clock::time_point> readOptionalTimestamp(const nlohmann::json& json,
                                                                                     const std::string& key,
                                                                                     const std::string& oldKey = "") {
        const auto* found = findWithFallback(json, key, oldKey);
        if (found == nullptr || found->is_null())
            return std::nullopt;
        return readTimestamp(json, key, oldKey);
    }

    /**
     * Writes a timestamp (ISO 8601 with "Z") or omits the key if there is none.
     */
    inline void writeOptionalTimestamp(nlohmann::json& target, const std::string& key,
                                       const std::optional<std::chrono::system_clock::time_point>& time) {
        if (time.has_value())
            target[key] = Utilities::toIso8601(*time);
    }
}
