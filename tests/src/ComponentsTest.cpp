#include "gmock/gmock-matchers.h"
#include "SpatialComponent.h"

using namespace testing;
using namespace flash;

using Container = SpatialComponentContainer;

namespace {
}

class ComponentTest : public Test {
public:
    static const unsigned SIZE = 4;

    Container* container{nullptr};

protected:
    void SetUp() override {
        container = new Container(SIZE);
    }

    void TearDown() override {
        if (container) {
            delete container;
        }
    }
};

TEST_F(ComponentTest, Fails_whenRequestedMoreThenSize) {
    for (int i = 0; i < SIZE; ++i) {
        container->createIndex();
    }
    ASSERT_DEATH(container->createIndex(), "");
}

TEST_F(ComponentTest, CreateIndexIsDifferent) {
    const auto& i1 = container->createIndex();
    const auto& i2 = container->createIndex();
    ASSERT_THAT(i1, Not(i2));
}

TEST_F(ComponentTest, AddComponentReturnsSameObj_ifSameIndexGiven) {
    const auto& i1 = container->createIndex();
    const auto& i2 = container->createIndex();
    auto& c1 = container->getComponent(i1);
    auto& c2 = container->getComponent(i2);
    c1.width += 1;
    c1.height += 1;
    ASSERT_THAT(c1.width, Not(c2.width));
    ASSERT_THAT(c1.height, Not(c2.height));
    ASSERT_THAT(container->getComponent(i1).width, FloatEq(c1.width));
    ASSERT_THAT(container->getComponent(i1).height, FloatEq(c1.height));
    ASSERT_THAT(container->getComponent(i1).width, Not(container->getComponent(i2).width));
    ASSERT_THAT(container->getComponent(i1).height, Not(container->getComponent(i2).height));
}

TEST_F(ComponentTest, NewIndexDdesNotFail_ifOldOnesAreRemoved) {
    const auto& i1 = container->createIndex();
    const auto& i2 = container->createIndex();
    for (int i = 2; i < SIZE; ++i) {
        container->createIndex();
    }
    container->removeIndex(i1);
    container->removeIndex(i2);
    container->createIndex();
    container->createIndex();
}

TEST_F(ComponentTest, RemoveIndexDoesNotAlterOthers) {
    const auto& i1 = container->createIndex();
    const auto& i2 = container->createIndex();
    const auto& i3 = container->createIndex();
    const auto& i4 = container->createIndex();
    auto& c1 = container->getComponent(i1);
    auto& c2 = container->getComponent(i2);
    auto& c3 = container->getComponent(i3);
    auto& c4 = container->getComponent(i4);

    c2.width += 2;
    c2.height += 2;
    auto c1Width = c1.width += 1;
    auto c1Height = c1.height += 1;
    auto c3Width = c3.width += 3;
    auto c3Height = c3.height += 3;
    auto c4Width = c4.width += 4;
    auto c4Height = c4.height += 4;

    container->removeIndex(i2);
    const auto& iNew = container->createIndex();
    auto& cNew = container->getComponent(iNew);
    cNew.width += 5;
    cNew.height += 5;

    c1 = container->getComponent(i1);
    c3 = container->getComponent(i3);
    c4 = container->getComponent(i4);

    ASSERT_THAT(c1Width, FloatEq(c1.width));
    ASSERT_THAT(c1Height, FloatEq(c1.height));
    ASSERT_THAT(c3Width, FloatEq(c3.width));
    ASSERT_THAT(c3Height, FloatEq(c3.height));
    ASSERT_THAT(c4Width, FloatEq(c4.width));
    ASSERT_THAT(c4Height, FloatEq(c4.height));
}