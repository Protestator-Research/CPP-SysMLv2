//
// Created by Moritz Herzog on 25.03.25.
//

#include <kerml/core/features/Feature.h>
#include <vector>
#include <unordered_set>
#include <stack>

#include <kerml/core/features/Redefinition.h>
#include <kerml/core/features/FeatureTyping.h>
#include <kerml/core/features/ReferenceSubsetting.h>
#include <kerml/core/features/CrossSubsetting.h>
#include <kerml/core/features/Subsetting.h>
#include <kerml/root/namespaces/Membership.h>
#include <kerml/root/namespaces/VisibilityKind.h>
#include <kerml/core/types/Type.h>
#include <kerml/KerML.h>
#include <nlohmann/json.hpp>
#include "../../model/JsonSupport.h"

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
	Direction( std::nullopt )
	{
		_dType = "Feature";
	}

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
		clearUnresolvedJsonReferences("type");
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
		return Element::effectiveName();
	}

	std::optional<std::shared_ptr<Feature>> Feature::namingFeature() const
	{
		if (OwnedRedefinition.empty())
			return {};

		return OwnedRedefinition.front()->redefinedFeature();
	}

	std::vector<std::shared_ptr<Type>> Feature::supertypes(bool excludeImplied)
	{
        auto result = Type::supertypes(excludeImplied);
        for (const auto& typing : OwnedTyping) if (typing && typing->type()) result.push_back(typing->type());
        for (const auto& subsetting : OwnedSubsetting) if (subsetting && subsetting->subsettedFeature()) result.push_back(subsetting->subsettedFeature());
        return result;
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
		clearUnresolvedJsonReferences("featuringType");
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
		clearUnresolvedJsonReferences("ownedTypeFeaturing");
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
        clearUnresolvedJsonReferences("chainingFeature");
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
        if (CrossFeatureSnapshot) return CrossFeatureSnapshot;
        if (!OwnedCrossSubsetting || !OwnedCrossSubsetting->crossedFeature()) return {};
        auto chain = OwnedCrossSubsetting->crossedFeature()->chainingFeature();
        return chain.size() > 1 ? std::optional<std::shared_ptr<Feature>>{chain[1]} : std::nullopt;
    }

	void Feature::setCrossFeature(std::optional<std::shared_ptr<Feature>> crossFeature)
	{
        clearUnresolvedJsonReferences("crossFeature");
        CrossFeatureSnapshot = crossFeature.value_or(nullptr);
    }

	std::optional<std::shared_ptr<Type>> Feature::endOwningType() const
	{
        if(EndOwningType== nullptr)
            return {};

        return EndOwningType;
	}

	void Feature::setEndOwningType(std::optional<std::shared_ptr<Type>> endOwningType)
	{
        clearUnresolvedJsonReferences("endOwningType");
        EndOwningType = endOwningType.value_or(nullptr);
    }

	std::shared_ptr<Feature> Feature::featureTarget()
	{
		if (ChainingFeature.size() > 0)
			return ChainingFeature.back();

		return weak_from_this().lock();
	}

	std::optional<std::shared_ptr<CrossSubsetting>> Feature::ownedCrossSubsetting() const
	{
        if(OwnedCrossSubsetting == nullptr)
            return {};

        return OwnedCrossSubsetting;
	}

	void Feature::setOwnedCrossSubsetting(std::optional<std::shared_ptr<CrossSubsetting>> ownedCrossSubsetting)
	{
        clearUnresolvedJsonReferences("ownedCrossSubsetting");
        OwnedCrossSubsetting = ownedCrossSubsetting.value_or(nullptr);
    }

	void Feature::setOwnedFeatureChaining(std::vector<std::shared_ptr<FeatureChaining>> ownedFeatureChaining)
	{
        clearUnresolvedJsonReferences("ownedFeatureChaining");
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
        clearUnresolvedJsonReferences("ownedFeatureInverting");
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
        clearUnresolvedJsonReferences("ownedRedefinition");
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
        clearUnresolvedJsonReferences("ownedReferenceSubsetting");
        OwnedReferenceSubsetting = referenceSubsetting.value_or(nullptr);
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
        clearUnresolvedJsonReferences("ownedTyping");
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
        clearUnresolvedJsonReferences("owningFeatureMembership");
        OwningFeatureMembership = owningMembership.value_or(nullptr);
    }

	std::optional<std::shared_ptr<FeatureMembership>> Feature::owningFeatureMembership() const
	{
        if(OwningFeatureMembership == nullptr)
            return {};

        return OwningFeatureMembership;
	}

	void Feature::setOwningType(std::optional<std::shared_ptr<Type>> owningType)
	{
        clearUnresolvedJsonReferences("owningType");
        OwningType = owningType.value_or(nullptr);
    }

	std::optional<std::shared_ptr<Type>> Feature::owningType() const
	{
        if(OwningType == nullptr)
            return {};

        return OwningType;
	}
}

