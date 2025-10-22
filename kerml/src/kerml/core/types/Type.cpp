//
// Created by Moritz Herzog on 25.03.25.
//

#include <kerml/core/types/Type.h>
#include <kerml/core/features/Multiplicity.h>
#include <kerml/kernel/assiciations/Association.h>

namespace KerML::Entities {
	Type::Type(boost::uuids::uuid elementID, std::shared_ptr<Element> owner) :
		Namespace(elementID, owner) {

	}

	Type::Type(std::string namespaceName, boost::uuids::uuid elementID, std::shared_ptr<Element> owner) :
		Namespace(namespaceName, elementID, owner) {

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

	std::vector<std::shared_ptr<Feature>> Type::allRedefinedFeaturesOf(std::shared_ptr<Membership> ) {
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
		_Multiplicity = multiplicity;
	}

	std::vector<std::shared_ptr<Feature>> Type::output() const
	{
		return Output;
	}

	void Type::setOutput(std::vector<std::shared_ptr<Feature>> output)
	{
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