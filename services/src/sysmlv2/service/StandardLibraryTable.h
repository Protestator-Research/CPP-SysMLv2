//
// The table of the embedded standard library: the package that each file defines and its paths in the resources, text and XMI. The one place
// where the list of the files is kept (private header of sysmlv2service: used by InstanceManager and by StandardLibraryResources).
//
#pragma once

namespace SysMLv2::API::Detail
{
	/// A file of the embedded standard library: the name of the (top-level) package and the paths of its files in the resources: the text
	/// (sysmlv2resources, namespace Library) and the XMI (sysmlv2xmiresources, namespace LibraryXmi). The paths are those of
	/// resources/CMakeLists.txt.
	struct StandardLibraryEntry
	{
		const char* Name;
		const char* Path;
		const char* XmiPath;
	};

	inline constexpr StandardLibraryEntry StandardLibraryTable[] = {
		// KerML/Semantic
		{"Base", "sysml.library/KerML/Semantic/Base.kerml", "sysml.library.xmi/Kernel Libraries/Kernel Semantic Library/Base.kermlx"},
		{"Clocks", "sysml.library/KerML/Semantic/Clocks.kerml", "sysml.library.xmi/Kernel Libraries/Kernel Semantic Library/Clocks.kermlx"},
		{"ControlPerformances", "sysml.library/KerML/Semantic/ControlPerformances.kerml", "sysml.library.xmi/Kernel Libraries/Kernel Semantic Library/ControlPerformances.kermlx"},
		{"FeatureReferencingPerformances", "sysml.library/KerML/Semantic/FeatureReferencingPerformances.kerml", "sysml.library.xmi/Kernel Libraries/Kernel Semantic Library/FeatureReferencingPerformances.kermlx"},
		{"KerML", "sysml.library/KerML/Semantic/KerML.kerml", "sysml.library.xmi/Kernel Libraries/Kernel Semantic Library/KerML.kermlx"},
		{"Links", "sysml.library/KerML/Semantic/Links.kerml", "sysml.library.xmi/Kernel Libraries/Kernel Semantic Library/Links.kermlx"},
		{"Metaobjects", "sysml.library/KerML/Semantic/Metaobjects.kerml", "sysml.library.xmi/Kernel Libraries/Kernel Semantic Library/Metaobjects.kermlx"},
		{"Objects", "sysml.library/KerML/Semantic/Objects.kerml", "sysml.library.xmi/Kernel Libraries/Kernel Semantic Library/Objects.kermlx"},
		{"Observation", "sysml.library/KerML/Semantic/Observation.kerml", "sysml.library.xmi/Kernel Libraries/Kernel Semantic Library/Observation.kermlx"},
		{"Occurrences", "sysml.library/KerML/Semantic/Occurrences.kerml", "sysml.library.xmi/Kernel Libraries/Kernel Semantic Library/Occurrences.kermlx"},
		{"Performances", "sysml.library/KerML/Semantic/Performances.kerml", "sysml.library.xmi/Kernel Libraries/Kernel Semantic Library/Performances.kermlx"},
		{"SpatialFrames", "sysml.library/KerML/Semantic/SpatialFrames.kerml", "sysml.library.xmi/Kernel Libraries/Kernel Semantic Library/SpatialFrames.kermlx"},
		{"StatePerformances", "sysml.library/KerML/Semantic/StatePerformances.kerml", "sysml.library.xmi/Kernel Libraries/Kernel Semantic Library/StatePerformances.kermlx"},
		{"Transfers", "sysml.library/KerML/Semantic/Transfers.kerml", "sysml.library.xmi/Kernel Libraries/Kernel Semantic Library/Transfers.kermlx"},
		{"TransitionPerformances", "sysml.library/KerML/Semantic/TransitionPerformances.kerml", "sysml.library.xmi/Kernel Libraries/Kernel Semantic Library/TransitionPerformances.kermlx"},
		{"Triggers", "sysml.library/KerML/Semantic/Triggers.kerml", "sysml.library.xmi/Kernel Libraries/Kernel Semantic Library/Triggers.kermlx"},
		// KerML/DataTypes
		{"Collections", "sysml.library/KerML/DataTypes/Collections.kerml", "sysml.library.xmi/Kernel Libraries/Kernel Data Type Library/Collections.kermlx"},
		{"ScalarValues", "sysml.library/KerML/DataTypes/ScalarValues.kerml", "sysml.library.xmi/Kernel Libraries/Kernel Data Type Library/ScalarValues.kermlx"},
		{"VectorValues", "sysml.library/KerML/DataTypes/VectorValues.kerml", "sysml.library.xmi/Kernel Libraries/Kernel Data Type Library/VectorValues.kermlx"},
		// KerML/Function
		{"BaseFunctions", "sysml.library/KerML/Function/BaseFunctions.kerml", "sysml.library.xmi/Kernel Libraries/Kernel Function Library/BaseFunctions.kermlx"},
		{"BooleanFunctions", "sysml.library/KerML/Function/BooleanFunctions.kerml", "sysml.library.xmi/Kernel Libraries/Kernel Function Library/BooleanFunctions.kermlx"},
		{"CollectionFunctions", "sysml.library/KerML/Function/CollectionFunctions.kerml", "sysml.library.xmi/Kernel Libraries/Kernel Function Library/CollectionFunctions.kermlx"},
		{"ComplexFunctions", "sysml.library/KerML/Function/ComplexFunctions.kerml", "sysml.library.xmi/Kernel Libraries/Kernel Function Library/ComplexFunctions.kermlx"},
		{"ControlFunctions", "sysml.library/KerML/Function/ControlFunctions.kerml", "sysml.library.xmi/Kernel Libraries/Kernel Function Library/ControlFunctions.kermlx"},
		{"DataFunctions", "sysml.library/KerML/Function/DataFunctions.kerml", "sysml.library.xmi/Kernel Libraries/Kernel Function Library/DataFunctions.kermlx"},
		{"IntegerFunctions", "sysml.library/KerML/Function/IntegerFunctions.kerml", "sysml.library.xmi/Kernel Libraries/Kernel Function Library/IntegerFunctions.kermlx"},
		{"NaturalFunctions", "sysml.library/KerML/Function/NaturalFunctions.kerml", "sysml.library.xmi/Kernel Libraries/Kernel Function Library/NaturalFunctions.kermlx"},
		{"NumericalFunctions", "sysml.library/KerML/Function/NumericalFunctions.kerml", "sysml.library.xmi/Kernel Libraries/Kernel Function Library/NumericalFunctions.kermlx"},
		{"OccurrenceFunctions", "sysml.library/KerML/Function/OccurrenceFunctions.kerml", "sysml.library.xmi/Kernel Libraries/Kernel Function Library/OccurrenceFunctions.kermlx"},
		{"RationalFunctions", "sysml.library/KerML/Function/RationalFunctions.kerml", "sysml.library.xmi/Kernel Libraries/Kernel Function Library/RationalFunctions.kermlx"},
		{"RealFunctions", "sysml.library/KerML/Function/RealFunctions.kerml", "sysml.library.xmi/Kernel Libraries/Kernel Function Library/RealFunctions.kermlx"},
		{"ScalarFunctions", "sysml.library/KerML/Function/ScalarFunctions.kerml", "sysml.library.xmi/Kernel Libraries/Kernel Function Library/ScalarFunctions.kermlx"},
		{"SequenceFunctions", "sysml.library/KerML/Function/SequenceFunctions.kerml", "sysml.library.xmi/Kernel Libraries/Kernel Function Library/SequenceFunctions.kermlx"},
		{"StringFunctions", "sysml.library/KerML/Function/StringFunctions.kerml", "sysml.library.xmi/Kernel Libraries/Kernel Function Library/StringFunctions.kermlx"},
		{"TrigFunctions", "sysml.library/KerML/Function/TrigFunctions.kerml", "sysml.library.xmi/Kernel Libraries/Kernel Function Library/TrigFunctions.kermlx"},
		{"VectorFunctions", "sysml.library/KerML/Function/VectorFunctions.kerml", "sysml.library.xmi/Kernel Libraries/Kernel Function Library/VectorFunctions.kermlx"},
		// DomainLibraries/Analysis
		{"AnalysisTooling", "sysml.library/DomainLibraries/Analysis/AnalysisTooling.sysml", "sysml.library.xmi/Domain Libraries/Analysis/AnalysisTooling.sysmlx"},
		{"SampledFunctions", "sysml.library/DomainLibraries/Analysis/SampledFunctions.sysml", "sysml.library.xmi/Domain Libraries/Analysis/SampledFunctions.sysmlx"},
		{"StateSpaceRepresentation", "sysml.library/DomainLibraries/Analysis/StateSpaceRepresentation.sysml", "sysml.library.xmi/Domain Libraries/Analysis/StateSpaceRepresentation.sysmlx"},
		{"TradeStudies", "sysml.library/DomainLibraries/Analysis/TradeStudies.sysml", "sysml.library.xmi/Domain Libraries/Analysis/TradeStudies.sysmlx"},
		// DomainLibraries/CauseAndEffect
		{"CausationConnections", "sysml.library/DomainLibraries/CauseAndEffect/CausationConnections.sysml", "sysml.library.xmi/Domain Libraries/Cause and Effect/CausationConnections.sysmlx"},
		{"CauseAndEffect", "sysml.library/DomainLibraries/CauseAndEffect/CauseAndEffect.sysml", "sysml.library.xmi/Domain Libraries/Cause and Effect/CauseAndEffect.sysmlx"},
		// DomainLibraries/Geometry
		{"ShapeItems", "sysml.library/DomainLibraries/Geometry/ShapeItems.sysml", "sysml.library.xmi/Domain Libraries/Geometry/ShapeItems.sysmlx"},
		{"SpatialItems", "sysml.library/DomainLibraries/Geometry/SpatialItems.sysml", "sysml.library.xmi/Domain Libraries/Geometry/SpatialItems.sysmlx"},
		// DomainLibraries/Metadata
		{"ImageMetadata", "sysml.library/DomainLibraries/Metadata/ImageMetadata.sysml", "sysml.library.xmi/Domain Libraries/Metadata/ImageMetadata.sysmlx"},
		{"ModelingMetadata", "sysml.library/DomainLibraries/Metadata/ModelingMetadata.sysml", "sysml.library.xmi/Domain Libraries/Metadata/ModelingMetadata.sysmlx"},
		{"ParametersOfInterestMetadata", "sysml.library/DomainLibraries/Metadata/ParametersOfInterestMetadata.sysml", "sysml.library.xmi/Domain Libraries/Metadata/ParametersOfInterestMetadata.sysmlx"},
		{"RiskMetadata", "sysml.library/DomainLibraries/Metadata/RiskMetadata.sysml", "sysml.library.xmi/Domain Libraries/Metadata/RiskMetadata.sysmlx"},
		// DomainLibraries/QuantitiesAndUnits
		{"ISQ", "sysml.library/DomainLibraries/QuantitiesAndUnits/ISQ.sysml", "sysml.library.xmi/Domain Libraries/Quantities and Units/ISQ.sysmlx"},
		{"ISQAcoustics", "sysml.library/DomainLibraries/QuantitiesAndUnits/ISQAcoustics.sysml", "sysml.library.xmi/Domain Libraries/Quantities and Units/ISQAcoustics.sysmlx"},
		{"ISQAtomicNuclear", "sysml.library/DomainLibraries/QuantitiesAndUnits/ISQAtomicNuclear.sysml", "sysml.library.xmi/Domain Libraries/Quantities and Units/ISQAtomicNuclear.sysmlx"},
		{"ISQBase", "sysml.library/DomainLibraries/QuantitiesAndUnits/ISQBase.sysml", "sysml.library.xmi/Domain Libraries/Quantities and Units/ISQBase.sysmlx"},
		{"ISQCharacteristicNumbers", "sysml.library/DomainLibraries/QuantitiesAndUnits/ISQCharacteristicNumbers.sysml", "sysml.library.xmi/Domain Libraries/Quantities and Units/ISQCharacteristicNumbers.sysmlx"},
		{"ISQChemistryMolecular", "sysml.library/DomainLibraries/QuantitiesAndUnits/ISQChemistryMolecular.sysml", "sysml.library.xmi/Domain Libraries/Quantities and Units/ISQChemistryMolecular.sysmlx"},
		{"ISQCondensedMatter", "sysml.library/DomainLibraries/QuantitiesAndUnits/ISQCondensedMatter.sysml", "sysml.library.xmi/Domain Libraries/Quantities and Units/ISQCondensedMatter.sysmlx"},
		{"ISQElectromagnetism", "sysml.library/DomainLibraries/QuantitiesAndUnits/ISQElectromagnetism.sysml", "sysml.library.xmi/Domain Libraries/Quantities and Units/ISQElectromagnetism.sysmlx"},
		{"ISQInformation", "sysml.library/DomainLibraries/QuantitiesAndUnits/ISQInformation.sysml", "sysml.library.xmi/Domain Libraries/Quantities and Units/ISQInformation.sysmlx"},
		{"ISQLight", "sysml.library/DomainLibraries/QuantitiesAndUnits/ISQLight.sysml", "sysml.library.xmi/Domain Libraries/Quantities and Units/ISQLight.sysmlx"},
		{"ISQMechanics", "sysml.library/DomainLibraries/QuantitiesAndUnits/ISQMechanics.sysml", "sysml.library.xmi/Domain Libraries/Quantities and Units/ISQMechanics.sysmlx"},
		{"ISQSpaceTime", "sysml.library/DomainLibraries/QuantitiesAndUnits/ISQSpaceTime.sysml", "sysml.library.xmi/Domain Libraries/Quantities and Units/ISQSpaceTime.sysmlx"},
		{"ISQThermodynamics", "sysml.library/DomainLibraries/QuantitiesAndUnits/ISQThermodynamics.sysml", "sysml.library.xmi/Domain Libraries/Quantities and Units/ISQThermodynamics.sysmlx"},
		{"MeasurementRefCalculations", "sysml.library/DomainLibraries/QuantitiesAndUnits/MeasurementRefCalculations.sysml", "sysml.library.xmi/Domain Libraries/Quantities and Units/MeasurementRefCalculations.sysmlx"},
		{"MeasurementReferences", "sysml.library/DomainLibraries/QuantitiesAndUnits/MeasurementReferences.sysml", "sysml.library.xmi/Domain Libraries/Quantities and Units/MeasurementReferences.sysmlx"},
		{"QuantityCalculations", "sysml.library/DomainLibraries/QuantitiesAndUnits/QuantityCalculations.sysml", "sysml.library.xmi/Domain Libraries/Quantities and Units/QuantityCalculations.sysmlx"},
		{"Quantities", "sysml.library/DomainLibraries/QuantitiesAndUnits/Quantities.sysml", "sysml.library.xmi/Domain Libraries/Quantities and Units/Quantities.sysmlx"},
		{"SI", "sysml.library/DomainLibraries/QuantitiesAndUnits/SI.sysml", "sysml.library.xmi/Domain Libraries/Quantities and Units/SI.sysmlx"},
		{"SIPrefixes", "sysml.library/DomainLibraries/QuantitiesAndUnits/SIPrefixes.sysml", "sysml.library.xmi/Domain Libraries/Quantities and Units/SIPrefixes.sysmlx"},
		{"TensorCalculations", "sysml.library/DomainLibraries/QuantitiesAndUnits/TensorCalculations.sysml", "sysml.library.xmi/Domain Libraries/Quantities and Units/TensorCalculations.sysmlx"},
		{"Time", "sysml.library/DomainLibraries/QuantitiesAndUnits/Time.sysml", "sysml.library.xmi/Domain Libraries/Quantities and Units/Time.sysmlx"},
		{"USCustomaryUnits", "sysml.library/DomainLibraries/QuantitiesAndUnits/USCustomaryUnits.sysml", "sysml.library.xmi/Domain Libraries/Quantities and Units/USCustomaryUnits.sysmlx"},
		{"VectorCalculations", "sysml.library/DomainLibraries/QuantitiesAndUnits/VectorCalculations.sysml", "sysml.library.xmi/Domain Libraries/Quantities and Units/VectorCalculations.sysmlx"},
		// DomainLibraries/RequirementDerivation
		{"DerivationConnections", "sysml.library/DomainLibraries/RequirementDerivation/DerivationConnections.sysml", "sysml.library.xmi/Domain Libraries/Requirement Derivation/DerivationConnections.sysmlx"},
		{"RequirementDerivation", "sysml.library/DomainLibraries/RequirementDerivation/RequirementDerivation.sysml", "sysml.library.xmi/Domain Libraries/Requirement Derivation/RequirementDerivation.sysmlx"},
		// SystemsLibrary
		{"Actions", "sysml.library/SystemsLibrary/Actions.sysml", "sysml.library.xmi/Systems Library/Actions.sysmlx"},
		{"Allocations", "sysml.library/SystemsLibrary/Allocations.sysml", "sysml.library.xmi/Systems Library/Allocations.sysmlx"},
		{"AnalysisCases", "sysml.library/SystemsLibrary/AnalysisCases.sysml", "sysml.library.xmi/Systems Library/AnalysisCases.sysmlx"},
		{"Attributes", "sysml.library/SystemsLibrary/Attributes.sysml", "sysml.library.xmi/Systems Library/Attributes.sysmlx"},
		{"Calculations", "sysml.library/SystemsLibrary/Calculations.sysml", "sysml.library.xmi/Systems Library/Calculations.sysmlx"},
		{"Cases", "sysml.library/SystemsLibrary/Cases.sysml", "sysml.library.xmi/Systems Library/Cases.sysmlx"},
		{"Connections", "sysml.library/SystemsLibrary/Connections.sysml", "sysml.library.xmi/Systems Library/Connections.sysmlx"},
		{"Constraints", "sysml.library/SystemsLibrary/Constraints.sysml", "sysml.library.xmi/Systems Library/Constraints.sysmlx"},
		{"Flows", "sysml.library/SystemsLibrary/Flows.sysml", "sysml.library.xmi/Systems Library/Flows.sysmlx"},
		{"Interfaces", "sysml.library/SystemsLibrary/Interfaces.sysml", "sysml.library.xmi/Systems Library/Interfaces.sysmlx"},
		{"Items", "sysml.library/SystemsLibrary/Items.sysml", "sysml.library.xmi/Systems Library/Items.sysmlx"},
		{"Metadata", "sysml.library/SystemsLibrary/Metadata.sysml", "sysml.library.xmi/Systems Library/Metadata.sysmlx"},
		{"Parts", "sysml.library/SystemsLibrary/Parts.sysml", "sysml.library.xmi/Systems Library/Parts.sysmlx"},
		{"Ports", "sysml.library/SystemsLibrary/Ports.sysml", "sysml.library.xmi/Systems Library/Ports.sysmlx"},
		{"Requirements", "sysml.library/SystemsLibrary/Requirements.sysml", "sysml.library.xmi/Systems Library/Requirements.sysmlx"},
		{"StandardViewDefinitions", "sysml.library/SystemsLibrary/StandardViewDefinitions.sysml", "sysml.library.xmi/Systems Library/StandardViewDefinitions.sysmlx"},
		{"States", "sysml.library/SystemsLibrary/States.sysml", "sysml.library.xmi/Systems Library/States.sysmlx"},
		{"SysML", "sysml.library/SystemsLibrary/SysML.sysml", "sysml.library.xmi/Systems Library/SysML.sysmlx"},
		{"UseCases", "sysml.library/SystemsLibrary/UseCases.sysml", "sysml.library.xmi/Systems Library/UseCases.sysmlx"},
		{"VerificationCases", "sysml.library/SystemsLibrary/VerificationCases.sysml", "sysml.library.xmi/Systems Library/VerificationCases.sysmlx"},
		{"Views", "sysml.library/SystemsLibrary/Views.sysml", "sysml.library.xmi/Systems Library/Views.sysmlx"},
	};
}
