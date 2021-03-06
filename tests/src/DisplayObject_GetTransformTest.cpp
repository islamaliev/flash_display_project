#include "Shape.h"
#include "matrix_asserts.h"
#include "StageBasedTest.h"

using namespace flash::display;
using Mat4 = flash::math::Mat4;

class DisplayObject_GetTransformTest : public StageBasedTest {
public:
    Mat4 getTransform(float x, float y, float scaleX, float scaleY) {
        Mat4 m;
        m.translate(x, y, 0);
        m.scale(scaleX, scaleY, 1);
        return m;
    }

    void makeHierarchy() {
        stage().addChild(&grandParent);
        grandParent.addChild(&parent);
        parent.addChild(&obj);
    }

    Shape obj;
    DisplayObjectContainer parent;
    DisplayObjectContainer grandParent;
};

TEST_F(DisplayObject_GetTransformTest, ObjectReturnsIdentity) {
    ASSERT_THAT(obj.treeSize(), Eq(1));
    ASSERT_THAT(parent.treeSize(), Eq(1));
    ASSERT_THAT(stage().treeSize(), Eq(1));
}

TEST_F(DisplayObject_GetTransformTest, ForPositionAndScale) {
    int x = 10;
    int y = 20;
    int w = 40;
    int h = 60;
    obj.setX(x);
    obj.setY(y);
    obj.setWidth(w);
    obj.setHeight(h);

    ASSERT_TRUE(MatrixEQ(obj.getTransform(), getTransform(x, y, w, h)));
}

TEST_F(DisplayObject_GetTransformTest, ReturnsIdentity_ifNoParent) {
    DisplayObjectContainer notParent;
    obj.setWidth(2);
    obj.setY(10);
    ASSERT_TRUE(MatrixEQ(obj.getTransform(&notParent), Mat4::IDENTITY));
}

TEST_F(DisplayObject_GetTransformTest, ReturnsInParentsSpace_ifParentGiven) {
    makeHierarchy();
    int x = 10;
    int y = 20;
    int w = 40;
    int h = 60;
    obj.setX(x);
    obj.setY(y);
    obj.setWidth(w);
    obj.setHeight(h);
    ASSERT_TRUE(MatrixEQ(obj.getTransform(&parent), getTransform(x, y, w, h)));
}

TEST_F(DisplayObject_GetTransformTest, ReturnsInGrandParentsSpace_ifGrandParentGiven) {
    makeHierarchy();
    grandParent.setX(13);
    grandParent.setY(6);
    parent.setX(2);
    parent.setY(17);
    obj.setWidth(37);
    obj.setHeight(41);
    obj.setX(5);
    ASSERT_TRUE(MatrixEQ(obj.getTransform(&grandParent), getTransform(obj.x() + parent.x(), obj.y() + parent.y(), 37, 41)));
    ASSERT_TRUE(MatrixEQ(obj.getTransform(&stage()), getTransform(obj.x() + parent.x() + grandParent.x(), obj.y() + parent.y() + grandParent.y(), 37, 41)));
}
