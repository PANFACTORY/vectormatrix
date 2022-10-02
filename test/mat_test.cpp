#include "../src/mat.h"

#include <gtest/gtest.h>

TEST(MatrixTest, MatrixConstructorTest1) {
    PANSFE::Mat<int> a;
    ASSERT_EQ(a.Row(), 0);
    ASSERT_EQ(a.Col(), 0);
    ASSERT_EQ(a.Values(), nullptr);
}

TEST(MatrixTest, MatrixConstructorTest2) {
    PANSFE::Mat<int> a(2, 3);
    ASSERT_EQ(a.Row(), 2);
    ASSERT_EQ(a.Col(), 3);
    ASSERT_EQ(*(a.Values() + 0), 0);
    ASSERT_EQ(*(a.Values() + 1), 0);
    ASSERT_EQ(*(a.Values() + 2), 0);
    ASSERT_EQ(*(a.Values() + 3), 0);
    ASSERT_EQ(*(a.Values() + 4), 0);
    ASSERT_EQ(*(a.Values() + 5), 0);
}

TEST(MatrixTest, MatrixConstructorTest3) {
    PANSFE::Mat<int> a(2, 3, 4);
    ASSERT_EQ(a.Row(), 2);
    ASSERT_EQ(a.Col(), 3);
    ASSERT_EQ(*(a.Values() + 0), 4);
    ASSERT_EQ(*(a.Values() + 1), 4);
    ASSERT_EQ(*(a.Values() + 2), 4);
    ASSERT_EQ(*(a.Values() + 3), 4);
    ASSERT_EQ(*(a.Values() + 4), 4);
    ASSERT_EQ(*(a.Values() + 5), 4);
}

TEST(MatrixTest, MatrixConstructorTest4) {
    PANSFE::Mat<int> a = {{1, 2, 3}, {4, 5, 6}};
    ASSERT_EQ(a.Row(), 2);
    ASSERT_EQ(a.Col(), 3);
    ASSERT_EQ(*(a.Values() + 0), 1);
    ASSERT_EQ(*(a.Values() + 1), 2);
    ASSERT_EQ(*(a.Values() + 2), 3);
    ASSERT_EQ(*(a.Values() + 3), 4);
    ASSERT_EQ(*(a.Values() + 4), 5);
    ASSERT_EQ(*(a.Values() + 5), 6);
}

TEST(MatrixTest, MatrixConstructorTest5) {
    PANSFE::Mat<int> a = {{1, 2, 3}, {4, 5, 6}}, b = a;
    ASSERT_EQ(a.Row(), b.Row());
    ASSERT_EQ(a.Col(), b.Col());
    ASSERT_EQ(*(a.Values() + 0), *(b.Values() + 0));
    ASSERT_EQ(*(a.Values() + 1), *(b.Values() + 1));
    ASSERT_EQ(*(a.Values() + 2), *(b.Values() + 2));
    ASSERT_EQ(*(a.Values() + 3), *(b.Values() + 3));
    ASSERT_EQ(*(a.Values() + 4), *(b.Values() + 4));
    ASSERT_EQ(*(a.Values() + 5), *(b.Values() + 5));
    ASSERT_NE(a.Values(), b.Values());
}

TEST(MatrixTest, MatrixAccessorTest1) {
    PANSFE::Mat<int> a = {{1, 2, 3}, {4, 5, 6}};
    ASSERT_EQ(a[1][2], 6);
    ASSERT_EQ(a(0, 1), 2);
}

TEST(MatrixTest, MatrixAccessorTest2) {
    PANSFE::Mat<int> a = {{1, 2, 3}, {4, 5, 6}};
    a(1, 2) = 2;
    a[0][1] = 3;
    ASSERT_EQ(*(a.Values() + 5), 2);
    ASSERT_EQ(*(a.Values() + 1), 3);
}

TEST(MatrixTest, MatrixCompareTest1) {
    PANSFE::Mat<int> a = {{1, 2, 3}, {4, 5, 6}}, b = {{1, 2, 3}, {4, 5, 6}};
    ASSERT_TRUE(a == b);
}

