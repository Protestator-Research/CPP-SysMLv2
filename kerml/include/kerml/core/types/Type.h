//
// Created by Moritz Herzog on 25.03.25.
//
#pragma once
#include <kerml/model/Forward.h>

#include <kerml/root/namespaces/Namespace.h>
#include <kerml/core/features/FeatureDirectionKind.h>
#include <kerml/kerml_global.h>

namespace KerML::Entities {
    class Membership;
    class Feature;
    class Multiplicity;
    class FeatureMembership;
    class Conjugation;
    class Differencing;
    class Disjoining;
    class Intersecting;
    class Specialization;
    class Unioning;
}

namespace KerML::Entities {
    /**
     * @class Type
     * @author Moritz Herzog
     * @version 1.0 Beta 3
     * @brief Represents the Type Class according to the SysMLv2 Standard.
     */
    class KERML_EXPORT Type : public Namespace{
        friend struct ::KerML::Entities::ElementDisposer;
    public:
	    /**
	     * 
	     * @param elementID 
	     * @param owner 
	     */
	    explicit Type(boost::uuids::uuid elementID = boost::uuids::random_generator()(), std::shared_ptr<Element> owner = nullptr);
        /**
         * Constructor to allow
         * @param typeName
         * @param elementID
         * @param owner
         * If the string is a JSON object (it starts with '{') it is the JSON representation of the element, see serializeToJson(); otherwise it is the declared name.
         */
        explicit Type(std::string typeName, boost::uuids::uuid elementID = boost::uuids::random_generator()(), std::shared_ptr<Element> owner = nullptr);
        /**
         * Destructor
         */
        ~Type() override = default;

        /**
         *
         * @param excluded
         * @param isRecursive
         * @param includeAll
         * @return
         */
        [[nodiscard]] std::vector<std::shared_ptr<Membership>> visibleMemberships(std::vector<std::shared_ptr<Namespace>> excluded, bool isRecursive, bool includeAll) override;
        /**
         *
         * @param excludedNamespace
         * @param excludedTypes
         * @param excludeImplied
         * @return
         */
        [[nodiscard]] std::vector<std::shared_ptr<Membership>> inheritedMemberships(std::vector<std::shared_ptr<Namespace>> excludedNamespace, std::vector<std::shared_ptr<Type>> excludedTypes, bool excludeImplied);
        [[nodiscard]] std::vector<std::shared_ptr<Membership>> inheritableMemberships(std::vector<std::shared_ptr<Namespace>> excludedNamespace, std::vector<std::shared_ptr<Type>> excludedTypes, bool excludeImplied);
        [[nodiscard]] std::vector<std::shared_ptr<Membership>> nonPrivateMemberships(std::vector<std::shared_ptr<Namespace>> excludedNamespace, std::vector<std::shared_ptr<Type>> excludedTypes, bool excludeImplied);
        [[nodiscard]] std::vector<std::shared_ptr<Membership>> removeRedefinedFeature(std::vector<std::shared_ptr<Membership>> memberships);
        [[nodiscard]] std::vector<std::shared_ptr<Feature>> allRedefinedFeaturesOf(std::shared_ptr<Membership> membership);

        FeatureDirectionKind directionOf(std::shared_ptr<Feature> feature);
        FeatureDirectionKind directionOfExcluding(std::shared_ptr<Feature> feature, std::vector<std::shared_ptr<Type>> excluded);

        [[nodiscard]] virtual std::vector<std::shared_ptr<Type>> supertypes(bool excludeImplied);
        [[nodiscard]] std::vector<std::shared_ptr<Type>> allSupertypes();

        bool specializes(std::shared_ptr<Type> supertype);
        bool specializesFromLibrary(std::string libraryTypeName);
        virtual void isCompatibleWith(std::shared_ptr<Type> otherType);

        [[nodiscard]] std::vector<std::shared_ptr<Multiplicity>> multiplicities();

        bool isAbstract();
        void setAbstract(bool isAbstract);

        bool isSufficient();
        void setIsSufficient(bool isSufficient);

        void setIsConjugated(bool isConjugated);
        bool isConjugated();

        [[nodiscard]] std::vector<std::shared_ptr<Type>> differencingType() const;
        void setDifferencingType(std::vector<std::shared_ptr<Type>> differencingType);
        void appendDifferencingType(std::shared_ptr<Type> differencingType);
        void appendDifferencingType(std::vector<std::shared_ptr<Type>> differencingType);

        [[nodiscard]] std::vector<std::shared_ptr<Feature>> directedFeature() const;
        void setDirectedFeature(std::vector<std::shared_ptr<Feature>> directedFeature);
        void appendDirectedFeature(std::shared_ptr<Feature> directedFeature);
        void appendDirectedFeature(std::vector<std::shared_ptr<Feature>> directedFeature);

