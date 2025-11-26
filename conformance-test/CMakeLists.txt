cmake_minimum_required(VERSION 3.15)

project(conformance-test CXX C)


find_package(GTest REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(Boost REQUIRED)
find_package(date REQUIRED)
find_package(antlr4-runtime REQUIRED)

add_executable(conformance-test
        src/TestKerMLParser.cpp
        src/TestProjectController.cpp
        src/TestRestAPI.cpp
)

if(EXISTS antlr4_shared)
    target_link_libraries(conformance-test
            boost::boost
            nlohmann_json::nlohmann_json
            date::date
            gtest::gtest
            antlr4_shared
            sysmlv2parser
            sysmlv2service
            sysmlv2rest)
else ()
    target_link_libraries(conformance-test
            boost::boost
            nlohmann_json::nlohmann_json
            date::date
            gtest::gtest
            antlr4_static
            sysmlv2parser
            sysmlv2service
            sysmlv2rest)
endif ()

target_include_directories(conformance-test PRIVATE
        ../filehandling/include
        ../services/include
        ../kerml/include
        ../rest-api/include)

file(GLOB_RECURSE _source_list *.cpp* *.h* *.hpp*)
foreach(_source IN ITEMS ${_source_list})
    get_filename_component(_source_path "${_source}" PATH)
    string(REPLACE "${CMAKE_SOURCE_DIR}" "" _group_path "${_source_path}")
    string(REPLACE "/" "\\" _group_path "${_group_path}")
    source_group("${_group_path}" FILES "${_source}")
endforeach()

add_test(NAME conformance-test COMMAND conformance-test)