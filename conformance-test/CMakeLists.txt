cmake_minimum_required(VERSION 3.15)

project(conformance-test CXX C)

enable_testing()
find_package(GTest)

add_executable(conformance-test
        src/TestKerMLParser.cpp)

target_link_libraries(conformance-test
        boost::boost
        nlohmann_json::nlohmann_json
        date::date
        gtest::gtest
        sysmlv2file)

target_include_directories(conformance-test PRIVATE
        ../filehandling/src)

file(GLOB_RECURSE _source_list *.cpp* *.h* *.hpp*)
foreach(_source IN ITEMS ${_source_list})
    get_filename_component(_source_path "${_source}" PATH)
    string(REPLACE "${CMAKE_SOURCE_DIR}" "" _group_path "${_source_path}")
    string(REPLACE "/" "\\" _group_path "${_group_path}")
    source_group("${_group_path}" FILES "${_source}")
endforeach()