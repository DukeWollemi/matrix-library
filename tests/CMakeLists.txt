include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

if(MSVC)
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif()
FetchContent_MakeAvailable(googletest)

add_executable(test_matrix test_matrix.cpp)
target_link_libraries(test_matrix PRIVATE Matrix GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(test_matrix)