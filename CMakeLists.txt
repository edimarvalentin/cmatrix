cmake_minimum_required(VERSION 3.31)
project(cmatrix C)

set(CMAKE_C_STANDARD 90)

add_executable(cmatrix src/main.c
        src/cmatrix.c
        include/cmatrix.h)