// BEGIN GENERATED JSON (kerml/tools/generate_json.py): do not edit, run the script instead.
namespace KerML::Entities {
    Feature::Feature(const std::string& nameOrJson) :
        Feature() {
        _dType = "Feature";
        if (Json::looksLikeJson(nameOrJson)) {
            deserializeAndPopulate(nameOrJson);
            captureJsonSource(nameOrJson);
        } else {
            setDeclaredName(nameOrJson);
        }
    }

    std::string Feature::serializeToJson() {
        nlohmann::json json = nlohmann::json::parse(Type::serializeToJson());
        json["owningType"] = Json::reference(unresolvedJsonReferences("owningType"), Feature::owningType());
        json["isUnique"] = Json::value(Feature::isUnique());
        json["isOrdered"] = Json::value(Feature::isOrdered());
        json["type"] = Json::reference(unresolvedJsonReferences("type"), Feature::type());
        json["ownedRedefinition"] = Json::reference(unresolvedJsonReferences("ownedRedefinition"), Feature::ownedRedefinition());
        json["ownedSubsetting"] = Json::reference(unresolvedJsonReferences("ownedSubsetting"), Feature::ownedSubsetting());
        json["owningFeatureMembership"] = Json::reference(unresolvedJsonReferences("owningFeatureMembership"), Feature::owningFeatureMembership());
        json["isComposite"] = Json::value(Feature::isComposite());
        json["isEnd"] = Json::value(Feature::isEnd());
        json["endOwningType"] = Json::reference(unresolvedJsonReferences("endOwningType"), Feature::endOwningType());
        json["ownedTyping"] = Json::reference(unresolvedJsonReferences("ownedTyping"), Feature::ownedTyping());
        json["featuringType"] = Json::reference(unresolvedJsonReferences("featuringType"), Feature::featuringType());
        json["ownedTypeFeaturing"] = Json::reference(unresolvedJsonReferences("ownedTypeFeaturing"), Feature::ownedTypeFeaturing());
        json["isDerived"] = Json::value(Feature::isDerived());
        json["chainingFeature"] = Json::reference(unresolvedJsonReferences("chainingFeature"), Feature::chainingFeature());
        json["ownedFeatureInverting"] = Json::reference(unresolvedJsonReferences("ownedFeatureInverting"), Feature::ownedFeatureInverting());
        json["ownedFeatureChaining"] = Json::reference(unresolvedJsonReferences("ownedFeatureChaining"), Feature::ownedFeatureChaining());
        json["isPortion"] = Json::value(Feature::isPortion());
        json["isVariable"] = Json::value(Feature::isVariable());
        json["isConstant"] = Json::value(Feature::isConstant());
        json["ownedReferenceSubsetting"] = Json::reference(unresolvedJsonReferences("ownedReferenceSubsetting"), Feature::ownedReferenceSubsetting());
        json["featureTarget"] = Json::reference(unresolvedJsonReferences("featureTarget"), Feature::featureTarget());
        json["crossFeature"] = Json::reference(unresolvedJsonReferences("crossFeature"), Feature::crossFeature());
        json["direction"] = Json::value(Feature::direction());
        json["ownedCrossSubsetting"] = Json::reference(unresolvedJsonReferences("ownedCrossSubsetting"), Feature::ownedCrossSubsetting());
        return applyJsonSource(json.dump(JSON_INTENT));
    }

