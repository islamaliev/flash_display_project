#include <Stage.h>
#include <Shape.h>
#include "DisplayObjectContainer.h"
#include "gmock/gmock-matchers.h"

using namespace testing;
using namespace flash::display;

namespace {
    const unsigned WIDTH = 40;
    const unsigned HEIGHT = 20;
}

class DisplayObject_TreeSizeTest : public Test {
public:
    DisplayObject_TreeSizeTest()
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
    Shape obj1;
    Shape obj2;
    Shape obj3;
    DisplayObjectContainer cont1;
    DisplayObjectContainer cont2;
    DisplayObjectContainer cont3;
};

TEST_F(DisplayObject_TreeSizeTest, InitiallyIsOne) {
    ASSERT_THAT(obj1.treeSize(), Eq(1));
    ASSERT_THAT(cont1.treeSize(), Eq(1));
    ASSERT_THAT(stage.treeSize(), Eq(1));
}

TEST_F(DisplayObject_TreeSizeTest, isTwo_ifChildIsAdded) {
    cont1.addChild(&obj1);
    ASSERT_THAT(cont1.treeSize(), Eq(2));

    cont2.addChildAt(&cont3, 0);
    ASSERT_THAT(cont2.treeSize(), Eq(2));

    stage.addChild(&obj2);
    ASSERT_THAT(stage.treeSize(), Eq(2));
}

TEST_F(DisplayObject_TreeSizeTest, isOne_ifChildIsRemoved) {
    cont1.addChild(&obj1);
    ASSERT_THAT(cont1.treeSize(), Not(1));
    cont1.removeChild(&obj1);
    ASSERT_THAT(cont1.treeSize(), Eq(1));

    cont2.addChildAt(&cont3, 0);
    ASSERT_THAT(cont2.treeSize(), Not(1));
    cont2.removeChildAt(0);
    ASSERT_THAT(cont2.treeSize(), Eq(1));

    stage.addChild(&obj2);
    ASSERT_THAT(stage.treeSize(), Not(1));
    stage.removeChildren();
    ASSERT_THAT(stage.treeSize(), Eq(1));
}

TEST_F(DisplayObject_TreeSizeTest, EveryAddedChildIncreasesTreeSize) {
    ASSERT_THAT(cont1.treeSize(), Eq(1));

    cont1.addChild(&obj1);
    ASSERT_THAT(cont1.treeSize(), Eq(2));

    cont1.addChild(&obj2);
    ASSERT_THAT(cont1.treeSize(), Eq(3));

    cont1.addChild(&cont2);
    ASSERT_THAT(cont1.treeSize(), Eq(4));
}

TEST_F(DisplayObject_TreeSizeTest, EveryRemovedChildDecreasesTreeSize) {
    cont1.addChild(&obj1);
    cont1.addChild(&obj2);
    cont1.addChild(&cont2);
    cont1.addChild(&cont3);
    ASSERT_THAT(cont1.treeSize(), Eq(5));

    cont1.removeChild(&obj1);
    ASSERT_THAT(cont1.treeSize(), Eq(4));

    cont1.removeChildAt(0);
    ASSERT_THAT(cont1.treeSize(), Eq(3));

    cont1.removeChildren();
    ASSERT_THAT(cont1.treeSize(), Eq(1));
}

TEST_F(DisplayObject_TreeSizeTest, EveryAddedDescendantIncreasesTreeSize) {
    cont1.addChild(&cont2);
    ASSERT_THAT(cont1.treeSize(), Eq(2));

    cont2.addChild(&cont3);
    ASSERT_THAT(cont1.treeSize(), Eq(3));
    ASSERT_THAT(cont2.treeSize(), Eq(2));

    cont3.addChild(&obj1);
    ASSERT_THAT(cont1.treeSize(), Eq(4));
    ASSERT_THAT(cont2.treeSize(), Eq(3));

    cont3.addChild(&obj2);
    ASSERT_THAT(cont1.treeSize(), Eq(5));
    ASSERT_THAT(cont2.treeSize(), Eq(4));
}

