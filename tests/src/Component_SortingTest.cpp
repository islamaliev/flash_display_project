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

    Container* container{nullptr};

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

        std::vector<int> actualSpatialOrder = {};
        std::vector<int> actualDepthOrder = {};
        for (int i = 0; i < expectedOrder.size(); ++i) {
            const auto& e = *m_entities[i];
            auto addr = getAddress(container->getSpatialComponent(e));
            actualSpatialOrder.push_back((int) (addr - spatialBaseAddr) / SPACIAL_SIZE);

            addr = getAddress(container->getDepthComponent(e));
            actualDepthOrder.push_back((int) (addr - depthBaseAddr) / DEPTH_SIZE);
        }

        ASSERT_THAT(actualSpatialOrder, Eq(expectedOrder));
        ASSERT_THAT(actualDepthOrder, Eq(expectedOrder));
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
    auto& e1 = createEntity();
    auto& e2 = createEntity();

    container->getOrderComponent(e1) = 0;
    container->getOrderComponent(e2) = 1;
    container->sort();

    assertSort({0, 1});

    container->getOrderComponent(e1) = 1;
    container->getOrderComponent(e2) = 0;
    container->sort();

    assertSort({1, 0});
}

TEST_F(Component_SortingTest, ComponentsArePreserved_whenTwoElementsSwapped) {
    auto& e1 = createEntity();
    auto& e2 = createEntity();

    container->getOrderComponent(e1) = 0;
    container->getOrderComponent(e2) = 1;

    container->getSpatialComponent(e1).width = 7;
    container->getSpatialComponent(e2).width = 11;
    container->getDepthComponent(e1) = 7;
    container->getDepthComponent(e2) = 11;

    container->sort();

    container->getOrderComponent(e1) = 1;
    container->getOrderComponent(e2) = 0;
    container->sort();

    ASSERT_THAT(container->getSpatialComponent(e1).width, Eq(7));
    ASSERT_THAT(container->getSpatialComponent(e2).width, Eq(11));
    ASSERT_THAT(container->getDepthComponent(e1), Eq(7));
    ASSERT_THAT(container->getDepthComponent(e2), Eq(11));
}

TEST_F(Component_SortingTest, SomeChildrenAreRemovedInTheMiddle) {
    auto& e1 = createEntity();
    auto& e2 = createEntity();
    auto& e3 = createEntity();
    auto& e4 = createEntity();
    auto& e5 = createEntity();
    auto& e6 = createEntity();

    removeEntity(e2);
    removeEntity(e3);
    removeEntity(e5);

    container->getOrderComponent(e1) = 2;
    container->getOrderComponent(e4) = 0;
    container->getOrderComponent(e6) = 1;
    container->sort();

    assertSort({2, 0, 1});

    container->getOrderComponent(e1) = 0;
    container->getOrderComponent(e4) = 1;
    container->getOrderComponent(e6) = 2;
    container->sort();

    assertSort({0, 1, 2});
}
