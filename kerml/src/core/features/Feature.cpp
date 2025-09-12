//
// Created by Moritz Herzog on 25.03.25.
//

#include "Feature.h"
#include <vector>
#include <unordered_set>
#include <stack>

#include "Redefinition.h"
#include "ReferenceSubsetting.h"
#include "CrossSubsetting.h"
#include "Subsetting.h"
#include "../../root/namespaces/Membership.h"
#include "../../root/namespaces/VisibilityKind.h"

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

	void Feature::setDirection(std::optional<FeatureDirectionKind> direction)
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

	FeatureDirectionKind Feature::directionFor(std::shared_ptr<Type>)
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
        if(featureTarget()==shared_from_this())
            return supertypes(excludeImplied);

        std::vector<std::shared_ptr<Type>> returnValue;

        for(const auto& element : Type::supertypes(excludeImplied)){
            try {
                const auto value = std::dynamic_pointer_cast<Feature>(element);
                if(value)
                    returnValue.push_back(value);
            }catch (...){

            }
        }
		return returnValue;
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
        if(libraryFeatureName.empty())
            return false;

        for(const auto& redefinition : ownedRedefinition()){
            if(redefinition->effectiveName()==libraryFeatureName)
                return true;
        }

        return false;
	}

	bool Feature::subsetsChain(std::shared_ptr<Feature> first, std::shared_ptr<Feature> second)
	{
        if( !first || !second || first == second)
            return false;

        std::unordered_set<std::shared_ptr<Feature>> visited;
        std::stack<std::shared_ptr<Feature>> toVisit;
        toVisit.push(first);

        while (!toVisit.empty()) {
            const auto current = toVisit.top();
            toVisit.pop();

            if(!current || visited.contains(current))
                continue;

            for(const auto& subSetting : current->OwnedSubsetting) {
                if(subSetting->subsettedFeature() == second)
                    return true;

                toVisit.push(subSetting->subsettedFeature());
            }
        }
        return false;
	}

	void Feature::isCompatibleWith(std::shared_ptr<Type> otherType)
	{
		Type::isCompatibleWith(otherType);
	}

	std::vector<std::shared_ptr<Feature>> Feature::typingFeatures()
	{
        if(isConjugated()) {
            std::vector<std::shared_ptr<Feature>> typingFeatures;
            for(const auto& supertype : Type::supertypes(false)) {
                const auto value = std::dynamic_pointer_cast<Feature>(supertype);
                if(value)
                    typingFeatures.push_back(value);
            }
            return typingFeatures;
        }

        std::vector<std::shared_ptr<Feature>> typingFeatures;
        for(const auto & subsetting : ownedSubsetting()){
            typingFeatures.push_back(subsetting->subsettedFeature());
        }

        return typingFeatures;
	}

	std::vector<std::shared_ptr<Type>> Feature::asCartesianProduct()
	{
        if(isCartesianProduct()) {
            std::vector<std::shared_ptr<Type>> value = {OwnedCrossSubsetting->crossedFeature()};
            value.insert(value.end(), ownedEndFeature().begin(), ownedEndFeature().end());
            return value;
        }

        return std::vector<std::shared_ptr<Type>>();
	}

	bool Feature::isCartesianProduct()
	{
        return IsCartesianProduct;
	}

	bool Feature::isOwnedCrossFeature()
	{
        return (OwnedCrossSubsetting!= nullptr);
	}

	std::optional<std::shared_ptr<Feature>> Feature::ownedCrossFeature()
	{
        return OwnedCrossSubsetting->crossedFeature();
	}

	std::vector<std::shared_ptr<Feature>> Feature::allRedefinedFeatures()
	{
        std::vector<std::shared_ptr<Feature>> redefinitions;
        for(const auto& redefinition : OwnedRedefinition)
            redefinitions.push_back(redefinition->redefinedFeature());

        return redefinitions;
	}

	bool Feature::isFeaturedWithin(std::optional<std::shared_ptr<Type>> type)
	{
        bool returnValue = false;
        if(!type.has_value()) {
            const std::string namespaceSearchedFor = "Base::Anything";
            const auto baseAnythingResolved = resolveGlobal(namespaceSearchedFor);
            if(baseAnythingResolved.has_value()) {
                const auto value = baseAnythingResolved.value()->ownedElements()[0];
                const auto AnythingType = std::dynamic_pointer_cast<Type>(value);
                for(const auto& featuredType : featuringType()){
                    returnValue|=std::dynamic_pointer_cast<Feature>(featuredType)->isFeaturedWithin(AnythingType);
                }
            }
        }else {
            if(shared_from_this() == type.value())
                return true;

            for(const auto& featuredType : featuringType()){
                returnValue|=std::dynamic_pointer_cast<Feature>(featuredType)->isFeaturedWithin(type.value());
            }
        }
        return returnValue;
	}

	bool Feature::canAccess(std::shared_ptr<Feature> feature)
	{
        if(!feature)
            return false;

        if(feature.get() == this)
            return true;

        for(const auto& membership : memberships()) {
            if (membership->includes(feature)) {
                switch (membership->visibility()) {
                    case VisibilityKind::PUBLIC:
                    case VisibilityKind::PROTECTED:
                        return true;
                    case VisibilityKind::PRIVATE:
                        return false;
                }
            }
        }
        return false;
    }

	bool Feature::isFeaturingType(std::shared_ptr<Type> type)
	{
        if(!type)
            return false;

        std::unordered_set<std::shared_ptr<Type>> visited;
        std::stack<std::shared_ptr<Type>> toVisit;

        for(const auto& featuredType : featuringType())
            if(featuredType)
                toVisit.push(featuredType);

        while (!toVisit.empty()) {
            std::shared_ptr<Type> current = toVisit.top();
            toVisit.pop();

            if(!current || visited.contains(current))
                continue;

            visited.insert(current);

            if(current==type)
                return true;

            if(std::dynamic_pointer_cast<Feature>(current)) {
                for (const auto &superType: std::dynamic_pointer_cast<Feature>(current)->featuringType())
                    if(superType)
                        toVisit.push(superType);
            }
        }

        return false;
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
        ChainingFeature = chainingFeature;
	}

	std::vector<std::shared_ptr<Feature>> Feature::chainingFeature() const
	{
        return ChainingFeature;
	}

	void Feature::appendChainingFeature(std::vector<std::shared_ptr<Feature>> chainingFeature)
	{
        ChainingFeature.insert(ChainingFeature.end(), chainingFeature.begin(), chainingFeature.end());
	}

	void Feature::appendChainingFeature(std::shared_ptr<Feature> chainingFeature)
	{
        ChainingFeature.push_back(chainingFeature);
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
        if(EndOwningType== nullptr)
            return {};

        return EndOwningType;
	}

	void Feature::setEndOwningType(std::optional<std::shared_ptr<Type>> endOwningType)
	{
        if(endOwningType.has_value())
            EndOwningType = *endOwningType;
	}

	std::shared_ptr<Feature> Feature::featureTarget()
	{
		if (ChainingFeature.size() > 0)
			return ChainingFeature.back();

		return shared_from_this();
	}

	std::optional<std::shared_ptr<CrossSubsetting>> Feature::ownedCrossSubsetting() const
	{
        if(OwnedCrossSubsetting == nullptr)
            return {};

        return OwnedCrossSubsetting;
	}

	void Feature::setOwnedCrossSubsetting(std::optional<std::shared_ptr<CrossSubsetting>> ownedCrossSubsetting)
	{
        if(ownedCrossSubsetting.has_value())
            OwnedCrossSubsetting = *ownedCrossSubsetting;
	}

	void Feature::setOwnedFeatureChaining(std::vector<std::shared_ptr<FeatureChaining>> ownedFeatureChaining)
	{
        OwnedFeatureChaining = ownedFeatureChaining;
	}

	std::vector<std::shared_ptr<FeatureChaining>> Feature::ownedFeatureChaining() const
	{
        return OwnedFeatureChaining;
	}

	void Feature::appendOwnedFeatureChaining(std::vector<std::shared_ptr<FeatureChaining>> ownedFeatureChaining)
	{
        OwnedFeatureChaining.insert(OwnedFeatureChaining.end(),ownedFeatureChaining.begin(), ownedFeatureChaining.end());
	}

	void Feature::appendOwnedFeatureChaining(std::shared_ptr<FeatureChaining> ownedFeatureChaining)
	{
        OwnedFeatureChaining.push_back(ownedFeatureChaining);
	}

	void Feature::setOwnedFeatureInverting(std::vector<std::shared_ptr<FeatureInverting>> ownedFeatureInverting)
	{
        OwnedFeatureInverting = ownedFeatureInverting;
	}

	std::vector<std::shared_ptr<FeatureInverting>> Feature::ownedFeatureInverting() const
	{
        return OwnedFeatureInverting;
	}

	void Feature::appendOwnedFeatureInverting(std::vector<std::shared_ptr<FeatureInverting>> ownedFeaureInverting)
	{
        OwnedFeatureInverting.insert(OwnedFeatureInverting.end(), ownedFeaureInverting.begin(), ownedFeaureInverting.end());
	}

	void Feature::appendOwnedFeatureInverting(std::shared_ptr<FeatureInverting> ownedFeatureInverting)
	{
        OwnedFeatureInverting.push_back(ownedFeatureInverting);
	}

	void Feature::setOwnedRedefinition(std::vector<std::shared_ptr<Redefinition>> ownedRedefinition)
	{
        OwnedRedefinition = ownedRedefinition;
	}

	std::vector<std::shared_ptr<Redefinition>> Feature::ownedRedefinition() const
	{
        return OwnedRedefinition;
	}

	void Feature::appendOwnedRedefinition(std::vector<std::shared_ptr<Redefinition>> ownedRedefinition)
	{
        OwnedRedefinition.insert(OwnedRedefinition.end(), ownedRedefinition.begin(), ownedRedefinition.end());
	}

	void Feature::appendOwnedRedefinition(std::shared_ptr<Redefinition> ownedRedefinition)
	{
        OwnedRedefinition.push_back(ownedRedefinition);
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

        return OwnedReferenceSubsetting;
	}

	void Feature::setOwendSubsetting(std::vector<std::shared_ptr<Subsetting>> ownedSubsetting)
	{
        OwnedSubsetting = ownedSubsetting;
	}

	std::vector<std::shared_ptr<Subsetting>> Feature::ownedSubsetting() const
	{
        return OwnedSubsetting;
	}

	void Feature::appendOwnedSubsetting(std::vector<std::shared_ptr<Subsetting>> ownedSubsetting)
	{
        OwnedSubsetting.insert(OwnedSubsetting.begin(), ownedSubsetting.begin(), ownedSubsetting.end());
	}

	void Feature::appendOwnedSubsetting(std::shared_ptr<Subsetting> ownedSubsetting)
	{
        OwnedSubsetting.push_back(ownedSubsetting);
	}

	void Feature::setOwnedTyping(std::vector<std::shared_ptr<FeatureTyping>> ownedTyping)
	{
        OwnedTyping = ownedTyping;
	}

	std::vector<std::shared_ptr<FeatureTyping>> Feature::ownedTyping() const
	{
        return OwnedTyping;
	}

	void Feature::appendOwnedTyping(std::vector<std::shared_ptr<FeatureTyping>> ownedTyping)
	{
        OwnedTyping.insert(OwnedTyping.end(), ownedTyping.begin(), ownedTyping.end());
	}

	void Feature::appendOwnedTyping(std::shared_ptr<FeatureTyping> ownedTyping)
	{
        OwnedTyping.push_back(ownedTyping);
	}

	void Feature::setOwningFeatureMembership(std::optional<std::shared_ptr<FeatureMembership>> owningMembership)
	{
        if(owningMembership.has_value())
            OwningFeatureMembership = *owningMembership;
	}

	std::optional<std::shared_ptr<FeatureMembership>> Feature::owningFeatureMembership() const
	{
        if(OwningFeatureMembership == nullptr)
            return {};

        return OwningFeatureMembership;
	}

	void Feature::setOwningType(std::optional<std::shared_ptr<Type>> owningType)
	{
        if(owningType.has_value())
            OwningType = *owningType;
	}

	std::optional<std::shared_ptr<Type>> Feature::owningType() const
	{
        if(OwningType == nullptr)
            return {};

        return OwningType;
	}
}
