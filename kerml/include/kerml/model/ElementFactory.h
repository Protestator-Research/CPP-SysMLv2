//
// Created by Moritz Herzog.
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
#include <vector>
//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include <kerml/root/elements/Element.h>
#include <kerml/kerml_global.h>
//---------------------------------------------------------

namespace KerML::Entities {
    /**
     * Creates an element from its JSON representation (as produced by serializeToJson() or by a SysML v2 API server). The
     * "@type" decides which metaclass is created: every concrete KerML metaclass is created by its constructor that takes a
     * JSON string, so the result is an object of that class. For every other type (for example the types of SysML, or "Element" itself)
     * the element is created by Element::fromJson(), which keeps the original JSON.
     *
     * The references to other elements are only stored as ids, see Element::resolveJsonReferences().
     * @param json The JSON representation of the element.
     * @return The created element.
     * @throws std::invalid_argument If the JSON is no object, or "@id" is missing or no valid UUID.
     * @throws nlohmann::json::parse_error If the string is no valid JSON.
     */
    KERML_EXPORT std::shared_ptr<Element> createElementFromJson(const std::string& json);

    /**
     * Creates the elements that belong together (for example the elements of one commit) from their JSON representations, in the same order,
     * and links them: the references are resolved by the element ids among the created elements and the derived properties (owner, ownedElement,
     * the members of the namespaces, ...) are rebuilt, see linkElements(). References to elements that are not among the JSON objects stay
     * unresolved (and are still written by serializeToJson()).
     * @param jsons The JSON representations of the elements.
     * @return The created elements.
     * @throws std::invalid_argument If one JSON is no object, or "@id" is missing or no valid UUID.
     * @throws nlohmann::json::parse_error If one string is no valid JSON.
     */
    KERML_EXPORT std::vector<std::shared_ptr<Element>> createElementsFromJson(const std::vector<std::string>& jsons);
} // KerML::Entities
