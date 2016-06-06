#include <Stage.h>
#include "DisplayObjectContainer.h"
#include "gmock/gmock-matchers.h"

using namespace testing;
using namespace flash::display;

namespace {
    const unsigned WIDTH = 40;
    const unsigned HEIGHT = 20;
}

class DisplayObject_DepthTest : public Test {
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
    DisplayObject obj1;
    DisplayObject obj2;
    DisplayObject obj3;
    DisplayObjectContainer cont1;
    DisplayObjectContainer cont2;
    DisplayObjectContainer cont3;
};

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