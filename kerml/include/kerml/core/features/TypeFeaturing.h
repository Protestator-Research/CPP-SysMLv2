//
// Created by Moritz Herzog on 25.03.25.
//
#pragma once

#include <kerml/core/features/Featuring.h>
#include <kerml/kerml_global.h>

namespace KerML::Entities {
    class Feature;
    class Type;

    /**
     * Defines the Typefeatureing
     * @version 1.0 SysML v2 Release March 2026
     * @author Moritz Herzog <herzogm@rptu.de>
     * @date 02.06.2026
     */
    class KERML_EXPORT TypeFeaturing : public Relationship {
        friend struct ::KerML::Entities::ElementDisposer;
    public:
        TypeFeaturing() = delete;
        TypeFeaturing(const std::shared_ptr<Type>& typeFeaturingOfType, const std::shared_ptr<Feature>& featureOfType, const std::shared_ptr<Feature>& owningFeatureOfType = nullptr);
        ~TypeFeaturing() = default;

        void setFeaturingType(const std::shared_ptr<Type>& typeFeaturingOfType);
        std::shared_ptr<Type> featuringType() const;

        void setFeatureOfType(const std::shared_ptr<Feature>& featureOfType);
        std::shared_ptr<Feature> featureOfType() const;

    public:
        void setOwningFeatureOfType(const std::shared_ptr<Feature>& owningFeatureOfType);
        std::shared_ptr<Feature> owningFeatureOfType();


    private:
        std::shared_ptr<Type> TypeFeaturingOfType;
        std::shared_ptr<Feature> FeatureOfType;
        std::shared_ptr<Feature> OwningFeatureOfType;

    // BEGIN GENERATED JSON (kerml/tools/generate_json.py): do not edit, run the script instead.
    public:
        /**
         * Creates a TypeFeaturing either from its JSON representation (if the string starts with '{') or with the given declared name.
         * Reading JSON only stores the ids of the referenced elements, see Element::resolveJsonReferences(). The type of the object stays "TypeFeaturing".
         * @param nameOrJson The JSON representation of the TypeFeaturing, or its declared name.
         */
        explicit TypeFeaturing(const std::string& nameOrJson);

        /**
         * Serializes the TypeFeaturing to JSON: all properties of the metaclass (stored and derived ones). References to other elements are
         * only written as identities ({"@id": "<uuid>"}), never recursively.
         * @return The JSON representation of the TypeFeaturing.
         */
        std::string serializeToJson() override;

        /**
         * Resolves the references that were read from JSON to the elements (see Element::resolveJsonReferences()), for the properties
         * of TypeFeaturing and of its base classes.
         * @param lookup Returns the element of an element id, or an empty pointer if it is not known.
         */
        void resolveJsonReferences(const std::function<std::shared_ptr<Element>(const boost::uuids::uuid&)>& lookup) override;

    protected:
        /**
         * Populates the TypeFeaturing from its JSON representation; the stored properties of TypeFeaturing and of its base classes are read,
         * computed derived properties are ignored, the derived references that the model keeps as collections are read like the stored ones,
         * and references are only stored as ids.
         * @param jsonString The JSON representation of the TypeFeaturing.
         */
        void deserializeAndPopulate(const std::string& jsonString) override;
    // END GENERATED JSON
    };
}
