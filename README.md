# Cmaker: CMakeLists.txt generator

CMaker is a command line CMakelists.txt generator


## Requirement
- [Conan](https://conan.io/): Version 2.x (Package manager)
- [CMake](https://cmake.org/): Version 3.10 or higher
- C++ Compiler: [GCC](https://gcc.gnu.org/), [Clang](https://clang.llvm.org/), [MSVC](https://visualstudio.microsoft.com/)
- [Python](https://www.python.org/): Required for Conan (ensure Python 3.x is installed)

## Install
``` bash
git clone https://github.com/taaheer/CMaker.git
conan install . --build=missing
cmake --preset conan-release
cmake --build --preset conan-release
```

## Usage: cmaker <operation>
operations:
``` bash
cmaker {-h --help}
cmaker {-v --version}
cmaker {-M --make}
cmaker {-R --remove}
```
