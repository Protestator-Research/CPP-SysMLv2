cmake_minimum_required(VERSION 3.15)

project(sysml CXX C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(nlohmann_json REQUIRED)
find_package(Boost REQUIRED)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out) 
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out) 
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out) 

option(BUILD_WITH_REST "Builds with the SysMLv2 REST API" ON)
option(BUILD_WITH_SERVICES "Builds with the SysMLv2 services API" ON)
# The client of a SysML v2 API server (services/*/online, SysMLAPIImplementation) needs libcurl. Everything else of the
# services (InstanceManager, ...) does not.
option(BUILD_WITH_ONLINE "Builds the online part of the services (SysMLv2 API client, requires libcurl)" ON)
# The checker of SysML v2 texts (sysmlv2check): C interface sysml_pruefe, command line tool, tests.
option(BUILD_WITH_CHECK "Builds sysmlv2check, the checker for SysML v2 texts (requires BUILD_WITH_PARSING)" OFF)
option(BUILD_WITH_PARSING "Builds with the SysMLv2 parsing API" ON)
# The Python module (check/python): one self-contained shared library sysmlv2check_native with the C interface of sysmlv2check, everything else linked statically.
option(BUILD_PYTHON_MODULE "Builds the shared library for the Python package sysmlv2 (requires BUILD_WITH_CHECK, static build)" OFF)
option(BUILD_TESTING "Build the conformance tests" ON)
# Warnings are errors (GCC / Clang). Switch off for toolchains whose warnings differ (Emscripten) or optimized builds with newer compilers.
option(SYSMLV2_WERROR "Treats compiler warnings as errors" ON)
# Static build: the export macros (*_global.h) must be empty (no __declspec(dllimport) on Windows); position independent code so that the
# static libraries can be linked into a shared library (Python module) on Linux. There is no installed CMake config, consumers get
# SYSMLV2_STATIC from the Conan recipe (package_info).
if(NOT BUILD_SHARED_LIBS)
    add_compile_definitions(SYSMLV2_STATIC)
    if(NOT EMSCRIPTEN)
        set(CMAKE_POSITION_INDEPENDENT_CODE ON)
    endif()
endif()
if(BUILD_TESTING)
    enable_testing()
endif()


if(BUILD_WITH_REST)
    # date is only used by the REST entities (date/date.h)
    find_package(date REQUIRED)
endif()

add_subdirectory(sysmlinterfaces)

if (BUILD_WITH_REST)
    add_subdirectory(rest-api)
endif ()

if (BUILD_WITH_SERVICES)
    add_subdirectory(services)
endif ()

if (BUILD_WITH_PARSING)
    add_subdirectory(resources)
    add_subdirectory(filehandling)
endif ()


add_subdirectory(kerml)
add_subdirectory(sysml)

if (BUILD_WITH_CHECK)
    if (NOT BUILD_WITH_PARSING)
        message(FATAL_ERROR "BUILD_WITH_CHECK requires BUILD_WITH_PARSING")
    endif ()
    add_subdirectory(check)
elseif (BUILD_PYTHON_MODULE)
    message(FATAL_ERROR "BUILD_PYTHON_MODULE requires BUILD_WITH_CHECK")
endif ()
if(BUILD_TESTING AND BUILD_WITH_PARSING AND BUILD_WITH_SERVICES AND BUILD_WITH_REST)
    add_subdirectory(conformance-test)
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)