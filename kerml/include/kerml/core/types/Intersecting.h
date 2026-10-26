//
// Created by Moritz Herzog on 25.03.25.
//

#pragma once
#include <kerml/model/Forward.h>

#include <kerml//root/elements/Relationship.h>

namespace KerML::Entities {
    class Type;

    /**
     * @class Intersecting
     * @version 1.0 Beta 4
     */
    class KERML_EXPORT Intersecting : public Relationship{
        friend struct ::KerML::Entities::ElementDisposer;
    public:
        Intersecting() = delete;
        Intersecting(std::shared_ptr<Type> typeIntersecting, std::shared_ptr<Type> intersectingType);
        ~Intersecting() override = default;


        std::shared_ptr<Type> intersectingType();
        void setIntersectingType(std::shared_ptr<Type> intersectingType);

    public:
        std::shared_ptr<Type> typeIntersecting();
        void setTypeIntersecting(std::shared_ptr<Type> typeIntersecting);

    private:
        std::shared_ptr<Type> TypeIntersected;
        std::shared_ptr<Type> IntersectingType;
    public:
        std::shared_ptr<Type> typeIntersected() const;

    // BEGIN GENERATED JSON (kerml/tools/generate_json.py): do not edit, run the script instead.
    public:
        /**
         * Creates a Intersecting either from its JSON representation (if the string starts with '{') or with the given declared name.
         * Reading JSON only stores the ids of the referenced elements, see Element::resolveJsonReferences(). The type of the object stays "Intersecting".
         * @param nameOrJson The JSON representation of the Intersecting, or its declared name.
         */
        explicit Intersecting(const std::string& nameOrJson);

        /**
         * Serializes the Intersecting to JSON: all properties of the metaclass (stored and derived ones). References to other elements are
         * only written as identities ({"@id": "<uuid>"}), never recursively.
         * @return The JSON representation of the Intersecting.
         */
        std::string serializeToJson() override;

        /**
         * Resolves the references that were read from JSON to the elements (see Element::resolveJsonReferences()), for the properties
         * of Intersecting and of its base classes.
         * @param lookup Returns the element of an element id, or an empty pointer if it is not known.
         */
        void resolveJsonReferences(const std::function<std::shared_ptr<Element>(const boost::uuids::uuid&)>& lookup) override;

    protected:
        /**
         * Populates the Intersecting from its JSON representation; the stored properties of Intersecting and of its base classes are read,
         * computed derived properties are ignored, the derived references that the model keeps as collections are read like the stored ones,
         * and references are only stored as ids.
         * @param jsonString The JSON representation of the Intersecting.
         */
        void deserializeAndPopulate(const std::string& jsonString) override;
    // END GENERATED JSON
    };
}
