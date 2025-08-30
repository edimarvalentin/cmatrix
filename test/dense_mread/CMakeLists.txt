# Test executable for mread
add_executable(test_dense_mread test_mread.c)
target_link_libraries(test_dense_mread PRIVATE cmatrix)
target_include_directories(test_dense_mread PRIVATE ${CMAKE_SOURCE_DIR}/include)

configure_file(
        mread_input_0.txt
        dense_mread_input_0.txt
        COPYONLY
)

configure_file(
        mread_input_1.txt
        dense_mread_input_1.txt
        COPYONLY
)

configure_file(
        mread_input_2.txt
        dense_mread_input_2.txt
        COPYONLY
)

add_test(NAME test_dense_mread COMMAND test_dense_mread)
