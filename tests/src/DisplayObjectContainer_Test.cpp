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
        cont1.addChild(&obj1);
        cont1.addChild(&obj2);
        cont1.addChild(&obj3);
    }

    DisplayObject obj1;
    DisplayObject obj2;
    DisplayObject obj3;
    DisplayObjectContainer cont1;
    DisplayObjectContainer cont2;
    DisplayObjectContainer cont3;
};

class DisplayObject_DepthTest : public DisplayObjectContainer_Test {
public:
    DisplayObject_DepthTest()
            : stage(WIDTH, HEIGHT) {}

    void makeHierarchy() {
        stage.addChild(&cont1);
        cont1.addChild(&cont2);
        cont2.addChild(&cont3);
        cont3.addChild(&obj1);
        cont3.addChild(&obj2);
        cont3.addChild(&obj3);
    }

    Stage stage;
};

TEST_F(DisplayObjectContainer_Test, DefaultConstructor) {
    DisplayObjectContainer doCont;
}

TEST_F(DisplayObjectContainer_Test, NewContainerIsEmpty) {
    ASSERT_EQ(cont1.numChildren(), 0);
}

TEST_F(DisplayObjectContainer_Test, OnAddChildSizeIncrease) {
    cont1.addChild(&obj1);
    ASSERT_EQ(cont1.numChildren(), 1);
    cont1.addChild(&obj2);
    ASSERT_EQ(cont1.numChildren(), 2);
}

TEST_F(DisplayObjectContainer_Test, OnRemoveChildSizeDecreased) {
    addChildren();
    ASSERT_EQ(cont1.numChildren(), 3);
    cont1.removeChild(&obj3);
    ASSERT_EQ(cont1.numChildren(), 2);
    cont1.removeChild(&obj2);
    ASSERT_EQ(cont1.numChildren(), 1);
    cont1.removeChild(&obj1);
    ASSERT_EQ(cont1.numChildren(), 0);
}

TEST_F(DisplayObjectContainer_Test, GetChildAt) {
    addChildren();
    ASSERT_EQ(cont1.getChildAt(0), &obj1);
    ASSERT_EQ(cont1.getChildAt(1), &obj2);
    ASSERT_EQ(cont1.getChildAt(2), &obj3);
}

TEST_F(DisplayObjectContainer_Test, AddChildAt) {
    cont1.addChild(&obj3);
    cont1.addChildAt(&obj1, 0);
    cont1.addChildAt(&obj2, 1);
    ASSERT_EQ(cont1.getChildAt(0), &obj1);
    ASSERT_EQ(cont1.getChildAt(1), &obj2);
    ASSERT_EQ(cont1.getChildAt(2), &obj3);
}

TEST_F(DisplayObjectContainer_Test, RemoveChildAt) {
    addChildren();
    ASSERT_EQ(cont1.removeChildAt(2), &obj3);
    ASSERT_EQ(cont1.removeChildAt(0), &obj1);
}

TEST_F(DisplayObjectContainer_Test, RemoveChildren) {
    addChildren();
    ASSERT_EQ(cont1.numChildren(), 3);
    cont1.removeChildren();
    ASSERT_EQ(cont1.numChildren(), 0);
}

TEST_F(DisplayObjectContainer_Test, GetChildIndex) {
    addChildren();
    ASSERT_EQ(cont1.getChildIndex(&obj1), 0);
    ASSERT_EQ(cont1.getChildIndex(&obj2), 1);
    ASSERT_EQ(cont1.getChildIndex(&obj3), 2);
}

TEST_F(DisplayObjectContainer_Test, Contains) {
    addChildren();
    DisplayObject outerObject;
    ASSERT_TRUE(cont1.contains(&obj1));
    ASSERT_TRUE(cont1.contains(&obj2));
    ASSERT_TRUE(cont1.contains(&obj3));
    ASSERT_FALSE(cont1.contains(&outerObject));
}

TEST_F(DisplayObjectContainer_Test, AddChildSetsChildsParent) {
    cont1.addChild(&obj1);
    ASSERT_EQ(obj1.getParent(), &cont1);
}

TEST_F(DisplayObjectContainer_Test, AddChildAtSetsChildsParent) {
    cont1.addChildAt(&obj1, 0);
    ASSERT_EQ(obj1.getParent(), &cont1);
}

TEST_F(DisplayObjectContainer_Test, RemoveChildNullsChildsParent) {
    cont1.addChild(&obj1);
    cont1.removeChild(&obj1);
    ASSERT_TRUE(obj1.getParent() == nullptr);
}

TEST_F(DisplayObjectContainer_Test, RemoveChildAtNullsChildsParent) {
    cont1.addChild(&obj1);
    cont1.removeChildAt(0);
    ASSERT_TRUE(obj1.getParent() == nullptr);
}

