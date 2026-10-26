//
// Created by Moritz Herzog on 25.03.25.
//

#pragma once

#include <kerml/root/elements/Relationship.h>

namespace KerML::Entities {
    class Type;

    /**
     * @class Unioning
     * @version 1.0 Beta 4
     * 
     */
    class KERML_EXPORT Unioning : public Relationship {
        friend struct ::KerML::Entities::ElementDisposer;
    public:
        Unioning() = delete;

        Unioning(std::shared_ptr<Type> typeUnioned, std::shared_ptr<Type> unioningType);
        ~Unioning() override = default;

        std::shared_ptr<Type> typeUnioned();
        void setTypeUnioned(std::shared_ptr<Type> typeUnioned);

        std::shared_ptr<Type> unioningType();
        void setUnioningType(std::shared_ptr<Type> unioningType);

    private:
        std::shared_ptr<Type> TypeUnionioned;
        std::shared_ptr<Type> UnioningType;

    // BEGIN GENERATED JSON (kerml/tools/generate_json.py): do not edit, run the script instead.
    public:
        /**
         * Creates a Unioning either from its JSON representation (if the string starts with '{') or with the given declared name.
         * Reading JSON only stores the ids of the referenced elements, see Element::resolveJsonReferences(). The type of the object stays "Unioning".
         * @param nameOrJson The JSON representation of the Unioning, or its declared name.
         */
        explicit Unioning(const std::string& nameOrJson);

        /**
         * Serializes the Unioning to JSON: all properties of the metaclass (stored and derived ones). References to other elements are
         * only written as identities ({"@id": "<uuid>"}), never recursively.
         * @return The JSON representation of the Unioning.
         */
        std::string serializeToJson() override;

        /**
         * Resolves the references that were read from JSON to the elements (see Element::resolveJsonReferences()), for the properties
         * of Unioning and of its base classes.
         * @param lookup Returns the element of an element id, or an empty pointer if it is not known.
         */
        void resolveJsonReferences(const std::function<std::shared_ptr<Element>(const boost::uuids::uuid&)>& lookup) override;

    protected:
        /**
         * Populates the Unioning from its JSON representation; the stored properties of Unioning and of its base classes are read,
         * computed derived properties are ignored, the derived references that the model keeps as collections are read like the stored ones,
         * and references are only stored as ids.
         * @param jsonString The JSON representation of the Unioning.
         */
        void deserializeAndPopulate(const std::string& jsonString) override;
    // END GENERATED JSON
    };
}