TEST(MatrixTest, MatrixCompareTest2) {
    PANSFE::Mat<int> a = {{1, 2, 3}, {4, 5, 6}}, b = {{4, 5, 6}, {1, 2, 3}};
    ASSERT_TRUE(a != b);
}

TEST(MatrixTest, MatrixAssignmentTest1) {
    PANSFE::Mat<int> a = {{1, 2, 3}, {4, 5, 6}}, b = {{4, 5, 6}, {1, 2, 3}};
    a = b;
    ASSERT_EQ(a, b);
    ASSERT_NE(&a, &b);
    ASSERT_NE(a.Values(), b.Values());
}

TEST(MatrixTest, MatrixAssignmentTest2) {
    PANSFE::Mat<int> a = {{1, 2}, {3, 4}}, b = {{5, 6}, {7, 8}},
                     c = {{6, 8}, {10, 12}};
    a += b;
    ASSERT_EQ(a, c);
}

TEST(MatrixTest, MatrixAssignmentTest3) {
    PANSFE::Mat<int> a = {{6, 8}, {10, 12}}, b = {{5, 6}, {7, 8}},
                     c = {{1, 2}, {3, 4}};
    a -= b;
    ASSERT_EQ(a, c);
}

TEST(MatrixTest, MatrixAssignmentTest4) {
    PANSFE::Mat<int> a = {{1, 2}, {3, 4}}, b = {{2, 4}, {6, 8}};
    a *= 2;
    ASSERT_EQ(a, b);
}

TEST(MatrixTest, MatrixAssignmentTest5) {
    PANSFE::Mat<int> a = {{1, 2}, {3, 4}}, b = {{5, 6}, {7, 8}},
                     c = {{19, 22}, {43, 50}};
    a *= b;
    ASSERT_EQ(a, c);
}

TEST(MatrixTest, MatrixAssignmentTest6) {
    PANSFE::Mat<int> a = {{2, 4}, {6, 8}}, b = {{1, 2}, {3, 4}};
    a /= 2;
    ASSERT_EQ(a, b);
}

TEST(MatrixTest, MatrixOperatorTest1) {
    PANSFE::Mat<int> a = {{1, 2}, {3, 4}}, b = {{5, 6}, {7, 8}},
                     c = {{6, 8}, {10, 12}};
    ASSERT_EQ(a + b, c);
}

TEST(MatrixTest, MatrixOperatorTest2) {
    PANSFE::Mat<int> a = {{6, 8}, {10, 12}}, b = {{5, 6}, {7, 8}},
                     c = {{1, 2}, {3, 4}};
    ASSERT_EQ(a - b, c);
}

TEST(MatrixTest, MatrixOperatorTest3) {
    PANSFE::Mat<int> a = {{1, 2}, {3, 4}}, b = {{-1, -2}, {-3, -4}};
    ASSERT_EQ(-a, b);
}

TEST(MatrixTest, MatrixOperatorTest4) {
    PANSFE::Mat<int> a = {{1, 2}, {3, 4}}, b = {{5, 10}, {15, 20}};
    ASSERT_EQ(a * 5, b);
}

TEST(MatrixTest, MatrixOperatorTest5) {
    PANSFE::Mat<int> a = {{1, 2}, {3, 4}}, b = {{5, 10}, {15, 20}};
    ASSERT_EQ(5 * a, b);
}

TEST(MatrixTest, MatrixOperatorTest6) {
    PANSFE::Mat<int> a = {{1, 2}, {3, 4}}, b = {{5, 6}, {7, 8}},
                     c = {{19, 22}, {43, 50}};
    ASSERT_EQ(a * b, c);
}

TEST(MatrixTest, MatrixOperatorTest7) {
    PANSFE::Mat<int> a = {{2, 4}, {6, 8}}, b = {{1, 2}, {3, 4}};
    ASSERT_EQ(a / 2, b);
}

TEST(MatrixTest, MatrixConversionTest1) {
    PANSFE::Mat<int> a = {{3}};
    ASSERT_EQ(int(a), 3);
}

