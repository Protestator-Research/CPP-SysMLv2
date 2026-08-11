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
        sysml.library/SystemsLibrary/Views.sysml
)

include(GNUInstallDirs)
install(TARGETS sysmlv2resources ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(TARGETS sysmlv2resources RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})