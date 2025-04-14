cmake_minimum_required(VERSION 3.15)

project(sysmlv2service CXX C)

set(INTERFACE_HEADER
        src/interfaces/IProjectUsageService.h
        src/interfaces/IElementNavigationService.h
        src/interfaces/IExternalReleationshipService.h
        src/interfaces/IProjectService.h
        src/interfaces/IProjectVersioningService.h
        src/interfaces/IQueryService.h)

set(API_HEADER
        src/implementation/ElementNavigationService.h
        src/implementation/ProjectService.h
        src/implementation/ProjectUsageService.h
        src/implementation/ProjectVersioningService.h)

add_library(sysmlv2service
        ${API_HEADER}
        ${INTERFACE_HEADER}
        src/implementation/ElementNavigationService.cpp
        src/implementation/ProjectService.cpp
        src/implementation/ProjectUsageService.cpp
        src/implementation/ProjectVersioningService.cpp
        src/sysmlv2service_global.h)

target_link_libraries(sysmlv2service
        boost::boost
        nlohmann_json::nlohmann_json
        date::date
        sysmlv2rest)

target_include_directories(sysmlv2service PUBLIC
        ../rest-api/src
        ../interfaces/src)

include(GNUInstallDirs)
install(TARGETS sysmlv2service ARCHIVE DESTINATION lib)
install(FILES ${API_HEADER} DESTINATION include/sysmlv2service/implementation)
install(FILES ${INTERFACE_HEADER} DESTINATION include/sysmlv2service/interfaces)

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