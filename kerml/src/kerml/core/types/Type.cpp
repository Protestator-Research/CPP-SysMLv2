//
// Created by Moritz Herzog on 25.03.25.
//

#include <kerml/core/types/Type.h>
#include <kerml/core/features/Multiplicity.h>
#include <kerml/kernel/assiciations/Association.h>
#include <kerml/KerML.h>
#include <nlohmann/json.hpp>
#include "../../model/JsonSupport.h"

namespace KerML::Entities {
	Type::Type(boost::uuids::uuid elementID, std::shared_ptr<Element> owner) :
		Element(elementID, owner), Namespace(elementID, owner) {
		_dType = "Type";
	}

	Type::Type(std::string namespaceName, boost::uuids::uuid elementID, std::shared_ptr<Element> owner) :
		Element(elementID, owner), Namespace(Json::looksLikeJson(namespaceName) ? std::string() : namespaceName, elementID, owner) {
		_dType = "Type";
		if (Json::looksLikeJson(namespaceName)) {
		    deserializeAndPopulate(namespaceName);
		    captureJsonSource(namespaceName);
		}
	}

	std::vector<std::shared_ptr<Membership>>
		Type::visibleMemberships(std::vector<std::shared_ptr<Namespace>> excluded, bool isRecursive, bool includeAll) {
		return Namespace::visibleMemberships(excluded, isRecursive, includeAll);
	}

	std::vector<std::shared_ptr<Membership>>
		Type::inheritedMemberships(std::vector<std::shared_ptr<Namespace>> ,
			std::vector<std::shared_ptr<Type>> , bool ) {
		return std::vector<std::shared_ptr<Membership>>();
	}

	std::vector<std::shared_ptr<Membership>>
		Type::inheritableMemberships(std::vector<std::shared_ptr<Namespace>> ,
			std::vector<std::shared_ptr<Type>> , bool ) {
		return std::vector<std::shared_ptr<Membership>>();
	}

	std::vector<std::shared_ptr<Membership>>
		Type::nonPrivateMemberships(std::vector<std::shared_ptr<Namespace>> ,
			std::vector<std::shared_ptr<Type>> , bool ) {
		return std::vector<std::shared_ptr<Membership>>();
	}

	std::vector<std::shared_ptr<Membership>>
		Type::removeRedefinedFeature(std::vector<std::shared_ptr<Membership>> ) {
		return std::vector<std::shared_ptr<Membership>>();
	}

	std::vector<std::shared_ptr<Feature>> Type::allRedefinedFeaturesOf(std::shared_ptr<Membership>) {
		return std::vector<std::shared_ptr<Feature>>();
	}

	FeatureDirectionKind Type::directionOf(std::shared_ptr<Feature> ) {
		return OUT;
	}

	FeatureDirectionKind
		Type::directionOfExcluding(std::shared_ptr<Feature> , std::vector<std::shared_ptr<Type>> ) {
		return OUT;
	}

	std::vector<std::shared_ptr<Type>> Type::supertypes(bool ) {
		return std::vector<std::shared_ptr<Type>>();
	}

	std::vector<std::shared_ptr<Type>> Type::allSupertypes() {
		return std::vector<std::shared_ptr<Type>>();
	}

	bool Type::specializes(std::shared_ptr<Type> ) {
		return false;
	}

	bool Type::specializesFromLibrary(std::string ) {
		return false;
	}

	void Type::isCompatibleWith(std::shared_ptr<Type> ) {

	}

	std::vector<std::shared_ptr<Multiplicity>> Type::multiplicities() {
		return { _Multiplicity };
	}

	bool Type::isAbstract() {
		return IsAbstract;
	}

	void Type::setAbstract(bool isAbstract) {
		IsAbstract = isAbstract;
	}

	bool Type::isSufficient() {
		return IsSufficient;
	}

	void Type::setIsSufficient(bool isSufficient) {
		IsSufficient = isSufficient;
	}

	void Type::setIsConjugated(bool isConjugated) {
		IsConjugated = isConjugated;
	}

	bool Type::isConjugated() {
		return IsConjugated;
	}

	std::vector<std::shared_ptr<Type>> Type::differencingType() const {
		return DifferencingType;
	}

	void Type::setDifferencingType(std::vector<std::shared_ptr<Type>> differencingType) {
		clearUnresolvedJsonReferences("differencingType");
		DifferencingType = differencingType;
	}