        [[nodiscard]] std::vector<std::shared_ptr<Feature>> endFeature() const;
        void setEndFeatures(std::vector<std::shared_ptr<Feature>> endFeatures);
        void appendEndFeatures(std::shared_ptr<Feature> endFeature);
        void appendEndFeatures(std::vector<std::shared_ptr<Feature>> endFeatures);

        [[nodiscard]] std::vector<std::shared_ptr<Feature>> features() const;
        void setFeatures(std::vector<std::shared_ptr<Feature>> features);
        void appendFeatures(std::shared_ptr<Feature> feature);
        void appendFeatures(std::vector<std::shared_ptr<Feature>> features);

        [[nodiscard]] std::vector<std::shared_ptr<FeatureMembership>> featureMemberships() const;
        void setFeatureMemberships(std::vector<std::shared_ptr<FeatureMembership>> featureMemberships);
        void appendFeatureMemberships(std::shared_ptr<FeatureMembership> featureMembership);
        void appendFeatureMemberships(std::vector<std::shared_ptr<FeatureMembership>> featureMemberships);

        [[nodiscard]] std::vector<std::shared_ptr<Feature>> inheritedFeature() const;
        void setInheritedFeature(std::vector<std::shared_ptr<Feature>> inheritedFeature);
        void appendInheritedFeature(std::shared_ptr<Feature> inheritedFeature);
        void appendInheritedFeature(std::vector<std::shared_ptr<Feature>> inheritedFeature);

        [[nodiscard]] std::vector<std::shared_ptr<Membership>> inheritedMemberships() const;
        void setInheritedMembership(std::vector<std::shared_ptr<Membership>> inheritedMembership);
        void appendInheritedMembership(std::shared_ptr<Membership> inheritedMembership);
        void appendInheritedMembership(std::vector<std::shared_ptr<Membership>> inheritedMembership);

        [[nodiscard]] std::vector<std::shared_ptr<Feature>> input() const;
        void setInput(std::vector<std::shared_ptr<Feature>> input);
        void appendInput(std::shared_ptr<Feature> input);
        void appendInput(std::vector<std::shared_ptr<Feature>> input);

        [[nodiscard]] std::vector<std::shared_ptr<Type>> intersectingType() const;
        void setIntersectingType(std::vector<std::shared_ptr<Type>> intersectingType);
        void appendIntersectingType(std::shared_ptr<Type> intersectingType);
        void appendIntersectingType(std::vector<std::shared_ptr<Type>> intersectingType);

        std::optional<std::shared_ptr<Multiplicity>> multiplicity();
        void setMultiplicity(std::shared_ptr<Multiplicity> multiplicity);

        [[nodiscard]] std::vector<std::shared_ptr<Feature>> output() const;
        void setOutput(std::vector<std::shared_ptr<Feature>> output);
        void appendOutput(std::shared_ptr<Feature> output);
        void appendOutput(std::vector<std::shared_ptr<Feature>> output);

        std::optional<std::shared_ptr<Conjugation>> conjugation();
        void setConjugation(std::shared_ptr<Conjugation> conjugation);

        [[nodiscard]] std::vector<std::shared_ptr<Differencing>> ownedDifferencing() const;
        void setOwnedDifferencing(std::vector<std::shared_ptr<Differencing>> ownedDifferencing);
        void appendOwnedDifferencing(std::shared_ptr<Differencing> ownedDifferencing);
        void appendOwnedDifferencing(std::vector<std::shared_ptr<Differencing>> ownedDifferencing);

        [[nodiscard]] std::vector<std::shared_ptr<Disjoining>> ownedDisjoining() const;
        void setOwnedDisjoining(std::vector<std::shared_ptr<Disjoining>> ownedDisjoining);
        void appendOwnedDisjoining(std::shared_ptr<Disjoining> ownedDisjoining);
        void appendOwnedDisjoining(std::vector<std::shared_ptr<Disjoining>> ownedDisjoining);

        [[nodiscard]] std::vector<std::shared_ptr<Feature>> ownedEndFeature() const;
        void setOwnedEndFeature(std::vector<std::shared_ptr<Feature>> ownedEndFeature);
        void appendOwnedEndFeature(std::shared_ptr<Feature> ownedEndFeature);
        void appendOwnedEndFeature(std::vector<std::shared_ptr<Feature>> ownedEndFeature);

        [[nodiscard]] std::vector<std::shared_ptr<Feature>> ownedFeature() const;
        void setOwnedFeature(std::vector<std::shared_ptr<Feature>> ownedFeature);
        void appendOwnedFeature(std::shared_ptr<Feature> ownedFeature);
        void appendOwnedFeature(std::vector<std::shared_ptr<Feature>> ownedFeature);

        [[nodiscard]] std::vector<std::shared_ptr<FeatureMembership>> ownedFeatureMembership() const;
        void setOwnedFeatureMembership(std::vector<std::shared_ptr<FeatureMembership>> ownedFeatureMembership);
        void appendOwnedFeatureMembership(std::shared_ptr<FeatureMembership> ownedFeatureMembership);
        void appendOwnedFeatureMembership(std::vector<std::shared_ptr<FeatureMembership>> ownedFeatureMembership);

