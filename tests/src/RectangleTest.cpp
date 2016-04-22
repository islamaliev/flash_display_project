#include <gmock/gmock-matchers.h>
#include "gtest/gtest.h"
#include <Rectangle.h>


using namespace testing;
using namespace flash::core;

class RectangleTest : public Test {
public:
    void SetUp() override {

    }

    Rectangle rect;
};

TEST_F(RectangleTest, Constructor) {
    Rectangle r = {1, 2, 3, 4};
    ASSERT_EQ(r.x(), 1);
    ASSERT_EQ(r.y(), 2);
    ASSERT_EQ(r.width(), 3);
    ASSERT_EQ(r.height(), 4);
}

TEST_F(RectangleTest, DefaultConstructor) {
    Rectangle r;
    ASSERT_EQ(r.x(), 0);
    ASSERT_EQ(r.y(), 0);
    ASSERT_EQ(r.width(), 1);
    ASSERT_EQ(r.height(), 1);
}

TEST_F(RectangleTest, SetX) {
    rect.setX(3);
    ASSERT_EQ(rect.x(), 3);
    rect.setX(7);
    ASSERT_EQ(rect.x(), 7);
}

TEST_F(RectangleTest, SetY) {
    rect.setY(5);
    ASSERT_EQ(rect.y(), 5);
    rect.setY(9);
    ASSERT_EQ(rect.y(), 9);
}

TEST_F(RectangleTest, SetWidth) {
    rect.setWidth(5);
    ASSERT_EQ(rect.width(), 5);
    rect.setWidth(6);
    ASSERT_EQ(rect.width(), 6);
}

TEST_F(RectangleTest, SetHeight) {
    rect.setHeight(2);
    ASSERT_EQ(rect.height(), 2);
    rect.setHeight(4);
    ASSERT_EQ(rect.height(), 4);
}