	void Type::appendDifferencingType(std::shared_ptr<Type> differencingType) {
		DifferencingType.push_back(differencingType);
	}

	void Type::appendDifferencingType(std::vector<std::shared_ptr<Type>> differencingType) {
		DifferencingType.insert(DifferencingType.end(), differencingType.begin(), differencingType.end());
	}

	std::vector<std::shared_ptr<Feature>> Type::directedFeature() const {
		return DirectedFeature;
	}

	void Type::setDirectedFeature(std::vector<std::shared_ptr<Feature>> directedFeature)
	{
		clearUnresolvedJsonReferences("directedFeature");
		DirectedFeature = directedFeature;
	}

	void Type::appendDirectedFeature(std::shared_ptr<Feature> directedFeature)
	{
		DirectedFeature.push_back(directedFeature);
	}

	void Type::appendDirectedFeature(std::vector<std::shared_ptr<Feature>> directedFeature)
	{
		DirectedFeature.insert(DirectedFeature.begin(), directedFeature.begin(), directedFeature.end());
	}

	std::vector<std::shared_ptr<Feature>> Type::endFeature() const
	{
		return EndFeature;
	}

	void Type::setEndFeatures(std::vector<std::shared_ptr<Feature>> endFeatures)
	{
		EndFeature = endFeatures;
	}

	void Type::appendEndFeatures(std::shared_ptr<Feature> endFeature)
	{
		EndFeature.push_back(endFeature);
	}

	void Type::appendEndFeatures(std::vector<std::shared_ptr<Feature>> endFeatures)
	{
		EndFeature.insert(EndFeature.end(), endFeatures.begin(), endFeatures.end());
	}

	std::vector<std::shared_ptr<Feature>> Type::features() const
	{
		return Features;
	}

	void Type::setFeatures(std::vector<std::shared_ptr<Feature>> features)
	{
		Features = features;
	}

	void Type::appendFeatures(std::shared_ptr<Feature> feature)
	{
		Features.push_back(feature);
	}

	void Type::appendFeatures(std::vector<std::shared_ptr<Feature>> features)
	{
		Features.insert(Features.end(), features.begin(), features.end());
	}

	std::vector<std::shared_ptr<FeatureMembership>> Type::featureMemberships() const
	{
		return FeatureMemberships;
	}

	void Type::setFeatureMemberships(std::vector<std::shared_ptr<FeatureMembership>> featureMemberships)
	{
		FeatureMemberships = featureMemberships;
	}

	void Type::appendFeatureMemberships(std::shared_ptr<FeatureMembership> featureMembership)
	{
		FeatureMemberships.push_back(featureMembership);
	}

	void Type::appendFeatureMemberships(std::vector<std::shared_ptr<FeatureMembership>> featureMemberships)
	{
		FeatureMemberships.insert(FeatureMemberships.end(), featureMemberships.begin(), featureMemberships.end());
	}

	std::vector<std::shared_ptr<Feature>> Type::inheritedFeature() const
	{
		return InheritedFeature;
	}

	void Type::setInheritedFeature(std::vector<std::shared_ptr<Feature>> inheritedFeature)
	{
		clearUnresolvedJsonReferences("inheritedFeature");
		InheritedFeature = inheritedFeature;
	}

	void Type::appendInheritedFeature(std::shared_ptr<Feature> inheritedFeature)
	{
		InheritedFeature.push_back(inheritedFeature);
	}

	void Type::appendInheritedFeature(std::vector<std::shared_ptr<Feature>> inheritedFeature)
	{
		InheritedFeature.insert(InheritedFeature.end(), inheritedFeature.begin(), inheritedFeature.end());
	}

	std::vector<std::shared_ptr<Membership>> Type::inheritedMemberships() const
	{
		return InheritedMembership;
	}

	void Type::setInheritedMembership(std::vector<std::shared_ptr<Membership>> inheritedMembership)
	{
		clearUnresolvedJsonReferences("inheritedMembership");
		InheritedMembership = inheritedMembership;
	}

	void Type::appendInheritedMembership(std::shared_ptr<Membership> inheritedMembership)
	{
		InheritedMembership.push_back(inheritedMembership);
	}

