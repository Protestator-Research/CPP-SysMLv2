cmake_minimum_required(VERSION 3.15)

project(kerml CXX C)

set(GLOBAL_HEADER
        include/kerml/kerml_global.h)

set(ROOT_ELEMENTS_HEADER
        include/kerml/root/elements/Element.h
        include/kerml/root/elements/Relationship.h)

set(ROOT_DEPENDENCIES_HEADER
        include/kerml/root/dependencies/Dependency.h)

set(ROOT_ANNOTATIONS_HEADER
        include/kerml/root/annotations/AnnotatingElement.h
        include/kerml/root/annotations/Annotation.h
        include/kerml/root/annotations/Comment.h
        include/kerml/root/annotations/Documentation.h
        include/kerml/root/annotations/TextualRepresentation.h)

set(ROOT_NAMESPACES_HEADER
        include/kerml/root/namespaces/Namespace.h
        include/kerml/root/namespaces/VisibilityKind.h
        include/kerml/root/namespaces/Membership.h
        include/kerml/root/namespaces/OwningMembership.h
        include/kerml/root/namespaces/Import.h
        include/kerml/root/namespaces/MembershipImport.h
        include/kerml/root/namespaces/NamespaceImport.h)

set(CORE_TYPES_HEADER
        include/kerml/core/types/Type.h
        include/kerml/core/types/Specialization.h
        include/kerml/core/types/Conjugation.h
        include/kerml/core/types/Disjoining.h
        include/kerml/core/types/Unioning.h
        include/kerml/core/types/Intersecting.h
        include/kerml/core/types/Differencing.h)

set(CORE_CLASSIFIER_HEADER
        include/kerml/core/classifiers/Classifier.h
        include/kerml/core/classifiers/Subclassification.h)

set(CORE_FEATURES_HEADER
        include/kerml/core/features/TypeFeaturing.h
        include/kerml/core/features/FeatureDirectionKind.h
        include/kerml/core/features/Feature.h
        include/kerml/core/features/Multiplicity.h
        include/kerml/core/features/FeatureInverting.h
        include/kerml/core/features/Subsetting.h
        include/kerml/core/features/FeatureTyping.h
        include/kerml/core/features/Featuring.h
        include/kerml/core/features/Redefinition.h
        include/kerml/core/features/ReferenceSubsetting.h
        include/kerml/core/features/FeatureChaining.h
        include/kerml/core/features/FeatureMembership.h
        include/kerml/core/features/EndFeatureMembership.h
        include/kerml/core/features/CrossSubsetting.h)

set(KERNEL_DATATYPES_HEADER
        include/kerml/kernel/datatypes/DataType.h)

set(KERNEL_CLASSES_HEADER
        include/kerml/kernel/classes/Class.h)

set(KERNEL_STRUCTURES_HEADER
        include/kerml/kernel/structures/Structure.h)

set(KERNEL_ASSOCIATIONS_HEADER
        include/kerml/kernel/assiciations/Association.h
        include/kerml/kernel/assiciations/AssociationStructure.h)

set(KERNEL_CONNECTORS_HEADER
        include/kerml/kernel/connectors/ParameterMembership.h
        include/kerml/kernel/connectors/BindingConnector.h
        include/kerml/kernel/connectors/Succession.h
        include/kerml/kernel/connectors/Expression.h)

set(KERNEL_FEATUREVALUES_HEADER
        include/kerml/kernel/featurevalues/FeatureValue.h)

set(KERNEL_FUNCTIONS_HEADER
        include/kerml/kernel/functions/Function.h
        include/kerml/kernel/functions/Expression.h
        include/kerml/kernel/functions/Predicate.h
        include/kerml/kernel/functions/BooleanExpression.h
        include/kerml/kernel/functions/Invariant.h
        include/kerml/kernel/functions/ParameterMembership.h
        include/kerml/kernel/functions/ReturnParameterMembership.h
        include/kerml/kernel/functions/ResultExpressionMembersip.h)

