cmake_minimum_required(VERSION 3.15)

project(sysmlv2rest CXX C)

find_package(nlohmann_json REQUIRED)
find_package(Boost REQUIRED)
find_package(date REQUIRED)

set(GLOBAL_HEADER
        include/sysmlv2/rest/sysmlv2rest_global.h
)

set(ENTITIES_HEADER
        include/sysmlv2/rest/entities/DataIdentity.h
        include/sysmlv2/rest/entities/Record.h
        include/sysmlv2/rest/entities/Project.h
        include/sysmlv2/rest/entities/JSONEntities.h
        include/sysmlv2/rest/entities/Commit.h
        include/sysmlv2/rest/entities/CommitReference.h
        include/sysmlv2/rest/entities/CommitRequest.h
        include/sysmlv2/rest/entities/DataVersion.h
        include/sysmlv2/rest/entities/Query.h
        include/sysmlv2/rest/entities/Tag.h
        include/sysmlv2/rest/entities/Branch.h
        include/sysmlv2/rest/entities/ProjectUsage.h
        include/sysmlv2/rest/entities/Element.h
        include/sysmlv2/rest/entities/Relationship.h
        include/sysmlv2/rest/entities/ExternalData.h
        include/sysmlv2/rest/entities/ExternalRelationship.h
        include/sysmlv2/rest/entities/Identification.h
        include/sysmlv2/rest/entities/Direction.h
        include/sysmlv2/rest/entities/ChangeType.h
        include/sysmlv2/rest/entities/MergeResult.h
        include/sysmlv2/rest/entities/DataDifference.h)

set(SERIALIZATION_HEADER
        include/sysmlv2/rest/serialization/SysMLv2Deserializer.h
        include/sysmlv2/rest/serialization/Utilities.hpp)


add_library(sysmlv2rest
        src/sysmlv2/rest/entities/DataIdentity.cpp
        src/sysmlv2/rest/entities/Record.cpp
        src/sysmlv2/rest/entities/Project.cpp
        src/sysmlv2/rest/entities/Commit.cpp
        src/sysmlv2/rest/entities/CommitRequest.cpp
        src/sysmlv2/rest/entities/CommitReference.cpp
        src/sysmlv2/rest/entities/DataVersion.cpp
        src/sysmlv2/rest/entities/Query.cpp
        src/sysmlv2/rest/entities/Tag.cpp
        src/sysmlv2/rest/entities/Branch.cpp
        src/sysmlv2/rest/entities/ProjectUsage.cpp
        src/sysmlv2/rest/entities/Element.cpp
        src/sysmlv2/rest/entities/Relationship.cpp
        src/sysmlv2/rest/entities/ExternalData.cpp
        src/sysmlv2/rest/entities/ExternalRelationship.cpp
        src/sysmlv2/rest/entities/Identification.cpp
        src/sysmlv2/rest/serialization/SysMLv2Deserializer.cpp
        src/sysmlv2/rest/entities/MergeResult.cpp
        src/sysmlv2/rest/entities/DataDifference.cpp
        ${ENTITIES_HEADER}
        ${SERIALIZATION_HEADER}
        ${GLOBAL_HEADER})

target_link_libraries(sysmlv2rest
        boost::boost
        nlohmann_json::nlohmann_json
        date::date)

include(GNUInstallDirs)
install(TARGETS sysmlv2rest ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(TARGETS sysmlv2rest RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(FILES ${ENTITIES_HEADER} DESTINATION include/sysmlv2/rest/entities)
install(FILES ${GLOBAL_HEADER} DESTINATION include/sysmlv2/rest)
install(FILES ${SERIALIZATION_HEADER} DESTINATION include/sysmlv2/rest/serialization)



if(MSVC)
    target_compile_options(sysmlv2rest PRIVATE /W4 /WX- /bigobj)
    target_link_directories(sysmlv2rest PUBLIC ${CMAKE_BINARY_DIR}/out)
    target_include_directories(sysmlv2rest PUBLIC
        ./include/)
else ()
    target_compile_options(sysmlv2rest PRIVATE -Wall -Wextra -Wpedantic -Werror)
    target_include_directories(sysmlv2rest PRIVATE
        ./include/)
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