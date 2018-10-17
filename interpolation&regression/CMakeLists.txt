cmake_minimum_required(VERSION 3.10)
project(interpolation)

set(CMAKE_CXX_STANDARD 17)

add_library(interpolation interpolation.cpp regression.cpp)

add_executable(interpolation.cpp interpolation.cpp)