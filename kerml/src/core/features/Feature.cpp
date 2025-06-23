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
}
