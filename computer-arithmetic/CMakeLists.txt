cmake_minimum_required(VERSION 3.10)
project(lab1)

set(CMAKE_CXX_STANDARD 17)

add_library(lab1 ex1/ex1.cpp ex2/ex2.cpp ex3/ex3.cpp ex4/ex4.cpp)

# order matters
link_libraries(-lgsl -lgslcblas -lm)

add_executable(ex1 ex1/ex1.cpp)
add_executable(ex2 ex2/ex2.cpp)
add_executable(ex3 ex3/ex3.cpp)
add_executable(ex4 ex4/ex4.cpp)

