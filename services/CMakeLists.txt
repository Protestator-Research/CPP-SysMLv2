cmake_minimum_required(VERSION 3.15)

project(sysmlv2service CXX C)

set(GLOBAL_HEADER
        include/sysmlv2/service/sysmlv2service_global.h)

set(API_HEADER
        include/sysmlv2/service/implementation/ElementNavigationService.h
        include/sysmlv2/service/implementation/ProjectService.h
        include/sysmlv2/service/implementation/ProjectUsageService.h
        include/sysmlv2/service/implementation/ProjectVersioningService.h)

set(ONLINE_HEADER
        include/sysmlv2/service/online/ConnectionError.h
        include/sysmlv2/service/online/HttpException.h
        include/sysmlv2/service/online/NotEnoughMemoryError.h
        include/sysmlv2/service/online/HttpReturnCodes.h
        include/sysmlv2/service/online/StatusCode.h
        include/sysmlv2/service/online/SysMLAPIImplementation.h)

add_library(sysmlv2service
        ${GLOBAL_HEADER}
        ${API_HEADER}
        ${INTERFACE_HEADER}
        ${ONLINE_HEADER}
        src/sysmlv2/service/implementation/ElementNavigationService.cpp
        src/sysmlv2/service/implementation/ProjectService.cpp
        src/sysmlv2/service/implementation/ProjectUsageService.cpp
        src/sysmlv2/service/implementation/ProjectVersioningService.cpp
        src/sysmlv2/service/online/ConnectionError.cpp
        src/sysmlv2/service/online/HttpException.cpp
        src/sysmlv2/service/online/NotEnoughMemoryError.cpp
        src/sysmlv2/service/online/SysMLAPIImplementation.cpp)

target_link_libraries(sysmlv2service
        boost::boost
        nlohmann_json::nlohmann_json
        date::date
        sysmlv2rest)


include(GNUInstallDirs)
install(TARGETS sysmlv2service ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(TARGETS sysmlv2service RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(FILES ${GLOBAL_HEADER} DESTINATION include/sysmlv2/service)
install(FILES ${API_HEADER} DESTINATION include/sysmlv2/service/implementation)
install(FILES ${ONLINE_HEADER} DESTINATION include/sysmlv2/service/online)

if(MSVC)
    target_compile_options(sysmlv2service PRIVATE /W4 /WX- /bigobj)
    target_link_directories(sysmlv2service PUBLIC ${CMAKE_BINARY_DIR}/out)
    target_include_directories(sysmlv2service PUBLIC
        ./include
        ../rest-api/include)
else ()
    target_compile_options(sysmlv2service PRIVATE -Wall -Wextra -Wpedantic -Werror)
    target_include_directories(sysmlv2service PRIVATE
        ./include
        ../rest-api/include)
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