#include "gmock/gmock-matchers.h"
#include "Shape.h"
#include "DisplayObjectContainer.h"
#include "matrix_asserts.h"

using namespace testing;
using Mat4 = flash::math::Mat4;
using Shape = flash::display::Shape;
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

    Shape obj;
};

TEST_F(DisplayObject_Test, SetWidth) {
    obj.setWidth(100);
    ASSERT_THAT(obj.width(), Eq(100));
    obj.setWidth(200);
    ASSERT_THAT(obj.width(), Eq(200));
}

TEST_F(DisplayObject_Test, SetHeight) {
    obj.setHeight(100);
    ASSERT_THAT(obj.height(), Eq(100));
    obj.setHeight(200);
    ASSERT_THAT(obj.height(), Eq(200));
}

TEST_F(DisplayObject_Test, SetX) {
    obj.setX(3);
    ASSERT_THAT(obj.x(), Eq(3));
    obj.setX(7);
    ASSERT_THAT(obj.x(), Eq(7));
}

TEST_F(DisplayObject_Test, SetY) {
    obj.setY(5);
    ASSERT_THAT(obj.y(), Eq(5));
    obj.setY(9);
    ASSERT_THAT(obj.y(), Eq(9));
}

TEST_F(DisplayObject_Test, SetPivotX) {
    obj.setPivotX(3);
    ASSERT_THAT(obj.pivotX(), Eq(3));
    obj.setPivotX(7);
    ASSERT_THAT(obj.pivotX(), Eq(7));
}

TEST_F(DisplayObject_Test, SetPivotY) {
    obj.setPivotY(5);
    ASSERT_THAT(obj.pivotY(), Eq(5));
    obj.setPivotY(9);
    ASSERT_THAT(obj.pivotY(), Eq(9));
}

TEST_F(DisplayObject_Test, SetRotation) {
    obj.setRotation(1);
    ASSERT_THAT(obj.rotation(), Eq(1));
    obj.setRotation(2);
    ASSERT_THAT(obj.rotation(), Eq(2));
}

TEST_F(DisplayObject_Test, SetScaleX) {
    obj.setScaleX(3);
    ASSERT_THAT(obj.scaleX(), Eq(3));
    obj.setScaleX(7);
    ASSERT_THAT(obj.scaleX(), Eq(7));
}

TEST_F(DisplayObject_Test, SetScaleY) {
    obj.setScaleY(5);
    ASSERT_THAT(obj.scaleY(), Eq(5));
    obj.setScaleY(9);
    ASSERT_THAT(obj.scaleY(), Eq(9));
}

TEST_F(DisplayObject_Test, DefaultConstructor) {
    Shape localObj;
    ASSERT_THAT(localObj.x(), Eq(0));
    ASSERT_THAT(localObj.y(), Eq(0));
    ASSERT_THAT(localObj.width(), Eq(40));
    ASSERT_THAT(localObj.height(), Eq(40));
    ASSERT_THAT(localObj.scaleX(), Eq(1));
    ASSERT_THAT(localObj.scaleY(), Eq(1));
    ASSERT_THAT(localObj.pivotX(), Eq(0));
    ASSERT_THAT(localObj.pivotY(), Eq(0));
    ASSERT_THAT(localObj.rotation(), Eq(0));
    ASSERT_THAT(localObj.depth(), Eq(-1));
    ASSERT_THAT(localObj.orderIndex(), Eq(-1));
    ASSERT_THAT(localObj.treeSize(), Eq(1));
    ASSERT_THAT(localObj.visible(), Eq(true));
}

TEST_F(DisplayObject_Test, NewObjectHasNoParent) {
    ASSERT_FALSE(obj.getParent() != nullptr);
}

TEST_F(DisplayObject_Test, GetBoundsInOwnSpace) {
    obj.setX(10);
    obj.setY(10);
    obj.setWidth(33);
    obj.setHeight(35);
    Rectangle r = obj.getBounds(&obj);
    ASSERT_TRUE(RectanglesEQ(r, {0, 0, 33, 35}));
}
