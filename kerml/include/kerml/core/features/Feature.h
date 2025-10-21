//
// Created by Moritz Herzog on 25.03.25.
//

#pragma once

#include <optional>

#include <../types/Type.h>

#include "FeatureDirectionKind.h"

namespace KerML::Entities {
    class TypeFeaturing;
    class Subsetting;
    class Redefinition;
    class ReferenceSubsetting;
    class FeatureChaining;
    class FeatureInverting;
    class FreatureEndMember;
    class FeatureTyping;
    class CrossSubsetting;

	/**
	 * @class Feature
	 * @version 1.0 Beta 4
	 * @author Moritz Herzog <herzogm@rptu.de>
	 * @brief Describes the Feature class according to the Standard.
	 */
	class Feature : public Type, public std::enable_shared_from_this<Feature> {
    public:
		/**
		 * Constuctor
		 */
		Feature();
		/**
		 * Destructor
		 */
		~Feature() override = default;

		/**
		 * Sets the isUnique variable. The variable describes if the values of the feature must have duplicates or not.
		 * @param isUnique True if no duplicates are allowed, False if duplicates are allowed and / or available.
		 */
		void setIsUnique(bool isUnique);
        /**
         * Returns the isUnique is allowed. The variable describes if the values of the feature must have duplicates or not.
         * @return True if no duplicates are allowed, False if duplicates are allowed and / or available.
         */
        bool isUnique();

        /**
         * Sets the isOrdered variable. Defines weather an order exists for the values of this feature or not.
         * @param isOrdered True if an order exists, False if no order is 
         */
        void setIsOrdered(bool isOrdered);
        /**
         * Allows access to the isOrdered variable. This variables defines weather an order exists for the values of this Feature or not.
         * @return True if an order exists, False if no order is
         */
        bool isOrdered();

        /**
         * Sets the isComposite variable. This variables represents if the values of this Feature can be built by other Features.
         * @param isComposite Is true if the values can be built by other Features values, False otherwise.
         */
        void setIsComposite(bool isComposite);
        /**
         * Gives access to the isComposite variable. This variables represents if the values of this Feature can be built by other Features.
         * @return Is true if the values can be built by other Features values, False otherwise.
         */
        bool isComposite();

        /**
         * Sets the isEnd variable. This variable defines if an Feature is an end Feature or not.
         * @param isEnd True if feature is end feature, False if no end feature.
         */
        void setIsEnd(bool isEnd);
        /**
         * Gives access to the isEnd variable. This variable defines if an Feature is an end Feature or not.
         * @return True if feature is end feature, False if no end feature.
         */
        bool isEnd();

        /**
         * Sets the IsDerived variable. This variable defines whether the variables can be computed by the variables of other Features.
         * @param isDerived True if the values can be calculated from other available features, false otherwise.
         */
        void setIsDerived(bool isDerived);
        /**
         * Gives access to the isDerived variable. This variable defines whether the variables can be computed by the variables of other Features.
         * * @return True if the values can be calculated from other available features, false otherwise.
         */
        bool isDerived();

        /**
         * Sets the isPortion variable. This variable defines if the values of this Feature are contained within a instance of this feature.
         * @param isPortion True if the values of this Feature persist in an instance, False otherwise.
         */
        void setIsPortion(bool isPortion);
        /**
         * Gives access to the value of the isPortion Variable. This variable defines if the values of this Feature are contained within a instance of this feature.
         * @return True if the values of this Feature persist in an instance, False otherwise.
         */
        bool isPortion();

        /**
         * Sets the isVariable variable. This variable defines if the values are changing over time.
         * @param isVariable True if the values of this feature might change over time.
         */
        void setIsVariable(bool isVariable);
        /**
         * Gives access to the value of the isVariable. This variable defines if the values are changing over time.
         * @return True if the values of this feature might change over time.
         */
        bool isVariable();

        /**
         * Sets the variable isConstant. This variable defines if the values of this Feature do not change over time.
         * @param isConstant True if the values of this Feature do not change, False otherwise.
         */
        void setIsConstant(bool isConstant);
        /**
         * Gives access to the value of the isConstant variable. This variable defines if the values of this Feature do not change over time.
         * @return True if the values of this Feature do not change, False otherwise.
         */
        bool isConstant();