TEST_F(DisplayObject_TreeSizeTest, EveryRemovedDecsendantDecreasesTreeSize) {
    makeHierarchy();
    ASSERT_THAT(stage.treeSize(), Eq(7));
    ASSERT_THAT(cont1.treeSize(), Eq(6));
    ASSERT_THAT(cont2.treeSize(), Eq(5));

    cont3.removeChild(&obj1);
    ASSERT_THAT(stage.treeSize(), Eq(6));
    ASSERT_THAT(cont1.treeSize(), Eq(5));
    ASSERT_THAT(cont2.treeSize(), Eq(4));

    cont3.removeChildren();
    ASSERT_THAT(stage.treeSize(), Eq(4));
    ASSERT_THAT(cont1.treeSize(), Eq(3));
    ASSERT_THAT(cont2.treeSize(), Eq(2));

    cont2.removeChildAt(0);
    ASSERT_THAT(stage.treeSize(), Eq(3));
    ASSERT_THAT(cont1.treeSize(), Eq(2));
    ASSERT_THAT(cont2.treeSize(), Eq(1));

    cont1.removeChildren();
    ASSERT_THAT(stage.treeSize(), Eq(2));
    ASSERT_THAT(cont1.treeSize(), Eq(1));
}

TEST_F(DisplayObject_TreeSizeTest, AddingTreeBranch) {
    stage.addChild(&cont1);
    cont2.addChild(&obj1);
    cont3.addChild(&obj2);
    cont3.addChild(&obj3);

    ASSERT_THAT(cont2.treeSize(), Eq(2));
    ASSERT_THAT(cont3.treeSize(), Eq(3));

    cont2.addChild(&cont3);
    ASSERT_THAT(cont2.treeSize(), Eq(5));

    ASSERT_THAT(stage.treeSize(), Eq(2));
    ASSERT_THAT(cont1.treeSize(), Eq(1));

    cont1.addChildAt(&cont2, 0);
    ASSERT_THAT(stage.treeSize(), Eq(7));
    ASSERT_THAT(cont1.treeSize(), Eq(6));
}

TEST_F(DisplayObject_TreeSizeTest, RemovingTreeBranch) {
    stage.addChild(&cont1);
    cont1.addChild(&cont2);
    cont2.addChild(&obj1);
    cont2.addChild(&cont3);
    cont3.addChild(&obj2);
    cont3.addChild(&obj3);

    ASSERT_THAT(stage.treeSize(), Eq(7));
    ASSERT_THAT(cont1.treeSize(), Eq(6));
    ASSERT_THAT(cont3.treeSize(), Eq(3));

    cont2.removeChild(&cont3);
    ASSERT_THAT(stage.treeSize(), Eq(4));
    ASSERT_THAT(cont1.treeSize(), Eq(3));

    stage.removeChildAt(0);
    ASSERT_THAT(stage.treeSize(), Eq(1));

    stage.addChild(&cont1);
    cont2.addChild(&cont3);
    ASSERT_THAT(stage.treeSize(), Eq(7));
    ASSERT_THAT(cont1.treeSize(), Eq(6));
    ASSERT_THAT(cont2.treeSize(), Eq(5));

    cont2.removeChildren();
    ASSERT_THAT(stage.treeSize(), Eq(3));
    ASSERT_THAT(cont1.treeSize(), Eq(2));
}

TEST_F(DisplayObject_TreeSizeTest, MovingTreeBranch) {
    stage.addChild(&cont1);
    stage.addChild(&cont2);
    cont3.addChild(&obj1);
    cont3.addChild(&obj2);
    cont3.addChild(&obj3);

    cont2.addChild(&cont3);

    ASSERT_THAT(stage.treeSize(), Eq(7));
    ASSERT_THAT(cont1.treeSize(), Eq(1));
    ASSERT_THAT(cont2.treeSize(), Eq(5));

    cont1.addChild(&cont3);
    ASSERT_THAT(stage.treeSize(), Eq(7));
    ASSERT_THAT(cont1.treeSize(), Eq(5));
    ASSERT_THAT(cont2.treeSize(), Eq(1));

    cont2.addChildAt(&cont3, 0);
    ASSERT_THAT(stage.treeSize(), Eq(7));
    ASSERT_THAT(cont1.treeSize(), Eq(1));
    ASSERT_THAT(cont2.treeSize(), Eq(5));
}