find_package(GTest REQUIRED)
#enable_testing()

set(CMAKE_CXX_STANDARD 11)

add_executable(test_matrix_one_thread tests_matrix_transpose_one_thread.cpp)
target_link_libraries(test_matrix_one_thread lib_matrix_one_thread ${GTEST_LIBRARIES} GTest::Main)
target_include_directories(test_matrix_one_thread PRIVATE ../include)

add_executable(test_matrix_multi_thread tests_matrix_transpose_multi_thread.cpp)
target_link_libraries(test_matrix_multi_thread lib_matrix_multi_thread ${GTEST_LIBRARIES} GTest::Main)
target_include_directories(test_matrix_multi_thread PRIVATE ../include)

add_subdirectory(stress)