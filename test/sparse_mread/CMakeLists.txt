# Test executable for mread
add_executable(test_sparse_mread test_mread.c)
target_link_libraries(test_sparse_mread PRIVATE cmatrix)
target_include_directories(test_sparse_mread PRIVATE include)

configure_file(
        mread_input_0.txt
        sparse_mread_input_0.txt
        COPYONLY
)

configure_file(
        mread_input_1.txt
        sparse_mread_input_1.txt
        COPYONLY
)

configure_file(
        mread_input_2.txt
        sparse_mread_input_2.txt
        COPYONLY
)

add_test(NAME test_sparse_mread COMMAND test_sparse_mread)