	void Type::appendInheritedMembership(std::vector<std::shared_ptr<Membership>> inheritedMembership)
	{
		InheritedMembership.insert(InheritedMembership.end(), inheritedMembership.begin(), inheritedMembership.end());
	}

	std::vector<std::shared_ptr<Feature>> Type::input() const
	{
		return Input;
	}

	void Type::setInput(std::vector<std::shared_ptr<Feature>> input)
	{
		clearUnresolvedJsonReferences("input");
		Input = input;
	}

	void Type::appendInput(std::shared_ptr<Feature> input)
	{
		Input.push_back(input);
	}

	void Type::appendInput(std::vector<std::shared_ptr<Feature>> input)
	{
		Input.insert(Input.end(), input.begin(), input.end());
	}

	std::vector<std::shared_ptr<Type>> Type::intersectingType() const
	{
		return IntersectingType;
	}

	void Type::setIntersectingType(std::vector<std::shared_ptr<Type>> intersectingType)
	{
		clearUnresolvedJsonReferences("intersectingType");
		IntersectingType = intersectingType;
	}

	void Type::appendIntersectingType(std::shared_ptr<Type> intersectingType)
	{
		IntersectingType.push_back(intersectingType);
	}

	void Type::appendIntersectingType(std::vector<std::shared_ptr<Type>> intersectingType)
	{
		IntersectingType.insert(IntersectingType.end(), intersectingType.begin(), intersectingType.end());
	}

	std::optional<std::shared_ptr<Multiplicity>> Type::multiplicity()
	{
		if (_Multiplicity!=nullptr)
			return _Multiplicity;

		return {};
	}

	void Type::setMultiplicity(std::shared_ptr<Entities::Multiplicity> multiplicity)
	{
		clearUnresolvedJsonReferences("multiplicity");
		_Multiplicity = multiplicity;
	}

	std::vector<std::shared_ptr<Feature>> Type::output() const
	{
		return Output;
	}

	void Type::setOutput(std::vector<std::shared_ptr<Feature>> output)
	{
		clearUnresolvedJsonReferences("output");
		Output = output;
	}

	void Type::appendOutput(std::shared_ptr<Feature> output)
	{
		Output.push_back(output);
	}

	void Type::appendOutput(std::vector<std::shared_ptr<Feature>> output)
	{
		Output.insert(Output.end(), output.begin(), output.end());
	}

	std::optional<std::shared_ptr<Conjugation>> Type::conjugation()
	{
		if (OwnedConjugator != nullptr)
			return OwnedConjugator;
		return { };
	}

	void Type::setConjugation(std::shared_ptr<Conjugation> conjugation)
	{
		OwnedConjugator = conjugation;
	}

	std::vector<std::shared_ptr<Differencing>> Type::ownedDifferencing() const
	{
		return OwnedDifferencing;
	}

	void Type::setOwnedDifferencing(std::vector<std::shared_ptr<Differencing>> ownedDifferencing)
	{
		clearUnresolvedJsonReferences("ownedDifferencing");
		OwnedDifferencing = ownedDifferencing;
	}

	void Type::appendOwnedDifferencing(std::shared_ptr<Differencing> ownedDifferencing)
	{
		OwnedDifferencing.push_back(ownedDifferencing);
	}

	void Type::appendOwnedDifferencing(std::vector<std::shared_ptr<Differencing>> ownedDifferencing)
	{
		OwnedDifferencing.insert(OwnedDifferencing.end(), ownedDifferencing.begin(), ownedDifferencing.end());
	}

	std::vector<std::shared_ptr<Disjoining>> Type::ownedDisjoining() const
	{
		return OwnedDisjoining;
	}

	void Type::setOwnedDisjoining(std::vector<std::shared_ptr<Disjoining>> ownedDisjoining)
	{
		clearUnresolvedJsonReferences("ownedDisjoining");
		OwnedDisjoining = ownedDisjoining;
	}

	void Type::appendOwnedDisjoining(std::shared_ptr<Disjoining> ownedDisjoining)
	{
		OwnedDisjoining.push_back(ownedDisjoining);
	}

	void Type::appendOwnedDisjoining(std::vector<std::shared_ptr<Disjoining>> ownedDisjoining)
	{
		OwnedDisjoining.insert(OwnedDisjoining.end(), ownedDisjoining.begin(), ownedDisjoining.end());
	}

