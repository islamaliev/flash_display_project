#include "gmock/gmock-matchers.h"
#include "SpatialComponent.h"

using namespace testing;
using namespace flash;

using Container = SpatialComponentContainer;

namespace {
}

class Component_Test : public Test {
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

TEST_F(Component_Test, CreateEntityFails_whenRequestedMoreThanSize) {
    for (int i = 0; i < SIZE; ++i) {
        container->createEntity();
    }
    ASSERT_DEATH(container->createEntity(), "");
}

TEST_F(Component_Test, EachCreateEntityGivesDifferentResult) {
    const auto& i1 = container->createEntity();
    const auto& i2 = container->createEntity();
    ASSERT_THAT(i1, Not(i2));
}

TEST_F(Component_Test, AddComponentReturnsSameObj_ifSameEntityGiven) {
    const auto& i1 = container->createEntity();
    const auto& i2 = container->createEntity();
    auto& c1 = container->getSpatialComponent(i1);
    auto& c2 = container->getSpatialComponent(i2);
    c1.width += 1;
    c1.height += 1;
    ASSERT_THAT(c1.width, Not(c2.width));
    ASSERT_THAT(c1.height, Not(c2.height));
    ASSERT_THAT(container->getSpatialComponent(i1).width, FloatEq(c1.width));
    ASSERT_THAT(container->getSpatialComponent(i1).height, FloatEq(c1.height));
    ASSERT_THAT(container->getSpatialComponent(i1).width, Not(container->getSpatialComponent(i2).width));
    ASSERT_THAT(container->getSpatialComponent(i1).height, Not(container->getSpatialComponent(i2).height));
}

TEST_F(Component_Test, NewEntityDoesNotFail_ifOldOnesAreRemoved) {
    const auto& i1 = container->createEntity();
    const auto& i2 = container->createEntity();
    for (int i = 2; i < SIZE; ++i) {
        container->createEntity();
    }
    container->removeEntity(i1);
    container->removeEntity(i2);
    container->createEntity();
    container->createEntity();
}

TEST_F(Component_Test, RemoveEntityDoesNotAlterOthers) {
    const auto& i1 = container->createEntity();
    const auto& i2 = container->createEntity();
    const auto& i3 = container->createEntity();
    const auto& i4 = container->createEntity();
    auto& c1 = container->getSpatialComponent(i1);
    auto& c2 = container->getSpatialComponent(i2);
    auto& c3 = container->getSpatialComponent(i3);
    auto& c4 = container->getSpatialComponent(i4);

    c2.width += 2;
    auto c1Width = c1.width += 1;
    auto c3Width = c3.width += 3;
    auto c4Width = c4.width += 4;

    container->removeEntity(i2);
    const auto& iNew = container->createEntity();
    auto& cNew = container->getSpatialComponent(iNew);
    cNew.width += 5;

    c1 = container->getSpatialComponent(i1);
    c3 = container->getSpatialComponent(i3);
    c4 = container->getSpatialComponent(i4);

    ASSERT_THAT(c1Width, FloatEq(c1.width));
    ASSERT_THAT(c3Width, FloatEq(c3.width));
    ASSERT_THAT(c4Width, FloatEq(c4.width));
}

TEST_F(Component_Test, UtilizedEntityHasInitialDefaultValues) {
    const auto& i1 = container->createEntity();
    const auto& i2 = container->createEntity();
    const auto& i3 = container->createEntity();
    const auto& i4 = container->createEntity();

    auto initialValue = container->getSpatialComponent(i1).width;

    container->getSpatialComponent(i1).width += 1;
    container->getSpatialComponent(i2).width += 2;
    container->getSpatialComponent(i3).width += 3;
    container->getSpatialComponent(i4).width += 4;

    container->removeEntity(i2);
    const auto& iNew = container->createEntity();
    auto& cNew = container->getSpatialComponent(iNew);

    ASSERT_THAT(cNew.width, FloatEq(initialValue));
}

TEST_F(Component_Test, ForEach) {
    using EntVec = std::vector<std::decay_t<decltype(container->createEntity())>>;
    EntVec entities  = EntVec(SIZE);
    for (int i = 0; i < SIZE; ++i) {
        entities[i] = container->createEntity();
    }
    auto initValue = container->getSpatialComponent(entities[0]).width;
    container->forEachComponent([](SpatialComponent& comp) {
        comp.width += 5;
    });
    for (int i = 0; i < SIZE; ++i) {
        ASSERT_THAT(container->getSpatialComponent(entities[0]).width, FloatEq(initValue + 5));
    }
}

