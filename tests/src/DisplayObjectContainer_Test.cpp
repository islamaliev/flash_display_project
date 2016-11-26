#include "gmock/gmock-matchers.h"
#include "Shape.h"
#include "DisplayObjectContainer.h"

using namespace testing;
using namespace flash::display;

class DisplayObjectContainer_Test : public Test {
public:
    void addChildren() {
        container.addChild(&obj1);
        container.addChild(&obj2);
        container.addChild(&obj3);
    }

    Shape obj1;
    Shape obj2;
    Shape obj3;
    DisplayObjectContainer container;
};

TEST_F(DisplayObjectContainer_Test, DefaultConstructor) {
    DisplayObjectContainer doCont;
}

TEST_F(DisplayObjectContainer_Test, NewContainerIsEmpty) {
    ASSERT_EQ(container.numChildren(), 0);
}

TEST_F(DisplayObjectContainer_Test, OnAddChildSizeIncrease) {
    container.addChild(&obj1);
    ASSERT_EQ(container.numChildren(), 1);
    container.addChild(&obj2);
    ASSERT_EQ(container.numChildren(), 2);
}

TEST_F(DisplayObjectContainer_Test, OnRemoveChildSizeDecreased) {
    addChildren();
    ASSERT_EQ(container.numChildren(), 3);
    container.removeChild(&obj3);
    ASSERT_EQ(container.numChildren(), 2);
    container.removeChild(&obj2);
    ASSERT_EQ(container.numChildren(), 1);
    container.removeChild(&obj1);
    ASSERT_EQ(container.numChildren(), 0);
}

TEST_F(DisplayObjectContainer_Test, GetChildAt) {
    addChildren();
    ASSERT_EQ(container.getChildAt(0), &obj1);
    ASSERT_EQ(container.getChildAt(1), &obj2);
    ASSERT_EQ(container.getChildAt(2), &obj3);
}

TEST_F(DisplayObjectContainer_Test, AddChildAt) {
    container.addChild(&obj3);
    container.addChildAt(&obj1, 0);
    container.addChildAt(&obj2, 1);
    ASSERT_EQ(container.getChildAt(0), &obj1);
    ASSERT_EQ(container.getChildAt(1), &obj2);
    ASSERT_EQ(container.getChildAt(2), &obj3);
}

TEST_F(DisplayObjectContainer_Test, RemoveChildAt) {
    addChildren();
    ASSERT_EQ(container.removeChildAt(2), &obj3);
    ASSERT_EQ(container.removeChildAt(0), &obj1);
}

TEST_F(DisplayObjectContainer_Test, RemoveChildren) {
    addChildren();
    ASSERT_EQ(container.numChildren(), 3);
    container.removeChildren();
    ASSERT_EQ(container.numChildren(), 0);
}

TEST_F(DisplayObjectContainer_Test, GetChildIndex) {
    addChildren();
    ASSERT_EQ(container.getChildIndex(&obj1), 0);
    ASSERT_EQ(container.getChildIndex(&obj2), 1);
    ASSERT_EQ(container.getChildIndex(&obj3), 2);
}

TEST_F(DisplayObjectContainer_Test, Contains) {
    addChildren();
    Shape outerObject;
    ASSERT_TRUE(container.contains(&obj1));
    ASSERT_TRUE(container.contains(&obj2));
    ASSERT_TRUE(container.contains(&obj3));
    ASSERT_FALSE(container.contains(&outerObject));
}

TEST_F(DisplayObjectContainer_Test, AddChildSetsChildsParent) {
    container.addChild(&obj1);
    ASSERT_EQ(obj1.getParent(), &container);
}

TEST_F(DisplayObjectContainer_Test, AddChildAtSetsChildsParent) {
    container.addChildAt(&obj1, 0);
    ASSERT_EQ(obj1.getParent(), &container);
}

TEST_F(DisplayObjectContainer_Test, RemoveChildNullsChildsParent) {
    container.addChild(&obj1);
    container.removeChild(&obj1);
    ASSERT_TRUE(obj1.getParent() == nullptr);
}

TEST_F(DisplayObjectContainer_Test, RemoveChildAtNullsChildsParent) {
    container.addChild(&obj1);
    container.removeChildAt(0);
    ASSERT_TRUE(obj1.getParent() == nullptr);
}

TEST_F(DisplayObjectContainer_Test, RemoveChildrenNullsAllChildrensParents) {
    addChildren();
    container.removeChildren();
    ASSERT_TRUE(obj1.getParent() == nullptr);
    ASSERT_TRUE(obj2.getParent() == nullptr);
    ASSERT_TRUE(obj3.getParent() == nullptr);
}

TEST_F(DisplayObjectContainer_Test, AddChildToAnotherContainer_childsParentUpdated) {
    addChildren();
    DisplayObjectContainer cont2;

    ASSERT_THAT(container.numChildren(), Eq(3));
    ASSERT_THAT(cont2.numChildren(), Eq(0));

    cont2.addChild(&obj1);

    ASSERT_THAT(obj1.getParent(), Eq(&cont2));
    ASSERT_THAT(obj2.getParent(), Eq(&container));
    ASSERT_THAT(obj3.getParent(), Eq(&container));
    ASSERT_THAT(container.numChildren(), Eq(2));
    ASSERT_THAT(cont2.numChildren(), Eq(1));
    ASSERT_TRUE(container.contains(&obj2));
    ASSERT_TRUE(container.contains(&obj3));
    ASSERT_TRUE(cont2.contains(&obj1));
    ASSERT_FALSE(container.contains(&obj1));
}