	std::vector<std::shared_ptr<Feature>> Type::ownedEndFeature() const
	{
		return OwnedEndFeature;
	}

	void Type::setOwnedEndFeature(std::vector<std::shared_ptr<Feature>> ownedEndFeature)
	{
		clearUnresolvedJsonReferences("ownedEndFeature");
		OwnedEndFeature = ownedEndFeature;
	}

	void Type::appendOwnedEndFeature(std::shared_ptr<Feature> ownedEndFeature)
	{
		OwnedEndFeature.push_back(ownedEndFeature);
	}

	void Type::appendOwnedEndFeature(std::vector<std::shared_ptr<Feature>> ownedEndFeature)
	{
		OwnedEndFeature.insert(OwnedEndFeature.end(), ownedEndFeature.begin(), ownedEndFeature.end());
	}

	std::vector<std::shared_ptr<Feature>> Type::ownedFeature() const
	{
		return OwnedFeature;
	}

	void Type::setOwnedFeature(std::vector<std::shared_ptr<Feature>> ownedFeature)
	{
		clearUnresolvedJsonReferences("ownedFeature");
		OwnedFeature = ownedFeature;
	}

	void Type::appendOwnedFeature(std::shared_ptr<Feature> ownedFeature)
	{
		OwnedFeature.push_back(ownedFeature);
	}

	void Type::appendOwnedFeature(std::vector<std::shared_ptr<Feature>> ownedFeature)
	{
		OwnedFeature.insert(OwnedFeature.end(), ownedFeature.begin(), ownedFeature.end());
	}

	std::vector<std::shared_ptr<FeatureMembership>> Type::ownedFeatureMembership() const
	{
		return OwnedFeatureMembership;
	}

	void Type::setOwnedFeatureMembership(std::vector<std::shared_ptr<FeatureMembership>> ownedFeatureMembership)
	{
		clearUnresolvedJsonReferences("ownedFeatureMembership");
		OwnedFeatureMembership = ownedFeatureMembership;
	}

	void Type::appendOwnedFeatureMembership(std::shared_ptr<FeatureMembership> ownedFeatureMembership)
	{
		OwnedFeatureMembership.push_back(ownedFeatureMembership);
	}

	void Type::appendOwnedFeatureMembership(std::vector<std::shared_ptr<FeatureMembership>> ownedFeatureMembership)
	{
		OwnedFeatureMembership.insert(OwnedFeatureMembership.end(), ownedFeatureMembership.begin(), ownedFeatureMembership.end());
	}

	std::vector<std::shared_ptr<Intersecting>> Type::ownedIntersecting() const
	{
		return OwnedIntersecting;
	}

	void Type::setOwnedIntersecting(std::vector<std::shared_ptr<Intersecting>> ownedIntersecting)
	{
		clearUnresolvedJsonReferences("ownedIntersecting");
		OwnedIntersecting = ownedIntersecting;
	}

	void Type::appendOwnedIntersecting(std::shared_ptr<Intersecting> ownedIntersecting)
	{
		OwnedIntersecting.push_back(ownedIntersecting);
	}

	void Type::appendOwnedIntersecting(std::vector<std::shared_ptr<Intersecting>> ownedIntersecting)
	{
		OwnedIntersecting.insert(OwnedIntersecting.end(), ownedIntersecting.begin(), ownedIntersecting.end());
	}

	std::vector<std::shared_ptr<Specialization>> Type::ownedSpecialization() const
	{
		return OwnedSpecialization;
	}

	void Type::setOwnedSpecialization(std::vector<std::shared_ptr<Specialization>> ownedSpecialization)
	{
		clearUnresolvedJsonReferences("ownedSpecialization");
		OwnedSpecialization = ownedSpecialization;
	}

	void Type::appendOwnedSpecialization(std::shared_ptr<Specialization> ownedSpecialization)
	{
		OwnedSpecialization.push_back(ownedSpecialization);
	}

	void Type::appendOwnedSpecialization(std::vector<std::shared_ptr<Specialization>> ownedSpecialization)
	{
		OwnedSpecialization.insert(OwnedSpecialization.end(), ownedSpecialization.begin(), ownedSpecialization.end());
	}

	std::vector<std::shared_ptr<Unioning>> Type::ownedUnioning() const
	{
		return OwnedUnioning;
	}

