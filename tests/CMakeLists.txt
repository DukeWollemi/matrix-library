find_package(GTest REQUIRED)

add_executable(test_matrix test_matrix.cpp)
target_link_libraries(test_matrix PRIVATE Matrix GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(test_matrix)