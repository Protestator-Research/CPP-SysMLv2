include(FetchContent)

FetchContent_Declare(cmrc
    GIT_REPOSITORY https://github.com/vector-of-bool/cmrc.git
    GIT_TAG        952ffddba731fc110bd50409e8d2b8a06abbd237  # Newest Version
)

FetchContent_MakeAvailable(cmrc)

cmrc_add_resource_library(sysmlv2resources
        NAMESPACE Library
        sysml.library/KerML/Semantic/Base.kerml
        sysml.library/KerML/Semantic/Clocks.kerml
        sysml.library/KerML/Semantic/ControlPerformances.kerml
        sysml.library/KerML/Semantic/FeatureReferencingPerformances.kerml
        sysml.library/KerML/Semantic/KerML.kerml
        sysml.library/KerML/Semantic/Links.kerml
        sysml.library/KerML/Semantic/Metaobjects.kerml
        sysml.library/KerML/Semantic/Objects.kerml
        sysml.library/KerML/Semantic/Observation.kerml
        sysml.library/KerML/Semantic/Occurrences.kerml
        sysml.library/KerML/Semantic/Performances.kerml
        sysml.library/KerML/Semantic/SpatialFrames.kerml
        sysml.library/KerML/Semantic/StatePerformances.kerml
        sysml.library/KerML/Semantic/Transfers.kerml
        sysml.library/KerML/Semantic/TransitionPerformances.kerml
        sysml.library/KerML/Semantic/Triggers.kerml

        sysml.library/KerML/DataTypes/Collections.kerml
        sysml.library/KerML/DataTypes/ScalarValues.kerml
        sysml.library/KerML/DataTypes/VectorValues.kerml

        sysml.library/KerML/Function/BaseFunctions.kerml
        sysml.library/KerML/Function/BooleanFunctions.kerml
        sysml.library/KerML/Function/CollectionFunctions.kerml
        sysml.library/KerML/Function/ComplexFunctions.kerml
        sysml.library/KerML/Function/ControlFunctions.kerml
        sysml.library/KerML/Function/DataFunctions.kerml
        sysml.library/KerML/Function/IntegerFunctions.kerml
        sysml.library/KerML/Function/NaturalFunctions.kerml
        sysml.library/KerML/Function/NumericalFunctions.kerml
        sysml.library/KerML/Function/OccurrenceFunctions.kerml
        sysml.library/KerML/Function/RationalFunctions.kerml
        sysml.library/KerML/Function/RealFunctions.kerml
        sysml.library/KerML/Function/ScalarFunctions.kerml
        sysml.library/KerML/Function/SequenceFunctions.kerml
        sysml.library/KerML/Function/StringFunctions.kerml
        sysml.library/KerML/Function/TrigFunctions.kerml
        sysml.library/KerML/Function/VectorFunctions.kerml

        sysml.library/DomainLibraries/Analysis/AnalysisTooling.sysml
        sysml.library/DomainLibraries/Analysis/SampledFunctions.sysml
        sysml.library/DomainLibraries/Analysis/StateSpaceRepresentation.sysml
        sysml.library/DomainLibraries/Analysis/TradeStudies.sysml

        sysml.library/DomainLibraries/CauseAndEffect/CausationConnections.sysml
        sysml.library/DomainLibraries/CauseAndEffect/CauseAndEffect.sysml

        sysml.library/DomainLibraries/Geometry/ShapeItems.sysml
        sysml.library/DomainLibraries/Geometry/SpatialItems.sysml

        sysml.library/DomainLibraries/Metadata/ImageMetadata.sysml
        sysml.library/DomainLibraries/Metadata/ModelingMetadata.sysml
        sysml.library/DomainLibraries/Metadata/ParametersOfInterestMetadata.sysml
        sysml.library/DomainLibraries/Metadata/RiskMetadata.sysml

        sysml.library/DomainLibraries/QuantitiesAndUnits/ISQ.sysml
        sysml.library/DomainLibraries/QuantitiesAndUnits/ISQAcoustics.sysml
        sysml.library/DomainLibraries/QuantitiesAndUnits/ISQAtomicNuclear.sysml
        sysml.library/DomainLibraries/QuantitiesAndUnits/ISQBase.sysml
        sysml.library/DomainLibraries/QuantitiesAndUnits/ISQCharacteristicNumbers.sysml
        sysml.library/DomainLibraries/QuantitiesAndUnits/ISQChemistryMolecular.sysml
        sysml.library/DomainLibraries/QuantitiesAndUnits/ISQCondensedMatter.sysml
        sysml.library/DomainLibraries/QuantitiesAndUnits/ISQElectromagnetism.sysml
        sysml.library/DomainLibraries/QuantitiesAndUnits/ISQInformation.sysml
        sysml.library/DomainLibraries/QuantitiesAndUnits/ISQLight.sysml
        sysml.library/DomainLibraries/QuantitiesAndUnits/ISQMechanics.sysml
        sysml.library/DomainLibraries/QuantitiesAndUnits/ISQSpaceTime.sysml
        sysml.library/DomainLibraries/QuantitiesAndUnits/ISQThermodynamics.sysml
        sysml.library/DomainLibraries/QuantitiesAndUnits/MeasurementRefCalculations.sysml
        sysml.library/DomainLibraries/QuantitiesAndUnits/MeasurementReferences.sysml
        sysml.library/DomainLibraries/QuantitiesAndUnits/QuantityCalculations.sysml
        sysml.library/DomainLibraries/QuantitiesAndUnits/Quantities.sysml
        sysml.library/DomainLibraries/QuantitiesAndUnits/SI.sysml
        sysml.library/DomainLibraries/QuantitiesAndUnits/SIPrefixes.sysml
        sysml.library/DomainLibraries/QuantitiesAndUnits/TensorCalculations.sysml
        sysml.library/DomainLibraries/QuantitiesAndUnits/Time.sysml
        sysml.library/DomainLibraries/QuantitiesAndUnits/USCustomaryUnits.sysml
        sysml.library/DomainLibraries/QuantitiesAndUnits/VectorCalculations.sysml

        sysml.library/DomainLibraries/RequirementDerivation/DerivationConnections.sysml
        sysml.library/DomainLibraries/RequirementDerivation/RequirementDerivation.sysml

        sysml.library/SystemsLibrary/Actions.sysml
        sysml.library/SystemsLibrary/Allocations.sysml
        sysml.library/SystemsLibrary/AnalysisCases.sysml
        sysml.library/SystemsLibrary/Attributes.sysml
        sysml.library/SystemsLibrary/Calculations.sysml
        sysml.library/SystemsLibrary/Cases.sysml
        sysml.library/SystemsLibrary/Connections.sysml
        sysml.library/SystemsLibrary/Constraints.sysml
        sysml.library/SystemsLibrary/Flows.sysml
        sysml.library/SystemsLibrary/Interfaces.sysml
        sysml.library/SystemsLibrary/Items.sysml
        sysml.library/SystemsLibrary/Metadata.sysml
        sysml.library/SystemsLibrary/Parts.sysml
        sysml.library/SystemsLibrary/Ports.sysml
        sysml.library/SystemsLibrary/Requirements.sysml
        sysml.library/SystemsLibrary/StandardViewDefinitions.sysml
        sysml.library/SystemsLibrary/States.sysml
        sysml.library/SystemsLibrary/SysML.sysml
        sysml.library/SystemsLibrary/UseCases.sysml
        sysml.library/SystemsLibrary/VerificationCases.sysml
        sysml.library/SystemsLibrary/Views.sysml)

