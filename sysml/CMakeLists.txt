cmake_minimum_required(VERSION 3.15)

project(sysml CXX C)

set(GLOBAL_HEADER
        include/sysml/sysml_global.h)

set(USAGE_HEADER
        include/sysml/usage/Definition.h
        include/sysml/usage/Usage.h
        include/sysml/usage/ReferenceUsage.h
        include/sysml/usage/VariantMembership.h)

set(ATTRIBUTIONS_HEADER
        include/sysml/attibutes/AttributeDefinition.h
        include/sysml/attibutes/AttributeUsage.h)

#set(ROOT_ANNOTATIONS_HEADER
#        include/kerml/root/annotations/AnnotatingElement.h
#        include/kerml/root/annotations/Annotation.h
#        include/kerml/root/annotations/Comment.h
#        include/kerml/root/annotations/Documentation.h
#        include/kerml/root/annotations/TextualRepresentation.h)

#set(ROOT_NAMESPACES_HEADER
#        include/kerml/root/namespaces/Namespace.h
#        include/kerml/root/namespaces/VisibilityKind.h
#        include/kerml/root/namespaces/Membership.h
#        include/kerml/root/namespaces/OwningMembership.h
#        include/kerml/root/namespaces/Import.h
#        include/kerml/root/namespaces/MembershipImport.h
#        include/kerml/root/namespaces/NamespaceImport.h)

#set(CORE_TYPES_HEADER
#        include/kerml/core/types/Type.h
#        include/kerml/core/types/Specialization.h
#        include/kerml/core/types/Conjugation.h
#        include/kerml/core/types/Disjoining.h
#        include/kerml/core/types/Unioning.h
#        include/kerml/core/types/Intersecting.h
#        include/kerml/core/types/Differencing.h)

#set(CORE_CLASSIFIER_HEADER
#        include/kerml/core/classifiers/Classifier.h
#        include/kerml/core/classifiers/Subclassification.h)

#set(CORE_FEATURES_HEADER
#        include/kerml/core/features/TypeFeaturing.h
#        include/kerml/core/features/FeatureDirectionKind.h
#        include/kerml/core/features/Feature.h
#        include/kerml/core/features/Multiplicity.h
#        include/kerml/core/features/FeatureInverting.h
#        include/kerml/core/features/Subsetting.h
#        include/kerml/core/features/FeatureTyping.h
#        include/kerml/core/features/Featuring.h
#        include/kerml/core/features/Redefinition.h
#        include/kerml/core/features/ReferenceSubsetting.h
#        include/kerml/core/features/FeatureChaining.h
#        include/kerml/core/features/FeatureMembership.h
#        include/kerml/core/features/EndFeatureMembership.h
#        include/kerml/core/features/CrossSubsetting.h)

