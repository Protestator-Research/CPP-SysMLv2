cmake_minimum_required(VERSION 3.15)

project(sysmlv2base CXX C)

set(ENTITIES_HEADER ../rest-api/src/entities/IEntity.h)

add_library(sysmlv2base INTERFACE
        ${ENTITIES_HEADER}
        src/sysmlv2base_global.h)

target_link_libraries(sysmlv2base INTERFACE
        boost::boost
        nlohmann_json::nlohmann_json
        date::date)


include(GNUInstallDirs)
install(TARGETS sysmlv2base ARCHIVE DESTINATION lib)
install(FILES ${ENTITIES_HEADER} DESTINATION include/sysmlv2/rest/entities)

if(MSVC)
    target_compile_options(sysmlv2base INTERFACE /W4 /WX- /bigobj)
else ()
    target_compile_options(sysmlv2base INTERFACE -Wall -Wextra -Wpedantic -Werror)
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