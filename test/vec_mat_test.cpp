#include <gtest/gtest.h>

#include "../src/mat.h"
#include "../src/vec.h"

TEST(VecMatTest, VecMatConversionTest1) {
    PANSFE::Mat<int> A = {{1}, {2}, {3}};
    PANSFE::Vec<int> b = PANSFE::Vec<int>(A), c = {1, 2, 3};
    ASSERT_EQ(b, c);
}

TEST(VecMatTest, VecMatConversionTest2) {
    PANSFE::Vec<int> a = {1, 2, 3};
    PANSFE::Mat<int> B = PANSFE::Mat<int>(a), C = {{1}, {2}, {3}};
    ASSERT_EQ(B, C);
}

TEST(VecMatTest, VecMatHstackTest1) {
    PANSFE::Vec<int> a = {1, 2}, b = {3, 4};
    PANSFE::Mat<int> C = {{1, 3}, {2, 4}};
    ASSERT_EQ(a.Hstack(b), C);
}

TEST(VecMatTest, VecMatHstackTest2) {
    PANSFE::Vec<int> a = {1, 2};
    PANSFE::Mat<int> B = {{3, 4, 5}, {6, 7, 8}},
                     C = {{1, 3, 4, 5}, {2, 6, 7, 8}};
    ASSERT_EQ(a.Hstack(B), C);
}

TEST(VecMatTest, VecMatHstackTest3) {
    PANSFE::Vec<int> a = {1, 2};
    PANSFE::Mat<int> B = {{3, 4, 5}, {6, 7, 8}},
                     C = {{3, 4, 5, 1}, {6, 7, 8, 2}};
    ASSERT_EQ(B.Hstack(a), C);
}

TEST(VecMatTest, VecMatVstackTest1) {
    PANSFE::Mat<int> A = {{1}, {2}};
    PANSFE::Vec<int> b = {3, 4, 5}, c = {1, 2, 3, 4, 5};
    ASSERT_EQ(A.Vstack(b), c);
}

TEST(VecMatTest, VecMatVstackTest2) {
    PANSFE::Mat<int> A = {{1}, {2}};
    PANSFE::Vec<int> b = {3, 4, 5}, c = {3, 4, 5, 1, 2};
    ASSERT_EQ(b.Vstack(A), c);
}

TEST(VecMatTest, VecMatTransposeTest1) {
    PANSFE::Vec<int> a = {1, 2, 3};
    PANSFE::Mat<int> B = {{1, 2, 3}};
    ASSERT_EQ(a.Transpose(), B);
}

TEST(VecMatTest, VecMatDiagonalTest1) {
    PANSFE::Vec<int> a = {1, 2, 3};
    PANSFE::Mat<int> B = {{1, 0, 0}, {0, 2, 0}, {0, 0, 3}};
    ASSERT_EQ(a.Diagonal(), B);
}

TEST(VecMatTest, VecMatOperatorTest1) {
    PANSFE::Mat<int> A = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    PANSFE::Vec<int> b = {1, 2, 3}, c = {14, 32, 50};
    ASSERT_EQ(A * b, c);
}

TEST(VecMatTest, VecMatOperatorTest2) {
    PANSFE::Vec<int> a = {1, 2, 3};
    PANSFE::Mat<int> B = {{4, 5, 6}},
                     C = {{4, 5, 6}, {8, 10, 12}, {12, 15, 18}};
    ASSERT_EQ(a * B, C);
}

TEST(VecMatTest, VecMatOperatorTest3) {
    PANSFE::Vec<int> a = {1, 2, 3}, b = {4, 5, 6};
    ASSERT_EQ(int(a.Transpose() * b), 32);
}