        [[nodiscard]] std::vector<std::shared_ptr<Intersecting>> ownedIntersecting() const;
        void setOwnedIntersecting(std::vector<std::shared_ptr<Intersecting>> ownedIntersecting);
        void appendOwnedIntersecting(std::shared_ptr<Intersecting> ownedIntersecting);
        void appendOwnedIntersecting(std::vector<std::shared_ptr<Intersecting>> ownedIntersecting);

        [[nodiscard]] std::vector<std::shared_ptr<Specialization>> ownedSpecialization() const;
        void setOwnedSpecialization(std::vector<std::shared_ptr<Specialization>> ownedSpecialization);
        void appendOwnedSpecialization(std::shared_ptr<Specialization> ownedSpecialization);
        void appendOwnedSpecialization(std::vector<std::shared_ptr<Specialization>> ownedSpecialization);

        [[nodiscard]] std::vector<std::shared_ptr<Unioning>> ownedUnioning() const;
        void setOwnedUnioning(std::vector<std::shared_ptr<Unioning>> ownedUnioning);
        void appendOwnedUnioning(std::shared_ptr<Unioning> ownedUnioning);
        void appendOwnedUnioning(std::vector<std::shared_ptr<Unioning>> ownedUnioning);

        [[nodiscard]] std::vector<std::shared_ptr<Type>> unioningType() const;
        void setUnioningType(std::vector<std::shared_ptr<Type>> unioningType);
        void appendUnioningType(std::shared_ptr<Type> unioningType);
        void appendUnioningType(std::vector<std::shared_ptr<Type>> unioningType);

    private:
        bool IsAbstract = false;
        bool IsSufficient = false;
        bool IsConjugated = false;

        std::vector<std::shared_ptr<Type>> DifferencingType;
        std::vector<std::shared_ptr<Feature>> DirectedFeature;
        std::vector<std::shared_ptr<Feature>> EndFeature;
        std::vector<std::shared_ptr<Feature>> Features;
        std::vector<std::shared_ptr<FeatureMembership>> FeatureMemberships;
        std::vector<std::shared_ptr<Feature>> InheritedFeature;
        std::vector<std::shared_ptr<Membership>> InheritedMembership;
        std::vector<std::shared_ptr<Feature>> Input;
        std::vector<std::shared_ptr<Type>> IntersectingType;
        std::shared_ptr<Multiplicity> _Multiplicity;
        std::vector<std::shared_ptr<Feature>> Output;
        std::shared_ptr<Conjugation> OwnedConjugator;
        std::vector<std::shared_ptr<Differencing>> OwnedDifferencing;
        std::vector<std::shared_ptr<Disjoining>> OwnedDisjoining;
        std::vector<std::shared_ptr<Feature>> OwnedEndFeature;
        std::vector<std::shared_ptr<Feature>> OwnedFeature;
        std::vector<std::shared_ptr<FeatureMembership>> OwnedFeatureMembership;
        std::vector<std::shared_ptr<Intersecting>> OwnedIntersecting;
        std::vector<std::shared_ptr<Specialization>> OwnedSpecialization;
        std::vector<std::shared_ptr<Unioning>> OwnedUnioning;
        std::vector<std::shared_ptr<Type>> UnioningType;
    public:
        std::vector<std::shared_ptr<Feature>> feature() const;
        std::vector<std::shared_ptr<FeatureMembership>> featureMembership() const;
        std::vector<std::shared_ptr<Membership>> inheritedMembership() const;
        std::optional<std::shared_ptr<Conjugation>> ownedConjugator() const;

    // BEGIN GENERATED JSON (kerml/tools/generate_json.py): do not edit, run the script instead.
    public:
        /**
         * Serializes the Type to JSON: all properties of the metaclass (stored and derived ones). References to other elements are
         * only written as identities ({"@id": "<uuid>"}), never recursively.
         * @return The JSON representation of the Type.
         */
        std::string serializeToJson() override;

        /**
         * Resolves the references that were read from JSON to the elements (see Element::resolveJsonReferences()), for the properties
         * of Type and of its base classes.
         * @param lookup Returns the element of an element id, or an empty pointer if it is not known.
         */
        void resolveJsonReferences(const std::function<std::shared_ptr<Element>(const boost::uuids::uuid&)>& lookup) override;

    protected:
        /**
         * Populates the Type from its JSON representation; the stored properties of Type and of its base classes are read,
         * computed derived properties are ignored, the derived references that the model keeps as collections are read like the stored ones,
         * and references are only stored as ids.
         * @param jsonString The JSON representation of the Type.
         */
        void deserializeAndPopulate(const std::string& jsonString) override;
    // END GENERATED JSON
    };
} // KerML::Entities
