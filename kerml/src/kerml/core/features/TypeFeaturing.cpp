//
// Created by Moritz Herzog on 25.03.25.
//

#include <kerml/core/features/TypeFeaturing.h>
#include <kerml/core/features/Feature.h>
#include <kerml/core/types/Type.h>

namespace KerML::Entities {
	TypeFeaturing::TypeFeaturing(const std::shared_ptr<Type>& typeFeaturingOfType,
		const std::shared_ptr<Feature>& featureOfType, const std::shared_ptr<Feature>& owningFeatureOfType) :
	Relationship(boost::uuids::random_generator()(), owningFeatureOfType)
	{
		_dType = "TypeFeaturing";
		OwningFeatureOfType = owningFeatureOfType;
		FeatureOfType = featureOfType;
		TypeFeaturingOfType = typeFeaturingOfType;
	}

	void TypeFeaturing::setFeaturingType(const std::shared_ptr<Type>& typeFeaturingOfType)
	{
		TypeFeaturingOfType = typeFeaturingOfType;
	}

	std::shared_ptr<Type> TypeFeaturing::featuringType() const
	{
		return TypeFeaturingOfType;
	}

	void TypeFeaturing::setFeatureOfType(const std::shared_ptr<Feature>& featureOfType)
	{
		FeatureOfType = featureOfType;
	}

	std::shared_ptr<Feature> TypeFeaturing::featureOfType() const
	{
		return FeatureOfType;
	}

	void TypeFeaturing::setOwningFeatureOfType(const std::shared_ptr<Feature>& owningFeatureOfType)
	{
		OwningFeatureOfType = owningFeatureOfType;
	}

	std::shared_ptr<Feature> TypeFeaturing::owningFeatureOfType()
	{
		return OwningFeatureOfType;
	}
}
