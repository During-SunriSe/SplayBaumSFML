cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(SplayTreeVisualization VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add an executable
add_executable(SplayTreeVisualization src/main.cpp)

# Find the SFML libraries
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Link the SFML libraries
target_link_libraries(SplayTreeVisualization sfml-graphics sfml-window sfml-system)