set(KERNEL_METADATA_HEADER
        include/kerml/kernel/metadata/MetadataFeature.h)

set(KERNEL_EXPRESSIONS_HEADER
        include/kerml/kernel/expressions/InvocationExpression.h
        include/kerml/kernel/expressions/FeatureChainExpression.h
        include/kerml/kernel/expressions/CollectExpression.h
        include/kerml/kernel/expressions/SelectExpression.h
        include/kerml/kernel/expressions/LiteralString.h
        include/kerml/kernel/expressions/LiteralBoolean.h
        include/kerml/kernel/expressions/LiteralRational.h
        include/kerml/kernel/expressions/LiteralInfinity.h
        include/kerml/kernel/expressions/Expression.h
        include/kerml/kernel/expressions/NullExpression.h
        include/kerml/kernel/expressions/LiteralExpression.h
        include/kerml/kernel/expressions/FeatureReferenceExpression.h
        include/kerml/kernel/expressions/MetadataAccessExpression.h
        include/kerml/kernel/expressions/OperatorExpression.h
        include/kerml/kernel/expressions/LiteralInteger.h)

set(KERNEL_INTERACTIONS_HEADER
        include/kerml/kernel/interactions/Interaction.h
        include/kerml/kernel/interactions/ItemFeature.h
        include/kerml/kernel/interactions/ItemFlowEnd.h
        include/kerml/kernel/interactions/ItemFlow.h
        include/kerml/kernel/interactions/SuccessionItemFlow.h)

set(KERNEL_MULTIPLICITIES_HEADER
        include/kerml/kernel/multiplicities/MultiplicityRange.h)

set(KERNEL_PACKAGE_HEADER
        include/kerml/kernel/packages/Package.h
        include/kerml/kernel/packages/LibraryPackage.h
        include/kerml/kernel/packages/ElementFilterMembership.h)


set(KERNEL_BEHAVIORS_HEADER
        include/kerml/kernel/behaviors/Step.h
        include/kerml/kernel/behaviors/Behavior.h)