	void Type::setOwnedUnioning(std::vector<std::shared_ptr<Unioning>> ownedUnioning)
	{
		clearUnresolvedJsonReferences("ownedUnioning");
		OwnedUnioning = ownedUnioning;
	}

	void Type::appendOwnedUnioning(std::shared_ptr<Unioning> ownedUnioning)
	{
		OwnedUnioning.push_back(ownedUnioning);
	}

	void Type::appendOwnedUnioning(std::vector<std::shared_ptr<Unioning>> ownedUnioning)
	{
		OwnedUnioning.insert(OwnedUnioning.end(), ownedUnioning.begin(), ownedUnioning.end());
	}

	std::vector<std::shared_ptr<Type>> Type::unioningType() const
	{
		return UnioningType;
	}

	void Type::setUnioningType(std::vector<std::shared_ptr<Type>> unioningType)
	{
		clearUnresolvedJsonReferences("unioningType");
		UnioningType = unioningType;
	}

	void Type::appendUnioningType(std::shared_ptr<Type> unioningType)
	{
		UnioningType.push_back(unioningType);
	}

	void Type::appendUnioningType(std::vector<std::shared_ptr<Type>> unioningType)
	{
		UnioningType.insert(UnioningType.end(), unioningType.begin(), unioningType.end());
	}

} // KerML::Entities

// BEGIN GENERATED JSON (kerml/tools/generate_json.py): do not edit, run the script instead.
namespace KerML::Entities {
    std::string Type::serializeToJson() {
        nlohmann::json json = nlohmann::json::parse(Namespace::serializeToJson());
        json["ownedSpecialization"] = Json::reference(unresolvedJsonReferences("ownedSpecialization"), Type::ownedSpecialization());
        json["ownedFeatureMembership"] = Json::reference(unresolvedJsonReferences("ownedFeatureMembership"), Type::ownedFeatureMembership());
        json["feature"] = Json::reference(unresolvedJsonReferences("feature"), Type::feature());
        json["ownedFeature"] = Json::reference(unresolvedJsonReferences("ownedFeature"), Type::ownedFeature());
        json["input"] = Json::reference(unresolvedJsonReferences("input"), Type::input());
        json["output"] = Json::reference(unresolvedJsonReferences("output"), Type::output());
        json["isAbstract"] = Json::value(Type::isAbstract());
        json["inheritedMembership"] = Json::reference(unresolvedJsonReferences("inheritedMembership"), Type::inheritedMembership());
        json["endFeature"] = Json::reference(unresolvedJsonReferences("endFeature"), Type::endFeature());
        json["ownedEndFeature"] = Json::reference(unresolvedJsonReferences("ownedEndFeature"), Type::ownedEndFeature());
        json["isSufficient"] = Json::value(Type::isSufficient());
        json["ownedConjugator"] = Json::reference(unresolvedJsonReferences("ownedConjugator"), Type::ownedConjugator());
        json["isConjugated"] = Json::value(Type::isConjugated());
        json["inheritedFeature"] = Json::reference(unresolvedJsonReferences("inheritedFeature"), Type::inheritedFeature());
        json["multiplicity"] = Json::reference(unresolvedJsonReferences("multiplicity"), Type::multiplicity());
        json["unioningType"] = Json::reference(unresolvedJsonReferences("unioningType"), Type::unioningType());
        json["ownedIntersecting"] = Json::reference(unresolvedJsonReferences("ownedIntersecting"), Type::ownedIntersecting());
        json["intersectingType"] = Json::reference(unresolvedJsonReferences("intersectingType"), Type::intersectingType());
        json["ownedUnioning"] = Json::reference(unresolvedJsonReferences("ownedUnioning"), Type::ownedUnioning());
        json["ownedDisjoining"] = Json::reference(unresolvedJsonReferences("ownedDisjoining"), Type::ownedDisjoining());
        json["featureMembership"] = Json::reference(unresolvedJsonReferences("featureMembership"), Type::featureMembership());
        json["differencingType"] = Json::reference(unresolvedJsonReferences("differencingType"), Type::differencingType());
        json["ownedDifferencing"] = Json::reference(unresolvedJsonReferences("ownedDifferencing"), Type::ownedDifferencing());
        json["directedFeature"] = Json::reference(unresolvedJsonReferences("directedFeature"), Type::directedFeature());
        return applyJsonSource(json.dump(JSON_INTENT));
    }

