//
// Created by Moritz Herzog on 25.03.25.
//

#ifndef SYSMLV2_FEATURE_H
#define SYSMLV2_FEATURE_H

#include <optional>

#include <core/types/Type.h>

#include "FeatureDirectionKind.h"

namespace KerML::Entities {
    class TypeFeaturing;
    class Subsetting;
    class Redefintion;


	/**
	 * @class Feature
	 * @version 1.0 Beta 4
	 * @brief Describes the Feature class according to the Standard.
	 */
	class Feature : public Type {
    public:
        Feature();
        ~Feature() override = default;

        void setIsUnique(bool isUnique);
        bool isUnique();

        void setIsOrdered(bool isOrdered);
        bool isOrdered();

        void setIsComposite(bool isComposite);
        bool isComposite();

        void setIsEnd(bool isEnd);
        bool isEnd();

        void setIsDerived(bool isDerived);
        bool isDerived();

        void setIsPortion(bool isPortion);
        bool isPortion();
        
        void setIsVariable(bool isVariable);
        bool isVariable();

        void setIsConstant(bool isConstant);
        bool isConstant();

        void setDirection(FeatureDirectionKind direction);
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

        std::optional<Feature> namingFeature();
        std::vector<std::shared_ptr<Type>> supertypes(bool excludeImplied) override;
        bool redefinedFeature(std::shared_ptr<Feature> redefinedFeature);
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


    private:
        bool IsUnique;
        bool IsOrdered;
        bool IsComposite;
        bool IsEnd;
        bool IsDerived;
        bool IsPortion;
        bool IsVariable;
        bool IsConstant;

        std::optional<FeatureDirectionKind> Direction;

        std::vector<std::shared_ptr<Type>> _Type;
        std::vector<std::shared_ptr<Type>> FeaturingType;

        std::vector<std::shared_ptr<TypeFeaturing>> _TypeFeaturing;
        std::vector<std::shared_ptr<TypeFeaturing>> OwnedTypeFeaturing;
    };
}

#endif //SYSMLV2_FEATURE_H
