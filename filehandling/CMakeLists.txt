cmake_minimum_required(VERSION 3.15)

project(sysmlv2parser CXX C)

find_package(nlohmann_json REQUIRED)
find_package(Boost REQUIRED)
find_package(date REQUIRED)
find_package(antlr4-runtime REQUIRED)


set(GLOBAL_HEADER
        include/sysmlv2/sysmlv2file_global.h
        include/sysmlv2/ParserError.h
        include/sysmlv2/Parser.h)

set(KERML_PARSER_HEADER
        include/kerml/parser/KerMLBaseListener.h
        include/kerml/parser/KerMLLexer.h
        include/kerml/parser/KerMLListener.h
        include/kerml/parser/KerMLParser.h
        include/kerml/parser/KerMlError.h
        include/kerml/parser/KerMlErrorListener.h
        include/kerml/parser/KerMlListenerImplementation.h)

set(SYSML_PARSER_HEADER
        include/sysmlv2/parser/SysMLv2BaseListener.h
        include/sysmlv2/parser/SysMLv2Lexer.h
        include/sysmlv2/parser/SysMLv2Listener.h
        include/sysmlv2/parser/SysMLv2Parser.h)

add_library(sysmlv2parser
        ${KERML_PARSER_HEADER}
        ${SYSML_PARSER_HEADER}
        ${GLOBAL_HEADER}
        src/kerml/parser/KerMLBaseListener.cpp
        src/kerml/parser/KerMLLexer.cpp
        src/kerml/parser/KerMLListener.cpp
        src/kerml/parser/KerMLParser.cpp
        src/sysml2/parser/SysMLv2BaseListener.cpp
        src/sysml2/parser/SysMLv2Lexer.cpp
        src/sysml2/parser/SysMLv2Listener.cpp
        src/sysml2/parser/SysMLv2Parser.cpp
        src/kerml/parser/KerMlErrorListener.cpp
        src/kerml/parser/KerMlError.cpp
        src/sysml2/Parser.cpp
        src/sysml2/ParserError.cpp
        src/kerml/parser/KerMlListenerImplementation.cpp)

if(EXISTS antlr4_shared)
    target_link_libraries(sysmlv2parser
            boost::boost
            nlohmann_json::nlohmann_json
            date::date
            antlr4_shared
            kerml)
else ()
    target_link_libraries(sysmlv2parser
            boost::boost
            nlohmann_json::nlohmann_json
            date::date
            antlr4_static
            kerml)
endif ()


include(GNUInstallDirs)
install(TARGETS sysmlv2parser ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(TARGETS sysmlv2parser RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(FILES ${KERML_PARSER_HEADER} DESTINATION include/kerml/parser)
install(FILES ${SYSML_PARSER_HEADER} DESTINATION include/sysmlv2/parser)
install(FILES ${GLOBAL_HEADER} DESTINATION include/sysmlv2)

if(MSVC)
    target_compile_options(sysmlv2parser PRIVATE /W4 /WX- /bigobj)
    target_link_directories(sysmlv2parser PUBLIC ${CMAKE_BINARY_DIR}/out)
    target_include_directories(sysmlv2parser PUBLIC
        ../kerml/include
        include)
else ()
    target_compile_options(sysmlv2parser PRIVATE -Wall -Wextra -Wpedantic)
    target_include_directories(sysmlv2parser PRIVATE
        ../kerml/include
        include)
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