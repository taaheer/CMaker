cmake_minimum_required(VERSION 3.14)
project(CLI11_Project)

# Set C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Add subdirectories
add_subdirectory(CLI11)

# Add the main executable
add_executable(cmaker
    CMake.cpp
    CMaker.cpp
    Common.cpp
    Project.cpp
    Utility.cpp
)

# Link libraries to the main executable
target_link_libraries(cmaker PRIVATE CLI11)

