cmake_minimum_required(VERSION 3.15)

project(kerml CXX C)

set(GLOBAL_HEADER
        src/kerml_global.h)

set(ROOT_ELEMENTS_HEADER
        src/root/elements/Element.h
        src/root/elements/Relationship.h)

set(ROOT_DEPENDENCIES_HEADER
        src/root/dependencies/Dependency.h)

set(ROOT_ANNOTATIONS_HEADER
        src/root/annotations/AnnotatingElement.h
        src/root/annotations/Annotation.h
        src/root/annotations/Comment.h
        src/root/annotations/Documentation.h
        src/root/annotations/TextualRepresentation.h)

set(ROOT_NAMESPACES_HEADER
        src/root/namespaces/Namespace.h
        src/root/namespaces/VisibilityKind.h
        src/root/namespaces/Membership.h
        src/root/namespaces/OwningMembership.h
        src/root/namespaces/Import.h
        src/root/namespaces/MembershipImport.h
        src/root/namespaces/NamespaceImport.h)

set(CORE_TYPES_HEADER
        src/core/types/Type.h
        src/core/types/Specialization.h
        src/core/types/Conjunction.h
        src/core/types/Disjoining.h
        src/core/types/Unioning.h
        src/core/types/Intersecting.h
        src/core/types/Differencing.h)

set(CORE_CLASSIFIER_HEADER
        src/core/classifiers/Classifier.h
        src/core/classifiers/Subclassification.h)

set(CORE_FEATURES_HEADER
        src/core/features/TypeFeaturing.h
        src/core/features/FeatureDirectionKind.h
        src/core/features/Feature.h
        src/core/features/FeatureInverting.h
        src/core/features/Subsetting.h
        src/core/features/FeatureTyping.h
        src/core/features/Featuring.h
        src/core/features/Redefinition.h
        src/core/features/ReferenceSubsetting.h
        src/core/features/FeatureChaining.h
        src/core/features/FeatureMembership.h
        src/core/features/EndFeatureMembership.h)

set(KERNEL_DATATYPES_HEADER
        src/kernel/datatypes/DataType.h)

set(KERNEL_CLASSES_HEADER
        src/kernel/classes/Class.h)

set(KERNEL_STRUCTURES_HEADER
        src/kernel/structures/Structure.h)

set(KERNEL_ASSOCIATIONS_HEADER
        src/kernel/associations/Association.h
        src/kernel/associations/AssociationStructure.h)

set(KERNEL_CONNECTORS_HEADER
        src/kernel/connectors/ParameterMembership.h
        src/kernel/connectors/BindingConnector.h
        src/kernel/connectors/Succession.h
        src/kernel/connectors/Expression.h)

set(KERNEL_FEATUREVALUES_HEADER
        src/kernel/featurevalues/FeatureValue.h)

set(KERNEL_FUNCTIONS_HEADER
        src/kernel/functions/Function.h
        src/kernel/functions/Expression.h
        src/kernel/functions/Predicate.h
        src/kernel/functions/BooleanExpression.h
        src/kernel/functions/Invariant.h
        src/kernel/functions/ParameterMembership.h
        src/kernel/functions/ReturnParameterMembership.h
        src/kernel/functions/ResultExpressionMembersip.h)

set(KERNEL_METADATA_HEADER
        src/kernel/metadata/MetadataFeature.h)

set(KERNEL_EXPRESSIONS_HEADER
        src/kernel/expressions/InvocationExpression.h
        src/kernel/expressions/FeatureChainExpression.h
        src/kernel/expressions/CollectExpression.h
        src/kernel/expressions/SelectExpression.h
        src/kernel/expressions/LiteralString.h
        src/kernel/expressions/LiteralBoolean.h
        src/kernel/expressions/LiteralRational.h
        src/kernel/expressions/LiteralInfinity.h
        src/kernel/expressions/Expression.h
        src/kernel/expressions/NullExpression.h
        src/kernel/expressions/LiteralExpression.h
        src/kernel/expressions/FeatureReferenceExpression.h
        src/kernel/expressions/MetadataAccessExpression.h
        src/kernel/expressions/OperatorExpression.h
        src/kernel/expressions/LiteralInteger.h)

set(KERNEL_INTERACTIONS_HEADER
        src/kernel/interactions/Interaction.h
        src/kernel/interactions/ItemFeature.h
        src/kernel/interactions/ItemFlowEnd.h
        src/kernel/interactions/ItemFlow.h
        src/kernel/interactions/SuccessionItemFlow.h)

set(KERNEL_MULTIPLICITIES_HEADER
        src/kernel/multiplicities/MultiplicityRange.h)

set(KERNEL_PACKAGE_HEADER
        src/kernel/packages/Package.h
        src/kernel/packages/LibraryPackage.h
        src/kernel/packages/ElementFilterMembership.h)


