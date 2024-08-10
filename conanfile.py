from conan import ConanFile
from conan.tools.cmake import cmake_layout

class CMaker(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolchain"

    def requirements(self):
        self.requires("cli11/2.4.2")

    def layout(self):
        cmake_layout(self)
