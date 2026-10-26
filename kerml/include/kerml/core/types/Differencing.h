//
// Created by Moritz Herzog on 25.03.25.
//

#pragma once

#include <kerml/root/elements/Relationship.h>

namespace KerML::Entities {
    class Type;

    /**
     * @class Differencing
     * @version 1.0 Beta 4
     */
    class KERML_EXPORT Differencing : public Relationship{
        friend struct ::KerML::Entities::ElementDisposer;
    public:
        Differencing() = delete;
        Differencing(std::shared_ptr<Type> typeDifferenced, std::shared_ptr<Type> differencingType);
        ~Differencing() override = default;

        std::shared_ptr<Type> differencingType();
        void setDifferencingType(std::shared_ptr<Type> differencingType);

    public:
        std::shared_ptr<Type> typeDifferenced();
        void setTypeDifferenced(std::shared_ptr<Type> typeDifferenced);

    private:
        std::shared_ptr<Type> TypeDifferenced;
        std::shared_ptr<Type> DifferencingType;

    // BEGIN GENERATED JSON (kerml/tools/generate_json.py): do not edit, run the script instead.
    public:
        /**
         * Creates a Differencing either from its JSON representation (if the string starts with '{') or with the given declared name.
         * Reading JSON only stores the ids of the referenced elements, see Element::resolveJsonReferences(). The type of the object stays "Differencing".
         * @param nameOrJson The JSON representation of the Differencing, or its declared name.
         */
        explicit Differencing(const std::string& nameOrJson);

        /**
         * Serializes the Differencing to JSON: all properties of the metaclass (stored and derived ones). References to other elements are
         * only written as identities ({"@id": "<uuid>"}), never recursively.
         * @return The JSON representation of the Differencing.
         */
        std::string serializeToJson() override;

        /**
         * Resolves the references that were read from JSON to the elements (see Element::resolveJsonReferences()), for the properties
         * of Differencing and of its base classes.
         * @param lookup Returns the element of an element id, or an empty pointer if it is not known.
         */
        void resolveJsonReferences(const std::function<std::shared_ptr<Element>(const boost::uuids::uuid&)>& lookup) override;

    protected:
        /**
         * Populates the Differencing from its JSON representation; the stored properties of Differencing and of its base classes are read,
         * computed derived properties are ignored, the derived references that the model keeps as collections are read like the stored ones,
         * and references are only stored as ids.
         * @param jsonString The JSON representation of the Differencing.
         */
        void deserializeAndPopulate(const std::string& jsonString) override;
    // END GENERATED JSON
    };
}

