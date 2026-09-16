cmake_minimum_required(VERSION 3.15)

include(${CMAKE_CURRENT_SOURCE_DIR}/SysMLSources.cmake)
add_library(sysml ${SYSML_SOURCES})
target_compile_features(sysml PUBLIC cxx_std_20)
target_link_libraries(sysml PUBLIC kerml sysmlv2interfaces
        boost::boost nlohmann_json::nlohmann_json date::date)
target_include_directories(sysml PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>)
if(MSVC)
    target_compile_options(sysml PRIVATE /W4 /WX- /bigobj)
else()
    target_compile_options(sysml PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

include(GNUInstallDirs)
install(TARGETS sysml
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(DIRECTORY include/sysml DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

if(BUILD_TESTING)
    add_executable(sysml-representation-test tests/Representation.cpp tests/Inventory.cpp)
    target_link_libraries(sysml-representation-test PRIVATE sysml)
    add_test(NAME sysml-representation COMMAND sysml-representation-test)
    find_package(Python3 COMPONENTS Interpreter QUIET)
    if(Python3_Interpreter_FOUND)
        add_test(NAME sysml-generated-files
                COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/generate_abstract_syntax.py --check)
    endif()
endif()
