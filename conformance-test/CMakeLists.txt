cmake_minimum_required(VERSION 3.15)

project(conformance-test CXX C)


find_package(GTest REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(Boost REQUIRED)
find_package(date REQUIRED)
find_package(antlr4-runtime REQUIRED)

add_executable(conformance-test
        src/TestKerMLParser.cpp
        src/TestSysMLParser.cpp
        src/TestProjectController.cpp
        src/TestRestAPI.cpp
        src/TestResourcePackages.cpp
)

#if((EXISTS antlr4_shared) OR (MSVC))
    target_link_libraries(conformance-test
            Boost::headers
            nlohmann_json::nlohmann_json
            date::date
            gtest::gtest
            antlr4_shared
            sysmlv2interfaces
            sysmlv2parser
            sysmlv2service
            sysmlv2rest
            kerml)
target_link_libraries(conformance-test sysml)
#else ()
#    target_link_libraries(conformance-test
#            Boost::headers
#            nlohmann_json::nlohmann_json
#            date::date
#            gtest::gtest
#            antlr4_static
#            sysmlv2interfaces
#            sysmlv2parser
#            sysmlv2service
#            sysmlv2rest
#            kerml)
#endif ()

target_include_directories(conformance-test PRIVATE
        ../filehandling/include
        ../services/include
        ../kerml/include
        ../rest-api/include)

# The pre-existing test binary above (parser regression tests plus the service/REST tests) keeps its
# single-executable layout; its tests are all labeled "regression" below. AP1's new lexer/syntax/
# library/robustness suites, added underneath, each get their own executable so gtest_discover_tests
# can label them independently and so the (slow) library/robustness suites can be run or skipped on
# their own via `ctest -L <label>`.
#gtest_discover_tests(conformance-test PROPERTIES LABELS regression)

file(GLOB_RECURSE _source_list *.cpp* *.h* *.hpp*)
foreach(_source IN ITEMS ${_source_list})
    get_filename_component(_source_path "${_source}" PATH)
    string(REPLACE "${CMAKE_SOURCE_DIR}" "" _group_path "${_source_path}")
    string(REPLACE "/" "\\" _group_path "${_group_path}")
    source_group("${_group_path}" FILES "${_source}")
endforeach()

# ---------------------------------------------------------------------------
# AP1/AP2/AP4(e): lexer, syntax, library and robustness suites.
#
# Each links only what it needs (the parser + model libraries, not the REST/service stack), per its
# own small executable so gtest_discover_tests can attach a distinct CTest label to it. All four
# share conformance-test/src/support/TestHelpers.h (named<T>, parseFile, readFile, listFiles,
# loadExpectedFailures) instead of redefining their own copies.
#
# SYSML_LIBRARY_DIR / CONFORMANCE_TESTDATA_DIR / CONFORMANCE_EXPECTED_FAILURES_FILE are plain string
# compile definitions consumed as e.g. `std::filesystem::path root(SYSML_LIBRARY_DIR);` --
# CMAKE_SOURCE_DIR here is the top-level project source dir (CPP-SysMLv2/), same as any other
# target's, regardless of this subdirectory's own project(conformance-test ...) call above.
# ---------------------------------------------------------------------------
set(CONFORMANCE_LIBRARY_LINK_LIBS
        Boost::headers
        nlohmann_json::nlohmann_json
        date::date
        gtest::gtest
        antlr4_shared
        sysmlv2parser
        kerml
        sysml)
set(CONFORMANCE_LIBRARY_INCLUDE_DIRS
        ../filehandling/include
        ../kerml/include)

add_executable(conformance-lexer
        src/lexer/TestLexer.cpp
        src/support/TestHelpers.h)
target_link_libraries(conformance-lexer ${CONFORMANCE_LIBRARY_LINK_LIBS})
target_include_directories(conformance-lexer PRIVATE ${CONFORMANCE_LIBRARY_INCLUDE_DIRS})
#gtest_discover_tests(conformance-lexer PROPERTIES LABELS lexer)

add_executable(conformance-syntax
        src/syntax/TestSyntax.cpp
        src/support/TestHelpers.h)
target_link_libraries(conformance-syntax ${CONFORMANCE_LIBRARY_LINK_LIBS})
target_include_directories(conformance-syntax PRIVATE ${CONFORMANCE_LIBRARY_INCLUDE_DIRS})
target_compile_definitions(conformance-syntax PRIVATE
        CONFORMANCE_TESTDATA_DIR="${CMAKE_CURRENT_SOURCE_DIR}/testdata/syntax"
        CONFORMANCE_EXPECTED_FAILURES_FILE="${CMAKE_CURRENT_SOURCE_DIR}/expected_failures.txt")
#gtest_discover_tests(conformance-syntax PROPERTIES LABELS syntax)

add_executable(conformance-library
        src/library/TestLibrary.cpp
        src/support/TestHelpers.h)
target_link_libraries(conformance-library ${CONFORMANCE_LIBRARY_LINK_LIBS})
target_include_directories(conformance-library PRIVATE ${CONFORMANCE_LIBRARY_INCLUDE_DIRS})
target_compile_definitions(conformance-library PRIVATE
        SYSML_LIBRARY_DIR="${CMAKE_SOURCE_DIR}/resources/sysml.library"
        CONFORMANCE_EXPECTED_FAILURES_FILE="${CMAKE_CURRENT_SOURCE_DIR}/expected_failures.txt")
# gtest_discover_tests runs the (slow, ~94-file) executable at build/test time to enumerate its
# cases; DISCOVERY_TIMEOUT gives it more room than the 5s default (SI.sysml alone can take ~20s).
#gtest_discover_tests(conformance-library PROPERTIES LABELS library DISCOVERY_TIMEOUT 120)

add_executable(conformance-robustness
        src/robustness/TestRobustness.cpp
        src/support/TestHelpers.h)
target_link_libraries(conformance-robustness ${CONFORMANCE_LIBRARY_LINK_LIBS})
target_include_directories(conformance-robustness PRIVATE ${CONFORMANCE_LIBRARY_INCLUDE_DIRS})
target_compile_definitions(conformance-robustness PRIVATE
        SYSML_LIBRARY_DIR="${CMAKE_SOURCE_DIR}/resources/sysml.library")
#gtest_discover_tests(conformance-robustness PROPERTIES LABELS robustness DISCOVERY_TIMEOUT 120)

# AP10: name-resolution suite (unit tests of the scoped resolver plus the whole-library resolution ratchet).
# CONFORMANCE_EXPECTED_UNRESOLVED_FILE lists the library references that are still unresolved.
add_executable(conformance-resolution
        src/resolution/TestResolution.cpp
        src/support/TestHelpers.h)
target_link_libraries(conformance-resolution ${CONFORMANCE_LIBRARY_LINK_LIBS})
target_include_directories(conformance-resolution PRIVATE ${CONFORMANCE_LIBRARY_INCLUDE_DIRS})
target_compile_definitions(conformance-resolution PRIVATE
        SYSML_LIBRARY_DIR="${CMAKE_SOURCE_DIR}/resources/sysml.library"
        CONFORMANCE_EXPECTED_UNRESOLVED_FILE="${CMAKE_CURRENT_SOURCE_DIR}/expected_unresolved.txt")
#gtest_discover_tests(conformance-resolution PROPERTIES LABELS resolution DISCOVERY_TIMEOUT 120)

# AP11: abstract-syntax suites.
#  - conformance-abstract-syntax: the ownership structure of the whole library (memberships, owners, explicit relationships) against the
#    XMI that the pilot implementation exported (resources/sysml.library.xmi, NOT the .implied variant), one test per library file, with the
#    ratchet expected_xmi_diffs.txt. Also holds the unit tests of the XMI reader. (SYSML_LIBRARY_DIR / SYSML_LIBRARY_XMI_DIR: see above.)
#  - the metaclass-name test is generated from the model headers (tools/generate_metaclass_name_test.py): every concrete class of kerml/ and
#    sysml/ is instantiated and must report its exact metaclass name.
add_executable(conformance-abstract-syntax
        src/abstractsyntax/TestAbstractSyntax.cpp
        src/abstractsyntax/TestMetaclassNames.cpp
        src/support/TestHelpers.h
        src/support/XmiReader.h
        src/support/ModelDiff.h)
target_link_libraries(conformance-abstract-syntax ${CONFORMANCE_LIBRARY_LINK_LIBS})
target_include_directories(conformance-abstract-syntax PRIVATE ${CONFORMANCE_LIBRARY_INCLUDE_DIRS} ../sysml/include)
target_compile_definitions(conformance-abstract-syntax PRIVATE
        SYSML_LIBRARY_DIR="${CMAKE_SOURCE_DIR}/resources/sysml.library"
        SYSML_LIBRARY_XMI_DIR="${CMAKE_SOURCE_DIR}/resources/sysml.library.xmi"
        CONFORMANCE_EXPECTED_XMI_DIFFS_FILE="${CMAKE_CURRENT_SOURCE_DIR}/expected_xmi_diffs.txt")
#gtest_discover_tests(conformance-abstract-syntax PROPERTIES LABELS abstract-syntax DISCOVERY_TIMEOUT 120)
