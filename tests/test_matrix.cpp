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

// Size constructor  (rows × cols)

TEST(MatrixSizeConstructor, CanBeConstructed) {
    // Passes if constructor + destructor run without crashing.
    Matrix<int> matrix{2, 6};
    SUCCEED();
}

TEST(MatrixSizeConstructor, HasCorrectDimensions) {
    Matrix<int> m{3, 4};
    EXPECT_EQ(m.rows(), 3u);
    EXPECT_EQ(m.cols(), 4u);
    EXPECT_EQ(m.size(), 12u);
    EXPECT_FALSE(m.empty());
}

// Value constructor  (rows × cols, initial value)

TEST(MatrixValueConstructor, AllElementsEqualInitialValue) {
    Matrix<int> m{2, 3, 42};
    EXPECT_EQ(m.rows(), 2u);
    EXPECT_EQ(m.cols(), 3u);
    for (std::size_t r = 0; r < m.rows(); ++r)
        for (std::size_t c = 0; c < m.cols(); ++c)
            EXPECT_EQ(m(r, c), 42) << "at (" << r << ", " << c << ")";
}

// Initializer-list constructor

TEST(MatrixInitListConstructor, CorrectDimensionsAndValues) {
    Matrix<int> m{{1, 2, 3},
                  {4, 5, 6}};
    EXPECT_EQ(m.rows(), 2u);
    EXPECT_EQ(m.cols(), 3u);
    EXPECT_EQ(m(0, 0), 1);
    EXPECT_EQ(m(0, 1), 2);
    EXPECT_EQ(m(0, 2), 3);
    EXPECT_EQ(m(1, 0), 4);
    EXPECT_EQ(m(1, 1), 5);
    EXPECT_EQ(m(1, 2), 6);
}

// Destructor

TEST(MatrixDestructor, DestructorRunsWithoutCrash) {
    {
        Matrix<double> m{100, 100, 3.14};
        // m goes out of scope here; destructor must not crash.
    }
    SUCCEED();
}

TEST(MatrixDestructor, DefaultDestructorSuccessfully) {
    {
        Matrix<int> m;
        // data() == nullptr
        // delete[] nullptr must be safe.
    }
    SUCCEED();
}

// Copy constructor

TEST(MatrixCopyConstructor, CopiedMatrixHasSameDimensions) {
    Matrix<int> original{{1, 2}, {3, 4}};
    Matrix<int> copy{original};
    EXPECT_EQ(copy.rows(), original.rows());
    EXPECT_EQ(copy.cols(), original.cols());
}

TEST(MatrixCopyConstructor, CopiedMatrixHasSameValues) {
    Matrix<int> original{{1, 2}, {3, 4}};
    Matrix<int> copy{original};
    for (std::size_t r = 0; r < original.rows(); ++r)
        for (std::size_t c = 0; c < original.cols(); ++c)
            EXPECT_EQ(copy(r, c), original(r, c));
}

TEST(MatrixCopyConstructor, DeepCopy_ModifyingCopyDoesNotAffectOriginal) {
    Matrix<int> original{{1, 2}, {3, 4}};
    Matrix<int> copy{original};
    copy(0, 0) = 99;
    EXPECT_EQ(original(0, 0), 1) << "Original was mutated through the copy";
}

TEST(MatrixCopyConstructor, DeepCopy_ModifyingOriginalDoesNotAffectCopy) {
    Matrix<int> original{{1, 2}, {3, 4}};
    Matrix<int> copy{original};
    original(0, 0) = 99;
    EXPECT_EQ(copy(0, 0), 1) << "Copy was mutated through the original";
}

// Copy assignment operator

TEST(MatrixCopyAssignment, AssignedMatrixHasSameValues) {
    Matrix<int> original{{5, 6}, {7, 8}};
    Matrix<int> assigned{1, 1, 0};
    assigned = original;
    for (std::size_t r = 0; r < original.rows(); ++r)
        for (std::size_t c = 0; c < original.cols(); ++c)
            EXPECT_EQ(assigned(r, c), original(r, c));
}

