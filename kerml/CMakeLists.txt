cmake_minimum_required(VERSION 3.15)

project(kerml CXX C)

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
        src/kernel/datatypes/DataType.h
        src/kernel/datatypes/Class.h
        src/kernel/datatypes/Association.h
        src/kernel/datatypes/Structure.h
        src/kernel/datatypes/AssociationStructure.h)

add_library(kerml
        ${ROOT_ELEMENTS_HEADER}
        ${ROOT_DEPENDENCIES_HEADER}
        ${ROOT_ANNOTATIONS_HEADER}
        ${ROOT_NAMESPACES_HEADER}
        ${CORE_TYPES_HEADER}
        ${CORE_CLASSIFIER_HEADER}
        ${CORE_FEATURES_HEADER}
        ${KERNEL_DATATYPES_HEADER}
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
        src/kernel/datatypes/Class.cpp
        src/kernel/datatypes/Association.cpp
        src/kernel/datatypes/Structure.cpp
        src/kernel/datatypes/AssociationStructure.cpp)

target_link_libraries(kerml PRIVATE
        boost::boost
        nlohmann_json::nlohmann_json
        date::date
        antlr4_static)


include(GNUInstallDirs)
install(TARGETS kerml ARCHIVE DESTINATION lib)
install(FILES ${ROOT_ELEMENTS_HEADER} DESTINATION include/kerml/root/elements)
install(FILES ${ROOT_DEPENDENCIES_HEADER} DESTINATION include/kerml/root/dependencies)
install(FILES ${ROOT_ANNOTATIONS_HEADER} DESTINATION include/kerml/root/annotations)
install(FILES ${ROOT_NAMESPACES_HEADER} DESTINATION include/kerml/root/namespaces)

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