TEST_F(DisplayObjectContainer_Test, AddChildAtToAnotherContainer_childsParentUpdated) {
    addChildren();
    DisplayObjectContainer cont2;

    ASSERT_THAT(container.numChildren(), Eq(3));
    ASSERT_THAT(cont2.numChildren(), Eq(0));

    cont2.addChildAt(&obj1, 0);

    ASSERT_THAT(obj1.getParent(), Eq(&cont2));
    ASSERT_THAT(obj2.getParent(), Eq(&container));
    ASSERT_THAT(obj3.getParent(), Eq(&container));
    ASSERT_THAT(container.numChildren(), Eq(2));
    ASSERT_THAT(cont2.numChildren(), Eq(1));
    ASSERT_TRUE(container.contains(&obj2));
    ASSERT_TRUE(container.contains(&obj3));
    ASSERT_TRUE(cont2.contains(&obj1));
    ASSERT_FALSE(container.contains(&obj1));
}

TEST_F(DisplayObjectContainer_Test, SettingWidthOrHeightHasNoEffect) {
    addChildren();
    float oldWidth = container.width();
    container.setWidth(100);
    ASSERT_THAT(container.width(), Eq(oldWidth));
    container.setWidth(200);
    ASSERT_THAT(container.width(), Eq(oldWidth));
    float oldHeight = container.height();
    container.setHeight(100);
    ASSERT_THAT(container.height(), Eq(oldHeight));
    container.setHeight(200);
    ASSERT_THAT(container.height(), Eq(oldHeight));
}

TEST_F(DisplayObjectContainer_Test, AddingSameChild_whenOnlyOne) {
    container.addChild(&obj1);

    ASSERT_THAT(container.getChildAt(0), Eq(&obj1));

    container.addChild(&obj1);
    ASSERT_THAT(container.getChildAt(0), Eq(&obj1));
}

TEST_F(DisplayObjectContainer_Test, AddingSameChild_whenAmongOthers) {
    addChildren();
    ASSERT_THAT(container.getChildAt(0), Eq(&obj1));
    ASSERT_THAT(container.getChildAt(1), Eq(&obj2));
    ASSERT_THAT(container.getChildAt(2), Eq(&obj3));

    container.addChild(&obj1);
    ASSERT_THAT(container.getChildAt(0), Eq(&obj2));
    ASSERT_THAT(container.getChildAt(1), Eq(&obj3));
    ASSERT_THAT(container.getChildAt(2), Eq(&obj1));

    container.addChild(&obj3);
    ASSERT_THAT(container.getChildAt(0), Eq(&obj2));
    ASSERT_THAT(container.getChildAt(1), Eq(&obj1));
    ASSERT_THAT(container.getChildAt(2), Eq(&obj3));
}

TEST_F(DisplayObjectContainer_Test, AddingSameChildAtSpecificIndex_whenOnlyOne) {
    container.addChild(&obj1);

    ASSERT_THAT(container.getChildAt(0), Eq(&obj1));

    container.addChildAt(&obj1, 0);
    ASSERT_THAT(container.getChildAt(0), Eq(&obj1));
}

TEST_F(DisplayObjectContainer_Test, AddingSameChildAtSpecificIndex_whenAmongOthers) {
    addChildren();
    ASSERT_THAT(container.getChildAt(0), Eq(&obj1));
    ASSERT_THAT(container.getChildAt(1), Eq(&obj2));
    ASSERT_THAT(container.getChildAt(2), Eq(&obj3));

    container.addChildAt(&obj2, 0);
    ASSERT_THAT(container.getChildAt(0), Eq(&obj2));
    ASSERT_THAT(container.getChildAt(1), Eq(&obj1));
    ASSERT_THAT(container.getChildAt(2), Eq(&obj3));

    container.addChildAt(&obj3, 0);
    ASSERT_THAT(container.getChildAt(0), Eq(&obj3));
    ASSERT_THAT(container.getChildAt(1), Eq(&obj2));
    ASSERT_THAT(container.getChildAt(2), Eq(&obj1));
}

TEST_F(DisplayObjectContainer_Test, WhenChildIsDestroyed_itGetsRemovedFromParent) {
    container.addChild(&obj1);

    {
        Shape tempChild1;
        Shape tempChild2;

        container.addChild(&tempChild2);
        container.addChildAt(&tempChild1, 0);

        ASSERT_TRUE(container.contains(&obj1));
        ASSERT_TRUE(container.contains(&tempChild1));
        ASSERT_TRUE(container.contains(&tempChild2));
        ASSERT_THAT(container.numChildren(), Eq(3));
    }

    ASSERT_TRUE(container.contains(&obj1));
    ASSERT_THAT(container.numChildren(), Eq(1));
}

TEST_F(DisplayObjectContainer_Test, WhenContainerIsDestroyed_allChildrenAreRemoved) {
    {
        DisplayObjectContainer tempCont;
        tempCont.addChild(&obj1);
        tempCont.addChildAt(&obj2, 0);

        ASSERT_THAT(obj1.getParent(), Eq(&tempCont));
        ASSERT_THAT(obj2.getParent(), Eq(&tempCont));
    }

    ASSERT_THAT(obj1.getParent(), Eq(nullptr));
    ASSERT_THAT(obj2.getParent(), Eq(nullptr));
}