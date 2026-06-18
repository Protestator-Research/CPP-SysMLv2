//
// Created by Moritz Herzog on 25.03.25.
//

#include <kerml/core/features/FeatureTyping.h>
#include <kerml/core/features/Feature.h>
#include <kerml/core/types/Type.h>

namespace KerML::Entities
{
	FeatureTyping::FeatureTyping() : Specialization()
	{
		_dType = "FeatureTyping";
	}

	FeatureTyping::FeatureTyping(const std::shared_ptr<KerML::Entities::Type>& type,
		const std::shared_ptr<KerML::Entities::Feature>& typedFeature) : Specialization(type, typedFeature)
	{ 	}

	std::shared_ptr<KerML::Entities::Feature> FeatureTyping::typedFeature()
	{
		return TypedFeature;
	}

	void FeatureTyping::setTypedFeature(const std::shared_ptr<KerML::Entities::Feature>& typedFeature)
	{
		TypedFeature = typedFeature;
		Specialization::setSpecific(typedFeature);
	}

	std::shared_ptr<KerML::Entities::Type> FeatureTyping::type()
	{
		return Type;
	}

	void FeatureTyping::setType(const std::shared_ptr<KerML::Entities::Type>& type)
	{
		Type = type;
		Specialization::setGeneral(type);
	}
}
