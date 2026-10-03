from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout, CMakeDeps
from conan.tools.env import Environment
from conan.tools.apple import XcodeDeps
import os
from sys import platform


class CPPSysMLRecipe(ConanFile):
    name = "sysmllib"
    package_type = "library"

    # Optional metadata
    license = "GPL v3"
    author = "Moritz Herzog"
    url = "https://github.com/Protestator-Research/CPP-SysMLv2"
    description = "This library defines a SysMLv2 C++ Library allowing the usage of this for other projects."
    topics = ("SysMLv2", "modeling", "library")

    # Binary configuration
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False], "fPIC": [True, False], "with_rest": [True, False], "with_services":[True, False], "with_parsing":[True,False], "with_online":[True, False], "with_check":[True, False]}
    default_options = {"shared": True, "fPIC": True, "with_rest": True, "with_services": True, "with_parsing": True, "with_online": True, "with_check": False}

    # Sources are located in the same place as this recipe, copy them to the recipe
    exports_sources = "CMakeLists.txt", "interfaces/*", "conformance-test/*", "filehandling/*", "kerml/*", "rest-api/*", "services/*", "sysmlinterfaces/*", "resources/*", "sysml/*", "check/*"

    def requirements(self):
        self.requires("boost/[>=1.86.0 <2]")
        self.requires("nlohmann_json/[>=3.11.3 <44]")
        self.requires("date/3.0.4")
        if self.options.with_online:
            self.requires("libcurl/[>=8.4.0 <9]")
        self.requires("antlr4-cppruntime/4.13.2")

    def config_options(self):
        if self.settings.os == "Windows":
            del self.options.fPIC
            self.options.shared=True

    def configure(self):
        if not self.options.with_online:
            # date is only used through date/date.h (REST entities). Its time zone library, which the default build of the
            # package links, needs libcurl; the header-only variant needs nothing.
            self.options["date/*"].header_only = True
        if self.options.shared:
            self.options["boost/*"].shared = True
            self.options["nlohmann_json/*"].shared = True
            if self.options.with_online:
                self.options["date/*"].shared = True
            self.options["gtest/*"].shared = True
            if self.options.with_online:
                self.options["libcurl/*"].shared = True
            self.options["antlr4-cppruntime/*"].shared = True
        else:
            self.options["boost/*"].shared = False
            self.options["nlohmann_json/*"].shared = False
            if self.options.with_online:
                self.options["date/*"].shared = False
            self.options["gtest/*"].shared = False
            if self.options.with_online:
                self.options["libcurl/*"].shared = False
            self.options["antlr4-cppruntime/*"].shared = False

    def layout(self):
        cmake_layout(self)

    def generate(self):
        deps = CMakeDeps(self)
        deps.generate()
        tc = CMakeToolchain(self)

        if(self.options.with_parsing):
            tc.variables["BUILD_WITH_PARSING"]=True

        tc.variables["BUILD_WITH_ONLINE"] = bool(self.options.with_online)
        tc.variables["BUILD_WITH_CHECK"] = bool(self.options.with_check)

        tc.user_presets_path = 'CMakePresets.json'
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def build_requirements(self):
        self.tool_requires("cmake/[>=3.30.0 <5]")
        self.test_requires("gtest/[>=1.14.0 <2]")

    def test(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.test()

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.libs = ["sysmlv2interfaces", "sysmlv2service", "sysmlv2rest", "kerml", "sysmlv2parser", "sysmlv2resources", "sysml"]
        if self.options.with_check:
            self.cpp_info.libs.append("sysmlv2check")
        self.cpp_info.builddirs.append(os.path.join("lib", "cmake", "sysmlv2"))

    

    
