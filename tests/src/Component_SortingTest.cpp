#include "gmock/gmock-matchers.h"
#include "ComponentContainer.h"

using namespace testing;
using namespace flash;

using Container = ComponentContainer;

size_t getAddress(const SpatialComponent& c) {
    return reinterpret_cast<size_t>(&c);
}

size_t getAddress(const int& c) {
    return reinterpret_cast<size_t>(&c);
}

class Component_SortingTest : public Test {
public:
    static const unsigned SIZE = 6;
    static const unsigned SPACIAL_SIZE = sizeof(SpatialComponent);
    static const unsigned DEPTH_SIZE = sizeof(int);

    void assertSort(const std::vector<int>& expectedOrder) {
        if (expectedOrder.size() > m_entities.size()) {
            FAIL();
        }
        auto spatialBaseAddr = std::numeric_limits<size_t>::max();
        auto depthBaseAddr = spatialBaseAddr;
        for (const auto& e : m_entities) {
            auto addr = getAddress(container->getSpatialComponent(*e));
            if (addr < spatialBaseAddr)
                spatialBaseAddr = addr;
            addr = getAddress(container->getDepthComponent(*e));
            if (addr < depthBaseAddr)
                depthBaseAddr = addr;
        }

        auto negativeStart = expectedOrder.size() - std::count(expectedOrder.cbegin(), expectedOrder.cend(), -1);

        std::vector<int> actualSpatialOrder = {};
        std::vector<int> actualDepthOrder = {};
        for (int i = 0; i < expectedOrder.size(); ++i) {
            const auto& e = *m_entities[i];
            auto addr = getAddress(container->getSpatialComponent(e));
            int spatialAddrIndex = (int) (addr - spatialBaseAddr) / SPACIAL_SIZE;
            actualSpatialOrder.push_back(spatialAddrIndex < negativeStart ? spatialAddrIndex : -1);

            addr = getAddress(container->getDepthComponent(e));
            int depthAddrIndex = (int) (addr - depthBaseAddr) / DEPTH_SIZE;
            actualDepthOrder.push_back(depthAddrIndex < negativeStart ? depthAddrIndex : -1);
        }

        ASSERT_THAT(actualSpatialOrder, Eq(expectedOrder));
        ASSERT_THAT(actualDepthOrder, Eq(expectedOrder));
    }

    void sort(const std::vector<int>& order) {
        for (int i = 0; i < order.size(); ++i) {
            container->getOrderComponent(*m_entities[i]) = order[i];
        }
        container->sort();
    }

    void sortAndAssert(const std::vector<int>& order) {
        sort(order);
        assertSort(order);
    }

    const Entity& createEntity() {
        const auto& entity = container->createEntity();
        m_entities.push_back(&entity);
        return entity;
    }

    void removeEntity(const Entity& e) {
        m_entities.erase(std::remove(m_entities.begin(), m_entities.end(), &e));
        container->removeEntity(e);
    }
    
    void setAllValuesForEntity(const Entity& e, int value) {
        container->getSpatialComponent(e).width = value;
        container->getDepthComponent(e) = value;
        container->getTextureData(e).textureId = (unsigned) value;
    }

    Container* container{nullptr};
    
protected:
    void SetUp() override {
        container = new Container(SIZE);

    }

    void TearDown() override {
        if (container) {
            delete container;
        }
        m_entities.clear();
    }

private:
    std::vector<const Entity*> m_entities;
};

TEST_F(Component_SortingTest, EmptyContainer) {
    container->sort();
}

TEST_F(Component_SortingTest, OneEntityNotAltered) {
    const auto& entity = createEntity();
    auto oldAddr = getAddress(container->getSpatialComponent(entity));
    container->sort();
    auto newAddr = getAddress(container->getSpatialComponent(entity));

    ASSERT_THAT(newAddr, Eq(oldAddr));
}

TEST_F(Component_SortingTest, SwappingTwoElements) {
    createEntity();
    createEntity();

    sortAndAssert({0, 1});
    sortAndAssert({1, 0});
}

TEST_F(Component_SortingTest, ComponentsArePreserved_whenTwoElementsSwapped) {
    auto& e1 = createEntity();
    auto& e2 = createEntity();

    setAllValuesForEntity(e1, 7);
    setAllValuesForEntity(e2, 11);
    container->getDepthComponent(e2) = 11;

    sort({0, 1});
    sort({1, 0});
    
    ASSERT_THAT(container->getSpatialComponent(e1).width, Eq(7));
    ASSERT_THAT(container->getSpatialComponent(e2).width, Eq(11));
    ASSERT_THAT(container->getDepthComponent(e1), Eq(7));
    ASSERT_THAT(container->getDepthComponent(e2), Eq(11));
}

