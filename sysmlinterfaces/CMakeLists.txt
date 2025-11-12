cmake_minimum_required(VERSION 3.15)

project(sysmlv2interfaces CXX)

set(GLOBAL_HEADER
        include/sysmlv2/interfaces/sysmlv2interfaces_global.h)

set(INTERFACE_HEADER
        include/sysmlv2/service/interfaces/IProjectUsageService.h
        include/sysmlv2/service/interfaces/IElementNavigationService.h
        include/sysmlv2/service/interfaces/IExternalReleationshipService.h
        include/sysmlv2/service/interfaces/IProjectService.h
        include/sysmlv2/service/interfaces/IProjectVersioningService.h
        include/sysmlv2/service/interfaces/IQueryService.h)

set(REST_HEADER
        include/sysmlv2/rest/entities/IEntity.h
        include/sysmlv2/rest/entities/Data.h)

add_library(sysmlv2interfaces
        ${GLOBAL_HEADER}
        ${INTERFACE_HEADER}
        ${REST_HEADER}
        src/sysmlv2/rest/entities/Data.cpp)

target_link_libraries(sysmlv2interfaces
        boost::boost
        nlohmann_json::nlohmann_json
        date::date)

target_include_directories(sysmlv2interfaces PUBLIC
        ./include)

include(GNUInstallDirs)
install(TARGETS sysmlv2interfaces ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(TARGETS sysmlv2interfaces RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(FILES ${GLOBAL_HEADER} DESTINATION include/sysmlv2/interfaces)
install(FILES ${INTERFACE_HEADER} DESTINATION include/sysmlv2/service/interfaces)
install(FILES ${REST_HEADER} DESTINATION include/sysmlv2/rest/entities)

if(MSVC)
    target_compile_options(sysmlv2interfaces PRIVATE /W4 /WX- /bigobj)
else ()
    target_compile_options(sysmlv2interfaces PRIVATE -Wall -Wextra -Wpedantic -Werror)
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