TEST(MatrixTest, MatrixTransposeTest1) {
    PANSFE::Mat<int> a = {{1, 2, 3}, {4, 5, 6}}, b = {{1, 4}, {2, 5}, {3, 6}};
    ASSERT_EQ(a.Transpose(), b);
}

TEST(MatrixTest, MatrixDeterminantTest1) {
    PANSFE::Mat<int> a = {{2}};
    ASSERT_EQ(a.Determinant(), 2);
}

TEST(MatrixTest, MatrixDeterminantTest2) {
    PANSFE::Mat<int> a = {{1, 2}, {3, 4}};
    ASSERT_EQ(a.Determinant(), -2);
}

TEST(MatrixTest, MatrixDeterminantTest3) {
    PANSFE::Mat<int> a = {{1, 2, 3}, {6, 5, 4}, {9, 7, 8}};
    ASSERT_EQ(a.Determinant(), -21);
}

TEST(MatrixTest, MatrixDeterminantTest4) {
    PANSFE::Mat<int> a = {
        {1, 2, 3, 4}, {5, 7, 11, 8}, {9, 10, 6, 12}, {13, 14, 15, 16}};
    ASSERT_EQ(a.Determinant(), 180);
}

TEST(MatrixTest, MatrixInverseTest1) {
    PANSFE::Mat<double> a = {{2}};
    ASSERT_EQ(double(a.Inverse()), 0.5);
}

TEST(MatrixTest, MatrixInverseTest2) {
    PANSFE::Mat<double> a = {{1, 2}, {3, 4}}, b = {{-2, 1}, {1.5, -0.5}};
    ASSERT_EQ(a.Inverse(), b);
}

TEST(MatrixTest, MatrixInverseTest3) {
    PANSFE::Mat<double> a = {{1, 1, -1}, {-2, 0, 1}, {0, 2, 1}},
                        b = {{-0.5, -0.75, 0.25},
                             {0.5, 0.25, 0.25},
                             {-1, -0.5, 0.5}};
    ASSERT_EQ(a.Inverse(), b);
}

TEST(MatrixTest, MatrixCofactorTest1) {
    PANSFE::Mat<int> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}},
                     b = {{1, 2}, {7, 8}};
    ASSERT_EQ(a.Cofactor(1, 2), b);
}

TEST(MatrixTest, MatrixVstackTest1) {
    PANSFE::Mat<int> a = {{1, 2, 3}, {4, 5, 6}},
                     b = {{7, 8, 9}, {10, 11, 12}, {13, 14, 15}},
                     c = {{1, 2, 3},
                          {4, 5, 6},
                          {7, 8, 9},
                          {10, 11, 12},
                          {13, 14, 15}};
    ASSERT_EQ(a.Vstack(b), c);
}

TEST(MatrixTest, MatrixHstackTest1) {
    PANSFE::Mat<int> a = {{1, 2}, {3, 4}, {5, 6}},
                     b = {{7, 8, 9}, {10, 11, 12}, {13, 14, 15}},
                     c = {{1, 2, 7, 8, 9},
                          {3, 4, 10, 11, 12},
                          {5, 6, 13, 14, 15}};
    ASSERT_EQ(a.Hstack(b), c);
}

TEST(MatrixTest, MatrixBlockTest1) {
    PANSFE::Mat<int> a = {{1, 2, 3, 4, 5},
                          {6, 7, 8, 9, 10},
                          {11, 12, 13, 14, 15},
                          {16, 17, 18, 19, 20}},
                     b = {{7, 8, 9}, {12, 13, 14}};
    ASSERT_EQ(a.Block(1, 1, 2, 3), b);
}

TEST(MatrixTest, MatrixIdentityTest1) {
    PANSFE::Mat<int> a = {{1, 0}, {0, 1}};
    ASSERT_EQ(PANSFE::Mat<int>::Identity(2), a);
}

TEST(MatrixTest, MatrixOStreamTest1) {
    PANSFE::Mat<int> a = {{1, 2, 3}, {4, 5, 6}}, b = {{7, 8}, {9, 10}};
    std::stringstream ss;
    ss << a << b;
    ASSERT_EQ(ss.str(), "1\t2\t3\t\n4\t5\t6\t\n7\t8\t\n9\t10\t\n");
}