add_library(kerml
        ${GLOBAL_HEADER}
        ${ROOT_ELEMENTS_HEADER}
        ${ROOT_DEPENDENCIES_HEADER}
        ${ROOT_ANNOTATIONS_HEADER}
        ${ROOT_NAMESPACES_HEADER}
        ${CORE_TYPES_HEADER}
        ${CORE_CLASSIFIER_HEADER}
        ${CORE_FEATURES_HEADER}
        ${KERNEL_DATATYPES_HEADER}
        ${KERNEL_CLASSES_HEADER}
        ${KERNEL_STRUCTURES_HEADER}
        ${KERNEL_ASSOCIATIONS_HEADER}
        ${KERNEL_CONNECTORS_HEADER}
        ${KERNEL_FEATUREVALUES_HEADER}
        ${KERNEL_FUNCTIONS_HEADER}
        ${KERNEL_METADATA_HEADER}
        ${KERNEL_EXPRESSIONS_HEADER}
        ${KERNEL_INTERACTIONS_HEADER}
        ${KERNEL_MULTIPLICITIES_HEADER}
        ${KERNEL_PACKAGE_HEADER}
        ${KERNEL_BEHAVIORS_HEADER}
        src/kerml/root/elements/Element.cpp
        src/kerml/root/elements/Relationship.cpp
        src/kerml/root/dependencies/Dependency.cpp
        src/kerml/root/annotations/AnnotatingElement.cpp
        src/kerml/root/annotations/Annotation.cpp
        src/kerml/root/annotations/Comment.cpp
        src/kerml/root/annotations/Documentation.cpp
        src/kerml/root/annotations/TextualRepresentation.cpp
        src/kerml/root/namespaces/Namespace.cpp
        src/kerml/root/namespaces/Membership.cpp
        src/kerml/root/namespaces/OwningMembership.cpp
        src/kerml/root/namespaces/NamespaceImport.cpp
        src/kerml/root/namespaces/MembershipImport.cpp
        src/kerml/root/namespaces/Import.cpp
        src/kerml/core/types/Type.cpp
        src/kerml/core/types/Specialization.cpp
        src/kerml/core/types/Conjugation.cpp
        src/kerml/core/types/Disjoining.cpp
        src/kerml/core/types/Unioning.cpp
        src/kerml/core/types/Intersecting.cpp
        src/kerml/core/types/Differencing.cpp
        src/kerml/core/classifiers/Classifier.cpp
        src/kerml/core/features/TypeFeaturing.cpp
        src/kerml/core/features/Feature.cpp
        src/kerml/core/features/Multiplicity.cpp
        src/kerml/core/features/FeatureInverting.cpp
        src/kerml/core/classifiers/Subclassification.cpp
        src/kerml/core/features/FeatureTyping.cpp
        src/kerml/core/features/Featuring.cpp
        src/kerml/core/features/Subsetting.cpp
        src/kerml/core/features/Redefinition.cpp
        src/kerml/core/features/ReferenceSubsetting.cpp
        src/kerml/core/features/FeatureChaining.cpp
        src/kerml/core/features/FeatureMembership.cpp
        src/kerml/core/features/EndFeatureMembership.cpp
        src/kerml/core/features/CrossSubsetting.cpp
        src/kerml/kernel/datatypes/DataType.cpp
        src/kerml/kernel/classes/Class.cpp
        src/kerml/kernel/associations/Association.cpp
        src/kerml/kernel/structures/Structure.cpp
        src/kerml/kernel/associations/AssociationStructure.cpp
        src/kerml/kernel/packages/Package.cpp
        src/kerml/kernel/packages/LibraryPackage.cpp
        src/kerml/kernel/packages/ElementFilterMembership.cpp
        src/kerml/kernel/multiplicities/MultiplicityRange.cpp
        src/kerml/kernel/interactions/Interaction.cpp
        src/kerml/kernel/interactions/ItemFeature.cpp
        src/kerml/kernel/interactions/ItemFlowEnd.cpp
        src/kerml/kernel/expressions/InvocationExpression.cpp
        src/kerml/kernel/expressions/FeatureChainExpression.cpp
        src/kerml/kernel/expressions/CollectExpression.cpp
        src/kerml/kernel/expressions/SelectExpression.cpp
        src/kerml/kernel/expressions/LiteralString.cpp
        src/kerml/kernel/expressions/LiteralBoolean.cpp
        src/kerml/kernel/expressions/LiteralRational.cpp
        src/kerml/kernel/expressions/LiteralInfinity.cpp
        src/kerml/kernel/expressions/Expression.cpp
        src/kerml/kernel/expressions/NullExpression.cpp
        src/kerml/kernel/expressions/LiteralExpression.cpp
        src/kerml/kernel/expressions/FeatureReferenceExpression.cpp
        src/kerml/kernel/expressions/MetadataAccessExpression.cpp
        src/kerml/kernel/expressions/OperatorExpression.cpp
        src/kerml/kernel/expressions/LiteralInteger.cpp
        src/kerml/kernel/connectors/ParameterMembership.cpp
        src/kerml/kernel/connectors/Succession.cpp
        src/kerml/kernel/connectors/BindingConnector.cpp
        src/kerml/kernel/connectors/Expression.cpp
        src/kerml/kernel/metadata/MetadataFeature.cpp
        src/kerml/kernel/featurevalues/FeatureValue.cpp
        src/kerml/kernel/interactions/SuccessionItemFlow.cpp
        src/kerml/kernel/interactions/ItemFlow.cpp
        src/kerml/kernel/functions/Function.cpp
        src/kerml/kernel/functions/Expression.cpp
        src/kerml/kernel/functions/Predicate.cpp
        src/kerml/kernel/functions/BooleanExpression.cpp
        src/kerml/kernel/functions/Invariant.cpp
        src/kerml/kernel/functions/ParameterMembership.cpp
        src/kerml/kernel/functions/ReturnParameterMembership.cpp
        src/kerml/kernel/functions/ResultExpressionMembersip.cpp
        src/kerml/kernel/behaviors/Step.cpp
        src/kerml/kernel/behaviors/Behavior.cpp)

