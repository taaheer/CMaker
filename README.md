# Cmaker: CMakeLists.txt generator

CMaker is a command line CMakelists.txt generator


## Requirement
- C++23
- CLI11

## Install
``` bash
git clone --recurse-submodule https://github.com/taaheer/CMaker.git
cd CMaker
mkdir Build
cd Build
cmake ..
make
```

## Usage: cmaker <operation>
operations:
``` bash
cmaker {-h --help}
cmaker {-v --version}
cmaker {-M --make}
cmaker {-R --remove}
```
