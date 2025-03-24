cmake_minimum_required(VERSION 3.15)

project(kerml CXX C)

set(KERML_HEADER
        src/Root/Elements/Element.h
        src/Root/Elements/Relationship.h
        src/Root/Dependencies/Dependency.h
        src/Root/Annotations/AnnotatingElement.h
        src/Root/Annotations/Annotation.cpp
        src/Root/Annotations/Annotation.h
        src/Root/Annotations/Comment.cpp
        src/Root/Annotations/Comment.h
        src/Root/Annotations/Documentation.cpp
        src/Root/Annotations/Documentation.h
        src/Root/Annotations/TextualRepresentation.cpp
        src/Root/Annotations/TextualRepresentation.h)

add_library(kerml
        ${KERML_HEADER}
        src/Root/Elements/Element.cpp
        src/Root/Elements/Relationship.cpp
        src/Root/Dependencies/Dependency.cpp
        src/Root/Annotations/AnnotatingElement.cpp
        src/Root/Annotations/Annotation.cpp
        src/Root/Annotations/Annotation.h)

target_link_libraries(kerml PRIVATE
        boost::boost
        nlohmann_json::nlohmann_json
        date::date
        antlr4_static)


include(GNUInstallDirs)
install(TARGETS kerml ARCHIVE DESTINATION lib)
install(FILES ${KERML_HEADER} DESTINATION include/kerml/entities)

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