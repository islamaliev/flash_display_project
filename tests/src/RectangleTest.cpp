#include "gmock/gmock-matchers.h"
#include "Rectangle.h"


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
    ASSERT_EQ(r.x, 1);
    ASSERT_EQ(r.y, 2);
    ASSERT_EQ(r.width, 3);
    ASSERT_EQ(r.height, 4);
}

TEST_F(RectangleTest, DefaultConstructor) {
    Rectangle r;
    ASSERT_EQ(r.x, 0);
    ASSERT_EQ(r.y, 0);
    ASSERT_EQ(r.width, 1);
    ASSERT_EQ(r.height, 1);
}

TEST_F(RectangleTest, Equals) {
    rect = {2, 2, 4, 4};
    Rectangle otherRect = rect;
    ASSERT_TRUE(rect.equals(otherRect));
    ASSERT_TRUE(rect == otherRect);
    ASSERT_FALSE(rect != otherRect);
    otherRect.x += 1;
    ASSERT_FALSE(rect.equals(otherRect));
    ASSERT_FALSE(rect == otherRect);
    ASSERT_TRUE(rect != otherRect);
    otherRect = rect;
    otherRect.y += 1;
    ASSERT_FALSE(rect.equals(otherRect));
    ASSERT_FALSE(rect == otherRect);
    ASSERT_TRUE(rect != otherRect);
    otherRect = rect;
    otherRect.width += 1;
    ASSERT_FALSE(rect.equals(otherRect));
    ASSERT_FALSE(rect == otherRect);
    ASSERT_TRUE(rect != otherRect);
    otherRect = rect;
    otherRect.height += 1;
    ASSERT_FALSE(rect.equals(otherRect));
    ASSERT_FALSE(rect == otherRect);
    ASSERT_TRUE(rect != otherRect);
}