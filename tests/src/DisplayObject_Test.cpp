#include "gmock/gmock-matchers.h"
#include "DisplayObject.h"
#include "DisplayObjectContainer.h"
#include "matrix_asserts.h"

using namespace testing;
using Mat4 = flash::math::Mat4;
using DisplayObject = flash::display::DisplayObject;
using DisplayObjectContainer = flash::display::DisplayObjectContainer;
using Rectangle = flash::core::Rectangle;

std::string toString(const Rectangle& rect) {
    char buf[100];
    sprintf(buf, "(x = %f, y = %f, width = %f, height = %f)", rect.x, rect.y, rect.width, rect.height);
    return std::string(buf);
}

class DisplayObject_Test : public testing::Test {
public:
    ::testing::AssertionResult RectanglesEQ(const Rectangle& actual, const Rectangle& expected) {
        if (actual != expected) {
            return ::testing::AssertionFailure() << "rect " << toString(actual) << "!= " << toString(expected);
        }
        return ::testing::AssertionSuccess();
    }

    DisplayObject displayObject;
};

TEST_F(DisplayObject_Test, SetWidth) {
    displayObject.setWidth(100);
    ASSERT_THAT(displayObject.width(), Eq(100));
    displayObject.setWidth(200);
    ASSERT_THAT(displayObject.width(), Eq(200));
}

TEST_F(DisplayObject_Test, SetHeight) {
    displayObject.setHeight(100);
    ASSERT_THAT(displayObject.height(), Eq(100));
    displayObject.setHeight(200);
    ASSERT_THAT(displayObject.height(), Eq(200));
}

TEST_F(DisplayObject_Test, SetX) {
    displayObject.setX(3);
    ASSERT_THAT(displayObject.x(), Eq(3));
    displayObject.setX(7);
    ASSERT_THAT(displayObject.x(), Eq(7));
}

TEST_F(DisplayObject_Test, SetY) {
    displayObject.setY(5);
    ASSERT_THAT(displayObject.y(), Eq(5));
    displayObject.setY(9);
    ASSERT_THAT(displayObject.y(), Eq(9));
}

TEST_F(DisplayObject_Test, SetPivotX) {
    displayObject.setPivotX(3);
    ASSERT_THAT(displayObject.pivotX(), Eq(3));
    displayObject.setPivotX(7);
    ASSERT_THAT(displayObject.pivotX(), Eq(7));
}

TEST_F(DisplayObject_Test, SetPivotY) {
    displayObject.setPivotY(5);
    ASSERT_THAT(displayObject.pivotY(), Eq(5));
    displayObject.setPivotY(9);
    ASSERT_THAT(displayObject.pivotY(), Eq(9));
}

TEST_F(DisplayObject_Test, SetRotation) {
    displayObject.setRotation(1);
    ASSERT_THAT(displayObject.rotation(), Eq(1));
    displayObject.setRotation(2);
    ASSERT_THAT(displayObject.rotation(), Eq(2));
}

TEST_F(DisplayObject_Test, SetScaleX) {
    displayObject.setScaleX(3);
    ASSERT_THAT(displayObject.scaleX(), Eq(3));
    displayObject.setScaleX(7);
    ASSERT_THAT(displayObject.scaleX(), Eq(7));
}

TEST_F(DisplayObject_Test, SetScaleY) {
    displayObject.setScaleY(5);
    ASSERT_THAT(displayObject.scaleY(), Eq(5));
    displayObject.setScaleY(9);
    ASSERT_THAT(displayObject.scaleY(), Eq(9));
}

TEST_F(DisplayObject_Test, DefaultConstructor) {
    DisplayObject obj;
    ASSERT_THAT(obj.x(), Eq(0));
    ASSERT_THAT(obj.y(), Eq(0));
    ASSERT_THAT(obj.width(), Eq(40));
    ASSERT_THAT(obj.height(), Eq(40));
    ASSERT_THAT(obj.scaleX(), Eq(1));
    ASSERT_THAT(obj.scaleY(), Eq(1));
    ASSERT_THAT(obj.pivotX(), Eq(0));
    ASSERT_THAT(obj.pivotY(), Eq(0));
    ASSERT_THAT(obj.rotation(), Eq(0));
    ASSERT_THAT(obj.depth(), Eq(-1));
    ASSERT_THAT(obj.orderIndex(), Eq(-1));
    ASSERT_THAT(obj.treeSize(), Eq(1));
    ASSERT_THAT(obj.visible(), Eq(true));
}

TEST_F(DisplayObject_Test, NewObjectHasNoParent) {
    ASSERT_FALSE(displayObject.getParent() != nullptr);
}

TEST_F(DisplayObject_Test, GetBoundsInOwnSpace) {
    displayObject.setX(10);
    displayObject.setY(10);
    displayObject.setWidth(33);
    displayObject.setHeight(35);
    Rectangle r = displayObject.getBounds(&displayObject);
    ASSERT_TRUE(RectanglesEQ(r, {0, 0, 33, 35}));
}
