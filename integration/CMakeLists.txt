cmake_minimum_required(VERSION 3.10)
project(integration)

set(CMAKE_CXX_STANDARD 11)

add_library(diffEq aghIntegration.cpp aghIntegration.h main.cpp)
add_executable(main main.cpp)