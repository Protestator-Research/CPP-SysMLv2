//
// Created by Moritz Herzog on 25.03.25.
//

#pragma once

#include <kerml/core/features/FeatureMembership.h>

namespace KerML::Entities {
    class KERML_EXPORT EndFeatureMembership : public FeatureMembership {
    public:
        EndFeatureMembership() = delete;
        EndFeatureMembership(std::shared_ptr<Feature> ownedMemberFeature, std::shared_ptr<Type> owningType,  std::vector<std::shared_ptr<Type>> type);
        ~EndFeatureMembership() override = default;

        bool isEnd();

    // BEGIN GENERATED JSON (kerml/tools/generate_json.py): do not edit, run the script instead.
    public:
        /**
         * Creates a EndFeatureMembership either from its JSON representation (if the string starts with '{') or with the given declared name.
         * Reading JSON only stores the ids of the referenced elements, see Element::resolveJsonReferences(). The type of the object stays "EndFeatureMembership".
         * @param nameOrJson The JSON representation of the EndFeatureMembership, or its declared name.
         */
        explicit EndFeatureMembership(const std::string& nameOrJson);

        /**
         * Serializes the EndFeatureMembership to JSON: all properties of the metaclass (stored and derived ones). References to other elements are
         * only written as identities ({"@id": "<uuid>"}), never recursively.
         * @return The JSON representation of the EndFeatureMembership.
         */
        std::string serializeToJson() override;

        /**
         * Resolves the references that were read from JSON to the elements (see Element::resolveJsonReferences()), for the properties
         * of EndFeatureMembership and of its base classes.
         * @param lookup Returns the element of an element id, or an empty pointer if it is not known.
         */
        void resolveJsonReferences(const std::function<std::shared_ptr<Element>(const boost::uuids::uuid&)>& lookup) override;

    protected:
        /**
         * Populates the EndFeatureMembership from its JSON representation; the stored properties of EndFeatureMembership and of its base classes are read,
         * computed derived properties are ignored, the derived references that the model keeps as collections are read like the stored ones,
         * and references are only stored as ids.
         * @param jsonString The JSON representation of the EndFeatureMembership.
         */
        void deserializeAndPopulate(const std::string& jsonString) override;
    // END GENERATED JSON
    };
}
