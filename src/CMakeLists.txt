cmake_minimum_required(VERSION 4.0.0)
project(DataStructuresAndAlgorithms)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_FLAGS "-O3 -march=native -flto")
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_RELEASE TRUE)

add_subdirectory(containers)
add_subdirectory(test)
