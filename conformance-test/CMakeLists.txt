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
        src/TestElementDeserialization.cpp
        src/TestKerMLJson.cpp
        src/TestSysMLJson.cpp
        src/TestBranchRequest.cpp
        src/TestRestFoundation.cpp
        src/TestRestVersioning.cpp
        src/TestRestData.cpp
        src/TestRestQuery.cpp
        src/TestRestDeserializer.cpp
)

# TestRestAPI.cpp (unchanged tests) deliberately uses the deprecated ProjectRequest API to prove it keeps working.
if(MSVC)
    set_source_files_properties(src/TestRestAPI.cpp PROPERTIES COMPILE_OPTIONS /wd4996)
else()
    set_source_files_properties(src/TestRestAPI.cpp PROPERTIES COMPILE_OPTIONS -Wno-deprecated-declarations)
endif()

# TestKerMLJson.cpp and TestSysMLJson.cpp instantiate their round trip for every KerML/SysML metaclass and need more sections than an object file allows by default.
if(MSVC)
    set_source_files_properties(src/TestKerMLJson.cpp src/TestSysMLJson.cpp PROPERTIES COMPILE_OPTIONS /bigobj)
endif()

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
# library/robustness suites, added underneath, each get their own executable so CTest
# can label them independently and so the (slow) library/robustness suites can be run or skipped on
# their own via `ctest -L <label>`.
add_test(NAME conformance-regression COMMAND conformance-test)
set_tests_properties(conformance-regression PROPERTIES LABELS regression)

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
# own small executable so CTest can attach a distinct label to it. All four
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
add_test(NAME conformance-lexer COMMAND conformance-lexer)
set_tests_properties(conformance-lexer PROPERTIES LABELS lexer)

add_executable(conformance-syntax
        src/syntax/TestSyntax.cpp
        src/support/TestHelpers.h)
target_link_libraries(conformance-syntax ${CONFORMANCE_LIBRARY_LINK_LIBS})
target_include_directories(conformance-syntax PRIVATE ${CONFORMANCE_LIBRARY_INCLUDE_DIRS})
target_compile_definitions(conformance-syntax PRIVATE
        CONFORMANCE_TESTDATA_DIR="${CMAKE_CURRENT_SOURCE_DIR}/testdata/syntax"
        CONFORMANCE_EXPECTED_FAILURES_FILE="${CMAKE_CURRENT_SOURCE_DIR}/expected_failures.txt")
add_test(NAME conformance-syntax COMMAND conformance-syntax)
set_tests_properties(conformance-syntax PROPERTIES LABELS syntax)

add_executable(conformance-library
        src/library/TestLibrary.cpp
        src/support/TestHelpers.h)
target_link_libraries(conformance-library ${CONFORMANCE_LIBRARY_LINK_LIBS})
target_include_directories(conformance-library PRIVATE ${CONFORMANCE_LIBRARY_INCLUDE_DIRS})
target_compile_definitions(conformance-library PRIVATE
        SYSML_LIBRARY_DIR="${CMAKE_SOURCE_DIR}/resources/sysml.library"
        CONFORMANCE_EXPECTED_FAILURES_FILE="${CMAKE_CURRENT_SOURCE_DIR}/expected_failures.txt")
add_test(NAME conformance-library COMMAND conformance-library)
set_tests_properties(conformance-library PROPERTIES LABELS library)

add_executable(conformance-robustness
        src/robustness/TestRobustness.cpp
        src/support/TestHelpers.h)
target_link_libraries(conformance-robustness ${CONFORMANCE_LIBRARY_LINK_LIBS})
target_include_directories(conformance-robustness PRIVATE ${CONFORMANCE_LIBRARY_INCLUDE_DIRS})
target_compile_definitions(conformance-robustness PRIVATE
        SYSML_LIBRARY_DIR="${CMAKE_SOURCE_DIR}/resources/sysml.library")
add_test(NAME conformance-robustness COMMAND conformance-robustness)
set_tests_properties(conformance-robustness PROPERTIES LABELS robustness)

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
add_test(NAME conformance-resolution COMMAND conformance-resolution)
set_tests_properties(conformance-resolution PROPERTIES LABELS resolution)

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
add_test(NAME conformance-abstract-syntax COMMAND conformance-abstract-syntax)
set_tests_properties(conformance-abstract-syntax PROPERTIES LABELS abstract-syntax)

# XMI import: the XMI files of the pilot implementation (resources/sysml.library.xmi) are read by SysMLv2::Files::XmiReader into a Workspace and
# compared with the same files through the oracle of the abstract-syntax suite (src/support/ModelDiff.h); testdata/xmi/negative holds the
# malformed and inconsistent files whose ParserErrors are checked. TestXmiExport.cpp checks the XMI writer by round trips (library files and
# the SysML models of testdata/syntax/sysml/valid).
add_executable(conformance-xmi
        src/xmi/TestXmiImport.cpp
        src/xmi/TestXmiExport.cpp
        src/support/TestHelpers.h
        src/support/XmiReader.h
        src/support/ModelDiff.h)
target_link_libraries(conformance-xmi ${CONFORMANCE_LIBRARY_LINK_LIBS})
target_include_directories(conformance-xmi PRIVATE ${CONFORMANCE_LIBRARY_INCLUDE_DIRS} ../sysml/include)
target_compile_definitions(conformance-xmi PRIVATE
        SYSML_LIBRARY_XMI_DIR="${CMAKE_SOURCE_DIR}/resources/sysml.library.xmi"
        XMI_NEGATIVE_DIR="${CMAKE_CURRENT_SOURCE_DIR}/testdata/xmi/negative"
        SYSML_VALID_DIR="${CMAKE_CURRENT_SOURCE_DIR}/testdata/syntax/sysml/valid")
add_test(NAME conformance-xmi COMMAND conformance-xmi)
set_tests_properties(conformance-xmi PROPERTIES LABELS xmi)