    void Feature::deserializeAndPopulate(const std::string& jsonString) {
        Type::deserializeAndPopulate(jsonString);
        const nlohmann::json json = nlohmann::json::parse(jsonString);
        std::vector<boost::uuids::uuid> ids;
        if (Json::readReferences(json, "owningType", ids))
            setUnresolvedJsonReferences("owningType", ids);
        {
            bool value{};
            if (Json::readBool(json, "isUnique", value)) {
                try {
                    Feature::setIsUnique(value);
                } catch (const std::invalid_argument&) {
                    // A value the metaclass refuses (for example another operator than the fixed one) is ignored.
                }
            }
        }
        {
            bool value{};
            if (Json::readBool(json, "isOrdered", value)) {
                try {
                    Feature::setIsOrdered(value);
                } catch (const std::invalid_argument&) {
                    // A value the metaclass refuses (for example another operator than the fixed one) is ignored.
                }
            }
        }
        if (Json::readReferences(json, "type", ids))
            setUnresolvedJsonReferences("type", ids);
        if (Json::readReferences(json, "ownedRedefinition", ids))
            setUnresolvedJsonReferences("ownedRedefinition", ids);
        if (Json::readReferences(json, "owningFeatureMembership", ids))
            setUnresolvedJsonReferences("owningFeatureMembership", ids);
        {
            bool value{};
            if (Json::readBool(json, "isComposite", value)) {
                try {
                    Feature::setIsComposite(value);
                } catch (const std::invalid_argument&) {
                    // A value the metaclass refuses (for example another operator than the fixed one) is ignored.
                }
            }
        }
        {
            bool value{};
            if (Json::readBool(json, "isEnd", value)) {
                try {
                    Feature::setIsEnd(value);
                } catch (const std::invalid_argument&) {
                    // A value the metaclass refuses (for example another operator than the fixed one) is ignored.
                }
            }
        }
        if (Json::readReferences(json, "endOwningType", ids))
            setUnresolvedJsonReferences("endOwningType", ids);
        if (Json::readReferences(json, "ownedTyping", ids))
            setUnresolvedJsonReferences("ownedTyping", ids);
        if (Json::readReferences(json, "featuringType", ids))
            setUnresolvedJsonReferences("featuringType", ids);
        if (Json::readReferences(json, "ownedTypeFeaturing", ids))
            setUnresolvedJsonReferences("ownedTypeFeaturing", ids);
        {
            bool value{};
            if (Json::readBool(json, "isDerived", value)) {
                try {
                    Feature::setIsDerived(value);
                } catch (const std::invalid_argument&) {
                    // A value the metaclass refuses (for example another operator than the fixed one) is ignored.
                }
            }
        }
        if (Json::readReferences(json, "chainingFeature", ids))
            setUnresolvedJsonReferences("chainingFeature", ids);
        if (Json::readReferences(json, "ownedFeatureInverting", ids))
            setUnresolvedJsonReferences("ownedFeatureInverting", ids);
        if (Json::readReferences(json, "ownedFeatureChaining", ids))
            setUnresolvedJsonReferences("ownedFeatureChaining", ids);
        {
            bool value{};
            if (Json::readBool(json, "isPortion", value)) {
                try {
                    Feature::setIsPortion(value);
                } catch (const std::invalid_argument&) {
                    // A value the metaclass refuses (for example another operator than the fixed one) is ignored.
                }
            }
        }
        {
            bool value{};
            if (Json::readBool(json, "isVariable", value)) {
                try {
                    Feature::setIsVariable(value);
                } catch (const std::invalid_argument&) {
                    // A value the metaclass refuses (for example another operator than the fixed one) is ignored.
                }
            }
        }
        {
            bool value{};
            if (Json::readBool(json, "isConstant", value)) {
                try {
                    Feature::setIsConstant(value);
                } catch (const std::invalid_argument&) {
                    // A value the metaclass refuses (for example another operator than the fixed one) is ignored.
                }
            }
        }
        if (Json::readReferences(json, "ownedReferenceSubsetting", ids))
            setUnresolvedJsonReferences("ownedReferenceSubsetting", ids);
        if (Json::readReferences(json, "crossFeature", ids))
            setUnresolvedJsonReferences("crossFeature", ids);
        {
            FeatureDirectionKind value{};
            if (Json::readEnum(json, "direction", value)) {
                try {
                    Feature::setDirection(value);
                } catch (const std::invalid_argument&) {
                    // A value the metaclass refuses (for example another operator than the fixed one) is ignored.
                }
            }
        }
        if (Json::readReferences(json, "ownedCrossSubsetting", ids))
            setUnresolvedJsonReferences("ownedCrossSubsetting", ids);
    }

