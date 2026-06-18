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
)

include(GNUInstallDirs)
install(TARGETS sysmlv2resources ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(TARGETS sysmlv2resources RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})