#set(KERNEL_DATATYPES_HEADER
#        include/kerml/kernel/datatypes/DataType.h)
#
#set(KERNEL_CLASSES_HEADER
#        include/kerml/kernel/classes/Class.h)
#
#set(KERNEL_STRUCTURES_HEADER
#        include/kerml/kernel/structures/Structure.h)
#
#set(KERNEL_ASSOCIATIONS_HEADER
#        include/kerml/kernel/assiciations/Association.h
#        include/kerml/kernel/assiciations/AssociationStructure.h)
#
#set(KERNEL_CONNECTORS_HEADER
#        include/kerml/kernel/connectors/ParameterMembership.h
#        include/kerml/kernel/connectors/BindingConnector.h
#        include/kerml/kernel/connectors/Succession.h
#        include/kerml/kernel/connectors/Expression.h)
#
#set(KERNEL_FEATUREVALUES_HEADER
#        include/kerml/kernel/featurevalues/FeatureValue.h)
#
#set(KERNEL_FUNCTIONS_HEADER
#        include/kerml/kernel/functions/Function.h
#        include/kerml/kernel/functions/Expression.h
#        include/kerml/kernel/functions/Predicate.h
#        include/kerml/kernel/functions/BooleanExpression.h
#        include/kerml/kernel/functions/Invariant.h
#        include/kerml/kernel/functions/ParameterMembership.h
#        include/kerml/kernel/functions/ReturnParameterMembership.h
#        include/kerml/kernel/functions/ResultExpressionMembersip.h)
#
#set(KERNEL_METADATA_HEADER
#        include/kerml/kernel/metadata/MetadataFeature.h)
#
#set(KERNEL_EXPRESSIONS_HEADER
#        include/kerml/kernel/expressions/InvocationExpression.h
#        include/kerml/kernel/expressions/FeatureChainExpression.h
#        include/kerml/kernel/expressions/CollectExpression.h
#        include/kerml/kernel/expressions/SelectExpression.h
#        include/kerml/kernel/expressions/LiteralString.h
#        include/kerml/kernel/expressions/LiteralBoolean.h
#        include/kerml/kernel/expressions/LiteralRational.h
#        include/kerml/kernel/expressions/LiteralInfinity.h
#        include/kerml/kernel/expressions/Expression.h
#        include/kerml/kernel/expressions/NullExpression.h
#        include/kerml/kernel/expressions/LiteralExpression.h
#        include/kerml/kernel/expressions/FeatureReferenceExpression.h
#        include/kerml/kernel/expressions/MetadataAccessExpression.h
#        include/kerml/kernel/expressions/OperatorExpression.h
#        include/kerml/kernel/expressions/LiteralInteger.h)
#
#set(KERNEL_INTERACTIONS_HEADER
#        include/kerml/kernel/interactions/Interaction.h
#        include/kerml/kernel/interactions/ItemFeature.h
#        include/kerml/kernel/interactions/ItemFlowEnd.h
#        include/kerml/kernel/interactions/ItemFlow.h
#        include/kerml/kernel/interactions/SuccessionItemFlow.h)
#
#set(KERNEL_MULTIPLICITIES_HEADER
#        include/kerml/kernel/multiplicities/MultiplicityRange.h)
#
#set(KERNEL_PACKAGE_HEADER
#        include/kerml/kernel/packages/Package.h
#        include/kerml/kernel/packages/LibraryPackage.h
#        include/kerml/kernel/packages/ElementFilterMembership.h)
#
#
#set(KERNEL_BEHAVIORS_HEADER
#        include/kerml/kernel/behaviors/Step.h
#        include/kerml/kernel/behaviors/Behavior.h)

add_library(sysml
        ${GLOBAL_HEADER}
        ${USAGE_HEADER}
        ${ATTRIBUTIONS_HEADER}
        src/sysml/usage/Definition.cpp
        src/sysml/usage/Usage.cpp
        src/sysml/usage/ReferenceUsage.cpp
        src/sysml/usage/VariantMembership.cpp
        src/sysml/attributes/AttributeDefinition.cpp
        src/sysml/attributes/AttributeUsage.cpp

        #        ${ROOT_DEPENDENCIES_HEADER}
#        ${ROOT_ANNOTATIONS_HEADER}
#        ${ROOT_NAMESPACES_HEADER}
#        ${CORE_TYPES_HEADER}
#        ${CORE_CLASSIFIER_HEADER}
#        ${CORE_FEATURES_HEADER}
#        ${KERNEL_DATATYPES_HEADER}
#        ${KERNEL_CLASSES_HEADER}
#        ${KERNEL_STRUCTURES_HEADER}
#        ${KERNEL_ASSOCIATIONS_HEADER}
#        ${KERNEL_CONNECTORS_HEADER}
#        ${KERNEL_FEATUREVALUES_HEADER}
#        ${KERNEL_FUNCTIONS_HEADER}
#        ${KERNEL_METADATA_HEADER}
#        ${KERNEL_EXPRESSIONS_HEADER}
#        ${KERNEL_INTERACTIONS_HEADER}
#        ${KERNEL_MULTIPLICITIES_HEADER}
#        ${KERNEL_PACKAGE_HEADER}
#        ${KERNEL_BEHAVIORS_HEADER}
        )

