from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout, CMakeDeps
from conan.tools.env import Environment
from conan.tools.apple import XcodeDeps
import os
from sys import platform


class CPPSysMLRecipe(ConanFile):
    name = "Cpp-SysMLv2-lib"
    version = "1.0-beta-3"
    package_type = "library"

    # Optional metadata
    license = "<Put the package license here>"
    author = "Moritz Herzog"
    url = "https://github.com/Protestator-Research/CPP-SysMLv2"
    description = ("This library defines a SysMLv2 C++ Library allowing the usage of this for other projects.")
    topics = ("SysMLv2", "modeling", "library")

    # Binary configuration
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False], "fPIC": [True, False]}
    default_options = {"shared": True, "fPIC": False}

    # Sources are located in the same place as this recipe, copy them to the recipe
    exports_sources = "CMakeLists.txt", "src/*"

    def requirements(self):
        self.requires("boost/1.84.0")
        self.requires("nlohmann_json/3.11.3")
        self.requires("date/3.0.1")

    def config_options(self):
        if self.settings.os == "Windows":
            del self.options.fPIC

    def configure(self):
        if self.options.shared:
            self.options.rm_safe("fPIC")
            self.options["boost/*"].shared = True
            self.options["nlohmann_json/*"].shared = True
            self.options["date/*"].shared = True
        else:
            self.options["boost/*"].shared = False
            self.options["nlohmann_json/*"].shared = False
            self.options["date/*"].shared = False

    def layout(self):
        cmake_layout(self)

    def generate(self):
        deps = CMakeDeps(self)
        deps.generate()
        tc = CMakeToolchain(self)
        tc.user_presets_path = 'CMakePresets.json'
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def build_requirements(self):
        self.tool_requires("cmake/3.30.0")
        self.test_requires("gtest/1.14.0")

    #def test(self):
        #cmd = os.path.join(self.cpp.build.bindir, "To be determined")
        #self.run(cmd, env="conanrun")

    def package(self):
        cmake = CMake(self)
        cmake.install()

    

    
