cmake_minimum_required(VERSION 3.15)

project(CPP-SysMLv2-Lib CXX C)

find_package(nlohmann_json REQUIRED)
find_package(Boost REQUIRED)
find_package(date REQUIRED)

add_library(CPP-SysMLv2-Lib

        src/entities/DataIdentity.cpp
        src/entities/DataIdentity.h
        src/entities/Record.cpp
        src/entities/Record.h
        src/entities/IEntity.h
        src/entities/Project.cpp
        src/entities/Project.h
        src/entities/JSONEntities.h
        src/entities/DigitalTwin.cpp
        src/entities/DigitalTwin.h
        src/entities/Commit.cpp
        src/entities/Commit.h
        src/entities/CommitReference.cpp
        src/entities/CommitReference.h
        src/entities/DataVersion.cpp
        src/entities/DataVersion.h
        src/entities/Query.cpp
        src/entities/Query.h
        src/entities/Tag.cpp
        src/entities/Tag.h
        src/entities/Branch.cpp
        src/entities/Branch.h
        src/entities/Data.cpp
        src/entities/Data.h
        src/entities/ProjectUsage.cpp
        src/entities/ProjectUsage.h
        src/entities/Element.cpp
        src/entities/Element.h
        src/entities/Relationship.cpp
        src/entities/Relationship.h
        src/entities/ExternalData.cpp
        src/entities/ExternalData.h
        src/entities/ExternalRelationship.cpp
        src/entities/ExternalRelationship.h
        src/entities/Identification.cpp
        src/entities/Identification.h

        src/serialization/SysMLv2Deserializer.cpp
        src/serialization/SysMLv2Deserializer.h

        src/services/IProjectUsageService.h
        src/entities/Direction.h
        src/entities/ChangeType.h
        src/entities/MergeResult.cpp
        src/entities/MergeResult.h
        src/entities/DataDifference.cpp
        src/entities/DataDifference.h)

target_link_libraries(CPP-SysMLv2-Lib
        boost::boost
        nlohmann_json::nlohmann_json
        date::date)

install(TARGETS CPP-SysMLv2-Lib DESTINATION "src"
        RUNTIME DESTINATION bin
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib)

if(MSVC)
    target_compile_options(CPP-SysMLv2-Lib PRIVATE /W4 /WX- /bigobj)
elseif (UNIX AND NOT APPLE)
    target_compile_options(CPP-SysMLv2-Lib PRIVATE -Wall -Wextra -Wpedantic -Werror)
else ()
    target_compile_options(CPP-SysMLv2-Lib PRIVATE -Wall -Wextra -Wpedantic -Werror)
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