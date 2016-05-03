#include "gmock/gmock-matchers.h"
#include "DisplayObject.h"
#include <ostream>

using namespace testing;
using Mat4 = flash::math::Mat4;
using DisplayObject = flash::display::DisplayObject;
using Rectangle = flash::core::Rectangle;

std::string toString(const Mat4& m) {
    char buf[160];
    sprintf(buf, "[%.2f, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f]"
            , m.v1.x, m.v1.y, m.v1.z, m.v1.w, m.v2.x, m.v2.y, m.v2.z, m.v2.w
            , m.v3.x, m.v3.y, m.v3.z, m.v3.w, m.vt.x, m.vt.y, m.vt.z, m.vt.w);
    return std::string(buf);
}

std::string toString(const Rectangle& rect) {
    char buf[100];
    sprintf(buf, "(x = %f, y = %f, width = %f, height = %f)", rect.x, rect.y, rect.width, rect.height);
    return std::string(buf);
}

class DisplayObjectTest : public testing::Test {
public:

    ::testing::AssertionResult RectanglesEQ(const Rectangle& actual, const Rectangle& expected) {
        if (actual != expected) {
            return ::testing::AssertionFailure() << "rect " << toString(actual) << "!= " << toString(expected);
        }
        return ::testing::AssertionSuccess();
    }

    ::testing::AssertionResult MatrixEQ(const Mat4& actual, const Mat4& expected) {
        if (!actual.isEqual(expected)) {
            return ::testing::AssertionFailure() << "\nactual matrix:   " << toString(actual)
                   << "\nexpected matrix: " << toString(expected);
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

TEST_F(DisplayObjectTest, getTransfomrForPositionAndSize) {
    int x = 10;
    int y = 20;
    int w = 40;
    int h = 60;
    displayObject.setX(x);
    displayObject.setY(y);
    displayObject.setWidth(w);
    displayObject.setHeight(h);
    
    Mat4 m;
    m.translate(x + w / 2, y + h / 2, 0);
    m.scale(w, h, 0);
    ASSERT_TRUE(MatrixEQ(displayObject.getTransform(), m));
}