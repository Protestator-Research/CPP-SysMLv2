cmake_minimum_required(VERSION 3.15)

project(sysmlv2file CXX C)

find_package(nlohmann_json REQUIRED)
find_package(Boost REQUIRED)
find_package(date REQUIRED)
find_package(antlr4-runtime REQUIRED)

set(GLOBAL_HEADER
        src/sysmlv2file_global.h
        src/ParserError.h
        src/Parser.h)

set(KERML_PARSER_HEADER
        src/kerml/KerMLBaseListener.h
        src/kerml/KerMLLexer.h
        src/kerml/KerMLListener.h
        src/kerml/KerMLParser.h
        src/kerml/KerMlError.h
        src/kerml/KerMlErrorListener.h)

set(SYSML_PARSER_HEADER
        src/sysml2/SysMLv2BaseListener.h
        src/sysml2/SysMLv2Lexer.h
        src/sysml2/SysMLv2Listener.h
        src/sysml2/SysMLv2Parser.h)

add_library(sysmlv2file
        ${KERML_PARSER_HEADER}
        ${SYSML_PARSER_HEADER}
        ${GLOBAL_HEADER}
        src/kerml/KerMLBaseListener.cpp
        src/kerml/KerMLLexer.cpp
        src/kerml/KerMLListener.cpp
        src/kerml/KerMLParser.cpp
        src/sysml2/SysMLv2BaseListener.cpp
        src/sysml2/SysMLv2Lexer.cpp
        src/sysml2/SysMLv2Listener.cpp
        src/sysml2/SysMLv2Parser.cpp
        src/kerml/KerMlErrorListener.cpp
        src/kerml/KerMlError.cpp
        src/Parser.cpp
        src/ParserError.cpp
        src/kerml/KerMlListenerImplementation.cpp
        src/kerml/KerMlListenerImplementation.h)

target_link_libraries(sysmlv2file
        boost::boost
        nlohmann_json::nlohmann_json
        date::date
        antlr4_shared
        kerml)

target_include_directories(sysmlv2file PUBLIC
        ../kerml/src)

include(GNUInstallDirs)
install(TARGETS sysmlv2file ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(TARGETS sysmlv2file RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
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