TEST(MatrixCopyAssignment, DeepCopy_ModifyingAssignedDoesNotAffectOriginal) {
    Matrix<int> original{{5, 6}, {7, 8}};
    Matrix<int> assigned = original;
    assigned(0, 0) = 99;
    EXPECT_EQ(original(0, 0), 5);
}

TEST(MatrixCopyAssignment, SelfAssignmentIsSafe) {
    Matrix<int> m{{1, 2}, {3, 4}};
    // Silence compiler warning about self-assignment on purpose.
    Matrix<int>& ref = m;
    ref = m;
    EXPECT_EQ(m(0, 0), 1);
    EXPECT_EQ(m(1, 1), 4);
}

// Move constructor

TEST(MatrixMoveConstructor, MovedFromMatrixIsEmpty) {
    Matrix<int> original{{1, 2}, {3, 4}};
    Matrix<int> moved{std::move(original)};
    // The moved-from object must be in a valid (empty) state.
    EXPECT_EQ(original.rows(), 0u);
    EXPECT_EQ(original.cols(), 0u);
    EXPECT_EQ(original.data(), nullptr);
}

TEST(MatrixMoveConstructor, MoveTargetHasCorrectValues) {
    Matrix<int> original{{1, 2}, {3, 4}};
    Matrix<int> moved{std::move(original)};
    EXPECT_EQ(moved.rows(), 2u);
    EXPECT_EQ(moved.cols(), 2u);
    EXPECT_EQ(moved(0, 0), 1);
    EXPECT_EQ(moved(1, 1), 4);
}

// Move assignment operator

TEST(MatrixMoveAssignment, MovedFromMatrixIsEmpty) {
    Matrix<int> original{{9, 8}, {7, 6}};
    Matrix<int> target{1, 1, 0};
    target = std::move(original);
    EXPECT_EQ(original.rows(), 0u);
    EXPECT_EQ(original.cols(), 0u);
    EXPECT_EQ(original.data(), nullptr);
}

TEST(MatrixMoveAssignment, MoveTargetHasCorrectValues) {
    Matrix<int> original{{9, 8}, {7, 6}};
    Matrix<int> target{1, 1, 0};
    target = std::move(original);
    EXPECT_EQ(target.rows(), 2u);
    EXPECT_EQ(target.cols(), 2u);
    EXPECT_EQ(target(0, 0), 9);
    EXPECT_EQ(target(1, 1), 6);
}

TEST(MatrixMoveAssignment, SelfMoveAssignmentIsSafe) {
    Matrix<int> m{{1, 2}, {3, 4}};
    // Avoid the compiler warning by going through a pointer.
    Matrix<int>* p = &m;
    *p = std::move(m);
    // After self-move the object must still be in a valid state.
    // (Values may be unspecified, but it must not crash / double-free.)
    SUCCEED();
}

// Swap -- std::swap for now.

TEST(MatrixSwap, MemberSwapExchangesDimensions) {
    Matrix<int> a{2, 3, 1};
    Matrix<int> b{4, 5, 2};
    std::swap(a, b);
    EXPECT_EQ(a.rows(), 4u);
    EXPECT_EQ(a.cols(), 5u);
    EXPECT_EQ(b.rows(), 2u);
    EXPECT_EQ(b.cols(), 3u);
}

TEST(MatrixSwap, MemberSwapExchangesValues) {
    Matrix<int> a{{1, 2}, {3, 4}};
    Matrix<int> b{{9, 8}, {7, 6}};
    std::swap(a, b);
    EXPECT_EQ(a(0, 0), 9);
    EXPECT_EQ(b(0, 0), 1);
}

TEST(MatrixSwap, FreeSwapExchangesDimensions) {
    Matrix<int> a{2, 3, 1};
    Matrix<int> b{4, 5, 2};
    std::swap(a, b);
    EXPECT_EQ(a.rows(), 4u);
    EXPECT_EQ(a.cols(), 5u);
    EXPECT_EQ(b.rows(), 2u);
    EXPECT_EQ(b.cols(), 3u);
}