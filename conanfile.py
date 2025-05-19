from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout, CMakeDeps
from conan.tools.env import Environment
from conan.tools.apple import XcodeDeps
import os
from sys import platform


class CPPSysMLRecipe(ConanFile):
    name = "sysmllib"
    #version = ""
    package_type = "library"

    # Optional metadata
    license = "<Put the package license here>"
    author = "Moritz Herzog"
    url = "https://github.com/Protestator-Research/CPP-SysMLv2"
    description = ("This library defines a SysMLv2 C++ Library allowing the usage of this for other projects.")
    topics = ("SysMLv2", "modeling", "library")

    # Binary configuration
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False], "fPIC": [True, False], "with_rest": [True, False], "with_services":[True, False], "with_parsing":[True,False]}
    default_options = {"shared": True, "fPIC": False, "with_rest": True, "with_services": True, "with_parsing": True}

    # Sources are located in the same place as this recipe, copy them to the recipe
    exports_sources = "CMakeLists.txt", "interfaces/*", "conformance-test/*", "filehandling/*", "kerml/*", "rest-api/*", "services/*"

    def requirements(self):
        self.requires("boost/1.84.0")
        self.requires("nlohmann_json/3.11.3")
        self.requires("date/3.0.1")
        self.requires("libcurl/8.4.0")
        if(self.options.with_parsing):
            self.requires("flex/2.6.4")
            self.requires("bison/3.8.2")
            self.requires("antlr4-cppruntime/4.13.1")

    def config_options(self):
        if self.settings.os == "Windows":
            del self.options.fPIC

    def configure(self):
        if self.options.shared:
            self.options.rm_safe("fPIC")
            self.options["boost/*"].shared = True
            self.options["nlohmann_json/*"].shared = True
            self.options["date/*"].shared = True
            self.options["gtest/*"].shared = True
            self.options["libcurl/*"].shared = True
            if(self.options.with_parsing):
                self.options["antlr4-cppruntime/*"].shared = True
        else:
            self.options["boost/*"].shared = False
            self.options["nlohmann_json/*"].shared = False
            self.options["date/*"].shared = False
            self.options["gtest/*"].shared = False
            self.options["libcurl/*"].shared = False
            if(self.options.with_parsing):
                self.options["antlr4-cppruntime/*"].shared = False

    def layout(self):
        cmake_layout(self)

    def generate(self):
        deps = CMakeDeps(self)
        deps.generate()
        tc = CMakeToolchain(self)

        if(self.options.with_parsing):
            tc.variables["BUILD_WITH_PARSING"]=True

        tc.user_presets_path = 'CMakePresets.json'
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def build_requirements(self):
        self.tool_requires("cmake/3.30.0")
        self.test_requires("gtest/1.14.0")

    def test(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.test()

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.libs = ["sysmlv2service", "sysmlv2rest", "kerml", "sysmlv2file"]
        self.cpp_info.builddirs.append(os.path.join("lib", "cmake", "sysmlv2"))

    

    
