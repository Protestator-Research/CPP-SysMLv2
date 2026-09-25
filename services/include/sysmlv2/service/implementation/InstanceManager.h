//
// Created by herzo on 24.09.2026.
//

#pragma once

#include <memory>
#include <string>
#include <vector>
#include <list>
#include <boost/uuid.hpp>
#include <sysmlv2/service/sysmlv2service_global.h>

namespace KerML
{
	namespace Entities
	{
		class Namespace;
		class Element;
	}
}

namespace SysMLv2
{
	namespace Files
	{
		class ParserError;
	}
}

namespace SysMLv2::API
{
	class SYSMLV2SERVICE_EXPORT InstanceManager
	{
	public:
		InstanceManager() = default;
		virtual ~InstanceManager() = default;

		void parseModel(std::string model);
		void appendNonStandardLibrary(std::string model);

		std::vector<std::shared_ptr<SysMLv2::Files::ParserError>> getParserErrors() const;
		std::vector<std::shared_ptr<KerML::Entities::Element>> getElements() const;
		std::shared_ptr<KerML::Entities::Namespace> getRootNamespace() const;

		std::list<std::shared_ptr<KerML::Entities::Element>> findAllElementsWithDeclaredName(std::string name);
		std::shared_ptr<KerML::Entities::Element> findElementWithQualifiedName(const std::string& name) const;
		std::shared_ptr<KerML::Entities::Element> findElementWithId(const boost::uuids::uuid& uuid) const;

	private:
		void rebuildModel();
		void importStandardLibraries();
		void parseNonStandardLibraries();
		void resolveNamespaceImports();
		void analyzeRootNamespaces();

		

		std::vector<std::shared_ptr<SysMLv2::Files::ParserError>> ParserErrors;
		std::vector<std::shared_ptr<KerML::Entities::Element>> Elements;
		std::shared_ptr<KerML::Entities::Namespace> RootNamespace = nullptr;