set(KERNEL_BEHAVIORS_HEADER
        src/kernel/behaviors/Step.h
        src/kernel/behaviors/Behavior.h)

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
        src/root/elements/Element.cpp
        src/root/elements/Relationship.cpp
        src/root/dependencies/Dependency.cpp
        src/root/annotations/AnnotatingElement.cpp
        src/root/annotations/Annotation.cpp
        src/root/annotations/Comment.cpp
        src/root/annotations/Documentation.cpp
        src/root/annotations/TextualRepresentation.cpp
        src/root/namespaces/Namespace.cpp
        src/root/namespaces/Membership.cpp
        src/root/namespaces/OwningMembership.cpp
        src/root/namespaces/NamespaceImport.cpp
        src/root/namespaces/MembershipImport.cpp
        src/root/namespaces/Import.cpp
        src/core/types/Type.cpp
        src/core/types/Specialization.cpp
        src/core/types/Conjunction.cpp
        src/core/types/Disjoining.cpp
        src/core/types/Unioning.cpp
        src/core/types/Intersecting.cpp
        src/core/types/Differencing.cpp
        src/core/classifiers/Classifier.cpp
        src/core/features/TypeFeaturing.cpp
        src/core/features/Feature.cpp
        src/core/features/FeatureInverting.cpp
        src/core/classifiers/Subclassification.cpp
        src/core/features/FeatureTyping.cpp
        src/core/features/Featuring.cpp
        src/core/features/Subsetting.cpp
        src/core/features/Redefinition.cpp
        src/core/features/ReferenceSubsetting.cpp
        src/core/features/FeatureChaining.cpp
        src/core/features/FeatureMembership.cpp
        src/core/features/EndFeatureMembership.cpp
        src/kernel/datatypes/DataType.cpp
        src/kernel/classes/Class.cpp
        src/kernel/associations/Association.cpp
        src/kernel/structures/Structure.cpp
        src/kernel/associations/AssociationStructure.cpp
        src/kernel/packages/Package.cpp
        src/kernel/packages/LibraryPackage.cpp
        src/kernel/packages/ElementFilterMembership.cpp
        src/kernel/multiplicities/MultiplicityRange.cpp
        src/kernel/interactions/Interaction.cpp
        src/kernel/interactions/ItemFeature.cpp
        src/kernel/interactions/ItemFlowEnd.cpp
        src/kernel/expressions/InvocationExpression.cpp
        src/kernel/expressions/FeatureChainExpression.cpp
        src/kernel/expressions/CollectExpression.cpp
        src/kernel/expressions/SelectExpression.cpp
        src/kernel/expressions/LiteralString.cpp
        src/kernel/expressions/LiteralBoolean.cpp
        src/kernel/expressions/LiteralRational.cpp
        src/kernel/expressions/LiteralInfinity.cpp
        src/kernel/expressions/Expression.cpp
        src/kernel/expressions/NullExpression.cpp
        src/kernel/expressions/LiteralExpression.cpp
        src/kernel/expressions/FeatureReferenceExpression.cpp
        src/kernel/expressions/MetadataAccessExpression.cpp
        src/kernel/expressions/OperatorExpression.cpp
        src/kernel/expressions/LiteralInteger.cpp
        src/kernel/connectors/ParameterMembership.cpp
        src/kernel/connectors/Succession.cpp
        src/kernel/connectors/BindingConnector.cpp
        src/kernel/connectors/Expression.cpp
        src/kernel/metadata/MetadataFeature.cpp
        src/kernel/featurevalues/FeatureValue.cpp
        src/kernel/interactions/SuccessionItemFlow.cpp
        src/kernel/interactions/ItemFlow.cpp
        src/kernel/functions/Function.cpp
        src/kernel/functions/Expression.cpp
        src/kernel/functions/Predicate.cpp
        src/kernel/functions/BooleanExpression.cpp
        src/kernel/functions/Invariant.cpp
        src/kernel/functions/ParameterMembership.cpp
        src/kernel/functions/ReturnParameterMembership.cpp
        src/kernel/functions/ResultExpressionMembersip.cpp
        src/kernel/behaviors/Step.cpp
        src/kernel/behaviors/Behavior.cpp)

target_link_libraries(kerml PRIVATE
        boost::boost
        nlohmann_json::nlohmann_json
        date::date)


include(GNUInstallDirs)
install(TARGETS kerml ARCHIVE DESTINATION lib)
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

target_include_directories(kerml PRIVATE ./src/)

if(MSVC)
    target_compile_options(kerml PRIVATE /W4 /WX- /bigobj)
else ()
    target_compile_options(kerml PRIVATE -Wall -Wextra -Wpedantic -Werror)
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