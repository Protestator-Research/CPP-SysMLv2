add_executable(kerml-representation-test MissingClasses.cpp Inventory.cpp)
target_link_libraries(kerml-representation-test PRIVATE kerml sysmlv2interfaces boost::boost)
add_test(NAME kerml-representation COMMAND kerml-representation-test)

find_package(Python3 COMPONENTS Interpreter QUIET)
if(Python3_Interpreter_FOUND)
    add_test(NAME kerml-generated-files COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/../tools/generate_abstract_syntax.py --check)
endif()
