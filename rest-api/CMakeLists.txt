cmake_minimum_required(VERSION 3.15)

project(sysmlv2rest CXX C)

find_package(nlohmann_json REQUIRED)
find_package(Boost REQUIRED)
find_package(date REQUIRED)

set(ENTITIES_HEADER
        src/entities/DataIdentity.h
        src/entities/Record.h
        src/entities/IEntity.h
        src/entities/Project.h
        src/entities/JSONEntities.h
        src/entities/Commit.h
        src/entities/CommitReference.h
        src/entities/DataVersion.h
        src/entities/Query.h
        src/entities/Tag.h
        src/entities/Branch.h
        src/entities/Data.h
        src/entities/ProjectUsage.h
        src/entities/Element.h
        src/entities/Relationship.h
        src/entities/ExternalData.h
        src/entities/ExternalRelationship.h
        src/entities/Identification.h
        src/entities/Direction.h
        src/entities/ChangeType.h
        src/entities/MergeResult.h
        src/entities/DataDifference.h)

set(SERIALIZATION_HEADER
        src/serialization/SysMLv2Deserializer.h)


add_library(sysmlv2rest
        src/entities/DataIdentity.cpp
        src/entities/Record.cpp
        src/entities/Project.cpp
        src/entities/Commit.cpp
        src/entities/CommitReference.cpp
        src/entities/DataVersion.cpp
        src/entities/Query.cpp
        src/entities/Tag.cpp
        src/entities/Branch.cpp
        src/entities/Data.cpp
        src/entities/ProjectUsage.cpp
        src/entities/Element.cpp
        src/entities/Relationship.cpp
        src/entities/ExternalData.cpp
        src/entities/ExternalRelationship.cpp
        src/entities/Identification.cpp
        src/serialization/SysMLv2Deserializer.cpp
        src/entities/MergeResult.cpp
        src/entities/DataDifference.cpp
        ${ENTITIES_HEADER}
        ${SERIALIZATION_HEADER})

target_link_libraries(sysmlv2rest
        boost::boost
        nlohmann_json::nlohmann_json
        date::date)


include(GNUInstallDirs)
install(TARGETS sysmlv2rest ARCHIVE DESTINATION lib)
install(FILES ${ENTITIES_HEADER} DESTINATION include/sysmlv2/rest/entities)
install(FILES ${SERIALIZATION_HEADER} DESTINATION include/sysmlv2/rest/serialization)

if(MSVC)
    target_compile_options(sysmlv2rest PRIVATE /W4 /WX- /bigobj)
else ()
    target_compile_options(sysmlv2rest PRIVATE -Wall -Wextra -Wpedantic -Werror)
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