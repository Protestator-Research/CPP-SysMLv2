cmake_minimum_required(VERSION 3.15)

project(sysmlv2file CXX C)

find_package(nlohmann_json REQUIRED)
find_package(Boost REQUIRED)
find_package(date REQUIRED)
find_package(antlr4-runtime REQUIRED)

set(GLOBAL_HEADER
        src/sysmlv2file_global.h
        src/parsing/ParserError.h
        src/parsing/Parser.h)

set(KERML_PARSER_HEADER
        src/parsing/kerml/KerMLBaseListener.h
        src/parsing/kerml/KerMLLexer.h
        src/parsing/kerml/KerMLListener.h
        src/parsing/kerml/KerMLParser.h
        src/parsing/kerml/KerMlError.h
        src/parsing/kerml/KerMlErrorListener.h)

set(SYSML_PARSER_HEADER
        src/parsing/sysml2/SysMLv2BaseListener.h
        src/parsing/sysml2/SysMLv2Lexer.h
        src/parsing/sysml2/SysMLv2Listener.h
        src/parsing/sysml2/SysMLv2Parser.h
        src/parsing/kermlv2/KerMLParser.cpp
        src/parsing/kermlv2/KerMLParser.h
        src/parsing/kermlv2/KerMlListener.cpp
        src/parsing/kermlv2/KerMlListener.h
        src/parsing/kermlv2/KerMlLexer.cpp
        src/parsing/kermlv2/KerMlLexer.h
        src/parsing/kermlv2/KerMLConstants.h)

add_library(sysmlv2file
        ${KERML_PARSER_HEADER}
        ${SYSML_PARSER_HEADER}
        ${GLOBAL_HEADER}
        src/parsing/kerml/KerMLBaseListener.cpp
        src/parsing/kerml/KerMLLexer.cpp
        src/parsing/kerml/KerMLListener.cpp
        src/parsing/kerml/KerMLParser.cpp
        src/parsing/sysml2/SysMLv2BaseListener.cpp
        src/parsing/sysml2/SysMLv2Lexer.cpp
        src/parsing/sysml2/SysMLv2Listener.cpp
        src/parsing/sysml2/SysMLv2Parser.cpp
        src/parsing/kerml/KerMlErrorListener.cpp
        src/parsing/kerml/KerMlError.cpp
        src/parsing/Parser.cpp
        src/parsing/ParserError.cpp)

target_link_libraries(sysmlv2file
        boost::boost
        nlohmann_json::nlohmann_json
        date::date
        antlr4_shared
        kerml)

target_include_directories(sysmlv2file PUBLIC
        ../kerml/src)

include(GNUInstallDirs)
install(TARGETS sysmlv2file ARCHIVE DESTINATION lib)
install(FILES ${KERML_PARSER_HEADER} DESTINATION include/sysmlv2file/kerml)
install(FILES ${SYSML_PARSER_HEADER} DESTINATION include/sysmlv2file/sysmlv2)
install(FILES ${GLOBAL_HEADER} DESTINATION include/sysmlv2file)

if(MSVC)
    target_compile_options(sysmlv2file PRIVATE /W4 /WX- /bigobj)
else ()
    target_compile_options(sysmlv2file PRIVATE -Wall -Wextra -Wpedantic -Werror)
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