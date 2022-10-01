#include "../src/vec.h"

#include <gtest/gtest.h>

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

TEST(VectorTest, VectorOperatorTest1) {
    PANSFE::Vec<int> a = {5, 3}, b = {2, 1}, c = a + b;
    ASSERT_EQ(*(c.Values() + 0), 7);
    ASSERT_EQ(*(c.Values() + 1), 4);
}

TEST(VectorTest, VectorOperatorTest2) {
    PANSFE::Vec<int> a = {5, 3}, b = {2, 1}, c = a - b;
    ASSERT_EQ(*(c.Values() + 0), 3);
    ASSERT_EQ(*(c.Values() + 1), 2);
}

TEST(VectorTest, VectorOperatorTest3) {
    PANSFE::Vec<int> a = {5, 3}, b = -a;
    ASSERT_EQ(*(b.Values() + 0), -5);
    ASSERT_EQ(*(b.Values() + 1), -3);
}

TEST(VectorTest, VectorOperatorTest4) {
    PANSFE::Vec<int> a = {3, 4}, b = a * 5;
    ASSERT_EQ(*(b.Values() + 0), 15);
    ASSERT_EQ(*(b.Values() + 1), 20);
}

TEST(VectorTest, VectorOperatorTest5) {
    PANSFE::Vec<int> a = {3, 4}, b = 5 * a;
    ASSERT_EQ(*(b.Values() + 0), 15);
    ASSERT_EQ(*(b.Values() + 1), 20);
}

TEST(VectorTest, VectorOperatorTest6) {
    PANSFE::Vec<int> a = {5, 3}, b = {2, 1};
    ASSERT_EQ(a * b, 13);
}

TEST(VectorTest, VectorOperatorTest7) {
    PANSFE::Vec<int> a = {2, 4}, b = a / 2;
    ASSERT_EQ(*(b.Values() + 0), 1);
    ASSERT_EQ(*(b.Values() + 1), 2);
}

TEST(VectorTest, VectorOperatorTest8) {
    PANSFE::Vec<int> a = {1, 2, 5}, b = {3, 4, 6}, c = a ^ b;
    ASSERT_EQ(*(c.Values() + 0), -8);
    ASSERT_EQ(*(c.Values() + 1), 9);
    ASSERT_EQ(*(c.Values() + 2), -2);
}

TEST(VectorTest, VectorOperatorTest9) {
    PANSFE::Vec<int> a = {1, 2}, b = {3, 4}, c = 5 * (a + b * 6);
    ASSERT_EQ(*(c.Values() + 0), 95);
    ASSERT_EQ(*(c.Values() + 1), 130);
}

TEST(VectorTest, VectorAssignmentTest1) {
    PANSFE::Vec<int> a = {1, 2}, b = {3, 4};
    a = b;
    ASSERT_EQ(a.Size(), b.Size());
    ASSERT_EQ(*(a.Values() + 0), *(b.Values() + 0));
    ASSERT_EQ(*(a.Values() + 1), *(b.Values() + 1));
    ASSERT_NE(a.Values(), b.Values());
}

TEST(VectorTest, VectorAssignmentTest2) {
    PANSFE::Vec<int> a = {4, 3}, b = {2, 1};
    a += b;
    ASSERT_EQ(*(a.Values() + 0), 6);
    ASSERT_EQ(*(a.Values() + 1), 4);
}

TEST(VectorTest, VectorAssignmentTest3) {
    PANSFE::Vec<int> a = {3, 4}, b = {2, 1};
    a -= b;
    ASSERT_EQ(*(a.Values() + 0), 1);
    ASSERT_EQ(*(a.Values() + 1), 3);
}

TEST(VectorTest, VectorAssignmentTest4) {
    PANSFE::Vec<int> a = {4, 2};
    a *= 2;
    ASSERT_EQ(*(a.Values() + 0), 8);
    ASSERT_EQ(*(a.Values() + 1), 4);
}

TEST(VectorTest, VectorAssignmentTest5) {
    PANSFE::Vec<int> a = {4, 2};
    a /= 2;
    ASSERT_EQ(*(a.Values() + 0), 2);
    ASSERT_EQ(*(a.Values() + 1), 1);
}

TEST(VectorTest, VectorAssignmentTest6) {
    PANSFE::Vec<int> a = {1, 2, 5}, b = {3, 4, 6};
    a ^= b;
    ASSERT_EQ(*(a.Values() + 0), -8);
    ASSERT_EQ(*(a.Values() + 1), 9);
    ASSERT_EQ(*(a.Values() + 2), -2);
}
