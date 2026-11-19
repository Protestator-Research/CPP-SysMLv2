cmake_minimum_required(VERSION 3.15)

project(sysmlv2evaluation CXX)

# sysmlv2evaluation: evaluation of KerML / SysML v2 expressions. Options: BUILD_WITH_EVALUATION (root CMakeLists.txt); the tests need BUILD_TESTING.
# The module depends on the model (kerml) only, not on the parsers, so that it is usable on models loaded by any means.
#   sysmlv2evaluation       library: value model (Value), diagnostics, EvaluationContext, FunctionRegistry with the native
#                           implementations of the core functions of the Kernel Function Library, Evaluator
#   sysmlv2evaluation-test  the tests (gtest, hand-built models only)

find_package(nlohmann_json REQUIRED)
find_package(Boost REQUIRED)
find_package(Threads REQUIRED)

set(GLOBAL_HEADER
        include/sysmlv2/evaluation/sysmlv2evaluation_global.h)

set(API_HEADER
        include/sysmlv2/evaluation/Diagnostic.h
        include/sysmlv2/evaluation/EvaluationContext.h
        include/sysmlv2/evaluation/Evaluator.h
        include/sysmlv2/evaluation/FunctionRegistry.h
        include/sysmlv2/evaluation/ModelLevelEvaluable.h
        include/sysmlv2/evaluation/QualifiedName.h
        include/sysmlv2/evaluation/Value.h)

add_library(sysmlv2evaluation
        ${GLOBAL_HEADER}
        ${API_HEADER}
        src/Arguments.cpp
        src/Arguments.h
        src/Callables.cpp
        src/Callables.h
        src/CompilerSupport.h
        src/EvaluationContext.cpp
        src/ModelLevel.cpp
        src/Navigation.cpp
        src/Navigation.h
        src/Evaluator.cpp
        src/FunctionRegistry.cpp
        src/QualifiedName.cpp
        src/StackRunner.cpp
        src/StackRunner.h
        src/Value.cpp
        src/functions/BaseFunctions.cpp
        src/functions/ControlFunctions.cpp
        src/functions/DataFunctions.cpp
        src/functions/ScalarFunctions.cpp
        src/functions/SequenceFunctions.cpp
        src/functions/FunctionSupport.h
        src/functions/StandardFunctions.h)

target_link_libraries(sysmlv2evaluation
        PUBLIC kerml Boost::headers nlohmann_json::nlohmann_json sysmlv2interfaces
        PRIVATE Threads::Threads)

target_include_directories(sysmlv2evaluation PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>)
target_include_directories(sysmlv2evaluation PRIVATE
        ../kerml/include
        ../sysmlinterfaces/include)

if(MSVC)
    target_compile_options(sysmlv2evaluation PRIVATE /W4 /WX- /bigobj)
else()
    target_compile_options(sysmlv2evaluation PRIVATE -Wno-error=maybe-uninitialized -Wall -Wextra -Wpedantic $<$<BOOL:${SYSMLV2_WERROR}>:-Werror>)
endif()

include(GNUInstallDirs)
install(TARGETS sysmlv2evaluation ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(TARGETS sysmlv2evaluation RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(FILES ${GLOBAL_HEADER} ${API_HEADER} DESTINATION include/sysmlv2/evaluation)

file(GLOB_RECURSE _source_list *.cpp* *.h* *.hpp*)
foreach(_source IN ITEMS ${_source_list})
    get_filename_component(_source_path "${_source}" PATH)
    string(REPLACE "${CMAKE_SOURCE_DIR}" "" _group_path "${_source_path}")
    string(REPLACE "/" "\\" _group_path "${_group_path}")
    source_group("${_group_path}" FILES "${_source}")
endforeach()

if(BUILD_TESTING)
    find_package(GTest REQUIRED)
    add_subdirectory(tests)
endif()
