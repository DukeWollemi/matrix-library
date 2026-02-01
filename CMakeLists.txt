cmake_minimum_required(VERSION 3.31)
project(Matrix_library)

set(CMAKE_CXX_STANDARD 20)

# Header-only library
add_library(Matrix INTERFACE)
target_include_directories(Matrix INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

# Build examples
add_subdirectory(examples)

# Build tests
option(BUILD_TESTS "Build tests" ON)
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