# The XMI serialization of the standard library (release of the pilot implementation), separate from sysmlv2resources so that users of the text
# do not link the XMI as well. The paths contain blanks and are quoted.
cmrc_add_resource_library(sysmlv2xmiresources
        NAMESPACE LibraryXmi
        "sysml.library.xmi/Domain Libraries/Analysis/AnalysisTooling.sysmlx"
        "sysml.library.xmi/Domain Libraries/Analysis/SampledFunctions.sysmlx"
        "sysml.library.xmi/Domain Libraries/Analysis/StateSpaceRepresentation.sysmlx"
        "sysml.library.xmi/Domain Libraries/Analysis/TradeStudies.sysmlx"

        "sysml.library.xmi/Domain Libraries/Cause and Effect/CausationConnections.sysmlx"
        "sysml.library.xmi/Domain Libraries/Cause and Effect/CauseAndEffect.sysmlx"

        "sysml.library.xmi/Domain Libraries/Geometry/ShapeItems.sysmlx"
        "sysml.library.xmi/Domain Libraries/Geometry/SpatialItems.sysmlx"

        "sysml.library.xmi/Domain Libraries/Metadata/ImageMetadata.sysmlx"
        "sysml.library.xmi/Domain Libraries/Metadata/ModelingMetadata.sysmlx"
        "sysml.library.xmi/Domain Libraries/Metadata/ParametersOfInterestMetadata.sysmlx"
        "sysml.library.xmi/Domain Libraries/Metadata/RiskMetadata.sysmlx"

        "sysml.library.xmi/Domain Libraries/Quantities and Units/ISQ.sysmlx"
        "sysml.library.xmi/Domain Libraries/Quantities and Units/ISQAcoustics.sysmlx"
        "sysml.library.xmi/Domain Libraries/Quantities and Units/ISQAtomicNuclear.sysmlx"
        "sysml.library.xmi/Domain Libraries/Quantities and Units/ISQBase.sysmlx"
        "sysml.library.xmi/Domain Libraries/Quantities and Units/ISQCharacteristicNumbers.sysmlx"
        "sysml.library.xmi/Domain Libraries/Quantities and Units/ISQChemistryMolecular.sysmlx"
        "sysml.library.xmi/Domain Libraries/Quantities and Units/ISQCondensedMatter.sysmlx"
        "sysml.library.xmi/Domain Libraries/Quantities and Units/ISQElectromagnetism.sysmlx"
        "sysml.library.xmi/Domain Libraries/Quantities and Units/ISQInformation.sysmlx"
        "sysml.library.xmi/Domain Libraries/Quantities and Units/ISQLight.sysmlx"
        "sysml.library.xmi/Domain Libraries/Quantities and Units/ISQMechanics.sysmlx"
        "sysml.library.xmi/Domain Libraries/Quantities and Units/ISQSpaceTime.sysmlx"
        "sysml.library.xmi/Domain Libraries/Quantities and Units/ISQThermodynamics.sysmlx"
        "sysml.library.xmi/Domain Libraries/Quantities and Units/MeasurementRefCalculations.sysmlx"
        "sysml.library.xmi/Domain Libraries/Quantities and Units/MeasurementReferences.sysmlx"
        "sysml.library.xmi/Domain Libraries/Quantities and Units/Quantities.sysmlx"
        "sysml.library.xmi/Domain Libraries/Quantities and Units/QuantityCalculations.sysmlx"
        "sysml.library.xmi/Domain Libraries/Quantities and Units/SI.sysmlx"
        "sysml.library.xmi/Domain Libraries/Quantities and Units/SIPrefixes.sysmlx"
        "sysml.library.xmi/Domain Libraries/Quantities and Units/TensorCalculations.sysmlx"
        "sysml.library.xmi/Domain Libraries/Quantities and Units/Time.sysmlx"
        "sysml.library.xmi/Domain Libraries/Quantities and Units/USCustomaryUnits.sysmlx"
        "sysml.library.xmi/Domain Libraries/Quantities and Units/VectorCalculations.sysmlx"

        "sysml.library.xmi/Domain Libraries/Requirement Derivation/DerivationConnections.sysmlx"
        "sysml.library.xmi/Domain Libraries/Requirement Derivation/RequirementDerivation.sysmlx"

        "sysml.library.xmi/Kernel Libraries/Kernel Data Type Library/Collections.kermlx"
        "sysml.library.xmi/Kernel Libraries/Kernel Data Type Library/ScalarValues.kermlx"
        "sysml.library.xmi/Kernel Libraries/Kernel Data Type Library/VectorValues.kermlx"

        "sysml.library.xmi/Kernel Libraries/Kernel Function Library/BaseFunctions.kermlx"
        "sysml.library.xmi/Kernel Libraries/Kernel Function Library/BooleanFunctions.kermlx"
        "sysml.library.xmi/Kernel Libraries/Kernel Function Library/CollectionFunctions.kermlx"
        "sysml.library.xmi/Kernel Libraries/Kernel Function Library/ComplexFunctions.kermlx"
        "sysml.library.xmi/Kernel Libraries/Kernel Function Library/ControlFunctions.kermlx"
        "sysml.library.xmi/Kernel Libraries/Kernel Function Library/DataFunctions.kermlx"
        "sysml.library.xmi/Kernel Libraries/Kernel Function Library/IntegerFunctions.kermlx"
        "sysml.library.xmi/Kernel Libraries/Kernel Function Library/NaturalFunctions.kermlx"
        "sysml.library.xmi/Kernel Libraries/Kernel Function Library/NumericalFunctions.kermlx"
        "sysml.library.xmi/Kernel Libraries/Kernel Function Library/OccurrenceFunctions.kermlx"
        "sysml.library.xmi/Kernel Libraries/Kernel Function Library/RationalFunctions.kermlx"
        "sysml.library.xmi/Kernel Libraries/Kernel Function Library/RealFunctions.kermlx"
        "sysml.library.xmi/Kernel Libraries/Kernel Function Library/ScalarFunctions.kermlx"
        "sysml.library.xmi/Kernel Libraries/Kernel Function Library/SequenceFunctions.kermlx"
        "sysml.library.xmi/Kernel Libraries/Kernel Function Library/StringFunctions.kermlx"
        "sysml.library.xmi/Kernel Libraries/Kernel Function Library/TrigFunctions.kermlx"
        "sysml.library.xmi/Kernel Libraries/Kernel Function Library/VectorFunctions.kermlx"

        "sysml.library.xmi/Kernel Libraries/Kernel Semantic Library/Base.kermlx"
        "sysml.library.xmi/Kernel Libraries/Kernel Semantic Library/Clocks.kermlx"
        "sysml.library.xmi/Kernel Libraries/Kernel Semantic Library/ControlPerformances.kermlx"
        "sysml.library.xmi/Kernel Libraries/Kernel Semantic Library/FeatureReferencingPerformances.kermlx"
        "sysml.library.xmi/Kernel Libraries/Kernel Semantic Library/KerML.kermlx"
        "sysml.library.xmi/Kernel Libraries/Kernel Semantic Library/Links.kermlx"
        "sysml.library.xmi/Kernel Libraries/Kernel Semantic Library/Metaobjects.kermlx"
        "sysml.library.xmi/Kernel Libraries/Kernel Semantic Library/Objects.kermlx"
        "sysml.library.xmi/Kernel Libraries/Kernel Semantic Library/Observation.kermlx"
        "sysml.library.xmi/Kernel Libraries/Kernel Semantic Library/Occurrences.kermlx"
        "sysml.library.xmi/Kernel Libraries/Kernel Semantic Library/Performances.kermlx"
        "sysml.library.xmi/Kernel Libraries/Kernel Semantic Library/SpatialFrames.kermlx"
        "sysml.library.xmi/Kernel Libraries/Kernel Semantic Library/StatePerformances.kermlx"
        "sysml.library.xmi/Kernel Libraries/Kernel Semantic Library/Transfers.kermlx"
        "sysml.library.xmi/Kernel Libraries/Kernel Semantic Library/TransitionPerformances.kermlx"
        "sysml.library.xmi/Kernel Libraries/Kernel Semantic Library/Triggers.kermlx"

        "sysml.library.xmi/Systems Library/Actions.sysmlx"
        "sysml.library.xmi/Systems Library/Allocations.sysmlx"
        "sysml.library.xmi/Systems Library/AnalysisCases.sysmlx"
        "sysml.library.xmi/Systems Library/Attributes.sysmlx"
        "sysml.library.xmi/Systems Library/Calculations.sysmlx"
        "sysml.library.xmi/Systems Library/Cases.sysmlx"
        "sysml.library.xmi/Systems Library/Connections.sysmlx"
        "sysml.library.xmi/Systems Library/Constraints.sysmlx"
        "sysml.library.xmi/Systems Library/Flows.sysmlx"
        "sysml.library.xmi/Systems Library/Interfaces.sysmlx"
        "sysml.library.xmi/Systems Library/Items.sysmlx"
        "sysml.library.xmi/Systems Library/Metadata.sysmlx"
        "sysml.library.xmi/Systems Library/Parts.sysmlx"
        "sysml.library.xmi/Systems Library/Ports.sysmlx"
        "sysml.library.xmi/Systems Library/Requirements.sysmlx"
        "sysml.library.xmi/Systems Library/StandardViewDefinitions.sysmlx"
        "sysml.library.xmi/Systems Library/States.sysmlx"
        "sysml.library.xmi/Systems Library/SysML.sysmlx"
        "sysml.library.xmi/Systems Library/UseCases.sysmlx"
        "sysml.library.xmi/Systems Library/VerificationCases.sysmlx"
        "sysml.library.xmi/Systems Library/Views.sysmlx")

include(GNUInstallDirs)
install(TARGETS sysmlv2resources ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(TARGETS sysmlv2resources RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(TARGETS sysmlv2xmiresources ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(TARGETS sysmlv2xmiresources RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})