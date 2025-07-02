//
// Created by Moritz Herzog on 25.03.25.
//

#include "Feature.h"
#include <vector>

#include "Redefinition.h"
#include "ReferenceSubsetting.h"
#include "CrossSubsetting.h"

namespace KerML::Entities
{
	Feature::Feature() :
	Type(),
	IsUnique(true),
	IsOrdered(false),
	IsComposite(false),
	IsEnd(false),
	IsDerived(false),
	IsPortion(false),
	IsVariable(false),
	IsConstant(false),
	Direction( {} )
	{	}

	void Feature::setIsUnique(bool isUnique)
	{
		IsUnique = isUnique;
	}

	bool Feature::isUnique()
	{
		return IsUnique;
	}

	void Feature::setIsOrdered(bool isOrdered)
	{
		IsOrdered = isOrdered;
	}

	bool Feature::isOrdered()
	{
		return IsOrdered;
	}

	void Feature::setIsComposite(bool isComposite)
	{
		IsComposite = isComposite;
	}

	bool Feature::isComposite()
	{
		return IsComposite;
	}

	void Feature::setIsEnd(bool isEnd)
	{
		IsEnd = isEnd;
	}

	bool Feature::isEnd()
	{
		return IsEnd;
	}

	void Feature::setIsDerived(bool isDerived)
	{
		IsDerived = isDerived;
	}

	bool Feature::isDerived()
	{
		return IsDerived;
	}

	void Feature::setIsPortion(bool isPortion)
	{
		IsPortion = isPortion;
	}

	bool Feature::isPortion()
	{
		return IsPortion;
	}

	void Feature::setIsVariable(bool isVariable)
	{
		IsVariable = isVariable;
	}

	bool Feature::isVariable()
	{
		return IsVariable;
	}

	void Feature::setIsConstant(bool isConstant)
	{
		IsConstant = isConstant;
	}

	bool Feature::isConstant()
	{
		return IsConstant;
	}

	void Feature::setDirection(FeatureDirectionKind direction)
	{
		Direction = direction;
	}

	std::optional<FeatureDirectionKind> Feature::direction()
	{
		return Direction;
	}

	void Feature::setType(std::vector<std::shared_ptr<Type>> type)
	{
		_Type = type;
	}

	std::vector<std::shared_ptr<Type>> Feature::type() const
	{
		return _Type;
	}

	void Feature::appendType(std::vector<std::shared_ptr<Type>> type)
	{
		_Type.insert(_Type.begin(), type.begin(), type.end());
	}

	void Feature::appendType(std::shared_ptr<Type> type)
	{
		_Type.push_back(type);
	}

	void Feature::setTypeFeaturing(std::vector<std::shared_ptr<TypeFeaturing>> typeFeaturing)
	{
		_TypeFeaturing = typeFeaturing;
	}

	std::vector<std::shared_ptr<TypeFeaturing>> Feature::typeFeaturing() const
	{
		return _TypeFeaturing;
	}

	void Feature::appendTypeFeatuing(std::vector<std::shared_ptr<TypeFeaturing>> typeFeaturing)
	{
		_TypeFeaturing.insert(_TypeFeaturing.end(), typeFeaturing.begin(), typeFeaturing.end());
	}

	void Feature::appendTypeFeaturing(std::shared_ptr<TypeFeaturing> typeFeaturing)
	{
		_TypeFeaturing.push_back(typeFeaturing);
	}

	FeatureDirectionKind Feature::directionFor(std::shared_ptr<Type> type)
	{
		return FeatureDirectionKind::IN_OUT;
	}

	std::optional<std::string> Feature::effectiveShortName() const
	{
		if (declaredShortName().has_value() && declaredName().has_value())
			return declaredName();
		else
		{
			if (namingFeature().has_value())
				return namingFeature().value()->effectiveName();
			else
				return {};

		}
	}

	std::optional<std::string> Feature::effectiveName() const
	{
		return Type::effectiveName();
	}

	std::optional<std::shared_ptr<Feature>> Feature::namingFeature() const
	{
		if (OwnedRedefinition.empty())
			return {};

		return OwnedRedefinition.front()->redefinedFeature();
	}

	std::vector<std::shared_ptr<Type>> Feature::supertypes(bool excludeImplied)
	{
		return Type::supertypes(excludeImplied);
	}

