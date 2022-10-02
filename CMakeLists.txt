cmake_minimum_required(VERSION 3.24)

project(vectormatrix_test CXX)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/release-1.12.0.zip
)
FetchContent_MakeAvailable(googletest)
enable_testing()

add_executable(VectorMatrixTest test/vec_test.cpp test/mat_test.cpp test/vec_mat_test.cpp)
target_link_libraries(VectorMatrixTest gtest_main)

include(GoogleTest)
gtest_discover_tests(VectorMatrixTest)
