//
// Created by oelshora on 01/02/2026.
//

#include <gtest/gtest.h>
#include "matrix/Matrix.h"

// Default constructor

TEST(MatrixDefaultConstructor, ProducesEmptyMatrix) {
    Matrix<int> m;
    EXPECT_EQ(m.rows(), 0u);
    EXPECT_EQ(m.cols(), 0u);
    EXPECT_EQ(m.size(), 0u);
    EXPECT_TRUE(m.empty());
    EXPECT_EQ(m.data(), nullptr);
}

