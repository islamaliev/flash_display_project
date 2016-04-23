#include "gmock/gmock-matchers.h"
#include "DisplayObject.h"

using namespace testing;
using namespace flash::display;

class DisplayObjectTest : public testing::Test {
protected:
    void SetUp() override {
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

TEST_F(DisplayObjectTest, setVisible) {
    displayObject.setVisible(false);
    ASSERT_EQ(displayObject.visible(), false);
    displayObject.setVisible(true);
    ASSERT_EQ(displayObject.visible(), true);
}