        /**
         * Allows to set the value of the Direction. The direction indicates how the values of this feature are defined.
         * @param direction Defines how the values of the feature are defines.
         * @see KerML::Entities::FeatureDirectionKind.
         */
        void setDirection(std::optional<FeatureDirectionKind> direction);
        /**
         * Gives access to the value of the Direction. The direction indicates how the values of this feature are defined.
         * @return Defines how the values of the feature are defines.
         * @see KerML::Entities::FeatureDirectionKind.
         */
        std::optional<FeatureDirectionKind> direction();

        void setType(std::vector<std::shared_ptr<Type>> type);
        std::vector<std::shared_ptr<Type>> type() const;
        void appendType(std::vector<std::shared_ptr<Type>> type);
        void appendType(std::shared_ptr<Type> type);

        void setTypeFeaturing(std::vector<std::shared_ptr<TypeFeaturing>> typeFeaturing);

        std::vector<std::shared_ptr<TypeFeaturing>> typeFeaturing() const;

        void appendTypeFeatuing(std::vector<std::shared_ptr<TypeFeaturing>> typeFeaturing);
        void appendTypeFeaturing(std::shared_ptr<TypeFeaturing> typeFeaturing);

        FeatureDirectionKind directionFor(std::shared_ptr<Type> type);
        [[nodiscard]] std::optional<std::string> effectiveShortName() const override;
        [[nodiscard]] std::optional<std::string> effectiveName() const override;

        std::optional<std::shared_ptr<Feature>> namingFeature() const;
        std::vector<std::shared_ptr<Type>> supertypes(bool excludeImplied) override;

        bool redefines(std::shared_ptr<Feature> redefinedFeature);
        bool redefinesFromLibrary(std::string libraryFeatureName);
        bool subsetsChain(std::shared_ptr<Feature> first, std::shared_ptr<Feature> second);

        void isCompatibleWith(std::shared_ptr<Type> otherType) override;
        std::vector<std::shared_ptr<Feature>> typingFeatures();
        std::vector<std::shared_ptr<Type>> asCartesianProduct();
        bool isCartesianProduct();
        bool isOwnedCrossFeature();

        std::optional<std::shared_ptr<Feature>> ownedCrossFeature();
        std::vector<std::shared_ptr<Feature>> allRedefinedFeatures();

        bool isFeaturedWithin(std::optional<std::shared_ptr<Type>>);
        bool canAccess(std::shared_ptr<Feature> feature);
        bool isFeaturingType(std::shared_ptr<Type> type);

    protected:
        void setFeaturingType(std::vector<std::shared_ptr<Type>> featuringType);
        std::vector<std::shared_ptr<Type>> featuringType() const;
        void appendFeaturingType(std::vector<std::shared_ptr<Type>> featuringType);
        void appendFeaturingType(std::shared_ptr<Type> featuringType);

        void setOwnedTypeFeaturing(std::vector<std::shared_ptr<TypeFeaturing>> ownedTypeFeaturing);
        std::vector<std::shared_ptr<TypeFeaturing>> ownedTypeFeaturing() const;
        void appendOwnedTypeFeaturing(std::vector<std::shared_ptr<TypeFeaturing>> ownedTypeFeaturing);
        void appendOwnedTypeFeaturing(std::shared_ptr<TypeFeaturing> ownedTypeFeaturing);

        void setChainingFeature(std::vector<std::shared_ptr<Feature>> chainingFeature);
        std::vector<std::shared_ptr<Feature>> chainingFeature() const;
        void appendChainingFeature(std::vector<std::shared_ptr<Feature>> chainingFeature);
        void appendChainingFeature(std::shared_ptr<Feature> chainingFeature);

        std::optional<std::shared_ptr<Feature>> crossFeature() const;
		void setCrossFeature(std::optional<std::shared_ptr<Feature>> crossFeature);

        std::optional<std::shared_ptr<Type>> endOwningType() const;
        void setEndOwningType(std::optional<std::shared_ptr<Type>> crossFeature);

        std::shared_ptr<Feature> featureTarget();

        std::optional<std::shared_ptr<CrossSubsetting>> ownedCrossSubsetting() const;
        void setOwnedCrossSubsetting(std::optional<std::shared_ptr<CrossSubsetting>> ownedCrossSubsetting);

