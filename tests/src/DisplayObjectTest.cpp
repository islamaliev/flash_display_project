#include "gmock/gmock-matchers.h"
#include "DisplayObject.h"

using namespace testing;

class DisplayObjectTest : public testing::Test {
public:
    using DisplayObject = flash::display::DisplayObject;
    using Rectangle = flash::core::Rectangle;

    ::testing::AssertionResult RectanglesEQ(const Rectangle& r1, const Rectangle& r2) {
        if (r1 != r2) {
            return ::testing::AssertionFailure() << "rect " << r1 << "!= " << r2;
        }
        return ::testing::AssertionSuccess();
    }

    DisplayObject displayObject;
};

TEST_F(DisplayObjectTest, SetWidth) {
    displayObject.setWidth(100);
    ASSERT_EQ(displayObject.width(), 100);
    displayObject.setWidth(200);
    ASSERT_EQ(displayObject.width(), 200);
}

TEST_F(DisplayObjectTest, SetHeight) {
    displayObject.setHeight(100);
    ASSERT_EQ(displayObject.height(), 100);
    displayObject.setHeight(200);
    ASSERT_EQ(displayObject.height(), 200);
}

TEST_F(DisplayObjectTest, SetX) {
    displayObject.setX(3);
    ASSERT_EQ(displayObject.x(), 3);
    displayObject.setX(7);
    ASSERT_EQ(displayObject.x(), 7);
}

TEST_F(DisplayObjectTest, SetY) {
    displayObject.setY(5);
    ASSERT_EQ(displayObject.y(), 5);
    displayObject.setY(9);
    ASSERT_EQ(displayObject.y(), 9);
}

TEST_F(DisplayObjectTest, SetPivotX) {
    displayObject.setPivotX(3);
    ASSERT_EQ(displayObject.pivotX(), 3);
    displayObject.setPivotX(7);
    ASSERT_EQ(displayObject.pivotX(), 7);
}

TEST_F(DisplayObjectTest, SetPivotY) {
    displayObject.setPivotY(5);
    ASSERT_EQ(displayObject.pivotY(), 5);
    displayObject.setPivotY(9);
    ASSERT_EQ(displayObject.pivotY(), 9);
}

TEST_F(DisplayObjectTest, SetRotation) {
    displayObject.setRotation(1);
    ASSERT_EQ(displayObject.rotation(), 1);
    displayObject.setRotation(2);
    ASSERT_EQ(displayObject.rotation(), 2);
}

TEST_F(DisplayObjectTest, SetScaleX) {
    displayObject.setScaleX(3);
    ASSERT_EQ(displayObject.scaleX(), 3);
    displayObject.setScaleX(7);
    ASSERT_EQ(displayObject.scaleX(), 7);
}

TEST_F(DisplayObjectTest, SetScaleY) {
    displayObject.setScaleY(5);
    ASSERT_EQ(displayObject.scaleY(), 5);
    displayObject.setScaleY(9);
    ASSERT_EQ(displayObject.scaleY(), 9);
}

TEST_F(DisplayObjectTest, DefaultConstructor) {
    DisplayObject obj;
    ASSERT_EQ(obj.x(), 0);
    ASSERT_EQ(obj.y(), 0);
    ASSERT_EQ(obj.width(), 1);
    ASSERT_EQ(obj.height(), 1);
    ASSERT_EQ(obj.scaleX(), 1);
    ASSERT_EQ(obj.scaleY(), 1);
    ASSERT_EQ(obj.pivotX(), 0);
    ASSERT_EQ(obj.pivotY(), 0);
    ASSERT_EQ(obj.rotation(), 0);
    ASSERT_EQ(obj.visible(), true);
}

TEST_F(DisplayObjectTest, SetVisible) {
    displayObject.setVisible(false);
    ASSERT_EQ(displayObject.visible(), false);
    displayObject.setVisible(true);
    ASSERT_EQ(displayObject.visible(), true);
}

TEST_F(DisplayObjectTest, GetBoundsInOwnSpace) {
    displayObject.setX(10);
    displayObject.setY(10);
    displayObject.setWidth(33);
    displayObject.setHeight(35);
    Rectangle r = displayObject.getBounds(&displayObject);
    ASSERT_TRUE(RectanglesEQ(r, {0, 0, 33, 35}));

}