TEST_F(DisplayObjectContainer_Test, RemoveChildrenNullsAllChildrensParents) {
    addChildren();
    cont1.removeChildren();
    ASSERT_TRUE(obj1.getParent() == nullptr);
    ASSERT_TRUE(obj2.getParent() == nullptr);
    ASSERT_TRUE(obj3.getParent() == nullptr);
}

TEST_F(DisplayObjectContainer_Test, AddChildToAnotherContainer_childsParentUpdated) {
    addChildren();
    DisplayObjectContainer cont2;
    cont2.addChild(&obj1);
    ASSERT_EQ(obj1.getParent(), &cont2);
    ASSERT_EQ(obj2.getParent(), &cont1);
    ASSERT_EQ(obj3.getParent(), &cont1);
    ASSERT_TRUE(cont1.contains(&obj2));
    ASSERT_TRUE(cont1.contains(&obj3));
    ASSERT_TRUE(cont2.contains(&obj1));
}

TEST_F(DisplayObjectContainer_Test, AddChildAtToAnotherContainer_childsParentUpdated) {
    addChildren();
    DisplayObjectContainer cont2;
    cont2.addChildAt(&obj1, 0);
    ASSERT_EQ(obj1.getParent(), &cont2);
    ASSERT_EQ(obj2.getParent(), &cont1);
    ASSERT_EQ(obj3.getParent(), &cont1);
    ASSERT_TRUE(cont1.contains(&obj2));
    ASSERT_TRUE(cont1.contains(&obj3));
    ASSERT_TRUE(cont2.contains(&obj1));
}

TEST_F(DisplayObjectContainer_Test, SettingWidthOrHeightHasNoEffect) {
    addChildren();
    float oldWidth = cont1.width();
    cont1.setWidth(100);
    ASSERT_THAT(cont1.width(), Eq(oldWidth));
    cont1.setWidth(200);
    ASSERT_THAT(cont1.width(), Eq(oldWidth));
    float oldHeight = cont1.height();
    cont1.setHeight(100);
    ASSERT_THAT(cont1.height(), Eq(oldHeight));
    cont1.setHeight(200);
    ASSERT_THAT(cont1.height(), Eq(oldHeight));
}

TEST_F(DisplayObject_DepthTest, Invalid_ifNotOnStage) {
    ASSERT_THAT(obj1.depth(), Eq(-1));
}

TEST_F(DisplayObject_DepthTest, StageHasDepthZero) {
    ASSERT_THAT(stage.depth(), Eq(0));
}

TEST_F(DisplayObject_DepthTest, StageChildHasDepthOne) {
    stage.addChild(&obj1);
    ASSERT_THAT(obj1.depth(), Eq(1));
    stage.addChildAt(&obj2, 0);
    ASSERT_THAT(obj2.depth(), Eq(1));
}

TEST_F(DisplayObject_DepthTest, EachNestedChildIncresesDepth) {
    stage.addChild(&cont1);
    cont1.addChild(&cont2);
    cont2.addChild(&cont3);
    cont3.addChild(&obj1);
    cont3.addChildAt(&obj2, 0);
    ASSERT_THAT(cont1.depth(), Eq(1));
    ASSERT_THAT(cont2.depth(), Eq(2));
    ASSERT_THAT(cont3.depth(), Eq(3));
    ASSERT_THAT(obj1.depth(), Eq(4));
    ASSERT_THAT(obj2.depth(), Eq(4));
}

TEST_F(DisplayObject_DepthTest, NestedChildHasInvalidDepth_ifParentIsNotOnStage) {
    cont1.addChild(&cont2);
    cont2.addChild(&obj1);
    cont2.addChildAt(&obj2, 0);
    ASSERT_THAT(cont2.depth(), Eq(-1));
    ASSERT_THAT(obj1.depth(), Eq(-1));
    ASSERT_THAT(obj2.depth(), Eq(-1));
}

TEST_F(DisplayObject_DepthTest, DepthGetsInvalidated_ifRemoved) {
    stage.addChild(&obj1);
    stage.addChild(&obj2);
    stage.addChild(&obj3);
    ASSERT_THAT(obj1.depth(), Not(-1));
    ASSERT_THAT(obj2.depth(), Not(-1));
    ASSERT_THAT(obj3.depth(), Not(-1));
    stage.removeChild(&obj1);
    stage.removeChildAt(0);
    stage.removeChildren();
    ASSERT_THAT(obj1.depth(), Eq(-1));
    ASSERT_THAT(obj2.depth(), Eq(-1));
    ASSERT_THAT(obj3.depth(), Eq(-1));
}