    void Feature::resolveJsonReferences(const std::function<std::shared_ptr<Element>(const boost::uuids::uuid&)>& lookup) {
        Type::resolveJsonReferences(lookup);
        if (const auto ids = unresolvedJsonReferences("owningType")) {
            try {
                if (auto target = std::dynamic_pointer_cast<KerML::Entities::Type>(lookup(ids->front()))) {
                    Feature::setOwningType(std::move(target));
                    clearUnresolvedJsonReferences("owningType");
                }
            } catch (const std::exception&) {
                // The reference stays unresolved if the model refuses it.
                setUnresolvedJsonReferences("owningType", *ids);
            }
        }
        if (const auto ids = unresolvedJsonReferences("type")) {
            try {
                std::vector<std::shared_ptr<KerML::Entities::Type>> resolved;
                for (const auto& id : *ids) {
                    auto target = std::dynamic_pointer_cast<KerML::Entities::Type>(lookup(id));
                    if (!target)
                        break;
                    resolved.push_back(std::move(target));
                }
                // (the setter forgets the ids, see clearUnresolvedJsonReferences)
                if (resolved.size() == ids->size()) {
                    Feature::setType(std::move(resolved));
                    clearUnresolvedJsonReferences("type");
                }
            } catch (const std::exception&) {
                // The reference stays unresolved if the model refuses it.
                setUnresolvedJsonReferences("type", *ids);
            }
        }
        if (const auto ids = unresolvedJsonReferences("ownedRedefinition")) {
            try {
                std::vector<std::shared_ptr<KerML::Entities::Redefinition>> resolved;
                for (const auto& id : *ids) {
                    auto target = std::dynamic_pointer_cast<KerML::Entities::Redefinition>(lookup(id));
                    if (!target)
                        break;
                    resolved.push_back(std::move(target));
                }
                // (the setter forgets the ids, see clearUnresolvedJsonReferences)
                if (resolved.size() == ids->size()) {
                    Feature::setOwnedRedefinition(std::move(resolved));
                    clearUnresolvedJsonReferences("ownedRedefinition");
                }
            } catch (const std::exception&) {
                // The reference stays unresolved if the model refuses it.
                setUnresolvedJsonReferences("ownedRedefinition", *ids);
            }
        }
        if (const auto ids = unresolvedJsonReferences("owningFeatureMembership")) {
            try {
                if (auto target = std::dynamic_pointer_cast<KerML::Entities::FeatureMembership>(lookup(ids->front()))) {
                    Feature::setOwningFeatureMembership(std::move(target));
                    clearUnresolvedJsonReferences("owningFeatureMembership");
                }
            } catch (const std::exception&) {
                // The reference stays unresolved if the model refuses it.
                setUnresolvedJsonReferences("owningFeatureMembership", *ids);
            }
        }
        if (const auto ids = unresolvedJsonReferences("endOwningType")) {
            try {
                if (auto target = std::dynamic_pointer_cast<KerML::Entities::Type>(lookup(ids->front()))) {
                    Feature::setEndOwningType(std::move(target));
                    clearUnresolvedJsonReferences("endOwningType");
                }
            } catch (const std::exception&) {
                // The reference stays unresolved if the model refuses it.
                setUnresolvedJsonReferences("endOwningType", *ids);
            }
        }
        if (const auto ids = unresolvedJsonReferences("ownedTyping")) {
            try {
                std::vector<std::shared_ptr<KerML::Entities::FeatureTyping>> resolved;
                for (const auto& id : *ids) {
                    auto target = std::dynamic_pointer_cast<KerML::Entities::FeatureTyping>(lookup(id));
                    if (!target)
                        break;
                    resolved.push_back(std::move(target));
                }
                // (the setter forgets the ids, see clearUnresolvedJsonReferences)
                if (resolved.size() == ids->size()) {
                    Feature::setOwnedTyping(std::move(resolved));
                    clearUnresolvedJsonReferences("ownedTyping");
                }
            } catch (const std::exception&) {
                // The reference stays unresolved if the model refuses it.
                setUnresolvedJsonReferences("ownedTyping", *ids);
            }
        }
        if (const auto ids = unresolvedJsonReferences("featuringType")) {
            try {
                std::vector<std::shared_ptr<KerML::Entities::Type>> resolved;
                for (const auto& id : *ids) {
                    auto target = std::dynamic_pointer_cast<KerML::Entities::Type>(lookup(id));
                    if (!target)
                        break;
                    resolved.push_back(std::move(target));
                }
                // (the setter forgets the ids, see clearUnresolvedJsonReferences)
                if (resolved.size() == ids->size()) {
                    Feature::setFeaturingType(std::move(resolved));
                    clearUnresolvedJsonReferences("featuringType");
                }
            } catch (const std::exception&) {
                // The reference stays unresolved if the model refuses it.
                setUnresolvedJsonReferences("featuringType", *ids);
            }
        }
        if (const auto ids = unresolvedJsonReferences("ownedTypeFeaturing")) {
            try {
                std::vector<std::shared_ptr<KerML::Entities::TypeFeaturing>> resolved;
                for (const auto& id : *ids) {
                    auto target = std::dynamic_pointer_cast<KerML::Entities::TypeFeaturing>(lookup(id));
                    if (!target)
                        break;
                    resolved.push_back(std::move(target));
                }
                // (the setter forgets the ids, see clearUnresolvedJsonReferences)
                if (resolved.size() == ids->size()) {
                    Feature::setOwnedTypeFeaturing(std::move(resolved));
                    clearUnresolvedJsonReferences("ownedTypeFeaturing");
                }
            } catch (const std::exception&) {
                // The reference stays unresolved if the model refuses it.
                setUnresolvedJsonReferences("ownedTypeFeaturing", *ids);
            }
        }
        if (const auto ids = unresolvedJsonReferences("chainingFeature")) {
            try {
                std::vector<std::shared_ptr<KerML::Entities::Feature>> resolved;
                for (const auto& id : *ids) {
                    auto target = std::dynamic_pointer_cast<KerML::Entities::Feature>(lookup(id));
                    if (!target)
                        break;
                    resolved.push_back(std::move(target));
                }
                // (the setter forgets the ids, see clearUnresolvedJsonReferences)
                if (resolved.size() == ids->size()) {
                    Feature::setChainingFeature(std::move(resolved));
                    clearUnresolvedJsonReferences("chainingFeature");
                }
            } catch (const std::exception&) {
                // The reference stays unresolved if the model refuses it.
                setUnresolvedJsonReferences("chainingFeature", *ids);
            }
        }
        if (const auto ids = unresolvedJsonReferences("ownedFeatureInverting")) {
            try {
                std::vector<std::shared_ptr<KerML::Entities::FeatureInverting>> resolved;
                for (const auto& id : *ids) {
                    auto target = std::dynamic_pointer_cast<KerML::Entities::FeatureInverting>(lookup(id));
                    if (!target)
                        break;
                    resolved.push_back(std::move(target));
                }
                // (the setter forgets the ids, see clearUnresolvedJsonReferences)
                if (resolved.size() == ids->size()) {
                    Feature::setOwnedFeatureInverting(std::move(resolved));
                    clearUnresolvedJsonReferences("ownedFeatureInverting");
                }
            } catch (const std::exception&) {
                // The reference stays unresolved if the model refuses it.
                setUnresolvedJsonReferences("ownedFeatureInverting", *ids);
            }
        }
        if (const auto ids = unresolvedJsonReferences("ownedFeatureChaining")) {
            try {
                std::vector<std::shared_ptr<KerML::Entities::FeatureChaining>> resolved;
                for (const auto& id : *ids) {
                    auto target = std::dynamic_pointer_cast<KerML::Entities::FeatureChaining>(lookup(id));
                    if (!target)
                        break;
                    resolved.push_back(std::move(target));
                }
                // (the setter forgets the ids, see clearUnresolvedJsonReferences)
                if (resolved.size() == ids->size()) {
                    Feature::setOwnedFeatureChaining(std::move(resolved));
                    clearUnresolvedJsonReferences("ownedFeatureChaining");
                }
            } catch (const std::exception&) {
                // The reference stays unresolved if the model refuses it.
                setUnresolvedJsonReferences("ownedFeatureChaining", *ids);
            }
        }
        if (const auto ids = unresolvedJsonReferences("ownedReferenceSubsetting")) {
            try {
                if (auto target = std::dynamic_pointer_cast<KerML::Entities::ReferenceSubsetting>(lookup(ids->front()))) {
                    Feature::setOwnedReferenceSubsetting(std::move(target));
                    clearUnresolvedJsonReferences("ownedReferenceSubsetting");
                }
            } catch (const std::exception&) {
                // The reference stays unresolved if the model refuses it.
                setUnresolvedJsonReferences("ownedReferenceSubsetting", *ids);
            }
        }
        if (const auto ids = unresolvedJsonReferences("crossFeature")) {
            try {
                if (auto target = std::dynamic_pointer_cast<KerML::Entities::Feature>(lookup(ids->front()))) {
                    Feature::setCrossFeature(std::move(target));
                    clearUnresolvedJsonReferences("crossFeature");
                }
            } catch (const std::exception&) {
                // The reference stays unresolved if the model refuses it.
                setUnresolvedJsonReferences("crossFeature", *ids);
            }
        }
        if (const auto ids = unresolvedJsonReferences("ownedCrossSubsetting")) {
            try {
                if (auto target = std::dynamic_pointer_cast<KerML::Entities::CrossSubsetting>(lookup(ids->front()))) {
                    Feature::setOwnedCrossSubsetting(std::move(target));
                    clearUnresolvedJsonReferences("ownedCrossSubsetting");
                }
            } catch (const std::exception&) {
                // The reference stays unresolved if the model refuses it.
                setUnresolvedJsonReferences("ownedCrossSubsetting", *ids);
            }
        }
    }
}
// END GENERATED JSON