target_link_libraries(kerml PRIVATE
        boost::boost
        nlohmann_json::nlohmann_json
        date::date
        sysmlv2interfaces)


include(GNUInstallDirs)
install(TARGETS kerml ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(TARGETS kerml RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(FILES ${ROOT_ELEMENTS_HEADER} DESTINATION include/kerml/root/elements)
install(FILES ${ROOT_DEPENDENCIES_HEADER} DESTINATION include/kerml/root/dependencies)
install(FILES ${ROOT_ANNOTATIONS_HEADER} DESTINATION include/kerml/root/annotations)
install(FILES ${ROOT_NAMESPACES_HEADER} DESTINATION include/kerml/root/namespaces)
install(FILES ${CORE_TYPES_HEADER} DESTINATION include/kerml/core/types)
install(FILES ${CORE_CLASSIFIER_HEADER} DESTINATION include/kerml/core/classifiers)
install(FILES ${CORE_FEATURES_HEADER} DESTINATION include/kerml/core/features)
install(FILES ${KERNEL_DATATYPES_HEADER} DESTINATION include/kerml/kernel/datatypes)
install(FILES ${KERNEL_CLASSES_HEADER} DESTINATION include/kerml/kernel/classes)
install(FILES ${KERNEL_STRUCTURES_HEADER} DESTINATION include/kerml/kernel/structures)
install(FILES ${KERNEL_ASSOCIATIONS_HEADER} DESTINATION include/kerml/kernel/associations)
install(FILES ${KERNEL_CONNECTORS_HEADER} DESTINATION include/kerml/kernel/connectors)
install(FILES ${KERNEL_FEATUREVALUES_HEADER} DESTINATION include/kerml/kernel/featurevalues)
install(FILES ${KERNEL_FUNCTIONS_HEADER} DESTINATION include/kerml/kernel/functions)
install(FILES ${KERNEL_METADATA_HEADER} DESTINATION include/kerml/kernel/metadata)
install(FILES ${KERNEL_EXPRESSIONS_HEADER} DESTINATION include/kerml/kernel/expressions)
install(FILES ${KERNEL_INTERACTIONS_HEADER} DESTINATION include/kerml/kernel/interactions)
install(FILES ${KERNEL_MULTIPLICITIES_HEADER} DESTINATION include/kerml/kernel/multiplicities)
install(FILES ${KERNEL_PACKAGE_HEADER} DESTINATION include/kerml/kernel/packages)
install(FILES ${KERNEL_BEHAVIORS_HEADER} DESTINATION include/kerml/kernel/behaviors)
install(FILES ${GLOBAL_HEADER} DESTINATION include/kerml)


if(MSVC)
    target_compile_options(kerml PRIVATE /W4 /WX- /bigobj)
    target_link_directories(kerml PUBLIC ${CMAKE_BINARY_DIR}/out)
    target_include_directories(kerml PUBLIC
            ./include
            ../sysmlinterfaces/include)
else ()
    target_compile_options(kerml PRIVATE -Wall -Wextra -Wpedantic -Werror)
    target_include_directories(kerml PUBLIC
            ./include
            ../sysmlinterfaces/include)
endif()

file(GLOB_RECURSE _source_list *.cpp* *.h* *.hpp*)
foreach(_source IN ITEMS ${_source_list})
    get_filename_component(_source_path "${_source}" PATH)
    string(REPLACE "${CMAKE_SOURCE_DIR}" "" _group_path "${_source_path}")
    string(REPLACE "/" "\\" _group_path "${_group_path}")
    source_group("${_group_path}" FILES "${_source}")
endforeach()

if(RUN_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()