target_link_libraries(sysml PRIVATE
        boost::boost
        nlohmann_json::nlohmann_json
        date::date
        sysmlv2interfaces
        kerml)


include(GNUInstallDirs)
install(TARGETS sysml ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(TARGETS sysml RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(FILES ${USAGE_ELEMENTS_HEADER} DESTINATION include/sysml/usage)
install(FILES ${ATTRIBUTIONS_HEADER} DESTINATION include/sysml/attributes)
#install(FILES ${ROOT_ANNOTATIONS_HEADER} DESTINATION include/kerml/root/annotations)
#install(FILES ${ROOT_NAMESPACES_HEADER} DESTINATION include/kerml/root/namespaces)
#install(FILES ${CORE_TYPES_HEADER} DESTINATION include/kerml/core/types)
#install(FILES ${CORE_CLASSIFIER_HEADER} DESTINATION include/kerml/core/classifiers)
#install(FILES ${CORE_FEATURES_HEADER} DESTINATION include/kerml/core/features)
#install(FILES ${KERNEL_DATATYPES_HEADER} DESTINATION include/kerml/kernel/datatypes)
#install(FILES ${KERNEL_CLASSES_HEADER} DESTINATION include/kerml/kernel/classes)
#install(FILES ${KERNEL_STRUCTURES_HEADER} DESTINATION include/kerml/kernel/structures)
#install(FILES ${KERNEL_ASSOCIATIONS_HEADER} DESTINATION include/kerml/kernel/associations)
#install(FILES ${KERNEL_CONNECTORS_HEADER} DESTINATION include/kerml/kernel/connectors)
#install(FILES ${KERNEL_FEATUREVALUES_HEADER} DESTINATION include/kerml/kernel/featurevalues)
#install(FILES ${KERNEL_FUNCTIONS_HEADER} DESTINATION include/kerml/kernel/functions)
#install(FILES ${KERNEL_METADATA_HEADER} DESTINATION include/kerml/kernel/metadata)
#install(FILES ${KERNEL_EXPRESSIONS_HEADER} DESTINATION include/kerml/kernel/expressions)
#install(FILES ${KERNEL_INTERACTIONS_HEADER} DESTINATION include/kerml/kernel/interactions)
#install(FILES ${KERNEL_MULTIPLICITIES_HEADER} DESTINATION include/kerml/kernel/multiplicities)
#install(FILES ${KERNEL_PACKAGE_HEADER} DESTINATION include/kerml/kernel/packages)
#install(FILES ${KERNEL_BEHAVIORS_HEADER} DESTINATION include/kerml/kernel/behaviors)
#install(FILES ${GLOBAL_HEADER} DESTINATION include/kerml)


if(MSVC)
    target_compile_options(symsl PRIVATE /W4 /WX- /bigobj)
    target_link_directories(sysml PUBLIC ${CMAKE_BINARY_DIR}/out)
    target_include_directories(sysml PUBLIC
            ./include
            ../sysmlinterfaces/include
            ../kerml/include)
else ()
    target_compile_options(sysml PRIVATE -Wall -Wextra -Wpedantic -Werror)
    target_include_directories(sysml PUBLIC
            ./include
            ../sysmlinterfaces/include
            ../kerml/include)
endif()

file(GLOB_RECURSE _source_list *.cpp* *.h* *.hpp*)
foreach(_source IN ITEMS ${_source_list})
    get_filename_component(_source_path "${_source}" PATH)
    string(REPLACE "${CMAKE_SOURCE_DIR}" "" _group_path "${_source_path}")
    string(REPLACE "/" "\\" _group_path "${_group_path}")
    source_group("${_group_path}" FILES "${_source}")
endforeach()

#if(RUN_TESTS)
#    enable_testing()
#    add_subdirectory(tests)
#endif()