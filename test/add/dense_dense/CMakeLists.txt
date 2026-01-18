# Test executable for add (dense + dense)
add_executable(test_add_dense_dense test_add_dense_dense.c)
target_link_libraries(test_add_dense_dense PRIVATE cmatrix)
target_include_directories(test_add_dense_dense PRIVATE ${CMAKE_SOURCE_DIR}/include)

add_test(NAME test_add_dense_dense COMMAND test_add_dense_dense)