	bool Feature::redefines(std::shared_ptr<Feature> redefinedFeature)
	{
		for (const auto& redefinition : OwnedRedefinition)
			if (redefinition->redefinedFeature()->includes(redefinedFeature))
				return true;

		return false;
	}

	bool Feature::redefinesFromLibrary(std::string libraryFeatureName)
	{

	}

	bool Feature::subsetsChain(std::shared_ptr<Feature> first, std::shared_ptr<Feature> second)
	{
	}

	void Feature::isCompatibleWith(std::shared_ptr<Type> otherType)
	{
		Type::isCompatibleWith(otherType);
	}

	std::vector<std::shared_ptr<Feature>> Feature::typingFeatures()
	{
	}

	std::vector<std::shared_ptr<Type>> Feature::asCartesianProduct()
	{
	}

	bool Feature::isCartesianProduct()
	{
	}

	bool Feature::isOwnedCrossFeature()
	{
	}

	std::optional<std::shared_ptr<Feature>> Feature::ownedCrossFeature()
	{
	}

	std::vector<std::shared_ptr<Feature>> Feature::allRedefinedFeatures()
	{
	}

	bool Feature::isFeaturedWithin(std::optional<std::shared_ptr<Type>>)
	{
	}

	bool Feature::canAccess(std::shared_ptr<Feature> feature)
	{
	}

	bool Feature::isFeaturingType(std::shared_ptr<Type> type)
	{
	}

	void Feature::setFeaturingType(std::vector<std::shared_ptr<Type>> featuringType)
	{
		FeaturingType = featuringType;
	}

	std::vector<std::shared_ptr<Type>> Feature::featuringType() const
	{
		return FeaturingType;
	}

	void Feature::appendFeaturingType(std::vector<std::shared_ptr<Type>> featuringType)
	{
		FeaturingType.insert(FeaturingType.end(), featuringType.begin(), featuringType.end());
	}

	void Feature::appendFeaturingType(std::shared_ptr<Type> featuringType)
	{
		FeaturingType.push_back(featuringType);
	}

	void Feature::setOwnedTypeFeaturing(std::vector<std::shared_ptr<TypeFeaturing>> ownedTypeFeaturing)
	{
		OwnedTypeFeaturing = ownedTypeFeaturing;
	}

	std::vector<std::shared_ptr<TypeFeaturing>> Feature::ownedTypeFeaturing() const
	{
		return OwnedTypeFeaturing;
	}

	void Feature::appendOwnedTypeFeaturing(std::vector<std::shared_ptr<TypeFeaturing>> ownedTypeFeaturing)
	{
		OwnedTypeFeaturing.insert(OwnedTypeFeaturing.end(), ownedTypeFeaturing.begin(), ownedTypeFeaturing.end());
	}

	void Feature::appendOwnedTypeFeaturing(std::shared_ptr<TypeFeaturing> ownedTypeFeaturing)
	{
		OwnedTypeFeaturing.push_back(ownedTypeFeaturing);
	}

	void Feature::setChainingFeature(std::vector<std::shared_ptr<Feature>> chainingFeature)
	{
	}

	std::vector<std::shared_ptr<Feature>> Feature::chainingFeature() const
	{
	}

	void Feature::appendChainingFeature(std::vector<std::shared_ptr<Feature>> chainingFeature)
	{
	}

	void Feature::appendChainingFeature(std::shared_ptr<Feature> chainingFeature)
	{
	}

	std::optional<std::shared_ptr<Feature>> Feature::crossFeature() const
	{
		if (OwnedCrossSubsetting == nullptr)
			return {};

		const int CrossFeatureIndexInChainingFeature = 1;

		//TODO Too sketchy for me, this needs fixing. Implementation according to the Standard. This might cause many issues. 
		return OwnedCrossSubsetting->crossedFeature()->ChainingFeature.at(CrossFeatureIndexInChainingFeature);
	}

	void Feature::setCrossFeature(std::optional<std::shared_ptr<Feature>> crossFeature)
	{
		//TODO Too sketchy for me, this needs fixing. Implementation according to the Standard. This might cause many issues. 
		if (crossFeature.has_value())
			return;

        const int CrossFeatureIndexInChainingFeature = 1;

		if (OwnedCrossSubsetting)
            OwnedCrossSubsetting->crossedFeature()->ChainingFeature[CrossFeatureIndexInChainingFeature] = crossFeature.value();
	}

