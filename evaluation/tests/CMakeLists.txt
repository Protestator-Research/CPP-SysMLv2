add_executable(sysmlv2evaluation-test
        TestMain.cpp
        TestSupport.h
        TestValue.cpp
        TestQualifiedName.cpp
        TestRegistry.cpp
        TestDataFunctions.cpp
        TestBaseFunctions.cpp
        TestControlFunctions.cpp
        TestEvaluator.cpp
        TestUserFunctions.cpp)
target_link_libraries(sysmlv2evaluation-test sysmlv2evaluation kerml sysmlv2interfaces nlohmann_json::nlohmann_json Boost::headers gtest::gtest)
target_include_directories(sysmlv2evaluation-test PRIVATE
        ../../kerml/include
        ../../sysmlinterfaces/include)
if(MSVC)
    target_compile_options(sysmlv2evaluation-test PRIVATE /W4 /WX- /bigobj)
else()
    target_compile_options(sysmlv2evaluation-test PRIVATE -Wall -Wextra -Wpedantic $<$<BOOL:${SYSMLV2_WERROR}>:-Werror>)
endif()
add_test(NAME sysmlv2evaluation COMMAND sysmlv2evaluation-test)
