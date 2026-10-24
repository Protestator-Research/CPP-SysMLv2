//
// Created by Moritz Herzog on 25.03.25.
//

#pragma once

#include <kerml/root/elements/Relationship.h>

namespace KerML::Entities {
    class Feature;
}

namespace KerML::Entities {
    class KERML_EXPORT FeatureChaining : public Relationship {
        friend struct ::KerML::Entities::ElementDisposer;
    public:
        FeatureChaining() = delete;
        FeatureChaining(std::shared_ptr<Feature> chainingFeature, std::shared_ptr<Feature> featureChained, boost::uuids::uuid elementID = boost::uuids::random_generator()(), std::shared_ptr<Element> owner = nullptr);
        ~FeatureChaining() override = default;

        void setChainingFeature(std::shared_ptr<Feature> chainingFeature);
        [[nodiscard]] std::shared_ptr<Feature> chainingFeature() const;

    public:
        void setFeatureChained(std::shared_ptr<Feature> featureChained);
        std::shared_ptr<Feature> featureChained() const;

    private:
        std::shared_ptr<Feature> ChainingFeature;
        std::shared_ptr<Feature> FeatureChained;

    // BEGIN GENERATED JSON (kerml/tools/generate_json.py): do not edit, run the script instead.
    public:
        /**
         * Creates a FeatureChaining either from its JSON representation (if the string starts with '{') or with the given declared name.
         * Reading JSON only stores the ids of the referenced elements, see Element::resolveJsonReferences(). The type of the object stays "FeatureChaining".
         * @param nameOrJson The JSON representation of the FeatureChaining, or its declared name.
         */
        explicit FeatureChaining(const std::string& nameOrJson);

        /**
         * Serializes the FeatureChaining to JSON: all properties of the metaclass (stored and derived ones). References to other elements are
         * only written as identities ({"@id": "<uuid>"}), never recursively.
         * @return The JSON representation of the FeatureChaining.
         */
        std::string serializeToJson() override;

        /**
         * Resolves the references that were read from JSON to the elements (see Element::resolveJsonReferences()), for the properties
         * of FeatureChaining and of its base classes.
         * @param lookup Returns the element of an element id, or an empty pointer if it is not known.
         */
        void resolveJsonReferences(const std::function<std::shared_ptr<Element>(const boost::uuids::uuid&)>& lookup) override;

    protected:
        /**
         * Populates the FeatureChaining from its JSON representation; the stored properties of FeatureChaining and of its base classes are read,
         * computed derived properties are ignored, the derived references that the model keeps as collections are read like the stored ones,
         * and references are only stored as ids.
         * @param jsonString The JSON representation of the FeatureChaining.
         */
        void deserializeAndPopulate(const std::string& jsonString) override;
    // END GENERATED JSON
    };
}