	std::optional<std::shared_ptr<Type>> Feature::endOwningType() const
	{
	}

	void Feature::setEndOwningType(std::optional<std::shared_ptr<Type>> crossFeature)
	{
	}

	std::shared_ptr<Feature> Feature::featureTarget()
	{
		if (ChainingFeature.size() > 0)
			return ChainingFeature.back();

		return shared_from_this();
	}

	std::optional<std::shared_ptr<CrossSubsetting>> Feature::ownedCrossSubsetting() const
	{
	}

	void Feature::setOwnedCrossSubsetting(std::optional<std::shared_ptr<CrossSubsetting>> ownedCrossSubsetting)
	{
	}

	void Feature::setOwnedFeatureChaining(std::vector<std::shared_ptr<FeatureChaining>> ownedFeatureChaining)
	{
	}

	std::vector<std::shared_ptr<FeatureChaining>> Feature::ownedFeatureChaining() const
	{
	}

	void Feature::appendOwnedFeatureChaining(std::vector<std::shared_ptr<FeatureChaining>> ownedFeatureChaining)
	{
	}

	void Feature::appendOwnedFeatureChaining(std::shared_ptr<FeatureChaining> ownedFeatureChaining)
	{
	}

	void Feature::setOwnedFeatureInverting(std::vector<std::shared_ptr<FeatureInverting>> ownedFeatureInverting)
	{
	}

	std::vector<std::shared_ptr<FeatureInverting>> Feature::ownedFeatureInverting() const
	{
	}

	void Feature::appendOwnedFeatureInverting(std::vector<std::shared_ptr<FeatureInverting>> ownedFeaureInverting)
	{
	}

	void Feature::appendOwnedFeatureInverting(std::shared_ptr<FeatureTyping> ownedFeatureInverting)
	{
	}

	void Feature::setOwnedRedefinition(std::vector<std::shared_ptr<Redefinition>> ownedRedefinition)
	{
	}

	std::vector<std::shared_ptr<Redefinition>> Feature::ownedRedefinition() const
	{
	}

	void Feature::appendOwnedRedefinition(std::vector<std::shared_ptr<Redefinition>> ownedRedefinition)
	{
	}

	void Feature::appendOwnedRedefinition(std::shared_ptr<Redefinition> ownedRedefinition)
	{
	}

	void Feature::setOwnedReferenceSubsetting(
		std::optional<std::shared_ptr<Entities::ReferenceSubsetting>> referenceSubsetting)
	{
		if (referenceSubsetting.has_value() && (referenceSubsetting != nullptr))
			OwnedReferenceSubsetting = referenceSubsetting.value();
	}

	std::optional<std::shared_ptr<ReferenceSubsetting>> Feature::ownedReferenceSubsetting() const
	{
		if (OwnedReferenceSubsetting == nullptr)
			return {};
	}

	void Feature::setOwendSubsetting(std::vector<std::shared_ptr<Subsetting>> ownedSubsetting)
	{
	}

	std::vector<std::shared_ptr<Subsetting>> Feature::ownedSubsetting() const
	{
	}

	void Feature::appendOwnedSubsetting(std::vector<std::shared_ptr<Subsetting>> ownedSubsetting)
	{
	}

	void Feature::appendOwnedSubsetting(std::shared_ptr<Subsetting> ownedSubsetting)
	{
	}

	void Feature::setOwnedTyping(std::vector<std::shared_ptr<FeatureTyping>> ownedTyping)
	{
	}

	std::vector<std::shared_ptr<FeatureTyping>> Feature::ownedTyping() const
	{
	}

	void Feature::appendOwnedTyping(std::vector<std::shared_ptr<FeatureTyping>> ownedTyping)
	{
	}

	void Feature::appendOwnedTyping(std::shared_ptr<FeatureTyping> ownedTyping)
	{
	}

	void Feature::setOwningFeatureMembership(std::optional<std::shared_ptr<FeatureMembership>> owningMembership)
	{
	}

	std::optional<std::shared_ptr<FeatureMembership>> Feature::owningFeatureMembership() const
	{
	}

	void Feature::setOwningType(std::optional<std::shared_ptr<Type>> owningType)
	{
	}

	std::optional<std::shared_ptr<Type>> Feature::owningType() const
	{
	}
}
