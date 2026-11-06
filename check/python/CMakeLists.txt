# sysmlv2check-python: ONE self-contained shared library for the Python package sysmlv2 (loaded with ctypes).
#   Windows sysmlv2check_native.dll, Linux libsysmlv2check_native.so, macOS libsysmlv2check_native.dylib
# Our libraries, Boost, ANTLR4 runtime, pugixml, ... are linked statically (static build: -o '&:shared=False', BUILD_SHARED_LIBS=OFF,
# which defines SYSMLV2_STATIC, i.e. the *_EXPORT macros are empty). Exports ONLY the five functions of the C interface
# (sysml_pruefe, sysml_vorwaermen, sysml_konfigurieren, sysml_speicher, sysml_freigeben):
#   Windows  sysmlv2check_native.def
#   Linux    sysmlv2check_native.map (version script) + -fvisibility=hidden, libstdc++/libgcc linked statically (manylinux)
#   macOS    sysmlv2check_native.exp (-exported_symbols_list)
# CApi.cpp is compiled directly into this library (not taken from the archive sysmlv2check, whose member is never pulled in because
# nothing references it), so the C interface is always part of the library. Needs BUILD_WITH_CHECK and BUILD_PYTHON_MODULE.
# The *_EXPORT macros (visibility("default") with GCC/Clang) keep the five functions visible despite the hidden visibility preset.
# Windows: the static CRT (conan -s compiler.runtime=static) makes the DLL independent of MSVCP140/VCRUNTIME140.
# Install: cmake --install <build> --component python [--prefix <dir>]  (SYSMLV2_PYTHON_INSTALL_DIR = directory below the prefix, default `.`)
if(BUILD_SHARED_LIBS)
    message(FATAL_ERROR "BUILD_PYTHON_MODULE needs a static build (BUILD_SHARED_LIBS=OFF, conan option shared=False)")
endif()

set(SYSMLV2_PYTHON_INSTALL_DIR "." CACHE STRING "Install directory (below the prefix) of the Python module library")

add_library(sysmlv2check-python SHARED ../src/CApi.cpp)
set_target_properties(sysmlv2check-python PROPERTIES
        OUTPUT_NAME sysmlv2check_native
        CXX_VISIBILITY_PRESET hidden
        VISIBILITY_INLINES_HIDDEN ON)
target_link_libraries(sysmlv2check-python PRIVATE sysmlv2check)

if(WIN32)
    target_sources(sysmlv2check-python PRIVATE sysmlv2check_native.def)
elseif(APPLE)
    target_link_options(sysmlv2check-python PRIVATE "LINKER:-exported_symbols_list,${CMAKE_CURRENT_SOURCE_DIR}/sysmlv2check_native.exp")
else()
    target_link_options(sysmlv2check-python PRIVATE
            "LINKER:--version-script=${CMAKE_CURRENT_SOURCE_DIR}/sysmlv2check_native.map"
            LINKER:--exclude-libs,ALL LINKER:--no-undefined -static-libstdc++ -static-libgcc)
    set_property(TARGET sysmlv2check-python APPEND PROPERTY LINK_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/sysmlv2check_native.map)
endif()

install(TARGETS sysmlv2check-python COMPONENT python
        RUNTIME DESTINATION ${SYSMLV2_PYTHON_INSTALL_DIR}
        LIBRARY DESTINATION ${SYSMLV2_PYTHON_INSTALL_DIR}
        ARCHIVE DESTINATION lib COMPONENT python-dev EXCLUDE_FROM_ALL)  # import library (.lib): not part of the wheel
