#include "gmock/gmock-matchers.h"
#include "ComponentContainer.h"
#include "Contex.h"
#include "Stage.h"
#include "RenderState.h"
#include "StackAllocator.h"
#include "RenderBufferOrganizer.h"
#include "Shape.h"
#include "Mat4.h"
#include "matrix_asserts.h"

using namespace testing;
using namespace flash;
using namespace render;

using Shape = flash::display::Shape;
using DisplayObjectContainer = flash::display::DisplayObjectContainer;
using Mat4 = flash::math::Mat4;

namespace {
    const unsigned WIDTH = 40;
    const unsigned HEIGHT = 40;

    const unsigned ALLOCATOR_SIZE = 10000;
}

class RenderBufferOrganizer_Test : public Test {
public:
    RenderBufferOrganizer_Test()
            : stage(WIDTH, HEIGHT)
            , allocator(ALLOCATOR_SIZE) {}

    void run() {
        render::RenderState r;
        stage.preRender(r);
        RenderBufferOrganizer::organize(stage, allocator, bufferData);
    }

    unsigned getNumObjects() {
        return bufferData.batchSizes[0];
    }

    const Mat4& getMatrixAt(unsigned index) {
        return *((bufferData.matrices) + index);
    }
    
    Mat4 ignoreZ(Mat4 m) {
        m.zt(0);
        return m;
    }

    display::Stage stage;

protected:
    void SetUp() override {
    }

    void TearDown() override {
    }

private:
    BufferData bufferData;
    allocator::StackAllocator allocator;
};

TEST_F(RenderBufferOrganizer_Test, ifStageIsEmpty_noTransformations) {
    run();

    ASSERT_THAT(getNumObjects(), Eq(0));
}

TEST_F(RenderBufferOrganizer_Test, oneChild) {
    Shape obj;
    obj.setWidth(37);
    stage.addChild(&obj);

    run();

    ASSERT_THAT(getNumObjects(), Eq(1));
    ASSERT_TRUE(MatrixEQ(ignoreZ(getMatrixAt(0)), obj.getTransform()));
}

TEST_F(RenderBufferOrganizer_Test, twoChildren) {
    Shape obj1;
    obj1.setWidth(37);
    Shape obj2;
    obj2.setHeight(43);
    stage.addChild(&obj1);
    stage.addChild(&obj2);

    run();

    ASSERT_THAT(getNumObjects(), Eq(2));
    ASSERT_TRUE(MatrixEQ(ignoreZ(getMatrixAt(0)), obj1.getTransform()));
    ASSERT_TRUE(MatrixEQ(ignoreZ(getMatrixAt(1)), obj2.getTransform()));
}

TEST_F(RenderBufferOrganizer_Test, ParentsTransformationIsOverriddenByItsChildsOne) {
    Shape obj;
    obj.setWidth(37);
    DisplayObjectContainer cont;
    cont.setX(43);
    stage.addChild(&cont);
    cont.addChild(&obj);

    run();

    ASSERT_THAT(getNumObjects(), Eq(1));
    ASSERT_TRUE(MatrixEQ(ignoreZ(getMatrixAt(0)), obj.getTransform(&stage)));
}

TEST_F(RenderBufferOrganizer_Test, OnlyTransformationOfLeanNodesArePresent) {
    DisplayObjectContainer cont1;
    cont1.setX(43);
    Shape obj1;
    obj1.setWidth(37);
    DisplayObjectContainer cont2;
    cont2.setY(53);
    Shape obj2;
    obj2.setHeight(11);
    Shape obj3;
    obj3.setScaleX(3);
    stage.addChild(&cont1);
    cont1.addChild(&obj1);
    cont1.addChild(&cont2);
    cont2.addChild(&obj2);
    cont2.addChild(&obj3);

    run();

    ASSERT_THAT(getNumObjects(), Eq(3));
    ASSERT_TRUE(MatrixEQ(ignoreZ(getMatrixAt(0)), obj1.getTransform(&stage)));
    ASSERT_TRUE(MatrixEQ(ignoreZ(getMatrixAt(1)), obj2.getTransform(&stage)));
    ASSERT_TRUE(MatrixEQ(ignoreZ(getMatrixAt(2)), obj3.getTransform(&stage)));
}

TEST_F(RenderBufferOrganizer_Test, EmptyParentHasNoEffect) {
    Shape obj1;
    obj1.setWidth(37);
    DisplayObjectContainer emptyCont;
    emptyCont.setX(43);
    Shape obj2;
    obj2.setHeight(11);
    DisplayObjectContainer cont2;
    cont2.setY(53);
    Shape obj3;
    obj3.setScaleX(3);
    stage.addChild(&obj1);
    stage.addChild(&emptyCont);
    stage.addChild(&obj2);
    stage.addChild(&cont2);
    cont2.addChild(&obj3);

    run();

    ASSERT_THAT(getNumObjects(), Eq(3));
    ASSERT_TRUE(MatrixEQ(ignoreZ(getMatrixAt(0)), obj1.getTransform(&stage)));
    ASSERT_TRUE(MatrixEQ(ignoreZ(getMatrixAt(1)), obj2.getTransform(&stage)));
    ASSERT_TRUE(MatrixEQ(ignoreZ(getMatrixAt(2)), obj3.getTransform(&stage)));
}
