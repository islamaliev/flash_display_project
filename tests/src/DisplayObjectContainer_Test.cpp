#include <Stage.h>
#include "DisplayObjectContainer.h"
#include "gmock/gmock-matchers.h"

using namespace testing;
using namespace flash::display;

namespace {
    const unsigned WIDTH = 40;
    const unsigned HEIGHT = 20;
}

class DisplayObjectContainer_Test : public Test {
public:
    void addChildren() {
        cont.addChild(&obj1);
        cont.addChild(&obj2);
        cont.addChild(&obj3);
    }

    DisplayObject obj1;
    DisplayObject obj2;
    DisplayObject obj3;
    DisplayObjectContainer cont;
};

class DisplayObject_DepthTest : public DisplayObjectContainer_Test {
public:
    DisplayObject_DepthTest()
            : stage(WIDTH, HEIGHT) {}

    Stage stage;
};

TEST_F(DisplayObjectContainer_Test, DefaultConstructor) {
    DisplayObjectContainer doCont;
}

TEST_F(DisplayObjectContainer_Test, NewContainerIsEmpty) {
    ASSERT_EQ(cont.numChildren(), 0);
}

TEST_F(DisplayObjectContainer_Test, OnAddChildSizeIncrease) {
    cont.addChild(&obj1);
    ASSERT_EQ(cont.numChildren(), 1);
    cont.addChild(&obj2);
    ASSERT_EQ(cont.numChildren(), 2);
}

TEST_F(DisplayObjectContainer_Test, OnRemoveChildSizeDecreased) {
    addChildren();
    ASSERT_EQ(cont.numChildren(), 3);
    cont.removeChild(&obj3);
    ASSERT_EQ(cont.numChildren(), 2);
    cont.removeChild(&obj2);
    ASSERT_EQ(cont.numChildren(), 1);
    cont.removeChild(&obj1);
    ASSERT_EQ(cont.numChildren(), 0);
}

TEST_F(DisplayObjectContainer_Test, GetChildAt) {
    addChildren();
    ASSERT_EQ(cont.getChildAt(0), &obj1);
    ASSERT_EQ(cont.getChildAt(1), &obj2);
    ASSERT_EQ(cont.getChildAt(2), &obj3);
}

TEST_F(DisplayObjectContainer_Test, AddChildAt) {
    cont.addChild(&obj3);
    cont.addChildAt(&obj1, 0);
    cont.addChildAt(&obj2, 1);
    ASSERT_EQ(cont.getChildAt(0), &obj1);
    ASSERT_EQ(cont.getChildAt(1), &obj2);
    ASSERT_EQ(cont.getChildAt(2), &obj3);
}

TEST_F(DisplayObjectContainer_Test, RemoveChildAt) {
    addChildren();
    ASSERT_EQ(cont.removeChildAt(2), &obj3);
    ASSERT_EQ(cont.removeChildAt(0), &obj1);
}

TEST_F(DisplayObjectContainer_Test, RemoveChildren) {
    addChildren();
    ASSERT_EQ(cont.numChildren(), 3);
    cont.removeChildren();
    ASSERT_EQ(cont.numChildren(), 0);
}

TEST_F(DisplayObjectContainer_Test, GetChildIndex) {
    addChildren();
    ASSERT_EQ(cont.getChildIndex(&obj1), 0);
    ASSERT_EQ(cont.getChildIndex(&obj2), 1);
    ASSERT_EQ(cont.getChildIndex(&obj3), 2);
}

TEST_F(DisplayObjectContainer_Test, Contains) {
    addChildren();
    DisplayObject outerObject;
    ASSERT_TRUE(cont.contains(&obj1));
    ASSERT_TRUE(cont.contains(&obj2));
    ASSERT_TRUE(cont.contains(&obj3));
    ASSERT_FALSE(cont.contains(&outerObject));
}

TEST_F(DisplayObjectContainer_Test, AddChildSetsChildsParent) {
    cont.addChild(&obj1);
    ASSERT_EQ(obj1.getParent(), &cont);
}

TEST_F(DisplayObjectContainer_Test, AddChildAtSetsChildsParent) {
    cont.addChildAt(&obj1, 0);
    ASSERT_EQ(obj1.getParent(), &cont);
}

TEST_F(DisplayObjectContainer_Test, RemoveChildNullsChildsParent) {
    cont.addChild(&obj1);
    cont.removeChild(&obj1);
    ASSERT_TRUE(obj1.getParent() == nullptr);
}

TEST_F(DisplayObjectContainer_Test, RemoveChildAtNullsChildsParent) {
    cont.addChild(&obj1);
    cont.removeChildAt(0);
    ASSERT_TRUE(obj1.getParent() == nullptr);
}

TEST_F(DisplayObjectContainer_Test, RemoveChildrenNullsAllChildrensParents) {
    addChildren();
    cont.removeChildren();
    ASSERT_TRUE(obj1.getParent() == nullptr);
    ASSERT_TRUE(obj2.getParent() == nullptr);
    ASSERT_TRUE(obj3.getParent() == nullptr);
}

TEST_F(DisplayObjectContainer_Test, AddChildToAnotherContainer_childsParentUpdated) {
    addChildren();
    DisplayObjectContainer cont2;
    cont2.addChild(&obj1);
    ASSERT_EQ(obj1.getParent(), &cont2);
    ASSERT_EQ(obj2.getParent(), &cont);
    ASSERT_EQ(obj3.getParent(), &cont);
    ASSERT_TRUE(cont.contains(&obj2));
    ASSERT_TRUE(cont.contains(&obj3));
    ASSERT_TRUE(cont2.contains(&obj1));
}

TEST_F(DisplayObjectContainer_Test, AddChildAtToAnotherContainer_childsParentUpdated) {
    addChildren();
    DisplayObjectContainer cont2;
    cont2.addChildAt(&obj1, 0);
    ASSERT_EQ(obj1.getParent(), &cont2);
    ASSERT_EQ(obj2.getParent(), &cont);
    ASSERT_EQ(obj3.getParent(), &cont);
    ASSERT_TRUE(cont.contains(&obj2));
    ASSERT_TRUE(cont.contains(&obj3));
    ASSERT_TRUE(cont2.contains(&obj1));
}

TEST_F(DisplayObjectContainer_Test, SettingWidthOrHeightHasNoEffect) {
    addChildren();
    float oldWidth = cont.width();
    cont.setWidth(100);
    ASSERT_THAT(cont.width(), Eq(oldWidth));
    cont.setWidth(200);
    ASSERT_THAT(cont.width(), Eq(oldWidth));
    float oldHeight = cont.height();
    cont.setHeight(100);
    ASSERT_THAT(cont.height(), Eq(oldHeight));
    cont.setHeight(200);
    ASSERT_THAT(cont.height(), Eq(oldHeight));
}

TEST_F(DisplayObject_DepthTest, Negative_ifNotOnStage) {
    ASSERT_THAT(obj1.depth(), Eq(-1));
}

TEST_F(DisplayObject_DepthTest, ZeroForStage) {
    ASSERT_THAT(stage.depth(), Eq(0));
}