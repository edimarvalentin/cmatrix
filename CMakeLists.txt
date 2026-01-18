cmake_minimum_required(VERSION 3.31)
project(cmatrix C)

set(CMAKE_C_STANDARD 90)

add_library(cmatrix STATIC src/sparse.c
        include/dense.h
        src/dense.c
        include/sparse.h
        src/sparse.c
        include/add.h
        src/add.c
)
target_include_directories(cmatrix PUBLIC include)

add_subdirectory(test)




