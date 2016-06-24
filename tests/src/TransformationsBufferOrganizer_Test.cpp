#include "gmock/gmock-matchers.h"
#include "ComponentContainer.h"
#include "Contex.h"
#include "Stage.h"
#include "StackAllocator.h"
#include "DisplayObject.h"
#include "Mat4.h"

using namespace testing;
using namespace flash;
using namespace render;

using DisplayObject = flash::display::DisplayObject;
using DisplayObjectContainer = flash::display::DisplayObjectContainer;
using Mat4 = flash::math::Mat4;

namespace {
    const unsigned WIDTH = 40;
    const unsigned HEIGHT = 40;

    const unsigned ALLOCATOR_SIZE = 10000;

    const unsigned MATRIX_SIZE = sizeof(Mat4);

    std::string toString(const Mat4& m) {
        char buf[160];
        sprintf(buf, "[%.2f, %.2f, %.2f, %.2f,   %.2f, %.2f, %.2f, %.2f,   %.2f, %.2f, %.2f, %.2f,   %.2f, %.2f, %.2f, %.2f]"
                , m.v1.x, m.v1.y, m.v1.z, m.v1.w, m.v2.x, m.v2.y, m.v2.z, m.v2.w
                , m.v3.x, m.v3.y, m.v3.z, m.v3.w, m.vt.x, m.vt.y, m.vt.z, m.vt.w);
        return std::string(buf);
    }
}

class TransformationsBufferOrganizer_Test : public Test {
public:
    TransformationsBufferOrganizer_Test()
            : stage(WIDTH, HEIGHT)
            , allocator(ALLOCATOR_SIZE) {}

    void run() {
        stage.updateOrder();
        Context::TransformationsBufferOrganizer::organize(stage, allocator, bufferData);
    }

    unsigned getNumMatrices() {
        return bufferData.matricesSize / MATRIX_SIZE;
    }

    const Mat4& getMatrixAt(unsigned index) {
        return *(((Mat4*) bufferData.matrices) + index);
    }

    ::testing::AssertionResult MatrixEQ(const Mat4& actual, const Mat4& expected) {
        if (!actual.isEqual(expected)) {
            return ::testing::AssertionFailure() << "\nactual matrix:   " << toString(actual)
                   << "\nexpected matrix: " << toString(expected);
        }
        return ::testing::AssertionSuccess();
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

TEST_F(TransformationsBufferOrganizer_Test, ifStageIsEmpty_noTransformations) {
    run();

    ASSERT_THAT(getNumMatrices(), Eq(0));
}

TEST_F(TransformationsBufferOrganizer_Test, oneChild) {
    DisplayObject obj;
    obj.setWidth(37);
    stage.addChild(&obj);

    run();

    ASSERT_THAT(getNumMatrices(), Eq(1));
    ASSERT_TRUE(MatrixEQ(getMatrixAt(0), obj.getTransform()));
}

TEST_F(TransformationsBufferOrganizer_Test, twoChildren) {
    DisplayObject obj1;
    obj1.setWidth(37);
    DisplayObject obj2;
    obj2.setHeight(43);
    stage.addChild(&obj1);
    stage.addChild(&obj2);

    run();

    ASSERT_THAT(getNumMatrices(), Eq(2));
    ASSERT_TRUE(MatrixEQ(getMatrixAt(0), obj1.getTransform()));
    ASSERT_TRUE(MatrixEQ(getMatrixAt(1), obj2.getTransform()));
}

TEST_F(TransformationsBufferOrganizer_Test, ParentsTransformationIsOverriddenByItsChildsOne) {
    DisplayObject obj;
    obj.setWidth(37);
    DisplayObjectContainer cont;
    cont.setX(43);
    stage.addChild(&cont);
    cont.addChild(&obj);

    run();

    ASSERT_THAT(getNumMatrices(), Eq(1));
    ASSERT_TRUE(MatrixEQ(getMatrixAt(0), obj.getTransform(&stage)));
}

TEST_F(TransformationsBufferOrganizer_Test, OnlyTransformationOfLeanNodesArePresent) {
    DisplayObjectContainer cont1;
    cont1.setX(43);
    DisplayObject obj1;
    obj1.setWidth(37);
    DisplayObjectContainer cont2;
    cont2.setY(53);
    DisplayObject obj2;
    obj2.setHeight(11);
    DisplayObject obj3;
    obj3.setScaleX(3);
    stage.addChild(&cont1);
    cont1.addChild(&obj1);
    cont1.addChild(&cont2);
    cont2.addChild(&obj2);
    cont2.addChild(&obj3);

    run();

    ASSERT_THAT(getNumMatrices(), Eq(3));
    ASSERT_TRUE(MatrixEQ(getMatrixAt(0), obj1.getTransform(&stage)));
    ASSERT_TRUE(MatrixEQ(getMatrixAt(1), obj2.getTransform(&stage)));
    ASSERT_TRUE(MatrixEQ(getMatrixAt(2), obj3.getTransform(&stage)));
}

TEST_F(TransformationsBufferOrganizer_Test, DISABLED_EmptyParentHasNoEffect) {
    DisplayObject obj1;
    obj1.setWidth(37);
    DisplayObjectContainer emptyCont;
    emptyCont.setX(43);
    DisplayObject obj2;
    obj2.setHeight(11);
    DisplayObjectContainer cont2;
    cont2.setY(53);
    DisplayObject obj3;
    obj3.setScaleX(3);
    stage.addChild(&obj1);
    stage.addChild(&emptyCont);
    stage.addChild(&obj2);
    stage.addChild(&cont2);
    cont2.addChild(&obj3);

    run();

    ASSERT_THAT(getNumMatrices(), Eq(3));
    ASSERT_TRUE(MatrixEQ(getMatrixAt(0), obj1.getTransform(&stage)));
    ASSERT_TRUE(MatrixEQ(getMatrixAt(1), obj2.getTransform(&stage)));
    ASSERT_TRUE(MatrixEQ(getMatrixAt(2), obj3.getTransform(&stage)));
}
