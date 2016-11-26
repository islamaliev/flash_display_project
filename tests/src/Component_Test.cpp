#include "gmock/gmock-matchers.h"
#include "ComponentContainer.h"

using namespace testing;
using namespace flash;

using Container = ComponentContainer;

class Component_Test : public Test {
public:
    static const unsigned SIZE = 10;

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

TEST_F(Component_Test, GetComponentReturnsSameObj_ifSameEntityGiven) {
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
    // create entities
    const auto& e1 = container->createEntity();
    const auto& e2 = container->createEntity();
    const auto& e3 = container->createEntity();
    const auto& e4 = container->createEntity();
    const auto& e5 = container->createEntity();

    // just to make sure these values are not default
    std::vector<int> v = {1, 2, 3, 4, 5};
    ASSERT_THAT(v, Not(Contains(container->getSpatialComponent(e1).width)));
    ASSERT_THAT(v, Not(Contains(container->getDepthComponent(e1))));
    ASSERT_THAT(v, Not(Contains(container->getOrderComponent(e1))));

    // assign unique values
    container->getSpatialComponent(e1).width = 1;
    container->getSpatialComponent(e2).width = 2;
    container->getSpatialComponent(e3).width = 3;
    container->getSpatialComponent(e4).width = 4;
    container->getSpatialComponent(e5).width = 5;
    container->getDepthComponent(e1) = 1;
    container->getDepthComponent(e2) = 2;
    container->getDepthComponent(e3) = 3;
    container->getDepthComponent(e4) = 4;
    container->getDepthComponent(e5) = 5;
    container->getOrderComponent(e1) = 1;
    container->getOrderComponent(e2) = 2;
    container->getOrderComponent(e3) = 3;
    container->getOrderComponent(e4) = 4;
    container->getOrderComponent(e5) = 5;

    // remove entities
    container->removeEntity(e1);
    container->removeEntity(e3);
    container->removeEntity(e5);

    // create new one
    const auto& e6 = container->createEntity();
    const auto& e7 = container->createEntity();
    const auto& e8 = container->createEntity();

    // set uniques values for new entity's components
    container->getSpatialComponent(e6).width = 6;
    container->getSpatialComponent(e7).width = 7;
    container->getSpatialComponent(e8).width = 8;
    container->getDepthComponent(e6) = 6;
    container->getDepthComponent(e7) = 7;
    container->getDepthComponent(e8) = 8;
    container->getOrderComponent(e6) = 6;
    container->getOrderComponent(e7) = 7;
    container->getOrderComponent(e8) = 8;

    ASSERT_THAT(container->getSpatialComponent(e2).width, FloatEq(2));
    ASSERT_THAT(container->getSpatialComponent(e4).width, FloatEq(4));
    ASSERT_THAT(container->getDepthComponent(e2), Eq(2));
    ASSERT_THAT(container->getDepthComponent(e4), Eq(4));
    ASSERT_THAT(container->getOrderComponent(e2), Eq(2));
    ASSERT_THAT(container->getOrderComponent(e4), Eq(4));
}

TEST_F(Component_Test, UtilizedEntityHasInitialDefaultValues) {
    const auto& i1 = container->createEntity();
    const auto& i2 = container->createEntity();
    const auto& i3 = container->createEntity();
    const auto& i4 = container->createEntity();

    auto initialWidth = container->getSpatialComponent(i1).width;
    auto initialDepth = container->getDepthComponent(i1);
    auto initialOrder = container->getOrderComponent(i1);

    container->getSpatialComponent(i1).width += 1;
    container->getSpatialComponent(i2).width += 2;
    container->getSpatialComponent(i3).width += 3;
    container->getSpatialComponent(i4).width += 4;
    container->getDepthComponent(i1) += 1;
    container->getDepthComponent(i2) += 2;
    container->getDepthComponent(i3) += 3;
    container->getDepthComponent(i4) += 4;
    container->getOrderComponent(i1) += 1;
    container->getOrderComponent(i2) += 2;
    container->getOrderComponent(i3) += 3;
    container->getOrderComponent(i4) += 4;

    container->removeEntity(i2);
    const auto& iNew = container->createEntity();
    auto newWidth = container->getSpatialComponent(iNew).width;
    auto newDepth = container->getDepthComponent(iNew);
    auto newOrder = container->getOrderComponent(iNew);

    ASSERT_THAT(newWidth, FloatEq(initialWidth));
    ASSERT_THAT(newDepth, Eq(initialDepth));
    ASSERT_THAT(newOrder, Eq(initialOrder));
}

TEST_F(Component_Test, NewValuesCanBeSavedToUtilizedEntity) {
    container->createEntity();
    const auto& i2 = container->createEntity();
    container->createEntity();
    container->createEntity();

    container->removeEntity(i2);
    const auto& iNew = container->createEntity();
    container->getSpatialComponent(iNew).width = 5;
    container->getDepthComponent(iNew) = 5;
    container->getOrderComponent(iNew) = 5;

    auto newWidth = container->getSpatialComponent(iNew).width;
    auto newDepth = container->getDepthComponent(iNew);
    auto newOrder = container->getOrderComponent(iNew);

    ASSERT_THAT(newWidth, FloatEq(5));
    ASSERT_THAT(newDepth, Eq(5));
    ASSERT_THAT(newOrder, Eq(5));
}

TEST_F(Component_Test, ForEach) {
    using EntVec = std::vector<std::decay_t<decltype(container->createEntity())>>;
    EntVec entities = EntVec(SIZE);
    for (int i = 0; i < SIZE; ++i) {
        entities[i] = container->createEntity();
    }
    auto initWidth = container->getSpatialComponent(entities[0]).width;
    auto initTextureId = container->getTextureData(entities[0]).textureId;
    container->forEach([](SpatialComponent& comp, TextureData& textureData, int, int) {
        comp.width += 5;
        textureData.textureId += 5;
    });
    for (int i = 0; i < SIZE; ++i) {
        ASSERT_THAT(container->getSpatialComponent(entities[i]).width, FloatEq(initWidth + 5));
        ASSERT_THAT(container->getTextureData(entities[i]).textureId, Eq(initTextureId + 5));
    }
}

TEST_F(Component_Test, ForEachTextureData) {
    using EntVec = std::vector<std::decay_t<decltype(container->createEntity())>>;
    EntVec entities = EntVec(SIZE);
    for (int i = 0; i < SIZE; ++i) {
        entities[i] = container->createEntity();
    }
    auto initTextureId = container->getTextureData(entities[0]).textureId;
    container->forEachTextureData([](TextureData& textureData, int) {
        textureData.textureId += 5;
    });
    for (int i = 0; i < SIZE; ++i) {
        ASSERT_THAT(container->getTextureData(entities[i]).textureId, Eq(initTextureId + 5));
    }
}

