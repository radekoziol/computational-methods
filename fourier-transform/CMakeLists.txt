cmake_minimum_required(VERSION 3.10)
project(fourier_transform)

set(CMAKE_CXX_STANDARD 14)

add_library(fourier-transform fourier.cpp main.cpp)

add_executable(fourier_transform_main fourier.cpp)