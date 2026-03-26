//
// Created by oelshora on 01/02/2026.
//

#include <gtest/gtest.h>
#include "matrix/Matrix.h"

// Default constructor

TEST(MatrixDefaultConstructor, CreatesEmptyMatrix) {
    Matrix<int> matrix;

    EXPECT_EQ(matrix.rows(), 0);
    EXPECT_EQ(matrix.cols(), 0);
    EXPECT_EQ(matrix.size(), 0);
    EXPECT_TRUE(matrix.empty());
    EXPECT_EQ(matrix.data(), nullptr);
}

