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

TEST(MatrixSizeConstructor, TestNormalAndZero) {
    Matrix<int> matrix(2,3);
    EXPECT_EQ(matrix.rows(), 2);
    EXPECT_EQ(matrix.cols(), 3);
    EXPECT_EQ(matrix.size(), 6);
    EXPECT_FALSE(matrix.empty());
    EXPECT_NE(matrix.data(), nullptr);

    Matrix<int> matrix2(0, 3);
    EXPECT_EQ(matrix2.size(), 0);
    EXPECT_TRUE(matrix2.empty());
    EXPECT_NE(matrix2.data(), nullptr);
}

TEST(MatrixSizeConstructor, CreatesMatrixWithCorrectShape) {
    Matrix<int> matrix(2, 3);

    EXPECT_EQ(matrix.rows(), 2);
    EXPECT_EQ(matrix.cols(), 3);
    EXPECT_EQ(matrix.size(), 6);
    EXPECT_FALSE(matrix.empty());
    EXPECT_NE(matrix.data(), nullptr);
}

TEST(MatrixSizeConstructor, ZeroSizedMatrixHasNoStorage) {
    Matrix<int> matrix(0, 3);

    EXPECT_EQ(matrix.rows(), 0);
    EXPECT_EQ(matrix.cols(), 3);
    EXPECT_EQ(matrix.size(), 0);
    EXPECT_TRUE(matrix.empty());
    EXPECT_EQ(matrix.data(), nullptr);
}