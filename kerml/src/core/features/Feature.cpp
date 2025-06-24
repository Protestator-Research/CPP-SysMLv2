//
// Created by Moritz Herzog on 25.03.25.
//

#include "Feature.h"
#include <vector>

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
}
