cmake_minimum_required(VERSION 3.14)
project(CLI11_Project)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the main executable
add_executable(cmaker
    CMake.cpp
    CMaker.cpp
    Common.cpp
    Project.cpp
    Utility.cpp
)

find_package(CLI11 REQUIRED)

target_link_libraries(cmaker CLI11::CLI11)
