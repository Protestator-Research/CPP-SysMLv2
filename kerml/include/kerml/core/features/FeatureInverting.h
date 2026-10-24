//
// Created by Moritz Herzog on 25.03.25.
//

#pragma once

#include <kerml/root/elements/Relationship.h>
#include <kerml/kerml_global.h>

namespace KerML::Entities {
    class Feature;
}

namespace KerML::Entities {
    /**
     * @class FeatureInverting
     * @version 1.0 Beta 4
     * @author Moritz Herzog
     * @brief Representation of the FeatureInverting of the KerML standard.
     *
     */
    class KERML_EXPORT FeatureInverting : public Relationship{
        friend struct ::KerML::Entities::ElementDisposer;
    public:
        /**
         *
         */
        FeatureInverting() = delete;
        FeatureInverting(std::shared_ptr<Feature> featureInverted,std::shared_ptr<Feature> invertingFeature, boost::uuids::uuid elementID = boost::uuids::random_generator()(), std::shared_ptr<Element> owner = nullptr);
        ~FeatureInverting() override = default;

        void setFeatureInverted(std::shared_ptr<Feature> featureInverting);
        [[nodiscard]] std::shared_ptr<Feature> featureInverted() const;

        void setInvertingFeature(std::shared_ptr<Feature> invertingFeature);
        [[nodiscard]] std::shared_ptr<Feature> invertingFeature() const;

    public:
        void setOwningFeature(std::shared_ptr<Feature> owningFeature);
        [[nodiscard]] std::shared_ptr<Feature> owningFeature() const;
    private:
        std::shared_ptr<Feature> FeatureInverted;
        std::shared_ptr<Feature> InvertingFeature;
        std::shared_ptr<Feature> OwningFeature;

    // BEGIN GENERATED JSON (kerml/tools/generate_json.py): do not edit, run the script instead.
    public:
        /**
         * Creates a FeatureInverting either from its JSON representation (if the string starts with '{') or with the given declared name.
         * Reading JSON only stores the ids of the referenced elements, see Element::resolveJsonReferences(). The type of the object stays "FeatureInverting".
         * @param nameOrJson The JSON representation of the FeatureInverting, or its declared name.
         */
        explicit FeatureInverting(const std::string& nameOrJson);

        /**
         * Serializes the FeatureInverting to JSON: all properties of the metaclass (stored and derived ones). References to other elements are
         * only written as identities ({"@id": "<uuid>"}), never recursively.
         * @return The JSON representation of the FeatureInverting.
         */
        std::string serializeToJson() override;

        /**
         * Resolves the references that were read from JSON to the elements (see Element::resolveJsonReferences()), for the properties
         * of FeatureInverting and of its base classes.
         * @param lookup Returns the element of an element id, or an empty pointer if it is not known.
         */
        void resolveJsonReferences(const std::function<std::shared_ptr<Element>(const boost::uuids::uuid&)>& lookup) override;

    protected:
        /**
         * Populates the FeatureInverting from its JSON representation; the stored properties of FeatureInverting and of its base classes are read,
         * computed derived properties are ignored, the derived references that the model keeps as collections are read like the stored ones,
         * and references are only stored as ids.
         * @param jsonString The JSON representation of the FeatureInverting.
         */
        void deserializeAndPopulate(const std::string& jsonString) override;
    // END GENERATED JSON
    };
}