    void Type::deserializeAndPopulate(const std::string& jsonString) {
        Namespace::deserializeAndPopulate(jsonString);
        const nlohmann::json json = nlohmann::json::parse(jsonString);
        std::vector<boost::uuids::uuid> ids;
        if (Json::readReferences(json, "ownedSpecialization", ids))
            setUnresolvedJsonReferences("ownedSpecialization", ids);
        if (Json::readReferences(json, "ownedFeatureMembership", ids))
            setUnresolvedJsonReferences("ownedFeatureMembership", ids);
        if (Json::readReferences(json, "ownedFeature", ids))
            setUnresolvedJsonReferences("ownedFeature", ids);
        if (Json::readReferences(json, "input", ids))
            setUnresolvedJsonReferences("input", ids);
        if (Json::readReferences(json, "output", ids))
            setUnresolvedJsonReferences("output", ids);
        {
            bool value{};
            if (Json::readBool(json, "isAbstract", value)) {
                try {
                    Type::setAbstract(value);
                } catch (const std::invalid_argument&) {
                    // A value the metaclass refuses (for example another operator than the fixed one) is ignored.
                }
            }
        }
        if (Json::readReferences(json, "inheritedMembership", ids))
            setUnresolvedJsonReferences("inheritedMembership", ids);
        if (Json::readReferences(json, "ownedEndFeature", ids))
            setUnresolvedJsonReferences("ownedEndFeature", ids);
        {
            bool value{};
            if (Json::readBool(json, "isSufficient", value)) {
                try {
                    Type::setIsSufficient(value);
                } catch (const std::invalid_argument&) {
                    // A value the metaclass refuses (for example another operator than the fixed one) is ignored.
                }
            }
        }
        if (Json::readReferences(json, "inheritedFeature", ids))
            setUnresolvedJsonReferences("inheritedFeature", ids);
        if (Json::readReferences(json, "multiplicity", ids))
            setUnresolvedJsonReferences("multiplicity", ids);
        if (Json::readReferences(json, "unioningType", ids))
            setUnresolvedJsonReferences("unioningType", ids);
        if (Json::readReferences(json, "ownedIntersecting", ids))
            setUnresolvedJsonReferences("ownedIntersecting", ids);
        if (Json::readReferences(json, "intersectingType", ids))
            setUnresolvedJsonReferences("intersectingType", ids);
        if (Json::readReferences(json, "ownedUnioning", ids))
            setUnresolvedJsonReferences("ownedUnioning", ids);
        if (Json::readReferences(json, "ownedDisjoining", ids))
            setUnresolvedJsonReferences("ownedDisjoining", ids);
        if (Json::readReferences(json, "differencingType", ids))
            setUnresolvedJsonReferences("differencingType", ids);
        if (Json::readReferences(json, "ownedDifferencing", ids))
            setUnresolvedJsonReferences("ownedDifferencing", ids);
        if (Json::readReferences(json, "directedFeature", ids))
            setUnresolvedJsonReferences("directedFeature", ids);
    }