TEST_F(Component_SortingTest, SomeChildrenAreRemovedInTheMiddle) {
    createEntity();
    auto& e2 = createEntity();
    auto& e3 = createEntity();
    createEntity();
    auto& e5 = createEntity();
    createEntity();

    removeEntity(e2);
    removeEntity(e3);
    removeEntity(e5);

    sortAndAssert({2, 0, 1});
    sortAndAssert({0, 1, 2});
}

TEST_F(Component_SortingTest, ForEachWalksThroughInSortedOrder) {
    auto& e1 = createEntity();
    auto& e2 = createEntity();
    auto& e3 = createEntity();

    setAllValuesForEntity(e1, 7);
    setAllValuesForEntity(e2, 11);
    setAllValuesForEntity(e3, 13);

    sort({2, 0, 1});

    std::vector<int> vals = {11, 13, 7};
    int i = 0;

    container->forEach([&i, &vals](SpatialComponent& comp, TextureData& textureData, int depth, int) {
        ASSERT_THAT(comp.width, FloatEq(vals[i]));
        ASSERT_THAT(depth, Eq(vals[i]));
        ASSERT_THAT(textureData.textureId, Eq(vals[i]));
        ++i;
    });

    sort({0, 1, 2});

    vals = {7, 11, 13};
    i = 0;

    container->forEach([&i, &vals](SpatialComponent& comp, TextureData& textureData, int depth, int) {
        ASSERT_THAT(comp.width, FloatEq(vals[i]));
        ASSERT_THAT(depth, Eq(vals[i]));
        ASSERT_THAT(textureData.textureId, Eq(vals[i]));
        ++i;
    });
}

TEST_F(Component_SortingTest, NegativeOrdersAreInTheEnd) {
    auto& e1 = createEntity();
    auto& e2 = createEntity();
    auto& e3 = createEntity();
    auto& e4 = createEntity();
    auto& e5 = createEntity();

    setAllValuesForEntity(e1, 1);
    setAllValuesForEntity(e2, 2);
    setAllValuesForEntity(e3, 3);
    setAllValuesForEntity(e4, 4);
    setAllValuesForEntity(e5, 5);

    sortAndAssert({0, -1, 1, -1, 2});

    std::vector<int> vals = {1, 3, 5};
    int i = 0;

    container->forEach([&i, &vals](SpatialComponent& comp, TextureData& textureData, int depth, int) {
        if (i < 3) {
            ASSERT_THAT(comp.width, FloatEq(vals[i]));
            ASSERT_THAT(depth, Eq(vals[i]));
            ASSERT_THAT(textureData.textureId, Eq(vals[i]));
        }
        ++i;
    });
}

TEST_F(Component_SortingTest, afterNegativeIsSetToNormal_dataIsNotHarmed) {
    auto& e1 = createEntity();
    auto& e2 = createEntity();
    auto& e3 = createEntity();
    auto& e4 = createEntity();
    auto& e5 = createEntity();
    
    setAllValuesForEntity(e1, 1);
    setAllValuesForEntity(e2, 2);
    setAllValuesForEntity(e3, 3);
    setAllValuesForEntity(e4, 4);
    setAllValuesForEntity(e5, 5);

    sort({0, -1, 1, -1, 2});
    sort({0, 1, 2, 3, 4});

    int i = 1;

    container->forEach([&i](SpatialComponent& comp, TextureData& textureData, int depth, int) {
        ASSERT_THAT(comp.width, FloatEq(i));
        ASSERT_THAT(depth, Eq(i));
        ASSERT_THAT(textureData.textureId, Eq(i));
        ++i;
    });
}

TEST_F(Component_SortingTest, ForEachDoesNotWalsThoughtNegativeOrderedComponents) {
    createEntity();
    createEntity();
    createEntity();
    createEntity();
    createEntity();

    sort({0, -1, 1, -1, 2});

    int i = 0;
    container->forEach([&i](SpatialComponent& comp, TextureData& textureData, int depth, int) {
        ++i;
    });
    ASSERT_THAT(i, Eq(3));
}
