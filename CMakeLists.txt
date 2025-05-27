cmake_minimum_required(VERSION 3.31)
project(cmatrix C)

set(CMAKE_C_STANDARD 90)

add_library(cmatrix STATIC src/cmatrix.c)
target_include_directories(cmatrix PUBLIC include)

# Enable testing
enable_testing()

# Test executable for mread
add_executable(test_mread test/mread/test_mread.c)
target_link_libraries(test_mread PRIVATE cmatrix)
target_include_directories(test_mread PRIVATE include)

configure_file(
        ${CMAKE_SOURCE_DIR}/test/mread/mread_input_0.txt
        ${CMAKE_BINARY_DIR}/mread_input_0.txt
        COPYONLY
)

configure_file(
        ${CMAKE_SOURCE_DIR}/test/mread/mread_input_1.txt
        ${CMAKE_BINARY_DIR}/mread_input_1.txt
        COPYONLY
)

configure_file(
        ${CMAKE_SOURCE_DIR}/test/mread/mread_input_2.txt
        ${CMAKE_BINARY_DIR}/mread_input_2.txt
        COPYONLY
)

add_test(NAME test_mread COMMAND test_mread)
