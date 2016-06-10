#include <Stage.h>
#include "gmock/gmock-matchers.h"

using namespace testing;
using namespace flash::display;

namespace {
    const unsigned WIDTH = 40;
    const unsigned HEIGHT = 20;
}

class DisplayObject_OrderIndexTest : public Test {
public:
    DisplayObject_OrderIndexTest()
            : stage(WIDTH, HEIGHT) {}

    void makeHierarchy()
    {
        stage.addChildAt(&obj1, 0);
        stage.addChild(&cont1);
        cont1.addChild(&cont2);
        cont2.addChild(&obj2);
        cont1.addChild(&cont3);
        cont3.addChildAt(&obj3, 0);
        cont3.addChild(&cont4);
        cont4.addChild(&obj4);

        //      s
        //    /   \
        //  o1     c1
        //        /  \
        //      c2    c3
        //     /     /  \
        //   o2    o3    c4
        //              /
        //            o4
    }

    Stage stage;
    DisplayObject obj1;
    DisplayObject obj2;
    DisplayObject obj3;
    DisplayObject obj4;
    DisplayObjectContainer cont1;
    DisplayObjectContainer cont2;
    DisplayObjectContainer cont3;
    DisplayObjectContainer cont4;
};

TEST_F(DisplayObject_OrderIndexTest, StageHasZeroOrder) {
    stage.updateOrder();
    ASSERT_THAT(stage.orderIndex(), Eq(0));
}

TEST_F(DisplayObject_OrderIndexTest, ChildrenAreOrderedOneAfterAnother) {
    stage.addChild(&obj2);
    stage.addChild(&obj3);
    stage.addChildAt(&obj1, 0);

    stage.updateOrder();
    ASSERT_THAT(stage.orderIndex(), Eq(0));
    ASSERT_THAT(obj1.orderIndex(), Eq(1));
    ASSERT_THAT(obj2.orderIndex(), Eq(2));
    ASSERT_THAT(obj3.orderIndex(), Eq(3));
}

TEST_F(DisplayObject_OrderIndexTest, DescendantsAreOrderedInTreeTraverseOrder) {
    makeHierarchy();

    stage.updateOrder();
    ASSERT_THAT(stage.orderIndex(), Eq(0));
    ASSERT_THAT(obj1.orderIndex(), Eq(1));
    ASSERT_THAT(cont1.orderIndex(), Eq(2));
    ASSERT_THAT(cont2.orderIndex(), Eq(3));
    ASSERT_THAT(obj2.orderIndex(), Eq(4));
    ASSERT_THAT(cont3.orderIndex(), Eq(5));
    ASSERT_THAT(obj3.orderIndex(), Eq(6));
    ASSERT_THAT(cont4.orderIndex(), Eq(7));
    ASSERT_THAT(obj4.orderIndex(), Eq(8));
}

TEST_F(DisplayObject_OrderIndexTest, DescendantsOrderIsUpdatedProperly_whenBranchIsMoved) {
    makeHierarchy();

    stage.updateOrder();

    cont2.addChild(&cont4);
    //       s
    //     /   \
    //   o1      c1
    //         /    \
    //       c2      c3
    //      /  \    /
    //    o2   c4  o3
    //         /
    //       o4

    stage.updateOrder();

    ASSERT_THAT(stage.orderIndex(), Eq(0));
    ASSERT_THAT(obj1.orderIndex(), Eq(1));
    ASSERT_THAT(cont1.orderIndex(), Eq(2));
    ASSERT_THAT(cont2.orderIndex(), Eq(3));
    ASSERT_THAT(obj2.orderIndex(), Eq(4));
    ASSERT_THAT(cont4.orderIndex(), Eq(5));
    ASSERT_THAT(obj4.orderIndex(), Eq(6));
    ASSERT_THAT(cont3.orderIndex(), Eq(7));
    ASSERT_THAT(obj3.orderIndex(), Eq(8));

    stage.addChildAt(&cont4, 0);
    cont4.addChildAt(&cont1, 1);
    //          s
    //        /   \
    //      c4     o1
    //     /  \
    //   o4    c1
    //        /   \
    //      c2     c3
    //     /      /
    //   o2     o3

    stage.updateOrder();

    ASSERT_THAT(stage.orderIndex(), Eq(0));
    ASSERT_THAT(cont4.orderIndex(), Eq(1));
    ASSERT_THAT(obj4.orderIndex(), Eq(2));
    ASSERT_THAT(cont1.orderIndex(), Eq(3));
    ASSERT_THAT(cont2.orderIndex(), Eq(4));
    ASSERT_THAT(obj2.orderIndex(), Eq(5));
    ASSERT_THAT(cont3.orderIndex(), Eq(6));
    ASSERT_THAT(obj3.orderIndex(), Eq(7));
    ASSERT_THAT(obj1.orderIndex(), Eq(8));

}
