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


if(MSVC)
    target_compile_options(sysml PRIVATE /W4 /WX- /bigobj)
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