    void Type::resolveJsonReferences(const std::function<std::shared_ptr<Element>(const boost::uuids::uuid&)>& lookup) {
        Namespace::resolveJsonReferences(lookup);
        if (const auto ids = unresolvedJsonReferences("ownedSpecialization")) {
            try {
                std::vector<std::shared_ptr<KerML::Entities::Specialization>> resolved;
                for (const auto& id : *ids) {
                    auto target = std::dynamic_pointer_cast<KerML::Entities::Specialization>(lookup(id));
                    if (!target)
                        break;
                    resolved.push_back(std::move(target));
                }
                // (the setter forgets the ids, see clearUnresolvedJsonReferences)
                if (resolved.size() == ids->size()) {
                    Type::setOwnedSpecialization(std::move(resolved));
                    clearUnresolvedJsonReferences("ownedSpecialization");
                }
            } catch (const std::exception&) {
                // The reference stays unresolved if the model refuses it.
                setUnresolvedJsonReferences("ownedSpecialization", *ids);
            }
        }
        if (const auto ids = unresolvedJsonReferences("ownedFeatureMembership")) {
            try {
                std::vector<std::shared_ptr<KerML::Entities::FeatureMembership>> resolved;
                for (const auto& id : *ids) {
                    auto target = std::dynamic_pointer_cast<KerML::Entities::FeatureMembership>(lookup(id));
                    if (!target)
                        break;
                    resolved.push_back(std::move(target));
                }
                // (the setter forgets the ids, see clearUnresolvedJsonReferences)
                if (resolved.size() == ids->size()) {
                    Type::setOwnedFeatureMembership(std::move(resolved));
                    clearUnresolvedJsonReferences("ownedFeatureMembership");
                }
            } catch (const std::exception&) {
                // The reference stays unresolved if the model refuses it.
                setUnresolvedJsonReferences("ownedFeatureMembership", *ids);
            }
        }
        if (const auto ids = unresolvedJsonReferences("ownedFeature")) {
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
                    Type::setOwnedFeature(std::move(resolved));
                    clearUnresolvedJsonReferences("ownedFeature");
                }
            } catch (const std::exception&) {
                // The reference stays unresolved if the model refuses it.
                setUnresolvedJsonReferences("ownedFeature", *ids);
            }
        }
        if (const auto ids = unresolvedJsonReferences("input")) {
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
                    Type::setInput(std::move(resolved));
                    clearUnresolvedJsonReferences("input");
                }
            } catch (const std::exception&) {
                // The reference stays unresolved if the model refuses it.
                setUnresolvedJsonReferences("input", *ids);
            }
        }
        if (const auto ids = unresolvedJsonReferences("output")) {
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
                    Type::setOutput(std::move(resolved));
                    clearUnresolvedJsonReferences("output");
                }
            } catch (const std::exception&) {
                // The reference stays unresolved if the model refuses it.
                setUnresolvedJsonReferences("output", *ids);
            }
        }
        if (const auto ids = unresolvedJsonReferences("inheritedMembership")) {
            try {
                std::vector<std::shared_ptr<KerML::Entities::Membership>> resolved;
                for (const auto& id : *ids) {
                    auto target = std::dynamic_pointer_cast<KerML::Entities::Membership>(lookup(id));
                    if (!target)
                        break;
                    resolved.push_back(std::move(target));
                }
                // (the setter forgets the ids, see clearUnresolvedJsonReferences)
                if (resolved.size() == ids->size()) {
                    Type::setInheritedMembership(std::move(resolved));
                    clearUnresolvedJsonReferences("inheritedMembership");
                }
            } catch (const std::exception&) {
                // The reference stays unresolved if the model refuses it.
                setUnresolvedJsonReferences("inheritedMembership", *ids);
            }
        }
        if (const auto ids = unresolvedJsonReferences("ownedEndFeature")) {
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
                    Type::setOwnedEndFeature(std::move(resolved));
                    clearUnresolvedJsonReferences("ownedEndFeature");
                }
            } catch (const std::exception&) {
                // The reference stays unresolved if the model refuses it.
                setUnresolvedJsonReferences("ownedEndFeature", *ids);
            }
        }
        if (const auto ids = unresolvedJsonReferences("inheritedFeature")) {
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
                    Type::setInheritedFeature(std::move(resolved));
                    clearUnresolvedJsonReferences("inheritedFeature");
                }
            } catch (const std::exception&) {
                // The reference stays unresolved if the model refuses it.
                setUnresolvedJsonReferences("inheritedFeature", *ids);
            }
        }
        if (const auto ids = unresolvedJsonReferences("multiplicity")) {
            try {
                if (auto target = std::dynamic_pointer_cast<KerML::Entities::Multiplicity>(lookup(ids->front()))) {
                    Type::setMultiplicity(std::move(target));
                    clearUnresolvedJsonReferences("multiplicity");
                }
            } catch (const std::exception&) {
                // The reference stays unresolved if the model refuses it.
                setUnresolvedJsonReferences("multiplicity", *ids);
            }
        }
        if (const auto ids = unresolvedJsonReferences("unioningType")) {
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
                    Type::setUnioningType(std::move(resolved));
                    clearUnresolvedJsonReferences("unioningType");
                }
            } catch (const std::exception&) {
                // The reference stays unresolved if the model refuses it.
                setUnresolvedJsonReferences("unioningType", *ids);
            }
        }
        if (const auto ids = unresolvedJsonReferences("ownedIntersecting")) {
            try {
                std::vector<std::shared_ptr<KerML::Entities::Intersecting>> resolved;
                for (const auto& id : *ids) {
                    auto target = std::dynamic_pointer_cast<KerML::Entities::Intersecting>(lookup(id));
                    if (!target)
                        break;
                    resolved.push_back(std::move(target));
                }
                // (the setter forgets the ids, see clearUnresolvedJsonReferences)
                if (resolved.size() == ids->size()) {
                    Type::setOwnedIntersecting(std::move(resolved));
                    clearUnresolvedJsonReferences("ownedIntersecting");
                }
            } catch (const std::exception&) {
                // The reference stays unresolved if the model refuses it.
                setUnresolvedJsonReferences("ownedIntersecting", *ids);
            }
        }
        if (const auto ids = unresolvedJsonReferences("intersectingType")) {
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
                    Type::setIntersectingType(std::move(resolved));
                    clearUnresolvedJsonReferences("intersectingType");
                }
            } catch (const std::exception&) {
                // The reference stays unresolved if the model refuses it.
                setUnresolvedJsonReferences("intersectingType", *ids);
            }
        }
        if (const auto ids = unresolvedJsonReferences("ownedUnioning")) {
            try {
                std::vector<std::shared_ptr<KerML::Entities::Unioning>> resolved;
                for (const auto& id : *ids) {
                    auto target = std::dynamic_pointer_cast<KerML::Entities::Unioning>(lookup(id));
                    if (!target)
                        break;
                    resolved.push_back(std::move(target));
                }
                // (the setter forgets the ids, see clearUnresolvedJsonReferences)
                if (resolved.size() == ids->size()) {
                    Type::setOwnedUnioning(std::move(resolved));
                    clearUnresolvedJsonReferences("ownedUnioning");
                }
            } catch (const std::exception&) {
                // The reference stays unresolved if the model refuses it.
                setUnresolvedJsonReferences("ownedUnioning", *ids);
            }
        }
        if (const auto ids = unresolvedJsonReferences("ownedDisjoining")) {
            try {
                std::vector<std::shared_ptr<KerML::Entities::Disjoining>> resolved;
                for (const auto& id : *ids) {
                    auto target = std::dynamic_pointer_cast<KerML::Entities::Disjoining>(lookup(id));
                    if (!target)
                        break;
                    resolved.push_back(std::move(target));
                }
                // (the setter forgets the ids, see clearUnresolvedJsonReferences)
                if (resolved.size() == ids->size()) {
                    Type::setOwnedDisjoining(std::move(resolved));
                    clearUnresolvedJsonReferences("ownedDisjoining");
                }
            } catch (const std::exception&) {
                // The reference stays unresolved if the model refuses it.
                setUnresolvedJsonReferences("ownedDisjoining", *ids);
            }
        }
        if (const auto ids = unresolvedJsonReferences("differencingType")) {
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
                    Type::setDifferencingType(std::move(resolved));
                    clearUnresolvedJsonReferences("differencingType");
                }
            } catch (const std::exception&) {
                // The reference stays unresolved if the model refuses it.
                setUnresolvedJsonReferences("differencingType", *ids);
            }
        }
        if (const auto ids = unresolvedJsonReferences("ownedDifferencing")) {
            try {
                std::vector<std::shared_ptr<KerML::Entities::Differencing>> resolved;
                for (const auto& id : *ids) {
                    auto target = std::dynamic_pointer_cast<KerML::Entities::Differencing>(lookup(id));
                    if (!target)
                        break;
                    resolved.push_back(std::move(target));
                }
                // (the setter forgets the ids, see clearUnresolvedJsonReferences)
                if (resolved.size() == ids->size()) {
                    Type::setOwnedDifferencing(std::move(resolved));
                    clearUnresolvedJsonReferences("ownedDifferencing");
                }
            } catch (const std::exception&) {
                // The reference stays unresolved if the model refuses it.
                setUnresolvedJsonReferences("ownedDifferencing", *ids);
            }
        }
        if (const auto ids = unresolvedJsonReferences("directedFeature")) {
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
                    Type::setDirectedFeature(std::move(resolved));
                    clearUnresolvedJsonReferences("directedFeature");
                }
            } catch (const std::exception&) {
                // The reference stays unresolved if the model refuses it.
                setUnresolvedJsonReferences("directedFeature", *ids);
            }
        }
    }
}
// END GENERATED JSON
