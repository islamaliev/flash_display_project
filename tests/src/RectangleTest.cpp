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

TEST_F(RectangleTest, SetX) {
    rect.setX(3);
    ASSERT_EQ(rect.x(), 3);
    rect.setY(5);
    ASSERT_EQ(rect.y(), 5);
}

TEST_F(RectangleTest, SetY) {
    rect.setY(5);
    ASSERT_EQ(rect.y(), 5);
}

TEST_F(RectangleTest, SetWidth) {
    rect.setWidth(5);
    ASSERT_EQ(rect.width(), 5);
}

TEST_F(RectangleTest, SetHeight) {
    rect.setHeight(5);
    ASSERT_EQ(rect.height(), 5);
}