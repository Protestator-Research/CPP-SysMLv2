add_executable(kerml-representation-test MissingClasses.cpp Inventory.cpp)
target_link_libraries(kerml-representation-test PRIVATE kerml sysmlv2interfaces Boost::headers)
add_test(NAME kerml-representation COMMAND kerml-representation-test)
