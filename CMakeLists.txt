cmake_minimum_required(VERSION 3.15)

project(sysmlv2 CXX C)

find_package(nlohmann_json REQUIRED)
find_package(Boost REQUIRED)
find_package(date REQUIRED)

option(BUILD_WITH_REST "Builds with the SysMLv2 REST API" ON)
option(BUILD_WITH_SERVICES "Builds with the SysMLv2 services API" ON)
option(BUILD_WITH_PARSING "Builds with the SysMLv2 parsing API" ON)


add_subdirectory(interfaces)

if (BUILD_WITH_REST)
    add_subdirectory(rest-api)
endif ()

if (BUILD_WITH_SERVICES)
    add_subdirectory(services)
endif ()

if (BUILD_WITH_PARSING)
    add_subdirectory(filehandling)
endif ()