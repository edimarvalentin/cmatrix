cmake_minimum_required(VERSION 3.31)
project(cmatrix C)

set(CMAKE_C_STANDARD 90)

add_library(cmatrix STATIC src/sparse.c
        src/dense.c
        include/sparse.h
        include/dense.h
)
target_include_directories(cmatrix PUBLIC include)

add_subdirectory(test)




