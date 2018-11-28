# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("matrix_transposition")

add_executable(main main.cpp transposition.cpp)
