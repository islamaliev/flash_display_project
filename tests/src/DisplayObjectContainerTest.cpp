#include "DisplayObjectContainer.h"
#include "gmock/gmock-matchers.h"

using namespace testing;
using namespace flash::display;

class DisplayObjectContainerTest : public Test {
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

TEST_F(DisplayObjectContainerTest, DefaultConstructor) {
    DisplayObjectContainer doCont;
}

TEST_F(DisplayObjectContainerTest, NewContainerIsEmpty) {
    ASSERT_EQ(cont.numChildren(), 0);
}

TEST_F(DisplayObjectContainerTest, OnAddChildSizeIncrease) {
    cont.addChild(&obj1);
    ASSERT_EQ(cont.numChildren(), 1);
    cont.addChild(&obj2);
    ASSERT_EQ(cont.numChildren(), 2);
}

TEST_F(DisplayObjectContainerTest, OnRemoveChildSizeDecreased) {
    addChildren();
    ASSERT_EQ(cont.numChildren(), 3);
    cont.removeChild(&obj3);
    ASSERT_EQ(cont.numChildren(), 2);
    cont.removeChild(&obj2);
    ASSERT_EQ(cont.numChildren(), 1);
    cont.removeChild(&obj1);
    ASSERT_EQ(cont.numChildren(), 0);
}

TEST_F(DisplayObjectContainerTest, GetChildAt) {
    addChildren();
    ASSERT_EQ(cont.getChildAt(0), &obj1);
    ASSERT_EQ(cont.getChildAt(1), &obj2);
    ASSERT_EQ(cont.getChildAt(2), &obj3);
}

TEST_F(DisplayObjectContainerTest, AddChildAt) {
    cont.addChild(&obj3);
    cont.addChildAt(&obj1, 0);
    cont.addChildAt(&obj2, 1);
    ASSERT_EQ(cont.getChildAt(0), &obj1);
    ASSERT_EQ(cont.getChildAt(1), &obj2);
    ASSERT_EQ(cont.getChildAt(2), &obj3);
}

TEST_F(DisplayObjectContainerTest, RemoveChildAt) {
    addChildren();
    ASSERT_EQ(cont.removeChildAt(2), &obj3);
    ASSERT_EQ(cont.removeChildAt(0), &obj1);
}

TEST_F(DisplayObjectContainerTest, RemoveChildren) {
    addChildren();
    ASSERT_EQ(cont.numChildren(), 3);
    cont.removeChildren();
    ASSERT_EQ(cont.numChildren(), 0);
}

TEST_F(DisplayObjectContainerTest, GetChildIndex) {
    addChildren();
    ASSERT_EQ(cont.getChildIndex(&obj1), 0);
    ASSERT_EQ(cont.getChildIndex(&obj2), 1);
    ASSERT_EQ(cont.getChildIndex(&obj3), 2);
}

TEST_F(DisplayObjectContainerTest, Contains) {
    addChildren();
    DisplayObject outerObject;
    ASSERT_TRUE(cont.contains(&obj1));
    ASSERT_TRUE(cont.contains(&obj2));
    ASSERT_TRUE(cont.contains(&obj3));
    ASSERT_FALSE(cont.contains(&outerObject));
}