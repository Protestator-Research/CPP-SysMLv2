//
// Created by Moritz Herzog on 25.03.25.
//
#pragma once

#include <kerml/root/namespaces/OwningMembership.h>

namespace KerML::Entities {
    class Feature;
    class Type;
}

namespace KerML::Entities {
    /**
     * @class FeatureMembership
     * @version 1.0 Beta 4
     * @author Moritz Herzog <herzogm@rptu.de>
     * @brief Representation of the Feature Membership according to the SysML Standard.
     */
    class KERML_EXPORT FeatureMembership : public OwningMembership {
        friend struct ::KerML::Entities::ElementDisposer;
    public:
    public:
        // Derived metamodel elements may be populated in two phases.
        FeatureMembership();
    public:
        FeatureMembership(std::shared_ptr<Feature> ownedMemberFeature, std::shared_ptr<Type> owningType,  std::vector<std::shared_ptr<Type>> type);
        ~FeatureMembership() override = default;


    public:
        void setOwnedMemberFeature(std::shared_ptr<Feature> ownedMemberFeature);
        [[nodiscard]] std::shared_ptr<Feature> ownedMemberFeature() const;

        void setOwningType(std::shared_ptr<Type> owningType);
        [[nodiscard]] std::shared_ptr<Type> owningType() const;

        void setType(std::vector<std::shared_ptr<Type>> type);
        [[nodiscard]] std::vector<std::shared_ptr<Type>> type() const;
        void appendType(std::vector<std::shared_ptr<Type>> type);
        void appendType(std::shared_ptr<Type> type);

    private:
        std::shared_ptr<Feature> OwnedMemberFeature;
        std::shared_ptr<Type> OwningType;
        std::vector<std::shared_ptr<Type>> _Type;

    // BEGIN GENERATED JSON (kerml/tools/generate_json.py): do not edit, run the script instead.
    public:
        /**
         * Creates a FeatureMembership either from its JSON representation (if the string starts with '{') or with the given declared name.
         * Reading JSON only stores the ids of the referenced elements, see Element::resolveJsonReferences(). The type of the object stays "FeatureMembership".
         * @param nameOrJson The JSON representation of the FeatureMembership, or its declared name.
         */
        explicit FeatureMembership(const std::string& nameOrJson);

        /**
         * Serializes the FeatureMembership to JSON: all properties of the metaclass (stored and derived ones). References to other elements are
         * only written as identities ({"@id": "<uuid>"}), never recursively.
         * @return The JSON representation of the FeatureMembership.
         */
        std::string serializeToJson() override;

        /**
         * Resolves the references that were read from JSON to the elements (see Element::resolveJsonReferences()), for the properties
         * of FeatureMembership and of its base classes.
         * @param lookup Returns the element of an element id, or an empty pointer if it is not known.
         */
        void resolveJsonReferences(const std::function<std::shared_ptr<Element>(const boost::uuids::uuid&)>& lookup) override;

    protected:
        /**
         * Populates the FeatureMembership from its JSON representation; the stored properties of FeatureMembership and of its base classes are read,
         * computed derived properties are ignored, the derived references that the model keeps as collections are read like the stored ones,
         * and references are only stored as ids.
         * @param jsonString The JSON representation of the FeatureMembership.
         */
        void deserializeAndPopulate(const std::string& jsonString) override;
    // END GENERATED JSON
    };
}
