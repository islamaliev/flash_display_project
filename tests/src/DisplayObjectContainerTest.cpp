#include "DisplayObjectContainer.h"
#include "gmock/gmock-matchers.h"

using namespace testing;
using namespace flash::display;

class DisplayObjectContainerTest : public Test {
public:
    DisplayObjectContainer cont;
};

TEST_F(DisplayObjectContainerTest, DefaultConstructor) {
    DisplayObjectContainer doCont;
}

TEST_F(DisplayObjectContainerTest, NewContainerIsEmpty) {
    ASSERT_EQ(cont.numChildren(), 0);
}

TEST_F(DisplayObjectContainerTest, OnAddChildSizeIncrease) {
    DisplayObject obj1, obj2;
    cont.addChild(&obj1);
    ASSERT_EQ(cont.numChildren(), 1);
    cont.addChild(&obj2);
    ASSERT_EQ(cont.numChildren(), 2);
}

TEST_F(DisplayObjectContainerTest, OnRemoveChildSizeDecreased) {
    DisplayObject obj1, obj2;
    cont.addChild(&obj1);
    cont.addChild(&obj2);
    ASSERT_EQ(cont.numChildren(), 2);
    cont.removeChild(&obj2);
    ASSERT_EQ(cont.numChildren(), 1);
    cont.removeChild(&obj1);
    ASSERT_EQ(cont.numChildren(), 0);
}