        void setOwnedFeatureChaining(std::vector<std::shared_ptr<FeatureChaining>> ownedFeatureChaining);
        std::vector<std::shared_ptr<FeatureChaining>> ownedFeatureChaining() const;
        void appendOwnedFeatureChaining(std::vector<std::shared_ptr<FeatureChaining>> ownedFeatureChaining);
        void appendOwnedFeatureChaining(std::shared_ptr<FeatureChaining> ownedFeatureChaining);

        void setOwnedFeatureInverting(std::vector<std::shared_ptr<FeatureInverting>> ownedFeatureInverting);
        std::vector<std::shared_ptr<FeatureInverting>> ownedFeatureInverting() const;
        void appendOwnedFeatureInverting(std::vector<std::shared_ptr<FeatureInverting>> ownedFeaureInverting);
        void appendOwnedFeatureInverting(std::shared_ptr<FeatureInverting> ownedFeatureInverting);

        void setOwnedRedefinition(std::vector<std::shared_ptr<Redefinition>> ownedRedefinition);
        std::vector<std::shared_ptr<Redefinition>> ownedRedefinition() const;
        void appendOwnedRedefinition(std::vector<std::shared_ptr<Redefinition>> ownedRedefinition);
        void appendOwnedRedefinition(std::shared_ptr<Redefinition> ownedRedefinition);

        void setOwnedReferenceSubsetting(std::optional<std::shared_ptr<ReferenceSubsetting>> referenceSubsetting);
        std::optional<std::shared_ptr<ReferenceSubsetting>> ownedReferenceSubsetting() const;

        void setOwendSubsetting(std::vector<std::shared_ptr<Subsetting>> ownedSubsetting);
        std::vector<std::shared_ptr<Subsetting>> ownedSubsetting() const;
        void appendOwnedSubsetting(std::vector<std::shared_ptr<Subsetting>> ownedSubsetting);
        void appendOwnedSubsetting(std::shared_ptr<Subsetting> ownedSubsetting);

        void setOwnedTyping(std::vector<std::shared_ptr<FeatureTyping>> ownedTyping);
        std::vector<std::shared_ptr<FeatureTyping>> ownedTyping() const;
        void appendOwnedTyping(std::vector<std::shared_ptr<FeatureTyping>> ownedTyping);
        void appendOwnedTyping(std::shared_ptr<FeatureTyping> ownedTyping);

        void setOwningFeatureMembership(std::optional<std::shared_ptr<FeatureMembership>> owningMembership);
        std::optional<std::shared_ptr<FeatureMembership>> owningFeatureMembership() const;

        void setOwningType(std::optional<std::shared_ptr<Type>> owningType);
        std::optional<std::shared_ptr<Type>> owningType() const;

    private:
        bool IsUnique;
        bool IsOrdered;
        bool IsComposite;
        bool IsEnd;
        bool IsDerived;
        bool IsPortion;
        bool IsVariable;
        bool IsConstant;
        bool IsCartesianProduct;

        std::optional<FeatureDirectionKind> Direction;

        std::vector<std::shared_ptr<Type>> _Type;
        std::vector<std::shared_ptr<Type>> FeaturingType;

        std::vector<std::shared_ptr<TypeFeaturing>> _TypeFeaturing;
        std::vector<std::shared_ptr<TypeFeaturing>> OwnedTypeFeaturing;

        std::vector<std::shared_ptr<Feature>> ChainingFeature;

        std::shared_ptr<Type> EndOwningType;

        std::shared_ptr<CrossSubsetting> OwnedCrossSubsetting;
        std::vector<std::shared_ptr<FeatureChaining>> OwnedFeatureChaining;
        std::vector<std::shared_ptr<FeatureInverting>> OwnedFeatureInverting;
        std::vector<std::shared_ptr<Redefinition>> OwnedRedefinition;
        std::shared_ptr<ReferenceSubsetting> OwnedReferenceSubsetting;
        std::vector<std::shared_ptr<Subsetting>> OwnedSubsetting;
        std::vector<std::shared_ptr<FeatureTyping>> OwnedTyping;
        std::shared_ptr<FeatureMembership> OwningFeatureMembership;
        std::shared_ptr<Type> OwningType;
        
	};
}
