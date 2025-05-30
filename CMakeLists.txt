cmake_minimum_required(VERSION 3.31)
project(cmatrix C)

set(CMAKE_C_STANDARD 90)

add_library(cmatrix STATIC src/sparse.c
        src/dense.c
        include/sparse.h
        include/dense.h
        test/dense_mread/test_mread.c
)
target_include_directories(cmatrix PUBLIC include)

# Enable testing
enable_testing()

# Test executable for mread
add_executable(test_sparse_mread test/sparse_mread/test_mread.c)
target_link_libraries(test_sparse_mread PRIVATE cmatrix)
target_include_directories(test_sparse_mread PRIVATE include)

configure_file(
        ${CMAKE_SOURCE_DIR}/test/sparse_mread/mread_input_0.txt
        ${CMAKE_BINARY_DIR}/sparse_mread_input_0.txt
        COPYONLY
)

configure_file(
        ${CMAKE_SOURCE_DIR}/test/sparse_mread/mread_input_1.txt
        ${CMAKE_BINARY_DIR}/sparse_mread_input_1.txt
        COPYONLY
)

configure_file(
        ${CMAKE_SOURCE_DIR}/test/sparse_mread/mread_input_2.txt
        ${CMAKE_BINARY_DIR}/sparse_mread_input_2.txt
        COPYONLY
)

add_test(NAME test_sparse_mread COMMAND test_sparse_mread)

add_executable(test_dense_mread test/dense_mread/test_mread.c)
target_link_libraries(test_dense_mread PRIVATE cmatrix)
target_include_directories(test_sparse_mread PRIVATE include)

configure_file(
        ${CMAKE_SOURCE_DIR}/test/dense_mread/mread_input_0.txt;
        ${CMAKE_BINARY_DIR}/dense_mread_input_0.txt
        COPYONLY
)

configure_file(
        ${CMAKE_SOURCE_DIR}/test/dense_mread/mread_input_1.txt;
        ${CMAKE_BINARY_DIR}/dense_mread_input_1.txt
        COPYONLY
)

configure_file(
        ${CMAKE_SOURCE_DIR}/test/dense_mread/mread_input_2.txt;
        ${CMAKE_BINARY_DIR}/dense_mread_input_2.txt
        COPYONLY
)

add_test(NAME test_dense_mread COMMAND test_dense_mread)
