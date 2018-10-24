cmake_minimum_required(VERSION 3.10)
project(linear_eq_matrixes)

set(CMAKE_CXX_STANDARD 11)

add_library(matrixLib aghMatrix.cpp aghMatrix.h main.cpp)

add_executable(main main.cpp)
