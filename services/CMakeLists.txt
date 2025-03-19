cmake_minimum_required(VERSION 3.15)

project(sysmlv2service CXX C)

set(API_HEADER
        src/interfacess/IProjectUsageService.h
        src/interfacess/IElementNavigationService.h
        src/interfacess/IExternalReleationshipService.h
        src/interfacess/IProjectService.h
        src/interfacess/IProjectVersioningService.h
        src/interfacess/IQueryService.h
        src/implementation/ElementNavigationService.cpp)

add_library(sysmlv2service
        ${API_HEADER}
        src/implementation/ElementNavigationService.cpp)

include(GNUInstallDirs)
install(TARGETS sysmlv2service ARCHIVE DESTINATION lib)
install(FILES ${API_HEADER} DESTINATION include/sysmlv2/services)

if(MSVC)
    target_compile_options(sysmlv2service PRIVATE /W4 /WX- /bigobj)
else ()
    target_compile_options(sysmlv2service PRIVATE -Wall -Wextra -Wpedantic -Werror)
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