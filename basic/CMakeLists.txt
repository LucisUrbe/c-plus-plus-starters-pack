# Set the minimum version of CMake that can be used
# To find the cmake version run
# $ cmake --version
cmake_minimum_required(VERSION 3.27.8)

# Set the project name
project(basic)

# Add an executable
add_executable(basic.exe 01-average-and-rounding.cc)
