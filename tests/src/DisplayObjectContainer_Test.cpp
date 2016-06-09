#include <Stage.h>
#include "DisplayObjectContainer.h"
#include "gmock/gmock-matchers.h"

using namespace testing;
using namespace flash::display;

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

    ASSERT_THAT(cont1.numChildren(), Eq(3));
    ASSERT_THAT(cont2.numChildren(), Eq(0));

    cont2.addChild(&obj1);

    ASSERT_THAT(obj1.getParent(), Eq(&cont2));
    ASSERT_THAT(obj2.getParent(), Eq(&cont1));
    ASSERT_THAT(obj3.getParent(), Eq(&cont1));
    ASSERT_THAT(cont1.numChildren(), Eq(2));
    ASSERT_THAT(cont2.numChildren(), Eq(1));
    ASSERT_TRUE(cont1.contains(&obj2));
    ASSERT_TRUE(cont1.contains(&obj3));
    ASSERT_TRUE(cont2.contains(&obj1));
    ASSERT_FALSE(cont1.contains(&obj1));
}

TEST_F(DisplayObjectContainer_Test, AddChildAtToAnotherContainer_childsParentUpdated) {
    addChildren();
    DisplayObjectContainer cont2;

    ASSERT_THAT(cont1.numChildren(), Eq(3));
    ASSERT_THAT(cont2.numChildren(), Eq(0));

    cont2.addChildAt(&obj1, 0);

    ASSERT_THAT(obj1.getParent(), Eq(&cont2));
    ASSERT_THAT(obj2.getParent(), Eq(&cont1));
    ASSERT_THAT(obj3.getParent(), Eq(&cont1));
    ASSERT_THAT(cont1.numChildren(), Eq(2));
    ASSERT_THAT(cont2.numChildren(), Eq(1));
    ASSERT_TRUE(cont1.contains(&obj2));
    ASSERT_TRUE(cont1.contains(&obj3));
    ASSERT_TRUE(cont2.contains(&obj1));
    ASSERT_FALSE(cont1.contains(&obj1));
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

TEST_F(DisplayObjectContainer_Test, AddingSameChild_whenOnlyOne) {
    cont1.addChild(&obj1);

    ASSERT_THAT(cont1.getChildAt(0), Eq(&obj1));

    cont1.addChild(&obj1);
    ASSERT_THAT(cont1.getChildAt(0), Eq(&obj1));
}

TEST_F(DisplayObjectContainer_Test, AddingSameChild_whenAmongOthers) {
    addChildren();
    ASSERT_THAT(cont1.getChildAt(0), Eq(&obj1));
    ASSERT_THAT(cont1.getChildAt(1), Eq(&obj2));
    ASSERT_THAT(cont1.getChildAt(2), Eq(&obj3));

    cont1.addChild(&obj1);
    ASSERT_THAT(cont1.getChildAt(0), Eq(&obj2));
    ASSERT_THAT(cont1.getChildAt(1), Eq(&obj3));
    ASSERT_THAT(cont1.getChildAt(2), Eq(&obj1));

    cont1.addChild(&obj3);
    ASSERT_THAT(cont1.getChildAt(0), Eq(&obj2));
    ASSERT_THAT(cont1.getChildAt(1), Eq(&obj1));
    ASSERT_THAT(cont1.getChildAt(2), Eq(&obj3));
}

TEST_F(DisplayObjectContainer_Test, AddingSameChildAtSpecificIndex_whenOnlyOne) {
    cont1.addChild(&obj1);

    ASSERT_THAT(cont1.getChildAt(0), Eq(&obj1));

    cont1.addChildAt(&obj1, 0);
    ASSERT_THAT(cont1.getChildAt(0), Eq(&obj1));
}

TEST_F(DisplayObjectContainer_Test, AddingSameChildAtSpecificIndex_whenAmongOthers) {
    addChildren();
    ASSERT_THAT(cont1.getChildAt(0), Eq(&obj1));
    ASSERT_THAT(cont1.getChildAt(1), Eq(&obj2));
    ASSERT_THAT(cont1.getChildAt(2), Eq(&obj3));

    cont1.addChildAt(&obj2, 0);
    ASSERT_THAT(cont1.getChildAt(0), Eq(&obj2));
    ASSERT_THAT(cont1.getChildAt(1), Eq(&obj1));
    ASSERT_THAT(cont1.getChildAt(2), Eq(&obj3));

    cont1.addChildAt(&obj3, 0);
    ASSERT_THAT(cont1.getChildAt(0), Eq(&obj3));
    ASSERT_THAT(cont1.getChildAt(1), Eq(&obj2));
    ASSERT_THAT(cont1.getChildAt(2), Eq(&obj1));
}