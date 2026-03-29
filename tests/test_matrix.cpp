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

    Matrix<int> matrix2(3,0);

    EXPECT_EQ(matrix2.rows(), 3);
    EXPECT_EQ(matrix2.cols(), 0);
    EXPECT_EQ(matrix2.size(), 0);
    EXPECT_TRUE(matrix2.empty());
    EXPECT_EQ(matrix2.data(), nullptr);
}

TEST(MatrixValueConstructor, FillsAllElementsWithGivenValue) {
    Matrix<int> matrix(2,3,7);

    EXPECT_EQ(matrix.rows(), 2);
    EXPECT_EQ(matrix.cols(), 3);
    EXPECT_EQ(matrix.size(), 6);
    EXPECT_FALSE(matrix.empty());
    EXPECT_NE(matrix.data(), nullptr);

    EXPECT_EQ(matrix(0,0), 7);
    EXPECT_EQ(matrix(1, 0), 7);
}

TEST(TestInitListConstructor, CreatesValidInitConstructorWithShapeAndElements) {
    Matrix<int> matrix {{1, 2, 3}, {4,5,6}};

    EXPECT_EQ(matrix.rows(), 2);
    EXPECT_EQ(matrix.cols(), 3);

    EXPECT_EQ(matrix(0,0), 1);
    EXPECT_EQ(matrix(1, 1), 5);
}