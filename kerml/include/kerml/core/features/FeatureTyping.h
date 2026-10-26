//
// Created by Moritz Herzog on 25.03.25.
//

#pragma once
#include <kerml/model/Forward.h>

#include <kerml/core/types/Specialization.h>
#include <kerml/kerml_global.h>

namespace KerML::Entities {
    class Type;
    class Feature;

    class KERML_EXPORT FeatureTyping : public Specialization{
        friend struct ::KerML::Entities::ElementDisposer;
    public:
        FeatureTyping();
        FeatureTyping(const std::shared_ptr<KerML::Entities::Type>& type, const std::shared_ptr<KerML::Entities::Feature>& typedFeature = nullptr);

        /**
         * Keeps FeatureTyping(nullptr) unambiguous next to the constructor that takes a name or JSON. As before, a typing needs a type: this
         * throws like the constructor with the null type.
         */
        FeatureTyping(std::nullptr_t);
        ~FeatureTyping() = default;

        std::shared_ptr<KerML::Entities::Feature> typedFeature();
        void setTypedFeature(const std::shared_ptr<KerML::Entities::Feature>& typedFeature);

        std::shared_ptr<KerML::Entities::Type> type();
        void setType(const std::shared_ptr<KerML::Entities::Type>& type);

    private:
        std::shared_ptr<KerML::Entities::Feature> TypedFeature;
        std::shared_ptr<KerML::Entities::Type> Type;
    public:
        std::shared_ptr<Feature> owningFeature() const;
        void setOwningFeature(std::shared_ptr<Feature> value);

    // BEGIN GENERATED JSON (kerml/tools/generate_json.py): do not edit, run the script instead.
    public:
        /**
         * Creates a FeatureTyping either from its JSON representation (if the string starts with '{') or with the given declared name.
         * Reading JSON only stores the ids of the referenced elements, see Element::resolveJsonReferences(). The type of the object stays "FeatureTyping".
         * @param nameOrJson The JSON representation of the FeatureTyping, or its declared name.
         */
        explicit FeatureTyping(const std::string& nameOrJson);

        /**
         * Serializes the FeatureTyping to JSON: all properties of the metaclass (stored and derived ones). References to other elements are
         * only written as identities ({"@id": "<uuid>"}), never recursively.
         * @return The JSON representation of the FeatureTyping.
         */
        std::string serializeToJson() override;

        /**
         * Resolves the references that were read from JSON to the elements (see Element::resolveJsonReferences()), for the properties
         * of FeatureTyping and of its base classes.
         * @param lookup Returns the element of an element id, or an empty pointer if it is not known.
         */
        void resolveJsonReferences(const std::function<std::shared_ptr<Element>(const boost::uuids::uuid&)>& lookup) override;

    protected:
        /**
         * Populates the FeatureTyping from its JSON representation; the stored properties of FeatureTyping and of its base classes are read,
         * computed derived properties are ignored, the derived references that the model keeps as collections are read like the stored ones,
         * and references are only stored as ids.
         * @param jsonString The JSON representation of the FeatureTyping.
         */
        void deserializeAndPopulate(const std::string& jsonString) override;
    // END GENERATED JSON
    };
}