		std::string InstanceModel;
		std::vector<std::string> NonStandardLibraries;
		const std::vector<std::string> StandardLibraries = {
			// KerML Semantic
			"Base",
			"Clocks",
			"ControlPerformances",
			"FeatureReferencingPerformances",
			"KerML",
			"Links",
			"Metaobjects",
			"Objects",
			"Observation",
			"Occurrences",
			"Performances",
			"SpatialFrames",
			"StatePerformances",
			"Transfers",
			"TransitionPerformances",
			"Triggers",
			// KerML Functions
			"BaseFunctions",
			"BooleanFunctions",
			"CollectionFunctions",
			"ComplexFunctions",
			"ControlFunctions",
			"DataFunctions",
			"IntegerFunctions",
			"NaturalFunctions",
			"NumericalFunctions",
			"OccurrenceFunctions",
			"RationalFunctions",
			"RealFunctions",
			"ScalarFunctions",
			"SequenceFunctions",
			"StringFunctions",
			"TrigFunctions",
			"VectorFunctions",
			// KerML DataTypes
			"Collections",
			"ScalarValues",
			"VectorValues",
			// SysML 
			"Actions",
			"Allocations",
			"AnalysisCases",
			"Attributes",
			"Calculations",
			"Cases",
			"Connections",
			"Constraints",
			"Flows",
			"Interfaces",
			"Items",
			"Metadata",
			"Parts",
			"Ports",
			"Requirements",
			"StandardViewDefinitions",
			"States",
			"SysML",
			"UseCases",
			"VerificationCases",
			"Views",
			// Domain Libraries Analysis
			"AnalysisTooling",
			"SampledFunctions",
			"StateSpaceRepresentation",
			"TradeStudies",
			// Domain Libraries Cause and Effect
			"CausationConnections",
			"CauseAndEffect",
			// Domain Libraries Geometry
			"ShapeItems",
			"SpatialItems",
			// Domain Libraries Metadata
			"ImageMetadata",
			"ModelingMetadata",
			"ParametersOfInterestMetadata",
			"RiskMetadata",
			// Domain Libraries QuantitiesAndUnits
			"ISQ",
			"ISQAcoustics",
			"ISQAtomicNuclear",
			"ISQBase",
			"ISQCharacteristicNumbers",
			"ISQChemistryMolecular",
			"ISQCondensedMatter",
			"ISQElectromagnetism",
			"ISQInformation",
			"ISQLight",
			"ISQMechanics",
			"ISQSpaceTime",
			"ISQThermodynamics",
			"MeasurementRefCalculations",
			"MeasurementReferences",
			"Quantities",
			"QuantityCalculations",
			"SI",
			"SIPrefixes",
			"TensorCalculations",
			"Time",
			"USCustomaryUnits",
			"VectorCalculations",
			// Domain Libraries Requirement Derivation
			"DerivationConnections",
			"RequirementDerivation"
		};
		const std::vector<std::string> StandardLibrariesPaths = {
			// KerML Semantic
			"sysml.library/KerML/Semantic/Base.kerml",
			"sysml.library/KerML/Semantic/Clocks.kerml",
			"sysml.library/KerML/Semantic/ControlPerformances.kerml",
			"sysml.library/KerML/Semantic/FeatureReferencingPerformances.kerml",
			"sysml.library/KerML/Semantic/KerML.kerml",
			"sysml.library/KerML/Semantic/Links.kerml",
			"sysml.library/KerML/Semantic/Metaobjects.kerml",
			"sysml.library/KerML/Semantic/Objects.kerml",
			"sysml.library/KerML/Semantic/Observation.kerml",
			"sysml.library/KerML/Semantic/Occurrences.kerml",
			"sysml.library/KerML/Semantic/Performances.kerml",
			"sysml.library/KerML/Semantic/SpatialFrames.kerml",
			"sysml.library/KerML/Semantic/StatePerformances.kerml",
			"sysml.library/KerML/Semantic/Transfers.kerml",
			"sysml.library/KerML/Semantic/TransitionPerformances.kerml",
			"sysml.library/KerML/Semantic/Triggers.kerml",
			// KerML Functions
			"sysml.library/KerML/Function/BaseFunctions.kerml",
			"sysml.library/KerML/Function/BooleanFunctions.kerml",
			"sysml.library/KerML/Function/CollectionFunctions.kerml",
			"sysml.library/KerML/Function/ComplexFunctions.kerml",
			"sysml.library/KerML/Function/ControlFunctions.kerml",
			"sysml.library/KerML/Function/DataFunctions.kerml",
			"sysml.library/KerML/Function/IntegerFunctions.kerml",
			"sysml.library/KerML/Function/NaturalFunctions.kerml",
			"sysml.library/KerML/Function/NumericalFunctions.kerml",
			"sysml.library/KerML/Function/OccurrenceFunctions.kerml",
			"sysml.library/KerML/Function/RationalFunctions.kerml",
			"sysml.library/KerML/Function/RealFunctions.kerml",
			"sysml.library/KerML/Function/ScalarFunctions.kerml",
			"sysml.library/KerML/Function/SequenceFunctions.kerml",
			"sysml.library/KerML/Function/StringFunctions.kerml",
			"sysml.library/KerML/Function/TrigFunctions.kerml",
			"sysml.library/KerML/Function/VectorFunctions.kerml",
			// KerML Data Types
			"sysml.library/KerML/DataTypes/Collections.kerml",
			"sysml.library/KerML/DataTypes/ScalarValues.kerml",
			"sysml.library/KerML/DataTypes/VectorValues.kerml",
			// SysML
			"sysml.library/SystemsLibrary/Actions.sysml",
			"sysml.library/SystemsLibrary/Allocations.sysml",
			"sysml.library/SystemsLibrary/AnalysisCases.sysml",
			"sysml.library/SystemsLibrary/Attributes.sysml",
			"sysml.library/SystemsLibrary/Calculations.sysml",
			"sysml.library/SystemsLibrary/Cases.sysml",
			"sysml.library/SystemsLibrary/Connections.sysml",
			"sysml.library/SystemsLibrary/Constraints.sysml",
			"sysml.library/SystemsLibrary/Flows.sysml",
			"sysml.library/SystemsLibrary/Interfaces.sysml",
			"sysml.library/SystemsLibrary/Items.sysml",
			"sysml.library/SystemsLibrary/Metadata.sysml",
			"sysml.library/SystemsLibrary/Parts.sysml",
			"sysml.library/SystemsLibrary/Ports.sysml",
			"sysml.library/SystemsLibrary/Requirements.sysml",
			"sysml.library/SystemsLibrary/StandardViewDefinitions.sysml",
			"sysml.library/SystemsLibrary/States.sysml",
			"sysml.library/SystemsLibrary/SysML.sysml",
			"sysml.library/SystemsLibrary/UseCases.sysml",
			"sysml.library/SystemsLibrary/VerificationCases.sysml",
			"sysml.library/SystemsLibrary/Views.sysml",
			// Domain Libraries Analysis
			"sysml.library/DomainLibraries/Analysis/AnalysisTooling.sysml",
			"sysml.library/DomainLibraries/Analysis/SampledFunctions.sysml",
			"sysml.library/DomainLibraries/Analysis/StateSpaceRepresentation.sysml",
			"sysml.library/DomainLibraries/Analysis/TradeStudies.sysml",
			// Domain Libraries Cause and Effect
			"sysml.library/DomainLibraries/CauseAndEffect/CausationConnections.sysml",
			"sysml.library/DomainLibraries/CauseAndEffect/CauseAndEffect.sysml",
			// Domain Libraries Geometry
			"sysml.library/DomainLibraries/Geometry/ShapeItems.sysml",
			"sysml.library/DomainLibraries/Geometry/SpatialItems.sysml",
			// Domain Libraries Metadata
			"sysml.library/DomainLibraries/Metadata/ImageMetadata.sysml",
			"sysml.library/DomainLibraries/Metadata/ModelingMetadata.sysml",
			"sysml.library/DomainLibraries/Metadata/ParametersOfInterestMetadata.sysml",
			"sysml.library/DomainLibraries/Metadata/RiskMetadata.sysml",
			// Domain Libraries Quantities and Units
			"sysml.library/DomainLibraries/QuantitiesAndUnits/ISQ.sysml",
			"sysml.library/DomainLibraries/QuantitiesAndUnits/ISQAcoustics.sysml",
			"sysml.library/DomainLibraries/QuantitiesAndUnits/ISQAtomicNuclear.sysml",
			"sysml.library/DomainLibraries/QuantitiesAndUnits/ISQBase.sysml",
			"sysml.library/DomainLibraries/QuantitiesAndUnits/ISQCharacteristicNumbers.sysml",
			"sysml.library/DomainLibraries/QuantitiesAndUnits/ISQChemistryMolecular.sysml",
			"sysml.library/DomainLibraries/QuantitiesAndUnits/ISQCondensedMatter.sysml",
			"sysml.library/DomainLibraries/QuantitiesAndUnits/ISQElectromagnetism.sysml",
			"sysml.library/DomainLibraries/QuantitiesAndUnits/ISQInformation.sysml",
			"sysml.library/DomainLibraries/QuantitiesAndUnits/ISQLight.sysml",
			"sysml.library/DomainLibraries/QuantitiesAndUnits/ISQMechanics.sysml",
			"sysml.library/DomainLibraries/QuantitiesAndUnits/ISQSpaceTime.sysml",
			"sysml.library/DomainLibraries/QuantitiesAndUnits/ISQThermodynamics.sysml",
			"sysml.library/DomainLibraries/QuantitiesAndUnits/MeasurementRefCalculations.sysml",
			"sysml.library/DomainLibraries/QuantitiesAndUnits/MeasurementReferences.sysml",
			"sysml.library/DomainLibraries/QuantitiesAndUnits/Quantities.sysml",
			"sysml.library/DomainLibraries/QuantitiesAndUnits/QuantityCalculations.sysml",
			"sysml.library/DomainLibraries/QuantitiesAndUnits/SI.sysml",
			"sysml.library/DomainLibraries/QuantitiesAndUnits/SIPrefixes.sysml",
			"sysml.library/DomainLibraries/QuantitiesAndUnits/TensorCalculations.sysml",
			"sysml.library/DomainLibraries/QuantitiesAndUnits/Time.sysml",
			"sysml.library/DomainLibraries/QuantitiesAndUnits/USCustomaryUnits.sysml",
			"sysml.library/DomainLibraries/QuantitiesAndUnits/VectorCalculations.sysml",
			// Domain Libraries Requirement Derivation
			"sysml.library/DomainLibraries/RequirementDerivation/DerivationConnections.sysml",
			"sysml.library/DomainLibraries/RequirementDerivation/RequirementDerivation.sysml"
		};
	};
}
