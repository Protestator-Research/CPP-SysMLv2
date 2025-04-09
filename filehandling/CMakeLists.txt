cmake_minimum_required(VERSION 3.15)

project(sysmlv2file CXX C)

find_package(nlohmann_json REQUIRED)
find_package(Boost REQUIRED)
find_package(date REQUIRED)
find_package(antlr4-runtime REQUIRED)

set(PARSER_HEADER
        src/parsing/kerml/KerMLBaseListener.h
        src/parsing/kerml/KerMLLexer.h
        src/parsing/kerml/KerMLListener.h
        src/parsing/kerml/KerMLParser.h
        src/parsing/sysml2/SysMLv2BaseListener.h
        src/parsing/sysml2/SysMLv2Lexer.h
        src/parsing/sysml2/SysMLv2Listener.h
        src/parsing/sysml2/SysMLv2Parser.h
        src/parsing/kerml/KerMlError.h
        src/parsing/kerml/KerMlErrorListener.h)

add_library(sysmlv2file
        src/parsing/kerml/KerMLBaseListener.cpp
        src/parsing/kerml/KerMLLexer.cpp
        src/parsing/kerml/KerMLListener.cpp
        src/parsing/kerml/KerMLParser.cpp
        src/parsing/sysml2/SysMLv2BaseListener.cpp
        src/parsing/sysml2/SysMLv2Lexer.cpp
        src/parsing/sysml2/SysMLv2Listener.cpp
        src/parsing/sysml2/SysMLv2Parser.cpp
        src/sysmlv2file_global.h
        ${PARSER_HEADER}
        src/parsing/kerml/KerMlErrorListener.cpp
        src/parsing/kerml/KerMlError.cpp)

target_link_libraries(sysmlv2file
        boost::boost
        nlohmann_json::nlohmann_json
        date::date
        antlr4_shared)


include(GNUInstallDirs)
install(TARGETS sysmlv2file ARCHIVE DESTINATION lib)
install(FILES ${PARSER_HEADER} DESTINATION include/sysmlv2file)

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