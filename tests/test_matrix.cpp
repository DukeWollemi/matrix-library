//
// Created by oelshora on 01/02/2026.
//

#include <gtest/gtest.h>
#include "matrix/Matrix.h"

// A test smoke to make sure a Matrix can be contructed
TEST(MatrixContruct, CanBeConstructed) {
    //This test passes if the constructor and destructor can be called without crashing or throwing an unhandled exception.
    Matrix<int> matrix{2, 6};
    SUCCEED(); // Explicitly mark the test as successful.
}