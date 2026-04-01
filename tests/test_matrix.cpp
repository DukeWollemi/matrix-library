//
// Created by oelshora on 01/02/2026.
//

#include <iso646.h>
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


    EXPECT_THROW({Matrix<int> m({ {1, 2}, {3} });}, std::invalid_argument);
}

TEST(MatrixCopyConstructor, CreatesDeepCopy)
{
    Matrix<int> original{ {1, 2}, {3, 4} };
    Matrix<int> copy{ original };

    EXPECT_EQ(copy.rows(), 2);
    EXPECT_EQ(copy.cols(), 2);
    EXPECT_NE(copy.data(), original.data());

    copy(0, 0) = 99;

    EXPECT_EQ(copy(0, 0), 99);
    EXPECT_EQ(original(0, 0), 1);
}

TEST(MatrixCopyAssignment, AssignmentOperatorUpdatesExistingObject)
{
    Matrix<int> original{ {1,2}, {3, 4} };
    Matrix<int> copy{ {6, 7}, {8, 9} };

	copy = original;

    EXPECT_EQ(copy.data(), original.data());
}