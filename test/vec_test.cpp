#include "../src/vec.h"

#include <gtest/gtest.h>

#include <sstream>

TEST(VectorTest, VectorConstructorTest1) {
    PANSFE::Vec<int> a;
    ASSERT_EQ(a.Size(), 0);
    ASSERT_EQ(a.Values(), nullptr);
}

TEST(VectorTest, VectorConstructorTest2) {
    PANSFE::Vec<int> a(2);
    ASSERT_EQ(a.Size(), 2);
    ASSERT_EQ(*(a.Values() + 0), 0);
    ASSERT_EQ(*(a.Values() + 1), 0);
}

TEST(VectorTest, VectorConstructorTest3) {
    PANSFE::Vec<int> a(2, 3);
    ASSERT_EQ(a.Size(), 2);
    ASSERT_EQ(*(a.Values() + 0), 3);
    ASSERT_EQ(*(a.Values() + 1), 3);
}

TEST(VectorTest, VectorConstructorTest4) {
    PANSFE::Vec<int> a = {1, 2};
    ASSERT_EQ(a.Size(), 2);
    ASSERT_EQ(*(a.Values() + 0), 1);
    ASSERT_EQ(*(a.Values() + 1), 2);
}

TEST(VectorTest, VectorConstructorTest5) {
    PANSFE::Vec<int> a = {1, 2}, b = a;
    ASSERT_EQ(a.Size(), b.Size());
    ASSERT_EQ(*(a.Values() + 0), *(b.Values() + 0));
    ASSERT_EQ(*(a.Values() + 1), *(b.Values() + 1));
    ASSERT_NE(a.Values(), b.Values());
}

TEST(VectorTest, VectorAccessorTest1) {
    PANSFE::Vec<int> a = {1, 2};
    ASSERT_EQ(a[0], 1);
    ASSERT_EQ(a(1), 2);
}

TEST(VectorTest, VectorAccessorTest2) {
    PANSFE::Vec<int> a(2);
    a(0) = 1;
    a[1] = 2;
    ASSERT_EQ(*(a.Values() + 0), 1);
    ASSERT_EQ(*(a.Values() + 1), 2);
}

TEST(VectorTest, VectorCompareTest1) {
    PANSFE::Vec<int> a = {1, 2}, b = {1, 2};
    ASSERT_TRUE(a == b);
}

TEST(VectorTest, VectorCompareTest2) {
    PANSFE::Vec<int> a = {1, 2}, b = {1, 3};
    ASSERT_TRUE(a != b);
}

TEST(VectorTest, VectorAssignmentTest1) {
    PANSFE::Vec<int> a = {1, 2}, b = {3, 4};
    a = b;
    ASSERT_EQ(a, b);
    ASSERT_NE(&a, &b);
    ASSERT_NE(a.Values(), b.Values());
}

TEST(VectorTest, VectorAssignmentTest2) {
    PANSFE::Vec<int> a = {4, 3}, b = {2, 1}, c = {6, 4};
    a += b;
    ASSERT_EQ(a, c);
}

TEST(VectorTest, VectorAssignmentTest3) {
    PANSFE::Vec<int> a = {3, 4}, b = {2, 1}, c = {1, 3};
    a -= b;
    ASSERT_EQ(a, c);
}

TEST(VectorTest, VectorAssignmentTest4) {
    PANSFE::Vec<int> a = {4, 2}, b = {8, 4};
    a *= 2;
    ASSERT_EQ(a, b);
}

TEST(VectorTest, VectorAssignmentTest5) {
    PANSFE::Vec<int> a = {4, 2}, b = {2, 1};
    a /= 2;
    ASSERT_EQ(a, b);
}

TEST(VectorTest, VectorAssignmentTest6) {
    PANSFE::Vec<int> a = {1, 2, 5}, b = {3, 4, 6}, c = {-8, 9, -2};
    a ^= b;
    ASSERT_EQ(a, c);
}

TEST(VectorTest, VectorOperatorTest1) {
    PANSFE::Vec<int> a = {5, 3}, b = {2, 1}, c = {7, 4};
    ASSERT_EQ(a + b, c);
}

TEST(VectorTest, VectorOperatorTest2) {
    PANSFE::Vec<int> a = {5, 3}, b = {2, 1}, c = {3, 2};
    ASSERT_EQ(a - b, c);
}

TEST(VectorTest, VectorOperatorTest3) {
    PANSFE::Vec<int> a = {5, 3}, b = {-5, -3};
    ASSERT_EQ(-a, b);
}

TEST(VectorTest, VectorOperatorTest4) {
    PANSFE::Vec<int> a = {3, 4}, b = {15, 20};
    ASSERT_EQ(a * 5, b);
}

TEST(VectorTest, VectorOperatorTest5) {
    PANSFE::Vec<int> a = {3, 4}, b = {15, 20};
    ASSERT_EQ(5 * a, b);
}

TEST(VectorTest, VectorOperatorTest6) {
    PANSFE::Vec<int> a = {5, 3}, b = {2, 1};
    ASSERT_EQ(a * b, 13);
}

TEST(VectorTest, VectorOperatorTest7) {
    PANSFE::Vec<int> a = {2, 4}, b = {1, 2};
    ASSERT_EQ(a / 2, b);
}

TEST(VectorTest, VectorOperatorTest8) {
    PANSFE::Vec<int> a = {1, 2, 5}, b = {3, 4, 6}, c = {-8, 9, -2};
    ASSERT_EQ(a ^ b, c);
}

TEST(VectorTest, VectorOperatorTest9) {
    PANSFE::Vec<int> a = {1, 2}, b = {3, 4}, c = {95, 130};
    ASSERT_EQ(5 * (a + b * 6), c);
}

TEST(VectorTest, VectorConversionTest1) {
    PANSFE::Vec<int> a = {3};
    ASSERT_EQ(int(a), 3);
}

TEST(VectorTest, VectorNormTest1) {
    PANSFE::Vec<int> a = {3, 4};
    ASSERT_EQ(a.Norm(), 5);
}

TEST(VectorTest, VectorNormalTest) {
    PANSFE::Vec<double> a = {1, 2}, b = {1 / sqrt(5), 2 / sqrt(5)};
    ASSERT_EQ(a.Normal(), b);
}

TEST(VectorTest, VectorVstackTest1) {
    PANSFE::Vec<int> a = {1, 2}, b = {3, 4, 5}, c = {1, 2, 3, 4, 5};
    ASSERT_EQ(a.Vstack(b), c);
}

TEST(VectorTest, VectorBlockTest1) {
    PANSFE::Vec<int> a = {1, 2, 3, 4, 5, 6}, b = {2, 3, 4};
    ASSERT_EQ(a.Block(1, 3), b);
}

TEST(VectorTest, VectorOStreamTest1) {
    PANSFE::Vec<int> a = {1, 2}, b = {3, 4};
    std::stringstream ss;
    ss << a << b;
    ASSERT_EQ(ss.str(), "1\n2\n3\n4\n");
}
