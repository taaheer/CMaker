from conan import ConanFile
from conan.tools.cmake import cmake_layout

class CMaker(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolChain"

    def requirements(self):
        self.requires("cli1/*")

    def layout(self):
        cmake_layout(self)
