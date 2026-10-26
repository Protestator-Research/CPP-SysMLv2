//
// Created by Moritz Herzog on 25.03.25.
//

#pragma once

#include <kerml/core/types/Specialization.h>

namespace KerML::Entities {
    class Feature;

    /**
     * @class Subsetting
     * @version 1.0 Beta 4
     * @author Moritz Herzog <herzogm@rptu.de>
     * @brief
     */
    class KERML_EXPORT Subsetting : public Specialization{
        friend struct ::KerML::Entities::ElementDisposer;
    public:
        Subsetting(std::shared_ptr<Feature> subsettedFeature, std::shared_ptr<Feature> subsettingFeature);
        Subsetting() = delete;
        ~Subsetting() override = default;

        std::shared_ptr<Feature> subsettedFeature() const;
        void setSubsettedFeature(std::shared_ptr<Feature> subsetted);

        std::shared_ptr<Feature> subsettingFeature() const;
        void setSubsettingFeature(std::shared_ptr<Feature> subsettingFeature);


    public:
        std::shared_ptr<Feature> owningFeature() const;
        void setOwningFeature(std::shared_ptr<Feature> owningFeature);

    protected:
        /**
         * Marks the constructor that creates an empty Subsetting without populating it. It is used by the JSON constructors of the
         * derived classes (Redefinition, ReferenceSubsetting, CrossSubsetting), because they populate the complete object themselves.
         */
        struct JsonTag {};

        /**
         * Creates an empty Subsetting, because a Subsetting can not be created without features otherwise.
         */
        explicit Subsetting(JsonTag);

    private:
        std::shared_ptr<Feature> SubsettedFeature;
        std::shared_ptr<Feature> SubsettingFeature;
        std::shared_ptr<Feature> OwningFeature;


    // BEGIN GENERATED JSON (kerml/tools/generate_json.py): do not edit, run the script instead.
    public:
        /**
         * Creates a Subsetting either from its JSON representation (if the string starts with '{') or with the given declared name.
         * Reading JSON only stores the ids of the referenced elements, see Element::resolveJsonReferences(). The type of the object stays "Subsetting".
         * @param nameOrJson The JSON representation of the Subsetting, or its declared name.
         */
        explicit Subsetting(const std::string& nameOrJson);

        /**
         * Serializes the Subsetting to JSON: all properties of the metaclass (stored and derived ones). References to other elements are
         * only written as identities ({"@id": "<uuid>"}), never recursively.
         * @return The JSON representation of the Subsetting.
         */
        std::string serializeToJson() override;

        /**
         * Resolves the references that were read from JSON to the elements (see Element::resolveJsonReferences()), for the properties
         * of Subsetting and of its base classes.
         * @param lookup Returns the element of an element id, or an empty pointer if it is not known.
         */
        void resolveJsonReferences(const std::function<std::shared_ptr<Element>(const boost::uuids::uuid&)>& lookup) override;

    protected:
        /**
         * Populates the Subsetting from its JSON representation; the stored properties of Subsetting and of its base classes are read,
         * computed derived properties are ignored, the derived references that the model keeps as collections are read like the stored ones,
         * and references are only stored as ids.
         * @param jsonString The JSON representation of the Subsetting.
         */
        void deserializeAndPopulate(const std::string& jsonString) override;
    // END GENERATED JSON
    };
}
