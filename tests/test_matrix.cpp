//
// Created by oelshora on 01/02/2026.
//

#include <gtest/gtest.h>
#include "matrix/Matrix.h"

// Default constructor

// A test smoke to make sure a Matrix can be contructed
TEST(MatrixContruct, CanBeConstructed) {
    //This test passes if the constructor and destructor can be called without crashing or throwing an unhandled exception.
    Matrix<int> matrix{ 2, 6 };
    
	// Testing with empty init list.
	Matrix<double> d_matrix{};

    // Testing default constructor
    Matrix<int> def_matrix;

    // Testing matrix with value
    Matrix<int> value_matrix{ 4, 5, 9 };

    SUCCEED(); // Explicitly mark the test as successful.
}