TEST_F(DisplayObject_DepthTest, AllDescendantsDepthGetsInvalidated_ifRemoved) {
    makeHierarchy();
    ASSERT_THAT(cont2.depth(), Not(-1));
    ASSERT_THAT(cont3.depth(), Not(-1));
    ASSERT_THAT(obj1.depth(), Not(-1));
    ASSERT_THAT(obj2.depth(), Not(-1));
    ASSERT_THAT(obj3.depth(), Not(-1));
    cont1.removeChild(&cont2);
    ASSERT_THAT(cont2.depth(), Eq(-1));
    ASSERT_THAT(cont3.depth(), Eq(-1));
    ASSERT_THAT(obj1.depth(), Eq(-1));
    ASSERT_THAT(obj2.depth(), Eq(-1));
    ASSERT_THAT(obj3.depth(), Eq(-1));

    makeHierarchy();
    ASSERT_THAT(cont2.depth(), Not(-1));
    ASSERT_THAT(cont3.depth(), Not(-1));
    ASSERT_THAT(obj1.depth(), Not(-1));
    ASSERT_THAT(obj2.depth(), Not(-1));
    ASSERT_THAT(obj3.depth(), Not(-1));
    cont1.removeChildAt(0);
    ASSERT_THAT(cont2.depth(), Eq(-1));
    ASSERT_THAT(cont3.depth(), Eq(-1));
    ASSERT_THAT(obj1.depth(), Eq(-1));
    ASSERT_THAT(obj2.depth(), Eq(-1));
    ASSERT_THAT(obj3.depth(), Eq(-1));

    makeHierarchy();
    ASSERT_THAT(cont2.depth(), Not(-1));
    ASSERT_THAT(cont3.depth(), Not(-1));
    ASSERT_THAT(obj1.depth(), Not(-1));
    ASSERT_THAT(obj2.depth(), Not(-1));
    ASSERT_THAT(obj3.depth(), Not(-1));
    cont1.removeChildren();
    ASSERT_THAT(cont2.depth(), Eq(-1));
    ASSERT_THAT(cont3.depth(), Eq(-1));
    ASSERT_THAT(obj1.depth(), Eq(-1));
    ASSERT_THAT(obj2.depth(), Eq(-1));
    ASSERT_THAT(obj3.depth(), Eq(-1));
}

TEST_F(DisplayObject_DepthTest, AllDescendantsGetProperDepth_ifTreeAdded) {
    cont1.addChild(&cont2);
    cont2.addChild(&obj1);

    ASSERT_THAT(cont1.depth(), Eq(-1));
    ASSERT_THAT(cont2.depth(), Eq(-1));
    ASSERT_THAT(obj1.depth(), Eq(-1));

    stage.addChild(&cont1);

    ASSERT_THAT(cont1.depth(), Eq(1));
    ASSERT_THAT(cont2.depth(), Eq(2));
    ASSERT_THAT(obj1.depth(), Eq(3));

    cont3.addChild(&obj2);
    cont3.addChildAt(&obj3, 0);

    ASSERT_THAT(cont3.depth(), Eq(-1));
    ASSERT_THAT(obj2.depth(), Eq(-1));
    ASSERT_THAT(obj3.depth(), Eq(-1));

    cont2.addChild(&cont3);

    ASSERT_THAT(cont3.depth(), Eq(3));
    ASSERT_THAT(obj2.depth(), Eq(4));
    ASSERT_THAT(obj3.depth(), Eq(4));
}

TEST_F(DisplayObject_DepthTest, AllDescendantsGetProperDepth_ifTreeMoved) {
    makeHierarchy();
    ASSERT_THAT(cont1.depth(), Eq(1));
    ASSERT_THAT(cont2.depth(), Eq(2));
    ASSERT_THAT(cont3.depth(), Eq(3));
    ASSERT_THAT(obj1.depth(), Eq(4));
    ASSERT_THAT(obj2.depth(), Eq(4));
    ASSERT_THAT(obj3.depth(), Eq(4));

    stage.addChild(&cont2);

    ASSERT_THAT(cont1.depth(), Eq(1));
    ASSERT_THAT(cont2.depth(), Eq(1));
    ASSERT_THAT(cont3.depth(), Eq(2));
    ASSERT_THAT(obj1.depth(), Eq(3));
    ASSERT_THAT(obj2.depth(), Eq(3));
    ASSERT_THAT(obj3.depth(), Eq(3));

    cont1.addChildAt(&cont2, 0);

    ASSERT_THAT(cont1.depth(), Eq(1));
    ASSERT_THAT(cont2.depth(), Eq(2));
    ASSERT_THAT(cont3.depth(), Eq(3));
    ASSERT_THAT(obj1.depth(), Eq(4));
    ASSERT_THAT(obj2.depth(), Eq(4));
    ASSERT_THAT(obj3.depth(), Eq(4));
}