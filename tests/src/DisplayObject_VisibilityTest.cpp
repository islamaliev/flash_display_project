#include "gmock/gmock-matchers.h"
#include "Stage.h"
#include "RenderState.h"

using namespace testing;
using DisplayObject = flash::display::DisplayObject;
using DisplayObjectContainer = flash::display::DisplayObjectContainer;
using Stage = flash::display::Stage;

class DisplayObject_VisibilityTest : public testing::Test {
public:
    DisplayObject_VisibilityTest()
            : stage(100, 100) {};

    void updateStageOrder() {
        flash::render::RenderState r;
        stage.preRender(r);
    }

    DisplayObject obj1;
    DisplayObject obj2;
    DisplayObjectContainer cont1;
    DisplayObjectContainer cont2;
    Stage stage;
};

TEST_F(DisplayObject_VisibilityTest, SetGet) {
    obj1.setVisible(false);
    ASSERT_THAT(obj1.visible(), Eq(false));
    obj1.setVisible(true);
    ASSERT_THAT(obj1.visible(), Eq(true));
}

TEST_F(DisplayObject_VisibilityTest, ParentsVisibilityHasNoImpactOnChilsOne) {
    cont1.addChild(&obj1);
    ASSERT_THAT(obj1.visible(), Eq(true));
    cont1.setVisible(false);
    ASSERT_THAT(obj1.visible(), Eq(true));
}

TEST_F(DisplayObject_VisibilityTest, ifInvisible_orderIsReset) {
    stage.addChild(&obj1);
    updateStageOrder();
    ASSERT_THAT(obj1.orderIndex(), Not(-1));

    obj1.setVisible(false);

    updateStageOrder();
    ASSERT_THAT(obj1.orderIndex(), Eq(-1));
}

TEST_F(DisplayObject_VisibilityTest, ifContainerInvisible_allChildrensOrderIsReset) {
    stage.addChild(&cont1);
    cont1.addChild(&cont2);
    cont2.addChild(&obj1);
    cont2.addChild(&obj2);
    updateStageOrder();
    ASSERT_THAT(obj1.orderIndex(), Not(-1));
    ASSERT_THAT(obj2.orderIndex(), Not(-1));
    ASSERT_THAT(cont1.orderIndex(), Not(-1));
    ASSERT_THAT(cont2.orderIndex(), Not(-1));

    cont1.setVisible(false);

    updateStageOrder();
    ASSERT_THAT(obj1.orderIndex(), Eq(-1));
    ASSERT_THAT(obj2.orderIndex(), Eq(-1));
    ASSERT_THAT(cont1.orderIndex(), Eq(-1));
    ASSERT_THAT(cont2.orderIndex(), Eq(-1));
}

TEST_F(DisplayObject_VisibilityTest, ifInvisible_siblingTakesItsOrder) {
    stage.addChild(&cont1);
    stage.addChild(&cont2);
    stage.addChild(&obj1);
    stage.addChild(&obj2);
    updateStageOrder();
    ASSERT_THAT(obj1.orderIndex(), Not(stage.orderIndex() + 1));

    cont1.setVisible(false);
    cont2.setVisible(false);
    obj2.setVisible(false);

    updateStageOrder();
    ASSERT_THAT(obj1.orderIndex(), Eq(stage.orderIndex() + 1));
}

TEST_F(DisplayObject_VisibilityTest, ifVisible_orderIsRestored) {
    stage.addChild(&cont1);
    cont1.addChild(&cont2);
    stage.addChild(&obj1);
    stage.addChild(&obj2);
    updateStageOrder();

    int orderCont1 = cont1.orderIndex();
    int orderCont2 = cont2.orderIndex();
    int orderObj1 = obj1.orderIndex();
    int orderObj2 = obj2.orderIndex();

    cont1.setVisible(false);
    obj2.setVisible(false);
    updateStageOrder();

    ASSERT_THAT(obj1.orderIndex(), Not(orderObj1));
    ASSERT_THAT(obj2.orderIndex(), Not(orderObj2));
    ASSERT_THAT(cont1.orderIndex(), Not(orderCont1));
    ASSERT_THAT(cont2.orderIndex(), Not(orderCont2));
    
    cont1.setVisible(true);
    obj2.setVisible(true);
    updateStageOrder();

    ASSERT_THAT(obj1.orderIndex(), Eq(orderObj1));
    ASSERT_THAT(obj2.orderIndex(), Eq(orderObj2));
    ASSERT_THAT(cont1.orderIndex(), Eq(orderCont1));
    ASSERT_THAT(cont2.orderIndex(), Eq(orderCont2));
}

