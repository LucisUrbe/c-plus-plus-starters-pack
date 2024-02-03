# Set the minimum version of CMake that can be used
# To find the cmake version run
# $ cmake --version
cmake_minimum_required(VERSION 3.27.8)

# Set the project name
project(parenthesis_matching)

# Add an executable
add_executable(parenthesis_matching.exe parenthesis_matching.cc)
